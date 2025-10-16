#!/usr/bin/perl -w

BEGIN
{
	my $scriptdir = __FILE__;
	$scriptdir =~ s/[^\\\/]+$//;
	push @INC, $scriptdir;
}

#
# genld-diab.pl - generate Diab linker script
#
# $Id$
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
# so if core 0 isn't used it still gets 8 CSAs.
if($sysdesc->{'-corecsas'}[0] == 0)
{
	$sysdesc->{'-corecsas'}[0] = 8;
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
		$line =~ s/\bGENLD_csaCore(\d+)_NCSA\b/$sysdesc->{"-corecsas"}[$1]/ge;
		return $line;
	}
);

$LdBackend->beginOutputSectionMappings();

$LdBackend->beginMemoryBlockMappings('int_rom_vect');

# Entry code and vectors
$LdBackend->printOutputSection("text.bootword", 'RESET', undef, ['MK_bootword']);
$LdBackend->printOutputSection("text.reset", 'RESET', undef, ['MK_reset']);
$LdBackend->printOutputSection("text.vectors", 'RESET', undef, ['MK_exctable']);

$LdBackend->endMemoryBlockMappings('int_rom_vect');

$LdBackend->beginMemoryBlockMappings('int_rom');

# Text
$LdBackend->printOutputSection("text", 'TEXT', undef, ['.text', '.mk_text', '.os_text', '.rdata']);

# Readonly data
$LdBackend->printOutputSection("rodata", 'RODATA', undef, undef, undef, '__GLBL_RODATA_END');

$LdBackend->endMemoryBlockMappings('int_rom');

# Data sections to the core-local memories
# Core 0 catches all core-unspecific data and therefore must be last!
for (my $coreId = 0; $coreId < $sysdesc->{'-numcores'}; ++$coreId)
{
	$LdBackend->beginMemoryBlockMappings("int_ram_core$coreId");

	# Stacks
	$LdBackend->printComment("Stacks on core $coreId");

	# emit all symbols for Os thread stacks
	my @stacks = qw(
		kernel
		aux1
		aux2
		idleshutdown
		blocker
		errorhook
		protectionHook
	);

	for my $name (@stacks)
	{
		my $stack = "c$coreId"."_".$name."Stack";
		my $stacksym = "mk_stack_MK_$stack";
		my $lcname = lc $name;
		my $file = "Mk_c$coreId"."_$lcname"."_stack.o";

		$LdBackend->printOutputSection($stacksym, 'STACK', [$file], undef, "MK_RSA_MK_$stack", "MK_RLA_MK_$stack");
		$LdBackend->printBufferGap("MK_RSA_MK_$stack", "MK_RLA_MK_$stack");
	}

	my @threadStacks = ();
	my $numSlots = $sysdesc->{'-num-thread-slots'}[$coreId] || 0;
	if ($numSlots == 1)
	{
		push @threadStacks, [ "MK_threadStack$coreId", "mk_stack_MK_threadStack$coreId" ];
	}
	else
	{
		foreach my $stackId (0 .. $numSlots-1)
		{
			push @threadStacks, [ "MK_threadStack".$coreId."_slot$stackId", "mk_stack_MK_threadStack".$coreId."_slot$stackId" ];
		}
	}

	# These stacks are generated. Their sections are chosen using attributes.
	foreach my $stack (@threadStacks) {
		my ($stack, $stacksym) = @$stack;
		$LdBackend->printOutputSection($stacksym, 'STACK', undef, [".bss.$stacksym"], "MK_RSA_$stack", "MK_RLA_$stack");
		$LdBackend->printBufferGap("MK_RSA_$stack", "MK_RLA_$stack");
	}

	$LdBackend->printComment(
		"--------------------------------------------------------",
		"Memory regions for the MK and QM-OS data on core $coreId",
		"--------------------------------------------------------"
	);

	# microkernel data
	$LdBackend->printOutputSection("MK_Ram_data_C$coreId", 'DATA',
		["Mk*_c${coreId}_*", "Ioc_data_kern_c${coreId}_*"],
		undef, "MK_RSA_MK_Ram_C$coreId", undef, "MK_RDA_MK_Ram_C$coreId");

	$LdBackend->printOutputSection("MK_Ram_bss_C$coreId", 'BSS',
		["Mk*_c${coreId}_*", "Ioc_data_kern_c${coreId}_*"],
		undef, "MK_BSA_MK_Ram_C$coreId", "MK_RLA_MK_Ram_C$coreId");

	$LdBackend->printBufferGap("MK_RSA_MK_Ram_C$coreId", "MK_RLA_MK_Ram_C$coreId");

	# QM-OS data
	$LdBackend->printOutputSection("MK_OsRam_data_C$coreId", 'DATA', undef,
		[".data.core$coreId", ".data.shared.core$coreId"],
		"MK_RSA_MK_OsRam_C$coreId", undef, "MK_RDA_MK_OsRam_C$coreId");

	$LdBackend->printOutputSection("MK_OsRam_bss_C$coreId", 'BSS', undef,
		[".bss.core$coreId", ".bss.shared.core$coreId"],
		"MK_BSA_MK_OsRam_C$coreId", "MK_RLA_MK_OsRam_C$coreId");

	$LdBackend->printBufferGap("MK_RSA_MK_OsRam_C$coreId", "MK_RLA_MK_OsRam_C$coreId");


	$LdBackend->endMemoryBlockMappings("int_ram_core$coreId");
} # End of coreId loop

$LdBackend->printComment(
	"--------------------------------------------------------",
	"Memory regions for the MK and QM-OS data (core spanning)",
	"--------------------------------------------------------"
);

$LdBackend->beginMemoryBlockMappings("int_ram_core0");
$LdBackend->printOutputSection("MK_Ram_data", 'DATA',
	["Mk_*", "Ioc_data_kern_shared*"],
	undef, "MK_RSA_MK_Ram", undef, "MK_RDA_MK_Ram");
$LdBackend->printOutputSection("MK_Ram_bss", 'BSS',
	["Mk_*", "Ioc_data_kern_shared*"],
	undef, "MK_BSA_MK_Ram", "MK_RLA_MK_Ram");
$LdBackend->printBufferGap("MK_RSA_MK_Ram", "MK_RLA_MK_Ram");

$LdBackend->printOutputSection("MK_OsRam_data", 'DATA',
	["kern-*", "TRICORE-*", "Os_*"], undef,
	"MK_RSA_MK_OsRam", undef, "MK_RDA_MK_OsRam");
$LdBackend->printOutputSection("MK_OsRam_bss", 'BSS',
	["kern-*", "TRICORE-*", "Os_*"], undef,
	"MK_BSA_MK_OsRam", "MK_RLA_MK_OsRam");
$LdBackend->printBufferGap("MK_RSA_MK_OsRam", "MK_RLA_MK_OsRam");
$LdBackend->endMemoryBlockMappings("int_ram_core0");

for (my $coreId = 0; $coreId < $sysdesc->{'-numcores'}; ++$coreId)
{
	# only process applications which run on the current core
	my @coreapps = grep { $_->{'-core'} == $coreId } @{$sysdesc->{'-app'}};
	next if @coreapps==0;

	$LdBackend->printComment(
		"---------------------------------------------------------",
		"Private memory regions of the application on core $coreId",
		"---------------------------------------------------------"
	);

	$LdBackend->beginMemoryBlockMappings("int_ram_core$coreId");
	foreach my $app (@coreapps) {
		printPrivateObjectRegion($app, $coreId);
	}
	$LdBackend->endMemoryBlockMappings("int_ram_core$coreId");

} # End of coreId loop


# Anonymous catch-all sections
$LdBackend->printComment(
	"-----------------------------------------------------",
	"Anonymous catch-all sections for everything remaining",
	"-----------------------------------------------------"
);

$LdBackend->beginMemoryBlockMappings("int_ram_core0");
$LdBackend->printOutputSection("data.anon", 'DATA', undef, undef, "MK_ANON_DATA", "MK_ANON_DATA_END", "MK_ANON_IDAT");
$LdBackend->printOutputSection("bss.anon", 'BSS', undef, undef, "MK_ANON_BSS", "MK_ANON_BSS_END");
$LdBackend->endMemoryBlockMappings("int_ram_core0");

foreach my $obj (@{$sysdesc->{'-sysobj'}})
{
	$LdBackend->printComment("Empty private Data of system object $obj");
	printSymbolsForEmptyRegion($obj);
}

foreach my $mr (sort (keys %{$sysdesc->{'-mr'}}))
{
	$LdBackend->printComment("symbols for user configured memory region $mr");

	my $obj = $sysdesc->{'-mr'}{$mr};
	foreach my $mr_sym (@{$obj}{qw(RSA RLA BSA IDAT)})
	{
		next unless defined $mr_sym;
		my $dest_adr = "MK_DUMMY_ADR";

		if($mr_sym =~ /=/) {
			($mr_sym,$dest_adr) = ($`,$');
		}

		$LdBackend->printSymbolDefinition($mr_sym, $dest_adr);
	}
	GenldCommon::printOut("\n");
}

$LdBackend->endOutputSectionMappings();

GenldCommon::finalize();

exit 0;

################ HELPER FUNCTIONS ################

sub printSymbolsForEmptyRegion
{
	my ($name) = @_;
	$LdBackend->printSymbolDefinition("MK_RSA_$name", 0);
	$LdBackend->printSymbolDefinition("MK_RLA_$name", 0);
	$LdBackend->printSymbolDefinition("MK_RDA_$name", 0);
	$LdBackend->printSymbolDefinition("MK_BSA_$name", 0);
	GenldCommon::printOut("\n");
}

sub printPrivateObjectRegion
{
	my ($obj, $coreId) = @_;

	my $name    = $obj->{'name'};
	my $objtype = $obj->{'type'};
	my $files   = $obj->{'files'};

	if ( @$files == 0 ) {
		$LdBackend->printComment("$objtype $name --- NO FILES");
		printSymbolsForEmptyRegion($name);

	} else {
		my $data = "MK_RSA_$name";
		my $dend = "MK_RLA_$name";
		my $idat = "MK_RDA_$name";
		my $bss  = "MK_BSA_$name";
		$LdBackend->printOutputSection("data_C$coreId.$name", 'DATA', $files, undef, $data, undef, $idat);
		$LdBackend->printOutputSection("bss_C$coreId.$name", 'BSS', $files, undef, $bss, $dend);
		$LdBackend->printBufferGap($data, $dend);
	}

	if($objtype eq 'OS-Application')
	{
		$LdBackend->printSymbolDefinition("IOC_RSA_READABLE_$name", "\"BOARD_C${coreId}_RAM_BEG\"");
		$LdBackend->printSymbolDefinition("IOC_RLA_READABLE_$name", "\"BOARD_C${coreId}_URAM_END\"");
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
# vi:set ts=4:
