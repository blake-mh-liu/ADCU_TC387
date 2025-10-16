/* Mk_k_startupchecksynchere.c
 *
 * This file contains the MK_StartupCheckSyncHere() function.
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
#include <public/Mk_public_api.h>
#include <private/Mk_startup.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>


#if (MK_MAXCORES < 2)
#error "This file is not needed for single-core derivatives. Please check your makefiles."
#endif

/* MK_StartupCheckSyncHere
 *
 * Helper function for MK_Startup.
 * Check whether the sync-spot of the current core has been initialized correctly.
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_StartupCheckSyncHere(void)
{
	mk_objectid_t coreId = MK_HwGetCoreIndex();
	volatile mk_syncspot_t *mySyncSpot;

	mySyncSpot = MK_syncSpots[coreId];
	if (mySyncSpot == MK_NULL)
	{
		MK_StartupPanic(MK_panic_CoreNotConfigured);
	}
	if (*mySyncSpot != 0u)
	{
		MK_StartupPanic(MK_panic_SyncNotInitializedCorrectly);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
