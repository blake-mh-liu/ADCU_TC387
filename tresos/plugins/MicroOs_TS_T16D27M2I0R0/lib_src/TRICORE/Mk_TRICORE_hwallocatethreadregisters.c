/* Mk_TRICORE_hwallocatethreadregisters.c
 *
 * This file contains the function MK_HwAllocateThreadRegisters() for Tricore.
 * The function allocates register space from the free CSA list so that a new thread
 * can be started.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  This function can call itself again indirectly via MK_Panic. This happens if an error is
 *  detected here and MK_Panic is called to shut down the system. In doing so new threads
 *  (the shutdown idle thread and optionally the shutdown hook thread) will be created for
 *  which this function will also be called. If the error persists, MK_Panic will be called
 *  again, but will detect this and as a consequence call MK_PanicStop to halt the system
 *  immediately. So there is a maximum nesting of two calls to this function possible.
 *
*/

#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_thread.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/Mk_panic.h>

/* MK_HwAllocateThreadRegisters() - allocates register space for a new thread
 *
 * Two CSAs are borrowed from the free list and allocated to the thread. When the thread
 * gets dispatched for the first time they will get returned to the free list.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwAllocateThreadRegisters, 2
 * !doctype src
*/
/* Deviation MISRAC2012-1 */
void MK_HwAllocateThreadRegisters(mk_hwthreadregisters_t *regs)
{
	/* A temporary variable is used to store the pcxi value because the macro MK_PcxToAddr()
	 * evaluates its parameter twice.
	*/
	register mk_uint32_t pcxiVal;

	if ( regs->pcxi != 0u )
	{
		/* The registers are not clean.
		*/
		/* Deviation MISRAC2012-1 <+1> */
		MK_Panic(MK_panic_RegisterStoreIsNotClean);
	}

	pcxiVal = MK_AllocateTwoCsas();
	regs->pcxi = pcxiVal;
	regs->lower = (mk_lowerctx_t *)MK_PcxToAddr(pcxiVal);
	pcxiVal = regs->lower->pcxi;
	regs->upper = (mk_upperctx_t *)MK_PcxToAddr(pcxiVal);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
