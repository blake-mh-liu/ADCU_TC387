/* Mk_TRICORE_usrcallctrsub.s
 *
 * This file contains the functions MK_UsrCallCtrSub1() MK_UsrCallCtrSub2(),
 * MK_UsrCallCtrSub2V() and MK_UsrCallCtrSub3()
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  This file contains four related microkernel API functions that are identical at the assembly-language level,
 *  and are aliased to the same code.
 *  The exception is permitted by the DCG.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_syscall.h>

	MK_file(Mk_TRICORE_usrcallctrsub.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_UsrCallCtrSub1
	MK_global MK_UsrCallCtrSub2
	MK_global MK_UsrCallCtrSub2V
	MK_global MK_UsrCallCtrSub3

/* !LINKSTO Microkernel.TRICORE.SystemCallInterfaceFunctions, 4
 * !doctype src
*/
MK_UsrCallCtrSub1:
MK_UsrCallCtrSub2:
MK_UsrCallCtrSub2V:
MK_UsrCallCtrSub3:
	syscall	MK_imm(#, MK_SC_CallCtrSub)
	ret
