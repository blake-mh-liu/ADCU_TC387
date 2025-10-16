/* Mk_k_isexecutionbudgetconfigured.c
 *
 * This file contains the MK_IsExecutionBudgetConfigured function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>
#include <private/Mk_accounting.h>
#include <private/Mk_task.h>
#include <private/Mk_isr.h>

/* MK_IsExecutionBudgetConfigured() returns TRUE if execution budget monitoring is needed.
 *
 * This function examines the thread configuration for every executable object in the system
 * (tasks and ISRs only because the OS, trusted function and hook threads are currently
 * fixed with no budget). If any one of them has an execution budget the function
 * returns TRUE. It only returns FALSE if no examined object has a configured budget.
 *
 * The global thread configurations MK_bootThreadConfig is explicitly *not* examined,
 * because MK_bootThreadConfig is a dummy that is not used for any real thread.
 *
 * Note: this means that if execution budget monitoring is not used for any task or ISR,
 * the self-test will fail.
 *
 * The thread configurations for hook functions, trusted functions, counter subsystem API etc. are
 * not considered because their budgets are fixed at INFINITE by Mk_configuration*.c
 *
 * !LINKSTO Microkernel.Function.MK_IsExecutionBudgetConfigured, 2
 * !doctype src
*/
mk_boolean_t MK_IsExecutionBudgetConfigured(mk_objectid_t coreIndex)
{
	mk_objectid_t i;
	mk_boolean_t foundExecBudget = MK_FALSE;

	for ( i = 0; (!foundExecBudget) && (i < MK_nTasks); i++ )
	{
		if ( MK_taskCfg[i].threadCfg.coreIndex == coreIndex )
		{
			if ( MK_taskCfg[i].threadCfg.acctCfg.execBudget != MK_EXECBUDGET_INFINITE )
			{
				foundExecBudget = MK_TRUE;
			}
		}
	}

	for ( i = 0; (!foundExecBudget) && (i < MK_nIsrs); i++ )
	{
		if ( MK_isrCfg[i].threadCfg.coreIndex == coreIndex )
		{
			if ( MK_isrCfg[i].threadCfg.acctCfg.execBudget != MK_EXECBUDGET_INFINITE )
			{
				foundExecBudget = MK_TRUE;
			}
		}
	}

	return foundExecBudget;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
