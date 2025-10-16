/* Mk_k_syscalltrustedfunction.c
 *
 * This file contains the MK_SysCallTrustedFunction() function.
 *
 * This system call provides the possibility to run a "trusted" function in its own thread.
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
*/

#include <public/Mk_public_types.h>
#include <private/Mk_trustedfunction.h>
#include <private/Mk_core.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_syscall.h>

static mk_errorid_t MK_AddTrustedFunctionJob(mk_kernelcontrol_t *, mk_objectid_t);

/* MK_AddTrustedFunctionJob() - Tell the trusted function thread to execute a certain job.
 *
 * Parameters:
 *	- coreVars     : The kernel variables.
 *	- functionIndex: The function to be performed.
 *	                 This argument is assumed to be already checked for validity.
 * Return:
 *	- MK_eid_NoError, if no error occurred.
 *	- MK_eid_TryAgain, if the job queue is full.
*/
static mk_errorid_t MK_AddTrustedFunctionJob(mk_kernelcontrol_t *coreVars, mk_objectid_t functionIndex)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_thread_t *caller = coreVars->currentThread;
	mk_thread_t *thread = coreVars->aux2Thread;
	mk_threadcfg_t *threadCfg = coreVars->tfThreadConfig;
	const mk_trustedfunctioncfg_t *tfConfig = &MK_trustedFunctionCfg[functionIndex];

	if ( thread->state == MK_THS_IDLE )
	{
		threadCfg->currentObject = functionIndex;
		/* Deviation MISRAC2012-1 */
		threadCfg->entry = (mk_threadfunc_t)tfConfig->func;
		threadCfg->name = tfConfig->name;
		threadCfg->ps = tfConfig->ps;
		threadCfg->memoryPartition = tfConfig->memoryPartition;

		/* Trusted functions always run synchronously, because the semantic is that of a
		 * function call.
		*/
		threadCfg->queuePrio = caller->currentPriority;
		threadCfg->runningPriority = caller->currentPriority;

		MK_StartChildThread(&coreVars->threadQueueHead, thread, threadCfg,
							caller, MK_NULLCOOKIE, coreVars->coreIndex);

		/* Set the thread's parameters.
		*/
		MK_HwSetParameter1(thread->regs, functionIndex);
		MK_HwSetTfParameter2(thread->regs, MK_HwGetParameter2(caller->regs));

		/* Since we always set the thread's priority, we always set its interrupt level too.
		*/
		MK_HwSetIntLevel(thread->regs, MK_HwGetIntLevel(caller->regs));

		errorCode = MK_eid_NoError;
	}
	else
	{
		mk_jobelement_t jobBuf[MK_TFJ_SIZE];

		jobBuf[MK_BJ_ID] = (mk_parametertype_t) functionIndex;
		jobBuf[MK_BJ_TYPE] = MK_OBJTYPE_TRUSTEDFUNCTION;
		jobBuf[MK_BJ_P1] = (mk_parametertype_t) MK_HwGetParameter2(caller->regs);
		jobBuf[MK_BJ_PCOOKIE] = (mk_parametertype_t)caller;

		/* The thread is not idle; we must enqueue the job.
		*/
		if ( MK_BjqAppend(thread->jobQueue, jobBuf, MK_TFJ_SIZE) )
		{
			/* Job enqueued successfully.
			*/
			errorCode = MK_eid_NoError;
		}
		else
		{
			/* The job queue is full. Tell the caller to try again.
			*/
			errorCode = MK_eid_TryAgain;
		}

		/* Now we need to adjust the priority of the trusted function thread and requeue it
		 * so that it takes precedence over the caller.
		*/
		MK_IncreasePriority(&coreVars->threadQueueHead, thread,
											caller->currentPriority, MK_HwGetIntLevel(caller->regs));
	}

	return errorCode;
}

/* MK_SysCallTrustedFunction() starts a thread to run the given "trusted" function with two parameters.
 *
 * !LINKSTO Microkernel.Function.MK_SysCallTrustedFunction, 2
 * !doctype src
*/
void MK_SysCallTrustedFunction(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t p = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_errorid_t errorCode = MK_eid_Unknown;
	const mk_trustedfunctioncfg_t *tfConfig;

	if ( ((caller == coreVars->aux1Thread) || (caller == coreVars->aux2Thread))
		 || ((caller->objectType == MK_OBJTYPE_ERRORHOOK) || (caller->objectType == MK_OBJTYPE_PROTECTIONHOOK)) )
	{
		/* This prevents the thread from filling its own job queue by repeatedly calling
		 * CallTrustedFunction() - eventually it will get "try again".
		 * A similar situation can occur if trusted functions call the counter subsystem and then
		 * the counter subsystem calls trusted functions.
		 * There isn't a use case for the counter subsystem to call a trusted function,
		 * so we break the loop here.
		 *
		 * ErrorHook and ProtectionHook mustn't call trusted functions, either,
		 * because the trusted function thread's priority must not be increased to those hooks' levels.
		*/
		errorCode = MK_eid_TFCallFromWrongContext;
	}
	else
	if ( p < (mk_parametertype_t) MK_nTrustedFunctions )
	{
		/* Convert the in-range function index to a trusted function index type.
		*/
		mk_objectid_t functionIndex = (mk_objectid_t)p;
		tfConfig = &MK_trustedFunctionCfg[functionIndex];

		if ( tfConfig->coreIndex == coreVars->coreIndex )
		{
			/* Trusted function is bound to this core.
			*/
			errorCode = MK_AddTrustedFunctionJob(coreVars, functionIndex);
		}
		else
		{
			/* The trusted function is not configured to run on this core.
			*/
			errorCode = MK_eid_TFCallFromWrongCore;
		}
	}
	else
	{
		/* Out of range index.
		*/
		errorCode = MK_eid_InvalidTrustedFunctionId;
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_CallTrustedFunction, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
