/* Mk_u_libgetpanicexceptioninfoforcore.c
 *
 * This file contains the MK_GetPanicExceptionInfoForCore() function.
 *
 * This function returns the address of the panic exception info structure for the specified core or the current core.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_exceptionhandling.h>
#include <public/Mk_exceptioninfo.h>

/* MK_GetPanicExceptionInfoForCore() returns the address of the panic exception info structure.
 *
 * If the specified logical core index is negative, the panic exception information for the calling core is returned.
 *
 * !LINKSTO Microkernel.Function.MK_GetPanicExceptionInfoForCore, 2
 * !doctype src
*/
mk_hwexceptioninfo_t *MK_GetPanicExceptionInfoForCore(mk_objectid_t cIndex)
{
	mk_hwexceptioninfo_t *exi = MK_NULL;

	exi = MK_LibLookupExceptionInfoForCore(cIndex, MK_panicExceptionInfo);

	return exi;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
