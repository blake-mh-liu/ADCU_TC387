/* Mk_k_sstinit.c
 *
 * This file contains the function MK_SstInit()
 *
 * (c) Elektrobit Automotive GmbH
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_NAMING_070]
 *  Unused parameters shall have their identifiers prefixed with unused_.
 *
 * Reason:
 *  The use of coreVars depends on the configuration. In multi-core configurations the variable is
 *  used while in single-core configurations the variable is not used. Therefore adding the unused_
 *  prefix does not make sense here.
 *  The macro MK_PARAM_UNUSED() is used in a corresponding preprocessor #if-#endif block. The CGC
 *  cannot identify this.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_sst.h>
#include <private/Mk_tool.h>

static void MK_SstCheckConfiguration(const mk_sstcountercfg_t *);
static void MK_SstInitializeCounter(const mk_sstcountercfg_t *);

static void MK_SstInitializeCounter(const mk_sstcountercfg_t *sstCfg)
{
	mk_sstcounter_t *sstCtr;

	sstCtr = sstCfg->counter;
	sstCtr->counterModulus = sstCfg->counterModulus;
	sstCtr->actionTable = sstCfg->actionTable;
	sstCtr->nActions = sstCfg->nActions;
	sstCtr->tickerId = sstCfg->tickerId;
	sstCtr->reloadInterval = sstCfg->reloadInterval;

	sstCtr->state = MK_SST_STOPPED;
	sstCtr->currentCount = 0u;
	sstCtr->nextAction = 0u;

	if ( sstCtr->tickerId >= 0 )
	{
		MK_HwInitTicker(sstCtr->tickerId);
	}
}

static void MK_SstCheckConfiguration(const mk_sstcountercfg_t *sstCfg)
{
	if ( (sstCfg->actionTable == MK_NULL) && (sstCfg->nActions > 0) )
	{
		MK_StartupPanic(MK_panic_InvalidSstConfiguration);
	}
	else if ( (sstCfg->counterModulus < 2u) ||
			  (sstCfg->counterModulus > 1073741824u) )
	{
		MK_StartupPanic(MK_panic_InvalidSstConfiguration);
	}
	else if ( sstCfg->tickerId >= 0 )
	{
		if ( !MK_HwCheckTickerId(sstCfg->tickerId) )
		{
			MK_StartupPanic(MK_panic_InvalidSstConfiguration);
		}
		if ( sstCfg->reloadInterval == 0u )
		{
			MK_StartupPanic(MK_panic_InvalidSstConfiguration);
		}
	}
	else
	{
		/* MISRA-C */
	}
}

/* MK_SstInit() - handle the SST initialization.
 *
 * !LINKSTO Microkernel.Function.MK_SstInit, 2
 * !doctype src
*/
void MK_SstInit(const mk_kernelcontrol_t *coreVars)
{
	mk_objquantity_t i;
	const mk_sstcountercfg_t *sstCfg;

#if (MK_MAXCORES == 1)
	/* Deviation DCG-1 <+1> */
	MK_PARAM_UNUSED(coreVars);
#endif

	for ( i = 0; i < MK_nSsts; i++ )
	{
		sstCfg = &MK_sstConfigsBase[i];
#if (MK_MAXCORES > 1)
		if ( sstCfg->coreIndex == coreVars->coreIndex )
#endif
		{
			MK_SstCheckConfiguration(sstCfg);
			MK_SstInitializeCounter(sstCfg);
		}
	}
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
