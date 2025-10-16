/* Mk_u_libgetexceptioninfoforcore.c
 *
 * This file contains the MK_GetExceptionInfoForCore() function.
 *
 * This function returns the address of the exception info structure for the specified core or the current core.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_exceptionhandling.h>
#include <public/Mk_exceptioninfo.h>

/* MK_GetExceptionInfoForCore() returns the address of the exception info structure.
 *
 * If the specified logical core index is negative, the exception information for the calling core is returned.
 *
 * !LINKSTO Microkernel.Function.MK_GetExceptionInfoForCore, 3
 * !doctype src
*/
mk_hwexceptioninfo_t *MK_GetExceptionInfoForCore(mk_objectid_t cIndex)
{
	mk_hwexceptioninfo_t *exi = MK_NULL;

	exi = MK_LibLookupExceptionInfoForCore(cIndex, MK_exceptionInfo);

	return exi;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
