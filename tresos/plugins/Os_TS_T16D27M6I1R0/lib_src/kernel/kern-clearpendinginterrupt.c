/* kern-clearpendinginterrupt.c
 *
 * This file contains the OS_KernClearPendingInterrupt() function.
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
 *   statement not reached.
 * 
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   The statements can be reached if context checks are enabled.
 *
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   The statements can be reached, if status is EXTENDED.
 *
 * TOOLDIAG-3) Possible diagnostic: UnusedVariable
 *   Variable is set but never used.
 *
 * Reason: Not an issue, variable will be used if at least one application exists.
*/

#define OS_SID	OS_SID_ClearPendingInterrupt
#define OS_SIF	OS_svc_ClearPendingInterrupt

/* Note: this comment is needed for asc_Os/tools/errdb-to-c.pl
 *
 * OS_ERRORCODE_CHECK(OS_ERROR_CoreIsDown)
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernDisableInterruptSource
 *
 * Implements the API ClearPendingInterrupt() and hence clears the category-2 pending 
 * interrupt for source of ISR 'i'.
 *
 * !LINKSTO Kernel.API.InterruptHandling.ClearPendingInterrupt.API, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernClearPendingInterrupt(os_isrid_t i)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t r = OS_E_OK;
	OS_PARAMETERACCESS_DECL

	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)i);

	OS_TRACE_CLEARPENDINGINTERRUPT_ENTRY(i);
	if ( !OS_CallingContextCheck() )
	{
		/* !LINKSTO Kernel.API.InterruptHandling.ClearPendingInterrupt.Task, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ClearPendingInterrupt.ISRC2, 1
		*/
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		r =  OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_IsValidIsrId(i) )
	{
		/* !LINKSTO Kernel.API.InterruptHandling.ClearPendingInterrupt.API.InvalidIsrId, 1
		*/
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		r = OS_ERROR(OS_ERROR_InvalidIsrId, OS_GET_PARAMETER_VAR());
	}
	else
	{
		const os_isr_t *isr = &OS_isrTableBase[i];
		/* Possible diagnostic TOOLDIAG-3 <+1> */
		const os_appcontext_t * const app = OS_CurrentApp();
		if ( !OS_HasPermission(app, isr->permissions) )
		{
			r = OS_ERROR(OS_ERROR_Permission, OS_GET_PARAMETER_VAR());
		}
		else
		{
			os_errorresult_t e = OS_DoClearPendingInterrupt(i, isr);
			if ( e != OS_ERRORCODE_NOCHECK(OS_ERROR_NoError) )
			{
				/* !LINKSTO Kernel.Autosar.Multicore.ClearPendingInterrupt.Errorhandling, 1
				*/
				r = OS_ERROR_NOCHECK(e, OS_GET_PARAMETER_VAR());
			}
		}
	}

	OS_TRACE_CLEARPENDINGINTERRUPT_EXIT_P(r,i);
	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_clearpendinginterrupt_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
