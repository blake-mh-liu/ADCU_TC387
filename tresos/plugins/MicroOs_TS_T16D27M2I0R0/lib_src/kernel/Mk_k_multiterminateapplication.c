/* Mk_k_multiterminateapplication.c
 *
 * This file contains the MK_MultiTerminateApplication() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * Boolean type value needs to be stored in fixed length type for cross core messaging.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_application.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_message.h>

#if MK_MAXCORES <= 1
#error "This file is not needed for single-core systems."
#endif

/*
 * MK_MultiTerminateApplication() terminates an application.
 *
 * This function is called on multi-core systems to terminate an application on any core.
 * The application ID is assumed to have been previously validated.
 *
 * !LINKSTO Microkernel.Function.MK_MultiTerminateApplication, 2
 * !doctype src
*/
mk_errorid_t MK_MultiTerminateApplication
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t applicationId,
	mk_objectid_t callerApp,
	mk_boolean_t restart
)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	const mk_appcfg_t *appCfg = &MK_appCfg[applicationId];
	mk_parametertype_t p[MK_MSG_MAXPARAM];
	mk_objectid_t appCore;
	mk_thread_t *caller;

	appCore = appCfg->coreIndex;

	if ( appCore == coreVars->coreIndex )
	{
		errorCode = MK_LocalTerminateApplication(coreVars, applicationId, callerApp, restart);
	}
	else
	{
		p[0] = (mk_parametertype_t)applicationId;
		/* Deviation MISRAC2012-1 <+1> */
		p[1] = (mk_parametertype_t)restart;
		p[2] = 0;
		p[3] = 0;

		errorCode = MK_SendMessage(coreVars, appCore, MK_xcore_TerminateApplication, MK_NULLCOOKIE, p);

		if ( errorCode == MK_eid_NoError )
		{
			/* Set up the mechanism for waiting for and receiving the reply.
			*/
			caller = coreVars->currentThread;
			caller->xcoreReply.statusCode = MK_E_WAITFORREPLY;
			caller->xcoreReply.requestedValue = MK_WAITCOOKIE(coreVars->cookieGen, appCore);
			errorCode = MK_eid_WaitForReply;
		}
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
