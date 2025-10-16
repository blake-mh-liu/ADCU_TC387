/* kern-stopreslocktiming.c
 *
 * This file contains the OS_StopResLockTiming function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: UnusedVariable
 *   Variable is never used.
 *
 * Reason: Not an issue, variable will be used if timing protection is enabled.
 *
 * TOOLDIAG-2) Possible diagnostic: ControllingExpressionIsConstant
 *   Controlling expression is constant.
 *
 * Reason: Not an issue, controlling expression is not a constant if
 * timing protection is enabled.
 *
 * TOOLDIAG-3) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
 */
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * If the parameter was enclosed in parentheses, this would result in a
 * C language syntax error. Hence, this isn't viable.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_StopResLockTiming
 *
 * This function stops interrupt-lock timing for the resource. If execution
 * time monitoring was previously running the time remaining is computed
 * and monitoring is restarted.
 *
 * This function is only called if the resource lock was being timed.
 * Interrupts are disabled.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StopResLockTiming(os_resourcedynamic_t *rd)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_tick_t used;

	OS_PARAM_UNUSED(rd);
	/* Possible diagnostic TOOLDIAG-3 <+1> */
	OS_ResetExecTimingInterrupt();
	used = OS_GetTimeUsed();

	kernel_data->accounting.etUsed += used + OS_GET_RLOCK(rd->etUsed);
	kernel_data->accounting.etLimit = OS_GET_RLOCK(rd->etLimit);
	kernel_data->accounting.etType = OS_GET_RLOCK(rd->etType);

	if ( kernel_data->accounting.inFunction == OS_INTASK )
	{
		/* Possible diagnostic TOOLDIAG-1 <1> */
		const os_task_t * const taskCurrent = kernel_data->taskCurrent;
		/* Possible diagnostic TOOLDIAG-2 <1> */
		if ( OS_GET_ACCT(((taskCurrent->flags & OS_TF_MEASUREEXEC) != 0u)
				&& (taskCurrent->accounting->etMax < kernel_data->accounting.etUsed)) )
		{
			/* Deviation MISRAC2012-1 <+1> */
			OS_SET_ACCT(taskCurrent->accounting->etMax = kernel_data->accounting.etUsed);
		}
	}
	/* COVPT-1 +2 */
	else
	if ( kernel_data->accounting.inFunction == OS_INCAT2 )
	{
		/* Possible diagnostic TOOLDIAG-1 <1> */
		const os_isr_t *isr = &OS_isrTableBase[kernel_data->isrCurrent];

		/* Possible diagnostic TOOLDIAG-2 <1> */
		if ( OS_GET_ACCT(((isr->flags & OS_ISRF_MEASUREEXEC) != 0u)
				&& (isr->accounting->etMax < kernel_data->accounting.etUsed)) )
		{
			/* Deviation MISRAC2012-1 <+1> */
			OS_SET_ACCT(isr->accounting->etMax = kernel_data->accounting.etUsed);
		}
	}
	else
	{
		/* MISRA-C */
	}

#ifndef OS_EXCLUDE_TIMINGPROTECTION
	/* COVPT-2 */
	if ( kernel_data->accounting.etLimit > 0u )
	{
		/* COVPT-3 */
		if ( kernel_data->accounting.etUsed >= kernel_data->accounting.etLimit )
		{
			OS_ExceedExecTime();
		}
		else
		{
			/* Possible diagnostic TOOLDIAG-3 <+1> */
			OS_SetExecTimingInterrupt(
					kernel_data->accounting.frc,
					(kernel_data->accounting.etLimit - kernel_data->accounting.etUsed));
		}
	}
#endif
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_stopreslocktiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
