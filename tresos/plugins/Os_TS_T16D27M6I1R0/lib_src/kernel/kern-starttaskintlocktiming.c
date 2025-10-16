/* kern-starttaskintlocktiming.c
 *
 * This file contains the OS_StartTaskIntLockTiming function.
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
 * Reason: If timing protection is switched off, OS_GET_ILOCK always evaluates to zero.
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
 * OS_StartTaskIntLockTiming
 *
 * This function starts interrupt-lock timing for the task.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StartTaskIntLockTiming(const os_task_t *tp, os_intlocktype_t locktype)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_taskaccounting_t *acc = OS_GET_ACCT(tp->accounting);
	os_tick_t locktime;
	os_tick_t used;
	os_tick_t remaining;

	OS_PARAM_UNUSED(tp);

	locktime = OS_GET_ILOCK((locktype == OS_LOCKTYPE_OS) ? tp->osLockTime : tp->allLockTime);

	/* COVPT-1 +2 */
	/* Possible diagnostic TOOLDIAG-1 <1> */
	if ( locktime != 0u )
	{
		/* Possible diagnostic TOOLDIAG-3 <+1> */
		OS_ResetExecTimingInterrupt();
		used = OS_GetTimeUsed();

		kernel_data->accounting.etUsed += used;

		/* Possible diagnostic TOOLDIAG-2 <1> */
		if (OS_GET_ACCT(((tp->flags & OS_TF_MEASUREEXEC) != 0u)
				&& (tp->accounting->etMax < kernel_data->accounting.etUsed)))
		{
			/* Deviation MISRAC2012-1 <+1> */
			OS_SET_ACCT(tp->accounting->etMax = kernel_data->accounting.etUsed);
		}
		/* COVPT-2 +2 */
		if ((kernel_data->accounting.etLimit != 0u)
				&& (kernel_data->accounting.etUsed >= kernel_data->accounting.etLimit))
		{
			OS_ExceedExecTime();
		}
		else
		{
			if (kernel_data->accounting.etLimit == 0u)
			{
				remaining = OS_MAXTICK;
			}
			else
			{
				remaining = kernel_data->accounting.etLimit - kernel_data->accounting.etUsed;
			}

			if (locktype == OS_LOCKTYPE_OS)
			{
				acc->osSaveType = kernel_data->accounting.etType;
				acc->osSaveUsed = kernel_data->accounting.etUsed;
				acc->osSaveLimit = kernel_data->accounting.etLimit;
			}
			else
			{
				acc->allSaveType = kernel_data->accounting.etType;
				acc->allSaveUsed = kernel_data->accounting.etUsed;
				acc->allSaveLimit = kernel_data->accounting.etLimit;
			}

			/* Never allow a task to extend its execution budget by disabling
			 * interrupts!
			*/
			kernel_data->accounting.etUsed = 0;

			if (locktime >= remaining)
			{	/* old remaining time is shorter than new time */
				/* use old time for accounting (and leave accounting type unchanged) */
				kernel_data->accounting.etLimit = remaining;
			}
			else
			{	/* new time is shorter than old remaining time */
				/* use new time for accounting and set new accounting type */
				kernel_data->accounting.etLimit = locktime;
				kernel_data->accounting.inFunction = OS_INTASK;
				kernel_data->accounting.etType = OS_ACC_INTLOCK;
			}
			/* Possible diagnostic TOOLDIAG-3 <+1> */
			OS_SetExecTimingInterrupt(kernel_data->accounting.frc, kernel_data->accounting.etLimit);
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_starttaskintlocktiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
