/* kern-resumeisrexectiming.c
 *
 * This file contains the OS_ResumeIsrExecTiming function.
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
 * OS_ResumeIsrExecTiming
 *
 * This function is called from the category 2 interrupt entry routine.
 * It restarts any saved ISR execution timing, unless the limit has been reached.
 *
 * !LINKSTO Kernel.Autosar.Protection.TimingProtection.ExecutionTime.Measurement.ISR, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ResumeIsrExecTiming(os_accountingsave_t *save)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();

	kernel_data->accounting.inFunction = save->inFunction;
	kernel_data->accounting.etType = save->etType;
	kernel_data->accounting.etUsed = save->etUsed;
	kernel_data->accounting.etLimit = save->etLimit;

	/* COVPT-1 */
	if ((kernel_data->accounting.etLimit != 0u) && (kernel_data->accounting.etUsed >= kernel_data->accounting.etLimit))
	{
		OS_ExceedExecTime();
	}
	else
	{
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		kernel_data->accounting.frc = OS_ReadExecTimer();
		if (kernel_data->accounting.etLimit != 0u)
		{
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			OS_SetExecTimingInterrupt(kernel_data->accounting.frc,
					(kernel_data->accounting.etLimit - kernel_data->accounting.etUsed));
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_resumeisrexectiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
