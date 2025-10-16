/* Mk_k_xcoreshutdown.c
 *
 * This file contains the function MK_XcoreShutdown().
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
 *
 *
 * MISRAC2012-3) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * Enum type value needs to be stored in fixed length type for cross core messaging.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>
#include <private/Mk_shutdown.h>

/* MK_XcoreShutdown() - activate a task on request from another core.
 *
 * !LINKSTO Microkernel.Function.MK_XcoreShutdown, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_XcoreShutdown(mk_kernelcontrol_t *unused_coreVars, mk_msgptr_t msg, mk_objectid_t unused_fromCore)
{
	MK_PARAM_UNUSED(unused_coreVars);
	MK_PARAM_UNUSED(unused_fromCore);

	/* ShutdownOS() takes a parameter of type mk_uint8_t. Therefore this cast can only result in
	 * a loss of information, if internal functions are directly called. As this is not allowed
	 * we shut down independent of the parameter and ignore the possibly lost information in this
	 * case.
	*/
	/* Deviation MISRAC2012-3 <+1> */
	MK_Shutdown((mk_osekerror_t)msg->parameter[0]);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
