/* Mk_u_liblookupexceptioninfoforcore.c
 *
 * This file contains the MK_LibLookupExceptionInfoForCore() function.
 *
 * This function returns the address of the exception info structure for the specified core or the current core.
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

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_exceptionhandling.h>
#include <public/Mk_error.h>

/* MK_LibLookupExceptionInfoForCore() returns the address of the exception info structure.
 *
 * This is a helper function for MK_GetExceptionInfoForCore and MK_GetPanicExceptionInfoForCore.
 * It reads the exception info of the core with the given logical core index from the given table.
 * If the specified logical core index is negative, the exception information for the calling core is read.
 * If the logical core index is invalid, this function returns null.
 * This function is called from thread context.
 *
 * !LINKSTO Microkernel.Function.MK_LibLookupExceptionInfoForCore, 2
 * !doctype src
*/
mk_hwexceptioninfo_t *MK_LibLookupExceptionInfoForCore(
	mk_objectid_t cIndex,
	mk_hwexceptioninfo_t * const *exceptionInfoTable)
{
	mk_hwexceptioninfo_t *exceptionInfo = MK_NULL;

	if ( cIndex < 0 )
	{
		mk_kernelcontrol_t *coreVars;

		/* Deviation MISRAC2012-1 <+1> */
		coreVars = MK_GetCoreVarsFromThread();
		exceptionInfo = exceptionInfoTable[coreVars->coreIndex];
	}
	else
	if ( cIndex < (mk_objquantity_t) MK_MAXCORES )
	{
		mk_objectid_t cIndexPhy = MK_GetPhysicalCoreId(cIndex);
		exceptionInfo = exceptionInfoTable[cIndexPhy];
	}
	else
	{
		/* MISRA */
	}

	return exceptionInfo;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
