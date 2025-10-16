/* kern-appisaccessible.c
 *
 * This file contains the OS_AppIsAccessible() function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_AppIsAccessible
 *
 * Returns OS_TRUE if the specified application is accessible by the caller.
 *
 * !LINKSTO Kernel.Autosar.OsApplication.ApplicationStates, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_boolean_t OS_AppIsAccessible(const os_appcontext_t *app)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_boolean_t result;

	/* COVPT-1 */
	if ( app == OS_NULL )
	{
		result = OS_TRUE;
	}
	else
	{
		switch ( app->dynamic->appstate )
		{
		case OS_APP_ACCESSIBLE:
			result = OS_TRUE;
			break;

		case OS_APP_RESTARTING:
			/* If this is a cross core request, OS_CurrentApp will return OS_NULL,
			 * because OS_CrossCoreNotifyIsr() sets the inFunction flag to OS_ININTERNAL.
			 * Therefore, an AppIsAccessible request from another core, will always return OS_FALSE,
			 * if 'app' is the current application and restarting - which is the correct behavior.
			*/
			if ( app == OS_CurrentApp() )
			{
				result = OS_TRUE;
			}
			else
			{
				result = OS_FALSE;
			}
			break;

		case OS_APP_QUARANTINED:
		default:
			result = OS_FALSE;
			break;
		}
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_appisaccessible_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
