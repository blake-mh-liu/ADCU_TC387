/* Mk_k_initcorevars.c
 *
 * This file contains the MK_InitCoreVars() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/Mk_startup.h>
#include <private/Mk_panic.h>
#include <private/Mk_message.h>

/* MK_InitCoreVars() - initialize the core variables.
 *
 * !LINKSTO Microkernel.Function.MK_InitCoreVars, 1
 * !doctype src
*/
void MK_InitCoreVars(mk_kernelcontrol_t *coreVars)
{
	mk_objectid_t coreIndex;

	coreIndex = coreVars->coreIndex;
	coreVars->coreIndexLogical = MK_GetLogicalCoreId(coreIndex);

	coreVars->kernelStackTop = MK_kernelStackTop[coreIndex];
	coreVars->currentMemoryPartition = -1;
	coreVars->panicReason = MK_panic_None;

	coreVars->aux1Thread = MK_aux1Thread[coreIndex];
	coreVars->aux2Thread = MK_aux2Thread[coreIndex];

	coreVars->ctrsubThreadConfig = MK_ctrsubThreadConfig[coreIndex];
	coreVars->tfThreadConfig = MK_trustedFunctionThreadConfig[coreIndex];
	coreVars->ctrsubBasePrio = coreVars->ctrsubThreadConfig->queuePrio;
	coreVars->ctrsubCallerMaxPrio = MK_CalculateCtrSubCallerMaxPrio(coreVars);

	coreVars->ctrsubAppMode = MK_UNINITIALIZED_APPMODE;

#if MK_MAXCORES > 1
	coreVars->cookieGen = MK_MINCOOKIE - 1u;
#endif
#if MK_HASHEAP
	coreVars->heap = MK_coreHeaps[coreIndex];
#endif
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
