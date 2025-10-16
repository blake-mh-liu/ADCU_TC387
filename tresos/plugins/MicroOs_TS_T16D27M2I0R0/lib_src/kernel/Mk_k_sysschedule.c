/* Mk_k_sysschedule.c
 *
 * This file contains the MK_SysSchedule() function.
 *
 * This function is called by the system call function whenever the Schedule system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_lock.h>
#include <private/Mk_errorhandling.h>

/*
 * MK_SysSchedule() yields non-preemptive status and internal resources to permit other threads to run.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "Schedule" system call.
 *
 * !LINKSTO Microkernel.Function.MK_SysSchedule, 1
 * !doctype src
*/
void MK_SysSchedule(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;
	mk_lock_t *lock;
	mk_threadprio_t lowPrio;

	if ( caller->next == MK_NULL )
	{
		/* This can only happen if Schedule() gets called from the lowest-priority thread!
		 * Normally that's the idle thread, so shouldn't happen. But we must cater for the
		 * unusual cases too.
		*/
	}
	else
	{
		/* Calculate the priority that the thread has to drop to.
		 * As basis, use the queueing priority.
		*/
		lowPrio = caller->queueingPriority;

		/* However, it should not drop lower than the highest lock taken, so
		 * walk the list of locks and adjust the priority to drop to.
		 *
		 * NOTE: AUTOSAR treats this as an error, but this kernel permits it.
		 * If no lock is occupied the runtime of the following code is minimal.
		 *
		 * The advantage of this is that the kernel behaves "as you would expect" even if
		 * the error-checking is disabled (i.e. threads that are configured to use the
		 * lock *still* cannot run --> no unexpected violations of critical sections.
		*/
		lock = caller->lastLockTaken;
		while ( lock != MK_NULL )
		{
			if ( lock->cfg.ceilingPriority > lowPrio )
			{
				lowPrio = lock->cfg.ceilingPriority;
			}
			lock = lock->previousTaken;
		}

		if ( caller->next->currentPriority > lowPrio )
		{
			/* Dequeue current thread from head of queue.
			*/
			coreVars->threadQueueHead = caller->next;

			/* Requeue current thread at the lower priority.
			 * The thread must be inserted AHEAD of other threads with the same priority,
			 * so MK_RequeueThread() is the correct function to use.
			 * The search can start at the second thread in the queue because it is already known
			 * that the head of queue has a higher priority.
			*/
			caller->currentPriority = lowPrio;
			MK_RequeueThread(&(coreVars->threadQueueHead->next), caller);
		}
		/* else ... (omitted)
		 * No higher-priority threads waiting.
		*/
	}

	/* No errors are detected so the return value is always E_OK.
	*/
	MK_HwSetReturnValue1(caller->regs, MK_E_OK);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
