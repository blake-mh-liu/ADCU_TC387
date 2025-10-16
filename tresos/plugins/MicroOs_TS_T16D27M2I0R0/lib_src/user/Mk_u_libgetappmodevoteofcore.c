/* Mk_u_libgetappmodevoteofcore.c
 *
 * This file contains the MK_LibGetAppModeVoteOfCore() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>

#if (MK_CACHEOP_PRIVILEGE == MK_CACHEOP_USER)
#define MK_GetAppModeVoteOfCoreCacheOp(coreId)	MK_InternGetAppModeVoteOfCore(coreId)
#elif (MK_CACHEOP_PRIVILEGE == MK_CACHEOP_SUPERVISOR)
#define MK_GetAppModeVoteOfCoreCacheOp(coreId)	MK_GetAppModeVoteOfCore(coreId)
#else
#error "MK_CACHEOP_PRIVILEGE has an invalid value."
#endif

/* MK_LibGetAppModeVoteOfCore() - Gets the OsAppMode, for which the given core votes.
 *
 * This function gets the OsAppMode, for which the given core votes.
 * This might be MK_UNINITIALIZED_APPMODE, if the given core hasn't yet
 * suggested an application mode.
 * If the given logical core index is invalid, this function will also return
 * MK_UNINITIALIZED_APPMODE.
 * If the platform/derivative supports cache operations in user mode, it
 * retrieves the value directly. Otherwise, it delegates the request to the
 * system call MK_GetAppModeVoteOfCore().
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_appmodeid_t MK_LibGetAppModeVoteOfCore(mk_objectid_t coreId)
{
	mk_appmodeid_t appMode;
	mk_objectid_t coreIdPhy = MK_GetPhysicalCoreId(coreId);

	appMode = MK_GetAppModeVoteOfCoreCacheOp(coreIdPhy);

	return appMode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
