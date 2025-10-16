/* TRICORE-cat2interrupt.s
 *
 * This file contains the category 2 interrupt exit routine
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ASM
#define OS_ASM
#endif

#include <Os_asm_common.h>
#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_kernel.h>
#include <Os_tool.h>
#include <TRICORE/Os_TRICORE_core.h>

	_GLOBAL		OS_Cat2Exit
    _GLOBAL     OS_CatKExit
	_GLOBAL		OS_CatCCExit
	_EXTERN		OS_FreeCxList
	_EXTERN		OS_Dispatch

/* OS_Cat2Exit/OS_CatKExit/OS_CatCCExit
 *
 * This routine is the interrupt exit routine for Category 2 interrupts. It
 * is jumped to by the interrupt vector stub and exits via RSLCX/RFE or by
 * jumping to OS_Dispatch().
 * The old value of inKernel (in D2, returned from the ISR wrapper) is used
 * to determine whether a task switch is necessary.
 * The code here is very similar to that at the end of the system-call
 * dispatcher, except that the lower context has already been saved.
 * NOTE: unlike ProOSEK, the interrupt entry routine must consider that
 * the current task might be NULL, because a task could have been killed
 * for various reasons at interrupt level.
 *
 * On entry:
 *    previous value of OS_inKernel in D2 (returned by Cat2Entry)
 *    OS_inKernel set to 1
 *
 * !LINKSTO Kernel.InterruptProcessing.InterruptScheduling, 1
*/
	_TEXT

OS_Cat2Exit:
OS_CatKExit:
OS_CatCCExit:

	/* If inKernel was non-zero on entry, we're already nested somewhere
	 * inside the kernel, so no rescheduling is needed. Simply return
	 * using rfe. No need to restore the old inKernel value because
	 * it's already non-zero.
	*/
	jne			d2,_IMM(#,0),_JustReturn

	/* From now on we're manipulating the kernel's idea of what is the
	 * current task, so interrupts must remain disabled.
	 *
	 * a14 = OS_taskQueueHead
	 * a13 = OS_taskCurrent
	*/
    ld.a        a14,[a8]OS_T_TASKQHEAD
    ld.a        a13,[a8]OS_T_TASKCURRENT

	jz.a		a14,_WhichSwitch		/* No task to run - force schedule */
	jne.a		a13,a14,_WhichSwitch	/* Current != Q-head - force schedule */

/* Here the current task is at the head of the ready queue, but we have to test
 * for the possibility that the task is restarting (e.g. by TerminateApplication(RESTART)
 * at interrupt level
 *
 * Unlike the system call handler there's no need to consider READY_SYNC here!
*/
	ld.a		a12,[a13]OS_T_DYNA		/* Get outgoing task's variables */
	ld.bu		d15,[a12]OS_T_STAT		/* Get outgoing task's state */
	jeq			d15,_IMM(#,OS_TS_NEW),_FreeAndSwitch		/* Task is restarting */
	j			_RestoreReturn			/* Most likely RUNNING */

_WhichSwitch:
	jz.a		a13,_FreeAndSwitch		/* No outgoing task */
	ld.a		a15,[a13]OS_T_DYNA		/* Get task's dynamic state */
	ld.bu		d15,[a15]OS_T_STAT		/* Get task's state */
	jlt.u		d15,_IMM(#,(OS_TS_MAX_TERMINATING+1)),_FreeAndSwitch		/* Jump if the task is terminating */

_SaveAndSwitch:
	dsync								/* Wait for operation to finish */
	mfcr		d15,_IMM(#,OS_PCXI)		/* Get content of PCXI */
	st.w		[a15]OS_T_CTXT,d15		/* Save in task's context "pointer" */

	mov			d4,_IMM(#,0)			/* Set PCXI to 0 */
	_mtcr		_IMM(#,OS_PCXI),d4
	mov			d4,_IMM(#,OS_TS_READY_ASYNC)	/* Asynchronous dispatcher call */
	j			OS_Dispatch				/* Never returns */

_FreeAndSwitch:
	mfcr		d4,_IMM(#,OS_PCXI)		/* Get content of PCXI */
	call		OS_FreeCxList			/* Free up the list. */

	mov			d4,_IMM(#,0)			/* Set PCXI to 0 */
	_mtcr		_IMM(#,OS_PCXI),d4
	mov			d4,_IMM(#,OS_TS_READY_ASYNC)	/* Asynchronous dispatcher call */
	j			OS_Dispatch				/* Never returns */

_RestoreReturn:							/* Restore old inKernel and return */
    st.b        [a8]OS_T_INKERNEL,d2

_JustReturn:							/* Just return */
	rslcx
	rfe

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
