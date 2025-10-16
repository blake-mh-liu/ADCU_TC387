/* Mk_k_sysclearevent.c
 *
 * This file contains the MK_SysClearEvent() function.
 *
 * This function is called by the system call function whenever the ClearEvent system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>

/*
 * MK_SysClearEvent() clears the specified events from the current EXTENDED task's pending events
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "ClearEvent" system call.
 *
 * !LINKSTO Microkernel.Function.MK_SysClearEvent, 1
 * !doctype src
*/
void MK_SysClearEvent(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_eventmask_t eventsToClear;
	mk_eventstatus_t *eventStatus;

	mk_errorid_t errorCode = MK_eid_Unknown;

	if ( caller->objectType == MK_OBJTYPE_TASK )
	{
		eventStatus = MK_taskCfg[caller->currentObject].eventStatus;

		if ( eventStatus == MK_NULL )
		{
			/* Error: the caller is a BASIC task
			*/
			errorCode = MK_eid_TaskIsNotExtended;
		}
		else
		{
			/* The caller is an EXTENDED task
			*/
			errorCode = MK_eid_NoError;

			eventsToClear = (mk_eventmask_t)MK_HwGetParameter1(caller->regs);

			eventStatus->pendingEvents &= ~eventsToClear;
		}
	}
	else
	{
		/* Error: the caller isn't a task
		*/
		errorCode = MK_eid_ThreadIsNotATask;
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_ClearEvent, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
