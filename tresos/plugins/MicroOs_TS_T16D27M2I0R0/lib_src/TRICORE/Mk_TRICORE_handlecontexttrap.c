/* Mk_TRICORE_handlecontexttrap.c
 *
 * This file contains the function MK_HandleContextTrap()
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_CALLS]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *  In function MK_HandleContextTrap: Value 8.0 of metric "calls" is out of bounds (0..7)
 *
 * Reason:
 *  MK_HandleContextTrap doesn't contain more calls than necessary.
 *  The different kinds of exceptions have to be handled in an appropriate manner.
 *  Moreover, if we encounter this trap, we might only have a few CSAs left (MK_NCSAEXTRA)
 *  and calling static functions might increase the number of CSAs which are required to handle this trap.
*/
/* Deviation DCG-1 <*> */

#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_exceptionhandling.h>
#include <public/TRICORE/Mk_TRICORE_exceptioninfo.h>
#include <public/Mk_error.h>
#include <private/Mk_panic.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_exceptionhandling.h>
#include <private/Mk_thread.h>
#include <private/Mk_syscall.h>

#include <private/TRICORE/Mk_TRICORE_exceptionfunctions.h>

/* MK_HandleContextTrap()
 *
 * This function is entered via a jump instruction from the Context Management exception vector.
 * The vector provides the thread's PCXI value and the TIN as parameters.
 *
 * The Context List Underflow (PCX==0) exception is used by the microkernel to detect when a thread
 * returns from its top-level function. The remaining traps are reported. The two traps that report
 * a shortage of free CSAs must be treated as fatal.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HandleContextTrap, 2,
 * !        Microkernel.TRICORE.Exception.ReportProtectionFault, 1
 * !doctype src
*/
void MK_HandleContextTrap(mk_uint32_t pcxiValue, mk_uint32_t d15Value)
{
	mk_kernelcontrol_t *coreVars;

	if ( (d15Value == MK_TIN_CallStackUnderflowPcxEq0) )
	{
		mk_thread_t *threadCurrent;

		/* This exception is treated as TerminateSelf.
		*/
		/* Deviation MISRAC2012-1 <+1> */
		coreVars = MK_GetCoreVars();
		/* Doesn't return if exception is not "sane" */
		MK_ExceptionHandlerCommon(pcxiValue, d15Value, coreVars, MK_exc_ContextManagement, MK_FALSE);
		/* Terminate the calling thread.
		 * This is performed by calling MK_SysTerminateSelf(), which expects the return value to be
		 * placed in the first parameter register. Before making the call the return value is copied
		 * from D2 to D4. This supports a single 32-bit scalar return value.
		*/
		threadCurrent = coreVars->currentThread;
		threadCurrent->regs->lower->d4 = threadCurrent->regs->lower->d2;
		MK_SysTerminateSelf(coreVars);
	}
	else
	{
		/* All remaining exception types are considered as faults.
		*/
		coreVars = MK_TricoreGetCoreVarsException();
		/* Doesn't return if exception is not "sane" */
		MK_ExceptionHandlerCommon(pcxiValue, d15Value, coreVars, MK_exc_ContextManagement, MK_FALSE);
		MK_FillExceptionInfo(coreVars, MK_exc_ContextManagement, d15Value);

		/* Note: MK_TIN_FreeContextListUnderflowFcxEq0 can never reach this place, because it
		 *       triggers an endless loop in the assembler part of the exception handler
		*/
		if (d15Value == MK_TIN_FreeContextListDepletionFcxEqLcx)
		{
			/* Context list has reached low watermark.
			 * The only way to handle this is to shut down the system. Terminating
			 * all the running threads will free some CSAs to permit the shutdown to proceed.
			 * We prevent following spurious FCX==LCX traps by setting LCX to zero.
			 */
			MK_MTLCX(0);
			MK_Panic(MK_panic_ProcessorLimitExceeded);
		}
		else
		if ( (d15Value == MK_TIN_CallDepthOverflow) ||
			 (d15Value == MK_TIN_CallDepthUnderflow) ||
			 (d15Value == MK_TIN_ContextTypePcxiUlWrong) ||
			 (d15Value == MK_TIN_NestingErrorRfeNonZeroCallDepth) )
		{
			MK_ReportProtectionFault(coreVars, MK_sid_ExceptionHandling, MK_eid_CallNestingException);
		}
		else
		{
			/* Panic exception info is not written: already called MK_FillExceptionInfo; no in-kernel exception. */
			MK_Panic(MK_panic_UndocumentedException);
		}
	}

	MK_Dispatch(coreVars);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
