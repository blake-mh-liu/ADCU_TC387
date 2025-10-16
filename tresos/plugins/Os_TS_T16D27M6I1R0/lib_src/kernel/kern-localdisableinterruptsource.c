/* kern-localdisableinterruptsource.c
 *
 * This file contains the OS_LocalDisableInterruptSource function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* The SID and serviceinfo aren't actually used in the code, but the error table builder
 * needs them to check for error codes that are defined but not used, or used but not defined.
*/

#define OS_SID  OS_SID_DisableInterruptSource
#define OS_SIF  OS_svc_DisableInterruptSource

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_panic.h>

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_LocalDisableInterruptSource implements the DisableInterruptSource.
 *
*/

OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_LocalDisableInterruptSource(const os_isr_t *isr)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t result = OS_ERRORCODE_NOCHECK(OS_ERROR_NoError);
	os_intstatus_t is;
	if ( !OS_APPISACCESSIBLE(isr->app) )
	{
		result = OS_ERRORCODE_CHECK(OS_ERROR_ApplicationNotAccessible);
	}
	else
	{
		/* !LINKSTO	Kernel.API.InterruptHandling.DisableInterruptSource.Nest, 1
		 */
		is = OS_IntDisable();
		if ((isr->dynamic->statusflags & OS_ISRF_BLOCKED) == 0u )
		{
			isr->dynamic->statusflags |= OS_ISRF_BLOCKED;
			OS_DisableIsr(isr);
		}
		else
		{
			/* !LINKSTO Kernel.API.InterruptHandling.DisableInterruptSource.API.ErrorHandling, 1
			 */
			result = OS_ERRORCODE_CHECK(OS_ERROR_ISRAlreadyDisabled);
		}
		OS_IntRestore(is);
	}
	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_localdisableinterruptsource_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
