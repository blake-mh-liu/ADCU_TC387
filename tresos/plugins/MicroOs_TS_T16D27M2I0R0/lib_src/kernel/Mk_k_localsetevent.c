/* Mk_k_localsetevent.c
 *
 * This file contains the MK_LocalSetEvent() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_task.h>
#include <public/Mk_error.h>
#include <private/Mk_application.h>

/*
 * MK_LocalSetEvent() set the given event(s) in the specified EXTENDED task's pending events state and
 * if the task is waiting for one or more pending events, reactivates it on its thread.
 *
 * !LINKSTO Microkernel.Function.MK_LocalSetEvent, 2
 * !doctype src
*/
mk_errorid_t MK_LocalSetEvent
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t taskId,
	const mk_taskcfg_t *taskCfg,
	mk_eventmask_t eventsToSet,
	mk_objectid_t callerApp
)
{
	const mk_threadcfg_t *threadCfg;
	mk_thread_t *thread;
	mk_eventstatus_t *eventStatus;
	mk_objectid_t aId;
	mk_errorid_t errorCode = MK_eid_Unknown;

	aId = taskCfg->threadCfg.applicationId;

	if ( MK_AppStateOk(aId, callerApp) )
	{

		eventStatus = taskCfg->eventStatus;
		eventStatus->pendingEvents |= eventsToSet;

		if ( (eventStatus->pendingEvents & eventStatus->awaitedEvents) != 0u )
		{
			/* awaitedEvents != 0 is used as an indication that the task is waiting,
			 * so it must be set to 0 when leaving the WAITING state.
			*/
			eventStatus->awaitedEvents = 0u;

			thread = taskCfg->thread;

			if ( thread->state == MK_THS_IDLE )
			{
				threadCfg = &taskCfg->threadCfg;

				MK_SetupThread(thread, threadCfg);
				MK_EnqueueThread(&coreVars->threadQueueHead, thread);

				/* If the task used the WaitGetClearEvent system call, set the status to
				 * the dispatcher that it should do the Get and Clear parts of the API
				*/
				if ( eventStatus->waitingState == MK_WAITGETCLEAR )
				{
					thread->eventStatus = eventStatus;
				}

				/* Clear the task's "waiting" state; the task is no longer WAITING, it is now READY.
				*/
				eventStatus->waitingState = MK_NO_WAIT;
			}
			else
			{
				/* In this branch we don't change the "waiting" state because it gets used
				 * when the task comes out of the job queue (in MK_TerminateThread).
				*/
				MK_JqAppend(thread->jobQueue, (mk_jobid_t)taskId);
			}
		}

		errorCode = MK_eid_NoError;
	}
	else
	{
		errorCode = MK_eid_Quarantined;
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
