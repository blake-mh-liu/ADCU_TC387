/* kern-lowercurrenttaskspriority.c
 *
 * This file contains the OS_LowerCurrentTasksPriority function.
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
 * This function lowers the priority of the current task
 * by moving it to the correct position in the priority queue.
 * and setting the tasks priority field accordingly.
 *
 * This is a helper function for OS_GetResourceFromTask and OS_KernResumeInterrupts.
 *
 * Parameter:
 *  reqPrio: The priority to which the current task's priority is meant to be lowered.
 *
 * Preconditions:
 *  Interrupts must be disabled so there's no concurrent modification
 *  of the current task or the priority queue.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_LowerCurrentTasksPriority(os_prio_t reqPrio)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	const os_task_t * const currentTask = kernel_data->taskCurrent;
	os_taskdynamic_t * const td = currentTask->dynamic;

	/* The following part depends on the queue implementation.
	*/
	{
		/* Priority changes ...
		 * We need to dequeue the task and then re-queue it again
		 * because there might be a higher priority task in the queue.
		*/
		os_tasklink_t link;

		link = OS_CurrentLink(currentTask, td);
		OS_RequeueDown(link, reqPrio);
	}

	td->prio = reqPrio;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_lowercurrenttaskspriority_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
