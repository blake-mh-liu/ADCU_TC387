/* kern-inittaskstacks.c
 *
 * This file contains the OS_InitTaskStacks() function.
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

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_InitTaskStacks()
 *
 * Set all task stacks' content to OS_STACKFILL.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitTaskStacks(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-2 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();
	os_taskid_t tid;

	for (tid = 0; tid < OS_nTasks; tid++)
	{
		os_task_t const * const tp = &OS_taskTableBase[tid];
		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		if (OS_GetTaskCoreId(tp) == myCoreId)
		{
			/* Previously there was some code here that omitted to initialise stacks that were
			 * already initialised ( "if ( *p == OS_STACKFILL )" ), but that is not guaranteed
			 * to work, especially around a warm reboot.
			 * So we've removed the test, and now all stacks are initialised even if they've
			 * already been initialised. The disadvantage is a small increase in startup time.
			 * The old code also didn't take account of the fact that the shared stacks might
			 * be of different sizes.
			*/
			os_stackelement_t * p = tp->stackBase;
			os_size_t numElems = tp->stackLen / sizeof(os_stackelement_t);
			while ( numElems > 0u )
			{
				*p = OS_STACKFILL;
				p++;
				numElems--;
			}
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_inittaskstacks_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
