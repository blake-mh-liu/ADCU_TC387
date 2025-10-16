/* Mk_k_localsststartcounter.c
 *
 * This file contains the function MK_LocalSstStartCounter().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_api.h>
#include <private/Mk_sst.h>

/* MK_LocalSstStartCounter() - start a SST counter
 *
 * This function initializes the counter and the optional ticker mechanism.
 * The counter value is set to the counter's modulus minus the delay,
 * the "next action" to the first action in the table and the state is set to STARTING.
 *
 * While the counter is in the STARTING state, advancing the counter causes its value to increase,
 * but no actions are performed until the first wrap-around of the counter, at which time the
 * counter's state becomes RUNNING.
 *
 * Constraints:
 *	- the first parameter "ctr" is a valid counter on the calling core. This is not checked.
 *
 * !LINKSTO Microkernel.Function.MK_LocalSstStartCounter, 1
 * !doctype src
*/
mk_errorid_t MK_LocalSstStartCounter(mk_sstcounter_t *ctr, mk_tick_t delay)
{
	mk_errorid_t err = MK_eid_Unknown;

	if ( (delay == 0u) || (delay >= ctr->counterModulus) )
	{
		err = MK_eid_InvalidSstDelta;
	}
	else if ( ctr->state == MK_SST_STOPPED )
	{
		/* Set the counter to the STARTING state. The counter can be advanced, but no actions are performed
		 * until the count rolls over the modulus, which will occur after "delay" ticks.
		*/
		ctr->currentCount = (ctr->counterModulus - delay);
		ctr->nextAction = 0;
		ctr->state = MK_SST_STARTING;

		/* Start the ticker, if there is one.
		*/
		if ( ctr->tickerId >= 0 )
		{
			MK_HwStartTicker(ctr->tickerId, ctr->reloadInterval);
		}

		err = MK_eid_NoError;
	}
	else
	{
		err = MK_eid_OsNotStopped;
	}

	return err;
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
