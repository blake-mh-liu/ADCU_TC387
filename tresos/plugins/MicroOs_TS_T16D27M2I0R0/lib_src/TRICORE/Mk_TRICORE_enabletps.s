/* Mk_TRICORE_enabletps.s
 *
 * This file contains the function MK_EnableTps(). It globally enables the
 * temporal protection system by setting the respective bit in the SYSCON register
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

	MK_file(Mk_TRICORE_enabletps.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_EnableTps

/* void MK_EnableTps(void)
 *
 * This function globally enables the temporal protection system by setting the respective bit in the
 * SYSCON register
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_EnableTps, 1
 * !doctype src
*/
MK_EnableTps:

/* Before enabling the TPS, clear all decrementers.
*/
	mov		d0, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_TPS_TIMER0), d0
	mtcr	MK_imm(#, MK_TPS_TIMER1), d0
	mtcr	MK_imm(#, MK_TPS_TIMER2), d0
	isync

	mtcr	MK_imm(#, MK_TPS_CON), d0
	isync

	mov		d2, MK_imm(#, MK_lo(MK_SYSCON_TPROTEN))
	addih	d2, d2, MK_imm(#, MK_hi(MK_SYSCON_TPROTEN))

	mfcr	d1, MK_imm(#, MK_SYSCON)
	or		d1, d2
	mtcr	MK_imm(#, MK_SYSCON), d1

	isync

	ret								/* Back to caller */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
