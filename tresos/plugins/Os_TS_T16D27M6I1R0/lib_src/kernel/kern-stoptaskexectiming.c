/* kern-stoptaskexectiming.c
 *
 * This file contains the OS_StopTaskExecTiming function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *   Condition is always false.
 *
 * Reason: If timing protection is switched off, OS_GET_ACCT always evaluates to OS_NULL.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_StopTaskExecTiming
 *
 * This function stops the hardware timer used for execution timing.
 *
 * !LINKSTO Kernel.Autosar.Protection.TimingProtection.ExecutionTime.Measurement.Task, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StopTaskExecTiming(const os_task_t *tp)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_taskaccounting_t *acc = OS_GET_ACCT(tp->accounting);
	os_tick_t used;

	OS_PARAM_UNUSED(tp);

	/* Possible diagnostic TOOLDIAG-1 <1> */
	if ( acc != OS_NULL )
	{
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		OS_ResetExecTimingInterrupt();
		used = OS_GetTimeUsed();

		/* We don't check the limit here. The task managed to get as far as the disable interrupts
		 * section in terminate task wihtout being killed, so we give it the benefit of the doubt.
		*/
		kernel_data->accounting.etUsed += used;

		if (kernel_data->accounting.etUsed > acc->etMax)
		{
			acc->etMax = kernel_data->accounting.etUsed;
		}

		kernel_data->accounting.inFunction = OS_INNOTHING;
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_stoptaskexectiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
