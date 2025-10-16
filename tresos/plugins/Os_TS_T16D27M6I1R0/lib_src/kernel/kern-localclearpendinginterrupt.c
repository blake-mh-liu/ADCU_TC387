/* kern-localclearpendinginterrupt.c
 *
 * This file contains the OS_LocalClearPendingInterrupt function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 12.4 (advisory)
 * Evaluation of constant expressions should not lead to unsigned integer wrap-around.
 *
 * Reason:
 * Bitwise invert operator is used to clear specific bits.
*/

/* The SID and serviceinfo aren't actually used in the code, but the error table builder
 * needs them to check for error codes that are defined but not used, or used but not defined.
*/

#define OS_SID  OS_SID_ClearPendingInterrupt
#define OS_SIF  OS_svc_ClearPendingInterrupt

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_panic.h>

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_ClearPendingInterrupt implements the ClearPendingInterrupt.
 *
*/

OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_LocalClearPendingInterrupt(const os_isr_t *isr)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t result = OS_ERRORCODE_NOCHECK(OS_ERROR_NoError);
	if ( !OS_APPISACCESSIBLE(isr->app) )
	{
		/* !LINKSTO Kernel.API.InterruptHandling.ClearPendingInterrupt.API.ErrorHandling, 1
		 */
		result = OS_ERRORCODE_CHECK(OS_ERROR_ApplicationNotAccessible);
	}
	else
	{
		/* Deviation MISRAC2012-1 <+1> */
		OS_ClearIsr(isr);
	}
	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_localclearpendinginterrupt_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
