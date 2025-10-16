/* Mk_k_rejectshutdown.c
 *
 * This file contains the MK_RejectShutdown() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_thread.h>
#include <private/Mk_errorhandling.h>

/* RejectShutdown() - Handler for rejected shutdown requests
 *
 * This is a helper function for MK_SysShutdown and MK_SysShutdownAllCores.
 * It is called, when a thread requests a shutdown, but is not allowed to do so.
 * It terminates the thread and reports an error.
 *
 * Parameters:
 *	coreVars	- A pointer to the current core's kernel control data.
 *	sid			- The service id of the shutdown request which is to be rejected.
*/
void MK_RejectShutdown(mk_kernelcontrol_t *coreVars, mk_serviceid_t sid)
{
	mk_thread_t *caller = coreVars->currentThread;
	mk_hwlocklevel_t lockLevel;

	/* First dequeue the caller ...
	*/
	coreVars->threadQueueHead = caller->next;
	caller->next = MK_NULL;

	/* ... then report the error (while the caller's registers etc are still valid) ...
	*/
	(void)MK_InternReportError(coreVars, sid, MK_eid_WithoutPermission, caller, MK_NULL);

	/* ... then terminate the caller.
	*/
	lockLevel = MK_HwGetIntLevel(caller->regs);
	MK_HwFreeThreadRegisters(caller->regs);
	MK_TerminateThread(coreVars, caller, lockLevel);

	/* A thread has been terminated. If there are no more threads the problem needs to be handled.
	*/
	if (coreVars->threadQueueHead == MK_NULL)
	{
		MK_ThreadQueueEmpty();
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
