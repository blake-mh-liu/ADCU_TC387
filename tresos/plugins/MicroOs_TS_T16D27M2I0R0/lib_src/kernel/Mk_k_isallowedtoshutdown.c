/* Mk_k_isallowedtoshutdown.c
 *
 * This file contains the MK_IsAllowedToShutdown() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_shutdown.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>

/*
 * MK_IsAllowedToShutdown() tells whether the given thread is allowed to shut down.
 *
 * This is a helper function for MK_SysShutdown and MK_SysShutdownAllCores.
 * A thread is allowed to call shutdown,
 *  if it has 'flag' set in its application's globalPermissions field, or
 *  if it does not belong to an OS application (e.g. hook).
 *
 * Parameters:
 *	caller	- The thread whose permissions are to be checked.
 *	flag	- The bit pattern representing the shutdown which is requested in the globalPermissions field.
*/
mk_boolean_t MK_IsAllowedToShutdown(mk_thread_t *caller, mk_uint32_t flag)
{
	mk_objectid_t callerAppId = caller->applicationId;
	mk_boolean_t allowed = MK_FALSE;

	/* Do not shut down, unless the caller's application has the appropriate permission.
	*/
	if ((0 <= callerAppId) && (callerAppId < MK_nApps))
	{
		/* This object has an application, so have a look at its permissions. */
		allowed = ((MK_appCfg[callerAppId].globalPermissions & flag) != 0u);
	}
	else if (callerAppId == -1)
	{
		/* This object has no application, so it might be a hook.
		 * Permission check is intended for tasks and ISRs belonging to an OS application.
		 * Therefore, anything not belonging to an OS application is allowed to call Shutdown*.
		*/
		allowed = MK_TRUE;
	}
	else
	{
		/* Got an invalid application id, so don't grant access to shutdown.
		 * 'allowed' is already false.
		*/
	}
	return allowed;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
