/* Mk_k_clearcorevars.c
 *
 * This file contains the MK_ClearCoreVars() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/Mk_startup.h>
#include <private/Mk_panic.h>
#include <private/Mk_accounting.h>
#include <private/Mk_message.h>

/* MK_ClearCoreVars() - clear the core variables.
 *
 * This is similar to MK_InitCoreVars(), except some state (e.g. the panicReason) is retained.
 *
 * !LINKSTO Microkernel.Function.MK_ClearCoreVars, 2
 * !doctype src
*/
void MK_ClearCoreVars(mk_kernelcontrol_t *coreVars)
{
	mk_objectid_t const coreIndex = MK_HwGetCoreIndex();

	coreVars->currentThread = MK_NULL;
	coreVars->kernelStackTop = MK_kernelStackTop[coreIndex];
	coreVars->threadQueueHead = MK_NULL;
	coreVars->coreIndex = coreIndex;
	coreVars->coreIndexLogical = MK_GetLogicalCoreId(coreIndex);

	/* coreState is retained, except if it is broken. */
	if (((mk_parametertype_t)coreVars->coreState) >= ((mk_parametertype_t)MK_coreState_Invalid))
	{
		coreVars->coreState = MK_coreState_OsRun;
	}

	coreVars->dispatchTime = 0;
	coreVars->currentMemoryPartition = -1;

	/* panicReason is retained.
	*/

	coreVars->ctrsubThreadConfig = MK_ctrsubThreadConfig[coreIndex];
	coreVars->ctrsubBasePrio = coreVars->ctrsubThreadConfig->queuePrio;
	coreVars->ctrsubCallerMaxPrio = MK_CalculateCtrSubCallerMaxPrio(coreVars);

	/* nDroppedMessages is retained, because it is just informational.
	 * nDroppedJobs is retained, because it is just informational.
	*/

	coreVars->execBudgetIsConfigured = MK_IsExecutionBudgetConfigured(coreIndex);

	coreVars->aux1Thread = MK_aux1Thread[coreIndex];
	coreVars->aux2Thread = MK_aux2Thread[coreIndex];

	coreVars->tfThreadConfig = MK_trustedFunctionThreadConfig[coreIndex];

	/* ctrsubAppMode is retained. It is only used by the counter subsystem and
	 * we can't determine whether its value is valid.
	*/

#if MK_MAXCORES > 1
	/* cookieGen is retained, except if it is out of range.
	*/
	if (coreVars->cookieGen > MK_MAXCOOKIE)
	{
		coreVars->cookieGen = MK_MINCOOKIE - 1u;
	}
#endif

	/* coreIndex must be valid. */
	MK_HwClearCoreVars(coreVars);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
