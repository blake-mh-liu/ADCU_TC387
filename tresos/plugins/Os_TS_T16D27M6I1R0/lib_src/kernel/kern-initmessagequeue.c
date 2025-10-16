/* kern-initmessagequeue.c
 *
 * This file contains the initialization function OS_InitMessageQueues().
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
#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_InitMessageQueue()
 *
 * Initializes the message queue of the calling core.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitMessageQueue(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCore = OS_GetMyCoreId();
	os_uint_t m;
	os_uint_t p;
	os_messagequeue_t *mq;

	mq = OS_crosscoreMessageQueue_ptr[myCore];

	/* Mark queue as empty. */
	mq->fill = 0;
	mq->empty = 0;

	for (m = 0; m < OS_CROSSCORE_MESSAGE_QUEUE_SIZE; m++)
	{
		mq->messages[m].to		= OS_CORE_ID_INVALID;
		mq->messages[m].from	= OS_CORE_ID_INVALID;
		mq->messages[m].opcode	= OS_XC_OP_UnknownCall;
		/* Possible diagnostic TOOLDIAG-1 */
		mq->messages[m].result	= OS_NULL;

		for (p = 0; p < OS_MAXPARAM; p++)
		{
			/* In most cases, zero is a valid argument to a cross-core message,
			 * so we initialize them to 0xeb, which is a bit less likely to be valid.
			 * (Moreover, it is easily noticed while debugging.)
			*/
			mq->messages[m].parameter[p] = (os_paramtype_t)0xebebebebU;
		}
	}

	/* Make change of message queue state visible to other observers. */
	OS_CacheFlush(&mq->fill, sizeof(mq->fill));

	/* The message queues are initialized concurrently during startup! This causes problems if one function in
	 * OS_initFunc[] wants to communicate across cores. The receiving core might not have had a chance yet to
	 * initialize its message queue and would overwrite messages yet to be processed by that core. Bummer!
	 * This potential race-condition is prevented with a call of OS_SyncHere(), because it ensures that all cores
	 * have initialized their message queues before OS_initFunc[] is processed any further.
	 * See also ASCOS-3396 for a practical example, that cross-core communication may happen during startup.
	 */
	OS_SyncHere();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_initmessagequeue_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
