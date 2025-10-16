/* Mk_u_libgetcurrentapplicationid.c
 *
 * This file contains the GetCurrentApplicationID() function.
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

/* GetCurrentApplicationID() - Gets the application ID of the caller.
 *
 * Relevant AUTOSAR requirements:
 *
 * [SWS_Os_00797] (Description) This service [GetCurrentApplicationID()]
 * determines the OS-Application where the caller of the service is currently
 * executing.
 * Note that if the caller is not within a CallTrustedFunction() call the
 * value is equal to the result of GetApplicationID().
 *
 * [SWS_Os_00798] GetCurrentApplicationID() shall return the application
 * identifier in which the current Task/ISR/hook is executed.
 *
 * [SWS_Os_00799] If no OS-Application is running, GetCurrentApplicationID()
 * shall return INVALID_OSAPPLICATION.
 *
 * SWS_Os_00798 is badly stated, because there's a concept of "current task"
 * that AUTOSAR inherits from OSEK, and a concept of "current ISR" that
 * AUTOSAR defines itself, and there can be both a current task and a current
 * ISR at the same time, belonging to different OS-applications. But the
 * description part of SWS_Os_00797 makes it clear that this concept of
 * "current" doesn't apply here.
 *
 * !LINKSTO      Microkernel.Function.GetCurrentApplicationID, 1
 * !doctype      src
*/
ApplicationType GetCurrentApplicationID(void)
{
	ApplicationType callerApp = INVALID_OSAPPLICATION;

	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
	mk_thread_t *currThread = coreVars->currentThread;
	mk_objecttype_t objtyp = currThread->objectType;
	mk_thread_t *parent;

	if ( (objtyp == MK_OBJTYPE_TASK) || (objtyp == MK_OBJTYPE_ISR) )
	{
		callerApp = currThread->applicationId;
	}
	else
	if ( objtyp == MK_OBJTYPE_TRUSTEDFUNCTION )
	{
		parent = currThread->parentThread;

		/* If the parent of the trusted function was terminated, there could be another thread
		 * in the thread slot referenced by parent. However, this thread can't be started, yet,
		 * because the TF thread must currently have a equal or higher priority than threads in this thread slot.
		 * If 'parent' isn't READY, the caller was terminated, so we can't determine its application
		 * and, therefore, return INVALID_OSAPPLICATION.
		*/
		if ( (parent != MK_NULL) && (parent->state == MK_THS_READY) )
		{
			callerApp = parent->applicationId;
		}
	}
	else
	{
		/* Nothing to do, since callerApp is already INVALID_OSAPPLICATION. */
	}

	return callerApp;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
