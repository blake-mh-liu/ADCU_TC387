/* Mk_k_xcorereply.c
 *
 * This file contains the function MK_XcoreReply().
 *
 * (c) Elektrobit Automotive GmbH
*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: Dir 4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
 *
 *
 * MISRAC2012-2) Deviated Rule: D4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>
#include <private/Mk_thread.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>

static mk_thread_t *MK_FindCallerFromCookie(mk_thread_t *, mk_parametertype_t);		/* MISRA *sigh* */

/* MK_FindCallerFromCookie() - search for the caller after validating the cookie.
*/
static mk_thread_t *MK_FindCallerFromCookie(mk_thread_t *head, mk_parametertype_t searchCookie)
{
	mk_thread_t *t = head;
	mk_boolean_t searching = MK_TRUE;

	do
	{
		if ( t == MK_NULL )
		{
			/* No more threads.
			*/
			searching = MK_FALSE;
		}
		else
		if ( t->xcoreReply.statusCode == (mk_parametertype_t)MK_E_WAITFORREPLY )
		{
			/* Thread is waiting (as far as we know).
			 * Is it waiting for this cookie?
			*/
			if ( t->xcoreReply.requestedValue == searchCookie )
			{
				/* Found the thread that's waiting for this cookie!
				*/
				searching = MK_FALSE;
			}
			else
			{
				/* This is not the cookie it's waiting for. Try the next thread.
				*/
				t = t->next;
			}
		}
		else
		{
			/* This thread is not waiting. Try the next thread.
			*/
			t = t->next;
		}
	} while (searching);

	return t;
}

/* MK_XcoreReply() - handle an incoming reply message for a synchronous cross-core API call.
 *
 * !LINKSTO Microkernel.Function.MK_XcoreReply, 2
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_XcoreReply(mk_kernelcontrol_t *coreVars, mk_msgptr_t msg, mk_objectid_t fromCore)
{
	mk_parametertype_t msgCookie = msg->callerCookie;
	mk_parametertype_t searchCookie = MK_GET_MSGCOOKIE_VALUE(msgCookie);
	mk_thread_t *caller;

	/* Ensure that the cookie and its inverse in the upper half are the same.
	*/
	if ( searchCookie == 0u )
	{
		/* Bad cookie.
		*/
		MK_HandleInvalidXcoreMessage(coreVars, msg);
	}
	else
	{
		if ( MK_CHECK_WAITCOOKIE(msgCookie) )
		{
			/* Find the thread that matches this cookie.
			 * The thread's xcoreReply also contains the original target core.
			*/
			caller = MK_FindCallerFromCookie(coreVars->threadQueueHead, MK_WAITCOOKIE(searchCookie, fromCore));

			if ( caller != MK_NULL )
			{
				/* Copy the message payload to the caller.
				*/
				caller->xcoreReply.statusCode = msg->parameter[0];
				caller->xcoreReply.requestedValue = msg->parameter[1];
			}
		}
		else
		{
			/* Bad cookie.
			*/
			MK_HandleInvalidXcoreMessage(coreVars, msg);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
