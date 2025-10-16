/* Mk_k_synchere.c - synchronization of 2 or more cores during startup
 *
 * This file contains the MK_SyncHere() function
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

#include <public/Mk_basic_types.h>
#include <private/Mk_core.h>

/* MK_SyncHere()
 *
 * This function performs barrier-style synchronization for all cores.
 *
 *
 * Assumptions:
 *  The sync spots (referenced by MK_syncSpots) have to be initialized to 0, before any core enters MK_SyncHere.
 *    This is checked in MK_Startup, where each core checks that its sync spot is 0
 *    before calling MK_SyncHere for the first time.
 *
 * How it works:
 *
 * Every core "owns" one element of the MK_syncSpots array and is the only one writing
 * to this element. At the beginning of the function, each core increments his
 * array element. Then it repeatedly checks if the other cores have done the same
 * by looking at their values in turn.
 *
 * When all cores have incremented their elements, all cores will recognize this
 * within the next iteration of the check loop. Then all cores proceed further.
 *
 * The sync spots must all be initialized to zero before any calls to MK_SyncHere.
 * This is done on the primary core in early initialization before starting the other cores.
 *
 * !LINKSTO Microkernel.Function.MK_SyncHere, 1
 * !doctype src
*/

static mk_syncspot_t MK_SyncLoad(volatile mk_syncspot_t *);
static void MK_SyncStore(volatile mk_syncspot_t *, mk_syncspot_t);

static mk_syncspot_t MK_SyncLoad(volatile mk_syncspot_t *pspot)
{
	MK_HwCacheInvalidate(pspot, sizeof(mk_syncspot_t));
	return *pspot;
}
static void MK_SyncStore(volatile mk_syncspot_t *pspot, mk_syncspot_t val)
{
	*pspot = val;
	MK_HwCacheFlush(pspot, sizeof(mk_syncspot_t));
}

/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_SyncHere(void)
{
	mk_objectid_t coreIndex;
	mk_syncspot_t thisSync;
	volatile mk_syncspot_t *mySyncSpot;
	volatile mk_syncspot_t *syncSpot;
	mk_objquantity_t nExpected;
	mk_objquantity_t nReached;

	coreIndex = MK_HwGetCoreIndex();
	mySyncSpot = MK_syncSpots[coreIndex];

	if ( mySyncSpot == MK_NULL )
	{
		MK_StartupPanic(MK_panic_CoreNotConfigured);
	}

	/* Calculate how many cores are expected to reach the synchronization point.
	*/
	nExpected = 0;
	for ( coreIndex = 0; coreIndex < (mk_objquantity_t)MK_MAXCORES; coreIndex++ )
	{
		if ( MK_syncSpots[coreIndex] != MK_NULL )
		{
			nExpected++;
		}
	}

	/* Signal own presence.
	*/
	thisSync = (mk_syncspot_t)(MK_SyncLoad(mySyncSpot) + 1u);
	MK_SyncStore(mySyncSpot, thisSync);		/* I'm here! */

	do
	{
		/* Core waits here until all cores have arrived here.
		*/
		nReached = 0;

		MK_SyncStore(mySyncSpot, thisSync);		/* I'm still here! */

		for ( coreIndex = 0; coreIndex < (mk_objquantity_t)MK_MAXCORES; coreIndex++ )
		{
			syncSpot = MK_syncSpots[coreIndex];
			if ( syncSpot != MK_NULL )
			{
				/* Test for greater or equal rather than greater, because other cores might have
				 * advanced to the next sync point while we were waiting. This happens mainly on
				 * emulators.
				*/
				if ( MK_SyncLoad(syncSpot) >= thisSync )
				{
					nReached++;
				}
			}
		}
	} while ( nReached != nExpected );
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
