/* Mk_k_sysstartos.c
 *
 * This file contains the MK_SysStartOs() function from the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_NEG_010]
 *  if statements with negated boolean expressions shall not have an else clause.
 *
 * Reason:
 *  This function first checks whether it is called under correct conditions,
 *  before it actually does its work. This condition might have an exclamation mark in it
 *  but it has no other purpose than the two following else-if conditions.
 *
 *
 * DCG-2) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
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
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_ctrsub.h>

/* MK_SysStartOs() - starts the OS
 *
 * This function handles the "StartOS" system call. It is coded as a microkernel function
 * rather than a simple OS activation because it has to terminate the calling thread.
 *
 * !LINKSTO Microkernel.Function.MK_SysStartOs, 2
 * !doctype src
*/
/* Deviation DCG-2 <+1> */
void MK_SysStartOs(mk_kernelcontrol_t *coreVars)
{
	mk_errorid_t errorId = MK_eid_Unknown;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t applicationModeRaw = MK_HwGetParameter1(caller->regs);
	mk_parametertype_t applicationMode = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, applicationModeRaw);
	mk_hwlocklevel_t lockLevel = MK_HwGetIntLevel(caller->regs);
	mk_threadprio_t priority = caller->currentPriority;
	mk_thread_t *thread = coreVars->aux1Thread;
	mk_threadcfg_t *threadCfg = coreVars->ctrsubThreadConfig;
	const mk_ctrsubservicedescriptor_t *ctrsubDescr = &MK_ctrsubService[MK_ctrsub_StartOs];
	mk_parametertype_t p[MK_MAXPARAMS];

	if ( caller->objectType == MK_OBJTYPE_TASK )
	{
		/* If the caller is a task, decrement the activation counter
		*/
		MK_taskCfg[caller->currentObject].dynamic->activationCount--;
	}

	/* Dequeue and terminate the caller, even if there is an error!
	*/
	coreVars->threadQueueHead = caller->next;
	caller->state = MK_THS_IDLE;
	caller->next = MK_NULL;
	MK_HwFreeThreadRegisters(caller->regs);
	MK_TerminateThread(coreVars, caller, lockLevel);

	/* Deviation DCG-1 <+1> */
	if ( coreVars->coreState != MK_coreState_Run )
	{
		errorId = MK_eid_CoreIsNotRunning;		/* Core has not been started for Autosar operation */
	}
	else
	if ( (applicationMode >= (mk_parametertype_t)ctrsubDescr->nObjects)
			&& (applicationMode != MK_DONOTCARE_APPMODE) )
	{
		errorId = MK_eid_OsInvalidStartMode;
	}
	else
	if ( thread->state == MK_THS_IDLE )
	{
		errorId = MK_eid_NoError;

		/* Start the counter subsystem side of StartOS. If there's a StartupHook the counter subsystem is
		 * responsible for activating it.
		*/
		/* Deviation MISRAC2012-1 */
		threadCfg->entry = (mk_threadfunc_t)MK_ctrsubService[MK_ctrsub_StartOs].ctrsubFunction;
		threadCfg->currentObject = MK_ctrsub_StartOs;

		/* The thread's priority and interrupt level are the same as the caller, which
		 * should have been at the "cat2-lock" level if the caller is "main".
		 * And if not, well, hard luck. The counter subsystem "just works" anyway.
		*/
		threadCfg->queuePrio = priority;
		threadCfg->runningPriority = priority;

		MK_StartChildThread(&coreVars->threadQueueHead, thread, threadCfg, MK_NULL, MK_NULLCOOKIE, MK_NULLPARENTCORE);
		MK_HwSetParameter1(thread->regs, applicationMode);
		MK_HwSetIntLevel(thread->regs, lockLevel);

		/* Set this core's state to "OS run" to signify that the counter subsystem has been started.
		*/
		coreVars->coreState = MK_coreState_OsRun;
	}
	else
	{
		errorId = MK_eid_StartOsWhileCtrSubBusy;		/* Core is running counter subsystem already! */
	}

	if ( errorId == MK_eid_NoError )
	{
		/* This is a valid call to StartOS, so we set the counter subsystem application mode proposed
		 * by this core and flush the cache, so other cores can read this variable.
		 * This has to be done even if this core has no counter subsystem otherwise the counter subsystem
		 * on other cores will hang.
		*/
		coreVars->ctrsubAppMode = (mk_appmodeid_t)applicationMode;
		MK_HwCacheFlush(&(coreVars->ctrsubAppMode), sizeof(mk_appmodeid_t));
	}
	else
	{
		/* The culprit has been terminated so is no longer valid. Construct the parameter array.
		*/
		p[0] = applicationModeRaw;
		p[1] = MK_PARAMETERTYPE_INVALID;
		p[2] = MK_PARAMETERTYPE_INVALID;
		p[3] = MK_PARAMETERTYPE_INVALID;
		(void)MK_InternReportError(coreVars, MK_sid_StartOs, errorId, MK_NULL, p);
	}

	/* A thread has been terminated. If there are no more threads the problem needs to be handled.
	*/
	if ( coreVars->threadQueueHead == MK_NULL )
	{
		MK_ThreadQueueEmpty();
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
