/* kern-localcancelalarm.c
 *
 * This file contains the OS_LocalCancelAlarm() function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: UnusedVariable
 *   Dead assignment eliminated.
 *
 * Reason:
 *   Not an issue. This variable is not used in Safety OS. Safety OS
 *   serializes all counter subsystem calls. Therefore, we do not need to lock
 *   interrupts here. Standalone AutoCore OS uses this variable.
*/

#define OS_SID OS_SID_CancelAlarm
#define OS_SIF OS_svc_CancelAlarm

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

#pragma warning 588

/*!
 * OS_LocalCancelAlarm
 *
 * The alarm 'a' is cancelled, provided it is currently in use.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_LocalCancelAlarm(os_alarmid_t a, const os_alarm_t *as)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t e;
	os_alarmdynamic_t *ad;
	/* Possible diagnostic TOOLDIAG-1 <1> */
	os_intstatus_t is;

	ad = as->dynamic;

	/* Possible diagnostic TOOLDIAG-1 <1> */
	is = OS_IntDisable();

	if ( !OS_APPISACCESSIBLE(as->app) )
	{
		e = OS_ERRORCODE_CHECK(OS_ERROR_ApplicationNotAccessible);
	}
	else
	if ( ad->inUse == OS_ALARM_INUSE )
	{
		/* !LINKSTO Kernel.API.Alarms.CancelAlarm.CancelAlarm, 1
		*/
		e = OS_KillAlarm(a, OS_ALARM_IDLE);
	}
	else
	{
		/* !LINKSTO Kernel.API.Alarms.CancelAlarm.UnusedAlarm, 1
		*/
		e = OS_ERRORCODE_CHECK(OS_ERROR_AlarmNotInUse);
	}

	OS_IntRestore(is);

	return e;
}

#pragma warning default

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
