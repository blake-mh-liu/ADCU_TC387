/* Mk_k_sysaddoncontrol.c
 *
 * This file contains the MK_SysAddOnControl() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * The functions of add-on framework return their value and status as fixed length types.
 * The status is translated back to check for errors.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_addon.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>

/*
 * MK_SysAddOnControl() handles add-on control system calls
 *
 * This function is the kernel-side part of the "AddOnControl()" API, which also implements
 * an extensible API to support various optional modules.
 *
 * !LINKSTO Microkernel.Function.MK_SysAddOnControl, 1
 * !doctype src
*/
void MK_SysAddOnControl(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t addOnIndex = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_parametertype_t p1 = MK_HwGetParameter2(caller->regs);
	mk_parametertype_t p2 = MK_HwGetParameter3(caller->regs);
	mk_parametertype_t p3 = MK_HwGetParameter4(caller->regs);
	const mk_addondescriptor_t *addOn;
	mk_statusandvalue_t sr;
	mk_errorid_t errorid;

	sr.statusCode = MK_eid_Unknown;
	sr.requestedValue = 0u;

	/* Explicit cast to prevent compiler warning (ok, as the number of add-ons is always >= 0).
	*/
	if ( addOnIndex < (mk_parametertype_t)MK_nAddOns )
	{
		addOn = MK_addOnTable[addOnIndex];
		sr = (*addOn->ctrlFunc)(coreVars, addOn, p1, p2, p3);
	}
	else
	{
		sr.statusCode = MK_eid_InvalidAddOnId;
	}

	/* Deviation MISRAC2012-1 <+1> */
	errorid = (mk_errorid_t) sr.statusCode;

	/* This ensures that the requested information is always defined.
	*/
	if ( errorid < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorid);
		MK_HwSetReturnValue2(caller->regs, sr.requestedValue);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_AddOnControl, errorid, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
