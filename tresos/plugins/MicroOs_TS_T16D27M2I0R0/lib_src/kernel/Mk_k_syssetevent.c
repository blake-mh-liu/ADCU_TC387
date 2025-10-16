/* Mk_k_syssetevent.c
 *
 * This file contains the MK_SysSetEvent() function.
 *
 * This function is called by the system call function whenever the SetEvent system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>

/*
 * MK_SysSetEvent() sets the given event(s) in the specified EXTENDED task's pending events state and
 * if the task is waiting for one or more pending events, reactivates it on its thread.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "SetEvent" system call.
 *
 * !LINKSTO Microkernel.Function.MK_SysSetEvent, 1
 * !doctype src
*/
void MK_SysSetEvent(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t p = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	const mk_taskcfg_t *taskCfg;

	mk_errorid_t errorCode = MK_eid_Unknown;

	/* Explicit cast to prevent compiler warning (ok, as the number of tasks is always >= 0).
	*/
	if ( p < (mk_parametertype_t)MK_nTasks )
	{
		mk_objectid_t taskId = (mk_objectid_t)p;
		taskCfg = &MK_taskCfg[taskId];

		if ( taskCfg->eventStatus == MK_NULL )
		{
			errorCode = MK_eid_TaskIsNotExtended;
		}
		else
		{
			/* The task is a valid extended task.
			*/
			errorCode = MK_InternSetEvent(coreVars,
										  taskId,
										  taskCfg,
										  (mk_eventmask_t)(MK_HwGetParameter2(caller->regs)),
										  MK_xcore_SetEvent,
										  caller->applicationId);
		}
	}
	else
	{
		errorCode = MK_eid_InvalidTaskId;
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_SetEvent, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
