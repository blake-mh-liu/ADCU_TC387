/* Mk_TRICORE_dogetdpr.s
 *
 * This file contains the function MK_DoGetDpr for TC1.6E/P and TC1.6.2 MPUs.
 * See gen_Mk_TRICORE_dogetxpr for further information.
 *
 * (c) Elektrobit Automotive GmbH
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_ASM_STYLE_025]
 *  An opening comment delimiter may only be preceded by a tab or newline character.
 *
 * Reason:
 *  These comments at the end of the line form a table. This table is formatted using spaces.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>		/* Must be first! */

#include <private/TRICORE/Mk_TRICORE_mpu.h>

#ifndef MK_TRICORE_NDPR
#error "MK_TRICORE_NDPR is undefined. Please check derivative header and makefiles."
#endif

#define MK_GET_DPR_SUBROUTINE_SIZE      16  /* Size of a subroutine which handles one DPR pair. */
#define MK_GET_DPR_SUBROUTINE_LDSIZE    4   /* Binary logarithm of the subroutine size. */
#if ((1 << MK_GET_DPR_SUBROUTINE_LDSIZE) != MK_GET_DPR_SUBROUTINE_SIZE)
#error "Mismatch between MK_GET_DPR_SUBROUTINE_LDSIZE and MK_GET_DPR_SUBROUTINE_SIZE."
#endif


	MK_file(Mk_TRICORE_dogetdpr.s)

	MK_global	MK_DoGetDpr

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* mk_mpurange_t:e2 MK_DoGetDpr(mk_uint32_t dprIndex:d4)
 *
 * This routine reads the lower and upper boundary of the DPR specified by dprIndex.
 *
 * Parameters:
 *  - D4: dprIndex: The index of the PRS whose read and write enable bit-sets shall be read. This argument
 *                  must be below MK_TRICORE_NDPR, otherwise the result value is undefined.
 *
 * Return value:
 *  - E2: A mk_mpurange_t instance containing DPR[dprIndex]_L and DPR[dprIndex]_U.
 *
 * Variables:
 *  - D4: Argument is modified to calculate the jump-table offset.
 *  - A4: Used to calculate the address in the jump table.
 *  - D2: Used to check the index argument (register also used for return value).
 *
 * This routine is implemented using a jump table, which jumps to a "subroutine",
 * which handles the respective registers.
 * If the subroutines are changed, the SUBROUTINE_SIZE macros need to be checked.
*/
MK_DoGetDpr:
	/* Check index argument to prevent loss of control flow integrity. */
	mov     d2, MK_imm(#, MK_TRICORE_NDPR)
	jge.u   d4, d2, MK_DoGetDprEpilogue
	/* Branch to respective jump-table offset. */
	movh.a  a4, MK_imm(#, MK_hi(MK_DoGetDpr0))          /* a4 = &MK_DoGetDpr0; */
	lea     a4, [a4] MK_lo(MK_DoGetDpr0)
	sh      d4, MK_imm(#, MK_GET_DPR_SUBROUTINE_LDSIZE) /* a4 = a4 + (dprIndex * SUBROUTINE_SIZE); */
	addsc.a a4, a4, d4, MK_imm(#, 0)
	ji      a4

	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
MK_DoGetDpr0:
	/* Subroutine assembler code           Comment              Offset relative to begin of subroutine. */

#if (MK_TRICORE_NDPR > 0)
	mfcr    d2, MK_imm(#, MK_DPR0_L)    /* d2 = DPR0_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR0_U)    /* d3 = DPR0_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 1)
	mfcr    d2, MK_imm(#, MK_DPR1_L)    /* d2 = DPR1_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR1_U)    /* d3 = DPR1_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 2)
	mfcr    d2, MK_imm(#, MK_DPR2_L)    /* d2 = DPR2_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR2_U)    /* d3 = DPR2_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 3)
	mfcr    d2, MK_imm(#, MK_DPR3_L)    /* d2 = DPR3_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR3_U)    /* d3 = DPR3_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 4)
	mfcr    d2, MK_imm(#, MK_DPR4_L)    /* d2 = DPR4_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR4_U)    /* d3 = DPR4_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 5)
	mfcr    d2, MK_imm(#, MK_DPR5_L)    /* d2 = DPR5_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR5_U)    /* d3 = DPR5_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 6)
	mfcr    d2, MK_imm(#, MK_DPR6_L)    /* d2 = DPR6_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR6_U)    /* d3 = DPR6_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 7)
	mfcr    d2, MK_imm(#, MK_DPR7_L)    /* d2 = DPR7_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR7_U)    /* d3 = DPR7_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 8)
	mfcr    d2, MK_imm(#, MK_DPR8_L)    /* d2 = DPR8_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR8_U)    /* d3 = DPR8_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 9)
	mfcr    d2, MK_imm(#, MK_DPR9_L)    /* d2 = DPR9_L;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR9_U)    /* d3 = DPR9_U;                      0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 10)
	mfcr    d2, MK_imm(#, MK_DPR10_L)   /* d2 = DPR10_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR10_U)   /* d3 = DPR10_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 11)
	mfcr    d2, MK_imm(#, MK_DPR11_L)   /* d2 = DPR11_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR11_U)   /* d3 = DPR11_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 12)
	mfcr    d2, MK_imm(#, MK_DPR12_L)   /* d2 = DPR12_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR12_U)   /* d3 = DPR12_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 13)
	mfcr    d2, MK_imm(#, MK_DPR13_L)   /* d2 = DPR13_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR13_U)   /* d3 = DPR13_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 14)
	mfcr    d2, MK_imm(#, MK_DPR14_L)   /* d2 = DPR14_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR14_U)   /* d3 = DPR14_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 15)
	mfcr    d2, MK_imm(#, MK_DPR15_L)   /* d2 = DPR15_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR15_U)   /* d3 = DPR15_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 16)
	mfcr    d2, MK_imm(#, MK_DPR16_L)   /* d2 = DPR16_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR16_U)   /* d3 = DPR16_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 17)
	mfcr    d2, MK_imm(#, MK_DPR17_L)   /* d2 = DPR17_L;                     0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPR17_U)   /* d3 = DPR17_U;                     0x04..0x07 */
	j       MK_DoGetDprEpilogue         /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPR_SUBROUTINE_SIZE, MK_GET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 18)
#error "Unsupported number of DPRs, this routine needs to be extended."
#endif

MK_DoGetDprEpilogue:
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

