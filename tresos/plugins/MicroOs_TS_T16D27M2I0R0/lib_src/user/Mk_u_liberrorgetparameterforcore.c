/* Mk_u_liberrorgetparameterforcore.c
 *
 * This file contains the MK_ErrorGetParameterForCore() function.
 *
 * This function returns the specified parameter from the specified core's error-information structure.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 12.4 (advisory)
 * Evaluation of constant expressions should not lead to unsigned integer
 * wrap-around.
 *
 * Reason:
 * Intentional wrap-around to represent an invalid value.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>
#include <public/Mk_error.h>

/* MK_ErrorGetParameterForCore() returns the specified parameter from the core's error information.
 *
 * If the specified logical core index is negative, the error information for the calling core is returned.
 *
 * Parameter:
 *  paramNo - parameter number, 1..4
 *
 * !LINKSTO Microkernel.Function.MK_ErrorGetParameterForCore, 3
 * !doctype src
*/
mk_parametertype_t MK_ErrorGetParameterForCore(mk_objectid_t cIndex, mk_int_t paramNo)
{
	/* Deviation MISRAC2012-1 <+1> */
	mk_parametertype_t pVal = (mk_parametertype_t)(-1);
	mk_errorinfo_t *errorInfo;

	if ( (paramNo >= 1) && (paramNo <= 4) )
	{
		errorInfo = MK_GetErrorInfoForCore(cIndex);

		if ( errorInfo != MK_NULL )
		{
			pVal = errorInfo->parameter[paramNo-1];
		}
	}

	return pVal;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
