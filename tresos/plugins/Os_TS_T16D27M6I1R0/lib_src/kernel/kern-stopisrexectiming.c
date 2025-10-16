/* kern-stopisrexectiming.c
 *
 * This file contains the OS_StopIsrExecTiming function.
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
 * OS_StopIsrExecTiming
 *
 * This function is called from the category 2 interrupt exit routine.
 * It accepts the time-remaining value returned by the call to
 * OS_StartIsrExecTiming during interrupt entry.
 * The accounting inFunction has already been restored by the exit
 * routine.
 *
 * !LINKSTO Kernel.Autosar.Protection.TimingProtection.ExecutionTime.Measurement.ISR, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StopIsrExecTiming(const os_isr_t *isr)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_israccounting_t *acc = OS_GET_ACCT(isr->accounting);
	os_tick_t used;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	OS_ResetExecTimingInterrupt();

	/* Possible diagnostic TOOLDIAG-1 <1> */
	if ( acc != OS_NULL )
	{
		used = OS_GetTimeUsed();

		/* We don't check the limit here. The task manage to get as far as the disable interrupts
		 * section in terminate task wihtout being killed, so we give it the benefit of the doubt.
		*/
		kernel_data->accounting.etUsed += used;

		if (((isr->flags & OS_ISRF_MEASUREEXEC) != 0u) && (kernel_data->accounting.etUsed > acc->etMax))
		{
			acc->etMax = kernel_data->accounting.etUsed;
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_stopisrexectiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
