/* Mk_k_panic.c
 *
 * This file contains the MK_Panic function.
 *
 * This function is called by the microkernel whenever an internal problem is detected.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
 *
 *
 * MISRAC2012-2) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  MK_Panic can call itself again indirectly via MK_Dispatch and
 *  MK_ReportProtectionFault, but this can only happen if the protection hook
 *  thread has an execution budget and exceeds it.  In the unlikely case that
 *  also the shutdown thread has and exceeded execution budget, the calls to
 *  MK_Dispatch and MK_ReportProtectionFault will result in a call to
 *  MK_PanicStop.  So there is a maximum nesting of two calls to MK_Panic
 *  possible.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_panic.h>
#include <public/Mk_error.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_core.h>

/* MK_Panic() reports kernel panics.
 *
 * In most cases it will be possible to reinitialize the thread queues enough to be able to shut
 * down the system in an orderly fashion. However, only one panic is allowed. If another occurs
 * we stop immediately.
 *
 * !LINKSTO Microkernel.Function.MK_Panic, 1
 * !doctype src
*/
/* Deviation MISRAC2012-2 */
void MK_Panic(mk_panic_t panicReason)
{
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();

	/* This function may be called from code that is used both during startup and at runtime.
	 * In case we are still in startup, we call MK_StartupPanic().
	*/
	if ( coreVars->coreState == MK_coreState_Init )
	{
		MK_StartupPanic(panicReason);
	}

	if ( coreVars->panicReason == MK_panic_None )
	{
		coreVars->panicReason = panicReason;

		/* Deviation MISRAC2012-2 <+1> */
		MK_Shutdown(MK_E_PANIC);

		/* Now dispatch! This is because this function must *never* return to the caller.
		*/
		/* Deviation MISRAC2012-2 <+1> */
		MK_Dispatch(coreVars);
	}

	MK_PanicStop(panicReason);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
