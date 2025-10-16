/* TRICORE-initsp.s
 *
 * This file contains the OS_InitSp() function
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
	_GLOBAL	OS_InitSp
	_GTYPE(OS_InitSp,@function)
	_GLOBAL	__callee.OS_InitSp.da.v.v
	_GTYPE(__callee.OS_InitSp.da.v.v,@function)
	_EXTERN OS_INITIAL_SP


/* OS_InitSp() - initialise the stack pointer. DO NOT CALL FROM C!
 *
 * C Prototype: void OS_InitSp(void);
 *
 *
 * This function initialises the stack pointer for the startup code.
 * It is only used for the master core, the other cores' stack pointer
 * is initialized in OS_TricoreStartCore.
 *
 * The initial stack value is obtained from the symbol OS_INITIAL_SP.
 *
 * We can safely use the entire stack area, because StartOS is a
 * system call and so switches to the kernel/isr stack.
 *
 * It is called via a JL instruction from the startup code,
 * and therefore must return with a special instruction (JI A11).
 * No function calls are allowed inside this function.
 *
 * This function is needed by TRICORE BSPs.
 */
	_align(4,2)

_TTYPE(OS_InitSp,FUNC)
_TTYPE(__callee.OS_InitSp.da.v.v,FUNC)
	movh.a		sp,_IMM(#,_hiword(OS_INITIAL_SP))
	lea			sp,[sp]_loword(OS_INITIAL_SP)
	ji			a11

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
