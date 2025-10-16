/* kern-initresources.c
 *
 * This file contains the OS_InitResources function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * For single-core configurations, the expression is always true.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: UnusedVariable
 *   Variable is never used.
 *
 * Reason: Not an issue, variable will be used if there are at least two cores.
 *
 * TOOLDIAG-2) Possible diagnostic: PointlessComparison
 *   Condition is always true.
 *
 * Reason: This warning depends on the number of configured cores.
 *   Only in case of a single core configuration, this comparison can be evaluated at compile time.
 *
 * TOOLDIAG-3) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/* OS_InitResources
 *
 * The dynamic data for each resource needs initializing because the default
 * bss value of 0 has an unwanted meaning in the kernel.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitResources(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_unsigned_t i;
	/* Possible diagnostic TOOLDIAG-3 <+1> */
	os_coreid_t const myCore = OS_GetMyCoreId();

	for (i = 0; i < OS_nResources; ++i)
	{
		/* Possible diagnostic TOOLDIAG-1 <1> */
		os_resource_t const * const rs = &OS_resourceTableBase[i];
		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		if (OS_GetResourceCoreId(rs) == myCore)
		{
			os_resourcedynamic_t * const rd = OS_ResourceGetDynamic(i);
			rd->lastPrio = 0;
			rd->takenBy = OS_NULLTASK;
			rd->next = OS_NULLOBJECT;
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_initresources_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
