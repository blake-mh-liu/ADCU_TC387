/* Mk_k_errorinternaltoosek.c
 *
 * This file contains a table and a function to convert internal error codes
 * to AUTOSAR error codes.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 14.3 (required)
 *  Controlling expressions shall not be invariant.
 *
 * Reason:
 *  A range check for both boundaries is safer than for just one boundary.
 *  The eid variable is passed by the caller and could also have invalid values.
 *
 * MISRAC2012-2) Deviated Rule: 8.9 (advisory)
 *  An object should be defined at block scope if its identifier only appears
 *  in a single function.
 *
 * Reason:
 *  The definition at file scope is necessary to have more precise control over
 *  where this object is located in memory by the linker.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *   Pointless comparison of unsigned integer with zero.
 *
 * Reason:
 *   mk_errorid_t is not necessarily unsigned. It is implementation defined which integral type is used for an enum.
 *   The >= 0 test here is necessary because the enumerated type mk_errorid_t could be signed and
 *   the incoming value could be less than 0.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>

/* MK_ERRORLOOKUP is used to construct the lookup table. The 'internal' parameter is for documentation only
*/
#define MK_ERRORLOOKUP(internal, osek)		(osek)

/* MK_errorInternalToOsekTable[] - an array to convert internal error codes to AUTOSAR E_OS_xxx codes.
 *
 * This table provides a lookup from internal error code (MK_eid_*) to AUTOSAR-defined error codes (E_OS_*).
 * Each entry in the table contains an AUTOSAR code; the internal code is used as the index.
 * Therefore the entries in this table must be in the same order as the values in the mk_errorid_e
 * enumeration.
 *
 * The initializer for the lookup table is defined in a header file. This permits a simple unit
 * test to be devised that verifies that all error codes are listed, and in the correct order.
*/
/* Deviation MISRAC2012-2 */
static const mk_osekerror_t MK_errorInternalToOsekTable[MK_eid_Unknown+1]= { MK_ERRORLOOKUPTABLE };

/* MK_ErrorInternalToOsek() converts an internal errorcode to an AUTOSAR error code using the above table.
 *
 * !LINKSTO Microkernel.Function.MK_ErrorInternalToOsek, 2
 * !doctype src
*/
mk_osekerror_t MK_ErrorInternalToOsek(mk_errorid_t eid)
{
	mk_osekerror_t osekError;

	/* Possible diagnostic TOOLDIAG-1 <+2> */
	/* Deviation MISRAC2012-1 <+1> */
	if ( (eid >= MK_eid_NoError) && (eid < MK_eid_Unknown) )
	{
		osekError = MK_errorInternalToOsekTable[eid];
	}
	else
	{
		osekError = MK_E_ERROR;
	}

	return osekError;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
