/* Mk_k_sysgettaskstate.c
 *
 * This file contains the function MK_SysGetTaskState().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_errorhandling.h>

/* MK_SysGetTaskState() determines a task's state
 *
 * The state is determined by looking at:
 * - the activation counter
 * - whether the task is currently "on" its thread
 * - the pending events (for EXTENDED tasks)
 *
 * Note: this implementation is preferred over maintaining a task state for each task because
 * the cost of updating the state during normal running is borne by the system as a whole, whereas
 * with this method the cost is borne by the caller (and occurs much less frequently).
 *
 * !LINKSTO Microkernel.Function.MK_SysGetTaskState, 2
 * !doctype src
*/
void MK_SysGetTaskState(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_parametertype_t p = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	const mk_taskcfg_t *taskCfg;
	mk_taskstate_t state = MK_TS_INVALID;

	/* Explicit cast to prevent compiler warning (ok, as the number of tasks is always >= 0).
	*/
	if ( p < (mk_parametertype_t)MK_nTasks )
	{
		mk_objectid_t taskId = (mk_objectid_t)p;
		taskCfg = &MK_taskCfg[taskId];

		errorCode = MK_InternGetTaskState(coreVars, taskId, taskCfg, &state);
	}
	else
	{
		errorCode = MK_eid_InvalidTaskId;
	}

	/* This ensures that the requested information is always defined (for errors, it's MK_TS_INVALID).
	*/
	MK_HwSetReturnValue2(caller->regs, state);

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_GetTaskState, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
