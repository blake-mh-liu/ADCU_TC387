/* Mk_k_panicstop.c
 *
 * This file contains the MK_PanicStop() function.
 *
 * This function is called by MK_Panic whenever a normal MK_Panic() is not possible.
 * Typical calls are from the startup function or from MK_Panic() for a nested panic.
 *
 * (c) Elektrobit Automotive GmbH
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: InfiniteLoop
 *   Possible infinite loop
 *
 * Reason: This is the panic-stop loop, the endless loop is intentional.
 *
 * TOOLDIAG-2) Possible diagnostic: UnusedVariable
 *   Variable 'volatilePanicReason' set but not used.
 *
 * Reason: Variable 'volatilePanicReason' exists for debugging.
 *         You can examine it in your debugger.
 *         It may avoid that MK_PanicStop is linked to the same location
 *         as another function that only consists of an endless loop.
*/

#include <private/Mk_panic.h>

/* MK_PanicStop() reports kernel panics (problems of the "cannot continue" type)
 *
 * There's really nothing we can do except sit in a loop and wait till a watchdog
 * times out, or hope that there's a debugger attached.
 *
 * !LINKSTO Microkernel.Function.MK_PanicStop, 1
 * !doctype src
*/
void MK_PanicStop(mk_panic_t panicReason)
{
	/* Possible diagnostic TOOLDIAG-2 <1> */
#pragma warning 537
	volatile mk_panic_t volatilePanicReason = panicReason;
#pragma warning default

	/* Possible diagnostic TOOLDIAG-1 <1> */
	for (;;)
	{
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
