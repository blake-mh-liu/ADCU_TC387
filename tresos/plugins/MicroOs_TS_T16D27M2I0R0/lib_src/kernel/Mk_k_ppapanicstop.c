/* Mk_k_ppapanicstop.c
 *
 * This file contains the MK_PpaPanicStop() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <private/Mk_core.h>
#include <private/Mk_panic.h>
#include <private/Mk_errorhandling.h>

/* MK_PpaPanicStop()
 *
 * !LINKSTO Microkernel.Function.MK_PpaPanicStop, 1
 * !doctype src
*/
void MK_PpaPanicStop(mk_kernelcontrol_t *unused_coreVars)
{
	MK_PARAM_UNUSED(unused_coreVars);
	MK_PanicStop(MK_panic_PanicFromProtectionHook);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
