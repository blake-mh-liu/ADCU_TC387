/* Mk_k_localsstadvancecounter.c
 *
 * This file contains the function MK_LocalSstAdvanceCounter().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_public_api.h>
#include <private/Mk_sst.h>
#include <private/Mk_task.h>
#include <private/Mk_core.h>

/* Prototype to keep MISRA checkers happy.
*/
static mk_errorid_t MK_SstDoAction(const mk_sstaction_t *, mk_errorid_t);


/* MK_SstDoAction() - does the action of an expiry point
 *
 * In the cross-core case the commands are sent asynchronously.
*/
static mk_errorid_t MK_SstDoAction(const mk_sstaction_t *act, mk_errorid_t prevEid)
{
	mk_errorid_t eid = MK_eid_NoError;
	mk_objectid_t taskId = act->taskId;
	mk_uint32_t events = act->events;
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();

	if ( events == 0u )
	{
		eid = MK_InternActivateTask(coreVars, taskId, MK_xcore_AsyncActivateTask, MK_APPL_NONE);
	}
	else
	{
		eid = MK_InternSetEvent(coreVars, taskId, &MK_taskCfg[taskId], events, MK_xcore_AsyncSetEvent, MK_APPL_NONE);
	}

	if ( prevEid != MK_eid_NoError )
	{
		eid = prevEid;
	}

	return eid;
}

/* MK_LocalSstAdvanceCounter() - advance the counter and perform actions that become due.
 *
 * Advances the specified counter by a given number of ticks and performs all the events that become due as a result.
 *
 * Constraints:
 *	- the first parameter "ctr" is a valid counter on the calling core. This is not checked.
 *	- the second parameter "delta" is less than the counter's modulus.
 *	- the counter has already been initialized and started.
 *
 * !LINKSTO Microkernel.Function.MK_LocalSstAdvanceCounter, 1
 * !doctype src
*/
mk_errorid_t MK_LocalSstAdvanceCounter(mk_sstcounter_t *ctr, mk_tick_t delta)
{
	mk_errorid_t eid = MK_eid_NoError;
	mk_tick_t newCount;
	mk_objectid_t actionIndex = 0;

	/* At this point, the counter state ctr->state can't be MK_SST_STOPPED, because this is either checked by
	 * MK_SstProcessOpCode() or because MK_SstTickerInterruptHandler() is never called. The latter is true,
	 * because a ticker must be started first to trigger an interrupt.
	*/

	newCount = ctr->currentCount + delta;
	if ( newCount >= ctr->counterModulus )
	{
		/* Counter is wrapping around.
		 * Perform all the events scheduled to the end of the schedule table if the counter is running.
		 * Otherwise set it to the running state.
		*/
		if ( ctr->state == MK_SST_RUNNING )
		{
			for ( actionIndex = ctr->nextAction; actionIndex < ctr->nActions; actionIndex++ )
			{
				eid = MK_SstDoAction(&ctr->actionTable[actionIndex], eid);
			}
		}
		else
		{
			ctr->state = MK_SST_RUNNING;
		}

		/* Wrap the counter and restart the schedule table.
		*/
		newCount = newCount - ctr->counterModulus;
		ctr->nextAction = 0;
	}

	/* Now perform all events that become due up to the new counter value.
	 * If this results in all remaining events becoming due, the eventIndex will be
	 * equal to nActions, i.e. one greater than the last event. This is OK; the next
	 * and all subsequent calls will execute this loop zero times, until the counter finally
	 * wraps around, at which point the "wrap around" loop will execute zero times and the
	 * schedule table will begin from the start.
	*/
	if ( ctr->state == MK_SST_RUNNING )
	{
		for ( actionIndex = ctr->nextAction; actionIndex < ctr->nActions; actionIndex++ )
		{
			if (ctr->actionTable[actionIndex].counterValue <= newCount)
			{
				eid = MK_SstDoAction(&ctr->actionTable[actionIndex], eid);
			}
			else
			{
				break;
			}
		}
	}

	ctr->currentCount = newCount;
	ctr->nextAction = actionIndex;

	return eid;
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
