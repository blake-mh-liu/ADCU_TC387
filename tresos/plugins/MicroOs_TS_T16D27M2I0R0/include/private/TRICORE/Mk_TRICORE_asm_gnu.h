/* Mk_TRICORE_asm_gnu.h
 *
 * This file is the toolchain-dependent include file for the gnu assembler (gas) for Tricore.
 *
 * This file defines the macros used in assembler files in a way such that the assembler files
 * will compile with the gnu assembler.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_CHARSET_010]
 *  Only the following subset of characters from the ASCII character set are permitted in source code files:
 *  [table of characters]
 *  The characters $ (0x24), @ (0x40) and  (0x60) are only permitted inside comments.
 *
 * Reason:
 *  The @ character (0x40) is part of the assembly-language syntax.
*/
/* Deviation DCG-1 <*> */

#ifndef MK_TRICORE_ASM_GNU_H
#define MK_TRICORE_ASM_GNU_H

#ifndef MK_ASM
#error "MK_ASM is not defined. This file is not intended to be used in C files."
#endif

/* Filename directive
*/
#define MK_file(name)		.file	#name

/* Global and external symbol directives
 *
 * Note: gas has no ".extern", therefore we evaluate to "#" which starts a comment
*/
#define MK_global		.globl
#define MK_extern		#
#define MK_align(b,p2)	.balign	b

/* High and low halfwords of 32-bit values
*/
#define MK_hi(x)		hi:x
#define MK_lo(x)		lo:x

/* Prefix for immediate operands
*/
#define MK_imm(a,b)		b

/* Directive to define a 32-bit word
*/
#define MK_WORD			.word

/* Directive to define a 16-bit half-word
*/
#define MK_HWORD		.hword

/* Text section
 *
 * This could be already defined by the users memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_TEXT				.section ".text","ax",@progbits
#define MK_ASM_SDECL_TEXT

/* Boot header section
 *
 * The section containing the boot mode header
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_BOOTWORD			.section "MK_bootword","ax",@progbits
#define MK_ASM_SDECL_BOOTWORD

/* Reset section
 *
 * The section containing the reset vector
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_RESET			.section "MK_reset","ax",@progbits
#define MK_ASM_SDECL_RESET

/* Exception vector table section
 *
 * The section containing the exception vector table
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_EXCEPTIONTABLE	.section "MK_exctable","ax",@progbits
#define MK_ASM_SDECL_EXCEPTIONTABLE

/* The Gnu assembler expects the register names to be prefixed with %
 * so we define macros to add the % sign.
*/
#define a0		%a0
#define a1		%a1
#define a2		%a2
#define a3		%a3
#define a4		%a4
#define a5		%a5
#define a6		%a6
#define a7		%a7
#define a8		%a8
#define a9		%a9
#define a10		%a10
#define a11		%a11
#define a12		%a12
#define a13		%a13
#define a14		%a14
#define a15		%a15
#define d0		%d0
#define d1		%d1
#define d2		%d2
#define d3		%d3
#define d4		%d4
#define d5		%d5
#define d6		%d6
#define d7		%d7
#define d8		%d8
#define d9		%d9
#define d10		%d10
#define d11		%d11
#define d12		%d12
#define d13		%d13
#define d14		%d14
#define d15		%d15
#define e0		%e0
#define e2		%e2
#define e4		%e4
#define e6		%e6
#define e8		%e8
#define e10		%e10
#define e12		%e12
#define e14		%e14
#define sp		%sp


#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
