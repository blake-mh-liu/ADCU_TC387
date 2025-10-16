/* Mk_u_libdifftime32.c
 *
 * This file contains the MK_DiffTime32() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>

/* MK_DiffTime32() - calculates the difference between two absolute times.
 *
 * This function calculates the difference between the new time and the old time as a saturating
 * 32-bit value and returns the result. "Saturating" means that if the 64-bit difference is too
 * large to fit into 32 bits, the return value is the maximum time rather the difference
 * with underflow.
 *
 * !LINKSTO      Microkernel.Function.DiffTime32, 3
 * !doctype      src
*/
mk_uint32_t MK_DiffTime32(const mk_time_t *newTime, const mk_time_t *oldTime)
{
	mk_time_t diffTime;

	MK_DiffTime(&diffTime, newTime, oldTime);

	if ( diffTime.timeHi != 0u )
	{
		diffTime.timeLo = 0xffffffffu;
	}

	return diffTime.timeLo;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
