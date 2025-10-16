/* Mk_k_startthreadforisr.c
 *
 * This file contains the MK_StartThreadForIsr() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_isr.h>
#include <private/Mk_interrupt.h>

/* MK_StartThreadForIsr() starts a thread to run the given isr
 *
 * Precondition:
 *	the thread is idle
 *
 * !LINKSTO Microkernel.Function.MK_StartThreadForIsr, 2
 * !doctype src
*/
void MK_StartThreadForIsr
(	mk_kernelcontrol_t *coreVars,
	mk_objectid_t isrIndex,
	mk_hwvectorcode_t vectorCode
)
{
	const mk_isrcfg_t *isr;
	mk_thread_t *thread;

	if ( (isrIndex >= 0) && (isrIndex < MK_nIsrs) )
	{
		/* If MK_isrCfg is null, MK_nIsrs is 0, so this branch does not get executed
		 * because no integer can be >= 0 and < 0.
		 * This means that no test for null is necessary.
		*/
		isr = &MK_isrCfg[isrIndex];
		thread = isr->thread;

		if ( isr->threadCfg.coreIndex == coreVars->coreIndex )
		{
			if ( (isr->dynamic == MK_NULL) || isr->dynamic->enabled )
			{
				if ( thread->state == MK_THS_IDLE )
				{
					MK_StartThread(&coreVars->threadQueueHead, thread, &isr->threadCfg);
				}
				else
				{
					/* Checking for a job queue and enough room in it goes here when needed.
					 * If there's a job queue with space we enqueue the job. But this will
					 * probably need code to disable the IRQ (and to re-enable when the ISR terminates).
					 * If there's no job queue, or the job queue is full, panic!
					*/
					MK_Panic(MK_panic_UnexpectedInterrupt);
				}
			}
			else
			{
				/* Interrupted, but the ISR is disabled. There may be hardware race conditions
				 * that cause this, so no panic.
				 * But to be on the safe side we disable the IRQ. That should stop crashes
				 * causes by software that circumvents the OS too.  :-)
				*/
				MK_HwDisableIrq(isr->irq);
			}
		}
		else
		{
			/* The interrupt isn't known on this core.
			*/
			MK_UnknownInterrupt(coreVars, isrIndex, vectorCode);
		}
	}
	else
	{
		/* The interrupt isn't known at all.
		*/
		MK_UnknownInterrupt(coreVars, isrIndex, vectorCode);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
