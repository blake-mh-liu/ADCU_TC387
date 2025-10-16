/* Mk_k_localactivatetask.c
 *
 * This file contains the MK_LocalActivateTask function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_task.h>
#include <private/Mk_jobqueue.h>

/*
 * MK_LocalActivateTask() activates a task on the caller's core.
 *
 * This function is called to activate a task on the core on which the function is called.
 * It can be used in functions called directly from the microkernel, such as internal interrupt routines.
 *
 * Precondition: taskId has been range-checked by the caller.
 *
 * !LINKSTO Microkernel.Function.MK_LocalActivateTask, 2
 * !doctype src
*/
mk_errorid_t MK_LocalActivateTask
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t taskId,
	const mk_taskcfg_t *taskCfg,
	mk_objectid_t callerApp
)
{
	mk_task_t *task;
	mk_thread_t *thread;
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_objectid_t aId;

	task = taskCfg->dynamic;
	aId = taskCfg->threadCfg.applicationId;

	if ( MK_AppStateOk(aId, callerApp) )
	{
		if ( task->activationCount < taskCfg->maxActivations )
		{
			task->activationCount++;
			thread = taskCfg->thread;

			if ( taskCfg->eventStatus != MK_NULL )
			{
				/* Start with a clean slate of events.
				*/
				taskCfg->eventStatus->pendingEvents = 0u;
				taskCfg->eventStatus->awaitedEvents = 0u;
			}

			if ( thread->state == MK_THS_IDLE )
			{
				MK_StartThread(&coreVars->threadQueueHead, thread, &taskCfg->threadCfg);
			}
			else
			{
				MK_JqAppend(thread->jobQueue, (mk_jobid_t)taskId);

				if ( taskCfg->eventStatus != MK_NULL )
				{
					/* Extended tasks get their registers preloaded here because when they
					 * are taken off the queue it is assumed they are restarting, not starting.
					 *
					 * Some processors need to allocate some space for register windows, so that
					 * must be done first.
					*/
					MK_HwAllocateThreadRegisters(taskCfg->threadCfg.regs);
					MK_FillThreadRegisters(taskCfg->threadCfg.regs, &taskCfg->threadCfg);
				}
			}
			errorCode = MK_eid_NoError;
		}
		else
		{
			errorCode = MK_eid_MaxActivationsExceeded;
		}
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
