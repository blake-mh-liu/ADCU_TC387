/* Mk_k_systerminateself.c
 *
 * This file contains the MK_SysTerminateSelf() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 *  A project shall not contain unreachable code.
 *
 * Reason:
 *  Depending on the architecture, MK_HwIsRegisterStoreValid always evaluates to MK_TRUE.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_panic.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_message.h>

static void MK_TerminateSelfProtectionHook(mk_kernelcontrol_t *, mk_thread_t *);
static void MK_TerminateSelfCtrSub(mk_kernelcontrol_t *, mk_thread_t *);
static void MK_TerminateSelfBuiltin(mk_kernelcontrol_t *, mk_thread_t *);

/* MK_TerminateSelfProtectionHook - Terminates a ProtectionHook thread.
*/
static void MK_TerminateSelfProtectionHook(mk_kernelcontrol_t *coreVars, mk_thread_t *caller)
{
	/* If the terminated thread was the protection hook thread, the first parameter contains
	 * the protection action to perform.
	*/
	mk_parametertype_t protectionAction = MK_HwGetParameter1(caller->regs);

	/* Range check on the protection action
	*/
	if (protectionAction > (mk_parametertype_t)MK_PRO_INVALIDACTION)
	{
		protectionAction = (mk_parametertype_t)MK_PRO_INVALIDACTION;
	}

	/* Now perform this action
	*/
	(*MK_ppaFunctions[protectionAction])(coreVars);
}

/* MK_TerminateSelfCtrSub - Terminates a counter subsystem thread.
*/
static void MK_TerminateSelfCtrSub(mk_kernelcontrol_t *coreVars, mk_thread_t *caller)
{
	if ( caller->parentCore < 0 )
	{
		/* Asynchronous call - no reply needed.
		*/
	}
	else
	if ( caller->parentCore == coreVars->coreIndex )
	{
		/* Caller is on the same core --> parentThread is a pointer to the parent thread.
		 * Copy thread's return values to the parent.
		*/
		mk_thread_t *parent = caller->parentThread;

		/* Deviation MISRAC2012-1 <+1> */
		if ( MK_HwIsRegisterStoreValid(parent->regs) )
		{
			MK_HwSetReturnValue1(parent->regs, MK_HwGetParameter1(caller->regs));
			MK_HwSetReturnValue2(parent->regs, MK_HwGetParameter2(caller->regs));
		}
	}
	else
	{
#if (MK_MAXCORES > 1)
		/* Caller is on another core --> parentCookie identifies the caller.
		*/
		mk_parametertype_t reply[MK_MSG_MAXPARAM];

		reply[0] = MK_HwGetParameter1(caller->regs);
		reply[1] = MK_HwGetParameter2(caller->regs);
		reply[2] = 0u;
		reply[3] = 0u;
		(void)MK_SendMessage(coreVars, caller->parentCore, MK_xcore_Reply, caller->parentCookie, reply);
#else
		/* We can't send cross core messages in a single-core system.
		 * coreIndex or culprit's parentCore field must be corrupted.
		*/
		MK_Panic(MK_panic_CoreNotConfigured);
#endif
	}
}

/* MK_TerminateSelfBuiltin - Terminates a built-in thread.
*/
static void MK_TerminateSelfBuiltin(mk_kernelcontrol_t *coreVars, mk_thread_t *caller)
{
	/* Thread has a parent. This could mean:
	 *	- return value of thread main function needs to be returned to parent (OS threads etc.)
	 *	- AUTOSAR error code from global error status needs to be returned to parent (ErrorHook)
	 *	- return value of thread main function needs to be acted upon (ProtectionHook)
	*/
	if ( caller->objectType == MK_OBJTYPE_PROTECTIONHOOK )
	{
		MK_TerminateSelfProtectionHook(coreVars, caller);
	}
	else
	if ( (caller->objectType == MK_OBJTYPE_ERRORHOOK) || (caller->objectType == MK_OBJTYPE_TRUSTEDFUNCTION) )
	{
		/* No special action required
		*/
	}
	else
	if ( caller->objectType == MK_OBJTYPE_CTRSUB )
	{
		MK_TerminateSelfCtrSub(coreVars, caller);
	}
	else
	{
		/* What's this?
		*/
		MK_Panic(MK_panic_UnexpectedThreadWithParent);
	}
}


/*
 * MK_SysTerminateSelf() terminates the calling thread.
 *
 * This function is the kernel-side part of the "TerminateSelf()" API, which also implements
 * the TerminateTask() API.
 *
 * !LINKSTO Microkernel.Function.MK_SysTerminateSelf, 1
 * !doctype src
*/
void MK_SysTerminateSelf(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;

	if ( (caller->parentCookie == MK_NULLCOOKIE) && (caller->parentThread == MK_NULL) )
	{
		/* Thread has no parent, so it could be a task
		*/
		if ( caller->objectType == MK_OBJTYPE_TASK )
		{
			/* If the caller is a task, decrement the activation counter
			*/
			MK_taskCfg[caller->currentObject].dynamic->activationCount--;
		}
		else if (caller->objectType == MK_OBJTYPE_PROTECTIONHOOK)
		{
			/* There can be protection hooks without parents, because the parent application
			 * was terminated by TerminateApplication from another core.
			*/
			MK_TerminateSelfProtectionHook(coreVars, caller);
		}
		else
		{
			/* If this is an ISR, there is nothing to do.
			 * If this is a counter subsystem thread, a trusted function thread or an ErrorHook,
			 * whose parentThread was terminated, there's also nothing to do.
			*/
		}
	}
	else
	{
		/* Thread has a parent, so it's a built-in thread.
		*/
		MK_TerminateSelfBuiltin(coreVars, caller);
	}

	/* Terminate the current thread, if it hasn't already happened
	*/
	if ( caller->state != MK_THS_IDLE )
	{
		mk_hwlocklevel_t lockLevel;

		/* Dequeue the current thread from the head of the thread queue.
		 * (Precondition for MK_TerminateThread())
		 *
		 * The current thread *must* be at the head of the queue because nothing above activates any
		 * new threads except maybe MK_PerformProtectionAction. In that case, the terminating thread
		 * is the protection hook thread, which is the highest-priority thread in the system.
		*/
		coreVars->threadQueueHead = caller->next;
		caller->next = MK_NULL;

		/* Terminate the thread. Thread termination might need the lock level of the terminating thread,
		 * which will disappear when the registers are freed. So it is obtained here and passed as
		 * a parameter.
		*/
		lockLevel = MK_HwGetIntLevel(caller->regs);
		MK_HwFreeThreadRegisters(caller->regs);
		MK_TerminateThread(coreVars, caller, lockLevel);


		/* A thread has been terminated. If there are no more threads the problem needs to be handled.
		*/
		if ( coreVars->threadQueueHead == MK_NULL )
		{
			MK_ThreadQueueEmpty();
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
