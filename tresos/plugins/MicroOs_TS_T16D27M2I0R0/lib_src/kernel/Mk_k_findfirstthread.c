/* Mk_k_findfirstthread.c
 *
 * This file contains the function MK_FindFirstThread().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* MK_FindFirstThread()
 *
 * Returns the first thread in the thread queue that matches the specified object type and is not in
 * the state ignoreState.
 * If no such thread is in the queue, MK_NULL is returned.
 *
 * !LINKSTO Microkernel.Function.MK_FindFirstThread, 1
 * !doctype src
*/
mk_thread_t *MK_FindFirstThread(mk_thread_t *head, mk_objecttype_t objtype, mk_threadstate_t ignoreState)
{
	mk_thread_t *thread = head;

	/* Loop stops at first thread not in ignoreState that matches objType, or at end of list
	 * if no matching thread is found.
	*/
	while ( (thread != MK_NULL) && ((thread->objectType != objtype) || (thread->state == ignoreState)) )
	{
		thread = thread->next;
	}

	return thread;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
