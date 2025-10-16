/* Mk_k_unknowninterrupt.c
 *
 * This file contains the function MK_UnknownInterrupt().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_types_forward.h>
#include <private/Mk_panic.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_tool.h>

/* MK_UnknownInterrupt() - called if an unconfigured interrupt occurs.
 *
 * This function is used to fill all unused entries in the vector table.
 *
 * !LINKSTO Microkernel.Function.MK_UnknownInterrupt, 2
 * !doctype src
*/
void MK_UnknownInterrupt
(	mk_kernelcontrol_t *unused_coreVars,
	mk_objectid_t unused_intnum,
	mk_hwvectorcode_t unused_vecnum
)
{
	MK_PARAM_UNUSED(unused_coreVars);
	MK_PARAM_UNUSED(unused_intnum);
	MK_PARAM_UNUSED(unused_vecnum);

	MK_Panic(MK_panic_UnexpectedInterrupt);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
