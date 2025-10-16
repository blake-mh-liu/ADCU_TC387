/* Mk_k_panicinvalidxcoremessage.c
 *
 * This file contains the function MK_PanicInvalidXcoreMessage().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_tool.h>
#include <private/Mk_message.h>
#include <private/Mk_panic.h>

/* MK_PanicInvalidXcoreMessage() - panics on dropped cross-core messages.
 *
 * Panics.
 *
 * !LINKSTO Microkernel.Function.MK_PanicInvalidXcoreMessage, 1
 * !doctype src
*/
void MK_PanicInvalidXcoreMessage(mk_kernelcontrol_t *unused_coreVars, mk_constmsgptr_t unused_msg)
{
	MK_PARAM_UNUSED(unused_coreVars);
	MK_PARAM_UNUSED(unused_msg);

	MK_Panic(MK_panic_InvalidCrossCoreMessage);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
