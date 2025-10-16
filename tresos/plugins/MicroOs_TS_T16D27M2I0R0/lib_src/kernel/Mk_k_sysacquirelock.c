/* Mk_k_sysacquirelock.c
 *
 * This file contains the function MK_SysAcquireLock().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_lock.h>
#include <private/Mk_thread.h>
#include <private/Mk_errorhandling.h>


static void MK_LocalAcquireLock(mk_thread_t *, mk_lock_t*);

/* MK_LocalAcquireLock() performs the final acquisition of a lock
 *
 * Preconditions guaranteed by MK_SysAcquireLock():
 *	1. lock is not occupied
 *
 * This function is present to reduce the size and complexity of the MK_SysAcquireLock().
 * With any luck the compiler will inline it anyway.
*/
static void MK_LocalAcquireLock(mk_thread_t *caller, mk_lock_t *lock)
{
	/* Lock goes from free to occupied.
	*/
	lock->count = 1;

	/* Save current thread's lock status in the newly-occupied lock
	*/
	lock->savedPrio = caller->currentPriority;
	lock->savedLevel = MK_HwGetIntLevel(caller->regs);
	lock->previousTaken = caller->lastLockTaken;

	/* Set the current thread's lock status to the newly-occupied lock
	 * ensuring that priorities and levels don't decrease!
	*/
	lock->owner = caller;
	caller->lastLockTaken = lock;

	/* The lock level does not need to be considered here; if current priority
	 * is greater or equal to the ceiling priority, the lock level has already
	 * been set appropriately.
	*/
	if ( caller->currentPriority < lock->cfg.ceilingPriority )
	{
		/* No need to requeue here because the non-reentrant nature of the kernel
		 * guarantees that the current thread is at the head of the thread queue
		*/
		caller->currentPriority = lock->cfg.ceilingPriority;
		MK_HwSetIntLevel(caller->regs, lock->cfg.lockLevel);
	}
}

/* MK_SysAcquireLock() acquires the lock identified by the parameter.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * an "AcquireLock" system call.
 *
 * !LINKSTO Microkernel.Function.MK_SysAcquireLock, 2
 * !doctype src
*/
void MK_SysAcquireLock(mk_kernelcontrol_t *coreVars)
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
		if ( lock->count == 0 )
		{
			/* This is an "OK" branch.
			*/

#if MK_MAXCORES > 1
			/* If the lock has a spinlock associated with it, we need to acquire the spinlock first.
			 * if that fails the lock does not get taken, and the service returns "try again".
			*/
			if ( MK_HwLockHasSpinlock(lock) )
			{
				if ( MK_HwTrySpinlock(lock->spinlock) )
				{
					/* Got the spinlock; now occupy the lock.
					*/
					errorCode = MK_eid_NoError;
					MK_LocalAcquireLock(caller, lock);
				}
				else
				{
					/* Spinlock is occupied. We need to try again.
					*/
					errorCode = MK_eid_TryAgain;
				}
			}
			else
			{
				/* No spinlock. Just occupy the lock.
				*/
				errorCode = MK_eid_NoError;
				MK_LocalAcquireLock(caller, lock);
			}
#else
			errorCode = MK_eid_NoError;
			MK_LocalAcquireLock(caller, lock);
#endif
		}
		else
		if ( lock->owner == caller )
		{
			/* Lock is already occupied by the caller. Increase the nesting count
			 * unless it has already hit the maximum.
			*/
			if ( lock->count < lock->cfg.maxCount )
			{
				/* This is an "OK" branch.
				*/
				errorCode = MK_eid_NoError;

				lock->count++;
			}
			else
			{
				errorCode = MK_eid_LockNestingLimitExceeded;
			}
		}
		else
		{
			errorCode = MK_eid_LockAlreadyOccupied;
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
		osekError = MK_InternReportError(coreVars, MK_sid_AcquireLock, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
