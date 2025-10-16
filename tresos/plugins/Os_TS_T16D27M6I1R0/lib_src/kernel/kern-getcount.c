/* kern-getcount.c
 *
 * This file contains the OS_GetCount function.
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
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason: This warning depends on the OS configuration and library optimization.
 *   If there are no hardware counters (OS_EXCLUDE_HWCOUNTER), this condition is always false.
 *   If there are no software counters (OS_EXCLUDE_SWCOUNTER), this condition is always true.
 *   Otherwise this condition must be evaluated at runtime.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetCount
 *
 * The current tick value of the counter is returned.
 *
 * For software counters it is simply the "current" value.
 *
 * For hardware counters, the time elapsed on the hardware must be added to the current value
 * and any alarms that expire as a reult must be processed. If the counter is locked, the
 * current value is returned. This means that the value will reflect the state of the alarm queue.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_tick_t OS_GetCount(const os_counter_t *cs)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_tick_t count;
	os_counterdynamic_t *cd;

	cd = cs->dynamic;

	/* Possible diagnostic TOOLDIAG-1 <1> */
	if (OS_CounterIsHw(cs))
	{
		/* For a hardware counter that is not locked we need to update the counter.
		*/
		/* COVPT-1 +2 */
		/* Possible diagnostic TOOLDIAG-2 <1> */
		if (cd->lock == 0U)
		{
			OS_CtrUpdate(cs);
		}
	}

	OS_ATOMIC_ASSIGN_32(count, cd->current);

	return count;
}

#include <memmap/Os_mm_code_end.h>


/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
