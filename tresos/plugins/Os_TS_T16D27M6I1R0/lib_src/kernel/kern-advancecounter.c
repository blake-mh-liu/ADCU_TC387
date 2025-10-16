/* kern-advancecounter.c
 *
 * This file contains the OS_AdvanceCounter function.
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
 *   unused parameter 'is'
 *
 * Reason: Not an issue. This variable isn't used in Safety OS.
 *   The microkernel serializes all calls to the lower integrity OS server.
 *   Therefore we don't need to lock interrupts here.
 *   Standalone AutoCore OS uses this variable.
 *
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.7
 * There should be no unused parameters in functions.
 *
 * Reason:
 *   Not an issue. This variable is not used in Safety OS. Safety OS
 *   serializes all counter subsystem calls. Therefore, we do not need to lock
 *   interrupts here. Standalone AutoCore OS uses this variable.
 *
 *
 * MISRAC2012-2) Deviated Rule: 17.2 (required)
 * Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 * Counter is locked before any action function like OS_WrapIncrementCounter is called.
 * When locked, no action is performed, thus ensuring that no endless recursion is possible.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_AdvanceCounter
 *
 * This function is called in order to advance a counter by a specified number of ticks.
 * The return value is the number of ticks remaining (delta) of the first alarm in the queue, or
 * 0 if there are no alarms.
 *
 * On entry: interrupts are disabled. The "enable" level is passed as a parameter.
 *
 * !LINKSTO Kernel.Autosar.Counter.Types.SOFTWARE, 2
 * !LINKSTO Kernel.Autosar.Counter.Types.HARDWARE, 1
*/
/* Deviation MISRAC2012-1 <+7> */
OS_TOOL_FUNCTION_ATTRIB_PRE
os_tick_t OS_AdvanceCounter(
	const os_counter_t *cs,
	os_counterdynamic_t *cd,
	os_tick_t adv,
	/* Possible diagnostic TOOLDIAG-1 <1> */
	os_intstatus_t is)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_alarmid_t a;
	os_alarmdynamic_t *ad;
	os_tick_t returnTicks = 0;

	/* Add the number-of-ticks-to-advance to the current counter value
	*/
	cd->current = OS_CounterAdd(cd->current, adv, cs->maxallowedvalue);
	cd->error += adv;

	/* If the counter is locked, just add the no-of-ticks to the error and let the
	 * background processing take care of the alarm queue. This takes care of incrementing
	 * software counter in a high-priority interrupt while it is being incremented in a
	 * task or lower-priority interrupt.
	*/
	if ( cd->lock == 0u )
	{
		cd->error = adv;
		cd->lock = 1u;

		/* Head alarm in queue (if any)
		*/
		a = cd->head;

		while (a != OS_NULLALARM)
		{
			ad = OS_alarmTableBase[a].dynamic;

			if (ad->delta > cd->error)
			{
				/* There is an alarm remaining in the queue. Subtract the leftover error
				 * error from its delta and exit the while loop.
				*/
				ad->delta -= cd->error;
				returnTicks = ad->delta;
				a = OS_NULLALARM; /* no need to go further */
			}
			else
			{
				/* Remember the alarm and detach it from the queue
				*/
				cd->head = ad->next;
				ad->next = OS_NULLALARM;

				/* Subtract the alarm's delta from our running error
				*/
				cd->error -= ad->delta;

				/* If the alarm is periodic, requeue it. Otherwise set it
				* to IDLE
				*/
				ad->delta = ad->period;
				if ( ad->delta == 0u )
				{
					/* Nonperiodic
					*
					* !LINKSTO Kernel.API.Alarms.SetRelAlarm.SingleAlarm, 1
					* !LINKSTO Kernel.API.Alarms.SetAbsAlarm.SingleAlarm, 1
					*/
					ad->inUse = OS_ALARM_IDLE;
				}
				else
				{
					/* Periodic
					*
					* !LINKSTO Kernel.API.Alarms.SetRelAlarm.CyclicAlarm, 1
					* !LINKSTO Kernel.API.Alarms.SetAbsAlarm.CyclicAlarm, 1
					*/
					OS_EnqueueAlarmNoAdjust(cd, a, ad);
				}

				/* Now perform the alarm's action. Interrupts are enabled first because
				 * the wrappers expect this. The alarm and the counter are in a consistent
				 * state, apart from the hardware timer, but updating the timer is
				 * inhibited by the lock flag.
				*/
				OS_IntRestore(is);
				/* Deviation MISRAC2012-2 <+1> */
				(OS_alarmTableBase[a].wrapper)(&OS_alarmTableBase[a]);
				(void) OS_IntDisable();	/* Old level discarded */

				/* New head alarm in queue (if any)
				*/
				a = cd->head;
			}
		} /* while (a != OS_NULLALARM) */

		/* Set the error to zero. If there's an alarm in the queue we had accounted
		 * for the error. If not, we don't want any leftover error upsetting future
		 * SetxxxAlarm calls.
		*/
		cd->error = 0;

		/* Finally, unlock the counter
		*/
		cd->lock = 0u;
	}

	return returnTicks;
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
