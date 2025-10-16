/* kern-stopisrintlocktiming.c
 *
 * This file contains the OS_StopIsrIntLockTiming function.
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
 *   Variable is set but never used.
 *
 * Reason: Not an issue, variable will be used if timing protection is enabled.
 *
 * TOOLDIAG-2) Possible diagnostic: PointlessComparison
 *   Condition is always false.
 *
 * Reason: If timing protection is switched off, OS_GET_ILOCK always evaluates to zero.
 *
 * TOOLDIAG-3) Possible diagnostic: ControllingExpressionIsConstant
 *   Controlling expression is constant.
 *
 * Reason: Not an issue, controlling expression is not a constant if
 * timing protection is enabled.
 *
 * TOOLDIAG-4) Possible diagnostic: GNUStatementExpressionExtension
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
 * OS_StopIsrIntLockTiming
 *
 * This function stops interrupt-lock timing for the isr. If execution
 * time monitoring was previously running the time remaining is computed
 * and monitoring is restarted.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StopIsrIntLockTiming(os_isrid_t i, os_intlocktype_t locktype)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	/* Possible diagnostic TOOLDIAG-1 <1> */
	const os_isr_t * const isr = &OS_isrTableBase[i];
	os_tick_t locktime;
	os_tick_t used;

	OS_PARAM_UNUSED(i);

	locktime = OS_GET_ILOCK((locktype == OS_LOCKTYPE_OS) ? isr->osLockTime : isr->allLockTime);

	/* Possible diagnostic TOOLDIAG-2 <1> */
	if ( locktime != 0u )
	{
		/* Possible diagnostic TOOLDIAG-4 <+1> */
		OS_ResetExecTimingInterrupt();
		used = OS_GetTimeUsed();

		if ( locktype == OS_LOCKTYPE_OS )
		{
			kernel_data->accounting.etUsed += used + kernel_data->accounting.osSaveUsed;
			kernel_data->accounting.etLimit = kernel_data->accounting.osSaveLimit;
			kernel_data->accounting.etType = kernel_data->accounting.osSaveType;
		}
		else
		{
			kernel_data->accounting.etUsed += used + kernel_data->accounting.allSaveUsed;
			kernel_data->accounting.etLimit = kernel_data->accounting.allSaveLimit;
			kernel_data->accounting.etType = kernel_data->accounting.allSaveType;
		}

		/* Possible diagnostic TOOLDIAG-3 <1> */
		if ( OS_GET_ACCT(((isr->flags & OS_ISRF_MEASUREEXEC) != 0u)
				&& (isr->accounting->etMax < kernel_data->accounting.etUsed)) )
		{
			/* Deviation MISRAC2012-1 <+1> */
			OS_SET_ACCT(isr->accounting->etMax = kernel_data->accounting.etUsed);
		}

		/* COVPT-1 */
		if ( kernel_data->accounting.etLimit != 0u )
		{
			/* COVPT-2 */
			if ( kernel_data->accounting.etUsed >= kernel_data->accounting.etLimit )
			{
				OS_ExceedExecTime();
			}
			else
			{
				/* Possible diagnostic TOOLDIAG-4 <+1> */
				OS_SetExecTimingInterrupt(
						kernel_data->accounting.frc,
						(kernel_data->accounting.etLimit - kernel_data->accounting.etUsed));
			}
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_stopisrintlocktiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
