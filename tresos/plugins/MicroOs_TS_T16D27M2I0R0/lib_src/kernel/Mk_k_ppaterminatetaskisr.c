/* Mk_k_ppaterminatetaskisr.c
 *
 * This file contains the MK_PpaTerminateTaskIsr() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>

/* MK_PpaTerminateTaskIsr() terminates the current thread if it is a task or ISR.
 *
 * Preconditions:
 * - The current thread's parent points to the culprit
 *
 * !LINKSTO Microkernel.Function.MK_PpaTerminateTaskIsr, 1
 * !doctype src
*/
void MK_PpaTerminateTaskIsr(mk_kernelcontrol_t *coreVars)
{
	/* The culprit is the protection hook's parent.
	*/
	mk_thread_t *culprit = coreVars->currentThread->parentThread;

	if (culprit == MK_NULL)
	{
		/* The culprit was already terminated, so there is nothing more to do.
		*/
	}
	else
	{
		const mk_objecttype_t objType = culprit->objectType;

		if ( (objType == MK_OBJTYPE_TASK) || (objType == MK_OBJTYPE_ISR) )
		{
			MK_PpaTerminateThread(coreVars);
		}
		else
		{
			/* If there is no task or ISR, AUTOSAR requires to terminate the OS-Application.
			*/
			MK_PpaTerminateApplication(coreVars);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
