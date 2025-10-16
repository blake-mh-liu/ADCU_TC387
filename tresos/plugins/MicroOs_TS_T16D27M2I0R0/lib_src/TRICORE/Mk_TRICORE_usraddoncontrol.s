/* Mk_TRICORE_usraddoncontrol.s
 *
 * This file contains the function MK_UsrAddOnControl()
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

	MK_file(Mk_TRICORE_usraddoncontrol.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_UsrAddOnControl
	MK_global MK_UsrAddOnControl1
	MK_global MK_UsrAddOnControl2
	MK_global MK_UsrAddOnControl3

/* MK_UsrAddOnControl, MK_UsrAddOnControl1, MK_UsrAddOnControl2, MK_UsrAddOnControl3
 *
 * Prototypes:
 *	mk_statusandvalue_t MK_UsrAddOnControl(mk_objectid_t);
 *	mk_statusandvalue_t MK_UsrAddOnControl1(mk_objectid_t, mk_parametertype_t);
 *	mk_statusandvalue_t MK_UsrAddOnControl2(mk_objectid_t, mk_parametertype_t, mk_parametertype_t);
 *	mk_statusandvalue_t MK_UsrAddOnControl3(mk_objectid_t, mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
 *
 * Parameters:
 *	d4 - add-on ID (mk_objectid_t)
 *	d5..d7 - parameters
 *
 * Returned value:
 *	E2 - mk_statusandvalue_t
 *		mk_statusandvalue_t fits into 64 bit, so it is returned in E2 (d2, d3).
 *
 * !LINKSTO Microkernel.TRICORE.SystemCallInterfaceFunctions, 4
 * !doctype src
*/

MK_UsrAddOnControl:
MK_UsrAddOnControl1:
MK_UsrAddOnControl2:
MK_UsrAddOnControl3:
	syscall	MK_imm(#, MK_SC_AddOnControl)
	ret
