/* Mk_k_multisetevent.c
 *
 * This file contains the MK_MultiSetEvent() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_PARAM]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *  In function MK_MultiSetEvent: Value 6.0 of metric "param" is out of bounds (0..5)
 *
 * Reason:
 *  MK_MultiSetEvent's parameter 'taskCfg' could be deduced from 'taskId', however,
 *  the looking up taskCfg again might be expensive, since it involves a range check and possibly
 *  a multiplication. Therefore, MK_MultiSetEvent doesn't have more parameters than necessary.
*/
/* Deviation DCG-1 <*> */

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
 * MK_MultiSetEvent() sets events for a task.
 *
 * This function is called on multi-core systems to set events for a task on any core.
 * The task ID is assumed to have been previously validated.
 *
 * !LINKSTO Microkernel.Function.MK_MultiSetEvent, 2
 * !doctype src
*/
mk_errorid_t MK_MultiSetEvent
(	mk_kernelcontrol_t * coreVars,
	mk_objectid_t taskId,
	const mk_taskcfg_t *taskCfg,
	mk_eventmask_t eventsToSet,
	mk_xcall_t callType,
	mk_objectid_t callerApp
)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_parametertype_t p[MK_MSG_MAXPARAM];
	mk_objectid_t taskCore;
	mk_thread_t *caller;

	taskCore = taskCfg->threadCfg.coreIndex;

	if ( taskCore == coreVars->coreIndex )
	{
		errorCode = MK_LocalSetEvent(coreVars, taskId, taskCfg, eventsToSet, callerApp);
	}
	else
	{
		p[0] = (mk_parametertype_t)taskId;
		p[1] = (mk_parametertype_t)eventsToSet;
		p[2] = 0;
		p[3] = 0;

		errorCode = MK_SendMessage(coreVars, taskCore, callType, MK_NULLCOOKIE, p);

		if ( (errorCode == MK_eid_NoError) && (callType == MK_xcore_SetEvent) )
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
