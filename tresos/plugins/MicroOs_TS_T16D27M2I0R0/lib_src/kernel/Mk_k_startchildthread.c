/* Mk_k_startchildthread.c
 *
 * This file contains the function MK_StartChildThread().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_PARAM]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *   This function has as many parameters as required by the design.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_errorhandling.h>
#include <public/Mk_error.h>
#include <private/Mk_thread.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_core.h>

/* MK_StartChildThread() starts a thread to run the given function.
 *
 * The function is either a trusted function or a counter subsystem function. The caller has previously
 * set up the thread config with the correct configuration for the function. The caller must set
 * the parameters and the interrupt level after this function has set up the thread.
 *
 * !LINKSTO Microkernel.Function.MK_StartChildThread, 1
 * !doctype src
*/
/* Deviation DCG-1 <+1> */
void MK_StartChildThread
(	mk_thread_t **head,
	mk_thread_t *thread,
	const mk_threadcfg_t *threadCfg,
	mk_thread_t *parentThread,
	mk_parametertype_t parentCookie,
	mk_objectid_t parentCore
)
{
	mk_threadregisters_t *regs;

	/* Set up the thread as normal. The priority has been preset by the caller.
	*/
	MK_SetupThread(thread, threadCfg);

	regs = thread->regs;

	/* Some processors need to allocate some space for register windows before we can transfer the parameters.
	*/
	MK_HwAllocateThreadRegisters(regs);

	/* Set up the thread registers to run the synchronous object.
	*/
	MK_FillThreadRegisters(regs, threadCfg);

	/* Set up the thread's parent and core (for synchronous calls)
	*/
	thread->parentThread = parentThread;

	thread->parentCookie = parentCookie;

	thread->parentCore = parentCore;

	MK_RequeueThread(head, thread);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
