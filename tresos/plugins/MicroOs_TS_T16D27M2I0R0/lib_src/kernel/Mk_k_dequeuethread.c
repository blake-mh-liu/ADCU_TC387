/* Mk_k_dequeuethread.c
 *
 * This file contains the MK_DequeueThread function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>
#include <public/Mk_error.h>
#include <private/Mk_panic.h>


/* MK_DequeueThread
 *
 * Dequeue a thread that is somewhere in the thread queue. The queue must be searched
 * because the queue is a single-linked list.
 *
 * The "head" parameter is not necessarily the head of the queue; it might be the address of some
 * thread's "next" link, because it is often known that a thread is in the queue after the calling thread.
 *
 * !LINKSTO Microkernel.Function.MK_DequeueThread, 1
 * !doctype src
*/
void MK_DequeueThread(mk_thread_t **head, mk_thread_t *thread)
{
	mk_thread_t **pred_next = head;

	/* Find the given thread in the queue.
	*/
	while ( (*pred_next != thread) && (*pred_next != MK_NULL) )
	{
		pred_next = &((*pred_next)->next);
	}

	if ( *pred_next == MK_NULL )
	{
		/* Thread not found in queue.
		*/
		MK_Panic(MK_panic_ThreadNotFoundInQueue);
	}
	else
	{
		/* Now we remove the thread from the queue by linking its predecessor to its successor.
		 * The thread's "next" link is set to null.
		*/
		*pred_next = thread->next;
		thread->next = MK_NULL;
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
