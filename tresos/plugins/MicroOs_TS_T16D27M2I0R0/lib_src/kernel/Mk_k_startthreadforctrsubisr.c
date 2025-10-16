/* Mk_k_startthreadforctrsubisr.c
 *
 * This file contains the MK_StartThreadForCtrSubIsr() function.
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
 * MISRAC2012-2) Deviated Rule: 12.4 (advisory)
 * Evaluation of constant expressions should not lead to unsigned integer
 * wrap-around.
 *
 * Reason:
 * Intentional wrap-around to represent an invalid value.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_isr.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_ctrsub.h>

/* MK_StartThreadForCtrSubIsr() starts the counter subsystem thread (aux1) to run the given isr.
 *
 * If the aux1 thread is not idle, the counter subsystem ISR gets enqueued in the job queue, and the thread's
 * priority and level gets raised to the level of the ISR.
 *
 * If the aux1 thread's job queue is full, the ISR's own thread is activated (or the job gets
 * enqueued if possible). The priority and level of the aux1 thread gets raised to the level of the
 * ISR so that all the API calls are complete before the ISR runs.
 *
 * IMPORTANT: the ISR must not call the counter subsystem functions directly. It must make a microkernel call
 * to run the function in the aux1 thread (MK_UsrAsyncCallCtrSub or similar). The microkernel
 * can supply a "call counter subsystem and terminate" API to make this more efficient.
 *
 * !LINKSTO Microkernel.Function.MK_StartThreadForCtrSubIsr, 1
 * !doctype src
*/
void MK_StartThreadForCtrSubIsr
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t ctrsubIsrIndex,
	mk_hwvectorcode_t vectorCode
)
{
	const mk_isrcfg_t *isr;
	const mk_threadcfg_t *isrThreadCfg;
	mk_threadcfg_t *ctrsubThreadCfg;
	mk_thread_t *ctrsubThread;
	const mk_ctrsubservicedescriptor_t *ctrsubDescr;
	mk_jobelement_t jobBuf[MK_CSJ_SIZE];

	if ( (ctrsubIsrIndex >= 0) && (ctrsubIsrIndex < MK_nIsrs) )
	{
		mk_objectid_t counterId;

		isr = &MK_isrCfg[ctrsubIsrIndex];
		isrThreadCfg = &isr->threadCfg;
		counterId = isr->ctrsubHwCounterId;

		ctrsubThread = coreVars->aux1Thread;

		if ( ctrsubThread->state == MK_THS_IDLE )
		{
			/* The counter subsystem thread is idle. We can start the counter subsystem job directly in the thread.
			 * The counter subsystem job is always MK_ctrsub_UpdateCounter.
			*/
			ctrsubDescr = &MK_ctrsubService[MK_ctrsub_UpdateCounter];

			/* Set the function pointer
			*/
			ctrsubThreadCfg = coreVars->ctrsubThreadConfig;
			/* Deviation MISRAC2012-1 <+1> */
			ctrsubThreadCfg->entry = (mk_threadfunc_t)ctrsubDescr->ctrsubFunction;

			/* The priorities and lock level come from the ISR thread config.
			*/
			ctrsubThreadCfg->queuePrio = isrThreadCfg->queuePrio;
			ctrsubThreadCfg->runningPriority = isrThreadCfg->runningPriority;
			ctrsubThreadCfg->ps = isrThreadCfg->ps;					/* Might include the lock level */
			ctrsubThreadCfg->lockLevel = isrThreadCfg->lockLevel;

			/* Set correct object type and id for CTRSUBISR.
			*/
			ctrsubThreadCfg->objectType = MK_OBJTYPE_CTRSUBISR;
			ctrsubThreadCfg->currentObject = isrThreadCfg->currentObject;

			MK_StartThread(&coreVars->threadQueueHead, ctrsubThread, ctrsubThreadCfg);

			/* Reset object type back to counter subsystem in the counter subsystem thread config.
			*/
			ctrsubThreadCfg->objectType = MK_OBJTYPE_CTRSUB;

			/* Place the single parameter (the counter ID) in the thread's registers.
			*/
			MK_HwSetParameter1(ctrsubThread->regs, counterId);
		}
		else
		{
			jobBuf[MK_BJ_ID] = MK_ctrsub_UpdateCounter;
			jobBuf[MK_BJ_TYPE] = MK_OBJTYPE_CTRSUBISR;
			jobBuf[MK_BJ_PCOOKIE] = 0;
			jobBuf[MK_BJ_P1] = (mk_parametertype_t) counterId;
			/* Deviation MISRAC2012-2 <+1> */
			jobBuf[MK_BJ_PCORE] = (mk_jobelement_t) MK_NULLPARENTCORE;

			/* For queued CTRSUBISR activations, buffer the actual object id in P2.
			*/
			jobBuf[MK_BJ_P2] = (mk_parametertype_t) isrThreadCfg->currentObject;

			/* Unused parameter.
			*/
			jobBuf[MK_BJ_P3] = 0;

			if ( MK_BjqAppend(ctrsubThread->jobQueue, jobBuf, MK_CSJ_SIZE) )
			{
				/* Job enqueued successfully. We need to increase its priority and level.
				*/
			}
			else
			{
				if ( isr->thread->state == MK_THS_IDLE )
				{
					MK_StartThread(&coreVars->threadQueueHead, isr->thread, isrThreadCfg);
				}
				else
				{
					MK_Panic(MK_panic_UnexpectedInterrupt);
				}
			}

			/* In either case (job queued or fallback ISR started) we need to raise the priority
			 * of the counter subsystem thread.
			*/
			MK_IncreasePriority(&coreVars->threadQueueHead, ctrsubThread,
								isrThreadCfg->runningPriority, isrThreadCfg->lockLevel);
		}

	}
	else
	{
		MK_UnknownInterrupt(coreVars, ctrsubIsrIndex, vectorCode);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
