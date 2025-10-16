/* Mk_TRICORE_exceptionhandlercommon.c
 *
 * This file contains the function MK_ExceptionHandlerCommon()
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
*/

#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_exceptionhandling.h>
#include <private/Mk_thread.h>
#include <private/TRICORE/Mk_TRICORE_thread.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>

/* MK_ExceptionHandlerCommon()
 *
 * This function is called at the beginning of each exception handler. Its job is to
 * store the PCXI and D15 values (head of used CSA list and TIN or system-call index, respectively)
 * into the thread's register store.
 *
 * Before doing so, it checks if the exception is "sane". If the exception occurred within the
 * Microkernel (detected by the IS flag in the saved PSW being 1) the register values are not stored
 * and MK_Panic() is called.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_ExceptionHandlerCommon, 6
 * !doctype src
*/
/* Deviation DCG-1 <+1> */
void MK_ExceptionHandlerCommon(
	mk_uint32_t pcxiValue,
	mk_uint32_t d15Value,
	mk_kernelcontrol_t *coreVars,
	mk_exceptionclass_t excClass,
	mk_boolean_t returnOnPreempt)
{
	mk_lowerctx_t *lowerCx;
	mk_upperctx_t *upperCx = MK_NULL;

	/* First things first: stop TPS-decrementer to reduce number of in-kernel exceptions
	*/
	MK_MTTPS_TIMER0(0);

	/* Then clear any exception that may have happened up to here
	*/
	MK_MTTPS_CON(0);

	/* We are about to access active CSAs, a DSYNC is required first to make sure the processor
	 * is done writing the CSAs to memory.
	 */
	MK_DSYNC();

	lowerCx = (mk_lowerctx_t *)MK_PcxToAddr(pcxiValue);

	if ( lowerCx == MK_NULL )
	{
		/* This should be unreachable.
		 * Panic exception info is not written, because this is not an in-kernel exception.
		*/
		MK_Panic(MK_panic_UnexpectedHardwareResponse);
	}
	else
	{
		upperCx = (mk_upperctx_t *)MK_PcxToAddr(lowerCx->pcxi);

		if ( upperCx == MK_NULL )
		{
			/* This should be unreachable.
			 * Panic exception info is not written, because this is not an in-kernel exception.
			*/
			MK_Panic(MK_panic_UnexpectedHardwareResponse);
		}
	}

	if ( ( upperCx->psw & MK_PSW_IS ) == 0u )
	{
		/* IS flag was zero ==> exception apparently occurred in a thread.
		*/
		mk_thread_t *threadCurrent = coreVars->currentThread;
		mk_thread_t *threadQueueHead = coreVars->threadQueueHead;

		/* We must not dereference an invalid pointer, because we might be stuck in an
		 * exception loop and eventually end up without free CSAs.
		 * Therefore, we check that
		 *   - the thread queue head is not null and
		 *   - the thread queue head is identical to the current thread.
		 * which makes detecting corrupted kernel variables very likely.
		*/
		if ( threadQueueHead == MK_NULL )
		{
			/* Panic exception info is not written, because this is not an in-kernel exception. */
			MK_Panic(MK_panic_ExceptionNoThread);
		}
		else
		if ( threadCurrent == threadQueueHead )
		{
			/* Everything seems to be OK. Continue processing normally.
			 * Save the register values (and the pseudo-register values).
			*/
			threadCurrent->regs->pcxi = pcxiValue;
			threadCurrent->regs->trapCode = d15Value;
			threadCurrent->regs->upper = upperCx;
			threadCurrent->regs->lower = lowerCx;
		}
		else
		{
			/* The current thread is not at the head of the queue, so something has been tinkering
			 * without dispatching, or maybe the exception occurred in the Microkernel.
			 * The exception probably did not happen in the MK, because PSW.IS is not set,
			 * so we don't overwrite panic exception info.
			*/
			MK_Panic(MK_panic_ExceptionCurrentThreadNotAtHeadOfQueue);
		}
	}
	else
	{
		/* IS flag was non-zero ==> exception occurred in the Microkernel.
		*/

		if (returnOnPreempt)
		{
			/* Return to the interrupted kernel context
			*/
			MK_TricoreResumeThread(pcxiValue);
		}
		else
		{
			/* Report an in-kernel exception.
			 *
			 * !LINKSTO Microkernel.Panic.MK_panic_ExceptionFromKernel, 1
			*/
			MK_FillPanicExceptionInfo(coreVars, excClass, d15Value, lowerCx, upperCx);
			MK_Panic(MK_panic_ExceptionFromKernel);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
