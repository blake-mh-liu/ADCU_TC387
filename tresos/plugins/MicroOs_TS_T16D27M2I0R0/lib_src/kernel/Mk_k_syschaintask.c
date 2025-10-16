/* Mk_k_syschaintask.c
 *
 * This file contains the MK_SysChainTask() function.
 *
 * This function is called by the system call function whenever the ChainTask system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>

/*
 * MK_SysChainTask() terminates the caller and activates a new task.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "ChainTask" system call. As with all system calls, the parameters are obtained from
 * the current thread's register context.
 *
 * Note: ChainTask *never* returns to the caller, so the current thread is terminated
 * no matter what happens.
 *
 * !LINKSTO Microkernel.Function.MK_SysChainTask, 1
 * !doctype src
*/
void MK_SysChainTask(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t taskIdRaw = MK_HwGetParameter1(caller->regs);
	mk_parametertype_t taskId = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, taskIdRaw);
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_hwlocklevel_t lockLevel;
	mk_objectid_t callerApp;
	mk_parametertype_t p[MK_MAXPARAMS];

	/* If the caller is a task, decrement the activation counter
	*/
	if ( caller->objectType == MK_OBJTYPE_TASK )
	{
		MK_taskCfg[caller->currentObject].dynamic->activationCount--;
	}

	callerApp = caller->applicationId;

	/* Dequeue the caller (current thread) from the head of the thread queue.
	 * (Precondition for MK_TerminateThread())
	*/
	coreVars->threadQueueHead = caller->next;
	caller->next = MK_NULL;

	/* Terminate the thread
	*/
	lockLevel = MK_HwGetIntLevel(caller->regs);
	MK_HwFreeThreadRegisters(caller->regs);
	MK_TerminateThread(coreVars, caller, lockLevel);

	/* Explicit cast to prevent compiler warning (ok, as the number of tasks is always >= 0).
	*/
	if ( taskId < (mk_parametertype_t)MK_nTasks )
	{
		/* The cross-core portion is performed asynchronously, because the caller has terminated and is not
		 * expecting a return value. MK_xcore_AsyncChainTask is used as the cross-core message
		 * so that error handling gets the correct service ID.
		*/
		errorCode = MK_InternActivateTask(coreVars, (mk_objectid_t)taskId, MK_xcore_AsyncChainTask, callerApp);
	}
	else
	{
		errorCode = MK_eid_InvalidTaskId;
	}

	/* There's no need to set a return value; the calling thread has terminated.
	*/
	if ( errorCode >= MK_eid_FirstError )
	{
		/* The culprit has been terminated so is no longer valid. Construct the parameter array.
		*/
		p[0] = taskIdRaw;
		p[1] = MK_PARAMETERTYPE_INVALID;
		p[2] = MK_PARAMETERTYPE_INVALID;
		p[3] = MK_PARAMETERTYPE_INVALID;
		(void)MK_InternReportError(coreVars, MK_sid_ChainTask, errorCode, MK_NULL, p);
	}

	/* The calling thread has been terminated. If there are no more threads
	 * the problem needs to be handled.
	 * This is now checked unconditionally because the chained task could be on another core.
	*/
	if ( coreVars->threadQueueHead == MK_NULL )
	{
		MK_ThreadQueueEmpty();
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
