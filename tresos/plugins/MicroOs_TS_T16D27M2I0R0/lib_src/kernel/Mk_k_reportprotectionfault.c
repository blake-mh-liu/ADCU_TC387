/* Mk_k_reportprotectionfault.c
 *
 * This file contains the function MK_ReportProtectionFault().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  MK_ReportProtectionFault can call itself again indirectly via MK_Panic and
 *  MK_Dispatch, but this can only happen if the protection hook thread has an
 *  execution budget and exceeds it.  In the unlikely case that also the
 *  shutdown thread has and exceeded execution budget, the calls to MK_Panic,
 *  MK_Dispatch and MK_Panic again will result in a call to MK_PanicStop.  So
 *  there is a maximum nesting of two calls to MK_ReportProtectionFault
 *  possible.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_error.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_panic.h>
#include <private/Mk_shutdown.h>

/* MK_ReportProtectionFault() - report a protection violation
 *
 * A protection violation is reported by some combination (depending on configuration) of
 * - filling the MK_protectionInfo structure
 * - calling (starting a thread for) the ProtectionHook() function
 * - shutting down
 * - panicking ... if all else fails :-)
 *
 * !LINKSTO Microkernel.Function.MK_ReportProtectionFault, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 */
void MK_ReportProtectionFault(mk_kernelcontrol_t *coreVars, mk_serviceid_t sid, mk_errorid_t eid)
{
	mk_osekerror_t osekError;
	mk_thread_t *protectionHookThread = MK_protectionHookThread[coreVars->coreIndex];
	const mk_threadcfg_t *protectionHookThreadConfig = MK_protectionHookThreadConfig[coreVars->coreIndex];
	mk_protectioninfo_t *protectionInfo = MK_protectionInfo[coreVars->coreIndex];

	osekError = MK_ErrorInternalToOsek(eid);

	if ( protectionHookThread == MK_NULL )
	{
		/* No protection hook is configured. Just record the error, then shut down
		*/
		protectionInfo->serviceId = sid;
		protectionInfo->errorId = eid;
		protectionInfo->osekError = osekError;
		protectionInfo->culprit = coreVars->currentThread;
		protectionInfo->culpritApplicationId = coreVars->currentThread->applicationId;
		/* Deviation MISRAC2012-1 <+1> */
		MK_Shutdown(osekError);
	}
	else
	if ( protectionHookThread->state == MK_THS_IDLE )
	{
		/* Protection-hook thread is idle. The thread can be started.
		*/
		protectionInfo->serviceId = sid;
		protectionInfo->errorId = eid;
		protectionInfo->osekError = osekError;
		protectionInfo->culprit = coreVars->currentThread;
		protectionInfo->culpritApplicationId = coreVars->currentThread->applicationId;

		/* Deviation MISRAC2012-1 <+1> */
		MK_StartThread(&coreVars->threadQueueHead, protectionHookThread, protectionHookThreadConfig);

		/* This ensures that the error code is handled on termination of the
		 * protection hook thread.
		*/
		protectionHookThread->parentThread = coreVars->currentThread;

		protectionHookThread->parentCookie = MK_NULLCOOKIE;
		protectionHookThread->parentCore = coreVars->coreIndex;

		/* Preload the AUTOSAR error code parameter for the ProtectionHook function
		*/
		MK_HwSetParameter1(protectionHookThread->regs,  osekError);
	}
	else
	{
		/* Deviation MISRAC2012-1 <+1> */
		MK_Panic(MK_panic_ProtectionFaultInProtectionHook);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
