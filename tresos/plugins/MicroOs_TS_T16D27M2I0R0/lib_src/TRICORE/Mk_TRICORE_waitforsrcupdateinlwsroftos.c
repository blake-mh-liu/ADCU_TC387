/* Mk_TRICORE_waitforsrcupdateinlwsroftos.c
 *
 * This file implements the function MK_WaitForSrcUpdateInLwsrOfTos().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 5.5 (required)
 * Identifiers shall be distinct from macro names.
 *
 * Reason:
 * Depending on the architecture, an extra check is required before calling MK_WaitForSrcUpdateInLwsr.
 * If this is not the case, MK_WaitForSrcUpdateInLwsrOfTos is just mapped to MK_WaitForSrcUpdateInLwsr
 * using a function like macro.
 *
 *
 * MISRAC2012-2) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * Depending on the architecture, an extra check is required before calling MK_WaitForSrcUpdateInLwsr.
 * If this is not the case, MK_WaitForSrcUpdateInLwsrOfTos is just mapped to MK_WaitForSrcUpdateInLwsr
 * using a function like macro.
*/

#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>

#if (!MK_HAS_INVALID_TOS_VALUES)
#error "This file is not meant for this derivative."
#endif

/* MK_WaitForSrcUpdateInLwsrOfTos(tos, oldSrcValue)
 *
 * Calls MK_WaitForSrcUpdateInLwsr() if the TOS is valid. Otherwise there's nothing to wait for.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_ReconfigureSrnSrc, 1
*/
/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
void MK_WaitForSrcUpdateInLwsrOfTos(mk_uint32_t tos, mk_uint32_t oldSrcValue)
{
	if (MK_IsValidTosValue(tos))
	{
		MK_WaitForSrcUpdateInLwsr(MK_GetIcuRegsFromTosUnchecked(tos), oldSrcValue);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
