/* kern-actitask.c
 *
 * This file contains the OS_ActiTask function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_ActiTask
 *
 * The specified task is activated. The task *must* be in the
 * SUSPENDED or QUARANTINED state.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ActiTask(const os_task_t *tp)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_taskdynamic_t *td;

	td = tp->dynamic;

	td->prio = tp->queuePrio;

	OS_TRACE_STATE_TASK( OS_GetKernelData()->taskCurrent->taskId, td->state, OS_TS_NEW );
	td->state = OS_TS_NEW;

	OS_ClearCurrentActivation(td);

	OS_ClearPendingEvents(td);

	/* Reset the task's execution time measurement
	 *
	 * !LINKSTO Kernel.Autosar.Protection.TimingProtection.ExecutionTime.Measurement.Task, 1
	*/
	OS_InitTaskEtb(tp);

	OS_Enqueue(tp);

}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_actitask_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
