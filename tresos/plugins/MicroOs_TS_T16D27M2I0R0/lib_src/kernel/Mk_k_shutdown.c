/* Mk_k_shutdown.c
 *
 * This file contains the MK_Shutdown() function.
 *
 * This function is called by the kernel whenever it needs to shut down.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  This function is called by MK_Panic and it could indirectly call MK_Panic again.
 *  However MK_Panic calls MK_PanicStop, if it is entered a second time.
 *  So this function can't appear more than twice on the call stack.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_CALLS]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  Shutting down consists mainly of a sequence of calls
 *  to several clear and initialization functions for different subsystems.
 *  This leads to a high CALLS value.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_isr.h>
#include <private/Mk_lock.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_systemcontrol.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_addon.h>
#include <private/Mk_application.h>

/*
 * MK_Shutdown() shuts down the entire core.
 *
 * All threads get terminated (even the idle thread).
 * Then a new idle thread gets started to run the final shutdown loop.
 * Finally the shutdown-hook thread gets started.
 *
 * !LINKSTO Microkernel.Function.MK_Shutdown, 3
 * !doctype src
*/
/* Deviation DCG-1 <+2> */
/* Deviation MISRAC2012-1 <+1> */
void MK_Shutdown(mk_osekerror_t shutdownCode)
{
	mk_thread_t *thread;
	const mk_threadcfg_t *threadConfig;
	mk_kernelcontrol_t *coreVars;

	/* Start by resetting the core variables.
	*/
	coreVars = MK_GetCoreVarsStartup();
	MK_ClearCoreVars(coreVars);

	/* Clear out all the threads apart from task and ISR threads - they're done by MK_ClearTasks()/MK_ClearIsrs().
	*/
	MK_ClearThread(coreVars->aux1Thread);
	MK_ClearThread(coreVars->aux2Thread);
	MK_ClearThread(MK_idleThread[coreVars->coreIndex]);
	MK_ClearThread(MK_errorHookThread[coreVars->coreIndex]);
	MK_ClearThread(MK_protectionHookThread[coreVars->coreIndex]);

	/* Clear out all the tasks and ISRs, including their threads.
	*/
	MK_ClearTasks(coreVars->coreIndex);
	MK_ClearIsrs(coreVars->coreIndex);

	/* Clear all the locks, especially to release their spinlock-components
	*/
	MK_ClearLocks();

	/* Reinitialize the job queues, resources, interrupts (all disabled) and applications.
	*/
	MK_JqInit(coreVars);
	MK_InitLocks(coreVars->coreIndex);
	/* Deviation MISRAC2012-1 <+1> */
	MK_InitInterrupts(coreVars->coreIndex, MK_FALSE);
	MK_InitApplications(coreVars->coreIndex);

	/* Start the shutdown thread. This initializes the thread queue.
	*/
	thread = MK_idleThread[coreVars->coreIndex];
	threadConfig = MK_shutdownThreadConfig[coreVars->coreIndex];
	/* Deviation MISRAC2012-1 <+1> */
	MK_StartThread(&coreVars->threadQueueHead, thread, threadConfig);

	/* Start the shutdown-hook thread if there is one.
	*/
	threadConfig = MK_shutdownHookThreadConfig[coreVars->coreIndex];
	if ( threadConfig != MK_NULL )
	{
		thread = MK_aux2Thread[coreVars->coreIndex];
		/* Deviation MISRAC2012-1 <+1> */
		MK_StartThread(&coreVars->threadQueueHead, thread, threadConfig);

		/* Preload the AUTOSAR error code parameter for the ShutdownHook function.
		 * The ShutdownHook expects an argument of type StatusType (uint8), so we have to truncate the value.
		 *
		 * NOTE: The cast to mk_uint8_t fixes the handling of shutdownCode for AAPCS64 (ARM64), as
		 *       that parameter is nowhere else used in a different way. If you ever change this,
		 *       make sure that AAPCS64 is still correctly supported.
		*/
		MK_HwSetParameter1(thread->regs, (mk_uint8_t)shutdownCode);
	}

	/* Set the current thread to the thread queue head to simulate a thread termination.
	 * This avoids special cases in the dispatcher.
	*/
	coreVars->currentThread = coreVars->threadQueueHead;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
