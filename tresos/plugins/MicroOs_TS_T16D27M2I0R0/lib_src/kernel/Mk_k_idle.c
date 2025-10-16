/* Mk_k_idle.c
 *
 * This file contains the function MK_Idle(). It runs in the idle thread during normal operation
 * and (with interrupts disabled) after shutdown.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: InfiniteLoop
 *   Possible infinite loop
 *
 * Reason: This is the idle loop, the endless loop is intentional.
*/

/* MK_Idle() - the kernel/s default idle loop.
 *
 * The idle thread must never return, and must always be eligible to run. That means it must never
 * terminate itself or use a blocking kernel call.
 *
 * !LINKSTO Microkernel.Function.MK_Idle, 1
 * !doctype src
*/
void MK_Idle(void)
{
	/* Possible diagnostic TOOLDIAG-1 <1> */
#pragma warning 557
	for (;;)
	{
		/* Intentional endless loop
		*/
	}
#pragma warning default
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
