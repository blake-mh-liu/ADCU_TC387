/* Mk_u_libgetapplicationid.c
 *
 * This file contains the GetApplicationID() function.
 *
 * This function gets the application ID of the calling thread.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <public/Mk_autosar.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>

/* GetApplicationID() - Gets the application ID of the caller.
 *
 * Relevant AUTOSAR requirements:
 *
 * [SWS_Os_00016] (Description) This service determines the OS-Application [...]
 * where the caller originally belongs to (was configured to).
 *
 * [SWS_Os_00261] GetApplicationID() shall return the application
 * identifier to which the executing Task/ISR/hook was configured.
 *
 * [SWS_Os_00262] If no OS-Application is running, GetApplicationID() shall
 * return INVALID_OSAPPLICATION.
 *
 * The description part of SWS_Os_00016 is badly worded, but SWS_Os_00261
 * makes it clear that the return value is the configured application of
 * the calling task, ISR or (app-specific) hook function - i.e. NOT a
 * trusted function.
 *
 * !LINKSTO      Microkernel.Function.GetApplicationID, 2
 * !doctype      src
*/
ApplicationType GetApplicationID(void)
{
	ApplicationType callerApp = INVALID_OSAPPLICATION;

	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
	mk_thread_t *currThread = coreVars->currentThread;
	mk_objecttype_t objtyp = currThread->objectType;

	if ( (objtyp == MK_OBJTYPE_TASK) ||
		 (objtyp == MK_OBJTYPE_ISR) )
	{
		callerApp = currThread->applicationId;
	}

	return callerApp;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
