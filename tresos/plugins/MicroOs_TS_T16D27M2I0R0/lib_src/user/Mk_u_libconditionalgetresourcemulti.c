/* Mk_u_libconditionalgetresourcemulti.c
 *
 * This file contains the multi-core implementation of MK_ConditionalGetResource().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_public_api.h>
#include <public/Mk_error.h>
#include <private/Mk_lock.h>
#include <private/Mk_thread.h>
#include <private/Mk_core.h>
#include <public/Mk_autosar.h>

/* MK_ConditionalGetResource()
 *
 * This function only gets the resource if the current priority of the
 * requesting thread is less than the ceiling priority of the resource.
 *
 * This function assumes global read-only access to the microkernel's variables.
 *
 * !LINKSTO      Microkernel.Function.ConditionalGetResource, 3
 * !doctype      src
*/
StatusType MK_ConditionalGetResource(mk_lockid_t lockId)
{
	StatusType errorCode = (StatusType)E_OS_NOFUNC;
	mk_lock_t *lockTable;
	mk_lock_t *lock;

	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
	mk_objectid_t coreIndex = coreVars->coreIndex;
	mk_lockid_t lockIndex = MK_LockIdToIndex(lockId);

	if ( (lockId < (mk_lockid_t) MK_nGlobalLocks) ||
		 ( (MK_LockIdToCoreIndex(lockId) == (mk_lockid_t) coreIndex) &&
		 (lockIndex < (mk_lockid_t) MK_nLocks[coreIndex]) ) )
	{
		/* Lock is in range and has presence on this core.
		*/
		lockTable = MK_lockTables[coreIndex];
		lock = &lockTable[lockIndex];

		if ( MK_HwLockHasSpinlock(lock) )
		{
			/* Spinlocks have to be handled by a system call
			*/
			errorCode = (StatusType)MK_UsrAcquireLock(lockId);
		}
		else
		if ( coreVars->currentThread->currentPriority < lock->cfg.ceilingPriority )
		{
			errorCode = (StatusType)MK_UsrAcquireLock(lockId);
		}
		else
		{
			errorCode = (StatusType)E_OS_NOFUNC;
		}
	}
	else
	{
		/* Out of range: let the normal system call handle this.
		*/
		errorCode = (StatusType)MK_UsrAcquireLock(lockId);
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
