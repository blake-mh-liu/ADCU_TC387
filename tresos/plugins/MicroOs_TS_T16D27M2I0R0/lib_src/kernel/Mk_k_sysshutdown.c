/* Mk_k_sysshutdown.c
 *
 * This file contains the MK_SysShutdown() function.
 *
 * This function is called by the system call function whenever the ShutdownOS system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * The system call mechanism translates parameters to fixed length type based on register size.
 * The service handler then needs to translate them back.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_thread.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_application.h>

/*
 * MK_SysShutdown() shuts down the complete system on demand.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "ShutdownOS" system call.
 *
 * !LINKSTO Microkernel.Function.MK_SysShutdown, 1
 * !doctype src
 */
void MK_SysShutdown(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;

	if (MK_IsAllowedToShutdown(caller, MK_PERMIT_SHUTDOWNOS))
	{
		/* Permission granted: do regular shutdown.
		*/
		/* Deviation MISRAC2012-1 <+1> */
		mk_osekerror_t shutdownCode = (mk_osekerror_t)MK_HwGetParameter1(caller->regs);
		MK_Shutdown(shutdownCode);
	}
	else
	{
		MK_RejectShutdown(coreVars, MK_sid_Shutdown);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
