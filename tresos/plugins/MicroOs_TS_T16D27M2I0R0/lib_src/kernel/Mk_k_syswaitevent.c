/* Mk_k_syswaitevent.c
 *
 * This file contains the MK_SysWaitEvent() function.
 *
 * This function is called by the system call function whenever the WaitEvent system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_VOCF]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  Parts of this function look repetitive or similar because of the necessary sanity checks,
 *  the error reporting, and the different scenarios which have to be considered. Splitting up
 *  these parts into separate functions would not improve maintainability,
 *  because they form a logical unit with the rest of the code.
 *
 *
 * DCG-2) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
*/

#include <Mk_kconfig.h>
#include <public/Mk_public_types.h>
#include <public/Mk_syscallindex.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>

/*
 * MK_SysWaitEvent() places the current thread's EXTENDED task into the WAITING state.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "WaitEvent" system call.
 *
 * !LINKSTO Microkernel.Function.MK_SysWaitEvent, 1
 * !doctype src
*/
/* Deviation DCG-1 <+1>, DCG-2 <+1> */
void MK_SysWaitEvent(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_eventmask_t eventsAwaited;
	mk_eventstatus_t *eventStatus;
	mk_unsigned_t syscallIndex = (mk_unsigned_t)MK_HwGetSyscallIndex(caller->regs);

	mk_errorid_t errorCode = MK_eid_Unknown;

	if ( caller->objectType == MK_OBJTYPE_TASK )
	{
		eventStatus = MK_taskCfg[caller->currentObject].eventStatus;

		if ( eventStatus == MK_NULL )
		{
			errorCode = MK_eid_TaskIsNotExtended;
		}
		else
		{
			errorCode = MK_eid_NoError;

			/* Refill the execution time budget to its full extent,
			 * if there is a time budget imposed on this thread.
			*/
			if (caller->accounting.acctCfg != MK_NULL)
			{
				caller->accounting.timeRemaining = caller->accounting.acctCfg->execBudget;
			}

			eventsAwaited = (mk_eventmask_t)MK_HwGetParameter1(caller->regs);

			/* Preload an E_OK return value for the task that (might) wait.
			 * At the end of the function it is too late; a new task might already be
			 * sitting in the current thread. This comes *after" reading eventAwaited in
			 * case the 1st parameter and the return value use the same register.
			*/
			MK_HwSetReturnValue1(caller->regs, MK_E_OK);

			if ( (eventsAwaited == 0u) ||
				 ((eventStatus->pendingEvents & eventsAwaited) != 0u) )
			{
				/* Simply return with E_OK.
				 *
				 * The "eventsAwaited == 0" case for WaitEvent is really an error, but
				 * AUTOSAR has no requirement to detect and report it. Simply handling
				 * the request just like normal would result in the task getting into a
				 * strange "zombie" state.
				 *
				 * In the second case of the decision an awaited event is already set.
				*/
				if ( syscallIndex == MK_SC_WaitGetClearEvent )
				{
					/* If the system call was the WaitGetClear variant, we return (and clear)
					 * the pending events. This has an interesting side effect; WaitGetClearEvent(0) can
					 * be used as a combined Get/Clear without waiting :-)
					*/
					MK_HwSetReturnValue2(caller->regs, eventStatus->pendingEvents);
					eventStatus->pendingEvents = 0;
				}

				/* The state of this thread is changed to NEW to tell the dispatcher
				 * to prime the execution time monitoring for it again. This makes
				 * the refilling of the execution time budget above finally taking
				 * effect.
				*/
				MK_TRACE_STATE_THREAD(caller->objectType, caller->currentObject,
					caller->name, caller->state, MK_THS_NEW);
				caller->state = MK_THS_NEW;
			}
			else
			{
				/* None of the awaited events is already pending.
				 * The task enters the WAITING state.
				*/
				eventStatus->awaitedEvents = eventsAwaited;

				/* Place the task into one of the possible  WAITING states.
				*/
				if ( syscallIndex == MK_SC_WaitGetClearEvent )
				{
					eventStatus->waitingState = MK_WAITGETCLEAR;
				}
				else
				{
					eventStatus->waitingState = MK_WAIT;
				}

				/* Dequeue the current thread from the head of the thread queue.
				 * (Precondition for MK_TerminateThread())
				*/
				coreVars->threadQueueHead = caller->next;
				caller->next = MK_NULL;

				/* Terminate the thread
				 *
				 * Note: do not free thread registers (which currently point to task registers)
				 * because although the thread gets terminated the task does not.
				 * MK_TerminateThread() never sees the lock level in this case, so a dummy value is passed.
				*/
				MK_TerminateThread(coreVars, caller, 0);

				/* A thread has been terminated. If there are no more threads the problem needs
				 * to be handled.
				*/
				if ( coreVars->threadQueueHead == MK_NULL )
				{
					MK_ThreadQueueEmpty();
				}
			}
		}
	}
	else
	{
		errorCode = MK_eid_ThreadIsNotATask;
	}

	if ( errorCode == MK_eid_NoError )
	{
		/* E_OK is not reported here because the current thread might no longer contain the calling task!
		 * The value was placed in the register store before terminating the thread.
		*/
	}
	else
	{
		if ( syscallIndex == MK_SC_WaitGetClearEvent )
		{
			osekError = MK_InternReportError(coreVars, MK_sid_WaitGetClearEvent, errorCode, caller, MK_NULL);
		}
		else
		{
			osekError = MK_InternReportError(coreVars, MK_sid_WaitEvent, errorCode, caller, MK_NULL);
		}

		MK_HwSetReturnValue1(caller->regs, osekError);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
