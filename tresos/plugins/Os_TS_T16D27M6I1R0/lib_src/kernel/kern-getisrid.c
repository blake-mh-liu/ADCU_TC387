/* kern-getisrid.c
 *
 * This file contains the OS_GetIsrId function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   The statements can be reached, if "error handling for APIs returning void" is not excluded.
 *   See also OS_EXCLUDE_ERRORHANDLINGFORVOIDAPI.
 *   (In addition to this calling context checks or interrupt enable checks have to be enabled.)
*/

#define OS_SID	OS_SID_GetIsrId
#define OS_SIF	OS_svc_GetIsrId

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernGetIsrId implements the API GetISRID
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.GetISRID, 2
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_isrid_t OS_KernGetIsrId(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_isrid_t i = OS_NULLISR;

	OS_TRACE_GETISRID_ENTRY();

	if ( !OS_CallingContextCheck() )
	{
		if ( OS_ErrorHandlingForVoidApi() )
		{
			/* can't propagate the return value of OS_ERROR -> ignore it */
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			(void) OS_ERROR(OS_ERROR_WrongContext, OS_NULL);
		}
	}
	else
	if ( !OS_InterruptEnableCheck(OS_IEC_AUTOSAR) )
	{
		if ( OS_ErrorHandlingForVoidApi() )
		{
			/* can't propagate the return value of OS_ERROR -> ignore it */
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			(void) OS_ERROR(OS_ERROR_InterruptDisabled, OS_NULL);
		}
	}
	else
	{
		i = kernel_data->isrCurrent;
	}

	OS_TRACE_GETISRID_EXIT_P(i);
	return i;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_getisrid_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
