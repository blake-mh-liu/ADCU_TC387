/* Mk_TRICORE_compilerstackcheckfail.s
 *
 * This file contains the function MK_CompilerStackCheckFail for
 * the diab stack-protection features.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  For this DCG, an exception can be made for a group of routines that are always
 *  used together.
 *  This holds true for the routines in this file because they are closely related.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_tool.h>

	MK_file(Mk_TRICORE_compilerstackcheckfail.s)

	MK_global MK_CompilerStackCheckFail
	MK_global MK_CompilerStackCheckFailLandingPad

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* MK_CompilerStackCheckFail() - internal function to handle compiler stack smashing protection.
 *
 * !LINKSTO Microkernel.Function.MK_CompilerStackCheckFail, 2
 * !doctype src
*/
MK_CompilerStackCheckFail:
/* The following code inserts an invalid byte pattern into the instruction stream.
 * This triggers a trap (class 2, tin 1: "Illegal Opcode").
 * The label MK_CompilerStackCheckFailLandingPad marks the address of the exception.
 * Note: this function must never return! The 'ret' instruction is only there to comply with
 * the DCG but is unreachable through normal code execution.
*/
MK_CompilerStackCheckFailLandingPad:
	MK_HWORD    0xebeb
	j           MK_CompilerStackCheckFailLandingPad
	ret

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/

