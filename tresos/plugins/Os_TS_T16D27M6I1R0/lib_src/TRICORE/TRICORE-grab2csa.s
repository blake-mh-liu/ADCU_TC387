/* TRICORE-grab2csa.s
 *
 * This file contains the function OS_Grab2Csa
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
 * OS_Grab2Csa() - grabs 2 CSAs from the free list.
 *
 * This routine allocates 2 CSAs from the free list and returns the
 * link to the first one. The calling routine is responsible for
 * adjusting the link words of the 2 allocated CSAs so that no
 * linkage errors occur.
*/
	_TEXT
	_GLOBAL	OS_Grab2Csa
	_GTYPE(OS_Grab2Csa,@function)
	_GLOBAL	__callee.OS_Grab2Csa.da.i.v
	_GTYPE(__callee.OS_Grab2Csa.da.i.v,@function)


_TTYPE(OS_Grab2Csa,FUNC)
_TTYPE(__callee.OS_Grab2Csa.da.i.v,FUNC)

	mfcr	d15,_IMM(#,OS_PCXI)			/* Save current PCXI */
	svlcx								/* Get a CSA off the free list */
	svlcx								/* Get another CSA off the free list */
	dsync								/* Wait for instructions to finish */
	mfcr	d2,_IMM(#,OS_PCXI)			/* Get link to newly-grabbed CSA */
	extr.u	d2,d2,_IMM(#,0),_IMM(#,20)	/* Just the address parts */
	_mtcr	_IMM(#,OS_PCXI),d15			/* Restore original PCXI */
	ret

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
