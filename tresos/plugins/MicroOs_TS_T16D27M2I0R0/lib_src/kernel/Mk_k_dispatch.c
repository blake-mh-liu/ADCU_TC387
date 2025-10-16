/* Mk_k_dispatch.c
 *
 * This file contains the MK_Dispatch function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  MK_ChkExcBudgetAndSelNextThread can call itself again indirectly via
 *    MK_ReportProtectionFault and MK_Panic, but this can only happen if the
 *    protection hook thread has an execution budget and exceeds it.  In the
 *    unlikely case that also the shutdown thread has an exceeded execution
 *    budget, the calls to MK_ReportProtectionFault and MK_Panic will result in a
 *    call to MK_PanicStop. So there is a maximum nesting of two calls possible.
 *  MK_PrimeExecutionTimer can theoretically call itself again indirectly via
 *    MK_HwSetExecutionTimeAlarm for ARM64, as MK_HwSetExecutionTimeAlarm calls
 *    MK_Panic for an invalid execution budget value. As the shutdown thread
 *    has no execution budget this loop cannot happen.
 *  MK_PrepareThreadForRunning can call itself again indirectly via
 *    MK_HwIntLevelThreadToHardware for architectures/derivatives that perform
 *    read-back checks for the interrupt controller and abort with a panic
 *    (MK_Panic). If the second call also aborts with a panic the repeated call
 *    of MK_Panic results in a call to MK_PanicStop. So there is a maximum
 *    nesting depth of two calls possible.
*/

#include <Mk_kconfig.h>
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_event.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_memoryprotection.h>
#include <private/Mk_errorhandling.h>

static mk_thread_t *MK_ChkExcBudgetAndSelNextThread(mk_kernelcontrol_t *);
static void MK_PrimeExecutionTimer(mk_accounting_t *);
static void MK_UpdateExecutionTimeAlarm(mk_accounting_t *);
static void MK_PrepareThreadForRunning(mk_kernelcontrol_t *, mk_thread_t *);

/*
 * MK_ChkExcBudgetAndSelNextThread() selects the next thread with available execution budget.
 *
 * This helper function is called in case execution budget monitoring is enabled.
 *
 * It computes the remaining budget of the current thread. Then it selects the next thread with an available budget,
 * reporting protection faults for threads that exceeded their budget in the process.
 *
 * The returned thread has sufficient budget available and is eligible to be dispatched.
 */
/* Deviation MISRAC2012-1 */
static mk_thread_t *MK_ChkExcBudgetAndSelNextThread(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *nextThread;
	mk_tick_t currDispatchTime;
	mk_tick_t prevDispatchTime;
	mk_tick_t deltaTime;
	mk_accounting_t *acct;
	mk_thread_t *currThread = coreVars->currentThread;

	/* Update the time remaining for the current thread.
	*/
	prevDispatchTime = coreVars->dispatchTime;
	currDispatchTime = MK_HwReadExecutionTimer();
	coreVars->dispatchTime = currDispatchTime;

	acct = &currThread->accounting;

	if ( (acct->timeRemaining != MK_EXECBUDGET_INFINITE) && (currThread->state != MK_THS_NEW) )
	{
		/* Outgoing thread has an accounting monitor.
		 * Calculate the time used and subtract from the thread's time-remaining accumulator.
		 */
		deltaTime = MK_HwExecutionTimeDelta(currDispatchTime, prevDispatchTime);

		if ( acct->timeRemaining > deltaTime )
		{
			acct->timeRemaining -= deltaTime;
		}
		else
		{
			/* The thread has already reached or exceeded its budget.
			 * Set the time-remaining accumulator to 0. The fault will be picked
			 * up when the thread gets dispatched, which might be immediate if there's no
			 * change of thread. It might also never happen - the thread might have terminated
			 * or waited for an event)
			 */
			acct->timeRemaining = 0;
		}
	}

	/* Try to select a new thread that has enough time remaining.
	*/
	do
	{
		nextThread = coreVars->threadQueueHead;
		acct = &nextThread->accounting;

		/* Has the incoming thread used up its budget?
		 * (The comparison against a minimum time attempts to avoid starting a thread whose
		 * budget will expire immediately)
		 */
		if ( acct->timeRemaining <= MK_MIN_EXECUTIONTIME )
		{
			/* In the future, the error could also be MK_eid_LockBudgetExceeded, so we'll
			 * need to distinguish between the two here.
			 */
			/* Deviation MISRAC2012-1 <+1> */
			MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_ExecutionBudgetExceeded);

			/* Need to try again to get the next thread. Note: if MK_ReportProtectionFault doesn't
			 * change the thread queue, we get stuck in this loop. But it always does something...
			 */
			nextThread = MK_NULL;
		}

	} while ( nextThread == MK_NULL );

	return nextThread;
}

/*
 * MK_PrimeExecutionTimer() primes the execution timer as required for the passed accounting structure
 *
 * The passed pointer may be NULL, in which case no operation is performed. Otherwise, the alarm is
 * primed if the accounting structure contains a finite execution budget, or deactivated otherwise.
 */
/* Deviation MISRAC2012-1 */
static void MK_PrimeExecutionTimer(mk_accounting_t *acct)
{
	/* If execution budgets are configured, start or cancel the timer, as appropriate.
	*/
	if ( acct != MK_NULL )
	{
		if ( acct->timeRemaining == MK_EXECBUDGET_INFINITE )
		{
			/* Infinite budget: turn off the timer.
			*/
			/* Deviation MISRAC2012-1 <+1> */
			MK_HwDispatcherClearExecutionTimeAlarm();
		}
		else
		{
			/* Finite budget: start the timer.
			*/
			/* Deviation MISRAC2012-1 <+1> */
			MK_HwSetExecutionTimeAlarm(acct->timeRemaining);
		}
	}
}

/*
 * MK_PrepareThreadForRunning() prepares the given thread for running
 */
/* Deviation MISRAC2012-1 */
static void MK_PrepareThreadForRunning(mk_kernelcontrol_t *coreVars, mk_thread_t *nextThread)
{
	/* If the thread is a task that is returning from WaitGetClearEvent
	 * (indicated by the eventStatus pointer being non-NULL), do the Get and Clear parts
	 *  - place the pending events into the 2nd return value
	 *  - clear the events from the pending events
	 *  - set the waiting state to "not waiting"
	 *  - clear the eventStatus pointer so that this doesn't happen again until the next WaitGetClearEvent
	*/
	if ( nextThread->eventStatus != MK_NULL )
	{
		MK_HwSetReturnValue2(nextThread->regs, nextThread->eventStatus->pendingEvents);
		nextThread->eventStatus->pendingEvents = 0u;
		nextThread->eventStatus = MK_NULL;
	}

	/* Set the thread's running priority - only if not pre-empted, and
	 * only if the running priority is higher than the queued priority.
	 * This boils down to testing the 2nd condition only - preempted
	 * threads will have a priority not less than their running priority
	 * anyway.
	*/
	if ( nextThread->currentPriority < nextThread->runningPriority )
	{
		nextThread->currentPriority = nextThread->runningPriority;
	}

	/* Set up the context for the new thread.
	*/
	MK_HwIntLevelThreadToHardware(nextThread->regs);

	if ( coreVars->currentMemoryPartition != nextThread->memoryPartition )
	{
		coreVars->currentMemoryPartition = nextThread->memoryPartition;
		MK_HwSetDynamicMemoryPartition(coreVars, coreVars->currentMemoryPartition);
	}
}

/*
 * MK_UpdateExecutionTimeAlarm() calls the hardware specific MK_HwUpdateExecutionTimeAlarm function.
 */
static void MK_UpdateExecutionTimeAlarm(mk_accounting_t * acct)
{
	if ( acct != MK_NULL )
	{
		/* Thread has not changed. The execution timer might need to be updated
		 * or reprogrammed, depending on the hardware characteristics.
		*/
		MK_HwUpdateExecutionTimeAlarm(acct->timeRemaining);
	}
}

/* MK_Dispatch is the thread dispatcher.
 *
 * It selects the most eligible thread (the head of the thread queue) and makes it the current thread.
 * If that action involves a change of thread and the outgoing thread has not terminated, then it is
 * placed in the READY state.
 *
 * The correct memory partition for the incoming thread is loaded.
 *
 * The remaining execution budget for the incoming thread is programmed. The hardware dependent part of
 * this mechanism might need different handling for the cases where a change of thread has or has not occurred.
 *
 * The thread's priority is increased to its configured running priority if necessary (thus acquiring
 * any internal resources and becoming non-preemptive if so configured).
 *
 * Finally the thread's copy of the processor registers is loaded into the processor, thus resuming the
 * thread from where it left off. Most of this is processor-specific and needs to be done in assembly language,
 * so MK_HwResumeThread() is called.
 *
 * !LINKSTO Microkernel.Function.MK_Dispatch, 2
 * !doctype src
*/
/* Deviation MISRAC2012-1 */
void MK_Dispatch(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *currThread = coreVars->currentThread;
	mk_thread_t *nextThread;
	mk_accounting_t *acct;

	if ( coreVars->execBudgetIsConfigured )
	{
		nextThread = MK_ChkExcBudgetAndSelNextThread(coreVars);
		acct = &nextThread->accounting;
	}
	else
	{
		nextThread = coreVars->threadQueueHead;
		acct = MK_NULL;
	}

	/* Now we've got a next thread.
	 * And if exec budget is configured, acct is its accounting structure. Otherwise, it's null.
	*/
	if ( currThread == nextThread )
	{
		/* Thread has not changed. However, a new object instance might have been started.
		*/
		if ( nextThread->state == MK_THS_NEW )
		{
			/* Same thread but new object instance.
			 * State goes to running.
			*/
			MK_TRACE_STATE_THREAD(nextThread->objectType, nextThread->currentObject, nextThread->name,
																				MK_THS_NEW, MK_THS_RUNNING);
			nextThread->state = MK_THS_RUNNING;

			/* If execution budgets are configured, start or cancel the timer, as appropriate.
			*/
			MK_PrimeExecutionTimer(acct);
		}
		else
		{
			/* The thread remains the same. We might need to update the execution timer.
			*/
			MK_UpdateExecutionTimeAlarm(acct);
		}
	}
	else
	{
		/* Thread has changed. If the outgoing thread is still RUNNING, set it to READY.
		*/
		if ( currThread->state == MK_THS_RUNNING )
		{
			MK_TRACE_STATE_THREAD(currThread->objectType, currThread->currentObject, currThread->name,
																				MK_THS_RUNNING, MK_THS_READY);
			currThread->state = MK_THS_READY;
		}

		/* Make the next thread into the core's current thread. The set or cancel the execution timer, as appropriate.
		*/
		coreVars->currentThread = nextThread;

		/* Change state of the selected thread to RUNNING
		*/
		MK_TRACE_STATE_THREAD(nextThread->objectType, nextThread->currentObject, nextThread->name,
																		nextThread->state, MK_THS_RUNNING);
		nextThread->state = MK_THS_RUNNING;

		/* If execution budgets are configured, start or cancel the timer, as appropriate.
		*/
		MK_PrimeExecutionTimer(acct);
	}

	MK_PrepareThreadForRunning(coreVars, nextThread);

	MK_HwResumeThread(coreVars, nextThread);		/* MK_HwResumeThread() never returns. */
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
