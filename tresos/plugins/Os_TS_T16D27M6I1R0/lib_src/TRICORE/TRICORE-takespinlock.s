/* TRICORE-takespinlock.s
 *
 * This file contains the OS_TricoreTakeSpinlock() fucntion
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
#include <TRICORE/Os_TRICORE_core.h>

	_TEXT
	_GLOBAL	OS_TricoreTakeSpinlock
	_GTYPE(OS_TricoreTakeSpinlock,@function)
	_GLOBAL	__callee.OS_TricoreTakeSpinlock.da.v.p
	_GTYPE(__callee.OS_TricoreTakeSpinlock.da.v.p,@function)


/* OS_TricoreTakeSpinlock
 *
 * C Prototype: void OS_TricoreTakeSpinlock(os_int_t *spinlockAddr);
 *
 * Aquires a spinlock located at spinlockAddr (register a4), by writing one
 * to the address when it currently is zero. If it is not zero, it waits for
 * it to become zero (a.k.a. "spinning")
 */
	_align(4,2)

_TTYPE(OS_TricoreTakeSpinlock,FUNC)
_TTYPE(__callee.OS_TricoreTakeSpinlock.da.v.p,FUNC)

_retry:
	ld.w		d4, [a4]
	jne			d4, _IMM(#,0), _retry
	mov			d4,_IMM(#,1)
	swap.w		[a4]0, d4
	jne         d4, _IMM(#,0), _retry
	ret

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
