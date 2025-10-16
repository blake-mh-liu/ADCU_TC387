/* Mk_k_sysgetisrid.c
 *
 * This file contains the function MK_SysGetIsrId().
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

/* MK_SysGetIsrId() - works out what is the current ISR by walking down the thread queue.
 *
 * !LINKSTO Microkernel.Function.MK_SysGetIsrId, 2
 * !doctype src
*/
void MK_SysGetIsrId(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;

	/* Find highest-priority ISR thread. Threads in all states are considered (threads in the queue cannot be idle).
	 *
	 * If pure software leveling is ever implemented it might be necessary to ignore NEW threads here.
	*/
	mk_thread_t *thread = MK_FindFirstThread(caller, MK_OBJTYPE_ISR, MK_THS_IDLE);

	if ( thread == MK_NULL )
	{
		/* Deviation MISRAC2012-1 <+1> */
		MK_HwSetReturnValue1(caller->regs, MK_INVALID_ISR);
	}
	else
	{
		MK_HwSetReturnValue1(caller->regs, thread->currentObject);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
