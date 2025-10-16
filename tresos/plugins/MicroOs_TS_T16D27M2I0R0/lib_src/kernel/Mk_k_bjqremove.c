/* Mk_k_bjqremove.c
 *
 * This file contains the MK_BjqRemove() function from the microkernel.
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
#include <private/Mk_jobqueue.h>
#include <private/Mk_panic.h>
#include <public/Mk_error.h>
#include <private/Mk_tool.h>

/* MK_BjqRemove() - remove the next "big" job from a job queue and place it where indicated.
 *
 * Parameters:
 *  - jq : The job queue from which the job shall be taken.
 *  - job: An array of type mk_jobelement_t having at least MK_BJ_MAX elements,
 *         which shall be used to store the removed job.
 *
 * Precondition:
 *	the jobqueue parameter is not NULL
 *
 * Postconditions:
 *	- queue was empty -> no change
 *	- queue was not empty -> next is one more than on entry (if > limit, base)
 *	- queue was not empty -> count is one less than on entry
 *	- the job size is greater 0 (size > 0)
 *
 * Return value:
 *	- no. of jobelements placed in buffer (0 ==> no job in queue)
 *
 * !LINKSTO Microkernel.Function.MK_BjqRemove, 2
 * !doctype src
*/
mk_objquantity_t MK_BjqRemove(mk_jobqueue_t *jq, mk_jobelement_t *job)
{
	mk_objquantity_t jSize = 0;
	mk_objquantity_t i;

	if ( jq->count == 0 )
	{
		/* This job queue is empty, so we return 0, to indicate, that there are no jobs. */
		jSize = 0;
	}
	else
	{
		mk_jobelement_t *src;
		jSize = jq->size;
		src = jq->next;

		for ( i = 0; i < jSize; i++ )
		{
			job[i] = src[i];
		}

		if ( jq->next >= jq->limit )
		{
			jq->next = jq->base;
		}
		else
		{
			/* Deviation MISRAC2012-1 */
			jq->next += jSize;
		}

		jq->count--;
	}

	return jSize;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
