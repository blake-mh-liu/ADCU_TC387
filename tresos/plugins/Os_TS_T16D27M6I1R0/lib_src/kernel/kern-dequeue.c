/* kern-dequeue.c
 *
 * This file contains the OS_Dequeue function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/
#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_Dequeue
 *
 * The specified task activation is removed from the task queue. The task
 * can be anywhere in the queue.
 *
 * OS_Dequeue() must be called with interrupts locked
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_Dequeue(os_tasklink_t tAct)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_tasklink_t * const taskActivations = OS_GetTaskActivations();
	os_tasklink_t qAct = taskActivations[0];

	if ( tAct == qAct )
	{
		/* Task is at head of queue
		*/
		taskActivations[0] = taskActivations[tAct];
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		OS_GetKernelData()->taskQueueHead = OS_GetTaskPtrs(taskActivations[0]);
		taskActivations[tAct] = 0;
	}
	else
	{
		/* Task is not at head. Might be somewhere further along.
		 * This can happen if a higher priority task gets activated by an
		 * interrupt while we're in the kernel TerminateTask routine with
		 * interrupts enabled. It also covers the case for killing a task
		 * that is READY. (Autosar, protection violation etc.)
		*/
		/* COVPT-1 */
		while ( (taskActivations[qAct] != tAct) && (qAct != 0u) )
		{
			qAct = taskActivations[qAct];
		}

		/* COVPT-2 */
		if ( qAct == 0u )
		{
			/* Task is not in the queue - nothing to do */
		}
		else
		{
			taskActivations[qAct] = taskActivations[tAct];
			taskActivations[tAct] = 0;
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_dequeue_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
