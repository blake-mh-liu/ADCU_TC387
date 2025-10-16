/* Mk_u_liberrorgetserviceidforcore.c
 *
 * This file contains the MK_ErrorGetServiceIdForCore() function.
 *
 * This function returns the service ID from the specified core's error-information structure.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>
#include <public/Mk_error.h>

/* MK_ErrorGetServiceIdForCore() returns the service ID from the specified core's error-information structure.
 *
 * The specified core index is the logical core ID.
 * CAVEAT: the service ID only has meaning if an error has occurred.
 *
 * !LINKSTO Microkernel.Function.MK_ErrorGetServiceIdForCore, 2
 * !doctype src
*/
mk_serviceid_t MK_ErrorGetServiceIdForCore(mk_objectid_t cIndex)
{
	mk_serviceid_t sid;
	mk_errorinfo_t *errorInfo = MK_GetErrorInfoForCore(cIndex);

	if ( errorInfo == MK_NULL )
	{
		sid = MK_sid_UnknownService;
	}
	else
	{
		sid = errorInfo->serviceId;
	}

	return sid;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
