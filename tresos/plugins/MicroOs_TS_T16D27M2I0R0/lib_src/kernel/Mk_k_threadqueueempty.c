/* Mk_k_threadqueueempty.c
 *
 * This file contains the function MK_ThreadQueueEmpty().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_error.h>
#include <private/Mk_thread.h>
#include <private/Mk_shutdown.h>

/* MK_ThreadQueueEmpty() is called whenever a kernel function removes the last thread from the thread queue
 *
 * When there are no more threads in the thread queue after a service or operation that has removed (terminated)
 * a thread, this function is called.
 * Note: this can only happen if the idle thread terminates, but it doesn't necessarily happen immediately.
 *
 * The default behavior is to shut down the system (which creates more threads).
 *
 * Note: the test for the thread queue being empty is made outside this function. It would be possible
 * to put the decision inside the function and thus reduce the microkernel's code footprint slightly.
 * The disadvantage of that approach would be the increased runtime overhead of the function call
 * at each place where the test is made. In addition, placing the decision outside the function allows
 * the test coverage measurement to ensure that each branch is tested at each point of call rather than
 * at least once at some point of call.
 *
 * !LINKSTO Microkernel.Function.MK_ThreadQueueEmpty, 1
 * !doctype src
*/
void MK_ThreadQueueEmpty(void)
{
	MK_Shutdown(MK_E_THREADQUEUEEMPTY);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
