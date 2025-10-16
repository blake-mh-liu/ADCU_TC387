/* Mk_k_sysreleaselock.c
 *
 * This file contains the MK_SysReleaseLock() function.
 *
 * This function is called by the system call function whenever the ReleaseLock system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 5.5 (required)
 * Identifiers shall be distinct from macro names.
 *
 * Reason:
 * For single-core derivatives, the function is replaced by an empty function like macro.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_LEVEL]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  This perfectly readalbe function uses an if-elseif-else-cascade to check for serveral
 *  errors and to select the proper action for releasing the lock.
 *  This leads to a high LEVEL value.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_lock.h>
#include <private/Mk_thread.h>
#include <private/Mk_errorhandling.h>

static void MK_LocalReleaseLock(mk_thread_t **, mk_thread_t *, mk_lock_t*);
#if MK_MAXCORES > 1
static void MK_CondDropSpinlock(mk_lock_t*);
#else
#define MK_CondDropSpinlock(lock)	do { } while (0)
#endif


/* MK_LocalReleaseLock() performs the final release of a lock
 *
 * Preconditions guaranteed by MK_SysReleaseLock():
 *	1. lock is occupied by current thread
 *	2. lock is occupied exactly once
 *	3. lock is the thread's most-recently-taken lock
 *
 * This function is present to reduce the size and complexity of the MK_SysReleaseLock().
 * With any luck the compiler will inline it anyway.
*/
static void MK_LocalReleaseLock(mk_thread_t **head, mk_thread_t *caller, mk_lock_t *lock)
{
	lock->count = 0;

	/* Restore current thread's lock status from the newly-released lock
	*/
	caller->currentPriority = lock->savedPrio;
	MK_HwSetIntLevel(caller->regs, lock->savedLevel);
	caller->lastLockTaken = lock->previousTaken;

	/* Set the newly-freed lock's owner to "none". This helps with debugging.
	*/
	lock->owner = MK_NULL;

	/* The priority of the current thread might have been reduced to a level below
	 * that of the next thread in the ready-queue. If so, the current thread must be
	 * dequeued and requeued further along the queue.
	 *
	 * Note: the "next-is-NULL" case only happens if the idle thread is using locks
	 * (including the interrupt disable services), or if the idle thread has terminated.
	*/
	if ( (caller->next == MK_NULL) ||
		 (caller->currentPriority >= caller->next->currentPriority) )
	{
		/* Requeue is not necessary; the thread remains at the head of the queue
		*/
	}
	else
	{
		/* Dequeue current thread.
		*/
		*head = caller->next;

		/* Requeue the current thread. Current thread remains in RUNNING
		 * state until dispatcher is called.
		 * The thread must be inserted AHEAD of other threads with the same priority,
		 * so MK_RequeueThread() is the correct function to use. The search can start
		 * at threadQueueHead->next because we already know that threadQueueHead has a higher priority.
		*/
		MK_RequeueThread(&(*head)->next, caller);
	}
}

#if MK_MAXCORES > 1
/* MK_CondDropSpinlock() drops the spinlock of the given lock, if it has one.
*/
/* Deviation MISRAC2012-1 <+1> */
static void MK_CondDropSpinlock(mk_lock_t *lock)
{
	if ( MK_HwLockHasSpinlock(lock) )
	{
		MK_HwDropSpinlock(lock->spinlock);
	}
}
#endif

/* MK_SysReleaseLock() releases the lock identified by the parameter.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "ReleaseLock" system call.
 *
 * !LINKSTO Microkernel.Function.MK_SysReleaseLock, 2
 * !doctype src
*/
/* Deviation DCG-1 <+1> */
void MK_SysReleaseLock(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	/* Intentional deviation from standard system call parameter handling.
	 * See ASCMICROOS-4019 for details.
	*/
	mk_lockid_t lockId = (mk_lockid_t)MK_HwGetParameter1(caller->regs);
	mk_lock_t *lock = MK_NULL;
	mk_errorid_t errorCode = MK_eid_Unknown;

	lock = MK_GetLockObjectFromId(coreVars, lockId, &errorCode);

	if ( lock != MK_NULL )
	{
		if ( lock->count <= 0 )
		{
			errorCode = MK_eid_LockNotOccupied;
		}
		else
		if ( lock->owner == caller )
		{
			if ( lock->count > 1 )
			{
				/* Lock has been taken more than once by current thread.
				 * Release a single acquisition.
				 * Note: 2nd and subsequent acquisitions of same lock can be
				 * taken and released in any order. The final release must be
				 * in LIFO order.
				*/
				lock->count--;
				errorCode = MK_eid_NoError;
			}
			else
			if ( caller->lastLockTaken == lock )
			{
				/* Lock becomes free.
				 * Drop the spinlock if there is one.
				*/
				MK_CondDropSpinlock(lock);
				MK_LocalReleaseLock(&coreVars->threadQueueHead, caller, lock);
				errorCode = MK_eid_NoError;
			}
			else
			{
				errorCode = MK_eid_LockReleaseSequenceError;
			}
		}
		else
		{
			errorCode = MK_eid_LockNotOccupiedByCaller;
		}
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_ReleaseLock, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
