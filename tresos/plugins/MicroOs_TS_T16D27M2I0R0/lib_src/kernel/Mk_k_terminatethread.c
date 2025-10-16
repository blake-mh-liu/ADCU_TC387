/* Mk_k_terminatethread.c
 *
 * This file contains the MK_TerminateThread() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *  Conversions shall not be performed between a pointer to a function and
 *  any other type.
 *
 * Reason:
 *  This conversion is valid, because the arguments to this function aren't
 *  passed via a call, but by setting the thread's register values accordingly.
 *
 *
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 *  A project shall not contain unreachable code.
 *
 * Reason:
 *  Depending on the architecture, MK_HwIsRegisterStoreValid always evaluates to MK_TRUE.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
*/

#include <Mk_kconfig.h>
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>
#include <private/Mk_lock.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_task.h>
#include <private/Mk_isr.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_panic.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_trustedfunction.h>

static void MK_StartCtrSubJob(mk_kernelcontrol_t *, mk_thread_t *, mk_hwlocklevel_t, const mk_jobelement_t *);
static void MK_StartTfJob(mk_kernelcontrol_t *, mk_thread_t *, mk_hwlocklevel_t, const mk_jobelement_t *);
static void MK_TerminateBigJob(mk_kernelcontrol_t *, mk_thread_t *, mk_hwlocklevel_t);

/* MK_StartCtrSubJob - Restarts the counter subsystem thread to run job 'jBuf'.
*/
static void MK_StartCtrSubJob(mk_kernelcontrol_t *coreVars, mk_thread_t *thread,
								mk_hwlocklevel_t lockLevel, const mk_jobelement_t *jBuf)
{
	mk_threadcfg_t *threadCfg;
	mk_objectid_t jobParentCore;
	mk_parametertype_t jobParentCookie;
	mk_thread_t *jobParentThread;

	threadCfg = coreVars->ctrsubThreadConfig;
	/* Deviation MISRAC2012-1 */
	threadCfg->entry = (mk_threadfunc_t)MK_ctrsubService[jBuf[MK_BJ_ID]].ctrsubFunction;

	/* The thread's priority and interrupt level are retained.
	*/
	threadCfg->queuePrio = thread->currentPriority;
	threadCfg->runningPriority = thread->currentPriority;

	if (jBuf[MK_BJ_TYPE] == (mk_jobelement_t)MK_OBJTYPE_CTRSUBISR)
	{
		/* We actually execute the handler of a CTRSUBISR. Update type and id accordingly.
		*/
		threadCfg->objectType = MK_OBJTYPE_CTRSUBISR;
		threadCfg->currentObject = (mk_objectid_t) jBuf[MK_BJ_P2];
	}
	else
	{
		threadCfg->currentObject = (mk_objectid_t)jBuf[MK_BJ_ID];
	}

	jobParentCookie = jBuf[MK_BJ_PCOOKIE];
	jobParentCore = (mk_objectid_t) jBuf[MK_BJ_PCORE];
	if (jobParentCore == coreVars->coreIndex)
	{
		jobParentThread = (mk_thread_t *) jobParentCookie;
		jobParentCookie = MK_NULLCOOKIE;
	}
	else
	{
		/* The parent core is either another core or NULLPARENTCORE.
		 * In both cases, there is no parent thread on this core.
		*/
		jobParentThread = MK_NULL;
	}

	MK_StartChildThread(&coreVars->threadQueueHead, thread, threadCfg,
						jobParentThread, jobParentCookie, jobParentCore);
	MK_HwSetParameter1(thread->regs, jBuf[MK_BJ_P1]);
	MK_HwSetParameter2(thread->regs, jBuf[MK_BJ_P2]);
	MK_HwSetParameter3(thread->regs, jBuf[MK_BJ_P3]);
	MK_HwSetIntLevel(thread->regs, lockLevel);

	/* Reset object type to CTRSUB. May be clobbered if we executed an CTRSUBISR.
	*/
	threadCfg->objectType = MK_OBJTYPE_CTRSUB;
}

/* MK_StartTfJob - Restarts the trusted function thread to run job 'jBuf'.
*/
static void MK_StartTfJob(mk_kernelcontrol_t *coreVars, mk_thread_t *thread,
							mk_hwlocklevel_t lockLevel, const mk_jobelement_t *jBuf)
{
	mk_threadcfg_t *threadCfg = coreVars->tfThreadConfig;
	mk_objectid_t tfIndex = (mk_objectid_t)jBuf[MK_BJ_ID];
	const mk_trustedfunctioncfg_t *tfConfig = &MK_trustedFunctionCfg[tfIndex];

	threadCfg->currentObject = tfIndex;
	/* Deviation MISRAC2012-1 */
	threadCfg->entry = (mk_threadfunc_t)tfConfig->func;
	threadCfg->name = tfConfig->name;
	threadCfg->ps = tfConfig->ps;
	threadCfg->memoryPartition = tfConfig->memoryPartition;

	/* The thread's priority and interrupt level are retained.
	*/
	threadCfg->queuePrio = thread->currentPriority;
	threadCfg->runningPriority = thread->currentPriority;

	MK_StartChildThread(&coreVars->threadQueueHead, thread, threadCfg,
						(mk_thread_t *) jBuf[MK_BJ_PCOOKIE], MK_NULLCOOKIE, -1);
	MK_HwSetParameter1(thread->regs, tfIndex);
	MK_HwSetTfParameter2(thread->regs, jBuf[MK_BJ_P1]);
	MK_HwSetIntLevel(thread->regs, lockLevel);
}

/* MK_TerminateBigJob - Restarts threads having a big job queue, if the queue isn't empty.
*/
static void MK_TerminateBigJob(mk_kernelcontrol_t *coreVars, mk_thread_t *thread, mk_hwlocklevel_t lockLevel)
{
	mk_objquantity_t jSize;
	mk_jobelement_t jBuf[MK_BJ_MAX];

	jSize = MK_BjqRemove(thread->jobQueue, jBuf);

	if ( jSize > 0 )
	{
		/* There's a job - start it in the thread!
		*/
		if ( (jBuf[MK_BJ_TYPE] == (mk_jobelement_t)MK_OBJTYPE_CTRSUB) ||
			(jBuf[MK_BJ_TYPE] == (mk_jobelement_t)MK_OBJTYPE_CTRSUBISR) )
		{
			MK_StartCtrSubJob(coreVars, thread, lockLevel, jBuf);
		}
		else
		if ( jBuf[MK_BJ_TYPE] == (mk_jobelement_t)MK_OBJTYPE_TRUSTEDFUNCTION )
		{
			MK_StartTfJob(coreVars, thread, lockLevel, jBuf);
		}
		else
		{
			MK_Panic(MK_panic_UnknownJobType);
		}
	}
}

/* MK_TerminateThread() puts a thread into the idle state (without dequeueing)
 *
 * Preconditions:
 *	- the thread has already been dequeued
 *
 * !LINKSTO Microkernel.Function.MK_TerminateThread, 1
 * !doctype src
*/
/* Deviation DCG-1 <+1> */
void MK_TerminateThread(mk_kernelcontrol_t *coreVars, mk_thread_t *thread, mk_hwlocklevel_t lockLevel)
{
	/* Put thread in the idle state
	*/
	MK_TRACE_STATE_THREAD(thread->objectType, thread->currentObject, thread->name, thread->state, MK_THS_IDLE);
	thread->state = MK_THS_IDLE;

	/* Release all resources held by the thread
	*/
	if ( thread->lastLockTaken != MK_NULL )
	{
		mk_hwlocklevel_t savedLockLevel = MK_ClearLockList(thread->lastLockTaken);

		/* Deviation MISRAC2012-2 <+1> */
		if ( MK_HwIsRegisterStoreValid(coreVars->currentThread->regs) )
		{
			/* Restore interrupt lock level
			*/
			MK_HwSetIntLevel(coreVars->currentThread->regs, savedLockLevel);
		}
		thread->lastLockTaken = MK_NULL;
	}

	/* Run a hardware-specific action.
	*/
	MK_HwTerminateThreadAction(coreVars, thread, lockLevel);

	/* Re-activate the thread for the next job in the queue ...
	 * ... if there is one.
	 *
	 * If the thread has no job queue associated with it,
	 * it will only run one thread configuration per activation.
	*/
	if ( thread->jobQueue != MK_NULL )
	{
		if ( thread->objectType == MK_OBJTYPE_TASK )
		{
			mk_jobid_t job = MK_JqRemove(thread->jobQueue);

			if ( job != MK_NOJOB )
			{
				if ( MK_taskCfg[job].eventStatus == MK_NULL )
				{
					/* Basic tasks get started here
					*/
					MK_StartThread(&coreVars->threadQueueHead, thread, &MK_taskCfg[job].threadCfg);
				}
				else
				{
					/* Extended tasks get restarted here.
					 * If they are newly activated their registers have been preloaded.
					*/
					MK_SetupThread(thread, &MK_taskCfg[job].threadCfg);
					MK_EnqueueThread(&coreVars->threadQueueHead, thread);

					/* If the task used the WaitGetClearEvent system call, set the status to
					 * the dispatcher that it should do the Get and Clear parts of the API
					*/
					if ( MK_taskCfg[job].eventStatus->waitingState == MK_WAITGETCLEAR )
					{
						thread->eventStatus = MK_taskCfg[job].eventStatus;
					}

					/* Clear the task's "waiting" state; the task is no longer WAITING, it is now READY.
					*/
					MK_taskCfg[job].eventStatus->waitingState = MK_NO_WAIT;
				}
			}
		}
		else
		{
			/* Other types of thread can potentially have a "bigjob" queue.
			*/
			MK_TerminateBigJob(coreVars, thread, lockLevel);
		}
	}

	if ( thread->state == MK_THS_IDLE )
	{
		/* Set priority to zero to prevent the thread from interfering with things like error hook activation.
		*/
		thread->currentPriority = 0;
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
