/* Mk_k_multiactivatetask.c
 *
 * This file contains the MK_MultiActivateTask() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_message.h>

#if MK_MAXCORES <= 1
#error "This file is not needed for single-core systems."
#endif

/*
 * MK_MultiActivateTask() activates a task.
 *
 * This function is called on multi-core systems to activate a task on any core.
 * The task ID is assumed to have been previously validated.
 *
 * !LINKSTO Microkernel.Function.MK_MultiActivateTask, 2
 * !doctype src
*/
mk_errorid_t MK_MultiActivateTask
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t taskId,
	mk_xcall_t callType,
	mk_objectid_t callerApp
)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	const mk_taskcfg_t *taskCfg = &MK_taskCfg[taskId];
	mk_parametertype_t p[MK_MSG_MAXPARAM];
	mk_objectid_t taskCore;
	mk_thread_t *caller;

	taskCore = taskCfg->threadCfg.coreIndex;

	if ( taskCore == coreVars->coreIndex )
	{
		errorCode = MK_LocalActivateTask(coreVars, taskId, taskCfg, callerApp);
	}
	else
	{
		p[0] = (mk_parametertype_t)taskId;
		p[1] = 0;
		p[2] = 0;
		p[3] = 0;

		errorCode = MK_SendMessage(coreVars, taskCore, callType, MK_NULLCOOKIE, p);

		if ( (errorCode == MK_eid_NoError) && (callType == MK_xcore_ActivateTask) )
		{
			/* Set up the mechanism for waiting for and receiving the reply.
			*/
			caller = coreVars->currentThread;
			caller->xcoreReply.statusCode = MK_E_WAITFORREPLY;
			caller->xcoreReply.requestedValue = MK_WAITCOOKIE(coreVars->cookieGen, taskCore);
			errorCode = MK_eid_WaitForReply;
		}
		/* else it's MK_xcore_AsyncActivateTask or MK_xcore_AsyncChainTask and we don't wait. */
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
