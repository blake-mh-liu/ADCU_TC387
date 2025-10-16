/* Mk_k_multigettaskstate.c
 *
 * This file contains the MK_MultiGetTaskState() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_task.h>
#include <private/Mk_thread.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_message.h>

#if MK_MAXCORES <= 1
#error "This file is not needed for single-core systems."
#endif

/*
 * MK_MultiGetTaskState() gets the state of a specified task.
 *
 * This function is called on multi-core systems to get the state of a task on any core.
 * The task ID is assumed to have been previously validated.
 *
 * !LINKSTO Microkernel.Function.MK_MultiGetTaskState, 1
 * !doctype src
*/
mk_errorid_t MK_MultiGetTaskState
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t taskId,			/* Pre-validated task ID. */
	const mk_taskcfg_t *taskCfg,	/* Task config structure. */
	mk_taskstate_t *state			/* Where to put the state if available. */
)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_parametertype_t p[MK_MSG_MAXPARAM];
	mk_objectid_t taskCore;
	mk_thread_t *caller;

	taskCore = taskCfg->threadCfg.coreIndex;

	if ( taskCore == coreVars->coreIndex )
	{
		errorCode = MK_LocalGetTaskState(coreVars, taskId, taskCfg, state);
	}
	else
	{
		p[0] = (mk_parametertype_t)taskId;
		p[1] = MK_HwGetParameter2(coreVars->currentThread->regs);		/* Only for error reporting */
		p[2] = 0;
		p[3] = 0;

		errorCode = MK_SendMessage(coreVars, taskCore, MK_xcore_GetTaskState, MK_NULLCOOKIE, p);

		if ( errorCode == MK_eid_NoError )
		{
			/* Set up the mechanism for waiting for and receiving the reply.
			*/
			caller = coreVars->currentThread;
			caller->xcoreReply.statusCode = MK_E_WAITFORREPLY;
			caller->xcoreReply.requestedValue = MK_WAITCOOKIE(coreVars->cookieGen, taskCore);
			errorCode = MK_eid_WaitForReply;
		}
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
