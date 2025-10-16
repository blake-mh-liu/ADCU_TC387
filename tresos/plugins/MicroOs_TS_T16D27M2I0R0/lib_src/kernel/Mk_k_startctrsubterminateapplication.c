/* Mk_k_startctrsubterminateapplication.c
 *
 * This file contains the MK_StartCtrSubTerminateApplication() function from the microkernel.
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
 *
 *
 * MISRAC2012-3) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * Boolean type value needs to be stored in fixed length type for communication with counter subsystem.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_errorhandling.h>

/* MK_StartCtrSubTerminateApplication() - starts the counter subsystem TerminateApplication function in its thread.
 *
 * This function is called from MK_TerminateApplication to perform the counter subsystem part of the activity.
 *
 * MK_TerminateApplication() can be called from a task or ISR that is terminating itself. It can also be
 * called as a result of the return value from the ProtectionHook(). In neither of these cases is it possible
 * to return "try again" to the caller, so the case of the counter subsystem thread's queue being full must be handled
 * differently.
 *
 * !LINKSTO Microkernel.Function.MK_StartCtrSubTerminateApplication, 1
 * !doctype src
 */
mk_errorid_t MK_StartCtrSubTerminateApplication
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t applicationId,
	mk_boolean_t restartOption
)
{
	mk_errorid_t errorId = MK_eid_Unknown;
	mk_thread_t *thread = coreVars->aux1Thread;
	mk_threadcfg_t *threadCfg = coreVars->ctrsubThreadConfig;
	mk_jobelement_t jobBuf[MK_CSJ_SIZE];

	if ( thread->state == MK_THS_IDLE )
	{
		/* Start the counter subsystem side of TerminateApplication.
		 * The counter subsystem thread runs at its base priority.
		*/
		threadCfg = coreVars->ctrsubThreadConfig;
		/* Deviation MISRAC2012-1 <+1> */
		threadCfg->entry = (mk_threadfunc_t)MK_ctrsubService[MK_ctrsub_TerminateApplication].ctrsubFunction;
		threadCfg->currentObject = MK_ctrsub_TerminateApplication;

		threadCfg->queuePrio = coreVars->ctrsubBasePrio;
		threadCfg->runningPriority = coreVars->ctrsubBasePrio;

		MK_StartChildThread(&coreVars->threadQueueHead, thread, threadCfg, MK_NULL, MK_NULLCOOKIE, MK_NULLPARENTCORE);
		MK_HwSetParameter1(thread->regs, applicationId);
		/* Deviation MISRAC2012-3 <+1> */
		MK_HwSetParameter2(thread->regs, restartOption);
		MK_HwSetIntLevel(thread->regs, MK_HWENABLEALLLEVEL);
	}
	else
	{
		/* The thread is not idle; we must enqueue the job.
		*/
		jobBuf[MK_BJ_ID] = MK_ctrsub_TerminateApplication;
		jobBuf[MK_BJ_TYPE] = MK_OBJTYPE_CTRSUB;
		jobBuf[MK_BJ_PCOOKIE] = MK_NULLCOOKIE;
		jobBuf[MK_BJ_P1] = (mk_jobelement_t)applicationId;
		/* Deviation MISRAC2012-3 <+1> */
		jobBuf[MK_BJ_P2] = (mk_jobelement_t)restartOption;
		jobBuf[MK_BJ_P3] = 0u;
		/* Deviation MISRAC2012-2 <+1> */
		jobBuf[MK_BJ_PCORE] = (mk_jobelement_t) MK_NULLPARENTCORE;

		if ( MK_BjqAppend(thread->jobQueue, jobBuf, MK_CSJ_SIZE) )
		{
			/* Job enqueued successfully.
			*/
			errorId = MK_eid_NoError;
		}
		else
		{
			/* Job queue is full. It should be possible to handle this somehow.
			*/
			MK_Panic(MK_panic_JobQueueIsFull);
		}
	}

	return errorId;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
