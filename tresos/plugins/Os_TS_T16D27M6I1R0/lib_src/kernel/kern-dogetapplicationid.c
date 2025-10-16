/* kern-dogetapplicationid.c
 *
 * This file contains the OS_KernGetApplicationId function
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
 * OS_DoGetApplicationId gets the "id" of the currently running application.
 *
 * The id of the current application (or OS_NULLAPP if none) is
 * returned.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.GetApplicationID, 4
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_applicationid_t OS_DoGetApplicationId(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_uint8_t inFunction = kernel_data->inFunction;
	os_applicationid_t a = OS_NULLAPP;
	const os_appcontext_t *app = OS_NULL;

	{

		switch (inFunction)
		{
		case OS_INTASK:
			/* The current app is the current task's
			 * application.
			*/
			/* COVPT-1 */
			if ( kernel_data->taskCurrent != OS_NULL )
			{
				app = OS_GET_APP(kernel_data->taskCurrent->app);
			}
			break;

		case OS_INCAT1:
		case OS_INCAT2:
			/* The current app is the current ISR's
			 * application.
			*/
			if ( kernel_data->isrCurrent < OS_nInterrupts )
			{
				app = OS_GET_APP(OS_isrTableBase[kernel_data->isrCurrent].app);
			}
			break;
		
		case OS_INERRORHOOK:
		case OS_INSTARTUPHOOK:
		case OS_INSHUTDOWNHOOK:
			/* In this case, it might be
 			 * app specific error,startup or shutdown hook.
			 * For global hooks the kernel_data->hookApp will be NULL.
 			*/
			app = kernel_data->hookApp;
			break;

		default:
			/* In all other cases, we just fall through leaving app at OS_NULL.
			 * Protection Hook, Pre and Post task/ISR hooks,ACBs and Trusted functions.
			*/
			break;
		}

		/* Now we look up the app's ID
		*/
		if ( !OS_AppIsNull(app) )
		{
			a = app->appId;
		}
	}

	return a;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_dogetapplicationid_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
