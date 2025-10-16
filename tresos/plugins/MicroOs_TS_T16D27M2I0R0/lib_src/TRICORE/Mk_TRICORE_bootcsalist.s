/* Mk_TRICORE_bootcsalist.s
 *
 * This code initializes the CSA list.
 * It doesn't require CSAs itself.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_ASM_STRUCT_020]
 *  Each assembly file shall contain exactly one return instruction, which is the last instruction.
 *
 * Reason:
 *  This function is used before the CSA list is set up, so it can't be entered using a call.
 *  It is entered using JL and therefore returns using JI A11.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>			/* Must be first */
#include <private/Mk_startup.h>
#include <public/TRICORE/Mk_TRICORE_characteristics.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_bootcsalist.s)

	MK_global	MK_BootCsaList
	MK_extern	MK_InitCsaList

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* void MK_BootCsaList(mk_uint32_t csaBegin @d4, mk_uint32_t csaEnd @d5)
 *
 * Parameters:
 *  - csaBegin in register d4: The start address of the CSA array.
 *  - csaEnd   in register d5: The first address beyond the CSA array.
 *
 * This function initializes the CSA list.
 *  - It adds the first CSA to the free list.
 *  - Then the C function MK_InitCsaList is called.
 *
 * This function isn't meant to be called by C code.
 * It is entered using JL and it returns using JI A11.
 * Register values of the upper context are preserved.
 * Register values of the lower context are not preserved by this function.
*/

MK_BootCsaList:
/* Register allocation:
 *
 * d4: Argument csaBegin. Don't touch, must be passed to MK_InitCsaList.
 * d5: Argument csaEnd.   Don't touch, must be passed to MK_InitCsaList.
 * d1: Segment-value used to calculate the FCX-value.
 * d2: FCX-value derived from csaBegin (temporarily contains the offset value).
 * d6: Temporary immediate value.
 * d7: Shall be set to 0.
 * d8 .. d15: Must not be used, because they are part of the upper context.
 *
 * a4: Holds the value of d4.
*/
/* Setup initial CSA
*/
	mov.a	a4, d4										/* set PCXI of this CSA to zero */
	mov		d7, MK_imm(#, 0)
	st.w	[a4]0, d7

	/* now calculate FCX-value from CSA address */
	sh		d1, d4, MK_imm(#, -12)						/* d1 = d4 >> 12 */
	extr.u	d2, d4, MK_imm(#, 6), MK_imm(#, 16)			/* d2 = (d4 & 0x3fffc0) >> 6 */
	movh	d6, MK_imm(#, 0xf)							/* d6 = 0x000f0000 */
	and		d1, d6										/* d1 &= d6 */
	or		d2, d1										/* d2 |= d1 */

	mtcr	MK_imm(#, MK_FCX), d2

	/* Set PCXI and LCX to 0 */
	mtcr	MK_imm(#, MK_PCXI), d7
	mtcr	MK_imm(#, MK_LCX), d7

	/* Wait for the changes to take place */
	isync

/* Initialize the rest of the global free CSA list.
*/
	/* Note:
	 *  csaBegin must still be stored in d4.
	 *  csaEnd must still be stored in d5.
	*/
	call	MK_InitCsaList

/* Return from MK_BootCsaList.
*/
	ji		a11


/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
