/* Mk_k_ppaterminatethread.c
 *
 * This file contains the MK_PpaTerminateThread() function.
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
#include <private/Mk_errorhandling.h>
#include <private/Mk_panic.h>
#include <private/Mk_task.h>
#include <private/Mk_message.h>

static void MK_ReplyForCtrSub(mk_kernelcontrol_t *, mk_thread_t *);

/* MK_ReplyForCtrSub sets the return value for a counter subsystem thread, which is terminated by MK_PpaTerminateThread.
*/
static void MK_ReplyForCtrSub(mk_kernelcontrol_t *coreVars, mk_thread_t *culprit)
{
	mk_thread_t *parent;

	if ( culprit->parentCore < 0 )
	{
		/* Asynchronous call - no reply needed.
		*/
	}
	else
	if ( culprit->parentCore == coreVars->coreIndex )
	{
		/* Caller is on the same core -> parentThread contains the thread reference.
		 * Copy thread's return values to the parent.
		*/
		parent = culprit->parentThread;
		/* Deviation MISRAC2012-1 <+1> */
		if ( MK_HwIsRegisterStoreValid(parent->regs) )
		{
			MK_HwSetReturnValue1(parent->regs, MK_E_KILLED);
		}
	}
	else
	{
#if (MK_MAXCORES > 1)
		mk_parametertype_t reply[MK_MSG_MAXPARAM];

		/* Caller is on another core -> use parentCookie.
		*/
		reply[0] = (mk_parametertype_t)MK_E_KILLED;
		reply[1] = 0u;
		reply[2] = 0u;
		reply[3] = 0u;
		(void)MK_SendMessage(coreVars, culprit->parentCore, MK_xcore_Reply, culprit->parentCookie, reply);
#else
		/* We can't send cross core messages in a single-core system.
		 * coreIndex or culprit's parentCore field must be corrupted.
		*/
		MK_Panic(MK_panic_CoreNotConfigured);
#endif
	}
}

/* MK_PpaTerminateThread() dequeues and terminates the thread that caused the protection
 * violation (called the "culprit").
 *
 * Preconditions:
 *  - The current thread is the protection hook thread
 *  - The protection hook thread's parent points to the culprit
 *
 * !LINKSTO Microkernel.Function.MK_PpaTerminateThread, 1
 * !doctype src
*/
void MK_PpaTerminateThread(mk_kernelcontrol_t *coreVars)
{
	mk_hwlocklevel_t lockLevel;
	mk_thread_t *parent;

	/* Start with the current thread, which is the protection hook thread.
	*/
	mk_thread_t *pred = coreVars->currentThread;

	/* The culprit is the protection hook's parent.
	*/
	mk_thread_t *culprit = pred->parentThread;

	if (culprit == MK_NULL)
	{
		/* The culprit was already terminated, so there is nothing more to do.
		*/
	}
	else
	{
		MK_DequeueThread(&pred->next, culprit);		/* Panics if thread is not found in the queue */

		if ( (culprit->parentCookie == MK_NULLCOOKIE) && (culprit->parentThread == MK_NULL) )
		{
			/* Thread has no parent, so it could be a task. If it isn't a task there's nothing a special
			 * to do here.
			*/
			if ( culprit->objectType == MK_OBJTYPE_TASK )
			{
				/* If the caller is a task, decrement the activation counter
				*/
				MK_taskCfg[culprit->currentObject].dynamic->activationCount--;
			}
		}
		else
		{
			/* The culprit has a parent. This means that the thread is either the error hook,
			 * a counter subsystem thread or a trusted function thread. The only other type of thread with a
			 * parent is the protection hook, and our culprit cannot be that.
			 *
			 * If the culprit is a counter subsystem thread or a trusted function, the first return value register
			 * of the parent (the "status code") must be set to "KILLED" to indicated that the
			 * requested service didn't complete successfully.
			*/
			if ( culprit->objectType == MK_OBJTYPE_ERRORHOOK )
			{
				/* No special action required
				*/
			}
			else
			if ( culprit->objectType == MK_OBJTYPE_TRUSTEDFUNCTION )
			{
				/* A trusted function always runs on the same core as its
				 * parent, so the parentThread is a pointer to the thread.
				*/
				parent = culprit->parentThread;

				/* Set parent's return value (status code) to MK_E_KILLED.
				*/
				MK_HwSetReturnValue1(parent->regs, MK_E_KILLED);
			}
			else
			if ( culprit->objectType == MK_OBJTYPE_CTRSUB )
			{
				MK_ReplyForCtrSub(coreVars, culprit);
			}
			else
			{
				/* What's this?
				*/
				MK_Panic(MK_panic_UnexpectedThreadWithParent);
			}
		}

		/* The culprit can now be terminated. Termination might need to preserve the priority and
		 * lock level.
		*/
		lockLevel = MK_HwGetIntLevel(culprit->regs);
		MK_HwFreeThreadRegisters(culprit->regs);
		MK_TerminateThread(coreVars, culprit, lockLevel);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
