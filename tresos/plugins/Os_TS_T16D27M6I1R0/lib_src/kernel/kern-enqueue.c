/* kern-enqueue.c
 *
 * This file contains the OS_Enqueue function.
 * When multiple activations are permitted the function must not exist.
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

#if (OS_KERNEL_TYPE != OS_MICROKERNEL) && (defined(OS_EXCLUDE_MULTIPLE_ACTIVATIONS))

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_Enqueue
 *
 * The specified task activation is inserted into the task activation queue
 * in priority order behind those with equal priority.
 *
 * !LINKSTO Kernel.Architecture.ConformanceClasses.NonSuspendedTasksBCC, 1
 * !LINKSTO Kernel.Architecture.ConformanceClasses.NonSuspendedTasksECC, 1
 *		The number of tasks in the ready queue is not limited here.
 *
 * !LINKSTO Kernel.Architecture.ConformanceClasses.TasksPerPrio, 1
 *		The number of tasks per priority is not limited here.
 *
 * !LINKSTO Kernel.TaskManagement.Scheduling.PrioQueue, 1
 * !LINKSTO Kernel.TaskManagement.Scheduling, 1
 * !LINKSTO Kernel.TaskManagement, 1
 *		'>=' in the while loop --> FIFO order.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_Enqueue(const os_task_t *tp)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_tasklink_t * const taskActivations = OS_GetTaskActivations();
	os_tasklink_t tAct = tp->linkBase;
	os_prio_t prio = tp->queuePrio;
	os_tasklink_t qAct = taskActivations[0];
	os_tasklink_t lAct = 0;
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	while ( (qAct != 0) && (OS_FindPrio(qAct) >= prio) )
	{
		lAct = qAct;
		qAct = taskActivations[qAct];
	}

	/* Now we insert the activation between lAct and qAct. The
	 * test for zero here is kept because it's probably more efficient than recomputing tp
	 * from the OS_GetTaskPtrs(taskActivations[0]) every time.
	*/
	if ( lAct == 0 )
	{
		/* Enqueue at head
		*/
		taskActivations[0] = tAct;
		OS_GetKernelData()->taskQueueHead = tp;
	}
	else
	{
		taskActivations[lAct] = tAct;
	}

	taskActivations[tAct] = qAct;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_enqueue_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
