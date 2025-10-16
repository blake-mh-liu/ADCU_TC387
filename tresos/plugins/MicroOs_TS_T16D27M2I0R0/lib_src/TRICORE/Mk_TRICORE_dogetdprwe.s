/* Mk_TRICORE_dogetdprwe.s
 *
 * This file contains the function MK_DoGetDprwe for TC1.6E/P and TC1.6.2 MPUs.
 * See gen_Mk_TRICORE_dogetdprwe for further information.
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

#define MK_GET_DPRWE_SUBROUTINE_SIZE      16  /* Size of a subroutine which handles one DPRE/DPRWE pair. */
#define MK_GET_DPRWE_SUBROUTINE_LDSIZE    4   /* Binary logarithm of the subroutine size. */
#if ((1 << MK_GET_DPRWE_SUBROUTINE_LDSIZE) != MK_GET_DPRWE_SUBROUTINE_SIZE)
#error "Mismatch between MK_GET_DPRWE_SUBROUTINE_LDSIZE and MK_GET_DPRWE_SUBROUTINE_SIZE."
#endif


	MK_file(Mk_TRICORE_dogetdprwe.s)

	MK_global	MK_DoGetDprwe

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* mk_mpurwpermission_t:e2 MK_DoGetDprwe(mk_uint32_t prsIndex:d4)
 *
 * This routine reads the read and write enable bit-sets of the PRS specified by prsIndex.
 *
 * Parameters:
 *  - D4: prsIndex: The index of the PRS whose read and write enable bit-sets shall be read. This argument
 *                  must be below MK_TRICORE_NPRS, otherwise the result value is undefined.
 *
 * Return value:
 *  - E2: A mk_mpurwpermission_t instance containing DPRE_[prsIndex] and DPWE_[prsIndex].
 *
 * Variables:
 *  - D4: Argument is modified to calculate the jump-table offset.
 *  - A4: Used to calculate the address in the jump table.
 *
 * This routine is implemented using a jump table, which jumps to a "subroutine",
 * which handles the respective registers.
 * If the subroutines are changed, the SUBROUTINE_SIZE macros need to be checked.
*/
MK_DoGetDprwe:
	jge.u   d4, MK_imm(#, MK_TRICORE_NPRS), MK_DoGetDprweEpilogue    /* if (prsIndex >= NPRS) goto epilogue; */
	movh.a  a4, MK_imm(#, MK_hi(MK_DoGetDprwe0))                     /* a4 = &MK_DoGetDprwe0; */
	lea     a4, [a4] MK_lo(MK_DoGetDprwe0)
	sh      d4, MK_imm(#, MK_GET_DPRWE_SUBROUTINE_LDSIZE)            /* a4 = a4 + (prsIndex * SUBROUTINE_SIZE); */
	addsc.a a4, a4, d4, MK_imm(#, 0)
	ji      a4

	MK_align(MK_GET_DPRWE_SUBROUTINE_SIZE, MK_GET_DPRWE_SUBROUTINE_LDSIZE)
MK_DoGetDprwe0:
	/* Subroutine assembler code           Comment              Offset relative to begin of subroutine. */

#if (MK_TRICORE_NPRS > 0)
	mfcr    d2, MK_imm(#, MK_DPRE_0)    /* d2 = DPRE_0;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPWE_0)    /* d3 = DPWE_0;                      0x04..0x07 */
	j       MK_DoGetDprweEpilogue       /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPRWE_SUBROUTINE_SIZE, MK_GET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 1)
	mfcr    d2, MK_imm(#, MK_DPRE_1)    /* d2 = DPRE_1;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPWE_1)    /* d3 = DPWE_1;                      0x04..0x07 */
	j       MK_DoGetDprweEpilogue       /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPRWE_SUBROUTINE_SIZE, MK_GET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 2)
	mfcr    d2, MK_imm(#, MK_DPRE_2)    /* d2 = DPRE_2;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPWE_2)    /* d3 = DPWE_2;                      0x04..0x07 */
	j       MK_DoGetDprweEpilogue       /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPRWE_SUBROUTINE_SIZE, MK_GET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 3)
	mfcr    d2, MK_imm(#, MK_DPRE_3)    /* d2 = DPRE_3;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPWE_3)    /* d3 = DPWE_3;                      0x04..0x07 */
	j       MK_DoGetDprweEpilogue       /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPRWE_SUBROUTINE_SIZE, MK_GET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 4)
	mfcr    d2, MK_imm(#, MK_DPRE_4)    /* d2 = DPRE_4;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPWE_4)    /* d3 = DPWE_4;                      0x04..0x07 */
	j       MK_DoGetDprweEpilogue       /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPRWE_SUBROUTINE_SIZE, MK_GET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 5)
	mfcr    d2, MK_imm(#, MK_DPRE_5)    /* d2 = DPRE_5;                      0x00..0x03 */
	mfcr    d3, MK_imm(#, MK_DPWE_5)    /* d3 = DPWE_5;                      0x04..0x07 */
	j       MK_DoGetDprweEpilogue       /* Perform epilogue                  0x08..0x09,0x0b */
	MK_align(MK_GET_DPRWE_SUBROUTINE_SIZE, MK_GET_DPRWE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 6)
#error "Unsupported number of PRSs, this routine needs to be extended."
#endif

MK_DoGetDprweEpilogue:
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

