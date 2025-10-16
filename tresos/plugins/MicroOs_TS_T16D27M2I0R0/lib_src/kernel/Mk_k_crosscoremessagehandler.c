/* Mk_k_crosscoremessagehandler.c
 *
 * This file contains the function MK_CrossCoreMessageHandler(). It is vectored through the highest
 * priority interrupt.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_basic_types.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_message.h>
#include <private/Mk_core.h>


/* MK_CrossCoreMessageHandler() - handle the cross-core message interrupt
 *
 * This function is designed to be used as an internal interrupt handler in the MK.
 *
 * !LINKSTO Microkernel.Function.MK_CrossCoreMessageHandler, 1
 * !doctype src
*/
void MK_CrossCoreMessageHandler
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t unused_param,
	mk_hwvectorcode_t unused_vectorCode
)
{
	const mk_msgqueuepair_t *queuePair;
	mk_objectid_t fromCore;
	mk_objquantity_t nMsg;

	MK_PARAM_UNUSED(unused_param);
	MK_PARAM_UNUSED(unused_vectorCode);

	/* Repeat the outer loop until all queues are empty. It's cheaper to do this than to
	 * return from the ISR only to discover that there's another message waiting.
	*/
	do
	{
		nMsg = 0;
		queuePair = MK_messageQueues[coreVars->coreIndex];

		MK_HwNotifyCoreClear(coreVars);

		for ( fromCore = 0; fromCore < (mk_objquantity_t)MK_MAXCORES; fromCore++ )
		{
			if ( queuePair->input != MK_NULL )
			{
				nMsg += MK_HandleMessagesFrom(coreVars, fromCore, queuePair);
			}

			queuePair++;
		}
	} while ( nMsg != 0 );
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
