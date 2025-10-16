package GenldGhs;

=head1 The C<GenldGhs> package

This package implements the L<GenldBackend> interface for the Green Hills Multi linker.
This package's documentation only describes the specifics for this toolchain. The common
documentation can be found in L<GenldBackend>.

=head2 Toolchain-specific output section attributes

The following attributes are expected by the C<GenldGhs> back end in the output section type
specifications:

=over

=item C<_ghs_type>: Optional extra attributes for an output section definition

This optional attribute can be used to give extra attributes that are appended to the definition of
an output section. Currently, the C<CLEAR> attribute is used to instruct the linker to add an entry
to the runtime clear table, and the C<NOLOAD> attribute is used to indicate that the section
contents need not be loaded from flash.

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
	GenldCommon::printOut("// $_") foreach(@_);
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
	my ($currentMemoryBlock) = @_;

	$self->{currentMemoryBlock} = $currentMemoryBlock;
}

sub endMemoryBlockMappings
{
	my $self = shift;
	my ($block) = @_;

	$self->{currentMemoryBlock} = undef;
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

sub printOutputSection
{
	my $self = shift;
	my ($osecName, $osecType, $inFiles, $inSections, $startSymbol, $endSymbol, $initSymbol, $initEndSymbol) = @_;

	my $ot = $self->{osecTypes}{$osecType};
	my $disableRomInit = $GenldCommon::sysdesc{'-disableRomInit'};
	die "Unknown section type: $osecType" unless ref $ot eq 'HASH';

	$self->printComment("Output section $osecName (Type $osecType)");

	my $typestr = defined $ot->{_ghs_type} ? "($ot->{_ghs_type}) " : '';
	GenldCommon::printOut("$osecName $typestr ALIGN($ot->{align}) :");
	GenldCommon::printOut("{");
	$self->printSymbolDefinition($startSymbol, '.') if defined $startSymbol;

	my $files  = $inFiles || [ '*' ];
	my $isects = $inSections || $ot->{isectDefault};
	my @isectSelectors = map { $_, "$_.*" } @$isects;

	foreach my $file (@$files)
	{
		# Each selection statement must be enclosed in double
		# quotes if wildcards are used
		my ($pre, $post) = ('','');

		if (ref $file eq 'HASH')
		{
			$pre = "$file->{lib}($file->{file}";
			$post = ")";
		}
		else
		{
			$pre = $file;
		}
		foreach my $selector (@isectSelectors)
		{
			GenldCommon::printOut("\"$pre($selector)$post\"");
		}
	}

	if(defined $endSymbol)
	{
		# Optionally align the end of the section to $end_align bytes
		my $end_align = $ot->{endalign} || 1;
		GenldCommon::printOut(". = ALIGN($end_align);") if $end_align > 1;

		$self->printSymbolDefinition($endSymbol, '.');
	}

	GenldCommon::printOut("} > $self->{currentMemoryBlock}");

	# Init data section in ROM
	if(defined $initSymbol)
	{
		(my $osecName_no_periods = $osecName) =~ s/^\.//;

		# the section name in the ROM section must not contain periods
		# (according to GHS manual)
		if($osecName_no_periods =~ /\./)
		{
			die "Error: An output section with an initialization data ROM image must not contain periods other than the initial one.\n"
				. "Examples: .data_core1 (OK), .data.core1 (NOT OK), data_core1 (OK)\n"
				. "Erroneous section name: $osecName_no_periods\n";
		}

		if($disableRomInit)
		{
			$self->printSymbolDefinition($initSymbol, 0);
		}
		else
		{
			GenldCommon::printOut(".ROM.$osecName_no_periods ROM($osecName) : > $self->{memDefs}{initdata_memory}");
			$self->printSymbolDefinition($initSymbol, "addr(.ROM.$osecName_no_periods)");
		}
		if(defined $initEndSymbol)
		{
			if($disableRomInit)
			{
				$self->printSymbolDefinition($initEndSymbol, 0);
			}
			else
			{
				# The dot symbol ( . ) evaluates to the absolute address at the end of the last defined section.
				$self->printSymbolDefinition($initEndSymbol, ".");
			}
		}
	}
}

1;

# Editor settings: DO NOT DELETE
# vi:set ts=4 sw=4 noet tw=100:
