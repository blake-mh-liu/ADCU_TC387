/* kern-startupchecksschedule.c
 *
 * This file contains the OS_StartupChecksSchedule function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * For single-core configurations, the expression is always true.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *   Condition is always true.
 *
 * Reason: This warning depends on the number of configured cores.
 *   Only in case of a single core configuration, this comparison can be evaluated at compile time.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_panic.h>

#include <memmap/Os_mm_code_begin.h>

OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_StartupChecksSchedule(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();
	os_result_t result = OS_E_OK;
	os_unsigned_t i;
	os_unsigned_t j;
	const os_schedule_t *schedule;
	const os_scheduleentry_t *evt;
	os_eventmask_t foundevents;
	os_tick_t counterMax;
	os_tick_t extraDelay;
	os_tick_t lastOffset;
	os_tick_t delay;
	os_boolean_t syncable;
	os_permission_t perms;
	os_appcontext_t const* app;

	for ( i = 0; i < OS_nSchedules; i++ )
	{
		schedule = &OS_scheduleTableBase[i];
		app = OS_GET_APP(schedule->app);

		/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.NoOwningApplication, 1 */
		if ( OS_AppIsNull(app) )
		{
			result = OS_PANIC(OS_PANIC_SCHK_NoOwningApplication);
		}

		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		if (OS_GetScheduleTableCoreId(schedule) == myCoreId)
		{
			perms = OS_GET_APP(schedule->permissions);

			/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.NoApplicationPermission, 1 */
			if ( !OS_HasPermission(app, perms) )
			{
				result = OS_PANIC(OS_PANIC_SCHK_OwningApplicationHasNoPermission);
			}

			counterMax = OS_counterTableBase[OS_alarmTableBase[schedule->alarm].counter].maxallowedvalue;
			syncable = (schedule->flags & OS_ST_SYNCABLE) != 0u;

			foundevents = 0;
			lastOffset = 0;
			extraDelay = schedule->period - schedule->table[schedule->nEntries-1u].offset;

			for ( j = 0; j < schedule->nEntries; j++ )
			{
				evt = &schedule->table[j];

				/* Remember events that have been set at this offset.
				 * Reset memory of events at each new offset
				*/
				if ( evt->offset == lastOffset )
				{
					foundevents |= evt->event;
				}
				else
				{
					foundevents = evt->event;
				}

				/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.TaskAfterEvent, 1 */
				if ( (foundevents != 0u) && (evt->event == 0u) )
				{
					result = OS_PANIC(OS_PANIC_SCHK_ScheduleTableActivateTaskAfterSetEvent);
				}

				/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.WrongEventOrder, 1 */
				if ( evt->offset < lastOffset )
				{
					result = OS_PANIC(OS_PANIC_SCHK_ScheduleTableEventsNotInOrder);
				}

				/* These checks don't make sense if the offset is wrong.
				 * Furthermore, the sync-range checks are only done for the first event at a given offset.
				 * The sync parameters for the remainder of the events (at the same offset) are not used,
				 * so the OS doesn't care. Maybe the generator sets them to zero, maybe to the same as the
				 * first event at this offset.
				*/
				if ( (j == 0u) || (evt->offset != lastOffset) )
				{
					/* This is the delay from the last expiry point to this one.
					*/
					delay = (evt->offset - lastOffset) + extraDelay;

					/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.DelayTooBig, 1 */
					if ( delay > counterMax )
					{
						result = OS_PANIC(OS_PANIC_SCHK_DelayGreaterThanCounterMax);
					}

					/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.InvalidIncrease, 1 */
					if ( syncable && ((delay + evt->maxIncrease) > counterMax) )
					{
						result = OS_PANIC(OS_PANIC_SCHK_DelayPlusMaxIncreaseGreaterThanCounterMax);
					}

					/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.InvalidDecrease, 1 */
					if ( syncable && (evt->maxDecrease >= delay) )
					{
						result = OS_PANIC(OS_PANIC_SCHK_MaxDecreaseGreaterThanDelay);
					}

					/* !LINKSTO Kernel.Feature.StartupChecks.Schedule.InvalidIncreasePlusDecrease, 1 */
					if ( syncable && ((evt->maxDecrease + evt->maxIncrease) > schedule->period) )
					{
						result = OS_PANIC(OS_PANIC_SCHK_SynchronisationRangeGreaterThanScheduleTableLength);
					}
				}
				lastOffset = evt->offset;
				extraDelay = 0;
			}
		}
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_startupchecksschedule_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
