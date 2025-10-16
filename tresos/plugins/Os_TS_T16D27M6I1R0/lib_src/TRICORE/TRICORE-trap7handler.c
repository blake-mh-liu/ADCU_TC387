/* TRICORE-trap7handler.c
 *
 * This file contains the OS_Trap7Handler function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#define OS_SID OS_SID_ArchTrapHandler
#define OS_SIF OS_svc_ArchTrapHandler

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_panic.h>
#include <TRICORE/Os_TRICORE_core.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_Trap7Handler()
 *
 * This function handles TRICORE class 7 traps.
 *
 * Class 7 traps are caused by some internal event in the CPU, or an external
 * trigger. We just read the register, clear the traps, execute a DEBUG
 * instruction and then panic to shut down the OS. The user can override this
 * function if necessary.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_Trap7Handler(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	 os_uint32_t trapstat;

	/* Read the trap status registers and clear the traps */
	trapstat = OS_pwr.pwr_trapstat;
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
	OS_pwr.pwr_trapsetclr[OS_SETCLRGRP].clr = trapstat;
#else
	OS_pwr.pwr_trapclr = trapstat;
#endif

	OS_DEBUG_BREAK();

	/* can't propagate the return value of OS_PANIC -> ignore it */
	(void) OS_PANIC(OS_PANIC_UnhandledNmi);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_trap7handler_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
