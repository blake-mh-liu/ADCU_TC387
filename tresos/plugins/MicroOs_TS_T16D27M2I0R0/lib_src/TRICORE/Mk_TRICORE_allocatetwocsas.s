/* Mk_TRICORE_allocatetwocsas.s
 *
 * This file contains the function MK_AllocateTwoCsas(). The function allocates two CSAs
 * from the free list and returns the PCXI-register value for the head of the two-CSA
 * list. The allocated list contains a lower and an upper context, so that RSLCX/RFE works,
 * assuming that the call depth counter gets fixed correctly.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_allocatetwocsas.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_AllocateTwoCsas

/* mk_uint32_t MK_AllocateTwoCsas(void) - allocate two CSAs from the free list.
 *
 * Return value: PCXI value - head of list of 2 CSAs, one lower, one upper.
*/
MK_AllocateTwoCsas:

	mov		d5, MK_imm(#, 0)		/* Preload 0 for later. */
	mov.aa	a4, a11					/* Save return address for later */

	dsync
	mfcr	d4, MK_imm(#, MK_PCXI)	/* Get the head of the "used" list. We need to restore it later. */
	mtcr	MK_imm(#, MK_PCXI), d5	/* Set PCXI to 0 to cut the allocated list from the main "used" list. */

	call	MK_Alloc1				/* Allocates an upper context. Never returns to here */

MK_Alloc1:
	svlcx							/* Allocates a lower context */

	mov.aa	a11, a4					/* Restore return address */

	dsync
	mfcr	d2, MK_imm(#, MK_PCXI)	/* Get PCXI value: head of allocated list --> return value */
	mtcr	MK_imm(#, MK_PCXI), d4	/* Restore head of original "used" list. */
	isync

	ret								/* Returns to the original caller because PCXI and RA have been restored. */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
