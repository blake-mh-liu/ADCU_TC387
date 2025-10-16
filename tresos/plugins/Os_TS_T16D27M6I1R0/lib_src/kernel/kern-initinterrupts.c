/* kern-initinterrupts.c
 *
 * This file contains the implementation of the function to initialize ISRs.
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * For single-core configurations, the expression is always true.
 * 
 * MISRAC2012-2) Deviated Rule: 12.4 (advisory)
 * Evaluation of constant expressions should not lead to unsigned integer wrap-around.
 * 
 * Reason:
 * Bitwise invert operator is used to clear specific bits.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *   Condition is always true.
 *
 * Reason: This warning depends on the number of configured cores.
 *   Only in case of a single core configuration, this comparison can be evaluated at compile time.
 *
 * TOOLDIAG-2) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_InitInterrupts()
 *
 * This function initializes all the interrupt sources configured by the
 * OS generator.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitInterrupts(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_isrid_t i;
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();

	for (i = 0; i < OS_nInterrupts; i++)
	{
		os_isr_t const * const isr = &OS_isrTableBase[i];
		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		if (OS_GetIsrCoreId(isr) == myCoreId)
		{
			os_isrdynamic_t * const isrd = isr->dynamic;

			OS_SetupIsr(isr);

			if ( (isr->flags & OS_ISRF_ENABLE) != 0u )
			{
				/* Deviation MISRAC2012-2 <+1> */
				OS_EnableIsr(isr);
			}
			else
			{
				isrd->statusflags = OS_ISRF_BLOCKED;
			}
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_initinterrupts_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
