/* Mk_u_libgettaskid.c
 *
 * This file contains the GetTaskID() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>

/* GetTaskID() - Implements the AUTOSAR service.
 *
 * This function returns the ID of the current task.
 * If called from a task, the result is simply the caller's ID. This is derived from
 * the current thread.
 *
 * If the caller is not a task, the thread queue needs to be searched for the appropriate
 * thread. This is done by a system call to the microkernel via the MK_UsrGetTaskId API.
 * The function is implemented as a system call for concurrency reasons.
 * If the system call returns the status code is E_OK, the requested value is placed in
 * the referenced TaskType variable and the function returns the status code.
 *
 * !LINKSTO      Microkernel.Function.GetTaskID, 2
 * !doctype      src
*/
StatusType GetTaskID(TaskRefType taskIdRef)
{
	mk_statusandvalue_t syscallReturn;

	/* The shortcut is only possible if a thread can read the core identification directly.
	*/
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
	mk_thread_t *currThread = coreVars->currentThread;

	if ( currThread->objectType == MK_OBJTYPE_TASK )
	{
		*taskIdRef = (TaskType)currThread->currentObject;
	}
	else
	{
		syscallReturn = MK_UsrGetTaskId((mk_parametertype_t)taskIdRef);
		*taskIdRef = (TaskType)syscallReturn.requestedValue;
	}

	return E_OK;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
