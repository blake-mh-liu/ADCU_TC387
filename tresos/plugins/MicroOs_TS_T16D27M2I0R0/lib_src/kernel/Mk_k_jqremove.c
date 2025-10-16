/* Mk_k_jqremove.c
 *
 * This file contains the MK_JqRemove() function from the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <private/Mk_jobqueue.h>
#include <private/Mk_panic.h>
#include <public/Mk_error.h>

/* MK_JqRemove() - remove the next simple job from a job queue and return it.
 *
 * Precondition:
 *	the jobqueue parameter is not NULL
 *
 * Postconditions:
 *	- queue was empty -> no change
 *	- queue was not empty -> next is one more than on entry (if > limit, base)
 *	- queue was not empty -> count is one less than on entry
 *
 * Note: there is no error checking for a NULL job queue; the caller guarantees that is is not NULL.
 *
 * !LINKSTO Microkernel.Function.MK_JqRemove, 1
 * !doctype src
*/
mk_jobid_t MK_JqRemove(mk_jobqueue_t *jq)
{
	mk_jobid_t job = MK_NOJOB;

	if ( jq->count == 0 )
	{
		/* This job queue is empty, so we return MK_NOJOB, to indicate, that there are no jobs. */
		job = MK_NOJOB;
	}
	else
	{
		job = (mk_jobid_t)*jq->next;

		if ( jq->next >= jq->limit )
		{
			jq->next = jq->base;
		}
		else
		{
			jq->next++;
		}

		jq->count--;
	}

	return job;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
