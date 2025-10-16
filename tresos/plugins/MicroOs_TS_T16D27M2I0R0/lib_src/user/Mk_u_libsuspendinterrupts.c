/* Mk_u_libsuspendinterrupts.c
 *
 * This file contains the MK_SuspendInterrupts function.
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
#include <private/Mk_lock.h>
#include <private/Mk_core.h>
#include <public/Mk_autosar.h>

/* MK_SuspendInterrupts()
 *
 * This function acquires the MK_resLockCat1 or MK_resLockCat2 lock, unless the
 * caller's queuing priority is higher than the lock's ceiling priority.
 *
 * !LINKSTO      Microkernel.Function.MK_SuspendInterrupts, 1
 * !doctype      src
*/
void MK_SuspendInterrupts(mk_lockid_t lockId)
{
	mk_lock_t *lockTable;
	mk_lock_t *lock;
	mk_objectid_t coreIndex = 0;

	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
	coreIndex = coreVars->coreIndex;

	lockTable = MK_lockTables[coreIndex];
	lock = &lockTable[lockId];

	if ( coreVars->currentThread->queueingPriority > lock->cfg.ceilingPriority )
	{
		/* Do nothing; caller is higher than the lock level.
		*/
	}
	else
	{
		(void)MK_UsrAcquireLock(lockId);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
