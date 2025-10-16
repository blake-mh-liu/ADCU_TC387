/* kern-sendmessage.c
 *
 * This file contains the implementation of the function OS_SendMessage().
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: CastDiscardsQualPtrTgtType
 *   Cast discards qualifier from pointer target type
 *
 * Reason: The casted value is used for address calculations only and the code
 *   is well-aware of the volatile character of the destination.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
 */
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.2 (required)
 * There shall be no dead code.
 *
 * Reason:
 * Some architectures require certain measures to ensure proper exectuion
 * flow (e.g., flushing the instruction pipeline). These measures might be
 * classified as 'dead code', even though they are vital.
 */

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>
#if (OS_N_CORES >= 3)
#include <Os_spinlock.h>
#endif

/*!
 * OS_SendMessage()
 *
 * Sends a message asynchronously to the target core 'coreId'. The message's contents is based on the
 * remaining parameters.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_SendMessage(os_coreid_t coreId, os_uint32_t opcode, os_paramtype_t volatile *result, os_paramtype_t *param)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_intstatus_t is;
	os_messagequeue_t *mq;
	os_size_t fill;
	os_size_t next;
	os_message_t *msg_ptr;
	os_boolean_t slotFree = OS_FALSE;

	/* Get the message queue descriptor of the receiving core.
	*/
	mq = OS_crosscoreMessageQueue_ptr[coreId];

	/* Wait until there's room in the queue.
	*/
	do
	{
#if (OS_N_CORES >= 3)
		is = OS_TakeInternalLock(OS_GetIntercoreMsgQueueLockIdForCore(coreId));
#else
		is = OS_IntDisable();
#endif

		/* Get the current fill index and calculate the index, where the *next* message would be put.
		 * Hence, if this call of OS_SendMessage() returns, the next call will put the next message
		 * at index 'next' into the message queue buffer, i.e. mq->messages[next].
		*/
		OS_CacheInvalidate(&mq->fill, sizeof(mq->fill));

		fill = mq->fill;
		next = ((fill + 1u) >= OS_CROSSCORE_MESSAGE_QUEUE_SIZE) ? 0u : (fill + 1u);

		OS_CacheInvalidate(&mq->empty, sizeof(mq->empty));

		/* COVPT-1 */
		if (next == mq->empty)
		{
			/* There is no room in the queue. Enable interrupts and go round again for another attempt.
			 * As soon as the core 'coreId' processes its messages, there will be new vacant slots
			 * in the message queue '*mq'.
			*/
#if (OS_N_CORES >= 3)
			OS_DropInternalLock(OS_GetIntercoreMsgQueueLockIdForCore(coreId), is);
#else
			OS_IntRestore(is);
#endif
		}
		else
		{
			/* There's room!
			*/
			slotFree = OS_TRUE;
		}
	/* COVPT-2 */
	} while ( !slotFree );

	/* Put the new message into the message buffer.
	*/
	msg_ptr			= &mq->messages[fill];
	msg_ptr->to		= coreId;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	msg_ptr->from	= OS_GetMyCoreId();
	msg_ptr->opcode	= opcode;
	/* Possible diagnostic TOOLDIAG-1 */
	msg_ptr->result	= result;

	/* COVPT-3 */
	if ( param != OS_NULL )
	{
		msg_ptr->parameter[0] = param[0];
		msg_ptr->parameter[1] = param[1];
		msg_ptr->parameter[2] = param[2];
	}

	/* Make the new message visible to receiving core.
	*/
	OS_CacheFlush(msg_ptr, sizeof(*msg_ptr));

	/* Update the fill index with the value of the next vacant slot and make it visible to receiving core.
	 * This is where the next message will be put, if OS_SendMessage() is called once again.
	*/
	mq->fill = next;
	OS_CacheFlush(&mq->fill, sizeof(mq->fill));

	/* Inform the recipient that it has a message.
	*/
	/* Deviation MISRAC2012-1 <+2> */
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	OS_NotifyCore(coreId);

#if (OS_N_CORES >= 3)
	OS_DropInternalLock(OS_GetIntercoreMsgQueueLockIdForCore(coreId), is);
#else
	OS_IntRestore(is);
#endif
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sendmessage_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
