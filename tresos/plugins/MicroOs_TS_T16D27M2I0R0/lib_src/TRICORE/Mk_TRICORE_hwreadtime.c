/* Mk_TRICORE_hwreadtime.c
 *
 * This file contains the function MK_HwReadTime() for Tricore processors with an STM.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_basic_types.h>
#include <public/Mk_public_api.h>
#include <private/TRICORE/Mk_TRICORE_stm.h>

/* MK_HwReadTime
 *
 * Places the current value of the STM (56/64 bits) into the indicated mk_time_t (64-bit) location.
 *
 * Assumptions:
 *  - None. In particular, no assumption is made about interrupts being disabled.
 *
 * Parameters: currentTime points to the mk_time_t output location
 *
 * In this function, the loop terminates when the lower-part of the STM counter is read between two
 * identical values from the upper part.
 *
 * Termination: in theory, the loop might never terminate. However, this would require a very carefully-crafted
 * interrupt, or an interrupt load so high that in practice whatever called this function would never do
 * any processing anyway.
 *
 * !LINKSTO Microkernel.TRICORE.HwTimestamp.HwReadTime, 1
 * !doctype src
*/
void MK_HwReadTime(mk_time_t *currentTime)
{
	mk_uint32_t high1;
	mk_uint32_t high2;
	mk_uint32_t low;

	do
	{
		high1 = MK_timestampStm->stm_tim6;
		low = MK_timestampStm->stm_tim0;
		high2 = MK_timestampStm->stm_tim6;
	} while ( high1 != high2 );

	currentTime->timeLo = low;
	currentTime->timeHi = high1;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
