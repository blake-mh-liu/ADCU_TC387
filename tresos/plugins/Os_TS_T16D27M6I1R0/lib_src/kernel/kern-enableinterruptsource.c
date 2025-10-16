/* kern-enableinterruptsource.c
 *
 * This file contains the OS_KernEnableInterruptSource() function.
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
 *   The statements can be reached, if status is EXTENDED.
 *
 * TOOLDIAG-2) Possible diagnostic: UnusedVariable
 *   Variable is set but never used.
 *
 * Reason: Not an issue, variable will be used if at least one application exists.
*/

#define OS_SID	OS_SID_EnableInterruptSource
#define OS_SIF	OS_svc_EnableInterruptSource

/* Note: this comment is needed for asc_Os/tools/errdb-to-c.pl
 *
 * OS_ERRORCODE_CHECK(OS_ERROR_CoreIsDown)
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernEnableInterruptSource implements the API EnableInteruptSource
 *
 * The interrupt source corresponding to the given parameter is enabled.
 * !LINKSTO Kernel.API.InterruptHandling.EnableInterruptSource.API, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernEnableInterruptSource(os_isrid_t i, os_boolean_t clearPending)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t r = OS_E_OK;
	OS_PARAMETERACCESS_DECL

	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)i);
	OS_TRACE_ENABLEINTERRUPTSOURCE_ENTRY(i);
	
	if ( !OS_CallingContextCheck() )
	{
		/* !LINKSTO Kernel.API.InterruptHandling.EnableInterruptSource.Task, 1
		 * !LINKSTO Kernel.API.InterruptHandling.EnableInterruptSource.ISRC2, 1
		*/
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		r = OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_IsValidIsrId(i) )
	{
		/* !LINKSTO Kernel.API.InterruptHandling.EnableInterruptSource.API.InvalidIsrId, 1
		*/
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		r = OS_ERROR(OS_ERROR_InvalidIsrId, OS_GET_PARAMETER_VAR());
	}
	else
	{
		const os_isr_t *isr = &OS_isrTableBase[i];
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		const os_appcontext_t * const app = OS_CurrentApp();
		if ( !OS_HasPermission(app, isr->permissions) )
		{
			r = OS_ERROR(OS_ERROR_Permission, OS_GET_PARAMETER_VAR());
		}
		else
		{
			os_errorresult_t e = OS_DoEnableInterruptSource(i, isr, clearPending);
			if ( e != OS_ERRORCODE_NOCHECK(OS_ERROR_NoError) )
			{
				/* !LINKSTO Kernel.Autosar.Multicore.EnableInterruptSource.Errorhandling, 1
				*/
				r = OS_ERROR_NOCHECK(e, OS_GET_PARAMETER_VAR());
			}
		}
	}
	OS_TRACE_ENABLEINTERRUPTSOURCE_EXIT_P(r,i);
	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_enableinterruptsource_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
