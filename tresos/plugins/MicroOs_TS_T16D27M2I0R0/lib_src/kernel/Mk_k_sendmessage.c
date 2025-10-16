/* Mk_k_sendmessage.c
 *
 * This file contains the function MK_SendMessage().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 18.4 (advisory)
 *  The +, -, += and -= operators should not be applied to an expression of
 *  pointer type.
 *
 * Reason:
 *  Pointers are used here for efficiency.
 *  The boundary is checked right after the pointer has been incremented.
 *
 * MISRAC2012-2) Deviated Rule: 2.2 (required)
 *  There shall be no dead code.
 *
 * Reason:
 *  The macro MK_HwNotifyCore() might contain code, which identified as dead,
 *  but is nevertheless required to obey the hardware protocol (e.g., reading
 *  back registers of peripherals).
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
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

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>
#include <private/Mk_panic.h>
#include <public/Mk_error.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_types_forward.h>

/* MK_SendMessage() - send a message to another core
 *
 * !LINKSTO Microkernel.Function.MK_SendMessage, 1
 * !doctype src
*/
/* Deviation DCG-1 <+1> */
mk_errorid_t MK_SendMessage
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t destCore,
	mk_xcall_t opcode,
	mk_parametertype_t replyCookie,
	mk_parametertype_t const *params
)
{
	const mk_msgqueuepair_t *myQueueArray = MK_messageQueues[coreVars->coreIndex];
	const mk_msgqueuepair_t *queuePair = &myQueueArray[destCore];
	const mk_msgqueuedescriptor_t *queue = queuePair->output;
	mk_msgptr_t msg;
	mk_msgptr_t nextMsg;
	mk_int_t i;
	mk_errorid_t errorId = MK_eid_Unknown;

	if ( queue == MK_NULL )
	{
		errorId = MK_eid_CoreIsAutonomous;	/* Can't send messages to that core! */
	}
	else
	{
		mk_msgptr_t removeVal;
		mk_boolean_t queueOk = MK_FALSE;

		/* Find the place where we want to insert.
		*/
		msg = *queue->insert;

		/* Find the place where the insertion pointer will be after we've inserted.
		*/
		/* Deviation MISRAC2012-1 */
		nextMsg = (msg+1);
		if ( nextMsg > queue->limit )
		{
			nextMsg = queue->buffer;
		}

		do
		{
			/* Spin here until there's room in the queue.
			 * Do we need a timeout?
			*/
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			MK_HwCacheInvalidate(queue->withdraw, sizeof(*queue->withdraw));
			removeVal = *queue->withdraw;
			/* If the withdraw pointer is out of range, the other core corrupted its input queue.
			*/
			if (    (removeVal < queue->buffer)
				 || (    (queue->limit < removeVal)
					  || MK_MisalignedMessage(queue->buffer, removeVal)
					)
			   )
			{
				queueOk = MK_FALSE;
			}
			else
			{
				queueOk = MK_TRUE;
			}
		} while ( queueOk && (nextMsg == removeVal) );

		/* If the queue is not broken and there is room, we actually send the message.
		*/
		if ( queueOk )
		{
			msg->from = (mk_parametertype_t)coreVars->coreIndex;
			msg->opcode = (mk_parametertype_t)opcode;

			if ( replyCookie == MK_NULLCOOKIE )
			{
				/* Bake a cookie.
				*/
				coreVars->cookieGen++;
				if ( coreVars->cookieGen > MK_MAXCOOKIE )
				{
					coreVars->cookieGen = MK_MINCOOKIE;
				}
				msg->callerCookie = MK_MSGCOOKIE(coreVars->cookieGen);
			}
			else
			{
				/* Send back the reply cookie.
				*/
				msg->callerCookie = replyCookie;
			}

			for ( i = 0; i < MK_MSG_MAXPARAM; i++ )
			{
				msg->parameter[i] = params[i];
			}

			/* Make sure that the content of the message is actually written to memory.
			*/
			MK_HwCacheFlush(msg, sizeof(*msg));

			/* Signal that the message is there.
			*/
			*queue->insert = nextMsg;
			MK_HwCacheFlush(queue->insert, sizeof(*queue->insert));
			/* Deviation MISRAC2012-2 <+1> */
			MK_HwNotifyCore(destCore);

			errorId = MK_eid_NoError;
		}
		else
		{
			errorId = MK_eid_TargetCoreCorrupted;
		}
	}

	return errorId;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
