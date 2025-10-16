/* Mk_k_increasepriority.c
 *
 * This file contains the function MK_IncreasePriority().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* MK_IncreasePriority()
 *
 * This function adjusts the priority of the thread referenced by the parameter target so that
 * the priority is at least as high as the provided minimum priority (minPrio) and minimum lock
 * level (minLevel).
 *
 * If the priority gets changed, the interrupt level is also adjusted and the thread gets
 * dequeued and requeued (unless it is already at the queue head).
 *
 * !LINKSTO Microkernel.Function.MK_IncreasePriority, 1
 * !doctype src
*/
void MK_IncreasePriority(mk_thread_t **head, mk_thread_t *target, mk_threadprio_t minPrio, mk_hwlocklevel_t minLevel)
{
	mk_thread_t **pred;		/* (Address of) predecessor's next */
	mk_thread_t *succ;		/* Successor (of pred) */

	if ( target->currentPriority < minPrio )
	{
		target->currentPriority = minPrio;
		MK_HwSetIntLevel(target->regs, minLevel);

		if ( target != *head )
		{
			/* Target is not at head of queue.
			*/
			pred = head;
			succ = *pred;
			do
			{
				pred = &succ->next;		/* Walk along the thread queue. */
				succ = *pred;

				if ( succ == target )
				{
					/* Found the target thread.
					*/
					*pred = succ->next;			/* Remove target from queue. */
					break;						/* Terminate the loop. */
				}
			} while ( succ != MK_NULL );

			MK_RequeueThread(head, target);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
