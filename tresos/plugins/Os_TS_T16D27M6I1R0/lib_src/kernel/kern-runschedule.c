/* kern-runschedule.c
 *
 * This file contains the OS_RunSchedule function.
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

#define OS_SID OS_SID_RunSchedule
#define OS_SIF OS_svc_RunSchedule

#include <Os_kernel.h>
#include <Os_panic.h>


#define OS_SYNCHRONISE(sd, nextp, delta)	\
	( (OS_synchronizeFunc == OS_NULL) ? (delta) : (*OS_synchronizeFunc)((sd), (nextp), (delta)) )

#include <memmap/Os_mm_code_begin.h>

#pragma warning 588

/* These local functions help to break up the main function, which
 * would otherwise be very long.
 * Hopefully the compiler will in-line them if it considers it to
 * be worthwhile. That might make debugging trickier, but that can be
 * eliminated by temporarily turning off that optimisation.
*/
static os_boolean_t OS_Chain(os_scheduledynamic_t *sd);
static os_boolean_t OS_FinalExpiry(const os_schedule_t *ss, os_scheduledynamic_t *sd, const os_scheduleentry_t *currp);

/*!
 * OS_RunSchedule
 *
 * This function runs a schedule table. The current event (as indicated by
 * the dynamic "next" field) is noted. Then the next event is evaluated,
 * taking into account periodic tables and chained tables, and the resulting
 * delta time is programmed into the alarm. Finally the desired event action
 * is taken.
 *
 * !LINKSTO Kernel.Autosar.ScheduleTable, 2
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RunSchedule(os_scheduleid_t sIn)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_schedule_t *ss;
	os_scheduledynamic_t *sd;
	const os_scheduleentry_t *currp;
	const os_scheduleentry_t *nextp;
	os_tick_t delta;
	/* Possible diagnostic TOOLDIAG-1 <1> */
	os_intstatus_t is;
	os_boolean_t looping = OS_FALSE;
	os_scheduleid_t s = sIn;

	ss = &OS_scheduleTableBase[s];
	sd = ss->dynamic;

	/* Possible diagnostic TOOLDIAG-1 <1> */
	is = OS_IntDisable();

	/* COVPT-1 */
	if ( sd->status == (OS_ST_WAITING | OS_ST_SYNCHRONOUS) )
	{
		os_counterid_t counter;
		os_tick_t maxallowedvalue;

		/* Schedule table was started synchronously. Global time is
		 * available, but the timer does not have sufficient range
		 * to reach the first event from the sync time, so we had to
		 * insert some extra interrupts
		 * This can only happen when the range (maxallowedvalue) of
		 * a hardware counter is less than the range of os_tick_t.
		*/
		counter = OS_alarmTableBase[ss->alarm].counter;
		maxallowedvalue = OS_counterTableBase[counter].maxallowedvalue;

		/* COVPT-2 */
		if ( sd->adjRemaining > maxallowedvalue )
		{
			delta = maxallowedvalue;
			sd->adjRemaining -= maxallowedvalue;
		}
		else
		{
			delta = sd->adjRemaining;
			sd->adjRemaining = 0;
			sd->status = OS_ST_RUNNING | OS_ST_SYNCHRONOUS;
		}

		OS_SetScheduleAlarm(ss, sd, delta, OS_TRUE);

	}
	/* COVPT-3 +2 */
	else
	if ( (sd->status & OS_ST_STATE) != OS_ST_RUNNING )
	{
		/* Schedule table was stopped in a higher-priority interrupt
		 * routine, or something similar. We just ignore this call
		*/
	}
	else
	{
		/* Repeat until all expired events are processed.
		*/
		do {

			if ( (sd->status & OS_ST_RUNOUT) != 0U )
			{
				/* End of the special runout period inserted when ending a nonperiodic
				 * schedule table or chaining a new schedule table.
				 *
				 * !LINKSTO Kernel.Autosar.ScheduleTable.Single, 2
				*/
				sd->status = OS_ST_STOPPED;	/* Clears all flags */

				if ( sd->chain == OS_NULLSCHEDULE )
				{
					looping = OS_FALSE;
				}
				else
				{
					/* COVPT-4 +3 */
					/* !LINKSTO Kernel.Autosar.ScheduleTable.Chain, 2
					*/
					if ( OS_alarmTableBase[ss->alarm].counter != OS_alarmTableBase[OS_scheduleTableBase[sd->chain].alarm].counter )
					{
						/* The alarm is on the different counter. Can't propagate the return value of OS_PANIC -> ignore it */
						(void) OS_PANIC(OS_PANIC_RunST_ScheduleTableNotOnTheSameCounter); /* Should never return */

					}
					else
					{
						s = sd->chain;
						looping = OS_Chain(sd);
						ss = &OS_scheduleTableBase[s];
						sd = ss->dynamic;
					}
				}
			}
			else
			{
				/* !LINKSTO Kernel.Autosar.ScheduleTable.ExpiryPoint, 1
				*/
				currp = &ss->table[sd->next];

				OS_IntRestore(is);

				/* !LINKSTO Kernel.Autosar.ScheduleTable.ExpiryPoint.Actions, 1
				*/
				if ( currp->event == 0U )
				{
					/* no way to propagate the return value -> ignore it */
					(void) OS_InternalActivateTask(currp->task);
				}
				else
				{
					/* no way to propagate the return value -> ignore it */
					(void) OS_InternalSetEvent(currp->task, currp->event);
				}

				(void) OS_IntDisable();		/* Old level discarded */

				/* Move to the next event
				*/
				sd->next++;

				if ( sd->next >= ss->nEntries )
				{
					/* End of round. */
					looping = OS_FinalExpiry(ss, sd, currp);
				}
				else
				{
					/* Next event in schedule. Delta time is
					 * next_offset - current_offset
					*/
					nextp = &ss->table[sd->next];
					delta = nextp->offset - currp->offset;

					/* If delta is zero we process it immediately.
					*/
					/* !LINKSTO Kernel.Autosar.ScheduleTable.ExpiryPoint.Offset, 1 */
					if ( delta == 0U )
					{
						looping = OS_TRUE;
					}
					else
					{
						/* Perform SMOOTH synchronisation if so configured.
						*/
						delta = OS_SYNCHRONISE(sd, nextp, delta);

						looping = OS_ResetScheduleAlarm(ss, sd, delta);
					}
				}
			}
		} while ( looping );
	}

	OS_IntRestore(is);
}

/*!
 * OS_Chain
 *
 * This local function starts the chained schedule table at the
 * specified delta.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static os_boolean_t OS_Chain(os_scheduledynamic_t *sd )	/* Refers to current ST */
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_scheduleid_t sc;				/* Chained ST */
	const os_schedule_t *scs;		/* Refers to chained ST */
	os_scheduledynamic_t *scd;		/* Refers to chained ST */
	const os_scheduleentry_t *nextp;
	os_boolean_t repeat = OS_FALSE;

	sc = sd->chain;
	sd->chain = OS_NULLSCHEDULE;
	sd->status = OS_ST_STOPPED;

	scs = &OS_scheduleTableBase[sc];
	scd = scs->dynamic;

	/* sc, scs and scd now all refer to the incoming ST.
	*/

	/* COVPT-5 */
	if ( scd->status == OS_ST_CHAINED )
	{
		scd->status = OS_ST_RUNNING;
		scd->next = 0;
		nextp = scs->table;

		/* Set the alarm relative to the last
		 * counter expiry. We must copy the current ST's ctrAbs to the
		 * chained ST so that the counter algorithms work correctly.
		*/
		scd->ctrAbs = sd->ctrAbs;
		repeat = OS_ResetScheduleAlarm(scs, scd, nextp->offset);
	}
	else
	{
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_NotChained, OS_NULL);
	}

	return repeat;
}

/*!
 * OS_FinalExpiry
 *
 * This local function performs the end-of-round activities, including
 * synchronisation and chaining a new schedule table.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static os_boolean_t OS_FinalExpiry
(	const os_schedule_t *ss,
	os_scheduledynamic_t *sd,
	const os_scheduleentry_t *currp
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_scheduleentry_t *nextp;
	os_tick_t delta;
	os_boolean_t repeat = OS_FALSE;

	sd->next = 0;
	delta = ss->period - currp->offset;

	if ( sd->chain != OS_NULLSCHEDULE )
	{
		/*
		 * !LINKSTO Kernel.Autosar.API.SystemServices.ChainScheduleTable.Synchronisation, 2
		*/

		sd->status |= OS_ST_RUNOUT;

		repeat = OS_ResetScheduleAlarm(ss, sd, delta);
	}
	else
	if ( (ss->flags & OS_ST_REPEATING) != 0U )
	{
		/* "Periodic" schedule tables just "start again" from the beginning. The
		 * delta is computed as the time remaining in this period plus the offset of the
		 * first event
		 *
		 * !LINKSTO Kernel.Autosar.ScheduleTable.Periodic, 1
		*/
		nextp = ss->table;
		delta += nextp->offset;

		delta = OS_SYNCHRONISE(sd, nextp, delta);

		repeat = OS_ResetScheduleAlarm(ss, sd, delta);
	}
	else
	{
		/* "Nonperiodic" schedule tables continue "running" until the end of their period.
		 *
		 * !LINKSTO Kernel.Autosar.ScheduleTable.Single, 2
		*/
		sd->status |= OS_ST_RUNOUT;

		repeat = OS_ResetScheduleAlarm(ss, sd, delta);
	}

	return repeat;
}

#pragma warning default

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
