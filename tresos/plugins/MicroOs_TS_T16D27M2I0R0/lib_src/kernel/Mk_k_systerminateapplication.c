/* Mk_k_systerminateapplication.c
 *
 * This file contains the function MK_SysTerminateApplication().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * The system call mechanism translates parameters to fixed length type based on register size.
 * The service handler then needs to translate them back.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_syscall.h>

static mk_errorid_t MK_CheckTermAppConditions(mk_parametertype_t, mk_thread_t *, mk_parametertype_t);

/* MK_CheckTermAppConditions - Check (error) conditions for MK_TerminateApplication
 *
 * Returns MK_eid_NoError if all conditions are met to execute MK_TerminateApplication,
 * or an appropriate error code otherwise.
*/
static mk_errorid_t MK_CheckTermAppConditions
(
	mk_parametertype_t targetAppId,
	mk_thread_t *caller,
	mk_parametertype_t restart
)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_objectid_t callerAppId = caller->applicationId;

	/* Range-check the terminated OS-Application's Id.
	 * Explicit cast to prevent compiler warning (ok, as the number of applications is always
	 * >= 0).
	*/
	if ( targetAppId >= (mk_parametertype_t)MK_nApps )
	{
		errorCode = MK_eid_InvalidOsApplication;
	}
	/* Range-check the restart parameter.
	*/
	else
	if ( ((mk_int_t)restart != MK_TRUE) && ((mk_int_t)restart != MK_FALSE) )
	{
		errorCode = MK_eid_InvalidRestartParameter;
	}
	/* Check for permission.
	*/
	else
	if (caller->objectType == MK_OBJTYPE_PROTECTIONHOOK)
	{
		errorCode = MK_eid_NoError;
	}
	else
	if ( (callerAppId < 0) || (callerAppId >= MK_nApps) )
	{
		errorCode = MK_eid_CallFromNonApplication;
	}
	else
	{
		const mk_appcfg_t *callerApp = &MK_appCfg[callerAppId];
		mk_accessingapp_t permWord = MK_appCfg[targetAppId].accessingApps[callerApp->accessAppIndex];

		if ( (permWord & callerApp->accessAppMask) == 0u )
		{
			errorCode = MK_eid_WithoutPermission;
		}
		else
		{
			errorCode = MK_eid_NoError;
		}
	}

	return errorCode;
}

/* MK_SysTerminateApplication() - terminates the given OS-Application
 *
 * This function does range and permission checking.
 * If the checks are successful, the work is delegated to MK_InternTerminateApplication()
 *
 * !LINKSTO Microkernel.Function.MK_SysTerminateApplication, 2
 * !doctype src
*/
void MK_SysTerminateApplication(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t applicationId = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_parametertype_t restart = MK_ELIMINATE_UNDEFINED_BITS(mk_boolean_t, MK_HwGetParameter2(caller->regs));
	mk_objectid_t callerAppId = caller->applicationId;
	mk_errorid_t errorCode;

	errorCode = MK_CheckTermAppConditions(applicationId, caller, restart);

	if ( errorCode == MK_eid_NoError )
	{
		/* Deviation MISRAC2012-1 <+5> */
		errorCode = MK_InternTerminateApplication( coreVars,
												   (mk_objectid_t)applicationId,
												   callerAppId,
												   (mk_boolean_t)restart
												 );
	}

	if ( errorCode == MK_eid_NoError )
	{
		/* Only report E_OK if the caller didn't terminate itself.
		*/
		if ( (mk_objectid_t)applicationId != callerAppId )
		{
			MK_HwSetReturnValue1(caller->regs, MK_E_OK);
		}
	}
	else
	if ( errorCode < MK_eid_FirstError  )
	{
		/* Not a real error; just return the StatusType equivalent.
		 * Caller has not been terminated.
		*/
		MK_HwSetReturnValue1(caller->regs, MK_ErrorInternalToOsek(errorCode));
	}
	else
	{
		/* A real error. Caller has not been terminated.
		*/
		MK_HwSetReturnValue1(caller->regs,
							MK_InternReportError(coreVars, MK_sid_TerminateApplication, errorCode, caller, MK_NULL));
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
