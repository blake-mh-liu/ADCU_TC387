/* Mk_k_startthread.c
 *
 * This file contains the MK_StartThread() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  This function is part of a MK_Panic call-graph cycle (depends on the hardware).
 *  However MK_Panic calls MK_PanicStop, if it is entered a second time.
 *  So this function can't appear more than twice on the call stack.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* MK_StartThread() starts a thread to run the given function
 *
 * Parameters:
 *	thread		- the address of the thread structure
 *	threadCfg	- address of a thread config block for this thread
 *
 * Precondition:
 *	the thread is idle
 *
 * !LINKSTO Microkernel.Function.MK_StartThread, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 */
void MK_StartThread
(	mk_thread_t **head,
	mk_thread_t *thread,
	const mk_threadcfg_t *threadCfg
)
{
	/* Set up the thread (initialize thread fields)
	 * Must be done first because this initializes thread->registers, which is needed
	 * for the next step...
	*/
	MK_SetupThread(thread, threadCfg);

	/* Clear out the inter-core reply buffer.
	*/
#if MK_MAXCORES > 1
	thread->xcoreReply.statusCode = 0u;
	thread->xcoreReply.requestedValue = MK_NULLCOOKIE;
#endif

	/* Some processors need to allocate some space for register windows.
	*/
	/* Deviation MISRAC2012-1 <+1> */
	MK_HwAllocateThreadRegisters(thread->regs);

	/* Load the initial values into the registers.
	*/
	MK_FillThreadRegisters(thread->regs, threadCfg);

	/* Enqueue the thread according to its priority.
	*/
	MK_EnqueueThread(head, thread);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
