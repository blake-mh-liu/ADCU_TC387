/* Mk_k_ppaterminateapplication.c
 *
 * This file contains the MK_PpaTerminateApplication() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>

/* MK_PpaTerminateApplication() determines the currently running OS-Application and terminates it.
 * It also marks the application as terminated, which means that it cannot be restarted.
 *
 * Preconditions:
 * - The culprit's application id is stored in this core's protection info.
 *
 * !LINKSTO Microkernel.Function.MK_PpaTerminateApplication, 1
 * !doctype src
*/
void MK_PpaTerminateApplication(mk_kernelcontrol_t *coreVars)
{
	mk_protectioninfo_t *protectionInfo = MK_protectionInfo[coreVars->coreIndex];
	mk_objectid_t culpritApplicationId = protectionInfo->culpritApplicationId;

	if (culpritApplicationId == MK_APPL_NONE)
	{
		/* The culprit doesn't belong to an OS-Application, so we cannot terminate it. Instead, shut down.
		*/
		MK_PpaShutdown(coreVars);
	}
	else
	{
		/* Now terminate everything that is already running and belonging to the OS-Application.
		*/
		MK_TerminateApplication(coreVars, culpritApplicationId, MK_FALSE);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
