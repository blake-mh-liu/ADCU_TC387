/* TRICORE-syscallstartup.s
 *
 * This file contains the special startup version of the system call
 * dispatcher for TRICORE
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
#include <Os_syscalls.h>

	_GLOBAL	OS_SystemCallStartup
	_EXTERN	OS_SystemCall
	_EXTERN	OS_syscallTable		/* void *OS_syscallTable[] */

	_TEXT

/*!
 *	OS_SystemCallStartup
 *
 *	This routine dispatches a system call during startup (i.e. before
 *	StartOS has been called. It is jumped to directly by
 *	the system call exception vector stub, therefore must return by
 *	RFE. If the system call is StartOS(), the normal system call
 *	handler is jumped to. The remaining code is otherwise identical
 *  to the normal system call handler (except that interrupts are not
 *	enabled) until the call to the internal kernel function that performs
 *	the required service. On return from the kernel function the startup
 *	handler simply restores the inKernel flag and returns to the caller.
 *
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
*/

OS_SystemCallStartup:
	/* If the system call is StartOS we go to the normal handler.
	 * StartOS will switch the vector table over to the normal running
	 * vector table, so we'll never get here again.
	*/
	jne			d15,_IMM(#,OS_SC_StartOs),OS_SystemCallStartup_a
	j			OS_SystemCall

OS_SystemCallStartup_a:
	/* Set the inKernel to 1. This leaves the old value in D14, which is used later.
	 * Once inKernel has been set, interrupts can be re-enabled.
	 * This means that interrupts (at least, category 2 interrupts) must be
	 * disabled during critical parts of the system-call handlers.
	*/
	ld.bu		d14,[a8]OS_T_INKERNEL
	mov			d0,_IMM(#,1)
	st.b		[a8]OS_T_INKERNEL, d0

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
	 * depending on type. They are returned to the caller.
	 * D14 still contains the old value, and is restored here before
	 * returning.
	*/

	st.b        [a8]OS_T_INKERNEL,d14
	rfe

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
