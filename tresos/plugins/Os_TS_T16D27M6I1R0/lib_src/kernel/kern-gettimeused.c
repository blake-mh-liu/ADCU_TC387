/* kern-gettimeused.c
 *
 * This file contains the OS_GetTimeUsed function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/
#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetTimeUsed
 *
 * This function returns the amount of time used since it was last called.
 * It uses the global accounting structure, so it guarantees that the
 * global frc location holds the time of the last call and can therefore
 * be used as the baseline when setting the execution-timer interrupt.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_tick_t OS_GetTimeUsed(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_timervalue_t frc = OS_ReadExecTimer();
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_tick_t used = (os_tick_t)OS_ExecTimerSub(frc, kernel_data->accounting.frc);
	kernel_data->accounting.frc = frc;

	return used;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_gettimeused_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
