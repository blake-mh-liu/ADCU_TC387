/* Mk_k_jqappend.c
 *
 * This file contains the MK_JqAppend() function from the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_panic.h>
#include <public/Mk_error.h>

/* MK_JqAppend() - append a simple job to the end of the job queue
 *
 * Preconditions:
 *	- interrupts are disabled
 *	- the queue is not full (count < length)
 *
 * Postconditions:
 *	- free is one more than on entry (if > limit, base)
 *	- count is one more than on entry
 *
 * !LINKSTO Microkernel.Function.MK_JqAppend, 1
 * !doctype src
*/
void MK_JqAppend(mk_jobqueue_t *jq, mk_jobid_t job)
{
	if ( jq->count >= jq->length )
	{
		MK_Panic(MK_panic_JobQueueIsFull);
	}
	else
	{
		*jq->nextFree = (mk_jobelement_t) job;

		if ( jq->nextFree >= jq->limit )
		{
			jq->nextFree = jq->base;
		}
		else
		{
			jq->nextFree++;
		}

		jq->count++;
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
