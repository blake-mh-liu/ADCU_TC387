/* Mk_k_initsynchere.c - initialize the core synchronization variables
 *
 * This file contains the MK_InitSyncHere() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_basic_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>

/* MK_InitSyncHere()
 *
 * This function initializes all the syncspots. It must be called from the primary core
 * before the other cores are set running.
 *
 * !LINKSTO Microkernel.Function.MK_InitSyncHere, 1
 * !doctype src
*/

MK_ATTR_NO_STACKPROT void MK_InitSyncHere(void)
{
	mk_objectid_t i;
	volatile mk_syncspot_t *syncSpot;

	for ( i = 0; i < (mk_objquantity_t)MK_MAXCORES; i++ )
	{
		syncSpot = MK_syncSpots[i];

		if ( syncSpot != MK_NULL )
		{
			*syncSpot = 0u;
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
