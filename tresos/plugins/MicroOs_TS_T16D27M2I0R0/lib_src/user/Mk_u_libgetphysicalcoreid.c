/* Mk_u_libgetphysicalcoreid.c
 *
 * This file contains the MK_GetPhysicalCoreId() function.
 * It returns the physical ID of the given logical ID
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 5.5 (required)
 * Identifiers shall be distinct from macro names.
 *
 * Reason:
 * For single-core derivatives, the function is replaced by a function like macro.
 *
 *
 * MISRAC2012-2) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * For single-core derivatives, the function is replaced by a function like macro.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>

#if (MK_MAXCORES <= 1)
#error "MK_GetPhysicalCoreId() is not needed for single-core operation. Check your makefiles!"
#endif

/*!
 * MK_GetPhysicalCoreId() - Returns the physical ID of the given logical ID.
 *
 * This function returns the corresponding physical ID to the given logical ID.
 * If an invalid core ID (< 0 || >= MAXCORES) is passed, the result is the given core ID,
 * since some functions will then work with the core id on which the thread runs.
 *
 * !LINKSTO      Microkernel.Function.MK_GetPhysicalCoreId, 2
 * !doctype      src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
mk_objectid_t MK_GetPhysicalCoreId(mk_objectid_t core)
{
	mk_objectid_t phycore;
	if ((core < 0) || (core >= (mk_objectid_t) MK_MAXCORES))
	{
		phycore = core;
	}
	else
	{
		phycore = MK_alciLogToPhy[core];
	}
	return phycore;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/

