/* Mk_k_multidisableinterruptsource.c
 *
 * This file contains the MK_MultiDisableInterruptSource() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_isr.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_message.h>

#if MK_MAXCORES <= 1
#error "This file is not needed for single-core systems."
#endif

/*
 * MK_MultiDisableInterruptSource() disables an interrupt source belonging to an ISR.
 *
 * This function is called on multi-core systems to disable a source.
 * The ISR ID is assumed to have been previously validated.
 *
 * !LINKSTO Microkernel.Function.MK_MultiDisableInterruptSource, 2
 * !doctype src
*/
mk_errorid_t MK_MultiDisableInterruptSource
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t isrId,
	mk_objectid_t callerApp
)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	const mk_isrcfg_t *isrCfg = &MK_isrCfg[isrId];
	mk_objectid_t isrCore;

	isrCore = isrCfg->threadCfg.coreIndex;

	if ( isrCore == coreVars->coreIndex )
	{
		errorCode = MK_LocalDisableInterruptSource(isrCfg, callerApp);
	}
	else
	{
		errorCode = MK_eid_UnsupportedXCoreRequest;
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
