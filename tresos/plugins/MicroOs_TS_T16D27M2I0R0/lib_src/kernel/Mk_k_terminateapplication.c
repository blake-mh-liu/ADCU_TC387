/* Mk_k_terminateapplication.c
 *
 * This file contains the MK_TerminateApplication() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_panic.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_task.h>
#include <private/Mk_isr.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_ctrsub.h>

/* These prototypes keep MISRA checkers happy.
*/
static void MK_DisableAllAppIrqs(mk_objectid_t);
static void MK_ResetAllAppTaskActivationCounters(mk_objectid_t);

/* MK_DisableAllAppIrqs()
 *
 * Disables all interrupt sources that could trigger an ISR belonging
 * to the OS-Application.
*/
static void MK_DisableAllAppIrqs(mk_objectid_t applicationId)
{
	mk_objectid_t i;

	for ( i = 0; i < MK_nIsrs; i++ )
	{
		if ( MK_isrCfg[i].threadCfg.applicationId == applicationId )
		{
			MK_HwDisableIrq(MK_isrCfg[i].irq);
		}
	}
}

/* MK_ResetAllAppTaskActivationCounters()
 *
 * Resets all activation counters of tasks belonging to the OS-Application.
*/
static void MK_ResetAllAppTaskActivationCounters(mk_objectid_t applicationId)
{
	mk_objectid_t taskId;

	for ( taskId = 0; taskId < MK_nTasks; taskId++ )
	{
		if ( MK_taskCfg[taskId].threadCfg.applicationId == applicationId )
		{
			MK_taskCfg[taskId].dynamic->activationCount = 0;
		}
	}
}

/* MK_TerminateApplication() terminates all threads belonging to a given OS-Application
 * and removes all instances of a task belonging to this OS-Application from job queues.
 * It also disables all IRQs of the application.
 *
 * Precondition:
 * - applicationId is valid (different from MK_APPL_NONE).
 *
 * !LINKSTO Microkernel.Function.MK_TerminateApplication, 2
 * !doctype src
*/
void MK_TerminateApplication(mk_kernelcontrol_t *coreVars, mk_objectid_t applicationId, mk_boolean_t restartOption)
{
	mk_thread_t **pred_next;
	mk_thread_t *t;
	mk_thread_t *lqhead = MK_NULL;

	pred_next = &coreVars->threadQueueHead;

	/* Disable all application interrupt sources.
	*/
	MK_DisableAllAppIrqs(applicationId);

	/* Make sure the OS-Application is quarantined (cannot be restarted).
	*/
	MK_appCfg[applicationId].dynamic->appState = APPLICATION_TERMINATED;

	while ( *pred_next != MK_NULL )
	{
		t = *pred_next;

		/* If the thread has a job queue, we remove all jobs belonging to the OS-Application before terminating the
		 * thread itself, because MK_TerminateThread() could activate another task from the same OS-Application again.
		*/
		if ( t->jobQueue != MK_NULL )
		{
			if ( t->objectType == MK_OBJTYPE_TASK )
			{
				MK_JqRemoveAllTasksOfApp(t->jobQueue, applicationId);
			}
			else
			{
				/* If ISR threads have job queues we'll need to sort them out too.
				 * Other thread types have job queues, but nothing to kill in there.
				*/
			}
		}

		if ( t->applicationId == applicationId )
		{
			/* t's predecessor in the thread queue must be adjusted
			*/
			*pred_next = t->next;

			/* t needs to be terminated, so move it to the local queue first.
			*/
			t->next = lqhead;
			lqhead = t;
		}
		else
		{
			/* If this thread has a parent thread which belongs to the application
			 * that we are terminating, delete the reference to the parent thread.
			 */
			if ( (t->parentThread != MK_NULL) && (t->parentThread->applicationId == applicationId) )
			{
				t->parentThread = MK_NULL;
				t->parentCookie = MK_NULLCOOKIE;
				t->parentCore = MK_NULLPARENTCORE;
			}

			pred_next = &(t->next);
		}
	}

	/* Now, terminate everything in the local queue
	*/
	while ( lqhead != MK_NULL )
	{
		t = lqhead;
		lqhead = lqhead->next;

		/* Thread has been dequeued (from the thread queue), so terminate it.
		 * The lock level is never preserved for tasks and ISRs so we can pass 0 here.
		*/
		MK_HwFreeThreadRegisters(t->regs);
		MK_TerminateThread(coreVars, t, 0);
	}

	/* Reset all activation counters.
	*/
	MK_ResetAllAppTaskActivationCounters(applicationId);

	/* Start the counter subsystem side of TerminateApplication.
	*/
	(void)MK_StartCtrSubTerminateApplication(coreVars, applicationId, restartOption);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
