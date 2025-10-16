/* Mk_k_ppaterminateapplicationrestart.c
 *
 * This file contains the MK_PpaTerminateApplicationRestart() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_application.h>

/* MK_PpaTerminateApplicationRestart() determines the currently running OS-Application and restarts it.
 *
 * Preconditions:
 * - The current thread's parent points to the culprit
 *
 * !LINKSTO Microkernel.Function.MK_PpaTerminateApplicationRestart, 1
 * !doctype src
*/
void MK_PpaTerminateApplicationRestart(mk_kernelcontrol_t *coreVars)
{
	/* The culprit is the protection hook's parent.
	*/
	mk_thread_t *culprit = coreVars->currentThread->parentThread;
	mk_protectioninfo_t *protectionInfo = MK_protectionInfo[coreVars->coreIndex];
	mk_objectid_t culpritApplicationId = protectionInfo->culpritApplicationId;

	if (culprit == MK_NULL)
	{
		/* If the culprit's application was terminated, it cannot be MK_APPL_NONE.
		 * Because the application was already terminated, there is nothing to do.
		 * If the culprit's application was terminated with the NO_RESTART option,
		 * it must not restart, although a restart is requested here by the ProtectionHook.
		 * In other words, the NO_RESTART option outvotes any RESTART attempts.
		*/
	}
	else if (culpritApplicationId == MK_APPL_NONE)
	{
		/* The culprit doesn't belong to an OS-Application, so we cannot terminate it. Instead, shut down.
		*/
		MK_PpaShutdown(coreVars);
	}
	else
	{
		MK_TerminateApplication(coreVars, culpritApplicationId, MK_TRUE);
		MK_RestartApplication(coreVars, culpritApplicationId);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
