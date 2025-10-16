package GenldArchARC;

=head1 The C<GenldArchARC> package

This package collects objects and functions that are needed for the ARC architecture. This
package's documentation only describes the specifics for this architecture. The common documentation
can be found in L<GenldArch>.

=cut

our %memoryBlocks = (
	'initdata_memory' => 'ROM',
);

our %osecTypes =
(
	'VECTAB'   =>
	{
		align           => 1024,
		endalign        => undef,
		isectDefault    => [qw(.reset)],
	},
	'TEXT'    =>
	{
		align        => 8,
		endalign     => 8192,
		isectDefault => [qw(.text)],
	},
	'RODATA'  =>
	{
		align        => 8,
		endalign     => 8192,
		isectDefault => [qw(.rodata .zrodata .ldata)],
	},
	'DATA'    =>
	{
		align        => 8192,
		endalign     => 8,
		isectDefault => [qw(.data .zdata .sdata)],
	},
	'BSS'            =>
	{
		align        => 8,
		endalign     => 8192,
		isectDefault => [qw(.bss .zbss .sbss)],

		_gnu_extraattr    => 'NOLOAD',
	},
	'STACK'   =>
	{
		align        => 8192,
		endalign     => 8192,
		isectDefault => [qw(.bss .zbss .sbss)],

		_gnu_extraattr    => 'NOLOAD',
	},
	'HEAP'   =>
	{
		align        => 8192,
		endalign     => 8192,
		isectDefault => [],
	},
);

# This function is invoked by GenldCommon::parseArgs() if unknown arguments are encountered
sub parseArgs
{
	my ($arg, $sysdesc, $argv_position) = @_;

	if ($arg eq '-mpuMinRegionSize')
	{
		GenldCommon::setArg($sysdesc, $arg, ++$$argv_position);
		GenldCommon::checkIntArg($sysdesc, $arg);
	}
	elsif ($arg eq '-sizeAlignRegions')
	{
		GenldCommon::setArg($sysdesc, $arg, $$argv_position);
	}
	else
	{
		return 0;
	}

	return 1;
}

sub usage
{
	print STDERR <<EOUSAGE;
Additional options specific to ARC:

  -mpuMinRegionSize <REGION_SIZE>:
  Sets the smallest possible region size of the ARC MPU. This is used to
  determine the minimum alignment of a memory region that may be programmed
  into the MPU.

  -sizeAlignRegions
  Align memory regions according to their size

EOUSAGE

}
1;

# Editor settings: DO NOT DELETE
# vi:set ts=4 sw=4 noet tw=100:
