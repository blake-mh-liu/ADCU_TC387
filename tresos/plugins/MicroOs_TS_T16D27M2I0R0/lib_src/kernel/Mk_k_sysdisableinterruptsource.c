/* Mk_k_sysdisableinterruptsource.c
 *
 * This file contains the function MK_SysDisableInterruptSource().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_isr.h>
#include <private/Mk_errorhandling.h>

/* MK_SysDisableInterruptSource() disables an interrupt source belonging to an ISR.
 * First, a range check on the ISR id is performed.
 * Afterwards, the interrupt source is disabled.
 *
 * !LINKSTO Microkernel.Function.MK_SysDisableInterruptSource, 2
 * !doctype src
*/
void MK_SysDisableInterruptSource(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t isrId = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_errorid_t errorCode = MK_eid_Unknown;

	/* Range-check on the ISR id
	 * Explicit cast to prevent compiler warning (ok, as the number of ISRs is always >= 0).
	*/
	if ( isrId < (mk_parametertype_t)MK_nIsrs )
	{
		errorCode = MK_InternDisableInterruptSource(coreVars, (mk_objectid_t)isrId, caller->applicationId);
	}
	else
	{
		errorCode = MK_eid_InvalidIsrId;
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_DisableInterruptSource, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
