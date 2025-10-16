/* Mk_TRICORE_dosetcpr.s
 *
 * This file contains the function MK_DoSetCpr for TC1.6E/P and TC1.6.2 MPUs.
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

#ifndef MK_TRICORE_NCPR
#error "MK_TRICORE_NCPR is undefined. Please check derivative header and makefiles."
#endif

#define MK_SET_CPR_SUBROUTINE_SIZE      32  /* Size of a subroutine which handles one CPR pair. */
#define MK_SET_CPR_SUBROUTINE_LDSIZE    5   /* Binary logarithm of the subroutine size. */
#if ((1 << MK_SET_CPR_SUBROUTINE_LDSIZE) != MK_SET_CPR_SUBROUTINE_SIZE)
#error "Mismatch between MK_SET_CPR_SUBROUTINE_LDSIZE and MK_SET_CPR_SUBROUTINE_SIZE."
#endif


	MK_file(Mk_TRICORE_dosetcpr.s)

	MK_global	MK_DoSetCpr

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* mk_uint32_t:d2 MK_DoSetCpr(mk_uint32_t cprIndex:d4, mk_address_t lowerAddress:d5, mk_address_t upperAddress:d6)
 *
 * This routine sets the lower and upper boundary of the CPR specified by cprIndex to lowerAddress and upperAddress.
 * A synchronization primitive is executed to ensure that the register
 * bank has been completely programmed before returning.
 * A readback is performed. A non-zero value is returned if the readback failed. Otherwise zero is returned.
 *
 * Parameters:
 *  - D4: cprIndex    : The index of the CPR which shall be set. This argument must be below
 *                      MK_TRICORE_NCPR.
 *  - D5: lowerAddress: The value which shall be written to and CPR[cprIndex]_L
 *  - D6: upperAddress: The value which shall be written to and CPR[cprIndex]_U
 *
 * Return value:
 *  - D2: Zero, if all registers were written successfully, otherwise an arbitrary non-zero value.
 *        If cprIndex is invalid, this routine returns an undefined value.
 *
 * Variables:
 *  - D4: Argument is modified to calculate the jump-table offset.
 *  - A4: Used to calculate the address in the jump table.
 *  - D2: Used to -- check the index argument (this way the result is non-zero if the check fails),
 *                -- read back the respective CPRi_L register,
 *                -- return the result value of this routine.
 *  - D3: Used to read back the respective CPRi_U register.
 *
 * This routine is implemented using a jump table, which jumps to a "subroutine",
 * which handles the respective registers.
 * If the subroutines are changed, the SUBROUTINE_SIZE macros need to be checked.
*/
MK_DoSetCpr:
	/* Check index argument to prevent loss of control flow integrity. */
	mov     d2, MK_imm(#, MK_TRICORE_NCPR)
	jge.u   d4, d2, MK_DoSetCprEpilogue
	/* Branch to respective jump-table offset. */
	movh.a  a4, MK_imm(#, MK_hi(MK_DoSetCpr0))          /* a4 = &MK_DoSetCpr0; */
	lea     a4, [a4] MK_lo(MK_DoSetCpr0)
	sh      d4, MK_imm(#, MK_SET_CPR_SUBROUTINE_LDSIZE) /* a4 = a4 + (cprIndex * SUBROUTINE_SIZE); */
	addsc.a a4, a4, d4, MK_imm(#, 0)
	ji      a4

	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
MK_DoSetCpr0:
	/* Subroutine assembler code           Comment              Offset relative to begin of subroutine. */

#if (MK_TRICORE_NCPR > 0)
	mtcr    MK_imm(#, MK_CPR0_L), d5    /* CPR0_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR0_U), d6    /* CPR0_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR0_L)    /* d2 = CPR0_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR0_U)    /* d3 = CPR0_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 1)
	mtcr    MK_imm(#, MK_CPR1_L), d5    /* CPR1_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR1_U), d6    /* CPR1_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR1_L)    /* d2 = CPR1_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR1_U)    /* d3 = CPR1_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 2)
	mtcr    MK_imm(#, MK_CPR2_L), d5    /* CPR2_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR2_U), d6    /* CPR2_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR2_L)    /* d2 = CPR2_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR2_U)    /* d3 = CPR2_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 3)
	mtcr    MK_imm(#, MK_CPR3_L), d5    /* CPR3_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR3_U), d6    /* CPR3_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR3_L)    /* d2 = CPR3_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR3_U)    /* d3 = CPR3_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 4)
	mtcr    MK_imm(#, MK_CPR4_L), d5    /* CPR4_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR4_U), d6    /* CPR4_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR4_L)    /* d2 = CPR4_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR4_U)    /* d3 = CPR4_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 5)
	mtcr    MK_imm(#, MK_CPR5_L), d5    /* CPR5_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR5_U), d6    /* CPR5_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR5_L)    /* d2 = CPR5_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR5_U)    /* d3 = CPR5_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 6)
	mtcr    MK_imm(#, MK_CPR6_L), d5    /* CPR6_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR6_U), d6    /* CPR6_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR6_L)    /* d2 = CPR6_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR6_U)    /* d3 = CPR6_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 7)
	mtcr    MK_imm(#, MK_CPR7_L), d5    /* CPR7_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR7_U), d6    /* CPR7_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR7_L)    /* d2 = CPR7_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR7_U)    /* d3 = CPR7_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 8)
	mtcr    MK_imm(#, MK_CPR8_L), d5    /* CPR8_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR8_U), d6    /* CPR8_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR8_L)    /* d2 = CPR8_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR8_U)    /* d3 = CPR8_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 9)
	mtcr    MK_imm(#, MK_CPR9_L), d5    /* CPR9_L = lowerAddress;            0x00..0x03 */
	mtcr    MK_imm(#, MK_CPR9_U), d6    /* CPR9_U = upperAddress;            0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_CPR9_L)    /* d2 = CPR9_L;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_CPR9_U)    /* d3 = CPR9_U;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetCprEpilogue         /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_CPR_SUBROUTINE_SIZE, MK_SET_CPR_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NCPR > 10)
#error "Unsupported number of CPRs, this routine needs to be extended."
#endif

MK_DoSetCprEpilogue:
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

