/* Mk_u_libgetappstateforctrsub.c
 *
 * This file contains the MK_GetAppStateForCtrSub() function.
 *
 * This function gets the state of the specified Os-Application, or APPLICATION_ACCESSIBLE if
 * the application is not valid.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>
#include <private/Mk_application.h>

/* MK_GetAppStateForCtrSub() - Gets the current state of the specified OS-Application.
 *
 * This function gets the state of the given application.
 * If an invalid application ID is passed,
 * this function will return APPLICATION_TERMINATED.
 * If MK_APPL_NONE is passed, this function will return APPLICATION_ACCESSIBLE.
 *
 * This implementation assumes that the application state can be read from any core
 * and in a single bus cycle to avoid an update occurring part-way through a read.
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_appstate_t MK_GetAppStateForCtrSub(mk_objectid_t appId)
{
	mk_appstate_t appState = APPLICATION_TERMINATED;

	if ((0 <= appId) && (appId < MK_nApps))
	{
		appState = MK_appCfg[appId].dynamic->appState;
	}
	else
	if (appId == MK_APPL_NONE)
	{
		appState = APPLICATION_ACCESSIBLE;
	}
	else
	{
		/* Application ID is invalid */
		appState = APPLICATION_TERMINATED;
	}
	return appState;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
