/* Mk_k_bjqappend.c
 *
 * This file contains the MK_BjqAppend() function from the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 18.4 (advisory)
 *  The +, -, += and -= operators should not be applied to an expression of
 *  pointer type.
 *
 * Reason:
 *  Pointers are used here for efficiency. The boundary values are pre-calculated constants.
*/
#include <public/Mk_public_types.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_panic.h>
#include <public/Mk_error.h>

/* MK_BjqAppend() - append a "big" job to the end of the job queue
 *
 * Preconditions:
 *	- interrupts are disabled
 *	- the queue is not full (count < length)
 *	- the job size is greater 0 (size > 0)
 *
 * Postconditions:
 *	- free is one more than on entry (if > limit, base)
 *	- count is one more than on entry
 *
 * !LINKSTO Microkernel.Function.MK_BjqAppend, 1
 * !doctype src
*/
mk_boolean_t MK_BjqAppend(mk_jobqueue_t *jq, const mk_jobelement_t *job, mk_objquantity_t size)
{
	mk_jobelement_t *dest;
	mk_objquantity_t i;
	mk_boolean_t success = MK_FALSE;

	if ( jq->count < jq->length )
	{
		dest = jq->nextFree;

		if ( jq->nextFree >= jq->limit )
		{
			jq->nextFree = jq->base;
		}
		else
		{
			/* Deviation MISRAC2012-1 */
			jq->nextFree += jq->size;
		}

		jq->count++;

		for ( i = 0; i < size; i++ )
		{
			dest[i] = job[i];
		}

		success = MK_TRUE;
	}
	else
	{
		/* This job queue is full (or a panic was triggered above),
		 * so we do nothing and return MK_FALSE.
		*/
	}

	return success;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
