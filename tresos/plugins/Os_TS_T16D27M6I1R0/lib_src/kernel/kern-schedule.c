/* kern-schedule.c
 *
 * This file contains the OS_KernSchedule function
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
 *   The statements can be reached, if interrupt enable checks are enabled.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 13.5 (required)
 * The right hand operand of a logical && or || operator shall not contain side effects.
 *
 * Reason:
 * False positive: OS_FindPrio() does not have side effects but only reads information.
 */

#define OS_SID	OS_SID_Schedule
#define OS_SIF	OS_svc_Schedule

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernSchedule implements the API Schedule
 *
 * If the current task is non-preemptable it is requeued with
 * its true priority. However, since the task is already running,
 * it is enqueued AHEAD of those with equal priority, because they
 * might want to use the same context.
 *
 * Interrupts are enabled on entry. We must disable them before doing
 * anything and restore them afterwards.
 *
 * !LINKSTO Kernel.API.TaskManagement.Schedule.API, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernSchedule(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_intstatus_t is;
	os_result_t r = OS_E_OK;
	os_taskdynamic_t *td;

	OS_TRACE_SCHEDULE_ENTRY();

	if ( kernel_data->inFunction == OS_INTASK )
	{
		td = kernel_data->taskCurrent->dynamic;

		if ( !OS_InterruptEnableCheckFromTask(OS_IEC_OSEKEXTRA, td) )
		{
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			r = OS_ERROR(OS_ERROR_InterruptDisabled, OS_NULL);
		}
		else
		if ( td->lastLock != OS_NULLOBJECT )
		{
			/* !LINKSTO Kernel.API.TaskManagement.Schedule.Resources, 1
			 *
			 * If this requirement is ever relaxed, the requeue priority
			 * (below) will need to be adjusted so that it is not lower
			 * than that of the highest-priority resource that has been
			 * taken.
			*/
			/* COVPT-1 */
			if (OS_GetTypeFromObjectId(td->lastLock) == OS_OBJ_SPINLOCK)
			{
				/* !LINKSTO Kernel.Autosar.Multicore.Schedule.Spinlock, 1
				*/
				r = OS_ERROR(OS_ERROR_HoldsLock, OS_NULL);
			}
			else
			{
				r = OS_ERROR(OS_ERROR_HoldsResource, OS_NULL);
			}
		}
		else
		{
			os_tasklink_t link;
			os_tasklink_t next;
			/* Possible diagnostic TOOLDIAG-2 <+1> */
			os_tasklink_t * const taskActivations = OS_GetTaskActivations();

			is = OS_IntDisable();

			/* Requeue the task with its base priority if there's something
			 * with a higher priority waiting. We only do this if the task
			 * is in the running state --- it could have been killed at ISR
			 * level just before disabling interrupts.
			 *
			 * !LINKSTO Kernel.API.TaskManagement.Schedule.HigherPrioTask, 1
			 * !LINKSTO Kernel.API.TaskManagement.Schedule.LowerPrioTask, 1
			 * !LINKSTO Kernel.API.TaskManagement.Schedule.Schedule, 1
			 * !LINKSTO Kernel.API.TaskManagement.Schedule.InternalResource, 1
			*/
			link = OS_CurrentLink(kernel_data->taskCurrent, td);
			next = taskActivations[link];
			/* Deviation MISRAC2012-1 */
			if ( (td->state == OS_TS_RUNNING) &&
				 (next != 0u) &&
				 /* Possible diagnostic TOOLDIAG-2 <+1> */
				 (kernel_data->taskCurrent->queuePrio < OS_FindPrio(next)) )
			{
				td->prio =  kernel_data->taskCurrent->queuePrio;
				OS_RequeueDown(link, td->prio);
			}

			OS_IntRestore(is);
		}
	}
	else
	{
		/* !LINKSTO Kernel.API.TaskManagement.Schedule.ISRC2, 1
		*/
		r = OS_ERROR(OS_ERROR_WrongContext, OS_NULL);
	}

	OS_TRACE_SCHEDULE_EXIT_P(r);
	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_schedule_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
