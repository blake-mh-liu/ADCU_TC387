/* TRICORE-freecxlist.s
 *
 * This file contains the function TRICORE_FreeCxList
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ASM
#define OS_ASM
#endif

#include <Os_asm_common.h>
#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_kernel.h>
#include <Os_tool.h>
#include <TRICORE/Os_TRICORE_core.h>

/*!
 * OS_FreeCxList() - frees a list of CSAs
 *
 * This routine transfers a list of CSAs to the free list by executing
 * RSLCX repeatedly in a loop. The loop terminates when the PXCI link
 * becomes zero.
 * The head of the CSA list to free is passed in d4
*/
	_TEXT
	_GLOBAL	OS_FreeCxList
	_GTYPE(OS_FreeCxList,@function)
	_GLOBAL	__callee.OS_FreeCxList.da.v.i
	_GTYPE(__callee.OS_FreeCxList.da.v.i,@function)


_TTYPE(OS_FreeCxList,FUNC)
_TTYPE(__callee.OS_FreeCxList.da.v.i,FUNC)
	mov.aa	a15,a11				/* Save return address */
	mov		d15,d4				/* Working PCXI = head */
	mfcr	d14,_IMM(#,OS_PCXI)	/* Save current PCXI */

.l1:
	extr.u	d15,d15,_IMM(#,0),_IMM(#,20)	/* Just the address parts */
	jz		d15,.l2				/* Reached end of list? */
	_mtcr	_IMM(#,OS_PCXI),d15	/* U/L bit is zero! */
	rslcx						/* Release one CSA */
	dsync						/* Wait for instruction to finish */
	mfcr	d15,_IMM(#,OS_PCXI)	/* Get next CSA & repeat */
	j		.l1

.l2:
	mov.aa	a11,a15				/* Restore saved a11 */
	_mtcr	_IMM(#,OS_PCXI),d14	/* Restore saved PCXI */
	ret

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
