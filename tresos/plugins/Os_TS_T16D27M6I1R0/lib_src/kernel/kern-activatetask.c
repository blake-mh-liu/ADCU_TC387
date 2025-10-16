/* kern-activatetask.c
 *
 * This file contains the OS_KernActivateTask function.
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
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if "calling context checks" are not excluded.
 *
 * TOOLDIAG-3) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if "interrupt enable checks" are not excluded.
 *
 * TOOLDIAG-4) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if EXTENDED status is used.
*/

#define OS_SID OS_SID_ActivateTask
#define OS_SIF OS_svc_ActivateTask

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
 * OS_KernActivateTask implements the API ActivateTask
 *
 * The specified task is activated. If it is already active, the
 * pending activation counter is incremented (up to the maximum).
 * Otherwise the task state is set to NEW and it is enqueued.
 *
 * !LINKSTO Kernel.API.TaskManagement.ActivateTask.API, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernActivateTask(os_taskid_t t)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t r = OS_E_OK;
	OS_PARAMETERACCESS_DECL

	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)t);

	OS_TRACE_ACTIVATETASK_ENTRY(t);

	if ( !OS_CallingContextCheck() )
	{
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		r = OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_InterruptEnableCheck(OS_IEC_OSEKEXTRA) )
	{
		/* Possible diagnostic TOOLDIAG-3 <+1> */
		r = OS_ERROR(OS_ERROR_InterruptDisabled, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_IsValidTaskId(t) )
	{
		/* !LINKSTO Kernel.API.TaskManagement.ActivateTask.InvalidTask, 1
		*/
		/* Possible diagnostic TOOLDIAG-4 <+1> */
		r = OS_ERROR(OS_ERROR_InvalidTaskId, OS_GET_PARAMETER_VAR());
	}
	else
	{
		const os_task_t * const tp = &OS_taskTableBase[t];
		/* Possible diagnostic TOOLDIAG-1 <1> */
		const os_appcontext_t * const app = OS_CurrentApp();
		if ( !OS_HasPermission(app, tp->permissions) )
		{
			r = OS_ERROR(OS_ERROR_Permission, OS_GET_PARAMETER_VAR());
		}
		else
		{
			os_errorresult_t e;

			e = OS_DoActivateTask(tp);
			if ( e != OS_ERRORCODE_NOCHECK(OS_ERROR_NoError) )
			{
				/* !LINKSTO Kernel.Autosar.Multicore.ActivateTask.Errorhandling, 1
				*/
				r = OS_ERROR_NOCHECK(e, OS_GET_PARAMETER_VAR());
			}
		}
	}

	OS_TRACE_ACTIVATETASK_EXIT_P(r,t);
	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_activatetask_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
