/* Mk_k_calculatectrsubcallermaxprio.c
 *
 * This file contains the MK_CalculateCtrSubCallerMaxPrio function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>


/* MK_CalculateCtrSubCallerMaxPrio - Helper function for MK_InitCoreVars and MK_ClearCoreVars.
 *
 * This function determines the maximum priority a thread may have to be allowed to call the counter subsystem.
 * If the counter subsystem inherits a priority which is equal or higher than the ProtectionHook priority,
 * exceptions caused by the counter subsystem can't be handled correctly.
 * Therefore this must not happen.
 *
 * Assumption:
 *  MK_IncreasePriority(head, target, minPrio, minLevel) doesn't set the target thread's priority to
 *  a higher priority than minPrio.
*/
mk_threadprio_t MK_CalculateCtrSubCallerMaxPrio(const mk_kernelcontrol_t *coreVars)
{
	mk_objectid_t coreId = coreVars->coreIndex;
	const mk_threadcfg_t *protHookCfg;
	mk_threadprio_t prio;

	/* Set 'prio' to the maximum priority which can be represented.
	*/
	prio = MK_THREADPRIO_MAX_VALUE;

	/* Determine the minimum priority of the respective hooks (currently it's only about the ProtectionHook).
	 * The counter subsystem priority must be lower than the priority of these hooks, so decrease it by 1.
	*/
	protHookCfg = MK_protectionHookThreadConfig[coreId];
	if (protHookCfg != MK_NULL)
	{
		prio = protHookCfg->queuePrio - 1;
	}

	return prio;
}
