/* Mk_k_clearthread.c
 *
 * This file contains the MK_ClearThread() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* MK_ClearThread() clears a thread and releases all allocated objects.
 *
 * Parameters:
 *	thread		- the address of the thread structure
 *
 * !LINKSTO Microkernel.Function.MK_ClearThread, 1
 * !doctype src
*/
void MK_ClearThread(mk_thread_t *thread)
{
	if ( thread != MK_NULL )
	{
		/* It is not necessary to set all members of the thread to a specific value,
		 * because these members are only needed when the thread is running and are
		 * set while the thread is setup, started, enqueued or dispatched.
		*/

		if ( thread->regs != MK_NULL )
		{
			MK_HwFreeThreadRegisters(thread->regs);
			thread->regs = MK_NULL;
		}

		thread->name = MK_NULL;
		/* next - ignored. */
		/* parentThread - ignored. */
		/* parentCookie - ignored. */
#if MK_MAXCORES > 1
		thread->xcoreReply.statusCode = 0u;
		thread->xcoreReply.requestedValue = 0u;
#endif
		/* accounting - ignored. */
		thread->state = MK_THS_IDLE;
		thread->queueingPriority = 0;
		thread->runningPriority = 0;
		/* currentPriority - ignored. */
		/* lastLockTaken - ignored. */
		/* jobQueue - ignored (allocated and freed by MK_JqInit). */
		/* eventStatus - ignored. */
		thread->memoryPartition = -1;
		thread->currentObject = -1;
		thread->objectType = MK_OBJTYPE_UNKNOWN;
		thread->applicationId = -1;
		thread->parentCore = MK_NULLPARENTCORE;
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
