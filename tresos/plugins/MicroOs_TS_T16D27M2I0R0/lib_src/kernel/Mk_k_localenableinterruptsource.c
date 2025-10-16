/* Mk_k_localenableinterruptsource.c
 *
 * This file contains the function MK_LocalEnableInterruptSource().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_isr.h>
#include <private/Mk_errorhandling.h>

/* MK_LocalEnableInterruptSource() enables an interrupt source belonging to an ISR.
 * This function assumes that isrCfg is valid and the ISR belongs to the current core.
 * It is checked that the OS-Application to which this ISR belongs is not quarantined and the
 * interrupt is enabled.
 *
 * !LINKSTO Microkernel.Function.MK_LocalEnableInterruptSource, 1
 * !doctype src
*/
mk_errorid_t MK_LocalEnableInterruptSource(const mk_isrcfg_t *isrCfg, mk_objectid_t callerApp)
{
	mk_errorid_t errorCode = MK_eid_Unknown;
	mk_objectid_t const aId = isrCfg->threadCfg.applicationId;

	if ( MK_AppStateOk(aId, callerApp) )
	{
		if ( isrCfg->dynamic != MK_NULL )
		{
			isrCfg->dynamic->enabled = MK_TRUE;
		}
		MK_HwEnableIrq(isrCfg->irq);
		errorCode = MK_eid_NoError;
	}
	else
	{
		errorCode = MK_eid_Quarantined;
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
