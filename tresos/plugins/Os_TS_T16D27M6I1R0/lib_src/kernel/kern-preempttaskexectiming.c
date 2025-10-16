/* kern-preempttaskexectiming.c
 *
 * This file contains the OS_PreemptTaskExecTiming() function
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
 * OS_PreemptTaskExecTiming
 *
 * This function gets the amount of execution time that has passed since
 * the last measurement point, substracts it from the time remaining,
 * and stores the result in the given task's remaining budget.
 *
 * This function is called by the dispatcher when a task is pre-empted, after the state
 * has been set to READY_SYNC or READY_ASYNC. It is also called by the Category 2 wrapper
 * when a task has been interrupted. It is therefore safe to call OS_Error (and
 * possibly kill the task) here.
 *
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_PreemptTaskExecTiming(const os_task_t *tp)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_taskaccounting_t *acc = OS_GET_ACCT(tp->accounting);
	os_tick_t used;

	/* Possible diagnostic TOOLDIAG-1 <1> */
	if ( acc != OS_NULL )
	{
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		OS_ResetExecTimingInterrupt();
		used = OS_GetTimeUsed();

		kernel_data->accounting.etUsed += used;
		acc->etUsed = kernel_data->accounting.etUsed;
		acc->etType = kernel_data->accounting.etType;

		if ( ((tp->flags & OS_TF_MEASUREEXEC) != 0u) && (kernel_data->accounting.etUsed > acc->etMax) )
		{
			acc->etMax = kernel_data->accounting.etUsed;
		}

		/* COVPT-1 +2 */
		if ( (kernel_data->accounting.etLimit != 0u)
				&& (kernel_data->accounting.etUsed >= kernel_data->accounting.etLimit) )
		{
			OS_ExceedExecTime();
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_preempttaskexectiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
