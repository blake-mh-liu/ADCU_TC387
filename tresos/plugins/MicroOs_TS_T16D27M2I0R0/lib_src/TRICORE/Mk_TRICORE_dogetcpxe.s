/* Mk_TRICORE_dogetcpxe.s
 *
 * This file contains the function MK_DoGetCpxe for TC1.6E/P and TC1.6.2 MPUs.
 * See gen_Mk_TRICORE_dogetcpxe for further information.
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

#define MK_GET_CPXE_SUBROUTINE_SIZE     8   /* Size of a subroutine which handles one CPR pair. */
#define MK_GET_CPXE_SUBROUTINE_LDSIZE   3   /* Binary logarithm of the subroutine size. */
#if ((1 << MK_GET_CPXE_SUBROUTINE_LDSIZE) != MK_GET_CPXE_SUBROUTINE_SIZE)
#error "Mismatch between MK_GET_CPXE_SUBROUTINE_LDSIZE and MK_GET_CPXE_SUBROUTINE_SIZE."
#endif


	MK_file(Mk_TRICORE_dogetcpxe.s)

	MK_global	MK_DoGetCpxe

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* mk_uint32_t:d2 MK_DoGetCpxe(mk_uint32_t prsIndex:d4)
 *
 * Reads the execute enable bit-set of the PRS specified by prsIndex.
 *
 * Parameters:
 *  - D4: prsIndex    : The index of the PRS whose CPXE shall be read. This argument must be below
 *                      MK_TRICORE_NPRS, otherwise the result value is undefined.
 * Return value:
 *  - D2: The respective CPXE value.
 *
 * Variables:
 *  - A4: Used to calculate the address in the jump table.
 *
 * This routine is implemented using a jump table, which jumps to a "subroutine",
 * which handles the respective registers.
 * If the subroutines are changed, the SUBROUTINE_SIZE macros need to be checked.
*/
MK_DoGetCpxe:
	jge.u   d4, MK_imm(#, MK_TRICORE_NPRS), MK_DoGetCpxeEpilogue    /* if (prsIndex >= NPRS) goto epilogue; */
	movh.a  a4, MK_imm(#, MK_hi(MK_DoGetCpxe0))                     /* a4 = &MK_DoGetCpxe0; */
	lea     a4, [a4] MK_lo(MK_DoGetCpxe0)
	addsc.a a4, a4, d4, MK_imm(#, MK_GET_CPXE_SUBROUTINE_LDSIZE)    /* a4 = a4 + (prsIndex * SUBROUTINE_SIZE); */
	ji      a4

	MK_align(MK_GET_CPXE_SUBROUTINE_SIZE, MK_GET_CPXE_SUBROUTINE_LDSIZE)
MK_DoGetCpxe0:
	/* Subroutine assembler code           Comment              Offset relative to begin of subroutine. */

#if (MK_TRICORE_NPRS > 0)
	mfcr    d2, MK_imm(#, MK_CPXE_0)    /* d2 = CPXE_0;         0x00..0x03 */
	j       MK_DoGetCpxeEpilogue        /* Perform epilogue     0x04..0x05,0x07 */
	MK_align(MK_GET_CPXE_SUBROUTINE_SIZE, MK_GET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 1)
	mfcr    d2, MK_imm(#, MK_CPXE_1)    /* d2 = CPXE_1;         0x00..0x03 */
	j       MK_DoGetCpxeEpilogue        /* Perform epilogue     0x04..0x05,0x07 */
	MK_align(MK_GET_CPXE_SUBROUTINE_SIZE, MK_GET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 2)
	mfcr    d2, MK_imm(#, MK_CPXE_2)    /* d2 = CPXE_2;         0x00..0x03 */
	j       MK_DoGetCpxeEpilogue        /* Perform epilogue     0x04..0x05,0x07 */
	MK_align(MK_GET_CPXE_SUBROUTINE_SIZE, MK_GET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 3)
	mfcr    d2, MK_imm(#, MK_CPXE_3)    /* d2 = CPXE_3;         0x00..0x03 */
	j       MK_DoGetCpxeEpilogue        /* Perform epilogue     0x04..0x05,0x07 */
	MK_align(MK_GET_CPXE_SUBROUTINE_SIZE, MK_GET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 4)
	mfcr    d2, MK_imm(#, MK_CPXE_4)    /* d2 = CPXE_4;         0x00..0x03 */
	j       MK_DoGetCpxeEpilogue        /* Perform epilogue     0x04..0x05,0x07 */
	MK_align(MK_GET_CPXE_SUBROUTINE_SIZE, MK_GET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 5)
	mfcr    d2, MK_imm(#, MK_CPXE_5)    /* d2 = CPXE_5;         0x00..0x03 */
	j       MK_DoGetCpxeEpilogue        /* Perform epilogue     0x04..0x05,0x07 */
	MK_align(MK_GET_CPXE_SUBROUTINE_SIZE, MK_GET_CPXE_SUBROUTINE_LDSIZE)
#endif

#if (MK_TRICORE_NPRS > 6)
#error "Unsupported number of PRSs, this routine needs to be extended."
#endif

MK_DoGetCpxeEpilogue:
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

