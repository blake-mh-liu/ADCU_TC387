#!/usr/bin/perl -w

BEGIN
{
	my $scriptdir = __FILE__;
	$scriptdir =~ s/[^\\\/]+$//;
	push @INC, $scriptdir;
}

#
# genld-TRICORE.pl - generate tasking linker script
#
# Copyright 1998-2016 Elektrobit Automotive GmbH
# All rights exclusively reserved for Elektrobit Automotive GmbH,
# unless expressly agreed to otherwise.
#

use GenldCommon;
use GenldArchTricore;

# parseArgs will die if there is an error
push @GenldCommon::usage_fns, \&GenldArchTricore::usage;
my $sysdesc = GenldCommon::parseArgs(\&GenldArchTricore::parseArgs);

# Check that we got everything needed
GenldCommon::usage("Number of CSA counts given with -corecsas does not match number of cores given with -numcores") if $sysdesc->{'-numcores'} != @{$sysdesc->{'-corecsas'}};

# In our tests we need CSAs on core 0 (because it's the HW's "master-core"),
# so if core 0 isn't used it still gets 16 CSAs.
if($sysdesc->{'-corecsas'}[0] == 0)
{
	$sysdesc->{'-corecsas'}[0] = 16;
}

my $LdBackend = $sysdesc->{'backend'};
$LdBackend->setArchCharacteristics(\%GenldArchTricore::osecTypes, \%GenldArchTricore::memoryBlocks);

# process include files
GenldCommon::processIncludes(
	sub
	{
		my ($line) = @_;
		# We need to replace the GENLD_csaCorex_NCSA uses in the included file,
		# because DIAB does not allow the use of symbols within MEMORY
		$line =~ s/\bGENLD_csaCore(\d+)_NCSA\b/$1<$sysdesc->{'-numcores'}?$sysdesc->{"-corecsas"}[$1]:0/ge;
		return $line;
	}
);

$LdBackend->beginOutputSectionMappings();

# Define symbols containing the number of CSAs for each core
$LdBackend->printComment( "Number of CSAs for each core" );
for (my $coreid=0; $coreid < @{$sysdesc->{"-corecsas"}}; $coreid++)
{
	$LdBackend->printSymbolDefinition("OS_csaCore${coreid}_NCSA", $sysdesc->{"-corecsas"}[$coreid]);
}
my $aUserCoreOverride = $sysdesc->{"-map-all-user-ram-to-core"};

$LdBackend->beginMemoryBlockMappings('int_rom_vect');

# Entry code and vectors
if ( defined $sysdesc->{"-hv"} )
{
	$LdBackend->printOutputSection("TMPL_StartupHv", 'RESET', undef, ['TMPL_StartupHv']);
}
$LdBackend->printOutputSection("TMPL_Startup", 'RESET', undef, ['TMPL_Startup']);
$LdBackend->printOutputSection("OS_Vectors", 'RESET', undef, ['OS_InterruptVectors', 'OS_StartupVectors', 'OS_ExceptionVectors']);

$LdBackend->endMemoryBlockMappings('int_rom_vect');

$LdBackend->beginMemoryBlockMappings('int_rom');

# Text
$LdBackend->printOutputSection("text", 'TEXT', undef, undef, '__GLBL_TEXT_START', '__GLBL_TEXT_END');

# TSPI section (enables Synopsis VDK Instrumentation)
if ( defined $sysdesc->{"-use-Synoposys-VDK-Instrumentation"} )
{
	$LdBackend->printOutputSection(".tspi", 'TEXT', undef, ['tspi']);
}

# Small readonly data
$LdBackend->printOutputSection("srodata", 'SMALL_RODATA', undef, undef,
	'__GLBL_SMALL_RODATA_START', '__GLBL_SMALL_RODATA_END');
# Readonly data
$LdBackend->printOutputSection("rodata", 'RODATA', undef, undef, undef, '__GLBL_RODATA_END');
# read-only data may be embedded in the code, so make sure it's readable, too
$LdBackend->printSymbolDefinition("__GLBL_RODATA_START", '"__GLBL_TEXT_START"');

$LdBackend->endMemoryBlockMappings('int_rom');

# Data sections to the core-local memories
# Core 0 catches all core-unspecific data and therefore must be last!
for (my $coreid=$sysdesc->{'-numcores'}-1; $coreid>=0; $coreid--)
{
	$LdBackend->beginMemoryBlockMappings("int_ram_core$coreid");

	# Stacks
	$LdBackend->printOutputSection("stacks.TRICORE_core$coreid", 'STACK', undef,
		[ ".bss.core$coreid.os_kernstack*" ], undef, "KERN_STACK_END_CORE$coreid"
	);

	$LdBackend->printOutputSection("tstacks.TRICORE_core$coreid", 'STACK', undef,
		[ ".bss.core$coreid.os_taskstack*" ]
	);

	if (not defined $aUserCoreOverride) {
		# Private data/bss sections
		my @coreapps = grep { $_->{'-core'} eq $coreid } (@{$sysdesc->{'-app'}});
		foreach my $app (@coreapps) {
			printPrivateObjectRegion($app, $coreid);
		}
	}

	# Catch-all for core-specific data
	$LdBackend->printOutputSection("data.TRICORE_core$coreid", 'DATA', undef,
		[ ".data.core$coreid", ".data.shared.core$coreid" ],
		"__STARTDATA_C$coreid", "__ENDDATA_C$coreid", "__INITDATA_C$coreid");

	$LdBackend->printOutputSection("bss.TRICORE_core$coreid", 'BSS', undef,
		[ ".bss.core$coreid", ".bss.shared.core$coreid" ],
		"__STARTBSS_C$coreid", "__ENDBSS_C$coreid");

	$LdBackend->endMemoryBlockMappings("int_ram_core$coreid");
}

# Place OS variables which are shared among all cores.
# Let's map them to core 0.
$LdBackend->beginMemoryBlockMappings("int_ram_core0");
$LdBackend->printOutputSection(
	"data.TRICORE_shared_os", 'DATA', undef,
	[ ".data.shared.os" ],
	"__STARTDATA_SHARED_OS", "__ENDDATA_SHARED_OS", "__INITDATA_SHARED_OS");
$LdBackend->printOutputSection("bss.TRICORE_shared_os", 'BSS', undef,
	[ ".bss.shared.os" ],
	"__STARTBSS_SHARED_OS", "__ENDBSS_SHARED_OS");
$LdBackend->endMemoryBlockMappings("int_ram_core0");

if (defined $aUserCoreOverride) {

	$LdBackend->beginMemoryBlockMappings("int_ram_core$aUserCoreOverride");

	# When the user wants to use SDAs, we map all user specific variables to this one core.
	my $firstObj = undef;
	for (my $coreid = 0; $coreid < $sysdesc->{'-numcores'}; $coreid++) {
		my @coreapps = grep { $_->{'-core'} eq $coreid } (@{$sysdesc->{'-app'}});
		foreach my $app (@coreapps) {
			$firstObj ||= $app;
			printPrivateObjectRegion($app, $coreid);
		}
	}
	# Also map the ANON section to this core.
	$LdBackend->printOutputSection("data.TRICORE", 'DATA', undef, undef,
		"__STARTDATA_ANON", "__ENDDATA_ANON", "__INITDATA_ANON");

	$LdBackend->printOutputSection("bss.TRICORE", 'BSS', undef, undef,
		"__STARTBSS_ANON", "__ENDBSS_ANON");

	$LdBackend->printDummySdaSections();

	$LdBackend->endMemoryBlockMappings("int_ram_core$aUserCoreOverride");

	# Mark the begin of user data, so an SDA base address can be set.
	if (defined $firstObj) {
		my $firstObjName = $firstObj->{'name'};
		$LdBackend->printSymbolDefinition("__USER_DATA_CORE_OVERRIDE_BEGIN", "__DATA_$firstObjName");
	} else {
		$LdBackend->printSymbolDefinition("__USER_DATA_CORE_OVERRIDE_BEGIN", "__STARTDATA_ANON");
	}

} else {

	$LdBackend->printSymbolDefinition("__USER_DATA_CORE_OVERRIDE_BEGIN", 0);

	# Catch-all for data/bss not assigned to a specific core
	# Assigned to core 0
	$LdBackend->beginMemoryBlockMappings("int_ram_core0");
	$LdBackend->printOutputSection("data.TRICORE", 'DATA', undef, undef,
		"__STARTDATA_ANON", "__ENDDATA_ANON", "__INITDATA_ANON");

	$LdBackend->printOutputSection("bss.TRICORE", 'BSS', undef, undef,
		"__STARTBSS_ANON", "__ENDBSS_ANON");
	$LdBackend->endMemoryBlockMappings("int_ram_core0");

}

# initial stack pointer for startup code (must be 8-byte aligned)
$LdBackend->printSymbolDefinition("OS_INITIAL_SP", '("KERN_STACK_END_CORE0" & 0xfffffff8)');

$LdBackend->endOutputSectionMappings();

GenldCommon::finalize();

exit 0;

sub printPrivateObjectRegion
{
	my ($obj, $coreId) = @_;

	my $name    = $obj->{'name'};
	my $objtype = $obj->{'type'};
	my $files   = $obj->{'files'};

	if ( @$files == 0 ) {
		GenldCommon::printOut("/* $objtype $name --- NO FILES */");

		$LdBackend->printSymbolDefinition("__DATA_$name", 0);
		$LdBackend->printSymbolDefinition("__DEND_$name", 0);
		$LdBackend->printSymbolDefinition("__IDAT_$name", 0);
		$LdBackend->printSymbolDefinition("__IEND_$name", 0);

	} else {
		my $idat = "__IDAT_$name";
		my $iend = "__IEND_$name";
		my $data = "__DATA_$name";
		my $dend = "__DEND_$name";
		$LdBackend->printOutputSection("data_C$coreId.$name", 'DATA', $files, undef, $data, undef, $idat, $iend);
		$LdBackend->printOutputSection("bss_C$coreId.$name", 'BSS', $files, undef, undef, $dend);
		$LdBackend->printBufferGap($data, $dend);
	}

	GenldCommon::printOut("\n");

	# recurse to contained objects
	foreach my $containedObjectType (@{$obj->{'contains'}})
	{
		foreach my $containedObject (@{$obj->{$containedObjectType}})
		{
			printPrivateObjectRegion($containedObject, $coreId);
		}
	}
}

# Editor settings: DO NOT DELETE
# vi:set ts=4 sw=4 noet tw=100:
