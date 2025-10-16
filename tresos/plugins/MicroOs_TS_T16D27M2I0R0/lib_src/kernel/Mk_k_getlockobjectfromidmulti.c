/* Mk_k_getlockobjectfromidmulti.c
 *
 * This file contains the function MK_GetLockObjectFromIdMulti()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_error.h>
#include <private/Mk_core.h>
#include <private/Mk_lock.h>

#if (MK_MAXCORES < 2)
#error "This file is not needed for single-core derivatives. Please check your makefiles."
#endif

/* MK_GetLockObjectFromIdMulti() is a helper function for MK_SysAcquireLock and MK_SysReleaseLock.
 *
 * Parameters:
 *	- coreVars: The kernel control object of the current core.
 *	- lockId:   The ID which determines the lock object.
 *	- pError:   If an error occurs the resp. value is written to this output variable
 *	            and the result of this function is NULL.
 *	            Otherwise, the referenced value stays unchanged.
 *
 * Return value:
 *	- lock:     A pointer to the lock or NULL if an error occurred.
 *
 * MK_GetLockObjectFromIdMulti() gets the actual lock object belonging to the given index.
 * If the index is invalid, this function returns MK_NULL and the error code is set accordingly.
 * If the index is valid, the error code stays unchanged.
 *
 * !LINKSTO Microkernel.Function.MK_GetLockObjectFromId, 1
*/
mk_lock_t *MK_GetLockObjectFromIdMulti(const mk_kernelcontrol_t *coreVars, mk_lockid_t lockId, mk_errorid_t *pError)
{
	mk_lock_t *lock = MK_NULL;
	mk_lockid_t lockIndex = MK_LockIdToIndex(lockId);

	/* On a multi-core system we need to look at the core index that is embedded in the lock ID,
	 * but only if the lock isn't one of the "global" locks that are present on all cores.
	*/
	if ( lockId < (mk_lockid_t) MK_nGlobalLocks )
	{
		lock = &MK_lockTables[coreVars->coreIndex][lockIndex];
	}
	else
	{
		if ( MK_LockIdToCoreIndex(lockId) == (mk_lockid_t) coreVars->coreIndex )
		{
			if ( lockIndex < (mk_lockid_t) MK_nLocks[coreVars->coreIndex] )
			{
				lock = &MK_lockTables[coreVars->coreIndex][lockIndex];
			}
			else
			{
				*pError = MK_eid_InvalidLockId;
			}
		}
		else
		{
			*pError = MK_eid_LockConfiguredForDifferentCore;
		}
	}

	return lock;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
