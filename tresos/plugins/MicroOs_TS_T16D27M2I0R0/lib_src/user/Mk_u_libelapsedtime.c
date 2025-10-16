/* Mk_u_libelapsedtime.c
 *
 * This file contains the MK_ElapsedTime() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>

/* MK_ElapsedTime() - calculates the elapsed time
 *
 * void MK_ElapsedTime(mk_time_t *elapsedTime, mk_time_t *previousTime)
 * calculates the amount of time that has elapsed since the last call to MK_ElapsedTime with the
 * same previousTime reference. The return value is calculated as a 64-bit value by calling
 * MK_DiffTime() and the variable referenced by previousTime is updated with the current time.
 *
 * !LINKSTO      Microkernel.Function.ElapsedTime, 2
 * !doctype      src
*/
void MK_ElapsedTime(mk_time_t *elapsedTime, mk_time_t *previousTime)
{
	mk_time_t currTime;

	/* Read the current time
	*/
	MK_ReadTime(&currTime);

	/* Calculate the difference and place it into the specified variable.
	*/
	MK_DiffTime(elapsedTime, &currTime, previousTime);

	/* Update the previousTime with the currentTime
	*/
	*previousTime = currTime;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
