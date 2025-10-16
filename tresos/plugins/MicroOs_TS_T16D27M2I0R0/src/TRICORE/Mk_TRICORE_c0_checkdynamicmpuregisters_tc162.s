/* Mk_TRICORE_c0_checkdynamicmpuregisters_tc162.s
 *
 * This file contains the function MK_c0_CheckDynamicMpuRegisters for TC1.6E/P style MPUs
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */

#include <private/TRICORE/Mk_TRICORE_mpu.h>

#include <Mk_Cfg.h>

	MK_file(Mk_TRICORE_c0_checkdynamicmpuregisters_tc162.s)

	MK_global	MK_c0_CheckDynamicMpuRegisters

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT


/* MK_c0_CheckDynamicMpuRegisters(const mk_mpubounds_t *bounds, const mk_rwperm_t *permissions)
 *
 * This function reads the dynamic part of the userland MPU configuration from the MK_DPRx_L/U
 * registers. Since this function is executed whenever the memory partition is changed during
 * a thread dispatch, it is preprocessor-optimized to read exactly the number of registers
 * used in the biggest dynamic memory partition, as denoted by MK_CFG_C0_DYNREGIONS_MAX.
 * If no dynamic regions are used (MK_CFG_C0_DYNREGIONS_MAX == 0), it does nothing.
 *
 * The pointer parameter bounds in a4 needs to point to an array of boundary pairs and is mapped to
 * the available MPU registers in descending order, starting with the last one (DPR15).
 * The pointer parameter permissions in a5 needs to point to permission set.
 *
 * The function compares the bounds and permissions values from the provided data structures with the
 * the values contained in the respective MPU registers. It returns a 0 value in case all comparisons'
 * result is equality, otherwise a non-zero value.
 *
 * The code of this function contains no conditional branches.
*/

MK_c0_CheckDynamicMpuRegisters:
	mov		d2, MK_imm(#, 0)				/* initialize overall result */

/* First #if spans whole function */
#if MK_CFG_C0_DYNREGIONS_MAX > 0


#if MK_CFG_C0_DYNREGIONS_MAX > 0
	ld.w	d15, [a4]0						/* d15 = bounds[0].lower */
	mfcr	d14, MK_imm(#, MK_DPR17_L)		/* d14 = DPR17_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]4						/* d15 = bounds[0].upper */
	mfcr	d14, MK_imm(#, MK_DPR17_U)		/* d14 = DPR17_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 1
	ld.w	d15, [a4]8						/* d15 = bounds[1].lower */
	mfcr	d14, MK_imm(#, MK_DPR16_L)		/* d14 = DPR16_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]12						/* d15 = bounds[1].upper */
	mfcr	d14, MK_imm(#, MK_DPR16_U)		/* d14 = DPR16_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 2
	ld.w	d15, [a4]16						/* d15 = bounds[2].lower */
	mfcr	d14, MK_imm(#, MK_DPR15_L)		/* d14 = DPR15_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]20						/* d15 = bounds[2].upper */
	mfcr	d14, MK_imm(#, MK_DPR15_U)		/* d14 = DPR15_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 3
	ld.w	d15, [a4]24						/* d15 = bounds[3].lower */
	mfcr	d14, MK_imm(#, MK_DPR14_L)		/* d14 = DPR14_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]28						/* d15 = bounds[3].upper */
	mfcr	d14, MK_imm(#, MK_DPR14_U)		/* d14 = DPR14_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 4
	ld.w	d15, [a4]32						/* d15 = bounds[4].lower */
	mfcr	d14, MK_imm(#, MK_DPR13_L)		/* d14 = DPR13_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]36						/* d15 = bounds[4].upper */
	mfcr	d14, MK_imm(#, MK_DPR13_U)		/* d14 = DPR13_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 5
	ld.w	d15, [a4]40						/* d15 = bounds[5].lower */
	mfcr	d14, MK_imm(#, MK_DPR12_L)		/* d14 = DPR12_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]44						/* d15 = bounds[5].upper */
	mfcr	d14, MK_imm(#, MK_DPR12_U)		/* d14 = DPR12_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 6
	ld.w	d15, [a4]48						/* d15 = bounds[6].lower */
	mfcr	d14, MK_imm(#, MK_DPR11_L)		/* d14 = DPR11_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]52						/* d15 = bounds[6].upper */
	mfcr	d14, MK_imm(#, MK_DPR11_U)		/* d14 = DPR11_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 7
	ld.w	d15, [a4]56						/* d15 = bounds[7].lower */
	mfcr	d14, MK_imm(#, MK_DPR10_L)		/* d14 = DPR10_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]60						/* d15 = bounds[7].upper */
	mfcr	d14, MK_imm(#, MK_DPR10_U)		/* d14 = DPR10_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 8
	ld.w	d15, [a4]64						/* d15 = bounds[8].lower */
	mfcr	d14, MK_imm(#, MK_DPR9_L)		/* d14 = DPR9_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]68						/* d15 = bounds[8].upper */
	mfcr	d14, MK_imm(#, MK_DPR9_U)		/* d14 = DPR9_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 9
	ld.w	d15, [a4]72						/* d15 = bounds[9].lower */
	mfcr	d14, MK_imm(#, MK_DPR8_L)		/* d14 = DPR8_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]76						/* d15 = bounds[9].upper */
	mfcr	d14, MK_imm(#, MK_DPR8_U)		/* d14 = DPR8_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 10
	ld.w	d15, [a4]80						/* d15 = bounds[10].lower */
	mfcr	d14, MK_imm(#, MK_DPR7_L)		/* d14 = DPR7_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]84						/* d15 = bounds[10].upper */
	mfcr	d14, MK_imm(#, MK_DPR7_U)		/* d14 = DPR7_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 11
	ld.w	d15, [a4]88						/* d15 = bounds[11].lower */
	mfcr	d14, MK_imm(#, MK_DPR6_L)		/* d14 = DPR6_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]92						/* d15 = bounds[11].upper */
	mfcr	d14, MK_imm(#, MK_DPR6_U)		/* d14 = DPR6_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 12
	ld.w	d15, [a4]96						/* d15 = bounds[12].lower */
	mfcr	d14, MK_imm(#, MK_DPR5_L)		/* d14 = DPR5_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]100					/* d15 = bounds[12].upper */
	mfcr	d14, MK_imm(#, MK_DPR5_U)		/* d14 = DPR5_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 13
	ld.w	d15, [a4]104					/* d15 = bounds[13].lower */
	mfcr	d14, MK_imm(#, MK_DPR4_L)		/* d14 = DPR4_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]108					/* d15 = bounds[13].upper */
	mfcr	d14, MK_imm(#, MK_DPR4_U)		/* d14 = DPR4_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 14
	ld.w	d15, [a4]112					/* d15 = bounds[14].lower */
	mfcr	d14, MK_imm(#, MK_DPR3_L)		/* d14 = DPR3_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]116					/* d15 = bounds[14].upper */
	mfcr	d14, MK_imm(#, MK_DPR3_U)		/* d14 = DPR3_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 15
	ld.w	d15, [a4]120					/* d15 = bounds[15].lower */
	mfcr	d14, MK_imm(#, MK_DPR2_L)		/* d14 = DPR2_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]124					/* d15 = bounds[15].upper */
	mfcr	d14, MK_imm(#, MK_DPR2_U)		/* d14 = DPR2_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 16
	ld.w	d15, [a4]128					/* d15 = bounds[16].lower */
	mfcr	d14, MK_imm(#, MK_DPR1_L)		/* d14 = DPR1_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]132					/* d15 = bounds[16].upper */
	mfcr	d14, MK_imm(#, MK_DPR1_U)		/* d14 = DPR1_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

#if MK_CFG_C0_DYNREGIONS_MAX > 17
	ld.w	d15, [a4]136					/* d15 = bounds[17].lower */
	mfcr	d14, MK_imm(#, MK_DPR0_L)		/* d14 = DPR0_L */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a4]140					/* d15 = bounds[17].upper */
	mfcr	d14, MK_imm(#, MK_DPR0_U)		/* d14 = DPR0_U */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif

	ld.w	d15, [a5]0						/* d15 = permissions.dpre */
	mfcr	d14, MK_imm(#, MK_DPRE_1)		/* d14 = DPRE_1 */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */

	ld.w	d15, [a5]4						/* d15= permissions.dpwe */
	mfcr	d14, MK_imm(#, MK_DPWE_1)		/* d14 = DPWE_1 */
	xor		d14, d14, d15					/* if equal, the result is 0 */
	or		d2, d2, d14						/* OR this result to the overall result */
#endif	/* MK_CFG_C0_DYNREGIONS_MAX > 0 */

	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
