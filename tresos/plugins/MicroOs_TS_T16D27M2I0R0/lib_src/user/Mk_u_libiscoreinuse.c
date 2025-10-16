/* Mk_u_libiscoreinuse.c
 *
 * This file contains the MK_LibIsCoreInUse() function.
 *
 * This function tells whether the given core is under control of this microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>

/* MK_LibIsCoreInUse()
 *
 * This function tells whether the core with the given logical core ID is under control
 * of this microkernel. If an invalid logical core ID is passed, this function returns MK_FALSE.
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_boolean_t MK_LibIsCoreInUse(mk_objectid_t coreId)
{
	mk_boolean_t inUse = MK_FALSE;
	if ((0 <= coreId) && (coreId < (mk_objquantity_t)MK_MAXCORES))
	{
		mk_objectid_t coreIdPhy = MK_GetPhysicalCoreId(coreId);
		inUse = ((MK_coreProperties[coreIdPhy] & MK_COREPROP_STARTMASK) != MK_COREPROP_NOTUSED);
	}
	return inUse;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
