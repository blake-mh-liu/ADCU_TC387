/* Mk_k_xcoreasyncsetevent.c
 *
 * This file contains the function MK_XcoreAsyncSetEvent().
 *
 * (c) Elektrobit Automotive GmbH
*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: Dir 4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
 *
 *
 * MISRAC2012-2) Deviated Rule: D4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>
#include <private/Mk_task.h>
#include <private/Mk_event.h>
#include <private/Mk_thread.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>

/* MK_XcoreAsyncSetEvent() - set events for a task on request from another core.
 *
 * !LINKSTO Microkernel.Function.MK_XcoreAsyncSetEvent, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_XcoreAsyncSetEvent(mk_kernelcontrol_t *coreVars, mk_msgptr_t msg, mk_objectid_t unused_fromCore)
{
	mk_parametertype_t p = msg->parameter[0];		/* Task ID */
	mk_objectid_t taskId;
	const mk_taskcfg_t *taskCfg;
	mk_errorid_t eid;

	MK_PARAM_UNUSED(unused_fromCore);

	/* Sanity checks: task ID is in range, task is really configured for my core.
	*/
	if ( p >= (mk_parametertype_t) MK_nTasks )
	{
		MK_HandleInvalidXcoreMessage(coreVars, msg);
	}
	else
	{
		taskId = (mk_objectid_t)p;
		taskCfg = &MK_taskCfg[taskId];

		if ( taskCfg->threadCfg.coreIndex == coreVars->coreIndex )
		{
			if ( taskCfg->eventStatus == MK_NULL )
			{
				MK_HandleInvalidXcoreMessage(coreVars, msg);
			}
			else
			{
				eid = MK_LocalSetEvent(coreVars, taskId, taskCfg, (mk_eventmask_t)(msg->parameter[1]), MK_APPL_NONE);

				if ( eid != MK_eid_NoError)
				{
					(void)MK_InternReportError(coreVars, MK_sid_AsyncSetEvent, eid, MK_NULL, msg->parameter);
				}
			}
		}
		else
		{
			MK_HandleInvalidXcoreMessage(coreVars, msg);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
