/* Mk_TRICORE_handlebuserrortrap.c
 *
 * This file contains the function MK_HandleBusErrorTrap()
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

/* MK_HandleBusErrorTrap()
 *
 * This function is entered via a jump instruction from the System Bus and Peripheral Errors exception vector.
 * The vector provides the thread's PCXI value and the TIN as parameters.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HandleBusErrorTrap, 2,
 * !        Microkernel.TRICORE.Exception.ReportProtectionFault, 1
 * !doctype src
*/
void MK_HandleBusErrorTrap(mk_uint32_t pcxiValue, mk_uint32_t d15Value)
{
	mk_kernelcontrol_t *coreVars = MK_TricoreGetCoreVarsException();
	mk_boolean_t returnOnPreempt;

	/* For MK_TIN_TemporalAsynchronousError:
	 *  Exit (without storing register in the current thread) if the exception has occurred in the kernel.
	 *  This is the only case where such re-entrance is permitted.
	 * Otherwise:
	 *  Panic if the exception has occurred in the kernel.
	*/
	returnOnPreempt = (d15Value == MK_TIN_TemporalAsynchronousError);
	MK_ExceptionHandlerCommon(pcxiValue, d15Value, coreVars, MK_exc_SystemBus, returnOnPreempt);
	MK_FillExceptionInfo(coreVars, MK_exc_SystemBus, d15Value);

	if ( (d15Value == MK_TIN_ProgramFetchSynchronousError) ||
		 (d15Value == MK_TIN_DataAccessSynchronousError) ||
		 (d15Value == MK_TIN_DataAccessAsynchronousError) )
	{
		MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_MemoryProtectionException);
	}
	else
	if ( (d15Value == MK_TIN_CoprocessorTrapAsynchronousError) ||
		 (d15Value == MK_TIN_ProgramMemoryIntegrityError) ||
		 (d15Value == MK_TIN_DataMemoryIntegrityError) )
	{
		MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_ProcessorSpecificException);
	}
	else
	if ( d15Value == MK_TIN_TemporalAsynchronousError )
	{
		/* Nothing to do - expiration of runtime is detected in MK_Dispatch.
		*/
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
