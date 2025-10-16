/* Mk_k_initmessagequeues.c
 *
 * This file contains the function MK_InitMessageQueues().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_basic_types.h>
#include <private/Mk_message.h>
#include <private/Mk_core.h>


/* MK_InitMessageQueues() - initialize the parts of the message queues that are allocated for
 * writing by the current core.
 *
 * !LINKSTO Microkernel.Function.MK_InitMessageQueues, 1
 * !doctype src
*/
void MK_InitMessageQueues(mk_kernelcontrol_t *coreVars)
{
	const mk_msgqueuepair_t *queuePair;
	mk_objectid_t otherCore;
	const mk_msgqueuedescriptor_t *qd;

	queuePair = MK_messageQueues[coreVars->coreIndex];

	for ( otherCore = 0; otherCore < (mk_objquantity_t)MK_MAXCORES; otherCore++ )
	{
		qd = queuePair[otherCore].input;
		if ( qd == MK_NULL )
		{
			if ( queuePair[otherCore].output != MK_NULL )
			{
				MK_StartupPanic(MK_panic_InvalidMessageQueueConfiguration);
			}
		}
		else
		{
			/* Initialize the "withdraw" pointer on my incoming queue from the other core.
			*/
			*(qd->withdraw) = qd->buffer;
			MK_HwCacheFlush(qd->withdraw, sizeof(*(qd->withdraw)));

			qd = queuePair[otherCore].output;

			if ( qd == MK_NULL )
			{
				MK_StartupPanic(MK_panic_InvalidMessageQueueConfiguration);
			}
			else
			{
				/* Initialize the "insert" pointer for my outgoing queue to the other core.
				*/
				*(qd->insert) = qd->buffer;
				MK_HwCacheFlush(qd->insert, sizeof(*(qd->insert)));
			}
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
