/* kern-restartapplication.c
 *
 * This file contains the OS_RestartApplication function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 * Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 * Function OS_RestartApplication is called indirectly by OS_Error and OS_ErrorAction.
 * The implementation of OS_Error and OS_ErrorAction ensures that no recursion is possible.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: SetButNeverUsed
 *   Dead assignment.
 *
 * Reason: Not an issue, assignment is effective depending on OS error handling level.
 */

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_RestartApplication restarts the specified application.
 *
 * Restarting an application means:
 *  - setting all alarms, schedule tables and tasks to their respective
 *    "not running" states
 *  - activating the restart task for the application, if there is one.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RestartApplication(const os_appcontext_t *app)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_taskid_t taskid;
	os_alarmid_t alarmid;
	os_scheduleid_t scheduleid;
	const os_task_t *task;
	const os_alarm_t *alarm;
	const os_schedule_t *schedule;

	/* Set the application state to RESTARTING
	*/
	app->dynamic->appstate = OS_APP_RESTARTING;

	/* Set all alarms to the IDLE state.
	 * Only true OSEK alarms are considered. Others (such as
	 * those belonging to schedule tables) won't be in the
	 * QUARANTINED state.
	*/
	/* Possible diagnostic TOOLDIAG-1 <1> */
	alarm = OS_alarmTableBase;
	for ( alarmid = 0; alarmid < OS_nAlarms; alarmid++ )
	{
		if ( OS_GET_APP(alarm->app) == app )
		{
			/* Deviation MISRAC2012-1 <+1> */
			(void)(*OS_killAlarmFunc)(alarmid, OS_ALARM_IDLE);
		}
		/* Possible diagnostic TOOLDIAG-1 <2> */
		alarm++;
	}

	/* Set all schedule tables to the STOPPED state.
	*/
	/* Possible diagnostic TOOLDIAG-1 <1> */
	schedule = OS_scheduleTableBase;
	for ( scheduleid = 0; scheduleid < OS_nSchedules; scheduleid++ )
	{
		if ( OS_GET_APP(schedule->app) == app )
		{
			(void)(*OS_killScheduleFunc)(scheduleid, OS_ST_STOPPED);
		}
		/* Possible diagnostic TOOLDIAG-1 <2> */
		schedule++;
	}

	/* Set all tasks to the SUSPENDED state.
	*/
	task = OS_taskTableBase;
	for ( taskid = 0; taskid < OS_nTasks; taskid++ )
	{
		if ( OS_GET_APP(task->app) == app )
		{
			(void)(*OS_killTaskFunc)(task, OS_TS_SUSPENDED);
		}
		task++;
	}

	/* The ISRs remain disabled. They may be reenabled by the restart task.
	*/

	/* Finally, activate the restart task. We don't use OS_KernActivateTask
	 * because the autosar error checking would probably throw out the request.
	 * Plus, we don't want to link in the function if it isn't needed.
	 *
	 * !LINKSTO Kernel.Autosar.Protection.ProtectionHook.RestartApplication, 1
	*/
	/* COVPT-1 */
	if ( (OS_IsValidTaskId(app->restartTask) ) && (OS_actiTaskFunc != OS_NULL) )
	{
		(*OS_actiTaskFunc)(&OS_taskTableBase[app->restartTask]);
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_restartapplication_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
