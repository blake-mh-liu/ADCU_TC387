/* Mk_k_ignoreinvalidxcoremessage.c
 *
 * This file contains the function MK_IgnoreInvalidXcoreMessage().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_tool.h>
#include <private/Mk_message.h>

/* MK_IgnoreInvalidXcoreMessage() - ignore dropped cross-core messages.
 *
 * Returns without doing anything.
 *
 * !LINKSTO Microkernel.Function.MK_IgnoreInvalidXcoreMessage, 1
 * !doctype src
*/
void MK_IgnoreInvalidXcoreMessage(mk_kernelcontrol_t *unused_coreVars, mk_constmsgptr_t unused_msg)
{
	MK_PARAM_UNUSED(unused_coreVars);
	MK_PARAM_UNUSED(unused_msg);

	/* Ignored */
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
