/* Mk_k_startupinitdatasectionsmulti.c
 *
 * This file contains the MK_StartupInitDataSectionsMulti() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: NoSideEffectsInSizeOfParam
 *   Side effects not allowed in operand of sizeof operator
 *
 * Reason: This is a false positive that sometimes gets generated when
 * dereferencing a pointer to a volatile variable given as a parameter to
 * sizeof. Since sizeof only looks at the type of the expression, this is not
 * an issue.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_startup.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>


#if (MK_MAXCORES < 2)
#error "This file is not needed for single-core derivatives. Please check your makefiles."
#endif


/* MK_StartupInitDataSectionsMulti
 *
 * This is a helper function for MK_Startup.
 * This function initializes the data (and bss) sections by calling MK_InitDataSections.
 * Moreover it takes care of synchronization and synchronization variables.
 *
 * The master core initializes MK_startupControl to MK_MAXCORES before the synchronization
 * point. After the synchronization point, all slave cores wait until released by the
 * master.
 *
 * Note: the variable MK_startupControl lies in .bss so gets set to zero by the
 * data initialization. The slave cores continue to wait.
 * Note: the sync-spots used by MK_SyncHere also get set to zero by the data initialization.
 * We don't care.
 *
 * !LINKSTO Microkernel.Function.MK_StartupInitDataSectionsMulti, 1
*/
void MK_StartupInitDataSectionsMulti(void)
{
	mk_syncspot_t syncValue;
	mk_objectid_t coreId = MK_HwGetCoreIndex();

	if ( coreId == MK_hwMasterCoreIndex )
	{
		MK_startupControl = MK_MAXCORES;

		MK_SyncHere();

		syncValue = *MK_syncSpots[coreId];

		/* MK_startupControl and all the sync-spots on this core will get set to zero by MK_InitDataSections.
		*/
		MK_InitDataSections();

		*MK_syncSpots[coreId] = syncValue;
		MK_HwCacheFlush(MK_syncSpots[coreId], sizeof(mk_syncspot_t));

		/* Release the other cores, then wait until they all get here.
		*/
		MK_startupControl = MK_MAXCORES + 1;
		MK_HwCacheFlush(&MK_startupControl, sizeof(MK_startupControl));
	}
	else
	{
		MK_SyncHere();

		syncValue = *MK_syncSpots[coreId];

		/* All the sync-spots on this core will get set to zero by MK_InitDataSections.
		*/
		MK_InitDataSections();

		*MK_syncSpots[coreId] = syncValue;
		MK_HwCacheFlush(MK_syncSpots[coreId], sizeof(mk_syncspot_t));

		do
		{
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			MK_HwCacheInvalidate(&MK_startupControl, sizeof(MK_startupControl));
		} while ( MK_startupControl <= MK_MAXCORES );
	}

	/* Wait until all cores are done initializing their memory regions.
	*/
	MK_SyncHere();
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
