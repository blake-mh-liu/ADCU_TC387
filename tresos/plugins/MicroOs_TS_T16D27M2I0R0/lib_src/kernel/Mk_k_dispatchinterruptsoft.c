/* Mk_k_dispatchinterruptsoft.c
 *
 * This file contains the MK_DispatchInterruptSoft function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_softvector.h>
#include <private/Mk_thread.h>
#include <private/Mk_panic.h>

/* MK_DispatchInterruptSoft()
 *
 * This function handles the interrupt entry for the interrupt controller in software mode.
 * It uses the interrupt vector number obtained from the interrupt controller to determine
 * which handler function to call, and the parameter for the handler function.
 * On return from the handler function the thread dispatcher MK_Dispatch() is called to
 * dispatch the most eligible thread.
 *
 * !LINKSTO Microkernel.Function.MK_DispatchInterruptSoft, 1
 * !doctype src
*/
void MK_DispatchInterruptSoft(mk_hwvectorcode_t vectorCode)
{
	const mk_softvector_t *vector;
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();

	if ( coreVars->threadQueueHead == MK_NULL )
	{
		/* Paranoia!
		 * If there's no thread in the queue the current thread is invalid.
		*/
		MK_Panic(MK_panic_CurrentThreadNotAtHeadOfQueue);
	}
	else
	if ( coreVars->currentThread == coreVars->threadQueueHead )
	{
		/* Get the address of the soft vector. Hopefully this will be optimized to avoid
		 * multiplication and division if the hardware supports the right vector spacing.
		*/
		vector = &MK_softwareVectorTable[MK_HwVectorCodeToInt(vectorCode)];

		/* Acknowledge the interrupt.
		 * This must done before the interrupt is handled.
		 * Otherwise, the interrupt may be requested again during handling, and clearing the request
		 * after the handler introduces a window, where a request might be lost.
		*/
		MK_HwSignalEndOfInterrupt(vectorCode);

		/* Call the service routine. This might result in a change to the highest-priority thread.
		*/
		(*vector->func)(coreVars, vector->param, vectorCode);

		/* Dispatch the highest-priority thread; the dispatcher never returns
		*/
		MK_Dispatch(coreVars);
	}
	else
	{
		/* Paranoia!
		 * If the current thread is not at the head of the queue something has been tinkering
		 * without dispatching.
		*/
		MK_Panic(MK_panic_InterruptNoThread);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
