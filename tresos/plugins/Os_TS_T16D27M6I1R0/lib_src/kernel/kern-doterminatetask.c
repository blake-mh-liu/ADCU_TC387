/* kern-doterminatetask.c
 *
 * This file contains the OS_DoTerminateTask function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   This statement can be reached if there is at least one task which allows multiple activations.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_DoTerminateTask implements the business end of the API TerminateTask
 *
 * The task indicated by tp and td is terminated. and removed from the task queue.
 * If there are any activations pending, the task is enqueued again at
 * its base priority with state NEW. Otherwise the state is set to
 * SUSPENDED.
 *
 * Interrupts are enabled on entry. taskCurrent cannot be changed
 * by an ISR because it only gets updated by the dispatcher after
 * returning from here. However, we need to disable interrupts before
 * manipulating the queue. We can enable them again at on exit.
 *
 * Because interrupts are enabled, taskCurrent is not guaranteed to
 * be at the head of the queue, so we must use Dequeue(), not DequeueHead().
 *
 * !LINKSTO Kernel.API.TaskManagement.TerminateTask.API, 1
 *
 * !LINKSTO Kernel.API.TaskManagement.TerminateTask.Schedule, 1
 *      Happens automatically when this function returns.
 *
 * !LINKSTO Kernel.API.TaskManagement.TerminateTask.InternalResource, 1
 *      Happens automatically because internal resources are
 *      implemented by setting the run priority of the task.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_DoTerminateTask(const os_task_t *tp, os_taskdynamic_t *td)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_intstatus_t is;

	is = OS_IntDisable();

	/* COVPT-1 */
	if ( td->state == OS_TS_RUNNING )
	{
		/* Stop the execution timer.
		 * This could kill the task!
		*/
		OS_ARCH_STOPTASKEXECTIMING(tp);
		OS_STOPTASKEXECTIMING(tp);
	}

	/* COVPT-2 */
	if ( td->state == OS_TS_RUNNING )
	{

		/* Call post-task hook before task goes to SUSPENDED state.
		 * Interrupts are already disabled here.
		 *
		 * !LINKSTO Kernel.API.Hooks.PostTaskHook.API, 1
		 * !LINKSTO Kernel.HookRoutines.PrioISRC2, 1
		 *		Interrupts are disabled here
		*/
		OS_CALLPOSTTASKHOOK();

		OS_Dequeue(OS_CurrentLink(tp, td));

		if ( OS_ActivationPending(td) )
		{
			/* !LINKSTO Kernel.Architecture.ConformanceClasses.MultipleActivation, 1
			*/
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			td->nAct--;
			td->prio = tp->queuePrio;

			OS_TRACE_STATE_TASK( tp->taskId, td->state, OS_TS_NEW );
			td->state = OS_TS_NEW;

			/* Reset the task's execution time measurement
			 *
			 * !LINKSTO Kernel.Autosar.Protection.TimingProtection.ExecutionTime.Measurement.Task, 1
			*/
			OS_InitTaskEtb(tp);

			/* Advance the current activation index.
			*/
			if ( td->cAct >= tp->maxAct )
			{
				td->cAct = 0;
			}
			else
			{
				td->cAct++;
			}
		}
		else
		{
			/* !LINKSTO Kernel.API.TaskManagement.TerminateTask.StateChange, 1
			*/
			OS_TRACE_STATE_TASK( tp->taskId, td->state, OS_TS_SUSPENDED );
			td->state = OS_TS_SUSPENDED;
		}
	}

	OS_IntRestore(is);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_doterminatetask_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
