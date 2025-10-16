/* kern-preemptisrexectiming.c
 *
 * This file contains the OS_PreemptIsrExecTiming() function.
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
 * OS_PreemptIsrExecTiming
 *
 * This function is called from the category 2 interrupt entry routine.
 * It stops any current ISR execution timing and stores the state into
 * the specified accounting save structure.
 *
 * !LINKSTO Kernel.Autosar.Protection.TimingProtection.ExecutionTime.Measurement.Task, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_PreemptIsrExecTiming(os_accountingsave_t *save)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_tick_t used;

	/* COVPT-1 */
	if ( kernel_data->accounting.inFunction == OS_INNOTHING )
	{
		save->inFunction = OS_INNOTHING;
		save->etType = OS_ACC_NONE;
		save->etUsed = 0;
		save->etLimit = 0;
	}
	else
	{
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		OS_ResetExecTimingInterrupt();
		used = OS_GetTimeUsed();

		/* We don't check for exceeded here - that's best done in the "resume"
		 * function. Doing it here would "kill" the ISR immediately, and the
		 * ISR whose wrapper we're in won't run.
		*/
		save->etUsed = kernel_data->accounting.etUsed + used;
		save->etLimit = kernel_data->accounting.etLimit;
		save->inFunction = kernel_data->accounting.inFunction;
		save->etType = kernel_data->accounting.etType;

		kernel_data->accounting.inFunction = OS_INNOTHING;
		kernel_data->accounting.etType = OS_ACC_NONE;
		kernel_data->accounting.etUsed = 0;
		kernel_data->accounting.etLimit = 0;
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_preemptisrexectiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
