/* Mk_k_sysshutdownallcores.c
 *
 * This file contains the function MK_SysShutdownAllCores().
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
#include <private/Mk_message.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_application.h>

/* On single-core systems ShutdownAllCores is an alias for ShutdownOS. See user's guide.
*/
#if (MK_MAXCORES <= 1)
#error "This file is not needed for single-core systems. Please check your makefiles."
#endif

/* MK_SysShutdownAllCores() - shut down all AUTOSAR cores
 *
 * !LINKSTO Microkernel.Function.MK_SysShutdownAllCores, 1
 * !doctype src
*/
void MK_SysShutdownAllCores(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;

	if (MK_IsAllowedToShutdown(caller, MK_PERMIT_SHUTDOWNALLCORES))
	{
		/* Permission present, so shut down.
		*/
		mk_parametertype_t p[MK_MSG_MAXPARAM];
		const mk_msgqueuepair_t *myQueueArray = MK_messageQueues[coreVars->coreIndex];
		const mk_msgqueuepair_t *queuePair;
		const mk_msgqueuedescriptor_t *queue;
		mk_objectid_t coreIndex;

		p[0] = MK_HwGetParameter1(caller->regs);
		p[1] = 0;
		p[2] = 0;
		p[3] = 0;

		for ( coreIndex = 0; coreIndex < (mk_objectid_t) MK_MAXCORES; coreIndex++ )
		{
			/* Send a "shutdown" message to each core for which we have an output queue.
			 * There's no output queue to "self", so there's no need to test the core index explicitly against
			 * the core's own index.
			*/
			queuePair = &myQueueArray[coreIndex];
			queue = queuePair->output;

			if ( queue != MK_NULL )
			{
				(void)MK_SendMessage(coreVars, coreIndex, MK_xcore_Shutdown, MK_NULLCOOKIE, p);
			}
		}

		/* Now shut myself down.
		*/
		/* Deviation MISRAC2012-1 <+1> */
		MK_Shutdown((mk_osekerror_t)p[0]);
	}
	else
	{
		MK_RejectShutdown(coreVars, MK_sid_ShutdownAllCores);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
