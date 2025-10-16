/* Mk_k_initexecutionbudgetmonitor.c
 *
 * This file contains the MK_InitExecutionBudgetMonitor function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_accounting.h>
#include <private/Mk_core.h>

/* MK_InitExecutionBudgetMonitor() initializes the execution budget monitoring subsystem.
 *
 * !LINKSTO Microkernel.Function.MK_InitExecutionBudgetMonitor, 1
 * !doctype src
*/
void MK_InitExecutionBudgetMonitor(mk_kernelcontrol_t *coreVars)
{
	coreVars->execBudgetIsConfigured = MK_IsExecutionBudgetConfigured(coreVars->coreIndex);

	/* On some CPU families, the time stamp timer is identical to the
	 * execution budget timer.
	 * FUTURE: Separate the two properly.
	 */
	MK_HwInitExecutionTimer();
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
