/* Mk_k_startuppanic.c
 *
 * This file contains the MK_StartupPanic() function.
 *
 * This function is called from the startup sequence at places where a "panic" is needed
 * but the kernel is not yet fully initialized and thus MK_Panic() cannot be used.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_panic.h>
#include <private/Mk_panictailcall.h>

/* MK_StartupPanic() - reports kernel panics (problems of the "cannot continue" type) during startup
 *
 * First we call a configurable function. This is fairly harmless because the vector table
 * hasn't been initialized.
 * If the callout hasn't been enabled, or if it returns, there's really nothing we can do
 * except sit in a loop and wait till a watchdog times out, or hope that there's a debugger attached.
 * Calling MK_PanicStop does this.
 *
 * !LINKSTO Microkernel.Function.MK_StartupPanic, 1
 * !doctype src
*/
void MK_StartupPanic(mk_panic_t panicReason)
{
	if ( MK_startupPanicCallout != MK_NULL )
	{
		MK_startupPanicCallout(panicReason);
	}

	MK_PanicStopTailCall(panicReason);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
