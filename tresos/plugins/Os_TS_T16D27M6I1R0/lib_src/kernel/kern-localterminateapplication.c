/* kern-localterminateapplication.c
 *
 * This file contains the OS_LocalTerminateApplication() function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#define OS_SID	OS_SID_TerminateApplication
#define OS_SIF	OS_svc_TerminateApplication

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_LocalTerminateApplication
 *
 * This function implements part of TerminateApplication().
 * It terminates the application 'app'.
 * If the restart option is set to OS_APPL_RESTART the restart task is activated.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_LocalTerminateApplication(const os_appcontext_t *app, os_restart_t restart)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t result = OS_ERRORCODE_NOCHECK(OS_ERROR_NoError);
	os_appdynamic_t *appd = app->dynamic;

	/* !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication.Restart.Wrongstate, 1
	*/
	if ( appd->appstate != OS_APP_ACCESSIBLE )
	{
		result = OS_ERRORCODE_CHECK(OS_ERROR_ApplicationNotAccessible);
	}
	else
	{
		/* !LINKSTO Kernel.Autosar.OsApplication.Termination, 1
		*/
		OS_QUARANTINEAPPLICATION(app);

		if ( restart == OS_APPL_RESTART )
		{
			/* !LINKSTO Kernel.Autosar.API.SystemServices.TerminateApplication.Restart, 1
			*/
			OS_RESTARTAPPLICATION(app);
		}
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_localterminateapplication_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
