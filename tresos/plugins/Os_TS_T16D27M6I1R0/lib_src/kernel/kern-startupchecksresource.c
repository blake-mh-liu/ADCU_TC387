/* kern-startupchecksresource.c
 *
 * This file contains the OS_StartupChecksResource function.
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
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *   Condition is always true.
 *
 * Reason: This warning depends on the number of configured cores.
 *   Only in case of a single core configuration, this comparison can be evaluated at compile time.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_panic.h>

#include <memmap/Os_mm_code_begin.h>

OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_StartupChecksResource(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t result = OS_E_OK;
	os_resourceid_t i;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	const os_coreid_t myCoreId = OS_GetMyCoreId();

	for (i = 0; i < OS_nResources; i++)
	{
		const os_resource_t * const resource = &OS_resourceTableBase[i];
		const os_appcontext_t * const app = OS_GET_APP(resource->app);

		/* !LINKSTO Kernel.Feature.StartupChecks.Resource.NoOwningApplication, 1 */
		if ( OS_AppIsNull(app) )
		{
			result = OS_PANIC(OS_PANIC_SCHK_NoOwningApplication);
		}

		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		if (OS_GetResourceCoreId(resource) == myCoreId)
		{
			const os_permission_t perms = OS_GET_APP(resource->permissions);

			/* !LINKSTO Kernel.Feature.StartupChecks.Resource.NoApplicationPermission, 1 */
			if ( !OS_HasPermission(app, perms) )
			{
				result = OS_PANIC(OS_PANIC_SCHK_OwningApplicationHasNoPermission);
			}
		}
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_startupchecksresource_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
