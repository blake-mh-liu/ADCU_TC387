/***************************************************************************
 *
 * lockinghooks.c
 *
 * Sample for implementation of interupt locking hooks using suspend/resume
 * callouts.
 *
 * (c) Elektrobit Automotive GmbH
 *
 * Elektrobit Automotive GmbH
 * Phone: +49 (0)9131 7701 0
 * Am Wolfsmantel 46, 91058 Erlangen
 * GERMANY
 *
 *
 * This example illustrates how an interrupt locking hook can be implemented
 * which is called before/after unlocking/locking interrupts. It is achieved
 * by using the interrupt locking callouts. The preprocessor switch
 *
 *                    MK_USE_INT_LOCKING_CALLOUTS
 *
 * must be set to a non-zero value to enable the callouts.
 ****************************************************************************/

#include "lockinghooks.h"

#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <public/Mk_autosar.h>

void MK_SuspendCallout(mk_lockid_t resourceId)
{
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();

	/* suspend interrupts first */
	MK_SuspendInterrupts(resourceId);

	/* call hook afterwards */
	TMPL_InterruptLockingHook(
			coreVars->currentThread->objectType,
			coreVars->currentThread->currentObject,
			MK_sid_AcquireLock, resourceId);
}

void MK_ResumeCallout(mk_lockid_t resourceId)
{
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();

	/* call hook first */
	TMPL_InterruptLockingHook(
			coreVars->currentThread->objectType,
			coreVars->currentThread->currentObject,
			MK_sid_ReleaseLock, resourceId);

	/* now resume interrupts */
	MK_ResumeInterrupts(resourceId);
}
