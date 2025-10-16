/* kern-startupcheckstask.c
 *
 * This file contains the OS_StartupChecksTask function.
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
 *   Condition is always false.
 *
 * Reason: If timing protection is switched off,
 *  OS_GET_TP, OS_GET_ILOCK, OS_GET_RLOCK and OS_GET_ACCT always evaluate to zero or NULL.
 *
 * TOOLDIAG-2) Possible diagnostic: PointlessComparison
 *   Condition is always true.
 *
 * Reason: This warning depends on the number of configured cores.
 *   Only in case of a single core configuration, this comparison can be evaluated at compile time.
 *
 * TOOLDIAG-3) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason: If timing protection is switched off,
 *  OS_GET_TP, OS_GET_ILOCK, OS_GET_RLOCK and OS_GET_ACCT always evaluate to zero or NULL.
 *
 * TOOLDIAG-4) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_panic.h>

/* This macro is used for checking the assmbler offsets into the task structures.
 * MISRA note:
 * The 0 cast to a pointer isn't a OS_NULL dereference, since we only take the address and then cast it to
 * unsigned.
*/
#define OS_OFFSET(typ, f)		((os_unsigned_t)&((typ *)0)->f)

#include <memmap/Os_mm_code_begin.h>

/* MISRA-C checkers want prototypes for static helpers */
static os_result_t OS_CheckTaskAccountingConfig(const os_task_t *ts);

/* Checks the accounting / timing configuration
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static os_result_t OS_CheckTaskAccountingConfig(const os_task_t *ts)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t result = OS_E_OK;

	/* !LINKSTO Kernel.Feature.StartupChecks.Task.MeasureNoAcct, 1 */
	if ( ((ts->flags & OS_TF_MEASUREEXEC) != 0u) && (OS_GET_ACCT(ts->accounting) == OS_NULL) )
	{
		result = OS_PANIC(OS_PANIC_SCHK_TaskWithMeasureExecButNoAccountingStructure);
	}

	/* Possible diagnostic TOOLDIAG-1 <+4> */
	if ( (OS_GET_TP(ts->execBudget) != 0u) ||
		 (OS_GET_ILOCK(ts->osLockTime) != 0u) ||
		 (OS_GET_ILOCK(ts->allLockTime) != 0u) ||
		 (OS_GET_RLOCK(ts->resourceLockTime) != OS_NULL) )
	{
		/* !LINKSTO Kernel.Feature.StartupChecks.Task.ExecTimeNoAcct, 1 */
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		if ( OS_GET_ACCT(ts->accounting) == OS_NULL )
		{
			/* Possible diagnostic TOOLDIAG-3 <+1> */
			result = OS_PANIC(OS_PANIC_SCHK_TaskWithExecTimeLimitButNoAccountingStructure);
		}

		/* This check is here because there's an implicit assumption in SuspendOSInterrupts that
		 * if any kind of interrupts have been locked there's a time limit already running that is less
		 * than or equal to the OS lock limit, so no new timing is started.
		 *
		 * The check won't fail if both are zero - that's OK.
		 * It *will* fail if osLockTime != 0 and allLockTime == 0 - that's OK.
		 *
		 * !LINKSTO Kernel.Feature.StartupChecks.Task.IntLockBudgetsInvalid, 1
		*/
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		if ( OS_GET_ILOCK(ts->osLockTime) < OS_GET_ILOCK(ts->allLockTime) )
		{
			result = OS_PANIC(OS_PANIC_SCHK_TaskWithOsIntLockTimeLessThanAllIntLockTime);
		}
	}

	return result;
}

/* OS_StartupChecksTask
 *
 * This function performs a variety of consistency and sanity checks on the task configuration
 * data and other tables to try to ensure that the generator is behaving itself as far as we can
 * tell.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_StartupChecksTask(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-4 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();
	os_result_t result = OS_E_OK;
	os_unsigned_t n;
	os_result_t tempres;

	for ( n = 0; n < OS_nTasks; n++ )
	{
		os_task_t const* const ts = &OS_taskTableBase[n];
		os_appcontext_t const* const app = OS_GET_APP(ts->app);

		/* !LINKSTO Kernel.Feature.StartupChecks.Task.NoOwningApplication, 1 */
		if ( OS_AppIsNull(app) )
		{
			result = OS_PANIC(OS_PANIC_SCHK_NoOwningApplication);
		}

		/* COVPT-1 +3 */
		/* Deviation MISRAC2012-1 <+2> */
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		if (OS_GetTaskCoreId(ts) == myCoreId)
		{
			os_permission_t const perms = OS_GET_APP(ts->permissions);

			/* !LINKSTO Kernel.Feature.StartupChecks.Task.WrongId, 1 */
			if ( ts->taskId != n )
			{
				result = OS_PANIC(OS_PANIC_SCHK_TaskIdIsNotIndexInTaskTable);
			}

			/* !LINKSTO Kernel.Feature.StartupChecks.Task.NoApplicationPermission, 1 */
			if ( !OS_HasPermission(app, perms) )
			{
				result = OS_PANIC(OS_PANIC_SCHK_OwningApplicationHasNoPermission);
			}

			/* !LINKSTO Kernel.Feature.StartupChecks.Task.RunLowerQueuePrio, 1 */
			if ( ts->queuePrio > ts->runPrio )
			{
				result = OS_PANIC(OS_PANIC_SCHK_TaskWithRunPrioLowerThanQueuePrio);
			}

			if ( (ts->flags & OS_TF_EXTENDED) != 0u )
			{
				/* !LINKSTO Kernel.Feature.StartupChecks.Task.WrongBCC, 1 */
				if ( (OS_configMode & OS_ECC) == 0u )
				{
					result = OS_PANIC(OS_PANIC_SCHK_ExtendedTaskInBasicConformanceClass);
				}

				/* !LINKSTO Kernel.Feature.StartupChecks.Task.ExtendedWithMultActivations, 1 */
				if ( ts->maxAct != 0u )
				{
					result = OS_PANIC(OS_PANIC_SCHK_ExtendedTaskWithMultipleActivations);
				}
			}

			/* !LINKSTO Kernel.Feature.StartupChecks.Task.WrongCC1, 1 */
			if ( ((OS_configMode & OS_CC2) == 0u) && (ts->maxAct != 0u) )
			{
				result = OS_PANIC(OS_PANIC_SCHK_MultipleActivationsInConformanceClass1);
			}

			tempres = OS_CheckTaskAccountingConfig(ts);
			/* COVPT-2 */
			if (tempres != OS_E_OK)
			{
				result = tempres;
			}
		}
	}

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_startupcheckstask_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
