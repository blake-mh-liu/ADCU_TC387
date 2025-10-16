/* Mk_k_handlemessagesfrom.c
 *
 * This file contains the function MK_HandleMessagesFrom().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * Enum type value needs to be stored in fixed length type for cross core messaging.
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: NoSideEffectsInSizeOfParam
 *   Side effects not allowed in operand of sizeof operator
 *
 * Reason: This is a false positive that sometimes gets generated when
 * dereferencing a pointer to a volatile variable given as a parameter to
 * sizeof. Since sizeof only looks at the type of the expression, this is not
 * an issue.
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_VOCF]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function handles message queues and has to perform multiple sanity checks
 *  before a message can be processed further. In case of error an error handler
 *  is called. These sanity checks with nested calls to the error handler
 *  look similar and cause the high VOCF value.
 *
 *
 * DCG-2) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
*/
/* Deviation DCG-1 <*> */

#include <public/Mk_basic_types.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_message.h>
#include <public/Mk_error.h>
#include <private/Mk_panic.h>
#include <private/Mk_errorhandling.h>


/* MK_HandleMessagesFrom() - handle queued cross-core messages from a specified queue.
 *
 * There are two options here:
 *	1. we can handle all the queued messages in one go
 *	2. we can handle one queued message and leave the rest until later.
 *
 * Option (1) is better in terms of raw speed, but option (2) might give a more even distribution.
 * Let's go with option 1 for now.
 *
 * !LINKSTO Microkernel.Function.MK_HandleMessagesFrom, 1
 * !doctype src
*/
/* Deviation DCG-2 <+1> */
mk_objquantity_t MK_HandleMessagesFrom
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t fromCore,
	const mk_msgqueuepair_t *queuePair
)
{
	mk_objquantity_t nMsg = 0;
	const mk_msgqueuedescriptor_t *inputQ = queuePair->input;
	mk_msgptrfield_t *rem = inputQ->withdraw;
	mk_msgptrfield_t *ins = inputQ->insert;
	mk_msgptr_t insert;
	mk_msgptr_t msg;
	mk_xcall_t op;

	/* The insert pointer is written by another core, so make sure we get the current content. */
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	MK_HwCacheInvalidate(ins, sizeof(*ins));
	insert = *ins;

	/* Repeat this loop until the queue is empty.
	*/
	while ( *rem != insert )
	{
		if (    (insert < inputQ->buffer)
			 || (    (inputQ->limit < insert)
			      || MK_MisalignedMessage(inputQ->buffer, insert)
				)
		   )
		{
			/* The insertion pointer of this queue is invalid.
			 * Call the InvalidXcoreMessage handler with MK_NULL and stop this loop.
			*/
			MK_HandleInvalidXcoreMessage(coreVars, MK_NULL);
			break;
		}

		/* Dereference the pointer to give a local pointer-to-message.
		 * We work on this message locally and only update the message queue at the end.
		*/
		msg = *rem;
		/* Make sure the current content of the message is read.
		*/
		MK_HwCacheInvalidate(msg, sizeof(*msg));

		if ( ((mk_objectid_t)msg->from) == fromCore )
		{
			/* Deviation MISRAC2012-1 <+1> */
			op = (mk_xcall_t)msg->opcode;

			if ( ((mk_unsigned_t)op) <= ((mk_unsigned_t)MK_MAX_OPCODE) )
			{
				(*MK_xcallTable[op])(coreVars, msg, fromCore);
			}
			else
			{
				MK_HandleInvalidXcoreMessage(coreVars, msg);
			}
		}
		else
		{
			MK_HandleInvalidXcoreMessage(coreVars, msg);
		}

		/* Move the pointer along the buffer.
		 * When past the limit, wrap back to the start - it's a ring-buffer.
		*/
		msg++;
		if ( msg > inputQ->limit )
		{
			msg = inputQ->buffer;
		}
		*rem = msg;

		/* Make sure *rem is written to memory.
		*/
		MK_HwCacheFlush(rem, sizeof(*rem));

		/* Increment the message counter.
		*/
		nMsg++;

		/* Make sure we get the current content of *ins in the next round. */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		MK_HwCacheInvalidate(ins, sizeof(*ins));
		insert = *ins;
	}

	return nMsg;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
