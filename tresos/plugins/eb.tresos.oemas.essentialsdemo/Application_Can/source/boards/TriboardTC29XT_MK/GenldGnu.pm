package GenldGnu;

=head1 The C<GenldGnu> package

This package implements the L<GenldBackend> interface for the GNU ld linker that is typically used
with GCC-based toolchains.
This package's documentation only describes the specifics for this toolchain. The common
documentation can be found in L<GenldBackend>.

=head2 Toolchain-specific output section attributes

The following attributes are expected by the C<GenldGnu> back end in the output section type
specifications:

=over

=item C<_gnu_extraattr>: Optional extra attributes for an output section definition

This optional attribute can be used to give extra attributes that are appended to the definition of
an output section. Currently, the C<NOLOAD> attribute is used to instruct the linker that the
section has no contents that need to be loaded during startup.

=back

=cut

use GenldCommon;

our @ISA;

BEGIN
{
	require GenldBackend;
	push @ISA, 'GenldBackend';
}

sub _new
{
	my $pkg = shift;
	my $self = $pkg->SUPER::_new(@_);

	# remembers the memory block we are currently mapping to,
	# undef if none
	$self->{'currentMemoryBlock'} = undef;

	return $self;
}

sub printComment
{
	my $self = shift;
	GenldCommon::printOut("/*");
	GenldCommon::printOut(" * $_") foreach(@_);
	GenldCommon::printOut("*/");
}

sub beginOutputSectionMappings
{
	my $self = shift;
	GenldCommon::printOut("SECTIONS");
	GenldCommon::printOut("{");
}

sub endOutputSectionMappings
{
	my $self = shift;
	GenldCommon::printOut("}");
}

sub beginMemoryBlockMappings
{
	my $self = shift;
	my ($currentMemoryBlock, $phdr) = @_;

	$self->{currentMemoryBlock} = $currentMemoryBlock;
	$self->{'phdr'} = $phdr;
	$self->{'osecCount'} = 0;
}

sub endMemoryBlockMappings
{
	my $self = shift;
	my ($block) = @_;

	$self->{currentMemoryBlock} = undef;
	$self->{'phdr'} = undef;
	$self->{'osecCount'} = undef;
}

sub printSymbolDefinition
{
	my $self = shift;
	my ($symbol, $value) = @_;
	GenldCommon::printOut("$symbol = $value;");
}

sub printBufferGap
{
	my $self = shift;
	my ($start, $end, $gap) = @_;
	$gap ||= 8;

	if(defined $start && defined $end)
	{
		GenldCommon::printOut(". += (($end > $start) ? $gap : 0); /* gap between regions */\n");
	}
	else
	{
		GenldCommon::printOut(". += $gap; /* gap between regions */\n");
	}
}

sub _val_to_dec
{
	my $self = shift;
	my ($value) = @_;

	if ($value =~ /^0x[0-9A-F]+$/i)
	{
		$value = hex($value);
	}

	return $value;
}

# prints an output section
# $osecName:   name of the output section
# $osecType:   type of the output section (key to %osecTypes)
# $inFiles:    ref to array with input files/file patterns
#                each entry is either: a scalar, representing an input file name/pattern
#                a hash with entries:
#                	file => input file name/pattern
#                	lib  => library file name/pattern
# $inSections: ref to array with input sections/input-section patterns, undef for section-type-dependent defaults
#
sub printOutputSection
{
	my $self = shift;
	my ($osecName, $osecType, $inFiles, $inSections, $startSymbol, $endSymbol, $initSymbol,
		$initEndSymbol, $preciseFiles, $startAlign, $endAlign) = @_;

	my $ot = $self->{osecTypes}{$osecType};
	my $disableRomInit = $GenldCommon::sysdesc{'-disableRomInit'};
	die "Unknown section type: $osecType" unless ref $ot eq 'HASH';

	$self->{'osecCount'}++;
	$self->printComment("Output section $osecName (Type $osecType)");

	my $typestr = defined $ot->{_gnu_extraattr} ? "($ot->{_gnu_extraattr}) " : '';
	GenldCommon::printOut("$osecName $typestr:");
	GenldCommon::printOut("{");

	# Override region alignment from architecture definition
	if (defined $startAlign)
	{
		$startAlign = $self->_val_to_dec($startAlign);
	}

	# Override end alignment from architecture defintion
	if (defined $endAlign)
	{
		$endAlign = $self->_val_to_dec($endAlign);
	}

	# Get the alignment from the architecture configuration file or
	# use the size argument to overwrite the alignment. (e.g. for MPU)
	# Trusted function stacks have a size of 0x0, therefore align it to
	# the minimum boundary.
	$startAlign = $ot->{align} if !defined($startAlign);
	$startAlign = 8 if $startAlign == 0;

	GenldCommon::printOut(". = ALIGN($startAlign);");
	$self->printSymbolDefinition($startSymbol, '.') if defined $startSymbol;

	# input section mappings
	my @files = ( '*' );
	if($inFiles)
	{
		if ($preciseFiles)
		{
			# Use precise input file names
			@files = @$inFiles;
		}
		else
		{
			# GNU wants the full path name, which we do not support. We prepend a wildcard
			# to make the path of the module irrelevant
			# Also match backslashes which might appear in our paths on windows.
			@files = map {
				ref $_ eq 'HASH'
				? "$_->{lib}($_->{file}"
				: ( $_.'*', "*/$_", "*\\\\$_" )
			} @$inFiles;
		}
	}

	my $isects = $inSections || $ot->{isectDefault};
	my $isectSelector = join(" ", map { "$_ $_.*" } @$isects);

	foreach my $file (@files)
	{
		# If file contains an archive selector, indicated by opening (,
		# add a matching closing parenthesis
		my $post = ($file =~ /\(/) ? ')' : '';
		GenldCommon::printOut("\"$file\"($isectSelector)$post");
	}

	if(defined $endSymbol)
	{
		# Optionally align the end of the section to $end_align bytes
		# Could be from the architecture definitions or from a given parameter
		# or no alignment.
		$endAlign = $ot->{endalign} || 1 if !defined($endAlign);

		GenldCommon::printOut(". = ALIGN($endAlign);") if $endAlign > 1;

		$self->printSymbolDefinition($endSymbol, '.');
	}

	my $loadaddr = '';
	if(defined $initSymbol && !$disableRomInit) {
		$loadaddr = "AT>$self->{memDefs}{initdata_memory}";
	}

	#This is currently GNU only: Explicitly specify segments in the ELF header.
	#Print out for the first mapping of a new block. All following sections use this implicitly
	my $phdr = '';
	if(defined $self->{'phdr'} && $self->{'osecCount'} > 0) {
		$phdr = $self->{'phdr'};
	}
	GenldCommon::printOut("} >$self->{currentMemoryBlock} $phdr $loadaddr");


	if(defined $initSymbol)
	{
		my $align_minus_1 = $startAlign - 1;
		my $padding = sprintf "(((ADDR($osecName) + %d) & (~ %d)) - ADDR($osecName))", $align_minus_1, $align_minus_1;
		if ($disableRomInit) {
			$self->printSymbolDefinition($initSymbol, 0);
		} else {
			$self->printSymbolDefinition($initSymbol, sprintf("LOADADDR($osecName) + $padding"));
		}

		if(defined $initEndSymbol)
		{
			if ($disableRomInit) {
				$self->printSymbolDefinition($initEndSymbol, 0);
			} else {
				# SIZEOF(osecName) also contains the padding, so subtract the padding (like it was added to LOADADDR).
				$self->printSymbolDefinition($initEndSymbol, "$initSymbol + SIZEOF($osecName) - $padding");
			}
		}
	}
}

1;

# Editor settings: DO NOT DELETE
# vi:set ts=4 sw=4 noet tw=100:
