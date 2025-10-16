/* Mk_u_libgetcoreid.c
 *
 * This file contains the GetCoreID() function.
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
 *
 *
 * MISRAC2012-2) Deviated Rule: 5.5 (required)
 * Identifiers shall be distinct from macro names.
 *
 * Reason:
 * For single-core derivatives, the function is replaced by a function like macro.
 *
 *
 * MISRAC2012-3) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * For single-core derivatives, the function is replaced by a function like macro.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <public/Mk_autosar.h>
#include <public/Mk_public_api.h>

#if (MK_MAXCORES <= 1)
#error "GetCoreID() is not needed for single-core operation. Check your makefiles!"
#endif

/* GetCoreID() - Implements the AUTOSAR service.
 *
 * GetCoreID() returns the logical ID of the processor core on which it is called.
 *
 * !LINKSTO      Microkernel.Function.GetCoreID, 3
 * !doctype      src
*/
/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
CoreIdType GetCoreID(void)
{
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
	CoreIdType returnValue = coreVars->coreIndexLogical;

	return returnValue;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
