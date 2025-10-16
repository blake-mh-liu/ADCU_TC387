/* Mk_TRICORE_dosetdpr.s
 *
 * This file contains the function MK_DoSetDpr for TC1.6E/P and TC1.6.2 MPUs.
 * See gen_Mk_TRICORE_dosetxpr for further information.
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

#define MK_SET_DPR_SUBROUTINE_SIZE      32  /* Size of a subroutine which handles one DPR pair. */
#define MK_SET_DPR_SUBROUTINE_LDSIZE    5   /* Binary logarithm of the subroutine size. */
#if ((1 << MK_SET_DPR_SUBROUTINE_LDSIZE) != MK_SET_DPR_SUBROUTINE_SIZE)
#error "Mismatch between MK_SET_DPR_SUBROUTINE_LDSIZE and MK_SET_DPR_SUBROUTINE_SIZE."
#endif


	MK_file(Mk_TRICORE_dosetdpr.s)

	MK_global	MK_DoSetDpr

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* mk_uint32_t:d2 MK_DoSetDpr(mk_uint32_t dprIndex:d4, mk_address_t lowerAddress:d5, mk_address_t upperAddress:d6)
 *
 * This routine sets the lower and upper boundary of the DPR specified by dprIndex to lowerAddress and upperAddress.
 * A synchronization primitive is executed to ensure that the register
 * bank has been completely programmed before returning.
 * A readback is performed. A non-zero value is returned if the readback failed. Otherwise zero is returned.
 *
 * Parameters:
 *  - D4: dprIndex    : The index of the DPR which shall be set. This argument must be below
 *                      MK_TRICORE_NDPR.
 *  - D5: lowerAddress: The value which shall be written to and DPR[dprIndex]_L
 *  - D6: upperAddress: The value which shall be written to and DPR[dprIndex]_U
 *
 * Return value:
 *  - D2: Zero, if all registers were written successfully, otherwise an arbitrary non-zero value.
 *        If dprIndex is invalid, this routine returns an undefined value.
 *
 * Variables:
 *  - D4: Argument is modified to calculate the jump-table offset.
 *  - A4: Used to calculate the address in the jump table.
 *  - D2: Used to -- check the index argument (this way the result is non-zero if the check fails),
 *                -- read back the respective DPRi_L register,
 *                -- return the result value of this routine.
 *  - D3: Used to read back the respective DPRi_U register.
 *
 * This routine is implemented using a jump table, which jumps to a "subroutine",
 * which handles the respective registers.
 * If the subroutines are changed, the SUBROUTINE_SIZE macros need to be checked.
*/
MK_DoSetDpr:
	/* Check index argument to prevent loss of control flow integrity. */
	mov     d2, MK_imm(#, MK_TRICORE_NDPR)
	jge.u   d4, d2, MK_DoSetDprEpilogue
	/* Branch to respective jump-table offset. */
	movh.a  a4, MK_imm(#, MK_hi(MK_DoSetDpr0))          /* a4 = &MK_DoSetDpr0; */
	lea     a4, [a4] MK_lo(MK_DoSetDpr0)
	sh      d4, MK_imm(#, MK_SET_DPR_SUBROUTINE_LDSIZE) /* a4 = a4 + (dprIndex * SUBROUTINE_SIZE); */
	addsc.a a4, a4, d4, MK_imm(#, 0)
	ji      a4

	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
MK_DoSetDpr0:
	/* Subroutine assembler code           Comment              Offset relative to begin of subroutine. */

#if (MK_TRICORE_NDPR > 0)
	mtcr    MK_imm(#, MK_DPR0_L), d5    /* DPR0_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR0_U), d6    /* DPR0_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR0_L)    /* d2 = DPR0_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR0_U)    /* d3 = DPR0_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 1)
	mtcr    MK_imm(#, MK_DPR1_L), d5    /* DPR1_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR1_U), d6    /* DPR1_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR1_L)    /* d2 = DPR1_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR1_U)    /* d3 = DPR1_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 2)
	mtcr    MK_imm(#, MK_DPR2_L), d5    /* DPR2_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR2_U), d6    /* DPR2_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR2_L)    /* d2 = DPR2_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR2_U)    /* d3 = DPR2_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 3)
	mtcr    MK_imm(#, MK_DPR3_L), d5    /* DPR3_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR3_U), d6    /* DPR3_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR3_L)    /* d2 = DPR3_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR3_U)    /* d3 = DPR3_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 4)
	mtcr    MK_imm(#, MK_DPR4_L), d5    /* DPR4_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR4_U), d6    /* DPR4_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR4_L)    /* d2 = DPR4_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR4_U)    /* d3 = DPR4_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 5)
	mtcr    MK_imm(#, MK_DPR5_L), d5    /* DPR5_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR5_U), d6    /* DPR5_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR5_L)    /* d2 = DPR5_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR5_U)    /* d3 = DPR5_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 6)
	mtcr    MK_imm(#, MK_DPR6_L), d5    /* DPR6_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR6_U), d6    /* DPR6_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR6_L)    /* d2 = DPR6_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR6_U)    /* d3 = DPR6_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 7)
	mtcr    MK_imm(#, MK_DPR7_L), d5    /* DPR7_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR7_U), d6    /* DPR7_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR7_L)    /* d2 = DPR7_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR7_U)    /* d3 = DPR7_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 8)
	mtcr    MK_imm(#, MK_DPR8_L), d5    /* DPR8_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR8_U), d6    /* DPR8_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR8_L)    /* d2 = DPR8_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR8_U)    /* d3 = DPR8_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 9)
	mtcr    MK_imm(#, MK_DPR9_L), d5    /* DPR9_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR9_U), d6    /* DPR9_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR9_L)    /* d2 = DPR9_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR9_U)    /* d3 = DPR9_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 10)
	mtcr    MK_imm(#, MK_DPR10_L), d5   /* DPR10_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR10_U), d6   /* DPR10_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR10_L)   /* d2 = DPR10_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR10_U)   /* d3 = DPR10_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 11)
	mtcr    MK_imm(#, MK_DPR11_L), d5   /* DPR11_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR11_U), d6   /* DPR11_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR11_L)   /* d2 = DPR11_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR11_U)   /* d3 = DPR11_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 12)
	mtcr    MK_imm(#, MK_DPR12_L), d5   /* DPR12_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR12_U), d6   /* DPR12_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR12_L)   /* d2 = DPR12_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR12_U)   /* d3 = DPR12_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 13)
	mtcr    MK_imm(#, MK_DPR13_L), d5   /* DPR13_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR13_U), d6   /* DPR13_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR13_L)   /* d2 = DPR13_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR13_U)   /* d3 = DPR13_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 14)
	mtcr    MK_imm(#, MK_DPR14_L), d5   /* DPR14_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR14_U), d6   /* DPR14_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR14_L)   /* d2 = DPR14_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR14_U)   /* d3 = DPR14_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 15)
	mtcr    MK_imm(#, MK_DPR15_L), d5   /* DPR15_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR15_U), d6   /* DPR15_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR15_L)   /* d2 = DPR15_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR15_U)   /* d3 = DPR15_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 16)
	mtcr    MK_imm(#, MK_DPR16_L), d5   /* DPR16_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR16_U), d6   /* DPR16_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR16_L)   /* d2 = DPR16_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR16_U)   /* d3 = DPR16_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 17)
	mtcr    MK_imm(#, MK_DPR17_L), d5   /* DPR17_L = lowerAddress;           0x00..0x03 */
	mtcr    MK_imm(#, MK_DPR17_U), d6   /* DPR17_U = upperAddress;           0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPR17_L)   /* d2 = DPR17_L;                     0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPR17_U)   /* d3 = DPR17_U;                     0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPR_SUBROUTINE_SIZE, MK_SET_DPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NDPR > 18)
#error "Unsupported number of DPRs, this routine needs to be extended."
#endif

MK_DoSetDprEpilogue:
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

