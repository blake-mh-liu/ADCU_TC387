/* kern-enqueuelink.c
 *
 * This file contains the OS_EnqueueLink function.
 * The function is only necessary when multiple activations is enabled, but is
 * always present in the library.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 13.5 (required)
 * The right hand operand of a logical && or || operator shall not contain side effects.
 *
 * Reason:
 * False positive: OS_FindPrio() does not have side effects but only reads information.
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
 * OS_EnqueueLink
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
void OS_EnqueueLink(os_tasklink_t tAct, os_prio_t prio)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_tasklink_t * const taskActivations = OS_GetTaskActivations();
	os_tasklink_t qAct = taskActivations[0];
	os_tasklink_t lAct = 0;

	/* Deviation MISRAC2012-1 <+2> */
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	while ( (qAct != 0u) && (OS_FindPrio(qAct) >= prio) )
	{
		lAct = qAct;
		qAct = taskActivations[qAct];
	}

	/* Now we insert tAct between lAct and qAct and recompute the queue head.
	*/
	taskActivations[lAct] = tAct;
	taskActivations[tAct] = qAct;
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	OS_GetKernelData()->taskQueueHead = OS_GetTaskPtrs(taskActivations[0]);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_enqueuelink_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
