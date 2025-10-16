/* Mk_k_clearlocklist.c
 *
 * This file contains the function MK_ClearLockList()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_lock.h>

/* MK_ClearLockList() clears a list of locks
 *
 * It is used when a thread terminates/enters WAITING to free all the locks occupied by the thread.
 * The resources do not need to be released in the normal way, but the saved lock level of the
 * outermost lock is returned so the caller could release the IRQ lock.
 * However, the spinlocks need to be cleared within this function.
 *
 * !LINKSTO Microkernel.Function.MK_ClearLockList, 1
 * !doctype src
*/
mk_hwlocklevel_t MK_ClearLockList(mk_lock_t *headOfList)
{
	mk_lock_t *headOfListLocal = headOfList;
	mk_hwlocklevel_t savedLockLevel = MK_HWENABLEALLLEVEL;

	while ( headOfListLocal != MK_NULL )
	{
		/* Clear the unhooked lock.
		 * There's no need to clear the savedPrio and savedLevel fields, because
		 * they have no meaning if the lock is not occupied
		 * Leaving the owner field alone here means it indicates the last user of the lock.
		 * The previous taken (link pointer) is meaningless for an unoccupied lock, so isn't cleared
		 * This means we don't need a local variable for the lock-to-clear.
		*/
		headOfListLocal->count = 0;
		savedLockLevel = headOfListLocal->savedLevel;

#if MK_MAXCORES > 1
		/* If the lock has a spinlock variable the spinlock needs to be freed.
		*/
		if ( MK_HwLockHasSpinlock(headOfListLocal) )
		{
			MK_HwDropSpinlock(headOfListLocal->spinlock);
		}
#endif

		/* Unhook the first resource from the list
		*/
		headOfListLocal = headOfListLocal->previousTaken;
	}
	return savedLockLevel;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
