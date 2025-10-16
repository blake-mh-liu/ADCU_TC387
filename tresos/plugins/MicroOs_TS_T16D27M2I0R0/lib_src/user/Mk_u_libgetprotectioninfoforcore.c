/* Mk_u_libgetprotectioninfoforcore.c
 *
 * This file contains the MK_GetProtectionInfoForCore() function.
 *
 * This function returns the address of the protection info structure for the specified core or the current core.
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
#include <public/Mk_error.h>

/* MK_GetProtectionInfoForCore() returns the address of the protection info structure.
 *
 * If the specified logical core index is negative, the protection information for the
 * calling core is returned.
 *
 * !LINKSTO Microkernel.Function.MK_GetProtectionInfoForCore, 2
 * !doctype src
*/
mk_protectioninfo_t *MK_GetProtectionInfoForCore(mk_objectid_t cIndex)
{
	mk_kernelcontrol_t *coreVars;
	mk_protectioninfo_t *protectionInfo;

	if ( cIndex < 0 )
	{
		/* Deviation MISRAC2012-1 <+1> */
		coreVars = MK_GetCoreVarsFromThread();
		protectionInfo = MK_protectionInfo[coreVars->coreIndex];
	}
	else
	if ( cIndex < (mk_objquantity_t) MK_MAXCORES )
	{
		mk_objectid_t cIndexPhy = MK_GetPhysicalCoreId(cIndex);
		protectionInfo = MK_protectionInfo[cIndexPhy];
	}
	else
	{
		protectionInfo = MK_NULL;
	}

	return protectionInfo;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
