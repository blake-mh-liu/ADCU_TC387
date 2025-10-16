/* Mk_TRICORE_hwenablememoryprotection.s
 *
 * This file contains the function MK_HwEnableMemoryProtection(). It globally enables the
 * memory protection system by setting the respective bit in the SYSCON register
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_hwsetupexceptions.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_HwEnableMemoryProtection

/* void MK_HwEnableMemoryProtection(void)
 *
 * This function globally enables the memory protection system by setting the respective bit in the
 * SYSCON register
 *
*/
MK_HwEnableMemoryProtection:

	mov		d2, MK_imm(#, MK_lo(MK_SYSCON_PROTEN))
	addih	d2, d2, MK_imm(#, MK_hi(MK_SYSCON_PROTEN))

	mfcr	d1, MK_imm(#, MK_SYSCON)
	or		d1, d2
	mtcr	MK_imm(#, MK_SYSCON), d1

	isync

	ret								/* Back to caller */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
