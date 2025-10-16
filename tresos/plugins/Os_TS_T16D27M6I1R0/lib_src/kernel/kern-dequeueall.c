/* kern-dequeueall.c
 *
 * This file contains the OS_DequeueAll function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: UnusedVariable
 *   Variable is set but never used.
 *
 * Reason: Not an issue, variable will be used if scalability class 2 is used.
 *
 * TOOLDIAG-2) Possible diagnostic: PointlessComparison
 *   Condition is always true.
 *
 * Reason: This warning depends on the OS configuration and library optimization.
 *   Only if every queue has just one entry (OS_LCFG_TASKQUEUE_CC1),
 *   OS_Get_PriorityQueueHeadAfterRemoval will always yield OS_NULLTASK (at compile time).
 *
 * TOOLDIAG-3) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   If there aren't any tasks which have multiple activations,
 *   the respective if-condition can be evaluated at compile time.
 *   Otherwise this statement is reachable.
 *
 * TOOLDIAG-4) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_DequeueAll
 *
 * All activations of the specified task are removed from the task queue.
 * We don't need to go through the activations in order (from the task's
 * point of view) - we just walk the list and remove anything that's in
 * the task's range. We test for all activations removed to avoid walking
 * through all the lower priority tasks in the list. Our task can't possibly
 * be down there!
 *
 * OS_DequeueAll() must be called with interrupts locked
 *
 * CHECK: NOPARSE
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_DequeueAll(const os_task_t *tp)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-4 <+1> */
	os_tasklink_t * const taskActivations = OS_GetTaskActivations();
	os_taskdynamic_t *td = tp->dynamic;
	os_tasklink_t next = taskActivations[0];
	os_tasklink_t prev = 0;
	os_tasklink_t curr;
	os_tasklink_t min = tp->linkBase;
	os_tasklink_t max = (os_tasklink_t) (min + tp->maxAct);
	os_unsigned_t nAct = (os_unsigned_t)td->nAct + 1u;

	while ( (nAct > 0u) && (next != 0u) )
	{
		curr = next;
		next = taskActivations[next];

		if ( (curr >= min) && (curr <= max) )
		{
			taskActivations[prev] = next;
			taskActivations[curr] = 0;
			nAct--;
		}
		else
		{
			prev = curr;
		}
	}

	td->nAct = 0;
	td->cAct = 0;
	/* Possible diagnostic TOOLDIAG-4 <+1> */
	OS_GetKernelData()->taskQueueHead = OS_GetTaskPtrs(taskActivations[0]);
}

/* CHECK: PARSE */

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_dequeueall_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
