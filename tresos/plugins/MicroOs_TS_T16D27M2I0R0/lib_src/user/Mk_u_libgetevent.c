/* Mk_u_libgetevent.c
 *
 * This file contains the GetEvent() function.
 *
 * This function is called by a thread in order to get the pending events for a task.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_task.h>
#include <private/Mk_event.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>
#include <public/Mk_autosar.h>
#include <public/Mk_public_api.h>

/* GetEvent() - Implements the AUTOSAR service.
 *
 * GetEvent() copies the pending events from the specified EXTENDED task's
 * event-status structure to the event-mask variable referenced by eventRef.
 * The eventRef parameter is not checked for validity because GetEvent runs in
 * the context of the calling thread and is therefore subject to the same
 * access restrictions.
 *
 * If the supplied taskId is not valid, or if the indicated task is not an EXTENDED task,
 * an appropriate error code is reported.
 *
 * This implementation of GetEvent assumes global read-only access to the microkernel's variables.
 * On a multi-core implementation read access to the microkernel's variables on other cores is also assumed.
 * There is also a potential problem of cache coherency between the cores.
 *
 * !LINKSTO      Microkernel.Function.GetEvent, 2
 * !doctype      src
*/
StatusType GetEvent(TaskType taskId, EventMaskRefType eventRef)
{
	const mk_taskcfg_t *taskCfg;
	mk_eventstatus_t *eventStatus;

	mk_errorid_t errorCode = MK_eid_Unknown;
	StatusType returnValue = (StatusType)MK_E_ERROR;

	if ( (taskId >= 0) && (taskId < MK_nTasks) )
	{
		/* Task ID is valid
		*/
		taskCfg = &MK_taskCfg[taskId];
		eventStatus = taskCfg->eventStatus;

		if ( eventStatus == MK_NULL )
		{
			/* Task is a BASIC task.
			*/
			errorCode = MK_eid_TaskIsNotExtended;
		}
		else
		{
			/* Task is an EXTENDED task
			*/
			errorCode = MK_eid_NoError;

			*eventRef = eventStatus->pendingEvents;
		}
	}
	else
	{
		errorCode = MK_eid_InvalidTaskId;
	}

	if ( errorCode == MK_eid_NoError )
	{
		returnValue = (StatusType)E_OK;
	}
	else
	{
		/* Report the error.
		*/
		returnValue = (StatusType)MK_ReportError(MK_sid_GetEvent, errorCode,
														(mk_parametertype_t)taskId, (mk_parametertype_t)eventRef);
	}

	return returnValue;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
