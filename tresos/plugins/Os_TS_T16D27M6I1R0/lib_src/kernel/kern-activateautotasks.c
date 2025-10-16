/* kern-activateautotasks.c
 *
 * This file contains the OS_ActivateAutoTasks function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *   Comparison with constant compile-time result
 *
 * Reason: In single-core configurations, the result is compile-time constant.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
 */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 14.3 (required)
 * Controlling expressions shall not be invariant.
 *
 * Reason:
 * The invariance depends on the configuration and may be constant.
 *
 *
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * For single-core configurations, the expression is always true.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_ActivateAutoTasks()
 *
 * Activate all tasks that are specified for the requested mode
 *
 * !LINKSTO Kernel.Autosar.Autostart, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ActivateAutoTasks(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint16_t idx;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();

	idx = OS_startModeTasks[OS_GetAppMode()];

	while ( OS_autoStartTasks[idx] < (os_taskid_t)OS_GetNTasks() )
	{
		os_taskid_t tid = OS_autoStartTasks[idx];

		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2>, MISRAC2012-2 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
#pragma warning 549
		if (OS_GetCoreIdFromTaskId(tid) == myCoreId)
#pragma warning default
		{
			/* no way to propagate errors -> ignore return value */
			(void) OS_InternalActivateTask(tid);
		}
		idx++;
	}
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
