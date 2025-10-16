/* Mk_k_addxcorectrsubjob.c
 *
 * This file contains the function MK_AddXcoreCtrSubJob().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *  Conversions shall not be performed between a pointer to a function and any other type.
 *
 * Reason:
 *  This conversion is valid, because the arguments to this function aren't passed via a call, but by setting
 *  the thread's register values accordingly.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>
#include <private/Mk_thread.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_errorhandling.h>


static mk_boolean_t MK_DoAddXcoreCtrSubJob(
	mk_kernelcontrol_t *,
	mk_msgptr_t,
	mk_objectid_t,
	mk_parametertype_t,
	mk_parametertype_t);

/* MK_DoAddXcoreCtrSubJob() - Actually add the cross-core counter subsystem job.
 *
 * Parameter:
 *	- coreVars : The kernel control object of the current core.
 *	- msg      : The message that is about to be received.
 *	- fromCore : The core from which the message was sent or MK_NULLPARENTCORE for asynchronous jobs.
 *	- funcIndex: The index of the counter subsystem function. This argument is expected to be checked for
 *				 validity already.
 *	             Don't read it from msg again, because a non-lockstep core could concurrently corrupt it.
 *	- objId    : The index of the OS object. This argument is expected to be already checked for validity.
 *	             Don't read it from msg again, because a non-lockstep core could concurrently corrupt it.
 *
 * Return:
 *	MK_FALSE if "the queue was full".
 *	MK_TRUE if the message
 *		could be directly passed to the counter subsystem thread,
 *		could be added to the counter subsystem job queue,
 *		or was invalid.
*/
static mk_boolean_t MK_DoAddXcoreCtrSubJob(
	mk_kernelcontrol_t *coreVars,
	mk_msgptr_t msg,
	mk_objectid_t fromCore,
	mk_parametertype_t funcIndex,
	mk_parametertype_t objId)
{
	mk_thread_t *thread = coreVars->aux1Thread;
	mk_threadcfg_t *threadCfg = coreVars->ctrsubThreadConfig;
	const mk_ctrsubservicedescriptor_t *ctrsubDescr = &MK_ctrsubService[funcIndex];
	mk_boolean_t result = MK_TRUE;

	if ( thread->state == MK_THS_IDLE )
	{
		/* The thread is idle; we can start the job straight away.
		*/
		/* Deviation MISRAC2012-1 */
		threadCfg->entry = (mk_threadfunc_t)ctrsubDescr->ctrsubFunction;
		threadCfg->currentObject = (mk_objectid_t)funcIndex;
		threadCfg->queuePrio = coreVars->ctrsubBasePrio;
		threadCfg->runningPriority = coreVars->ctrsubBasePrio;

		MK_StartChildThread(&coreVars->threadQueueHead, thread, threadCfg,
							MK_NULL, msg->callerCookie, fromCore);

		MK_HwSetParameter1(thread->regs, objId);
		MK_HwSetParameter2(thread->regs, msg->parameter[2]);
		MK_HwSetParameter3(thread->regs, msg->parameter[3]);
	}
	else
	{
		/* The thread is not idle; we must enqueue the job.
		*/
		mk_jobelement_t jobBuf[MK_CSJ_SIZE];

		jobBuf[MK_BJ_ID] = funcIndex;
		jobBuf[MK_BJ_TYPE] = MK_OBJTYPE_CTRSUB;
		jobBuf[MK_BJ_PCOOKIE] = msg->callerCookie;
		jobBuf[MK_BJ_P1] = objId;
		jobBuf[MK_BJ_P2] = msg->parameter[2];
		jobBuf[MK_BJ_P3] = msg->parameter[3];
		jobBuf[MK_BJ_PCORE] = (mk_jobelement_t)fromCore;

		if ( MK_BjqAppend(thread->jobQueue, jobBuf, MK_CSJ_SIZE) )
		{
			/* Job enqueued successfully.
			*/
		}
		else
		{
			/* Oh woe is me! The job queue was full! What to do? What to do?
			*/
			result = MK_FALSE;
		}
	}

	return result;
}


/* MK_AddXcoreCtrSubJob() - Helper function for MK_XcoreAsyncCallCtrSub and MK_XcoreCallCtrSub.
 *
 * Parameter:
 *	- coreVars: The kernel control object of the current core.
 *	- msg     : The message that is about to be received.
 *	- fromCore: The core from which the message was sent or MK_NULLPARENTCORE for asynchronous jobs.
 *
 * Return:
 *	MK_FALSE if "the queue was full".
 *	MK_TRUE if the message
 *		could be directly passed to the counter subsystem thread,
 *		could be added to the counter subsystem job queue,
 *		or was invalid.
*/
mk_boolean_t MK_AddXcoreCtrSubJob(mk_kernelcontrol_t *coreVars, mk_msgptr_t msg, mk_objectid_t fromCore)
{
	const mk_ctrsubservicedescriptor_t *ctrsubDescr;
	mk_parametertype_t funcIndex;
	mk_parametertype_t objId;
	mk_boolean_t result = MK_TRUE;

	/* Sanity checks on the cross-core message:
	 *	- function index in range
	 *	- object index in range
	 *	- correct core
	*/
	funcIndex = msg->parameter[0];

	if ( funcIndex >= MK_N_CTRSUBCALLS )
	{
		/* Function index out of range.
		*/
		MK_HandleInvalidXcoreMessage(coreVars, msg);
	}
	else
	{
		/* Convert the in-range function index to a ctrsub index type and find the service descriptor.
		*/
		ctrsubDescr = &MK_ctrsubService[funcIndex];

		/* Range check on the object ID.
		*/
		objId = msg->parameter[1];
		if ( objId >= (mk_parametertype_t) ctrsubDescr->nObjects )
		{
			/* Object index out of range.
			*/
			MK_HandleInvalidXcoreMessage(coreVars, msg);
		}
		else
		if ( ctrsubDescr->props[objId].coreIndex == coreVars->coreIndex )
		{
			/* Correct core
			*/
			result = MK_DoAddXcoreCtrSubJob(coreVars, msg, fromCore, funcIndex, objId);
		}
		else
		{
			MK_HandleInvalidXcoreMessage(coreVars, msg);
		}
	}
	return result;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
