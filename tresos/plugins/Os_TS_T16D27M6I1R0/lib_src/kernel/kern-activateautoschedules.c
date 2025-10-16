/* kern-activateautoschedules.c
 *
 * This file contains the OS_ActivateAutoSchedules function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *   Comparison with constant compile-time result
 *
 * Reason: In single-core configurations, the result is compile-time constant.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
 */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 14.3 (required)
 * Controlling expressions shall not be invariant.
 *
 * Reason:
 * The invariance depends on the configuration. In single-core systems,
 * for example, the expression is always true.
 *
 *
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * For single-core configurations, the expression is always true.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_ActivateAutoSchedules()
 *
 * Activate all schedule tables that are specified for the requested mode
 *
 * !LINKSTO Kernel.Autosar.Autostart, 1
 * !LINKSTO Kernel.Autosar.ScheduleTable.Autostart, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ActivateAutoSchedules(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint16_t idx;
	const os_autoschedule_t *as;
	os_scheduleid_t s;
	const os_schedule_t *ss;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();

	idx = OS_startModeSchedules[OS_GetAppMode()];
	as = &OS_autoStartSchedules[idx];
	s = as->schedule;

	while ( s < OS_nSchedules )
	{
		ss = &OS_scheduleTableBase[s];

		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2>, MISRAC2012-2 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
#pragma warning 549
		if(OS_GetCoreIdFromScheduleTableId(s) == myCoreId)
#pragma warning default
		{

			if ( as->method == OS_STARTMETHOD_SYNC )
			{
				/* !LINKSTO Kernel.Autosar.ScheduleTable.Autostart.Synchronously, 1
				*/
				/* when called during autostart, DoStartScheduleTableSynchron can't
				 * fail, so we can safely ignore its return value
				 */
				(void) OS_LocalStartScheduleTableSynchron(ss);
			}
			else
			{
				/* An incorrectly generated method will start "relative".
				 *
				 * !LINKSTO Kernel.Autosar.ScheduleTable.Autostart.Absolute, 1
				 * !LINKSTO Kernel.Autosar.ScheduleTable.Autostart.Relative, 1
				 */
				/* when called during autostart, DoStartScheduleTable can't fail, so
				 * we can safely ignore its return value
				 */
				(void) OS_LocalStartScheduleTable(ss, OS_alarmTableBase[ss->alarm].counter,
						as->offset, (os_boolean_t)(as->method != OS_STARTMETHOD_ABS));
			}
		}
		idx++;
		as = &OS_autoStartSchedules[idx];
		s = as->schedule;
	}
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
