/* Mk_u_libdifftime.c
 *
 * This file contains the MK_DiffTime() function for 32-bit targets.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 5.5 (required)
 * Identifiers shall be distinct from macro names.
 *
 * Reason:
 * For 64-bit targets, the function is replaced by a function like macro.
 *
 *
 * MISRAC2012-2) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * For 64-bit targets, the function is replaced by a function like macro.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>

/* MK_DiffTime() - calculates the difference between two absolute times.
 *
 * void MK_DiffTime(mk_time_t *diffTime, const mk_time_t *newTime, const mk_time_t *oldTime)
 * calculates the difference between the old time and the new time (*oldTime - *newTime) and
 * places the result in the referenced result variable (*diffTime).
 *
 * The calculation is arranged so that the output is written after the calculation has been
 * performed, so that the caller can save variable space by using the same location for diff
 * and old, or for diff and new (or even for all three, though that doesn't make much sense).
 *
 * !LINKSTO      Microkernel.Function.DiffTime, 2
 * !doctype      src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_DiffTime(mk_time_t *diffTime, const mk_time_t *newTime, const mk_time_t *oldTime)
{
	/* Preliminary calculation of high-order word.
	*/
	diffTime->timeHi = newTime->timeHi - oldTime->timeHi;

	/* If the subtraction of the low-order words is going to underflow, the
	 * high-order word needs to be adjusted.
	*/
	if ( oldTime->timeLo > newTime->timeLo )
	{
		diffTime->timeHi -= 1u;
	}

	/* This might underflow. If it does, we don't care because we have already adjusted for it.
	*/
	diffTime->timeLo = newTime->timeLo - oldTime->timeLo;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
