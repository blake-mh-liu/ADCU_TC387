/* kern-requeueup.c
 *
 * This file contains the OS_RequeueUp function.
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
 * OS_RequeueUp
 *
 * The specified task activation is moved from its position in the task queue to somewhere
 * further up the queue because it has increased its priority. The task's priority has already
 * been set to its new value.
 *
 * OS_RequeueUp() must be called with interrupts locked
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RequeueUp(os_tasklink_t tAct, os_prio_t prio)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_tasklink_t * const taskActivations = OS_GetTaskActivations();
	os_tasklink_t qAct = taskActivations[0];
	os_tasklink_t qNew = 0;			/* New predecessor in queue */
	os_tasklink_t qOld;				/* Old predecessor in queue */
	os_tasklink_t qNewNext;			/* New successor in queue */

	/* Run through the queue till we find the new position. Note
	 * that this loop will automatically stop at the current position
	 * because the priority test will return "equal", so there's no
	 * need to explicitly stop at qAct==tAct.
	*/
	/* COVPT-1 +3 */
	/* Deviation MISRAC2012-1 <+2> */
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	while ( (qAct != 0u) && (OS_FindPrio(qAct) > prio) )
	{
		qNew = qAct;
		qAct = taskActivations[qAct];
	}

	/* If we leave the above loop with qAct == 0, the current task is not in the queue.
	 * We can't handle that here so we just leave the queue as it is.
	*/
	/* COVPT-2 */
	if ( qAct != 0u )
	{
		/* Remember the current queue position. This will be the new successor in the queue.
		*/
		qNewNext = qAct;

		/* Now we find the current ("old") position in the queue by searching from the current position.
		*/
		qOld = qNew;
		while ( (qAct != tAct) && (qAct != 0u) )
		{
			qOld = qAct;
			qAct = taskActivations[qAct];
		}

		/* COVPT-3 */
		if ( qOld == qNew )
		{
			/* The old position and the new position are the same, so no change.
			*/
		}
		else
		{
			/* COVPT-4 */
			if ( qAct == tAct )
			{
				/* Now we remove the activation from its former position
				 * (after qOld) and insert it after qNew.
				 * The above test is just a sanity test. If qAct != tAct it means the task isn't
				 * in the queue.
				*/
				/* Remove from old place in queue
				*/
				taskActivations[qOld] = taskActivations[tAct];

				/* Insert at new place in queue
				*/
				taskActivations[qNew] = tAct;
				taskActivations[tAct] = qNewNext;

				/* Finally, set the new queue head because it might have changed.
				*/
				/* Possible diagnostic TOOLDIAG-1 <+1> */
				OS_GetKernelData()->taskQueueHead = OS_GetTaskPtrs(taskActivations[0]);
			}
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_requeueup_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
