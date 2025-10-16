/* kern-setschedulealarm.c
 *
 * This file contains the OS_SetScheduleAlarm function.
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
 *   Condition is always false/true.
 *
 * Reason: This warning depends on the OS configuration and library optimization.
 *   If there are no hardware counters (OS_EXCLUDE_HWCOUNTER), this condition is always false.
 *   If there are no software counters (OS_EXCLUDE_SWCOUNTER), this condition is always true.
 *   Otherwise this condition must be evaluated at runtime.
 *
 * TOOLDIAG-2) Possible diagnostic: UnusedVariable
 *   Dead assignment eliminated.
 *
 * Reason:
 *   Not an issue. This variable is not used in Safety OS. Safety OS
 *   serializes all counter subsystem calls. Therefore, we do not need to lock
 *   interrupts here. Standalone AutoCore OS uses this variable.
 *
 * TOOLDIAG-3) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason: This warning depends on the OS configuration and library optimization.
 *   If there are no hardware counters (OS_EXCLUDE_HWCOUNTER), this condition is always false.
 *   If there are no software counters (OS_EXCLUDE_SWCOUNTER), this condition is always true.
 *   Otherwise this condition must be evaluated at runtime.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

#pragma warning 588

/*!
 * OS_SetScheduleAlarm
 *
 * The alarm is set to expire in/at the specified number of timer ticks.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_SetScheduleAlarm
(	const os_schedule_t *ss,	/* The schedule table (static stuff) */
	os_scheduledynamic_t *sd,	/* The schedule table (dynamic stuff) */
	os_tick_t val,				/* The relative or absolute counter value */
	os_boolean_t rel			/* TRUE if val is a relative value */
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_alarm_t *as;
	os_alarmdynamic_t *ad;
	const os_counter_t *cs;
	os_counterdynamic_t *cd;
	/* Possible diagnostic TOOLDIAG-2 <1> */
	os_intstatus_t is;

	/* COVPT-1 */
	as = &OS_alarmTableBase[ss->alarm];
	ad = as->dynamic;
	cs = &OS_counterTableBase[as->counter];
	cd = cs->dynamic;

	/* For a hardware counter we need the current value from the hardware,
	 * and we need to update the delta of the head alarm in the queue.
	 *
	 * This is done before disabling interrupts. If a timer interrupt
	 * happens here it is safe.
	 *
	 * If the counter is locked the value is already current.
	*/
	/* COVPT-2 +2 */
	/* Possible diagnostic TOOLDIAG-1 <1> */
	if ( (!rel) && (OS_CounterIsHw(cs)) && (cd->lock == 0U) )
	{
		/* Possible diagnostic TOOLDIAG-3 <1> */
		OS_CtrUpdate(cs);
	}

	/* Possible diagnostic TOOLDIAG-2 <1> */
	is = OS_IntDisable();

	ad->inUse = OS_ALARM_INUSE;
	ad->period = 0;

	/* Calculate an appropriate delta
	*/
	/* COVPT-3 */
	if ( rel )
	{
		/* Relative value: the delta is simply the given value
		*/
		ad->delta = val;
	}
	else
	{
		/* Absolute value. Take account of wrap-around.
		*/
		ad->delta = OS_CounterSub(val, cd->current, cs->maxallowedvalue);
	}

	/* Store the counter value at which the alarm will expire
	*/
	sd->ctrAbs = OS_CounterAdd(cd->current, ad->delta, cs->maxallowedvalue);

	OS_EnqueueAlarm(cs, cd, ss->alarm, ad);

	OS_IntRestore(is);

	/* If our alarm is at the beginning of the queue of a hardware counter we need
	 * to adjust the timer's time-to-next-interrupt to reflect this.
	 * (But not if the counter is locked)
	*/
	/* COVPT-4 +2 */
	/* Possible diagnostic TOOLDIAG-1 <1> */
	if (OS_CounterIsHw(cs))
	{
		/* COVPT-5 +2 */
		/* Possible diagnostic TOOLDIAG-3 <1> */
		if ((cd->lock == 0U) && (cd->head == ss->alarm))
		{
			OS_CtrUpdate(cs);
		}
	}

}

#pragma warning default

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
