/* Mk_k_clearspinlocks.c
 *
 * This file contains the MK_ClearSpinlocks() function.
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
 *
 *
 * MISRAC2012-2) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * For single-core derivatives, the function is replaced by an empty function like macro.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_lock.h>

#if (MK_MAXCORES < 2)
#error "This file is not needed for single-core derivatives. Please check your makefiles."
#endif

/* MK_ClearSpinlocks() releases the spinlock-components of all locks of the given core.
 *
 * MK_ClearSpinlocks() is a helper function of MK_ClearLocks().
 *
 * !LINKSTO Microkernel.Function.MK_ClearLocks, 1
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_ClearSpinlocks(const mk_kernelcontrol_t *coreVars)
{
	mk_objectid_t coreIndex = coreVars->coreIndex;
	mk_lock_t *lockTable = MK_lockTables[coreIndex];
	mk_objectid_t i;

	/* Release spinlock-components of all locks occupied by this core.
	*/
	for ( i = 0; i < MK_nLocksTotal; i++ )
	{
		mk_objquantity_t lockIndex = MK_lockCfg[i].lockIndex;
		mk_lock_t *lock = &lockTable[lockIndex];

		/* Only global locks can have spinlock components
		*/
		if ( (lockIndex < MK_nGlobalLocks) && (MK_lockCfg[i].coreIndex == coreIndex) )
		{
			/* Reinitialize the RAM copy of the inter-core part of the lock configuration,
			 * in case it got corrupted.
			*/
			MK_HwConfigureSpinlock(lock, &MK_lockCfg[i]);

			/* Now, if the lock has a spinlock and is occupied, release the spinlock-component.
			*/
			if ( MK_HwLockHasSpinlock(lock) && (lock->owner != MK_NULL) )
			{
				MK_HwDropSpinlock(lock->spinlock);
			}
		}
	}
}


/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
