/* Mk_k_internreporterror.c
 *
 * This file contains the function MK_InternReportError().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 *  A project shall not contain unreachable code.
 *
 * Reason:
 *  Depending on the architecture, MK_HwIsRegisterStoreValid always evaluates to MK_TRUE.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_message.h>

#if MK_MAXPARAMS != 4
#error "The handling of parameter lists in this file needs attention"
#endif

/* Helper functions to initialize an array of parameters
 *
 * The name suffix on MK_LoadParams_Intern avoids a MISRA violation; there's an identical function in another file.
 * The function is defined locally to encourage the compiler to inline it.
*/
static void MK_InvalidateParams(mk_parametertype_t p[4])
{
	p[0] = MK_PARAMETERTYPE_INVALID;
	p[1] = MK_PARAMETERTYPE_INVALID;
	p[2] = MK_PARAMETERTYPE_INVALID;
	p[3] = MK_PARAMETERTYPE_INVALID;
}

static void MK_LoadParams_Intern(mk_parametertype_t p[MK_MAXPARAMS], mk_thread_t *thr)
{
	p[0] = MK_HwGetParameter1(thr->regs);
	p[1] = MK_HwGetParameter2(thr->regs);
	p[2] = MK_HwGetParameter3(thr->regs);
	p[3] = MK_HwGetParameter4(thr->regs);
}

/* MK_FillErrorInfo() - place error information into the MK_errorInfo structure.
 *
 * Everything we know about the error is stored into the global error-info structure.
 *
 * The "culprit" thread is not guaranteed to be valid after the error hook terminates
 * but is stored for debugging purposes.
*/
static mk_osekerror_t MK_FillErrorInfo
(	mk_errorinfo_t *errorInfo,
	mk_serviceid_t sid,
	mk_errorid_t eid,
	mk_thread_t *culprit,		/* Optional: the culprit thread */
	mk_parametertype_t *p		/* Optional: an array of 4 parameters */
)
{
	mk_osekerror_t osekError = MK_ErrorInternalToOsek(eid);

	errorInfo->serviceId = sid;
	errorInfo->errorId = eid;
	errorInfo->osekError = osekError;
	errorInfo->culprit = culprit;

	if ( p == MK_NULL )
	{
		if ( culprit == MK_NULL )
		{
			MK_InvalidateParams(errorInfo->parameter);
		}
		else
		/* Deviation MISRAC2012-1 <+1> */
		if ( MK_HwIsRegisterStoreValid(culprit->regs) )
		{
			MK_LoadParams_Intern(errorInfo->parameter, culprit);
		}
		else
		{
			MK_InvalidateParams(errorInfo->parameter);
		}
	}
	else
	{
		errorInfo->parameter[0] = p[0];
		errorInfo->parameter[1] = p[1];
		errorInfo->parameter[2] = p[2];
		errorInfo->parameter[3] = p[3];
	}

	if ( culprit == MK_NULL )
	{
		errorInfo->culpritId = MK_OBJECTID_INVALID;
		errorInfo->culpritType = MK_OBJTYPE_UNKNOWN;
		errorInfo->culpritName = MK_NULL;
	}
	else
	{
		errorInfo->culpritId = culprit->currentObject;
		errorInfo->culpritType = culprit->objectType;
		errorInfo->culpritName = culprit->name;
	}

	return osekError;
}

/* MK_InternReportError() - report an error
 *
 * An error is reported by some combination (depending on configuration) of
 * - filling the MK_errorInfo structure
 * - calling (starting a thread for) the ErrorHook() function
 * - passing the AUTOSAR error code back to the caller
 *
 * Parameters for the MK_errorInfo structure are taken from the parameter array if supplied,
 * otherwise from the culprit's registers. If neither is provided the parameters are filled with INVALID
 *
 * !LINKSTO Microkernel.Function.MK_InternReportError, 2
 * !doctype src
*/
mk_osekerror_t MK_InternReportError
(	mk_kernelcontrol_t *coreVars,
	mk_serviceid_t sid,
	mk_errorid_t eid,
	mk_thread_t *culprit,		/* Optional: the culprit thread */
	mk_parametertype_t *p		/* Optional: an array of 4 parameters */
)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *errorHookThread = MK_errorHookThread[coreVars->coreIndex];
	const mk_threadcfg_t *errorHookThreadConfig = MK_errorHookThreadConfig[coreVars->coreIndex];

	if ( errorHookThread == MK_NULL )
	{
		/* No error-hook thread is configured. Just record the error in the error-info structure
		 * and return the error code.
		*/
		osekError = MK_FillErrorInfo(MK_errorInfo[coreVars->coreIndex], sid, eid, culprit, p);
	}
	else
	if  ( errorHookThread->state == MK_THS_IDLE )
	{
		osekError = MK_FillErrorInfo(MK_errorInfo[coreVars->coreIndex], sid, eid, culprit, p);

		/* Error-hook thread is idle. We can start the thread provided it will preempt the current
		 * thread. In case the culprit is the ProtectionHookThread, this is not the case.
		 * In any case we can record the error in the error-info structure.
		*/
		if ( errorHookThreadConfig->queuePrio > coreVars->currentThread->currentPriority )
		{
			/* Error-hook thread can preempt current thread. The thread can be started.
			*/
			MK_StartThread(&coreVars->threadQueueHead, errorHookThread, errorHookThreadConfig);
			errorHookThread->parentThread = culprit;

			errorHookThread->parentCookie = MK_NULLCOOKIE;
			errorHookThread->parentCore = coreVars->coreIndex;

			/* Preload the AUTOSAR error code parameter for the ErrorHook function
			*/
			MK_HwSetParameter1(errorHookThread->regs, osekError);
		}
	}
	else
	{
		/* Error hook thread is currently running the error hook --> a nested error. In this case
		 * we do not record the error in the error-info structure.
		 * Translate the error code for the return value.
		*/
		osekError = MK_ErrorInternalToOsek(eid);
	}

	return osekError;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
