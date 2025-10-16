/* Mk_TRICORE_usrterminateself.s
 *
 * This file contains the functions MK_UsrTerminateSelf(),
 * MK_UsrTerminateSelfWithResult() and MK_UsrTerminateSelfWithValue().
 * In addition, it contains the MK_HwThreadReturn symbol, which is a unreachable on TRICORE.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  This file contains three related microkernel API functions that are identical at the assembly-language level,
 *  and are aliased to the same code.
 *  The exception is permitted by the DCG.
 *
 * DCG-2) Deviated Rule: [OS_ASM_STRUCT_020]
 *  Each assembly file shall contain exactly one return instruction, which is the last instruction.
 *
 * Reason:
 *  TerminateSelf is not expected to return. If it returns for whatever reason (bug, hardware fault),
 *  the only thing we can do here is enter an endless loop.
 */
/* Deviation DCG-1 <*>, DCG-2 <*> */

#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_syscall.h>

	MK_file(Mk_TRICORE_usrterminateself.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_UsrTerminateSelf
	MK_global MK_UsrTerminateSelfWithResult
	MK_global MK_UsrTerminateSelfWithValue
	MK_global MK_HwThreadReturn

/* !LINKSTO Microkernel.TRICORE.SystemCallInterfaceFunctions, 4,
 * !        Microkernel.TRICORE.RegisterStore.MainFuncReturnAddress, 1
 * !doctype src
*/
MK_HwThreadReturn:
	mov		d4, d2					/* Copy return value to 1st parameter */
MK_UsrTerminateSelf:
MK_UsrTerminateSelfWithResult:
MK_UsrTerminateSelfWithValue:
	syscall	MK_imm(#, MK_SC_TerminateSelf)
TerminateSelfErrorLoop:
	j		TerminateSelfErrorLoop	/* Error: TerminateSelf should not return */


