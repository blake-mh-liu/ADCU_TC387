#!/usr/bin/perl -w

for ( $i = 1; $i < 256; $i++ )
{
	printf("	MK_align(32, 5)\n");
	printf("MK_InterruptVector_%02x:		/* Vector 0x%02x (%d) */\n", $i, $i, $i);
	printf("	svlcx\n");
	printf("	mov		d5, MK_imm(#, %d)\n", $i-1);
	printf("	mov		d15, MK_imm(#, 0)\n");
	printf("	dsync\n");
	printf("	mfcr	d4, MK_imm(#, MK_PCXI)\n");
	printf("	mtcr	MK_imm(#, MK_PCXI), d15\n");
	printf("	j		MK_TricoreDispatchInterruptSoft\n");
	printf("\n");
}
