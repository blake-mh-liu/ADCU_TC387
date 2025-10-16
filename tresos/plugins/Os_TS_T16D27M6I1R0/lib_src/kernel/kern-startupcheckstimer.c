/* kern-startupcheckstimer.c
 *
 * This file contains the OS_StartupChecksTimer function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
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

#include <Os_panic.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_StartupChecksTimer
 *
 * This function performs a variety of checks of the hardware timer systems
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_StartupChecksTimer(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();
	os_result_t result = OS_E_OK;
	os_unsigned_t i;

	for ( i = 0; i < OS_nHwTimers; i++ )
	{
		os_hwt_t const* const hwt = &OS_hwTimerTableBase[i];
		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		if (OS_GetTimerCoreId(hwt) == myCoreId)
		{
#if OS_HWT_POWEROF2
			/* If the architecture only supports power-of-2 timer wrap values we must check that
			 * the wrap masks are correct.
			 *
			 * !LINKSTO Kernel.Feature.StartupChecks.Timer.NoPowerOfTwo, 1
			*/
			if ( !OS_IsPowerOf2(hwt->wrapMask+1u) )
			{
				result = OS_PANIC(OS_PANIC_SCHK_NonPowerOfTwoTimerWraparoundNotSupported);
			}
#endif
			/* !LINKSTO Kernel.Feature.StartupChecks.Timer.DeltasInconsistent, 1 */
			if ( (hwt->wrapMask <= hwt->maxDelta) || (hwt->maxDelta <= hwt->defDelta) )
			{
				result = OS_PANIC(OS_PANIC_SCHK_TimerMaxDeltaAndDefDeltaInconsistent);
			}
		}
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_startupcheckstimer_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
