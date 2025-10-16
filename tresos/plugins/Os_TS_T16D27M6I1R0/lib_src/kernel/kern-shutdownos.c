/* kern-shutdownos.c
 *
 * This file contains the OS_KernShutdownOs function.
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
 * Reason: Not an issue, variable will be used if at least one application exists.
 *
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   The statements can be reached, if "error handling for APIs returning void" is not excluded.
 *   See also OS_EXCLUDE_ERRORHANDLINGFORVOIDAPI.
*/

#define OS_SID	OS_SID_ShutdownOs
#define OS_SIF	OS_svc_ShutdownOs

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernShutdownOs
 *
 * This function shuts down the OS.
 *
 * !LINKSTO Kernel.API.OSControl.ShutdownOS.API, 1
 * Look! No restrictions regarding calling cores!
 * !LINKSTO Kernel.Autosar.Multicore.ShutdownOS, 1
 * Look! No Cross-core calls!
 * !LINKSTO Kernel.Autosar.Multicore.ShutdownOS.CoreLocal, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_KernShutdownOs(os_result_t code)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	OS_PARAMETERACCESS_DECL

	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)code);

	OS_TRACE_SHUTDOWNOS_ENTRY(code);

	if ( !OS_CallingContextCheck() )
	{
		if ( OS_ErrorHandlingForVoidApi() )
		{
			/* can't propagate the return value of OS_ERROR -> ignore it */
			/* Possible diagnostic TOOLDIAG-2 <+1> */
			(void) OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
		}
	}
	else
	if ( !OS_InterruptEnableCheck(OS_IEC_AUTOSAR) )
	{
		if ( OS_ErrorHandlingForVoidApi() )
		{
			/* can't propagate the return value of OS_ERROR -> ignore it */
			/* Possible diagnostic TOOLDIAG-2 <+1> */
			(void) OS_ERROR(OS_ERROR_InterruptDisabled, OS_GET_PARAMETER_VAR());
		}
	}
	else
	{
		/* Possible diagnostic TOOLDIAG-1 <1> */
		const os_appcontext_t * const app = OS_CurrentApp();

		/* !LINKSTO Kernel.Autosar.ServiceErrors.Miscellaneous.Shutdown.Nontrusted, 1
		*/
		if ( OS_AppIsTrusted(app) )
		{
			OS_SHUTDOWN(code, OS_FALSE);
		}
		else
		{
			if ( OS_ErrorHandlingForVoidApi() )
			{
				/* can't propagate the return value of OS_ERROR -> ignore it */
				/* Possible diagnostic TOOLDIAG-2 <+1> */
				(void) OS_ERROR(OS_ERROR_NotTrusted, OS_GET_PARAMETER_VAR());
			}
		}
	}
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_shutdownos_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
