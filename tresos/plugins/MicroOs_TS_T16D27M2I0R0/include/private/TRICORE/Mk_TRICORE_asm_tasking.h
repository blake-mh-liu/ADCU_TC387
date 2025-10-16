/* Mk_TRICORE_asm_tasking.h
 *
 * This file is the toolchain-dependent include file for the tasking assembler for Tricore.
 *
 * This file defines the macros used in assembler files in a way such that the assembler files
 * will compile with the tasking assembler.
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

#ifndef MK_TRICORE_ASM_TASKING_H
#define MK_TRICORE_ASM_TASKING_H

#ifndef MK_ASM
#error "MK_ASM is not defined. This file is not intended to be used in C files."
#endif

/* Filename for the assembler
*/
#define MK_file(name)

/* Various assembler directives
*/
#define MK_global			.global
#define MK_extern			.extern
#define MK_align(b,p2)		.align	b

/* High and low halfwords of 32-bit values
*/
#define MK_hi(x)			@his(x)
#define MK_lo(x)			@los(x)

/* Prefix for immediate operands
*/
#define MK_imm(a,b)		a b

/* directive to define a 32-bit word
*/
#define MK_WORD			.word

/* directive to define a 16-bit half-word
*/
#define MK_HWORD		.half

/* Text section
 *
 * This could be already defined by the users memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_TEXT				.sect	".text"
#define MK_ASM_SDECL_TEXT				.sdecl	".text",code

/* Boot header section
 *
 * The section containing the boot mode header
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_BOOTWORD			.sect	"MK_bootword"
#define MK_ASM_SDECL_BOOTWORD			.sdecl	"MK_bootword",code

/* Reset section
 *
 * The section containing the reset vector
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_RESET			.sect	"MK_reset"
#define MK_ASM_SDECL_RESET				.sdecl	"MK_reset",code

/* Exception vector table section
 *
 * The section containing the exception vector table
 * This could be already defined by the user's memmap, so we only define it if it isn't already defined.
*/
#define MK_ASM_SECTION_EXCEPTIONTABLE	.sect	"MK_exctable"
#define MK_ASM_SDECL_EXCEPTIONTABLE		.sdecl	"MK_exctable",code

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
