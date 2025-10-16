/* kern-initcounters.c
 *
 * This file contains the OS_InitCounters() function.
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
 * The invariance depends on the configuration. In single-core systems,
 * for example, the expression is always true.
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

/*!
 * OS_InitCounters
 *
 * The 'head' of each counter's alarm queue needs to be set to NULLALARM.
 * This is because the default .bss section value (0) is a valid alarm id.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitCounters(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_counterid_t i;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();

	for (i = 0; i < OS_nCounters; ++i)
	{
		os_counter_t const * const cs = &OS_counterTableBase[i];
		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2>, MISRAC2012-2 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
#pragma warning 549
		if (OS_GetCoreIdFromCounterId(i) == myCoreId)
#pragma warning default
		{
			cs->dynamic->head = OS_NULLALARM;
		}
	}
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
