/* Mk_u_libgeterrorinfoforcore.c
 *
 * This file contains the MK_GetErrorInfoForCore() function.
 *
 * This function returns the address of the error info structure for the specified core or the current core.
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
#include <public/Mk_error.h>

/* MK_GetErrorInfoForCore() returns the address of the error info structure.
 *
 * If the specified logical core index is negative, the error information for the
 * calling core is returned.
 *
 * !LINKSTO Microkernel.Function.MK_GetErrorInfoForCore, 2
 * !doctype src
*/
mk_errorinfo_t *MK_GetErrorInfoForCore(mk_objectid_t cIndex)
{
	mk_kernelcontrol_t *coreVars;
	mk_errorinfo_t *errorInfo = MK_NULL;

	if ( cIndex < 0 )
	{
		/* Deviation MISRAC2012-1 <+1> */
		coreVars = MK_GetCoreVarsFromThread();
		errorInfo = MK_errorInfo[coreVars->coreIndex];
	}
	else
	if ( cIndex < (mk_objquantity_t) MK_MAXCORES )
	{
		mk_objectid_t cIndexPhy = MK_GetPhysicalCoreId(cIndex);
		errorInfo = MK_errorInfo[cIndexPhy];
	}
	else
	{
		/* MISRA */
	}

	return errorInfo;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
