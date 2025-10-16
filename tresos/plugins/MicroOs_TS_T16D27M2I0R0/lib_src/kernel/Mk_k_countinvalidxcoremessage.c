/* Mk_k_countinvalidxcoremessage.c
 *
 * This file contains the function MK_CountInvalidXcoreMessage().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_tool.h>
#include <private/Mk_message.h>

/* MK_CountInvalidXcoreMessage() - count a dropped cross-core message.
 *
 * Counts the dropped cross-core messages, saturated.
 *
 * !LINKSTO Microkernel.Function.MK_CountInvalidXcoreMessage, 1
 * !doctype src
*/
void MK_CountInvalidXcoreMessage(mk_kernelcontrol_t *coreVars, mk_constmsgptr_t unused_msg)
{
	MK_PARAM_UNUSED(unused_msg);

	/* Increment the dropped message counter up to its maximum value.
	 * Test possibly invokes wrap-around, which is well-defined for this unsigned variable.
	*/
	if ( (coreVars->nDroppedMessages + 1u) != 0u )
	{
		coreVars->nDroppedMessages++;
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
