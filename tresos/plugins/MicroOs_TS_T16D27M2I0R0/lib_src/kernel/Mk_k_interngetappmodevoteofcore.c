/* Mk_k_interngetappmodevoteofcore.c
 *
 * This file contains the function MK_InternGetAppModeVoteOfCore().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>

/* MK_InternGetAppModeVoteOfCore() - returns the app mode of the given core.
 *
 * !LINKSTO Microkernel.Function.MK_InternGetAppModeVoteOfCore, 2
 * !doctype src
*/
mk_appmodeid_t MK_InternGetAppModeVoteOfCore(mk_objectid_t coreId)
{
	mk_appmodeid_t appMode = MK_UNINITIALIZED_APPMODE;

	if (MK_LibIsCoreInUse(MK_GetLogicalCoreId(coreId)))
	{
		mk_appmodeid_t const *pAppMode;
		pAppMode = &(MK_coreTable[coreId]->ctrsubAppMode);
		MK_HwCacheInvalidate(pAppMode, sizeof(mk_appmodeid_t));
		appMode = *pAppMode;
	}

	return appMode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
