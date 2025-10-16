/* Mk_k_clearlocks.c
 *
 * This file contains the MK_ClearLocks() function.
 *
 * This function is called during shutdown, to release all locks held by the current core.
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

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_lock.h>


/* MK_ClearLocks() release all locks for the current core.
 *
 * !LINKSTO Microkernel.Function.MK_ClearLocks, 1
 * !doctype src
*/
void MK_ClearLocks(void)
{
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();
	mk_objectid_t coreIndex = coreVars->coreIndex;

	/* Release spinlock-components of all locks occupied by this core.
	*/
	MK_ClearSpinlocks(coreVars);

	/* Now completely re-initialize the lock structures.
	*/
	MK_InitLocks(coreIndex);
}


/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
