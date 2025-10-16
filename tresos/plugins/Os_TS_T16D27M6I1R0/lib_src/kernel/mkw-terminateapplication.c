/* mkw-terminateapplication.c
 *
 * This file contains the OS_MkwTerminateApplicationn function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#define OS_SID	OS_SID_TerminateApplication
#define OS_SIF	OS_svc_TerminateApplication

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <Os_mkctrsub.h>
#include <Os_microkernel.h>

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_MkwTerminateApplication implements the termination of alarms and schedule tables
 * of the API call TerminateApplication. ISRs and tasks are terminated by the microkernel.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication, 3
 * !LINKSTO Kernel.Autosar.OsApplication.Shutdown, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
mk_parametertype_t OS_MkwTerminateApplication(
	mk_parametertype_t p0,
	mk_parametertype_t p1,
	mk_parametertype_t p2 )
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_applicationid_t aId = (os_applicationid_t) p0;
	os_restart_t restart = (os_restart_t) p1;
	os_result_t r = OS_E_OK;

	os_alarmid_t alarmId;
	os_uint8_t newAlarmState = OS_ALARM_IDLE;

	os_scheduleid_t scheduleId;
	os_schedulestatus_t newScheduleState = OS_ST_STOPPED;

	OS_PARAMETERACCESS_DECL

	OS_SAVE_PARAMETER_N(0,(os_applicationid_t)aId);
	/* COVPT-1 */
	OS_SAVE_PARAMETER_N(1,(os_paramtype_t)restart);

	OS_TRACE_TERMINATEAPPLICATION_ENTRY(aId, restart);

	OS_PARAM_UNUSED(p2);

	/* COVPT-2 */
	if ( !OS_IsValidApplicationId(aId) )
	{
		r = OS_ERROR(OS_ERROR_InvalidApplicationId, OS_GET_PARAMETER_VAR());
	}
	else
	{
		/* COVPT-3 */
		if (restart == OS_APPL_RESTART)
		{
			newAlarmState = OS_ALARM_IDLE;
			newScheduleState = OS_ST_STOPPED;
		}
		/* COVPT-4 */
		else if (restart == OS_APPL_NO_RESTART)
		{
			newAlarmState = OS_ALARM_QUARANTINED;
			newScheduleState = OS_ST_QUARANTINED;
		}
		else
		{
			r = OS_ERROR(OS_ERROR_InvalidRestartOption, OS_GET_PARAMETER_VAR());
		}

		/* COVPT-5 */
		if (r == OS_E_OK)
		{
			/* Terminate all alarms and set to the selected state.
			 * Only true OSEK alarms are considered. Those belonging to schedule tables are
			 * terminated when the schedule table gets stopped.
			*/
			/* COVPT-6 */
			for (alarmId = 0; alarmId < OS_nAlarms; alarmId++)
			{
				const os_alarm_t *alarm = &OS_alarmTableBase[alarmId];
				/* COVPT-7 */
				if ( OS_GET_APPID(alarm->app) == (mk_objectid_t)aId )
				{
					(void)(*OS_killAlarmFunc)(alarmId, newAlarmState);
				}
			}

			/* Stop all schedule tables and set to the selected state.
			*/
			/* COVPT-8 */
			for (scheduleId = 0; scheduleId < OS_nSchedules; scheduleId++)
			{
				const os_schedule_t *schedule = &OS_scheduleTableBase[scheduleId];
				/* COVPT-9 */
				if ( OS_GET_APPID(schedule->app) == (mk_objectid_t)aId )
				{
					(void)(*OS_killScheduleFunc)(scheduleId, newScheduleState);
				}
			}
		}
	}

	return (mk_parametertype_t)r;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mkw_terminateapplication_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
