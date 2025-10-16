/* Mk_k_localsststopcounter.c
 *
 * This file contains the function MK_LocalSstStopCounter().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_api.h>
#include <private/Mk_sst.h>

/* MK_LocalSstStopCounter() - stop the SST counter.
 *
 * It sets the counter to STOPPED and stops the the optional ticker mechanism.
 * Other counter variables are unchanged.
 *
 * Constraints:
 *	- the parameter "ctr" is a valid counter on the calling core. This is not checked.
 *
 * !LINKSTO Microkernel.Function.MK_LocalSstStopCounter, 1
 * !doctype src
*/
mk_errorid_t MK_LocalSstStopCounter(mk_sstcounter_t *ctr)
{
	mk_errorid_t err = MK_eid_Unknown;

	if ( ctr->state == MK_SST_STOPPED )
	{
		err = MK_eid_OsNotRunning;
	}
	else
	{
		ctr->state = MK_SST_STOPPED;

		/* Stop the ticker if there is one.
		*/
		if ( ctr->tickerId >= 0 )
		{
			MK_HwStopTicker(ctr->tickerId);
		}

		err = MK_eid_NoError;
	}

	return err;
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
