/* TRICORE-syscall.s
 *
 * This file contains the system call dispatcher for TRICORE
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
#include <TRICORE/Os_TRICORE_cpu.h>
#include <Os_syscalls.h>

	_GLOBAL	OS_SystemCall
	_EXTERN	OS_syscallTable		/* void *OS_syscallTable[] */
	_EXTERN OS_kernDisableLevel	/* os_uint16_t */
	_EXTERN OS_FreeCxList
	_EXTERN OS_Dispatch

	_TEXT

/*!
 *	OS_SystemCall
 *
 *	This routine dispatches a system call. It is jumped to directly by
 *	the system call exception vector stub, therefore must return by
 *	RFE or dispatch a new task.
 *	We are already in the interrupt stack with interrupts disabled.
 *	The upper context registers have already been saved by the system
 *	call mechanism. D15 contains the system call index which is needed
 *	by the dispatcher. Otherwise, the upper context registers can be
 *	freely used.
 *	Registers D4-D7 and A4-A7 potentially contain parameters for the
 *	system call, so we must preserve them as up to the point when the
 *	system call is dispatched. On return from the system call D2,D3,A2
 *	and A3 potentially contain the return value, so those registers
 *	must be preserved afterwards.
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.CPU.SupervisorMode, 1
*/

OS_SystemCall:

	/* Set the inKernel to 1. This leaves the old value in D14, which is used later.
	 * NOTE: the full address of inKernel is loaded because the ld.bu
	 * instruction has no version with 16-bit offset.
	 * Once inKernel has been incremented, interrupts can be re-enabled.
	 * This means that interrupts (at least, category 2 interrupts) must be
	 * disabled during critical parts of the system-call handlers.
	*/
	ld.bu		d14,[a8]OS_T_INKERNEL
	mov			d0,_IMM(#,1)
	st.b		[a8]OS_T_INKERNEL, d0

	/* If the interrupt bit was enabled before the syscall, then we restore it
	 *
	 * !LINKSTO Kernel.Misc.SystemCall.PreserveInterruptEnabledState, 1
	*/
	dsync
	mfcr		d12,_IMM(#,OS_PCXI)
	jz.t		_REGBIT(d12,OS_PCXI_PIE_BIT),_CalculateSysCallIndex
	enable

_CalculateSysCallIndex:
	/* If the system-call index is greater than the max, the first entry
	 * of the system-call table is used instead, so this must be the
	 * "invalid system call" entry.
	*/
	mov			d13,_IMM(#,OS_N_SYSCALL)
	movh.a		a14,_IMM(#,_hiword(OS_syscallTable))
	jge.u		d15,d13,_GetScEntry

	addsc.a		a14,a14,d15,_IMM(#,2)

_GetScEntry:
	ld.a		a14,[a14]_loword(OS_syscallTable)
	calli		a14

	/* On return from the system call, the return value is in D2/3 or A2/3
	 * depending on type. So we must preserve those registers.
	 * D14 still contains the old value.
	*/

	/* If inKernel was non-zero on entry, we're already nested somewhere
	 * inside the kernel, so no rescheduling is needed.
	 * Simply return using rfe. No need to restore inKernel - it stays 1.
	*/
	jne			d14,_IMM(#,0),_JustReturn

	/* From now on we're manipulating the kernel's idea of what is the
	 * current task, so we have to disable interrupts.
	 * We can load the upper-half of the addresses of taskQueueHead and
	 * taskCurrent first because they're constant.
	*/

	/* Disable interrupts. Raise CCPN of ICR register to OS_kernDisableLevel,
	 * provided it isn't already higher.
	*/
	mfcr		d0,_IMM(#,OS_ICR)
	movh.a		a12,_IMM(#,_hiword(OS_kernDisableLevel))
	lea			a12,[a12]_loword(OS_kernDisableLevel)
	ld.hu		d1,[a12]0

	sub			d4,d4,d4
	addi		d4,d4, _IMM(#,0x83f)
	sh			d4,d4, _IMM(#,4)
	addi		d4,d4, _IMM(#,0xf)
	and			d4,d0,d4
	jge.u		d4,d1,_AlreadyDisabled

	/* The following will set the CCPN and IE fields of the Interrupt Control
	 * Register (ICR) register.
	 * Note, d1 still contains the value of OS_kernDisableLevel and d0 the
	 * (eventually preprocessed) value of the ICR register.
	 * All this enables higher priority interrupts again, i.e. those which are
	 * higher than OS_kernDisableLevel.
	*/
	insert		d0,d0,d1,_IMM(#,0),_IMM(#,16)
	_mtcr		_IMM(#,OS_ICR),d0
	enable

_AlreadyDisabled:

	ld.a		a14,[a8]OS_T_TASKQHEAD
	ld.a		a13,[a8]OS_T_TASKCURRENT

	jz.a		a14,_WhichSwitch			/* No task to run => force schedule */
	jne.a		a13,a14,_WhichSwitch		/* Current != Q-head => schedule */

/* Here, the current task is at the head of the queue. But we have to
 * test for the possibility that the current task chained itself
 * or terminated and had another activation pending
 *
 * !LINKSTO Kernel.API.TaskManagement.ChainTask.SelfCall, 1
*/
	ld.a		a12,[a13]OS_T_DYNA		/* Get outgoing task's variables */
	ld.bu		d15,[a12]OS_T_STAT		/* Get outgoing task's state */
	jeq			d15,_IMM(#,OS_TS_RUNNING),_RestoreReturn	/* Return to same task */
	jeq			d15,_IMM(#,OS_TS_NEW),_FreeAndSwitch		/* Task chained itself */
	j			_SaveAndSwitch			/* Most likely READY_SYNC (WaitEvent and SetEvent have occurred) */

_WhichSwitch:
	jz.a		a13,_FreeAndSwitch		/* No outgoing task */
	ld.a		a12,[a13]OS_T_DYNA		/* Get outgoing task's variables */
	ld.bu		d15,[a12]OS_T_STAT		/* Get outgoing task's state */
	jlt.u		d15,_IMM(#,(OS_TS_MAX_TERMINATING+1)),_FreeAndSwitch		/* Jump if the task is terminating */

/* This is the context switch. The upper context is already saved. THe
 * lower context is now saved too. The task context actually only consists
 * of the value of the PCXI register.
 *
 * !LINKSTO Kernel.Feature.FloatingPointContext, 1
 * Tricore's FPU, when present, uses the same registers as the integer
 * ALU, so no special FPU context save/restore is necessary.
*/
_SaveAndSwitch:
	svlcx								/* Stuff lower context on PCX list */
										/* This saves the return value! */
	dsync								/* Wait for operation to finish */
	mfcr		d15,_IMM(#,OS_PCXI)		/* Get content of PCXI */
	st.w		[a12]OS_T_CTXT,d15		/* Save in task's context "pointer" */

	mov			d4,_IMM(#,0)			/* Set PCXI to 0 */
	_mtcr		_IMM(#,OS_PCXI),d4
	mov			d4,_IMM(#,OS_TS_READY_SYNC)		/* Synchronous dispatcher call */
	j			OS_Dispatch				/* Never returns */

_FreeAndSwitch:
	mfcr		d4,_IMM(#,OS_PCXI)		/* Get content of PCXI */
	call		OS_FreeCxList			/* Free up the list. */

	mov			d4,_IMM(#,0)			/* Set PCXI to 0 */
	_mtcr		_IMM(#,OS_PCXI),d4
	mov			d4,_IMM(#,OS_TS_READY_SYNC)		/* Synchronous dispatcher call */
	j			OS_Dispatch				/* Never returns */

_RestoreReturn:
	st.b		[a8]OS_T_INKERNEL,d14	/* Restore old OS_inKernel */
	ld.hu		d15,[a12]OS_T_PRIO		/* Get current task's priority */
	ld.bu		d4,[a13]OS_T_RPRIO		/* Get outgoing task's runPrio (in d4, as 2nd parameter for OS_InsertTask) */
	jge			d15, d4, _JustReturn	/* Jump if current prio >= queuePrio */
	st.h		[a12]OS_T_PRIO, d4		/* Set new prio */

_JustReturn:
	rfe

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
