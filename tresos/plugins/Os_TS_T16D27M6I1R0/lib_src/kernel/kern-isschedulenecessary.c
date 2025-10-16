/* kern-isschedulenecessary.c
 *
 * This file contains the OS_IsScheduleNecessary function
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
 * Reason: Not an issue, variable will be used if multiple task activations are enabled.
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
#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_api.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_IsScheduleNecessary implements the API Schedule
 *
 * Returns TRUE is there is no current task or there is a task of higher priority enqueued behind the current task.
 * Otherwise returns FALSE.
 *
 * !LINKSTO Kernel.Feature.FastSchedule, 1
 * !LINKSTO Kernel.Feature.FastSchedule.ErrorChecking, 1
 * !LINKSTO Kernel.Feature.FastSchedule.IsScheduleNecessary, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_boolean_t OS_IsScheduleNecessary(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_boolean_t answer = OS_TRUE;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_tasklink_t * const taskActivations = OS_GetTaskActivations();
	os_task_t const * const current_task = OS_GetKernelData()->taskCurrent;
	
	if ( current_task != OS_NULL )
	{
		/* Possible diagnostic TOOLDIAG-1 <1> */
		os_taskdynamic_t * const td = current_task->dynamic;
		const os_tasklink_t link = OS_CurrentLink(current_task, td);
		const os_tasklink_t next = taskActivations[link];
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		answer = ( (next != 0u) && (current_task->queuePrio < OS_FindPrio(next)) );
	} /* else not needed */

	return answer;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_isschedulenecessary_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
