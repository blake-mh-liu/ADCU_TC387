/* TRICORE-cat1interrupt.s
 *
 * This file contains the category 1 interrupt exit routine
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

	_GLOBAL		OS_Cat1Exit

/* OS_Cat1Exit
 *
 * This routine is the interrupt exit routine for Category 1 interrupts. It
 * jumped to by the interrupt vector stub and exits via RSLCX/RFE.
*/
	_TEXT

OS_Cat1Exit:

	rslcx
	rfe

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
