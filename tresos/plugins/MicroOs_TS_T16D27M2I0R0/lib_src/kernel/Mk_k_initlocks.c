/* Mk_k_initlocks.c
 *
 * This file contains the function MK_InitLocks().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_lock.h>
#include <private/Mk_panic.h>
#include <public/Mk_error.h>

/* MK_InitLocks() initializes the kernel's lock table.
 *
 * Only the locks on core 'coreIndex' are initialized.
 *
 * !LINKSTO Microkernel.Function.MK_InitLocks, 1
 * !doctype src
*/
void MK_InitLocks(mk_objectid_t coreIndex)
{
	mk_objectid_t i;
	mk_lock_t *lockTable = MK_lockTables[coreIndex];
	mk_objquantity_t nLocks = MK_nLocks[coreIndex];
	mk_objquantity_t lockIndex;

	for ( i = 0; i < MK_nLocksTotal; i++ )
	{
		lockIndex = MK_lockCfg[i].lockIndex;

		if ( (lockIndex < MK_nGlobalLocks) || (MK_lockCfg[i].coreIndex == coreIndex) )
		{
			if ( lockIndex < nLocks )
			{
				lockTable[lockIndex].cfg = MK_lockCfg[i].common;

#if MK_MAXCORES > 1
				MK_HwConfigureSpinlock(&lockTable[lockIndex], &MK_lockCfg[i]);
#endif
				lockTable[lockIndex].count = 0;
				lockTable[lockIndex].savedPrio = 0;
				lockTable[lockIndex].savedLevel = 0;
				lockTable[lockIndex].previousTaken = MK_NULL;
				lockTable[lockIndex].owner = MK_NULL;
			}
			else
			{
				/* Configuration error - index out of bounds
				*/
				MK_StartupPanic(MK_panic_InvalidLockConfiguration);
			}
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
