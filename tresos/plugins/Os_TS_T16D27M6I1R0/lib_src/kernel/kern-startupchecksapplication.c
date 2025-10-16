/* kern-startupchecksapplication.c
 *
 * This file contains the OS_StartupChecksApplication function.
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
 * TOOLDIAG-1) Possible diagnostic: GNUStatementExpressionExtension
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
os_result_t OS_StartupChecksApplication(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t result = OS_E_OK;

	/* COVPT-1 +3 */
	/* Deviation MISRAC2012-1 <+2> */
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	if (OS_GetMyCoreId() == (os_coreid_t)OS_INITCORE)
	{
		os_unsigned_t i;
		os_permission_t permBits = 0;

		for ( i = 0; i < OS_nApps; i++ )
		{
			os_appcontext_t const* const app = &OS_appTableBase[i];

			/* !LINKSTO Kernel.Feature.StartupChecks.Application.WrongIndex, 1 */
			if (  app->appId != i )
			{
				result = OS_PANIC(OS_PANIC_SCHK_AppIdIsNotIndexInAppTable);
			}

			/* !LINKSTO Kernel.Feature.StartupChecks.Application.WrongConfId, 1 */
			if (  *app->buildId != OS_configurationId )
			{
				result = OS_PANIC(OS_PANIC_SCHK_AppConfigurationIdMismatch);
			}

			/* !LINKSTO Kernel.Feature.StartupChecks.Application.RestartTaskNotOwned, 1 */
			if ( app->restartTask != OS_NULLTASK )
			{
				if ( OS_GET_APP(OS_taskTableBase[app->restartTask].app) != app )
				{
					result = OS_PANIC(OS_PANIC_SCHK_AppRestartTaskNotMemberOfApp);
				}
			}

			/* !LINKSTO Kernel.Feature.StartupChecks.Application.NoPermission, 1 */
			if ( app->permissionBit == 0u )
			{
				result = OS_PANIC(OS_PANIC_SCHK_AppHasNoPermissions);
			}

			/* System applications have all bits set in their permissionBit field, because they
			 * may access any object. Hence, their permission identification value, i.e. 'permissionBit',
			 * is not unique.
			 *
			 * !LINKSTO Kernel.Feature.StartupChecks.Application.PermissionNotUnique, 1
			 */
			if ( !OS_AppIsSystemApp(app) )
			{
				if ( (permBits & app->permissionBit) != 0u )
				{
					result = OS_PANIC(OS_PANIC_SCHK_AppPermissionBitNotUnique);
				}

				permBits |= app->permissionBit;
			}
		}
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_startupchecksapplication_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
