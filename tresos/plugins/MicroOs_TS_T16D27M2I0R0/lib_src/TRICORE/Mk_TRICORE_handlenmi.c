/* Mk_TRICORE_handlenmi.c
 *
 * This file contains the function MK_HandleNmi()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_exceptionhandling.h>
#include <public/TRICORE/Mk_TRICORE_exceptioninfo.h>
#include <public/Mk_error.h>
#include <private/Mk_panic.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_exceptionhandling.h>
#include <private/Mk_thread.h>
#include <private/Mk_core.h>

#include <private/TRICORE/Mk_TRICORE_exceptionfunctions.h>

/* MK_HandleNmi()
 *
 * This function is entered via a jump instruction from the non-maskable interrupt exception vector.
 * The vector provides the thread's PCXI value and the TIN as parameters.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HandleNmi, 3
 * !doctype src
*/
void MK_HandleNmi(mk_uint32_t pcxiValue, mk_uint32_t d15Value)
{
	mk_kernelcontrol_t *coreVars = MK_TricoreGetCoreVarsException();

	/* Doesn't return if exception is not "sane" */
	MK_ExceptionHandlerCommon(pcxiValue, d15Value, coreVars, MK_exc_NMI, MK_FALSE);
	MK_FillExceptionInfo(coreVars, MK_exc_NMI, d15Value);

	if ( d15Value == MK_TIN_NonMaskableInterrupt )
	{
		MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_ProcessorSpecificException);
	}
	else
	{
		/* Panic exception info is not written: already called MK_FillExceptionInfo; no in-kernel exception. */
		MK_Panic(MK_panic_UndocumentedException);
	}

	MK_Dispatch(coreVars);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
