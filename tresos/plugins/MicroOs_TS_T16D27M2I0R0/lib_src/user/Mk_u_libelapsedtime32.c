/* Mk_u_libelapsedtime32.c
 *
 * This file contains the MK_ElapsedTime32() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>

/* MK_ElapsedTime32() - calculates the elapsed time
 *
 * This function calculates the amount of time that has elapsed since the last
 * call to MK_ElapsedTime32 with the same previousTime reference. The return
 * value is calculated as a saturating 32-bit value by means of MK_DiffTime32()
 * and the variable referenced by previousTime is updated with the current time.
 *
 * !LINKSTO      Microkernel.Function.ElapsedTime32, 3
 * !doctype      src
*/
mk_uint32_t MK_ElapsedTime32(mk_time_t *previousTime)
{
	mk_time_t currTime;
	mk_uint32_t elapsed;

	/* Read the current time
	*/
	MK_ReadTime(&currTime);

	/* Calculate the difference and place it into the specified variable.
	*/
	elapsed = MK_DiffTime32(&currTime, previousTime);

	/* Update the previousTime with the currentTime
	*/
	*previousTime = currTime;

	return elapsed;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
