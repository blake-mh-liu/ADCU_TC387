/* Mk_k_sysactivatetask.c
 *
 * This file contains the MK_SysActivateTask() function.
 *
 * This function is called by the system call function whenever the ActivateTask system call is made.
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
 * MK_SysActivateTask() activates a task.
 *
 * This function is present in the system call table and is called whenever a thread makes
 * an "ActivateTask" system call. As with all system calls, the parameters are obtained from
 * the current thread's register context.
 *
 * !LINKSTO Microkernel.Function.MK_SysActivateTask, 2
 * !doctype src
*/
void MK_SysActivateTask(mk_kernelcontrol_t * coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t taskId = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_errorid_t errorCode = MK_eid_Unknown;

	/* Explicit cast to prevent compiler warning (ok, as the number of tasks is always >= 0).
	*/
	if ( taskId < (mk_parametertype_t)MK_nTasks )
	{
		errorCode = MK_InternActivateTask( coreVars,
										   (mk_objectid_t)taskId,
										   MK_xcore_ActivateTask,
										   caller->applicationId
										 );
	}
	else
	{
		errorCode = MK_eid_InvalidTaskId;
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_ActivateTask, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
