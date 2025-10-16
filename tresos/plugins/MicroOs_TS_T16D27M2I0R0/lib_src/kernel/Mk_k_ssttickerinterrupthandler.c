/* Mk_k_ssttickerinterrupthandler.c
 *
 * This file contains the function MK_SstTickerInterruptHandler().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_api.h>
#include <private/Mk_sst.h>
#include <private/Mk_tool.h>
#include <private/Mk_ctrsub.h>

/* MK_SstTickerInterruptHandler() - handle the regular ticker interrupt
 *
 * This function is attached to the software vector table as an INTERNAL interrupt handler.
 * It clears and/or reloads the hardware for the next interval.
 * Then it advances the counter by the configured number of ticks.
 *
 * Note, there's no need to check if the tickerId is valid in this function. The interrupt handler can
 * only be installed for counters that are attached to tickers.
 *
 * Constraints:
 *	- the parameter "sstIndex" is in the range 0 <= sstIndex - MK_nScheduleTables < MK_nSsts
 *	- the counter defined by "sstIndex" is configured to be hardware-driven
 *
 * !LINKSTO Microkernel.Function.MK_SstTickerInterruptHandler, 1
 * !doctype src
*/
void MK_SstTickerInterruptHandler(mk_kernelcontrol_t *unused_coreVars,
									mk_objectid_t sstIndex,
									mk_hwvectorcode_t unused_vectorCode)
{
	mk_sstcounter_t *ctr;
	mk_objectid_t sstIndexLocal = sstIndex;

	MK_PARAM_UNUSED(unused_coreVars);
	MK_PARAM_UNUSED(unused_vectorCode);

	sstIndexLocal -= MK_nScheduleTables;
	ctr = MK_sstConfigsBase[sstIndexLocal].counter;

	if (ctr->state == MK_SST_STOPPED)
	{
		/* This branch is just in case an interrupt gets latched and remains pending after a stop command.
		*/
		MK_HwStopTicker(ctr->tickerId);
	}
	else
	{
		/* This is the normal branch. Reload the ticker, then advance the counter.
		*/
		MK_HwReloadTicker(ctr->tickerId, ctr->reloadInterval);

		(void)MK_LocalSstAdvanceCounter(ctr, 1u);
	}
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
