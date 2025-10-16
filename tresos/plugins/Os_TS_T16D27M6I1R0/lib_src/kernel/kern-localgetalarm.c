/* kern-localgetalarm.c
 *
 * This file contains the OS_LocalGetAlarm() function.
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

#define OS_SID	OS_SID_GetAlarm
#define OS_SIF	OS_svc_GetAlarm

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

#pragma warning 588

/*!
 * OS_LocalGetAlarm()
 *
 * The total number of ticks remaining before the alarm expires is written to the indicated location.
 *
 * !LINKSTO Kernel.API.Alarms.GetAlarm.API, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_LocalGetAlarm(os_alarmid_t a, const os_alarm_t *as, os_tick_t *out)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_alarmdynamic_t *ad;
	os_counterdynamic_t *cd;
	/* Possible diagnostic TOOLDIAG-1 <1> */
	os_intstatus_t is;
	os_int_t gadRes;
	os_errorresult_t result;

	ad = as->dynamic;

	/* Possible diagnostic TOOLDIAG-1 <1> */
	is = OS_IntDisable();

	/* Call internal function to do the job. If it returns nonzero, something was wrong:
	 *  > 0 --> Alarm not in use
	 *  < 0 --> Corrupt alarm list
	*/
	gadRes = OS_GetAlarmDelta(a, as, ad, out);

	OS_IntRestore(is);

	/* COVPT-1 */
	if ( gadRes < 0 )
	{
		result = OS_ERRORCODE_CHECK(OS_ERROR_InvalidAlarmState);
	}
	else
	if ( gadRes > 0 )
	{
		/* !LINKSTO Kernel.API.Alarms.GetAlarm.UnusedAlarm, 1
		*/
		result = OS_ERRORCODE_CHECK(OS_ERROR_AlarmNotInUse);
	}
	else
	{
		/* No need to keep interrupts disabled for this:
		 *  - if the counter is locked neither the counter's delta nor the error term will
		 *    change in an ISR.
		 *  - if the counter is not locked the error term will always be zero even if the
		 *    alarm's delta has changed since we calculated it.
		*/
		cd = OS_counterTableBase[as->counter].dynamic;

		if ( *out <= cd->error )
		{
			*out = 0;
		}
		else
		{
			*out -= cd->error;
		}

		result = OS_ERRORCODE_NOCHECK(OS_ERROR_NoError);
	}

	return result;
}

#pragma warning default

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
