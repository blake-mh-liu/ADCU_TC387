/* Mk_u_libgetapplicationstate.c
 *
 * This file contains the GetApplicationState() function.
 *
 * This function gets the state of the specified OS-application.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>
#include <private/Mk_application.h>

/* GetApplicationState() - Gets the current state of the specified OS-Application.
 *
 * This implementation assumes that the application state can be read from any core
 * and in a single bus cycle to avoid an update occurring part-way through a read.
 *
 * !LINKSTO      Microkernel.Function.GetApplicationState, 2
 * !doctype      src
*/
StatusType GetApplicationState(ApplicationType app, ApplicationStateRefType pState)
{
	StatusType returnVal = MK_E_ERROR;

	if ( (app >= 0) && (app < MK_nApps) )
	{
		*pState = MK_appCfg[app].dynamic->appState;
		returnVal = MK_E_OK;
	}
	else
	{
		returnVal = (StatusType)MK_ReportError(MK_sid_GetApplicationState, MK_eid_InvalidOsApplication,
														(mk_parametertype_t)app, (mk_parametertype_t)pState);
	}

	return returnVal;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
