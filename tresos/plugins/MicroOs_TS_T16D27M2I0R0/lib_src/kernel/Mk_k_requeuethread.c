/* Mk_k_requeuethread.c
 *
 * This file contains the MK_RequeueThread function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>


/* MK_RequeueThread
 *
 * Insert a thread at the correct place in the thread queue. The thread is placed AFTER
 * threads with higher priority but BEFORE threads with the same or lower priority.
 *
 * Preconditions:
 *	1. the thread to be requeued (parameter) is a valid thread that is not already in the queue.
 *
 * !LINKSTO Microkernel.Function.MK_RequeueThread, 2
 * !doctype src
*/
void MK_RequeueThread(mk_thread_t **head, mk_thread_t *thread)
{
	mk_thread_t **pred_next = head;
	mk_threadprio_t threadPrio = thread->currentPriority;

	/* Find the first thread in the queue that has a lower priority than or same priority as the thread-to-insert.
	 * Thus a newly-inserted thread gets placed *after* all higher-priority threads.
	*/
	while ( (*pred_next != MK_NULL) && ((*pred_next)->currentPriority > threadPrio) )
	{
		pred_next = &((*pred_next)->next);
	}

	/* Now we insert the thread between the predecessor and the successor.
	*/
	thread->next = *pred_next;
	*pred_next = thread;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
