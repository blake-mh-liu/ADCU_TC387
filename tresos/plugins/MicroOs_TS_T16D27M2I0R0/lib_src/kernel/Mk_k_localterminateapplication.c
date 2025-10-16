/* Mk_k_localterminateapplication.c
 *
 * This file contains the function MK_LocalTerminateApplication().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_errorhandling.h>

/* MK_LocalTerminateApplication() - terminates the given OS-Application
 *
 * The application id, the restart option and the permission to terminate have been verified by the caller.
 *
 * !LINKSTO Microkernel.Function.MK_LocalTerminateApplication, 2
 * !doctype src
*/
mk_errorid_t MK_LocalTerminateApplication
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t applicationId,
	mk_objectid_t callerApp,
	mk_boolean_t restart
)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	const mk_appcfg_t *appCfg = &MK_appCfg[applicationId];
	mk_appstate_t appState = appCfg->dynamic->appState;

	if ( appState == APPLICATION_ACCESSIBLE )
	{
		errorCode = MK_eid_NoError;
	}
	else
	if ( appState == APPLICATION_RESTARTING )
	{
		/* Restarting an application that's in the restarting state is harmless.
		 * The only problem is that if the requesting app is the same application but the
		 * application doesn't have a restart task. Then the internal state is inconsistent.
		*/
		if ( (callerApp == applicationId) && (appCfg->restartTask < 0) )
		{
			MK_Panic(MK_panic_ApplicationRunningWhileTerminated);
		}
		else
		{
			errorCode = MK_eid_NoError;
		}
	}
	else
	if ( appState == APPLICATION_TERMINATED )
	{
		/* Terminating an application that's already terminated is an error.
		 * If the requesting app is the same application the internal state is inconsistent.
		*/
		if ( callerApp == applicationId )
		{
			MK_Panic(MK_panic_ApplicationRunningWhileTerminated);
		}
		else
		{
			errorCode = MK_eid_Quarantined;
		}
	}
	else
	{
		/* Internal error: the application state is corrupt.
		*/
		MK_Panic(MK_panic_InvalidApplicationState);
	}

	if ( errorCode == MK_eid_NoError )
	{
		MK_TerminateApplication(coreVars, applicationId, restart);

		if ( restart )
		{
			MK_RestartApplication(coreVars, applicationId);
		}
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
