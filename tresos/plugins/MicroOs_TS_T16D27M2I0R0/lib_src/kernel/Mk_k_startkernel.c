/* Mk_k_startkernel.c
 *
 * This file contains the MK_StartKernel() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_CALLS]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  Starting the kernel consists mainly of a sequence of calls
 *  to several initialization functions for different subsystems.
 *  This leads to a high CALLS value.
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_lock.h>
#include <private/Mk_startup.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_memoryprotection.h>
#include <private/Mk_panic.h>
#include <private/Mk_exceptionhandling.h>
#include <private/Mk_message.h>
#include <private/Mk_sst.h>
#include <private/Mk_addon.h>


/* MK_StartKernel
 *
 * This function is called by the startup code in order to start the microkernel.
 *
 * This function should be running on the microkernel stack.
 *
 * A dummy thread is set up so that it appears that this code is running in the dummy thread.
 * One of the threads reserved for system calls to the counter subsystem is used for this.
 *
 * Then two more threads are created:
 *	- the idle thread (at priority zero)
 *	- the startup thread (at a priority higher than all tasks and ISRs)
 * Finally, the running thread terminates itself, permitting the startup thread to run.
 *
 * Preconditions:
 * - stack is the kernel stack (not really necessary, but it's the only stack that's guaranteed big enough).
 * - interrupts are disabled.
 *
 * !LINKSTO	Microkernel.Function.MK_StartKernel, 2
 * !doctype src
*/
/* Deviation DCG-1 <+1> */
void MK_StartKernel(mk_uint32_t q1, mk_uint32_t q2, mk_uint32_t q3, mk_uint32_t q4)
{
	mk_kernelcontrol_t *coreVars;
	mk_corestate_t newCoreState;

	/* Go no further if the .data and .bss sections haven't been initialized.
	*/
	MK_DataInitCheck(q1, q2, q3, q4);

	/* Check offsets of members in mk_kernelcontrol_t.
	*/
	MK_StartupCheckCoreVars();

	/* Get the core variables for this core and initialize them.
	*/
	coreVars = MK_GetCoreVarsStartup();
	MK_InitCoreVars(coreVars);

	/* Processor-specific initialization
	*/
	MK_HwInitProcessor();

	/* Initialize add-on modules
	*/
	MK_InitAddOn(coreVars);

	/* Initialize memory protection
	*/
	MK_InitMemoryProtection(coreVars);

#if MK_MAXCORES > 1
	/* Initialize the cross-core message queues.
	*/
	MK_InitMessageQueues(coreVars);
#endif

	/* Initialize execution budget monitoring
	*/
	MK_InitExecutionBudgetMonitor(coreVars);

	/* Initialize the job queues
	*/
	MK_JqInit(coreVars);

	/* Initialize lock table
	*/
	MK_InitLocks(coreVars->coreIndex);

	/* Initialize interrupt sources and handling.
	*/
	MK_InitInterrupts(coreVars->coreIndex, MK_TRUE);

	/* Initialize OS-Application handling.
	*/
	MK_InitApplications(coreVars->coreIndex);

	/* Initialize the simple schedule tables
	*/
	MK_SstInit(coreVars);

	/* Create the idle thread. No dispatch is performed so it sits in the queue.
	*/
	MK_StartThread(	&coreVars->threadQueueHead,
					MK_idleThread[coreVars->coreIndex],
					MK_idleThreadConfig[coreVars->coreIndex]);


	if ( (MK_coreProperties[coreVars->coreIndex] & MK_COREPROP_STARTMASK) == MK_COREPROP_STARTAUTO )
	{
		/* Core is marked as AutoStart, so we set the state to MK_coreState_Run.
		*/
		newCoreState = MK_coreState_Run;

		/* Create the initialization thread that runs main() (or whatever has been configured as "main").
		 * This only happens on the cores that have a configured "autostart" main. For AUTOSAR conformity,
		 * this should only be on the "master" core.
		 * All parameters to the thread are set to zero, to tell main that it has no arguments.
		 * No dispatch is performed so the thread sits in the queue.
		*/
		if ( MK_initThreadConfig[coreVars->coreIndex] != MK_NULL )
		{
			MK_StartThread(	&coreVars->threadQueueHead,
							coreVars->aux2Thread,
							MK_initThreadConfig[coreVars->coreIndex]);
			MK_HwSetParameter1(coreVars->aux2Thread->regs, 0u);
			MK_HwSetParameter2(coreVars->aux2Thread->regs, 0u);
			MK_HwSetParameter3(coreVars->aux2Thread->regs, 0u);
			MK_HwSetParameter4(coreVars->aux2Thread->regs, 0u);
		}
	}
	else
	{
		/* Core is marked as Manual Start, so we set the state to MK_coreState_Start.
		 * In this case the "main" thread is not started.
		*/
		newCoreState = MK_coreState_Startup;
	}

	/* Create a high-priority thread that will be set as "current", thus converting this
	 * executing function into a thread that can be terminated.
	*/
	MK_StartThread( &coreVars->threadQueueHead,
					coreVars->aux1Thread,
					MK_bootThreadConfig[coreVars->coreIndex]);

	/* Make the head-of-queue into the current thread and set its state to "running".
	 * This converts the running instance of this function into a thread that can be terminated.
	*/
	coreVars->currentThread = coreVars->threadQueueHead;
	coreVars->currentThread->state = MK_THS_RUNNING;

	/* Before we can terminate the newly-created thread in which we're running, the exception
	 * vectors need to be set up. This must not be done earlier because until there is a valid
	 * coreVars->currentThread the standard microkernel vectors do not work correctly.
	*/

	/* HwSetupExceptions has to take care about operations,
	 * which may only be performed by the master core
	*/
	MK_HwSetupExceptions(q3, q4, q1, q2);

	if ( ( (q1 ^ MK_ENDKEY_1) |
		   (q2 ^ MK_ENDKEY_2) |
		   (q3 ^ MK_ENDKEY_3) |
		   (q4 ^ MK_ENDKEY_4) ) == 0u )
	{

#if MK_MAXCORES > 1
		MK_SyncHere();
#endif

		coreVars->coreState = newCoreState;

		(void)MK_UsrTerminateSelf();
	}

	/* The "TerminateThread" system call above should never return. If it does we panic. This panic
	 * also covers the case where the key is not correct.
	*/
	MK_StartupPanic(MK_panic_IncorrectStartupKey);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
