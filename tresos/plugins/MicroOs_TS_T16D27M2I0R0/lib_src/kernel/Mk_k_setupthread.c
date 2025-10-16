/* Mk_k_setupthread.c
 *
 * This file contains the MK_SetupThread() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <Mk_kconfig.h>
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* MK_SetupThread() sets up a thread from a thread configuration structure.
 *
 * Parameters:
 *	thread		- the address of the thread structure
 *	threadCfg	- address of a thread config block for this thread
 *
 * Precondition:
 *	the thread is idle
 *
 * !LINKSTO Microkernel.Function.MK_SetupThread, 1
 * !doctype src
*/
void MK_SetupThread
(	mk_thread_t *thread,
	const mk_threadcfg_t *threadCfg
)
{
	thread->currentObject = threadCfg->currentObject;
	thread->objectType = threadCfg->objectType;

	/* Set the parent to "none". Most thread types do not need a parent.
	 * When there's a parent it will be overwritten by the caller.
	*/
	thread->parentThread = MK_NULL;

	thread->parentCookie = MK_NULLCOOKIE;

	thread->parentCore = MK_NULLPARENTCORE;

	thread->queueingPriority = threadCfg->queuePrio;
	thread->runningPriority = threadCfg->runningPriority;
	thread->memoryPartition = threadCfg->memoryPartition;
	thread->name = threadCfg->name;
	thread->regs = threadCfg->regs;
	thread->applicationId = threadCfg->applicationId;
	thread->lastLockTaken = MK_NULL;

	/* Copy and initialize the accounting information.
	*/
	thread->accounting.acctCfg = &threadCfg->acctCfg;
	thread->accounting.timeRemaining = threadCfg->acctCfg.execBudget;

	/* The thread gets queued (later) by default with its queueing priority.
	*/
	thread->currentPriority = thread->queueingPriority;

	MK_TRACE_STATE_THREAD(thread->objectType, thread->currentObject, thread->name, thread->state, MK_THS_NEW);
	thread->state = MK_THS_NEW;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
