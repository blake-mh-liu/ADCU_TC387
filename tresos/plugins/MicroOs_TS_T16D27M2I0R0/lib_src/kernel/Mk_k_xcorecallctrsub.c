/* Mk_k_xcorecallctrsub.c
 *
 * This file contains the function MK_XcoreCallCtrSub().
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
#include <private/Mk_ctrsub.h>
#include <public/Mk_error.h>


/* MK_XcoreCallCtrSub() - starts a counter subsystem call on request from another core.
 *
 * !LINKSTO Microkernel.Function.MK_XcoreCallCtrSub, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_XcoreCallCtrSub(mk_kernelcontrol_t *coreVars, mk_msgptr_t msg, mk_objectid_t fromCore)
{
	if (!MK_AddXcoreCtrSubJob(coreVars, msg, fromCore))
	{
		/* The job queue was full!
		 * We send a reply telling the caller to repeat the request.
		 * With any luck it will work next time.
		*/
		mk_parametertype_t reply[MK_MSG_MAXPARAM];

		reply[0] = MK_E_TRYAGAIN;
		reply[1] = 0u;
		reply[2] = 0u;
		reply[3] = 0u;
		(void)MK_SendMessage(coreVars, fromCore, MK_xcore_Reply, msg->callerCookie, reply);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
