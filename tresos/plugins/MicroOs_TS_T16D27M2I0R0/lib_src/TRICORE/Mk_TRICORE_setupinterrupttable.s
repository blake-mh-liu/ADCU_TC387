/* Mk_TRICORE_setupinterrupttable.s
 *
 * This file contains the function MK_SetupInterruptTable(). It sets the BIV register of the processor core.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_setupinterupttable.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_SetupInterruptTable

/* void MK_SetupInterruptTable(mk_uint32_t btaddr);
 *
 * This function writes its parameter (supposed to be the correct base address of the interupt
 * table) to the BIV register.
*/
MK_SetupInterruptTable:

	disable							/* Ensure interrupt table will not be used during startup */
	mtcr    MK_imm(#, MK_BIV), d4
	isync

	ret								/* Back to caller */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
