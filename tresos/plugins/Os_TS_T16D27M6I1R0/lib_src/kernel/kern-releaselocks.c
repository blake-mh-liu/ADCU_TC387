/* kern-releaselocks.c
 *
 * This file contains the function OS_ReleaseLocks().
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#if (OS_N_CORES > 1u)
#include <Os_spinlock.h>
#endif

/* OS_ReleaseLocks() releases all locks headed by the lock whose ID is given as parameter
 *
 * On single-core systems, the only locks are resources, so a lock ID is simply a resource ID.
 * On multicore systems there are resources and spinlocks. The lock ID identifies the type as well as
 * the ID of the spinlock or resource.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ReleaseLocks(os_objectid_t head)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_objectid_t lock = head;

	while (lock != OS_NULLOBJECT)
	{
#if (OS_N_CORES > 1)
		/* COVPT-1 */
		if (OS_GetTypeFromObjectId(lock) == OS_OBJ_SPINLOCK)
		{
			os_autosarspinlockdyn_t * const sld = OS_autosarSpinlockTableBase[OS_GetIdFromObjectId(lock)].dynamic;

			os_intstatus_t is = OS_TakeInternalLock(OS_SOFTWARELOCK_LOCKID);

			lock = sld->predecessor;
			sld->predecessor = OS_NULLOBJECT;
			sld->ownerCore = OS_CORE_ID_INVALID;
			sld->ownerType = OS_OBJ_NONE;
			sld->ownerId = OS_NULLOBJECT;
			OS_CacheFlush(sld, sizeof(os_autosarspinlockdyn_t));

			OS_DropInternalLock(OS_SOFTWARELOCK_LOCKID, is);
		}
		else
#endif
		{
			/* rd could (should?) be const, but due to a bug in WindRiver Data Diab 5.9.3.1,
			 * this leads to wrong array/structure-access code.
			 */
			os_resourcedynamic_t * rd = OS_ResourceGetDynamic(OS_GetIdFromObjectId(lock));

			lock = rd->next;

			rd->next = OS_NULLOBJECT;
			rd->takenBy = OS_NULLTASK;
			rd->lastPrio = 0;
		}
	}
}

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_releaselocks_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
