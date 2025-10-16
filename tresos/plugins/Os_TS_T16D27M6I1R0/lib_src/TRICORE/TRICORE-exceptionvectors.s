/* TRICORE-exceptionvectors.s
 *
 * This file contains the exception vectors for TRICORE
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

/*!
 * Exception vectors
 *
 * Tricore has 8 exception vectors. They can be located anywhere in memory,
 * as long as they are aligned on a 64-word (256-byte) boundary.
 *
 * The first 6 exceptions, numbered 0 to 5, are fairly standard processor
 * exceptions. In each case, the register D15 contains the traps
 * identification number, which gives more detail about the
 * trap that occurred.
 *
 * The 7th exception is the syscall exception. This exception is used
 * to provide the interface between user-side code and kernel code.
 * The register D15 contains the system-call number specified in the
 * instruction, which ranges from 0 to 255.
 *
 * The final exception is NMI. NMI is normally triggered as a result
 * of an external non-maskable interrupt. On some Tricore boards, NMI
 * is used instead of a normal maskable interrupt. It is a simple matter
 * to redirect the interrupt to a maskable interrupt by writing an NMI
 * handler that triggers a software-triggered interrupt (through CPUSRC1
 * for example), and then by handling the interrupt on CPUSRC1 in the
 * normal way. Note that the NMI trap can also be caused by other events,
 * such as the  watchdog timer or a PLL problem. The NMISR register can
 * be examined to determine the cause.
 * WARNING: some Tricore derivatives do not always set the NMIEXT bit in
 * this register, so if no source is indicated, an external NMI should be
 * assumed.
*/
	_GLOBAL	OS_trapTable
	_GLOBAL	OS_Trap0
	_GLOBAL	OS_Trap1
	_GLOBAL	OS_Trap2
	_GLOBAL	OS_Trap3
	_GLOBAL	OS_Trap4
	_GLOBAL	OS_Trap5
	_GLOBAL	OS_Trap6
	_GLOBAL	OS_Trap7

	_GLOBAL	OS_TrapEntry
	_GLOBAL	OS_TrapExit

/*	External functions
*/
	_EXTERN	OS_Trap0Handler
	_EXTERN	OS_Trap1Handler
	_EXTERN	OS_Trap2Handler
	_EXTERN	OS_Trap3Handler
	_EXTERN	OS_Trap4Handler
	_EXTERN	OS_Trap5Handler
	_EXTERN	OS_Trap7Handler

	_EXTERN	OS_SystemCall
	_EXTERN	OS_FreeCxList
	_EXTERN	OS_Dispatch

	_EXTERN OS_kernDisableLevel

/*	Exception vectors
*/
# if (OS_TOOL==OS_tasking)
		.sdecl	"OS_ExceptionVectors",code
		.sect	"OS_ExceptionVectors"
# else
		.section	"OS_ExceptionVectors","a"
# endif

/*==============================================================================
 *	Reset/MMU exception
 *==============================================================================
*/
	_align(256,8)

OS_trapTable:
OS_Trap0:
	svlcx
	jl		OS_TrapEntry
	call	OS_Trap0Handler
	j		OS_TrapExit

/*==============================================================================
 *	Internal protection traps
 *==============================================================================
*/
	_align(32,5)

OS_Trap1:
	svlcx
	jl		OS_TrapEntry
	call	OS_Trap1Handler
	j		OS_TrapExit

/*==============================================================================
 *	Instruction errors
 *==============================================================================
*/
	_align(32,5)

OS_Trap2:
	svlcx
	jl		OS_TrapEntry
	call	OS_Trap2Handler
	j		OS_TrapExit

/*==============================================================================
 *	Context management errors
 *==============================================================================
*/
	_align(32,5)

OS_Trap3:
	svlcx
	jl		OS_TrapEntry
	call	OS_Trap3Handler
	j		OS_TrapExit

/*==============================================================================
 *	System bus and peripheral errors
 *==============================================================================
*/
	_align(32,5)

OS_Trap4:
	svlcx
	jl		OS_TrapEntry
	call	OS_Trap4Handler
	j		OS_TrapExit

/*==============================================================================
 *	Assertion traps
 *==============================================================================
*/
	_align(32,5)

OS_Trap5:
	svlcx
	jl		OS_TrapEntry
	call	OS_Trap5Handler
	j		OS_TrapExit

/*==============================================================================
 *	System call exception
 *  System calls are not true exceptions. We do not need to preserve the
 *	lower-context registers because the calling function expects them to be
 *  destroyed.
 *	The calling function has placed its parameters in the registers
 *	d4-d7 and a4-a7, so we must not use those registers. Furthermore,
 *	the system call handler will leave its return value in either
 *	d2, d2/d3 or a2, so those registers must be preserved after
 *	returning from the system call.
 *	The OS_SystemCall function is specially written to either dispatch
 *	another task or to return using rfe, so we simply jump there.
 *==============================================================================
*/
	_align(32,5)

OS_Trap6:
	j		OS_SystemCall

/*==============================================================================
 *	NMI, watchdog and PLL traps
 *==============================================================================
*/
	_align(32,5)

OS_Trap7:
	svlcx
	call	OS_Trap7Handler
	rslcx
	rfe


/*!
 * OS_TrapEntry
 *
 * This routine is the trap entry routine. It gets "called" using a JL
 * instruction, and so returns using "JI A11". This is so that it can store
 * the previous value of inKernel in D14.
 * inKernel is set to 1 here.
 * Interrupts remain completely disabled.
 *
 * On entry:
 *    upper and lower context saved
 *    interrupts disabled
 *    trap identification number in D15
 *
 * On exit:
 *    previous value of OS_inKernel in D14
 *    trap identification number in D15
 *    OS_inKernel set to 1
*/
	_TEXT

OS_TrapEntry:
	ld.bu		d14,[a8]OS_T_INKERNEL
	mov			d12,_IMM(#,1)
	st.b		[a8]OS_T_INKERNEL,d12

	ji			a11

/* OS_TrapExit
 *
 * This routine is the trap exit routine. It is
 * jumped to by the trap vector stub and exits via RSLCX/RFE or by
 * jumping to OS_Dispatch().
 * Information saved by OS_TrapEntry is still valid.
 * The inFunction flag is restored immediately. This only serves to indicate
 * to system services that an trap handler is running. The inKernel flag is
 * used to determine whether a task switch is necessary.
 * The code here is very similar to that at the end of the system-call
 * dispatcher, except that the lower context has already been saved.
 *
 * On entry:
 *    previous value of OS_inKernel in D14
 *    OS_inKernel set to 1
*/
	_TEXT

OS_TrapExit:
	/* Now we can re-enable interrupts at the level that was enabled
	 * before the trap occurred. The exception has been handled
	 * and any necessary action has been taken. If the exception was
	 * fatal, we never get here anyway.
	*/
	enable

	/* If inKernel was non-zero on entry, we're already nested somewhere
	 * inside the kernel, so no rescheduling is needed. Simply restore
	 * the old inKernel value and return using rfe.
	*/
	jne			d14,_IMM(#,0),_JustReturn

	/* From now on we're manipulating the kernel's idea of what is the
	 * current task, so we have to disable interrupts.
	 * We can load the upper-half of the addresses of taskQueueHead and
	 * taskCurrent first because they're constant.
	*/

	mfcr		d0,_IMM(#,OS_ICR)
	movh.a		a12,_IMM(#,_hiword(OS_kernDisableLevel))
	lea			a12,[a12]_loword(OS_kernDisableLevel)
	ld.hu		d1,[a12]0

	/* The following will set the OS_kernDisableLevel, and enable afterwards allow higher prior interrupts */
	insert	d0,d0,d1,_IMM(#,0),_IMM(#,16)
	_mtcr		_IMM(#,OS_ICR),d0
	enable

	ld.a		a14,[a8]OS_T_TASKQHEAD
	ld.a		a13,[a8]OS_T_TASKCURRENT

	jz.a		a14,_WhichSwitch		/* No task to run - force schedule */
	jne.a		a13,a14,_WhichSwitch	/* Current != Q-head - force schedule */

/* Here the current task is at the head of the ready queue, but we have to test
 * for the possibility that the task is restarting (e.g. by application termination.
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
	mov			d4,_IMM(#,OS_TS_READY_ASYNC)	/* Asyncronous dispatcher call */
	j			OS_Dispatch				/* Never returns */

_FreeAndSwitch:
	mfcr		d4,_IMM(#,OS_PCXI)		/* Get content of PCXI */
	call		OS_FreeCxList			/* Free up the list. */

	mov			d4,_IMM(#,0)			/* Set PCXI to 0 */
	_mtcr		_IMM(#,OS_PCXI),d4
	mov			d4,_IMM(#,OS_TS_READY_ASYNC)	/* Asyncronous dispatcher call */
	j			OS_Dispatch				/* Never returns */

_RestoreReturn:							/* Restore old inKernel and return */
	st.b        [a15]0,d14

_JustReturn:							/* Just return */
	rslcx
	rfe


#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
