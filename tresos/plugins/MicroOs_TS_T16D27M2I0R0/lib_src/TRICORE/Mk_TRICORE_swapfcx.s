/* Mk_TRICORE_swapfcx.s
 *
 * This file contains the function MK_SwapFcx(). The function inserts a CSA list
 * into the free list.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_swapfcx.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_SwapFcx

/* void MK_SwapFcx(mk_uint32_t head, mk_uint32_t *tail)
 *
 * Parameters:
 *	head (d4) - head (pcxi link) of the list to be inserted.
 *	tail (a4) - pointer to the pcxi link of the last CSA in the list.
 *
 * This function inserts a CSA list into the processor's free list.
 * The current FCX value is read and placed in the tail pcxi link, then the head of the given
 * list is placed into FCX. At no time does the FCX register refer to an invalid list.
 *
 * Notes:
 * 1. Returning from this function frees the CSA that was used to call it, so the list that is freed
 *    is not at the head of the free list on return.
 * 2. The list to be freed does not get reversed by this process (as it does on allocation). As a result
 *    the CSA lists will become tangled over time. This is not a problem.
*/
MK_SwapFcx:

	dsync							/* Wait until the CALL operation completes */
	mfcr	d5, MK_imm(#, MK_FCX)	/* Get the current FCX value */
	isync							/* Wait until the operation completes */

	st.w	[a4], d5				/* Save the FCX value in the referenced link location. */

	mtcr	MK_imm(#, MK_FCX), d4	/* Put the head-of-list link into FCX */
	isync							/* Wait until the operation completes */

	ret								/* Back to caller */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
