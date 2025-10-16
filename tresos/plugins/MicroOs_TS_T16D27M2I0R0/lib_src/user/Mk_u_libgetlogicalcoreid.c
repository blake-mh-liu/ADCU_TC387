/* Mk_u_libgetlogicalcoreid.c
 *
 * This file contains the MK_GetLogicalCoreId() function.
 * It returns the logical ID of the given physical ID
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
#error "MK_GetLogicalCoreId() is not needed for single-core operation. Check your makefiles!"
#endif

/*!
 * MK_GetLogicalCoreId() - Returns the logical ID of the given physical ID.
 *
 * This function returns the corresponding logical ID to the given physical ID.
 * If an invalid core ID (< 0 || >= MAXCORES) is passed, the result is the given core ID,
 * since some functions will then work with the core id on which the thread runs.
 *
 * !LINKSTO      Microkernel.Function.MK_GetLogicalCoreId, 2
 * !doctype      src
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
mk_objectid_t MK_GetLogicalCoreId(mk_objectid_t core)
{
	mk_objectid_t logcore;
	if ((core < 0) || (core >= (mk_objectid_t) MK_MAXCORES))
	{
		logcore = core;
	}
	else
	{
		logcore = MK_alciPhyToLog[core];
	}
	return logcore;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/

