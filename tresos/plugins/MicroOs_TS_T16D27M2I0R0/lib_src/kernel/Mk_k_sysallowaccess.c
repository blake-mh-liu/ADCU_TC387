/* Mk_k_sysallowaccess.c
 *
 * This file contains the function MK_SysAllowAccess().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_syscall.h>
#include <private/Mk_errorhandling.h>
#include <public/Mk_autosar.h>

/* MK_SysAllowAccess() - sets the current OS-Application's state to APPLICATION_ACCESSIBLE.
 *
 * !LINKSTO Microkernel.Function.MK_SysAllowAccess, 1
 * !doctype src
*/
void MK_SysAllowAccess(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_objectid_t applicationId = caller->applicationId;
	mk_errorid_t errorCode = MK_eid_Unknown;

	if ( (applicationId >= 0) && (applicationId < MK_nApps) )
	{
		/* Trusted function threads no longer have an application ID.
		 * So any thread with a valid application ID is permitted to
		 * allow access to its application. The only check is that
		 * the application is in the RESTARTING state.
		*/
		if ( MK_appCfg[applicationId].dynamic->appState == APPLICATION_RESTARTING )
		{
			MK_appCfg[applicationId].dynamic->appState = APPLICATION_ACCESSIBLE;
			errorCode = MK_eid_NoError;
		}
		else
		{
			errorCode = MK_eid_AppNotRestarting;
		}
	}
	else
	{
		/* Caller doesn't belong to an application.
		*/
		errorCode = MK_eid_CallFromNonApplication;
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_AllowAccess, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
