/* Mk_u_libcalltrustedfunction.c
 *
 * This file contains the CallTrustedFunction() function.
 *
 * This function is called from a thread to call a trusted function.
 * The return value of MK_E_TRYAGAIN is handled by this function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.6 (required)
 *  A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 *  The microkernel API uses the type 'mk_parametertype_t' to pass data back
 *  and forth. This type ensures, that all bits of an object are preserved.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>

/* CallTrustedFunction() - Implements the AUTOSAR API.
 *
 * !LINKSTO      Microkernel.Function.CallTrustedFunction, 2
 * !doctype      src
*/
StatusType CallTrustedFunction(TrustedFunctionIndexType tfId, TrustedFunctionParameterRefType p)
{
	StatusType returnValue;

	do
	{
		/* Deviation MISRAC2012-1 <+1> */
		returnValue = (StatusType)MK_UsrCallTrustedFunction((mk_objectid_t)tfId, (mk_parametertype_t)p);
	} while ( returnValue == (StatusType)MK_E_TRYAGAIN );

	return returnValue;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
