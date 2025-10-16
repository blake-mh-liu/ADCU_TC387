/* Mk_k_appstateok.c
 *
 * This file contains the MK_AppStateOk function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_application.h>

/*
 * MK_AppStateOk() determines whether the application state of application 'aId' allows
 *  that an object of application 'aId' may be accessed by application 'callerApp'.
 *
 * Objects can be accessed when they
 * - either don't belong to an OS-Application
 * - or belong to an OS-Application that is accessible
 * - or belong to an OS-application that is restarting and the caller belongs to the same app.
 *
 * !LINKSTO Microkernel.Function.MK_AppStateOk, 1
 * !doctype src
*/
mk_boolean_t MK_AppStateOk(mk_objectid_t aId, mk_objectid_t callerApp)
{
	mk_boolean_t appStateOK = MK_FALSE;

	if ( aId == MK_APPL_NONE )
	{
		/* No application - anyone can access the object.
		*/
		appStateOK = MK_TRUE;
	}
	else
	{
		mk_appstate_t appState = MK_appCfg[aId].dynamic->appState;

		if ( appState == APPLICATION_ACCESSIBLE )
		{
			/* Application is accessible - anyone can access the object.
			*/
			appStateOK = MK_TRUE;
		}
		else
		{
			if ( appState == APPLICATION_RESTARTING )
			{
				/* Application is restarting - only the owner can access the object.
				*/
				if ( aId == callerApp )
				{
					appStateOK = MK_TRUE;
				}
			}
		}
	}

	return appStateOK;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
