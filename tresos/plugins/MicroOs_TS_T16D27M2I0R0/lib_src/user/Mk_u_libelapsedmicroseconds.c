/* Mk_u_libelapsedmicroseconds.c
 *
 * This file contains the MK_ElapsedMicroseconds() function.
 *
 * This function cannot be used for safety-related timing purpose in applications that are sensitive to
 * an overflow. An overflow of the 32-bit elapsed time will occur if there is a time interval of more
 * than 2**32 x N us between call to this function using a particular variable (where N is the unit size)
 * For a unit size of 100us the overflow time is just under 5 days, for 10us just under 12 hours and for 1us
 * 71 minutes.
 * An example of where an overflow could happen would be in an ECU that remains in active standby mode.
 * After leaving the standby mode, the elapsed time might indicate an interval that is less than
 * a lower limit and report an error spuriously. This will depend entirely on the duration of the
 * active standby mode.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_statustype.h>

/* MK_ElapsedMicroseconds() - calculates the elapsed time in units of 1 tick = N microseconds
 *
 * This function calculates the amount of time that has elapsed since the last call to
 * MK_ElapsedMicroseconds with the same previousTime reference. The answer is given in units
 * of N us, where N depends on the 3rd parameter, the clock factor.
 *
 * !LINKSTO      Microkernel.Function.ElapsedMicroseconds, 3
 * !doctype      src
*/
void MK_ElapsedMicroseconds(mk_uint32_t *previousTime, mk_uint32_t *elapsedTime, mk_uint16_t factor)
{
	mk_time_t currTime;
#if !MK_HAS_INT64
	mk_uint32_t rem;			/* The remainder from each stage of the division */
	mk_uint32_t temp;			/* Temporary store for intermediate values */
#endif
	mk_uint32_t timeWork;		/* The working result, in units of N us */

	/* Read the current time
	*/
	MK_ReadTime(&currTime);

	/* Convert the current time to units of N us. This is essentially a division of a 4 digit
	 * number by a single-digit number, except that the digits in this case are in base 65536.
	 * See the note at the end of the file for a detailed description of the algorithm.
	 *
	 * Note: the upper 32 bits of the (potentially) 64-bit result are not calculated because
	 * they would be discarded anyway.
	*/
#if MK_HAS_INT64
	timeWork = (mk_uint32_t)(currTime / factor);
#else
	rem = currTime.timeHi % factor;
	temp = (rem << 16) | (currTime.timeLo >> 16);
	timeWork = temp / factor;
	rem = temp % factor;
	temp = (rem << 16) | (currTime.timeLo & 0xffffu);
	timeWork = (timeWork << 16) | (temp / factor);
#endif

	/* Calculate the elapsed time and store where indicated.
	*/
	*elapsedTime = timeWork - *previousTime;

	/* Update the indicated previous time variable with the new time.
	*/
	*previousTime = timeWork;
}

/* How the division algorithm works:
 *
 * We assume that the clock factor is less than 65536 (i.e. it fits in 16 bits).
 *
 * We consider the 64-bit absolute time as a concatenation of 4 digits ABCD in base 65536
 * Thus the clock factor is a single digit F in base 65536
 *
 * The division is performed as a long division of single digits (just like in primary school).
 *
 *		    WXYZ
 *		  -------
 *		F | ABCD		F into A goes W times, remainder w.
 *			wB			F into w*10+B goes X times, remainder x.
 *			 xC			F into x*10+C goes Y times, remainder y
 *			  yD		F into y*10+D goes Z times, remainder r
 *
 * This algorithm works just as well no matter what the number base is.
 * We also notice that the first two steps (AB/F = WX remainder x) can be done by our 32-bit processor in
 * a single step, and that we can discard the result because we're only interested in the lower 32-bits
 * of the answer. We're also not interested in the final remainder, although discarding this results
 * in quite a large error if this function gets used for accumulating time.
 *
 * So the algorithm is:
 *		r = (A*base+B) % F					; (A*base)+B is simply the upper word of the 64 bit time
 *		answer = ((r*base+C) / F) * base	; first "digit" of the answer.
 *		r = (r*base+C) % F;
 *		answer = answer + (r*base+D) / F	; second "digit" of the answer.
*/

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
