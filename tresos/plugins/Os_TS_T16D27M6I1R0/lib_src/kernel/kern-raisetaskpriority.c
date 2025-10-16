/* kern-raisetaskpriority.c
 *
 * This file contains the OS_RaiseTaskPriority function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*
 * This function raises the priority of a task,
 * by moving it to the correct position in the priority queue.
 * and setting the tasks priority field accordingly.
 *
 * This is a helper function for OS_GetResourceFromTask and OS_KernSuspendInterrupts.
 *
 * Parameters:
 *  - td         : The dynamic data of the task whose priority is meant to be raised.
 *  - reqPrio    : The priority to which the task is meant to be raised.
 *
 * Preconditions:
 *  Interrupts must be disabled so there's no concurrent modification
 *  of the task's dynamic data or the priority queue.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RaiseTaskPriority(os_taskdynamic_t *td, os_prio_t reqPrio)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();

	/* The following depends on the priority queue implementation.
	*/
	{
		os_tasklink_t link;
		if ( kernel_data->taskQueueHead == kernel_data->taskCurrent )
		{
			/* The task is still at the head of the queue, so just do it.
			*/
			td->prio = reqPrio;
		}
		else
		{
			/* The task is no longer at the head of the queue. A
			 * higher-priority task has become active as a result of an interrupt.
			*/
			link = OS_CurrentLink(kernel_data->taskCurrent, td);
			td->prio = reqPrio;
			OS_RequeueUp(link, td->prio);
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_raisetaskpriority_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
