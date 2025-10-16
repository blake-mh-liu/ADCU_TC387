/* TRICORE-unknowninterrupt.s
 *
 * This file contains the unknown interrupt entry and exit routines
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

	_GLOBAL		OS_UnknownInterruptHandler
	_EXTERN		OS_UnknownInterrupt

/* OS_TRICORE_UnknownInterrupt
 *
 * This routine serves as the interrupt entry routine for unconfigured
 * interrupts. It gets called from the interrupt vector code using a
 * normal CALL instruction.
 *
 * On entry:
 *    upper and lower context saved
 *    interrupts enabled at the bisr level
 *    desired CCPN/IE in d4
 *
 * For unknown interrupts, the BISR level should be 255 and the
 * "desired" level should be the arbitration priority of the interrupt
 * (== the entry number in the interrupt table).
 *
 * On TRICORE, we have no direct way of finding out which interrupt
 * source triggered any particular interrupt, short of looking at each
 * service request register in turn. At the moment, we simply pass the
 * given interrupt number on to the generic OS_UnknownInterrupt
 * handler.
*/
	_TEXT

OS_UnknownInterruptHandler:

/* Using jl to call the generic OS_UnknownInterrupt error routine
 * means that the return from that function will be to this routine
 * (the next instruction), but the CSA stored by the CALL instruction
 * in the vector will get popped. After that, we simply return to the
 * interrupted code using rslcx/rfe as normal for a interrupt vector.
*/
	jl		OS_UnknownInterrupt
	rslcx
	rfe

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
