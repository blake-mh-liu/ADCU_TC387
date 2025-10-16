/* Mk_k_restartapplication.c
 *
 * This file contains the MK_RestartApplication() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_task.h>
#include <private/Mk_panic.h>

/*
 * MK_RestartApplication() terminates all threads belonging to a given OS-Application and starts its restart thread.
 *
 * Preconditions:
 * - applicationId has already been range-checked by the caller (denotes a valid OS-Application)
 *
 * !LINKSTO Microkernel.Function.MK_RestartApplication, 1
 * !doctype src
*/
void MK_RestartApplication(mk_kernelcontrol_t *coreVars, mk_objectid_t applicationId)
{
	/* Determine the OS-Application's restart task
	*/
	mk_objectid_t restartTaskId = MK_appCfg[applicationId].restartTask;
	mk_errorid_t e;

	if ( (restartTaskId >= 0) && (restartTaskId < MK_nTasks) )
	{
		/* Set the application's state to "RESTARTING".
		*/
		MK_appCfg[applicationId].dynamic->appState = APPLICATION_RESTARTING;

		/* Now start its restart task.
		 * We don't expect an error here, because
		 * - maxActivations cannot be exceeded
		 * - OS-Application can't be in state quarantined, because the OS-Application
		 *   was running when it called this function.
		 * - restartTaskId was range-checked (this happens in function MK_InitApplications())
         * The task has to be bound to this core (any cross-core activity happens at the
		 * "TerminateApplication" level) so we use MK_LocalActivateTask() directly.
		 *
		 * The application itself is passed as the application ID so that the activation
		 * does not get rejected because the app. is restarting.
		*/
		e = MK_LocalActivateTask(coreVars, restartTaskId, &MK_taskCfg[restartTaskId], applicationId);
		if ( e != MK_eid_NoError )
		{
			MK_Panic(MK_panic_UnexpectedTaskActivationFailure);
		}
	}
	/* It is not an error if no restart task is configured. The application stays terminated.
	*/
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
