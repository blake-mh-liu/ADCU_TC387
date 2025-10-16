/* TRICORE-idle.s
 *
 * This file contains the OS_TRICORE_Idle function.
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

#ifndef OS_Halt
#define OS_Halt()
#endif

/*!
 * OS_TricoreIdle()
 *
 * This function provides the body of the idle loop for the TRICORE processor.
 *
 * The idle loop is implemented using a function to provide an optimisation
 * barrier for the compiler. This prevents the compiler making assumptions
 * about the use of global variables during the idle loop. See kern-dispatch.c
 * for details. It also permits using different idle modes (with vs. without a
 * halt instruction).
 *
 * On entry: the inKernel flag has been cleared, so that an ISR will dispatch a task if
 * necessary. It is therefore safe to put a halt intruction into the idle loop.
 * The function should not return, but if it does so the dispatcher simply calls it
 * again.
 *
 * The function has been recoded in assembly language so that the stack can be safely
 * discarded before enabling interrupts without having to make assumptions about the
 * code that the compiler has generated. The old C code is retained as documentation at the end.
*/
	_TEXT
	_GLOBAL	OS_TricoreIdle
	_GTYPE(OS_TricoreIdle,@function)
	_GLOBAL	__callee.OS_TricoreIdle.da.v.v
	_GTYPE(__callee.OS_TricoreIdle.da.v.v,@function)

_TTYPE(OS_TricoreIdle,FUNC)
_TTYPE(__callee.OS_TricoreIdle.da.v.v,FUNC)
	disable								/* Disable interrupts, to be safe */

	mfcr	d0, _IMM(#,OS_PSW)			/* Clear the IS bit of PSW */
	mov.u	d1, _IMM(#,OS_PSW_IS)
	andn	d0, d0, d1
	_mtcr	_IMM(#,OS_PSW), d0			/* Now logically on task stack (though we're not using any stack) */

	mfcr	d0, _IMM(#,OS_ICR)			/* Clear the CCPN field of the ICR */
	mov.u	d1, _IMM(#,OS_ICR_CCPN)
	mov.u	d2, _IMM(#,OS_ICR_IE)
	andn	d0, d0, d1
	or		d0, d0, d2
	_mtcr	_IMM(#,OS_ICR), d0			/* Interrupts level now zero */

	enable								/* Enable interrupts */
	ld.bu	d0,[a8]OS_T_IDLEMODE		/* Get idle mode */
	jeq		d0,_IMM(#,OS_IDLE_WAIT),OS_TricoreIdleHalt	/* Halt is requested */


OS_TricoreIdleLoop:
	j		OS_TricoreIdleLoop

OS_TricoreIdleHalt:
	wait								/* Wait for events */
	j		OS_TricoreIdleHalt

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
