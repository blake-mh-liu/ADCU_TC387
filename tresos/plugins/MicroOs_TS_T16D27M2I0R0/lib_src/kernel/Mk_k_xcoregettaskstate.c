/* Mk_k_xcoregettaskstate.c
 *
 * This file contains the function MK_XcoreGetTaskState().
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
#include <private/Mk_thread.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>

/* MK_XcoreGetTaskState() - get the state of a task on request from another core.
 *
 * !LINKSTO Microkernel.Function.MK_XcoreGetTaskState, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_XcoreGetTaskState(mk_kernelcontrol_t *coreVars, mk_msgptr_t msg, mk_objectid_t fromCore)
{
	mk_parametertype_t p = msg->parameter[0];		/* Task ID */
	mk_objectid_t taskId;
	const mk_taskcfg_t *taskCfg;
	mk_errorid_t eid;
	mk_parametertype_t reply[MK_MSG_MAXPARAM];

	/* Sanity checks: task ID is in range, task is really configured for my core.
	*/
	if ( p >= (mk_parametertype_t)MK_nTasks )
	{
		MK_HandleInvalidXcoreMessage(coreVars, msg);
	}
	else
	{
		taskId = (mk_objectid_t)p;
		taskCfg = &MK_taskCfg[taskId];

		if ( taskCfg->threadCfg.coreIndex == coreVars->coreIndex )
		{
			mk_taskstate_t state;

			eid = MK_LocalGetTaskState(coreVars, taskId, taskCfg, &state);

			reply[0] = (mk_parametertype_t)MK_ErrorInternalToOsek(eid);
			reply[1] = (mk_parametertype_t)state;
			reply[2] = 0u;
			reply[3] = 0u;
			(void)MK_SendMessage(coreVars, fromCore, MK_xcore_Reply, msg->callerCookie, reply);

			if ( eid != MK_eid_NoError )
			{
				/* This is probably unreachable.
				*/
				(void)MK_InternReportError(coreVars, MK_sid_GetTaskState, eid, MK_NULL, msg->parameter);
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
