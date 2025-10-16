/* kern-localgetevent.c
 *
 * This file contains the OS_LocalGetEvent() function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* The SID and serviceinfo aren't actually used in the code, but the error table builder
 * needs them to check for error codes that are defined but not used, or used but not defined.
*/
#define OS_SID	OS_SID_GetEvent
#define OS_SIF	OS_svc_GetEvent

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_LocalGetEvent()
 *
 * The pending events for the specified task 'tp' are copied to the specified
 * location 'ep'.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_LocalGetEvent(const os_task_t *tp, os_eventmask_t *ep)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_taskdynamic_t *td;
	os_errorresult_t result;

	td = tp->dynamic;

	/* There's no need to disable interrupts here because
	 * the transition to SUSPENDED/QUARANTINED does not alter
	 * the state of the events. If we disabled interrupts,
	 * the transition could occur immediately when they were
	 * re-enabled, and the result would be the same.
	*/
	/* !LINKSTO Kernel.API.EventControl.GetEvent.SuspendedTask, 1
	*/
	if ( (td->state == OS_TS_SUSPENDED) || (td->state == OS_TS_QUARANTINED) )
	{
		result = OS_ERRORCODE_CHECK(OS_ERROR_TaskSuspended);
	}
	else
	{
		*ep = td->pEvents;

		result = OS_ERRORCODE_NOCHECK(OS_ERROR_NoError);
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_localgetevent_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
