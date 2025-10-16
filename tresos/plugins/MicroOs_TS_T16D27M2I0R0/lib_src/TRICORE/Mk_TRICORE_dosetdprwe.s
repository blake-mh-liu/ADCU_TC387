/* Mk_TRICORE_dosetdprwe.s
 *
 * This file contains the function MK_DoSetDprwe for TC1.6E/P and TC1.6.2 MPUs.
 * See gen_Mk_TRICORE_dosetdprwe for further information.
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

#ifndef MK_TRICORE_NPRS
#error "MK_TRICORE_NPRS is undefined. Please check derivative header and makefiles."
#endif

#define MK_SET_DPRWE_SUBROUTINE_SIZE      32  /* Size of a subroutine which handles one DPRE/DPRWE pair. */
#define MK_SET_DPRWE_SUBROUTINE_LDSIZE    5   /* Binary logarithm of the subroutine size. */
#if ((1 << MK_SET_DPRWE_SUBROUTINE_LDSIZE) != MK_SET_DPRWE_SUBROUTINE_SIZE)
#error "Mismatch between MK_SET_DPRWE_SUBROUTINE_LDSIZE and MK_SET_DPRWE_SUBROUTINE_SIZE."
#endif


	MK_file(Mk_TRICORE_dosetdprwe.s)

	MK_global	MK_DoSetDprwe

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* mk_uint32_t:d2 MK_DoSetDprwe(mk_uint32_t prsIndex:d4, mk_address_t re:d5, mk_address_t we:d6)
 *
 * This routine sets the read and write enable bit-sets of the PRS specified by prsIndex to re and we.
 * A synchronization primitive is executed to ensure that the register
 * bank has been completely programmed before returning.
 * A readback is performed. A non-zero value is returned if the readback failed. Otherwise zero is returned.
 *
 * Parameters:
 *  - D4: prsIndex: The index of the PRS whose read and write enable bit-sets shall be set. This argument
 *                  must be below MK_TRICORE_NPRS.
 *  - D5: re      : The read enable bits for DPRE_[prsIndex].
 *  - D6: we      : The write enable bits for DPWE_[prsIndex].
 *
 * Return value:
 *  - D2: Zero, if all registers were written successfully, otherwise an arbitrary non-zero value.
 *        If prsIndex is invalid, this routine returns an undefined value.
 *
 * Variables:
 *  - D4: Argument is modified to calculate the jump-table offset.
 *  - A4: Used to calculate the address in the jump table.
 *  - D2: Used to -- check the index argument (this way the result is non-zero if the check fails),
 *                -- read back the respective DPRE_i register,
 *                -- return the result value of this routine.
 *  - D3: Used to read back the respective DPWE_i register.
 *
 * This routine is implemented using a jump table, which jumps to a "subroutine",
 * which handles the respective registers.
 * If the subroutines are changed, the SUBROUTINE_SIZE macros need to be checked.
*/
MK_DoSetDprwe:
	/* Check index argument to prevent loss of control flow integrity. */
	mov     d2, MK_imm(#, MK_TRICORE_NPRS)
	jge.u   d4, d2, MK_DoSetDprweEpilogue
	/* Branch to respective jump-table offset. */
	movh.a  a4, MK_imm(#, MK_hi(MK_DoSetDprwe0))          /* a4 = &MK_DoSetDprwe0; */
	lea     a4, [a4] MK_lo(MK_DoSetDprwe0)
	sh      d4, MK_imm(#, MK_SET_DPRWE_SUBROUTINE_LDSIZE) /* a4 = a4 + (prsIndex * SUBROUTINE_SIZE); */
	addsc.a a4, a4, d4, MK_imm(#, 0)
	ji      a4

	MK_align(MK_SET_DPRWE_SUBROUTINE_SIZE, MK_SET_DPRWE_SUBROUTINE_LDSIZE)
MK_DoSetDprwe0:
	/* Subroutine assembler code           Comment              Offset relative to begin of subroutine. */

#if (MK_TRICORE_NPRS > 0)
	mtcr    MK_imm(#, MK_DPRE_0), d5    /* DPRE_0 = re;                      0x00..0x03 */
	mtcr    MK_imm(#, MK_DPWE_0), d6    /* DPWE_0 = we;                      0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPRE_0)    /* d2 = DPRE_0;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPWE_0)    /* d3 = DPWE_0;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprweEpilogue       /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPRWE_SUBROUTINE_SIZE, MK_SET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 1)
	mtcr    MK_imm(#, MK_DPRE_1), d5    /* DPRE_1 = re;                      0x00..0x03 */
	mtcr    MK_imm(#, MK_DPWE_1), d6    /* DPWE_1 = we;                      0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPRE_1)    /* d2 = DPRE_1;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPWE_1)    /* d3 = DPWE_1;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprweEpilogue       /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPRWE_SUBROUTINE_SIZE, MK_SET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 2)
	mtcr    MK_imm(#, MK_DPRE_2), d5    /* DPRE_2 = re;                      0x00..0x03 */
	mtcr    MK_imm(#, MK_DPWE_2), d6    /* DPWE_2 = we;                      0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPRE_2)    /* d2 = DPRE_2;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPWE_2)    /* d3 = DPWE_2;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprweEpilogue       /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPRWE_SUBROUTINE_SIZE, MK_SET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 3)
	mtcr    MK_imm(#, MK_DPRE_3), d5    /* DPRE_3 = re;                      0x00..0x03 */
	mtcr    MK_imm(#, MK_DPWE_3), d6    /* DPWE_3 = we;                      0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPRE_3)    /* d2 = DPRE_3;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPWE_3)    /* d3 = DPWE_3;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprweEpilogue       /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPRWE_SUBROUTINE_SIZE, MK_SET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 4)
	mtcr    MK_imm(#, MK_DPRE_4), d5    /* DPRE_4 = re;                      0x00..0x03 */
	mtcr    MK_imm(#, MK_DPWE_4), d6    /* DPWE_4 = we;                      0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPRE_4)    /* d2 = DPRE_4;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPWE_4)    /* d3 = DPWE_4;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprweEpilogue       /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPRWE_SUBROUTINE_SIZE, MK_SET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 5)
	mtcr    MK_imm(#, MK_DPRE_5), d5    /* DPRE_5 = re;                      0x00..0x03 */
	mtcr    MK_imm(#, MK_DPWE_5), d6    /* DPWE_5 = we;                      0x04..0x07 */
	isync                               /* Ensure all mtcr have taken place; 0x08..0x0b */
	mfcr    d2, MK_imm(#, MK_DPRE_5)    /* d2 = DPRE_5;                      0x0c..0x0f */
	mfcr    d3, MK_imm(#, MK_DPWE_5)    /* d3 = DPWE_5;                      0x10..0x13 */
	xor     d2, d5                      /* d2 ^= d5;                         0x14..0x15 */
	xor     d3, d6                      /* d3 ^= d6;                         0x16..0x17 */
	or      d2, d3                      /* d2 |= d3;                         0x18..0x19 */
	j       MK_DoSetDprweEpilogue       /* Perform epilogue                  0x1a..0x1b,0x1d */
	MK_align(MK_SET_DPRWE_SUBROUTINE_SIZE, MK_SET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 6)
#error "Unsupported number of PRSs, this routine needs to be extended."
#endif

MK_DoSetDprweEpilogue:
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

