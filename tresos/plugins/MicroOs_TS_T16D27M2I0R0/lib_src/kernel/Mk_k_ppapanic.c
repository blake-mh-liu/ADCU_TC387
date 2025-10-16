/* Mk_k_ppapanic.c
 *
 * This file contains the MK_PpaPanic() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <private/Mk_core.h>
#include <private/Mk_panic.h>
#include <private/Mk_errorhandling.h>

/* MK_PpaPanic()
 *
 * !LINKSTO Microkernel.Function.MK_PpaPanic, 1
 * !doctype src
*/
void MK_PpaPanic(mk_kernelcontrol_t *unused_coreVars)
{
	MK_PARAM_UNUSED(unused_coreVars);
	MK_Panic(MK_panic_PanicFromProtectionHook);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
