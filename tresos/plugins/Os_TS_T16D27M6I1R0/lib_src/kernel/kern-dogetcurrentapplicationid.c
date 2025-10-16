/* kern-dogetcurrentapplicationid.c
 *
 * This file contains the OS_KernGetCurrentApplicationId function
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
 * OS_DoGetCurrentApplicationId gets the "id" of the currently running application.
 *
 * The id of the current application (or OS_NULLAPP if none) is
 * returned.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.GetCurrentApplicationID, 2
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_applicationid_t OS_DoGetCurrentApplicationId(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_uint8_t inFunction = kernel_data->inFunction;
	os_applicationid_t a = OS_NULLAPP;
	const os_appcontext_t *app = OS_NULL;

	if( inFunction == OS_INTRUSTED )
	{
		if ( (kernel_data->isrCurrent < OS_nInterrupts) && (kernel_data->tfCalledFrom == OS_INCAT2) )
		{
			app = OS_GET_APP(OS_isrTableBase[kernel_data->isrCurrent].app);
		}
		else
		{
			/* Called from task */
			app = OS_GET_APP(OS_GetKernelData()->taskCurrent->app);
		}
		/* Now we look up the app's ID
		*/
		/* COVPT-1 */
		if ( !OS_AppIsNull(app) )
		{
			a = app->appId;
		}
	}
	else
	{
		a = OS_DoGetApplicationId();
	}

	return a;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_dogetcurrentapplicationid_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
