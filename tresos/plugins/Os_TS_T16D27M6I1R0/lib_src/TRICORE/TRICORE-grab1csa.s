/* TRICORE-grab1csa.s
 *
 * This file contains the function OS_Grab1Csa
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
 * OS_Grab1Csa() - grabs 1 CSA from the free list.
 *
 * This routine allocates 1 CSA from the free list and returns the
 * link to it. The calling routine is responsible for
 * adjusting the link words of the allocated CSA so that no
 * linkage errors occur.
*/
	_TEXT
	_GLOBAL	OS_Grab1Csa
	_GTYPE(OS_Grab1Csa,@function)
	_GLOBAL	__callee.OS_Grab1Csa.da.i.v
	_GTYPE(__callee.OS_Grab1Csa.da.i.v,@function)


_TTYPE(OS_Grab1Csa,FUNC)
_TTYPE(__callee.OS_Grab1Csa.da.i.v,FUNC)

	dsync								/* We need a DSYNC before the MFCR no matter what happens. */
	mfcr	d15,_IMM(#,OS_PCXI)			/* Save current PCXI */
	svlcx								/* Get a CSA off the free list */
	dsync								/* Wait for instructions to finish */
	mfcr	d2,_IMM(#,OS_PCXI)			/* Get link to newly-grabbed CSA */
	extr.u	d2,d2,_IMM(#,0),_IMM(#,20)	/* Just the address parts */
	_mtcr	_IMM(#,OS_PCXI),d15			/* Restore original PCXI */
	ret

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
