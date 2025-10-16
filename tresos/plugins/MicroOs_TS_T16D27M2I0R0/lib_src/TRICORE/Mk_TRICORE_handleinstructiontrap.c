/* Mk_TRICORE_handleinstructiontrap.c
 *
 * This file contains the function MK_HandleInstructionTrap()
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

/* MK_HandleInstructionTrap()
 *
 * This function is entered via a jump instruction from the instruction exception vector.
 * The vector provides the thread's PCXI value and the TIN as parameters.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HandleInstructionTrap, 2,
 * !        Microkernel.TRICORE.Exception.ReportProtectionFault, 1
 * !doctype src
*/
void MK_HandleInstructionTrap(mk_uint32_t pcxiValue, mk_uint32_t d15Value)
{
	mk_kernelcontrol_t *coreVars = MK_TricoreGetCoreVarsException();

	/* Doesn't return if exception is not "sane" */
	MK_ExceptionHandlerCommon(pcxiValue, d15Value, coreVars, MK_exc_InstructionError, MK_FALSE);
	MK_FillExceptionInfo(coreVars, MK_exc_InstructionError, d15Value);

	if ( (d15Value == MK_TIN_IllegalOpcode) ||
		 (d15Value == MK_TIN_UnimplementedOpcode) ||
		 (d15Value == MK_TIN_InvalidOperandspecification) )
	{
		MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_IllegalInstructionException);
	}
	else
	if ( (d15Value == MK_TIN_DataAddressAlignment) )
	{
		MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_AlignmentException);
	}
	else
	if ( (d15Value == MK_TIN_InvalidLocalMemoryAddress) )
	{
		MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_MemoryProtectionException);
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
