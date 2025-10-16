/* Mk_TRICORE_resumethread.s
 *
 * This file contains the MK_TricoreResumeThread function
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <private/Mk_asm.h>		/* Must be first! */
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_thread.h>

	MK_file(Mk_TRICORE_resumethread.s)

	MK_global	MK_TricoreResumeThread

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/*
 * MK_TricoreResumeThread(mk_uint32_t pcxi)
 *
 * Resumes a thread by loading its saved registers.
 *
 * Parameter pcxi (in d4) - saved PCXI value.
 *
 * Preconditions:
 *	Interrupts disabled.
 *
 * First we clean up the CSA list used by the kernel.
 * We start at the CSA referred to by PCXI.PCX. In case it does not refer to any CSA, we
 * are done and immediatly skip to MK_ResumeThreadDone.
 *
 * If PCXI.PCX, we enter a loop that follows the list until the last CSA in the list is
 * found. When the last CSA has been found, the kernel's CSA list is returned by making
 * the last CSA in the list point to the previous first element of the free list (FCX),
 * and making FCX point to the first CSA in the kernel's CSA list.
 *
 * Using optimizing compilers the loop is rarely executed more than two times. In kernel
 * invocations without errors, the loop is sometimes never entered at all.
 *
 * At MK_ResumeThreadDone, we restore the context of the thread that is resumed.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_TricoreResumeThread, 1
 * !doctype src
*/
MK_TricoreResumeThread:
	movh    d15, MK_imm(#, 0xf)			/* d15: mask to extract the segment from PCXI value */
	mfcr    d14, MK_imm(#, MK_PCXI)		/* d14: head of list */

	/* check if there are any CSAs at all */
	and		d2, d14, d15				/* Segment part in bits 19:16 */
	jeq		d2, MK_imm(#, 0), MK_ResumeThreadDone	/* Segment 0 => no CSAs */

	mov		d13, d14					/* d13: current CSA pointer in the loop */
	dsync								/* we are about to access active CSA memory, sync first */

MK_ResumeThreadNext:
	sh      d2, d2, MK_imm(#, 12)		/* shift segment from 19:16 to bits 31:28 */
	insert	d2, d2, d13, MK_imm(#, 6), MK_imm(#, 16)	/* offset part from bits 15:0 to 21:6 */
	mov.a   a2, d2						/* load link word from referred CSA to d13 */
	ld.w    d13, [a2]

	/* compute address of CSA referred by d13 in d2 */
	and		d2, d13, d15				/* Segment part in bits 19:16 */
	jne		d2, MK_imm(#, 0), MK_ResumeThreadNext	/* Segment != 0 => more CSAs in list */

	/* d14: first CSA, a2: link word in last CSA */
	mfcr	d15, MK_imm(#, MK_FCX)
	st.w	[a2], d15
	insert  d14, d14, MK_imm(#, 0), MK_imm(#, 20), MK_imm(#, 12)	/* clear non-PCX bits */
	mtcr	MK_imm(#, MK_FCX), d14

	/* disable call-depth counter so rfe works */
	mfcr    d13, MK_imm(#, MK_PSW)
	andn	d13, d13, MK_imm(#, MK_PSW_CDE)
	mtcr    MK_imm(#, MK_PSW), d13

MK_ResumeThreadDone:
	mtcr	MK_imm(#, MK_PCXI), d4		/* Put thread's pcxi back in register */
	isync								/* Force instruction to complete */
	rslcx								/* Restore lower context registers including A11 (RA) */
	rfe									/* Restore upper context registers including PC and PSW */

/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/
