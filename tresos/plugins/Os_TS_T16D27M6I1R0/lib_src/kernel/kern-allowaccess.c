/* kern-allowaccess.c
 *
 * This file contains the OS_KernAllowAccess() function.
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
 * Reason: If optimization parameter OS_EXCLUDE_INTSENABLEDCHECK is defined,
 *  OS_InterruptEnableCheck always evaluates to true.
 *
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason: If optimization parameter OS_EXCLUDE_INTSENABLEDCHECK is defined,
 *  OS_InterruptEnableCheck always evaluates to true.
 *
 * TOOLDIAG-3) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if there are Cat-2 ISRs.
*/

#define OS_SID	OS_SID_AllowAccess
#define OS_SIF	OS_svc_AllowAccess

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernAllowAccess
 *
 * This function implements the API AllowAccess().
 * If the current application is in the RESTARTING state it is placed in the ACCESSIBLE state.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.AllowAccess, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernAllowAccess(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-3 <+1> */
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_result_t r = OS_E_OK;
	const os_appcontext_t *app = OS_NULL;
	os_appdynamic_t *appd;
	os_intstatus_t is;

	OS_TRACE_ALLOWACCESS_ENTRY();

	/* Possible diagnostic TOOLDIAG-1 <+1> */
	if ( !OS_InterruptEnableCheck(OS_IEC_AUTOSAR) )
	{
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		r = OS_ERROR(OS_ERROR_InterruptDisabled, OS_NULL);
	}
	else
	{
		if ( kernel_data->inFunction == OS_INTASK )
		{
			/* COVPT-1 */
			if ( kernel_data->taskCurrent != OS_NULL )
			{
				app = kernel_data->taskCurrent->app;
			}
		}
		else
		if ( OS_IS_INCAT2( kernel_data->inFunction ) )
		{
			/* COVPT-2 +2 */
			/* Possible diagnostic TOOLDIAG-3 <+1> */
			if ( kernel_data->isrCurrent < OS_nInterrupts )
			{
				app = OS_isrTableBase[kernel_data->isrCurrent].app;
			}
		}
		else
		{
			/* MISRA-C */
		}

		if ( app == OS_NULL )
		{
			/* Either not from task or ISR, or task/ISR is not part of an application
			*/
			r = OS_ERROR(OS_ERROR_WrongContext, OS_NULL);
		}
		else
		{
			appd = app->dynamic;

			is = OS_IntDisable();

			if ( appd->appstate == OS_APP_RESTARTING )
			{
				appd->appstate = OS_APP_ACCESSIBLE;
			}
			else
			{
				/* !LINKSTO Kernel.Autosar.API.SystemServices.AllowAccess.NotRestarting, 1
				*/
				r = OS_ERROR(OS_ERROR_ApplicationNotRestarting, OS_NULL);
			}

			OS_IntRestore(is);
		}
	}

	OS_TRACE_ALLOWACCESS_EXIT_P(r);

	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_allowaccess_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
