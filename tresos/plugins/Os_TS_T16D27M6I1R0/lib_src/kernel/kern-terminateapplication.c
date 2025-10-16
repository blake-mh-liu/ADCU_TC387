/* kern-terminateapplication.c
 *
 * This file contains the OS_KernTerminateApplication function.
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
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if "interrupt enable checks" are not excluded.
 *
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if EXTENDED status is used.
*/

#define OS_SID	OS_SID_TerminateApplication
#define OS_SIF	OS_svc_TerminateApplication

/* Note: this comment is needed for asc_Os/tools/errdb-to-c.pl
 *
 * OS_ERRORCODE_CHECK(OS_ERROR_CoreIsDown)
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#if (OS_N_CORES > 1)
#include <Os_messagequeue.h>
#endif

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernTerminateApplication implements the API TerminateApplication
 *
 * The application with ID 'appid' is terminated.
 * If the restart option is set to RESTART the restart task is activated.
 * If no application can be identified, or if called from a context other
 * than task, Cat2 ISR or ErrorHook, the error handler is called.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication, 3
 * !LINKSTO Kernel.Autosar.OsApplication.Shutdown, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernTerminateApplication(os_applicationid_t appid, os_restart_t restart)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_result_t r = OS_E_OK;

#if (OS_KERNEL_TYPE!=OS_MICROKERNEL)

	OS_PARAMETERACCESS_DECL

	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)appid);
	OS_SAVE_PARAMETER_N(1,(os_paramtype_t)restart);

	OS_TRACE_TERMINATEAPPLICATION_ENTRY(appid, restart);

	/* The calling context check is performed explicitly in this function because the
	 * behaviour depends on the calling context.
	 * The check is done later after all other static checks
	*/
	if ( !OS_InterruptEnableCheck(OS_IEC_OSEKEXTRA) )
	{
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		r = OS_ERROR(OS_ERROR_InterruptDisabled, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_IsValidApplicationId(appid) )
	{
		/*
		 * !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication.InvalidApplication, 1
		*/
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		r = OS_ERROR(OS_ERROR_InvalidApplicationId, OS_NULL);
	}
	else
	if ( (restart != OS_APPL_RESTART) && (restart != OS_APPL_NO_RESTART) )
	{
		/*
		 * !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication.OutOfRange, 1
		*/
		r = OS_ERROR(OS_ERROR_InvalidRestartOption, OS_GET_PARAMETER_VAR());
	}
	else
	{
		const os_appcontext_t * const app = &OS_appTableBase[appid];
		const os_appcontext_t * const callingApp = OS_CurrentApp();

		/* AUTOSAR 4.0.3 [OS494] (only trusted applications may terminate other applications)
		 *
		 * !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication.Permission, 1
		*/
		if ( (callingApp != app) && (!OS_AppIsTrusted(callingApp)) )
		{
			r = OS_ERROR(OS_ERROR_Permission, OS_GET_PARAMETER_VAR());
		}
		else
		{
			/* Special calling context check: TASK or ISR are handled "normally"
			 * !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication.InvalidContext, 1
			*/
			if ( ( kernel_data->inFunction == OS_INTASK ) || ( kernel_data->inFunction == OS_INCAT2 ) )
			{
				os_errorresult_t e;

				e = OS_DoTerminateApplication(appid, app, restart);
				if ( e != OS_ERRORCODE_NOCHECK(OS_ERROR_NoError) )
				{
					r = OS_ERROR_NOCHECK(e, OS_GET_PARAMETER_VAR());
				}

				/* If called from an ISR belonging to the application to be terminated, we must
				 * kill the running instance of the ISR.
				*/
				if ( ( kernel_data->inFunction == OS_INCAT2 ) &&
					 ( OS_isrTableBase[kernel_data->isrCurrent].app == app ) )
				{
					r = OS_E_UNSUPPORTED;
					/* COVPT-1 */
					if ( OS_killIsrFunc == OS_NULL )
					{
						/* If the ISR cannot be killed for some reason we must shut down */
						OS_SHUTDOWN(r, OS_FALSE);
					}
					else
					{
						r = (*OS_killIsrFunc)(kernel_data->isrCurrent);
						/* COVPT-2 */
						if ( r != OS_E_OK )
						{
							OS_SHUTDOWN(r, OS_FALSE);
						}
					}
				}
			}
			else
			if ( ( kernel_data->inFunction == OS_INERRORHOOK ) && ( app == callingApp ) )
			{
				/* restart or quarantine is done by error handler */
				if ( kernel_data->errorStatus.action != OS_ACTION_SHUTDOWN )
				{
					kernel_data->errorStatus.action =
						(restart == OS_APPL_RESTART) ? OS_ACTION_RESTART
													 : OS_ACTION_QUARANTINEAPP;
				}

				/* The running instance of the hook must be killed in any case. */
				r = OS_E_UNSUPPORTED;
				/* COVPT-3 */
				if ( OS_killHookFunc == OS_NULL )
				{
					/* If the hook cannot be killed for some reason we must shut down. */
					OS_SHUTDOWN(r, OS_FALSE);
				}
				else
				{
					r = (*OS_killHookFunc)(&kernel_data->eHookContext);
					/* COVPT-4 */
					if ( r != OS_E_OK )
					{
						OS_SHUTDOWN(r, OS_FALSE);
					}
				}
			}
			else
			{
				r = OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
			}
		}
	}

	OS_TRACE_TERMINATEAPPLICATION_EXIT_P(r, appid, restart);

#endif /* OS_KERNEL_TYPE != OS_MICROKERNEL */

	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_terminateapplication_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
