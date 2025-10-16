/* Mk_TRICORE_dosetcpxe.s
 *
 * This file contains the function MK_DoSetCpxe for TC1.6E/P and TC1.6.2 MPUs.
 * See gen_Mk_TRICORE_dosetcpxe for further information.
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

#define MK_SET_CPXE_SUBROUTINE_SIZE     16  /* Size of a subroutine which handles one CPR pair. */
#define MK_SET_CPXE_SUBROUTINE_LDSIZE   4   /* Binary logarithm of the subroutine size. */
#if ((1 << MK_SET_CPXE_SUBROUTINE_LDSIZE) != MK_SET_CPXE_SUBROUTINE_SIZE)
#error "Mismatch between MK_SET_CPXE_SUBROUTINE_LDSIZE and MK_SET_CPXE_SUBROUTINE_SIZE."
#endif


	MK_file(Mk_TRICORE_dosetcpxe.s)

	MK_global	MK_DoSetCpxe

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* mk_uint32_t:d2 MK_DoSetCpxe(mk_uint32_t prsIndex:d4, mk_uint32_t xe:d5)
 *
 * This routine sets the execute enable bitset of the PRS specified by prsIndex to xe.
 * A synchronization primitive is executed to ensure that the register
 * bank has been completely programmed before returning.
 *
 * Parameters:
 *  - D4: prsIndex    : The index of the PRS whose CPXE shall be set. This argument must be below MK_TRICORE_NPRS.
 *  - D5: xe          : The value which shall be written to and CPXE[cprIndex]
 *
 * Return value:
 *  - D2: Zero, if the register was written successfully, otherwise an arbitrary non-zero value.
 *        If prsIndex is invalid, this routine returns an undefined value.
 *
 * Variables:
 *  - D4: Argument is modified to calculate the jump-table offset.
 *  - A4: Used to calculate the address in the jump table.
 *  - D2: Used to -- check the index argument (this way the result is non-zero if the check fails),
 *                -- read back the respective CPXE_i register,
 *                -- return the result value of this routine.
 *
 * This routine is implemented using a jump table, which jumps to a "subroutine",
 * which handles the respective registers.
 * If the subroutines are changed, the SUBROUTINE_SIZE macros need to be checked.
*/
MK_DoSetCpxe:
	/* Check index argument to prevent loss of control flow integrity. */
	mov     d2, MK_imm(#, MK_TRICORE_NPRS)
	jge.u   d4, d2, MK_DoSetCpxeReturn
	/* Branch to respective jump-table offset. */
	movh.a  a4, MK_imm(#, MK_hi(MK_DoSetCpxe0))                     /* a4 = &MK_DoSetCpxe0; */
	lea     a4, [a4] MK_lo(MK_DoSetCpxe0)
	sh      d4, MK_imm(#, MK_SET_CPXE_SUBROUTINE_LDSIZE)            /* a4 = a4 + (prsIndex * SUBROUTINE_SIZE); */
	addsc.a a4, a4, d4, MK_imm(#, 0)
	ji      a4

	MK_align(MK_SET_CPXE_SUBROUTINE_SIZE, MK_SET_CPXE_SUBROUTINE_LDSIZE)
MK_DoSetCpxe0:
	/* Subroutine assembler code           Comment              Offset relative to begin of subroutine. */

#if (MK_TRICORE_NPRS > 0)
	mtcr    MK_imm(#, MK_CPXE_0), d5    /* CPXE_0 = xe;                         0x00..0x03 */
	isync                               /* Ensure all mtcr have taken place;    0x04..0x07 */
	mfcr    d2, MK_imm(#, MK_CPXE_0)    /* d2 = CPXE_0;                         0x08..0x0b */
	j       MK_DoSetCpxeEpilogue        /* Perform epilogue;                    0x0c..0x0d,0x0f */
	MK_align(MK_SET_CPXE_SUBROUTINE_SIZE, MK_SET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 1)
	mtcr    MK_imm(#, MK_CPXE_1), d5    /* CPXE_1 = xe;                         0x00..0x03 */
	isync                               /* Ensure all mtcr have taken place;    0x04..0x07 */
	mfcr    d2, MK_imm(#, MK_CPXE_1)    /* d2 = CPXE_1;                         0x08..0x0b */
	j       MK_DoSetCpxeEpilogue        /* Perform epilogue;                    0x0c..0x0d,0x0f */
	MK_align(MK_SET_CPXE_SUBROUTINE_SIZE, MK_SET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 2)
	mtcr    MK_imm(#, MK_CPXE_2), d5    /* CPXE_2 = xe;                         0x00..0x03 */
	isync                               /* Ensure all mtcr have taken place;    0x04..0x07 */
	mfcr    d2, MK_imm(#, MK_CPXE_2)    /* d2 = CPXE_2;                         0x08..0x0b */
	j       MK_DoSetCpxeEpilogue        /* Perform epilogue;                    0x0c..0x0d,0x0f */
	MK_align(MK_SET_CPXE_SUBROUTINE_SIZE, MK_SET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 3)
	mtcr    MK_imm(#, MK_CPXE_3), d5    /* CPXE_3 = xe;                         0x00..0x03 */
	isync                               /* Ensure all mtcr have taken place;    0x04..0x07 */
	mfcr    d2, MK_imm(#, MK_CPXE_3)    /* d2 = CPXE_3;                         0x08..0x0b */
	j       MK_DoSetCpxeEpilogue        /* Perform epilogue;                    0x0c..0x0d,0x0f */
	MK_align(MK_SET_CPXE_SUBROUTINE_SIZE, MK_SET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 4)
	mtcr    MK_imm(#, MK_CPXE_4), d5    /* CPXE_4 = xe;                         0x00..0x03 */
	isync                               /* Ensure all mtcr have taken place;    0x04..0x07 */
	mfcr    d2, MK_imm(#, MK_CPXE_4)    /* d2 = CPXE_4;                         0x08..0x0b */
	j       MK_DoSetCpxeEpilogue        /* Perform epilogue;                    0x0c..0x0d,0x0f */
	MK_align(MK_SET_CPXE_SUBROUTINE_SIZE, MK_SET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 5)
	mtcr    MK_imm(#, MK_CPXE_5), d5    /* CPXE_5 = xe;                         0x00..0x03 */
	isync                               /* Ensure all mtcr have taken place;    0x04..0x07 */
	mfcr    d2, MK_imm(#, MK_CPXE_5)    /* d2 = CPXE_5;                         0x08..0x0b */
	j       MK_DoSetCpxeEpilogue        /* Perform epilogue;                    0x0c..0x0d,0x0f */
	MK_align(MK_SET_CPXE_SUBROUTINE_SIZE, MK_SET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 6)
#error "Unsupported number of PRSs, this routine needs to be extended."
#endif

MK_DoSetCpxeEpilogue:
	xor     d2, d5  /* d2 ^= xe; */
MK_DoSetCpxeReturn:
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

