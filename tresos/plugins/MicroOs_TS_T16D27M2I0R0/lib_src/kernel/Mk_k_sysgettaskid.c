/* Mk_k_sysgettaskid.c
 *
 * This file contains the function MK_SysGetTaskId().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 12.4 (advisory)
 * Evaluation of constant expressions should not lead to unsigned integer
 * wrap-around.
 *
 * Reason:
 * Intentional wrap-around to represent an invalid value.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>

/* MK_SysGetTaskId() - finds the ID of the current task
 *
 * It works by walking down the thread queue looking for the first task. Task in state NEW are ignored
 * because they've just been activated and cannot be "current".
 *
 * !LINKSTO Microkernel.Function.MK_SysGetTaskId, 1
 * !doctype src
*/
void MK_SysGetTaskId(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;

	/* Find highest-priority task thread. Threads in state NEW are ignored because they have never been dispatched
	 * and can therefore not be current even if they are of higher priority than the task that is considered
	 * to be "current".
	*/
	mk_thread_t *thread = MK_FindFirstThread(caller, MK_OBJTYPE_TASK, MK_THS_NEW);

	if ( thread == MK_NULL )
	{
		/* Deviation MISRAC2012-1 <+1> */
		MK_HwSetReturnValue2(caller->regs, MK_INVALID_TASK);
	}
	else
	{
		MK_HwSetReturnValue2(caller->regs, thread->currentObject);
	}

	MK_HwSetReturnValue1(caller->regs, MK_E_OK);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
