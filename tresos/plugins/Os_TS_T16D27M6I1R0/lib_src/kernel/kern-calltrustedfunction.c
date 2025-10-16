/* kern-calltrustedfunction.c
 *
 * This file contains the OS_KernCallTrustedFunction function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if "calling context checks" are not excluded.
 *
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if "interrupt enable checks" are not excluded.
 *
 * TOOLDIAG-3) Possible diagnostic: UnusedVariable
 *   Variable is set but never used.
 *
 * Reason: Not an issue, variable is not required for windows. For rest of targets its being used.
 *
 * TOOLDIAG-4) Possible diagnostic: CastFromPtrToIntOfEqualSize
 *   Conversion from pointer to same-sized integral type
 *
 * Reason: The casted value is used for address calculations only and the code
 *   is well-aware of the type conversion in the implementation.
 *
 * TOOLDIAG-5) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and on arithmetic type.
 *
 * Reason:
 * This is done to capture the parameters passed to the function.
 * The conversion ensures, that no bits are lost.
 *
 *
 * MISRAC2012-2) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and on arithmetic type.
 *
 * Reason:
 * Some architectures have to prepare information to be processed by hardware,
 * or query its current status. In both cases type casts are necessary,
 * because hardware has no notion of C language types.
 *
 *
 * MISRAC2012-3) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to
 * object.
 *
 * Reason:
 * Some architectures have to prepare information to be processed by hardware,
 * or query its current status. In both cases type casts are necessary,
 * because hardware has no notion of C language types.
 *
 *
 * MISRAC2012-4) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and any
 * other type.
 *
 * Reason:
 * Some architectures have to prepare information to be processed by hardware,
 * or query its current status. In both cases type casts are necessary,
 * because hardware has no notion of C language types.
 * 
 * MISRAC2012-5) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and on arithmetic type.
 *
 * Reason:
 * The conversion of a pointer into a number is intentional, because this is
 * necessary to do arithmetic and because the caller is only interested in
 * its numerical value to do bounds checks.
*/

#define OS_SID	OS_SID_CallTrustedFunction
#define OS_SIF	OS_svc_CallTrustedFunction

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

#if OS_NEEDS_GetTFStackBounds_Fctcall
static void OS_GetTFStackBounds_Fctcall(os_address_t *, os_address_t *);

OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_GetTFStackBounds_Fctcall(os_address_t *lbp, os_address_t *ubp)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	if ( kernel_data->inFunction == OS_INTASK )
	{
		/* Possible diagnostic TOOLDIAG-4 */
		*lbp = OS_TASK_STACK_START;
		/* Possible diagnostic TOOLDIAG-4 */
		*ubp = OS_TASK_STACK_END;
	}
	else
	{
		os_isr_t const * const isr = &OS_isrTableBase[kernel_data->isrCurrent];
		void *isrStackLimit = OS_GetIsrStackLimit(isr->dynamic);

		/* COVPT-1 */
		if (isrStackLimit == OS_NULL)
		{
			/* Possible diagnostic TOOLDIAG-4 */
			*lbp = (os_address_t)kernel_data->iStackBase;
			*ubp = *lbp + kernel_data->iStackLen;
		}
		else
		{
#if (OS_STACKGROWS == OS_STACKGROWSDOWN)
			/* Deviation MISRAC2012-5 <+2> */
			/* Possible diagnostic TOOLDIAG-4 */
			*ubp = (os_address_t)isrStackLimit;
			*lbp = *ubp - isr->stackLen;
#else /* OS_STACKGROWSUP */
			/* Deviation MISRAC2012-5 <+2> */
			/* Possible diagnostic TOOLDIAG-4 */
			*lbp = (os_address_t)isrStackLimit;
			*ubp = *lbp + isr->stackLen;
#endif /* OS_STACKGROWS */
		}
	}
}
#endif /* OS_NEEDS_GetTFStackBounds_Fctcall */

/*!
 * OS_KernCallTrustedFunction implements the API CallTrustedFunction
 *
 * Trusted functions are executed with kernel privileges on the kernel
 * stack in a kernel environment. The latter means that system calls
 * behave slightly differently.
 *
 * Calls that would not normally return immediately to the caller in a task
 * environment, such as ChainTask, TerminateTask, WaitEvent, Schedule and
 * ActivateTask will immediately return to the caller. Any context switch
 * that results from a system call inside a trusted function will happen
 * when the trusted function returns to its caller.
 *
 * If the trusted function has been called from an ISR context, ActivateTask
 * would do this in any case and the others are not permitted, so the
 * trusted function has to be written to handle this possibility in any case.
 *
 * !LINKSTO Kernel.Autosar.TrustedFunctions, 2
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernCallTrustedFunction
(	os_functionid_t fid,
	void *parms
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t r = OS_E_OK;
	OS_PARAMETERACCESS_DECL
	/* Possible diagnostic TOOLDIAG-4 */
	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)fid);
	/* Deviation MISRAC2012-1 <+2> */
	/* Possible diagnostic TOOLDIAG-4 */
	OS_SAVE_PARAMETER_N(1,(os_paramtype_t)parms);

	OS_TRACE_CALLTRUSTEDFUNCTION_ENTRY(fid);

	/* !LINKSTO Kernel.Autosar.API.SystemServices.CallTrustedFunction.CalledByIsr, 1
	 * !LINKSTO Kernel.Autosar.API.SystemServices.CallTrustedFunction.CalledByTask, 1
	*/
	if ( !OS_CallingContextCheck() )
	{
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		r = OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_InterruptEnableCheck(OS_IEC_AUTOSAR) )
	{
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		r = OS_ERROR(OS_ERROR_InterruptDisabled, OS_GET_PARAMETER_VAR());
	}
	else
	if ( fid >= OS_nFunctions )
	{
		/* !LINKSTO Kernel.Autosar.API.SystemServices.CallTrustedFunction.UnknownFunction, 1
		 * !LINKSTO Kernel.Autosar.TrustedFunctions.NotConfigured, 1
		*/
		r = OS_ERROR(OS_ERROR_InvalidFunctionId, OS_GET_PARAMETER_VAR());
	}
	else
	{
		const os_function_t * const fs = &OS_functionTableBase[fid];

		if ( !OS_APPISACCESSIBLE(fs->app) )
		{
			r = OS_ERROR(OS_ERROR_ApplicationNotAccessible, OS_GET_PARAMETER_VAR());
		}
#if (OS_N_CORES != 1)
		/* COVPT-2 +2 */
		else
		/* Possible diagnostic TOOLDIAG-5 <+1> */
		if(OS_GetMyCoreId() != fs->app->core)
		{
			/*
			 * !LINKSTO Kernel.Autosar.API.SystemServices.CallTrustedFunction.NoCrossCore, 1
			*/
			r = OS_ERROR(OS_ERROR_CallTrustedFunctionCrosscore, OS_GET_PARAMETER_VAR());
		}
#endif
		else
		{
			os_address_t upperSp;
			/* Possible diagnostic TOOLDIAG-3 <+1> */
			os_address_t lowerSp;
			os_address_t lowerBound;
			os_address_t upperBound;

#if OS_STACKGROWS==OS_STACKGROWSDOWN
			/* Deviation MISRAC2012-2 <+2>, MISRAC2012-3 <+2> */
			/* Possible diagnostic TOOLDIAG-5 <+1> */
			OS_GetTrustedCallerSp(&upperSp);
			lowerSp = upperSp - fs->stackLen;
#else
			/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
			OS_GetTrustedCallerSp(&lowerSp);
			upperSp = lowerSp + fs->stackLen;
#endif
			/* Possible diagnostic TOOLDIAG-4 */
			OS_GetTrustedFunctionStackBounds(&lowerBound, &upperBound);

			/* COVPT-3 */ 
			if ( OS_IsTFuncStackSizeInsufficient(lowerSp, upperSp, lowerBound, upperBound) )
			{
				r = OS_ERROR(OS_ERROR_StackError, OS_GET_PARAMETER_VAR());
			}
			else
			{
				/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1>, MISRAC2012-4 <+1> */
				OS_PushTrustedFunction(fid, fs->function, parms);
			}
		}
		
	}

	OS_TRACE_CALLTRUSTEDFUNCTION_EXIT_P(r,fid);
	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_calltrustedfunction_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
