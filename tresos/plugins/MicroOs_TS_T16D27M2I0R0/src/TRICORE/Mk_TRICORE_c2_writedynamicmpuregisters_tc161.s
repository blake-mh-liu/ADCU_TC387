/* Mk_TRICORE_c2_writedynamicmpuregisters_tc161.s
 *
 * This file contains the function MK_c2_WriteDynamicMpuRegisters for TC1.6E/P style MPUs
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */

#include <private/TRICORE/Mk_TRICORE_mpu.h>

#include <Mk_Cfg.h>

	MK_file(Mk_TRICORE_c2_writedynamicmpuregisters_tc161.s)

	MK_global	MK_c2_WriteDynamicMpuRegisters

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* MK_c2_WriteDynamicMpuRegisters(const mk_mpubounds_t *bounds, mk_rwperm_t *permissions)
 *
 * This function writes the dynamic part of the userland MPU configuration to the MK_DPRx_L/U
 * registers. Since this function is executed whenever the memory partition is changed during
 * a thread dispatch, it is preprocessor-optimized to write exactly the number of registers
 * used in the biggest dynamic memory partition, as denoted by MK_CFG_C2_DYNREGIONS_MAX.
 * If no dynamic regions are used (MK_CFG_C2_DYNREGIONS_MAX == 0), it does nothing.
 *
 * The pointer parameter "bounds" in a4 needs to point to an array of boundary pairs and is mapped to
 * the available MPU registers in descending order, starting with the last one (DPR15).
 *
 * The pointer parameter "permissions" (a5) points to the pre-calculated
 * permission set which is loaded into DPRE_1 and DPWE_1 respectively.
 *
 * Before returning, another synchronization primitive is executed to ensure
 * that the register bank has been completely programmed.
*/

MK_c2_WriteDynamicMpuRegisters:

/* First #if spans whole function */
#if MK_CFG_C2_DYNREGIONS_MAX > 0

	ld.w	d15, [a4]0						/* bounds[0].lower */
	ld.w	d14, [a4]4						/* bounds[0].upper */
#if MK_CFG_C2_DYNREGIONS_MAX > 1
	ld.w	d13, [a4]8						/* bounds[1].lower */
	ld.w	d12, [a4]12						/* bounds[1].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 2
	ld.w	d11, [a4]16						/* bounds[2].lower */
	ld.w	d10, [a4]20						/* bounds[2].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 3
	ld.w	d9,  [a4]24						/* bounds[3].lower */
	ld.w	d8,  [a4]28						/* bounds[3].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 4
	ld.w	d7,  [a4]32						/* bounds[4].lower */
	ld.w	d6,  [a4]36						/* bounds[4].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 5
	ld.w	d5,  [a4]40						/* bounds[5].lower */
	ld.w	d4,  [a4]44						/* bounds[5].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 6
	ld.w	d3,  [a4]48						/* bounds[6].lower */
	ld.w	d2,  [a4]52						/* bounds[6].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 7
	ld.w	d1,  [a4]56						/* bounds[7].lower */
	ld.w	d0,  [a4]60						/* bounds[7].upper */
#endif

	mtcr	MK_imm(#, MK_DPR15_L), d15		/* DPR15_L = bounds[0].lower */
	mtcr	MK_imm(#, MK_DPR15_U), d14		/* DPR15_U = bounds[0].upper */
#if MK_CFG_C2_DYNREGIONS_MAX > 1
	mtcr	MK_imm(#, MK_DPR14_L), d13		/* DPR14_L = bounds[1].lower */
	mtcr	MK_imm(#, MK_DPR14_U), d12		/* DPR14_U = bounds[1].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 2
	mtcr	MK_imm(#, MK_DPR13_L), d11		/* DPR13_L = bounds[2].lower */
	mtcr	MK_imm(#, MK_DPR13_U), d10		/* DPR13_U = bounds[2].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 3
	mtcr	MK_imm(#, MK_DPR12_L), d9		/* DPR12_L = bounds[3].lower */
	mtcr	MK_imm(#, MK_DPR12_U), d8		/* DPR12_U = bounds[3].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 4
	mtcr	MK_imm(#, MK_DPR11_L), d7		/* DPR11_L = bounds[4].lower */
	mtcr	MK_imm(#, MK_DPR11_U), d6		/* DPR11_U = bounds[4].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 5
	mtcr	MK_imm(#, MK_DPR10_L), d5		/* DPR10_L = bounds[5].lower */
	mtcr	MK_imm(#, MK_DPR10_U), d4		/* DPR10_U = bounds[5].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 6
	mtcr	MK_imm(#, MK_DPR9_L), d3		/* DPR9_L  = bounds[6].lower */
	mtcr	MK_imm(#, MK_DPR9_U), d2		/* DPR9_U  = bounds[6].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 7
	mtcr	MK_imm(#, MK_DPR8_L), d1		/* DPR8_L  = bounds[7].lower */
	mtcr	MK_imm(#, MK_DPR8_U), d0		/* DPR8_U  = bounds[7].upper */
#endif

#if MK_CFG_C2_DYNREGIONS_MAX > 8
	ld.w	d15, [a4]64						/* bounds[8].lower */
	ld.w	d14, [a4]68						/* bounds[8].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 9
	ld.w	d13, [a4]72						/* bounds[9].lower */
	ld.w	d12, [a4]76						/* bounds[9].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 10
	ld.w	d11, [a4]80						/* bounds[10].lower */
	ld.w	d10, [a4]84						/* bounds[10].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 11
	ld.w	d9,  [a4]88						/* bounds[11].lower */
	ld.w	d8,  [a4]92						/* bounds[11].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 12
	ld.w	d7,  [a4]96						/* bounds[12].lower */
	ld.w	d6,  [a4]100					/* bounds[12].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 13
	ld.w	d5,  [a4]104					/* bounds[13].lower */
	ld.w	d4,  [a4]108					/* bounds[13].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 14
	ld.w	d3,  [a4]112					/* bounds[14].lower */
	ld.w	d2,  [a4]116					/* bounds[14].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 15
	ld.w	d1,  [a4]120					/* bounds[15].lower */
	ld.w	d0,  [a4]124					/* bounds[15].upper */
#endif

#if MK_CFG_C2_DYNREGIONS_MAX > 8
	mtcr	MK_imm(#, MK_DPR7_L), d15		/* DPR7_L = bounds[8].lower */
	mtcr	MK_imm(#, MK_DPR7_U), d14		/* DPR7_U = bounds[8].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 9
	mtcr	MK_imm(#, MK_DPR6_L), d13		/* DPR6_L = bounds[9].lower */
	mtcr	MK_imm(#, MK_DPR6_U), d12		/* DPR6_U = bounds[9].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 10
	mtcr	MK_imm(#, MK_DPR5_L), d11		/* DPR5_L = bounds[10].lower */
	mtcr	MK_imm(#, MK_DPR5_U), d10		/* DPR5_U = bounds[10].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 11
	mtcr	MK_imm(#, MK_DPR4_L), d9		/* DPR4_L = bounds[11].lower */
	mtcr	MK_imm(#, MK_DPR4_U), d8		/* DPR4_U = bounds[11].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 12
	mtcr	MK_imm(#, MK_DPR3_L), d7		/* DPR3_L = bounds[12].lower */
	mtcr	MK_imm(#, MK_DPR3_U), d6		/* DPR3_U = bounds[12].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 13
	mtcr	MK_imm(#, MK_DPR2_L), d5		/* DPR2_L = bounds[13].lower */
	mtcr	MK_imm(#, MK_DPR2_U), d4		/* DPR2_U = bounds[13].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 14
	mtcr	MK_imm(#, MK_DPR1_L), d3		/* DPR1_L = bounds[14].lower */
	mtcr	MK_imm(#, MK_DPR1_U), d2		/* DPR1_U = bounds[14].upper */
#endif
#if MK_CFG_C2_DYNREGIONS_MAX > 15
	mtcr	MK_imm(#, MK_DPR0_L), d1		/* DPR0_L = bounds[15].lower */
	mtcr	MK_imm(#, MK_DPR0_U), d0		/* DPR0_U = bounds[15].upper */
#endif

	ld.w	d15, [a5]0						/* permissions.dpre */
	ld.w	d14, [a5]4						/* permissions.dpwe */

	mtcr	MK_imm(#, MK_DPRE_1), d15		/* DPRE_1 = permissions.dpre */
	mtcr	MK_imm(#, MK_DPWE_1), d14		/* DPWE_1 = permissions.dpwe */

	isync									/* Ensure all mtcr are effective */
#endif	/* MK_CFG_C2_DYNREGIONS_MAX > 0 */

	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
