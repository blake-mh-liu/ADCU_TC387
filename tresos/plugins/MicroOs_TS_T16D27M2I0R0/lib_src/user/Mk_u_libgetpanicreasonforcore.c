/* Mk_u_libgetpanicreasonforcore.c
 *
 * This file contains the MK_GetPanicReasonForCore() function.
 *
 * This function returns the panic reason for the specified core.
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

/* MK_GetPanicReasonForCore() returns the panic reason.
 *
 * If the specified logical core index is negative, the panic reason for the calling core is returned.
 * If the specified logical core index represents a valid core, the panic reason for that core is returned.
 * If the specified logical core index is greater than the indexes of the valid cores, the panic reason
 * MK_panic_Unknown is returned.
 *
 * !LINKSTO Microkernel.Function.MK_GetPanicReasonForCore, 2
 * !doctype src
*/
mk_panic_t MK_GetPanicReasonForCore(mk_objectid_t cIndex)
{
	mk_kernelcontrol_t *coreVars = MK_NULL;
	mk_panic_t panicReason = MK_panic_Unknown;

	if ( cIndex < 0 )
	{
		/* Deviation MISRAC2012-1 <+1> */
		coreVars = MK_GetCoreVarsFromThread();
	}
	else
	if ( cIndex < (mk_objquantity_t) MK_MAXCORES )
	{
		mk_objectid_t cIndexPhy = MK_GetPhysicalCoreId(cIndex);
		coreVars = MK_coreTable[cIndexPhy];
	}
	else
	{
		/* MISRA */
	}

	if ( coreVars != MK_NULL )
	{
		panicReason = coreVars->panicReason;
	}

	return panicReason;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
