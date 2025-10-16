/* Mk_k_localcallctrsub.c
 *
 * This file contains the MK_LocalCallCtrSub() function.
 *
 * This system call provides the possibility to run a counter subsystem function in its own thread on the local core.
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

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_VOCF]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *   The code, which sets the priorities in threadCfg, the lockLevel and the parentCore,
 *   looks repetitive, but it can hardly be moved to a new function.
 *   This is, because these variables are passed to MK_StartChildThread
 *   and the if is used to choose them correctly.
 *
 *
 * DCG-2) Deviated Rule: [OS_C_COMPL_010:HIS_STMT]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *   The code, which sets the priorities in threadCfg, the lockLevel and the parentCore,
 *   looks repetitive, but it can hardly be moved to a new function.
 *   This is, because these variables are passed to MK_StartChildThread
 *   and the if is used to choose them correctly.
 *
 *
 * DCG-3) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
*/
#include <public/Mk_public_types.h>
#include <public/Mk_ctrsubindex.h>
#include <private/Mk_core.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_message.h>

/* MK_LocalCallCtrSub() starts a thread to run the given counter subsystem function with up to three parameters.
 *
 * !LINKSTO Microkernel.Function.MK_LocalCallCtrSub, 1
 * !doctype src
*/
/* Deviation DCG-1 <+1>, DCG-2 <+1>, DCG-3 <+1> */
mk_errorid_t MK_LocalCallCtrSub
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t functionIndex,
	const mk_ctrsubservicedescriptor_t *ctrsubDescr,
	mk_parametertype_t ctrsubObjectId,
	mk_xcall_t callType
)
{
	mk_errorid_t errorId = MK_eid_Unknown;
	mk_thread_t *caller = coreVars->currentThread;
	mk_thread_t *thread;
	mk_threadcfg_t *threadCfg;
	mk_jobelement_t jobBuf[MK_CSJ_SIZE];
	mk_hwlocklevel_t lockLevel;
	mk_objectid_t parentCore;

	thread = coreVars->aux1Thread;
	threadCfg = coreVars->ctrsubThreadConfig;

	if ( caller->currentPriority > coreVars->ctrsubCallerMaxPrio )
	{
		errorId = MK_eid_OsWrongContext;
	}
	else
	if ( thread->state == MK_THS_IDLE )
	{
		/* The thread is idle; we can start the job straight away.
		 * The caller's priority controls the thread's priority.
		*/
		/* Deviation MISRAC2012-1 */
		threadCfg->entry = (mk_threadfunc_t)ctrsubDescr->ctrsubFunction;
		threadCfg->currentObject = functionIndex;

		if ( callType == MK_xcore_AsyncCallCtrSub )
		{
			/* For an asynchronous call we use the configured base priority for the counter subsystem thread.
			*/
			threadCfg->queuePrio = coreVars->ctrsubBasePrio;
			threadCfg->runningPriority = coreVars->ctrsubBasePrio;
			lockLevel = MK_HWENABLEALLLEVEL;
			parentCore = MK_NULLPARENTCORE;
		}
		else
		if ( caller->currentPriority < coreVars->ctrsubBasePrio )
		{
			/* If the caller's priority is lower than the configured lowest priority for
			 * counter subsystem threads, then use the configured lowest priority. The matching interrupt
			 * level is MK_HWENABLEALLLEVEL.
			*/
			threadCfg->queuePrio = coreVars->ctrsubBasePrio;
			threadCfg->runningPriority = coreVars->ctrsubBasePrio;
			lockLevel = MK_HWENABLEALLLEVEL;
			parentCore = coreVars->coreIndex;
		}
		else
		{
			/* If the caller's priority is higher than the configured lowest priority for
			 * counter subsystem threads (or the same), then use the caller's priority and interrupt level.
			*/
			threadCfg->queuePrio = caller->currentPriority;
			threadCfg->runningPriority = caller->currentPriority;
			lockLevel = MK_HwGetIntLevel(caller->regs);
			parentCore = coreVars->coreIndex;
		}

		/* Start the thread.
		*/
		MK_StartChildThread(&coreVars->threadQueueHead, thread, threadCfg, caller, MK_NULLCOOKIE, parentCore);

		/* Place the parameters into the thread's registers.
		*/
		MK_HwSetParameter1(thread->regs, ctrsubObjectId);
		MK_HwSetParameter2(thread->regs, MK_HwGetParameter3(caller->regs));
		MK_HwSetParameter3(thread->regs, MK_HwGetParameter4(caller->regs));
		MK_HwSetIntLevel(thread->regs, lockLevel);

		errorId = MK_eid_NoError;
	}
	else
	{
		/* The thread is not idle; we must enqueue the job.
		*/
		jobBuf[MK_BJ_ID] = (mk_jobelement_t)functionIndex;
		jobBuf[MK_BJ_TYPE] = MK_OBJTYPE_CTRSUB;
		jobBuf[MK_BJ_PCOOKIE] = (mk_jobelement_t)caller;
		jobBuf[MK_BJ_P1] = ctrsubObjectId;
		jobBuf[MK_BJ_P2] = (mk_parametertype_t) MK_HwGetParameter3(caller->regs);
		jobBuf[MK_BJ_P3] = (mk_parametertype_t) MK_HwGetParameter4(caller->regs);
		if ( callType == MK_xcore_AsyncCallCtrSub )
		{
			/* Deviation MISRAC2012-2 <+1> */
			jobBuf[MK_BJ_PCORE] = (mk_jobelement_t) MK_NULLPARENTCORE;
		}
		else
		{
			jobBuf[MK_BJ_PCORE] = (mk_jobelement_t) coreVars->coreIndex;
		}

		if ( MK_BjqAppend(thread->jobQueue, jobBuf, MK_CSJ_SIZE) )
		{
			/* Job enqueued successfully.
			*/
			if ( callType == MK_xcore_CallCtrSub )
			{
				MK_IncreasePriority(&coreVars->threadQueueHead, thread,
											caller->currentPriority, MK_HwGetIntLevel(caller->regs));
			}

			errorId = MK_eid_NoError;
		}
		else
		{
			/* The job queue was full. We return the code for "try again", but we force the
			 * priority of the counter subsystem so that it runs before control returns to the caller.
			 * Thus when the caller tries again, the call succeeds.
			*/
			errorId = MK_eid_TryAgain;

			MK_IncreasePriority(&coreVars->threadQueueHead, thread,
											caller->currentPriority, MK_HwGetIntLevel(caller->regs));
		}
	}

	return errorId;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
