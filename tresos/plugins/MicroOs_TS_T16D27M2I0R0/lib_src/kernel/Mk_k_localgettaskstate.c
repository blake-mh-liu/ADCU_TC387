/* Mk_k_localgettaskstate.c
 *
 * This file contains the function MK_LocalGetTaskState().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_event.h>
#include <private/Mk_errorhandling.h>

/* MK_LocalGetTaskState() determines a task's state
 *
 * The state is determined by looking at:
 * - the activation counter
 * - whether the task is currently "on" its thread
 * - the pending events (for EXTENDED tasks)
 *
 * Note: This implementation is preferred over maintaining a task state for each task because
 * the cost of updating the state during normal running is borne by the system as a whole, whereas
 * with this method the cost is borne by the caller (and occurs much less frequently).
 *
 * The function executes inside the microkernel on the same core as the task whose state is to
 * be determined. Otherwise the consistency of the task's state is not guaranteed.
 *
 * Note: The function puts the state in the output variable referenced by the pointer 'state'.
 *
 * !LINKSTO Microkernel.Function.MK_LocalGetTaskState, 1
 * !doctype src
*/
mk_errorid_t MK_LocalGetTaskState
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t taskId,			/* Pre-validated task index */
	const mk_taskcfg_t *taskCfg,	/* Task config structure */
	mk_taskstate_t *state
)
{
	mk_task_t *task;
	mk_thread_t *thread;

	task = taskCfg->dynamic;
	thread = taskCfg->thread;

	if ( task->activationCount <= 0 )
	{
		/* Task is not active
		*/
		*state = SUSPENDED;
	}
	else
	if ( (taskCfg->eventStatus != MK_NULL) && (taskCfg->eventStatus->awaitedEvents != 0u) )
	{
		/* Task is an extended task that is waiting for one or more events
		*/
		*state = WAITING;
	}
	else
	if ( thread->currentObject == taskId )
	{
		/* Task is currently occupying its thread, so is either RUNNING or READY.
		 * However, the task's state is not the same as the thread's state because the service
		 * might be called from an ISR or hook function, which also run in threads and will therefore
		 * have preempted the task's thread. So we need to determine if the task's thread is the
		 * highest-priority task thread in the system. Tasks in state NEW have never been dispatched
		 * so must not be reported as RUNNING.
		*/
		if ( thread == MK_FindFirstThread(coreVars->threadQueueHead, MK_OBJTYPE_TASK, MK_THS_NEW) )
		{
			*state = RUNNING;
		}
		else
		{
			*state = READY;
		}
	}
	else
	{
		/* Task is not occupying its thread. It is therefore assumed to be somewhere in the
		 * thread's job queue.
		 * CAVEAT: if an extended task has gone into the waiting state with an empty event set
		 * (awaitedEvents == 0) it became a zombie. This function will report it as "READY".
		 * WaitEvent should prevent that from happening so we don't try to differentiate here.
		*/
		*state = READY;
	}

	return MK_eid_NoError;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
