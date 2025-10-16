/* Mk_TRICORE_usrasynccallctrsub.s
 *
 * This file contains the functions MK_UsrAsyncCallCtrSub1(),
 * MK_UsrAsyncCallCtrSub2() and MK_UsrAsyncCallCtrSub3()
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
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_syscall.h>

	MK_file(Mk_TRICORE_usrasynccallctrsub.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_UsrAsyncCallCtrSub1
	MK_global MK_UsrAsyncCallCtrSub2
	MK_global MK_UsrAsyncCallCtrSub3

/* !LINKSTO Microkernel.TRICORE.SystemCallInterfaceFunctions, 4
 * !doctype src
*/
MK_UsrAsyncCallCtrSub1:
MK_UsrAsyncCallCtrSub2:
MK_UsrAsyncCallCtrSub3:
	syscall	MK_imm(#, MK_SC_AsyncCallCtrSub)
	ret
