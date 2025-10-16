/* Mk_TRICORE_freethreadregisters.c
 *
 * This file contains the function MK_FreeThreadRegisters() for Tricore.
 * The function frees register space from the allocated CSA list of a terminating thread.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_thread.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

/* MK_HwFreeThreadRegisters() - frees the registers that a thread occupies
 *
 * This function is called whenever a thread properly terminates (i.e. NOT when it waits for an event)
 * It releases all the CSAs that the thread has allocated for itself.
 *
 * Note: it is assumed that the list can be a mixture of upper and lower contexts. In particular,
 * the first two contexts in the list *should* be lower and upper (in that order) if the Microkernel
 * is behaving itself.
 *
 * There are two possible approaches to freeing the list:
 *	1: load PCXI with the head of the list and execute RSLCX and/or RET until the end is reached.
 *	2: walk down the list in software until the last CSA is found. Set the pcxi link of the last CSA to
 *     the current value in the FCX register, then set the FCX register to the head of the list.
 *
 * The length of the list could be quite long if the thread got terminated while it was deeply nested,
 * and RSLCX and RET can be quite expensive, so option 2 has been chosen.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwFreeThreadRegisters, 2
 * !doctype src
*/
void MK_HwFreeThreadRegisters(mk_hwthreadregisters_t *regs)
{
	/* An upper context structure is used for the loop. Even though some CSAs might be lower contexts, the pcxi link
	 * is in the same place, so we don't care, and using this type avoids a questionable cast.
	*/
	mk_uint32_t linkedCsa = (regs->pcxi & MK_PCX_CSA_MASK);

	if ( linkedCsa == 0u )
	{
		/* Already at the end - nothing to free */
	}
	else
	{
		mk_upperctx_t *cx;
		mk_upperctx_t *prev = MK_NULL;
		/* The lower context is always the head of the list. The upper context is always the next in the list.
		 * So this loop starts from the upper context.
		 * The loop body is executed at least once, otherwise linkedCsa would be 0.
		 * Therefore prev is not expected to be NULL after this loop.
		*/
		for (cx = regs->upper; cx != MK_NULL; cx = (mk_upperctx_t *)MK_PcxToAddr(cx->pcxi))
		{
			prev = cx;
		}

		/* Now cx points to the last CSA in the thread's "occupied" list. The assembler function
		 * MK_SwapFcx() places the "current" value of the FCX register in the pcxi link of the
		 * last CSA (whose address is passed as a pointer) and the head of the thread's list into
		 * the FCX register.
		 * Note: calling the function moves a CSA from the free list to the used list, which
		 * then gets moved back on return. So the call actually inserts the thread's list
		 * into the free list.
		*/
		MK_SwapFcx(linkedCsa, &prev->pcxi);
	}

	/* Finally, mark the register store as "clean"
	*/
	regs->pcxi = 0;
	regs->lower = MK_NULL;
	regs->upper = MK_NULL;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
