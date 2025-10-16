/* Mk_k_fillthreadregisters.c
 *
 * This file contains the MK_FillThreadRegisters() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *  Conversions shall not be performed between a pointer to a function
 *  and any other type.
 *
 * Reason:
 *  To set the address where to start or return to, the C language function
 *  pointer must be converted to its bare value so that hardware can interpret
 *  it correctly. That's because hardware has no notion of C language types.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_VOCF]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  Most of the macros used in this function set elements in a structure
 *  resulting in the high VOCF metric. The goal of the VOCF metric is to
 *  ensure maintainability. With only five macro calls the implementation
 *  of this function has this property.
*/

/* Deviation DCG-1 <*> */

#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* MK_FillThreadRegisters() fills the thread's registers with the initial values
 *
 * Parameters:
 *	threadCfg	- address of a thread config block for this thread
 *
 * Precondition:
 *	the registers are not in use (the thread is idle OR the registers are not shared)
 *
 * !LINKSTO Microkernel.Function.MK_FillThreadRegisters, 1
 * !doctype src
*/
void MK_FillThreadRegisters(mk_threadregisters_t *regs, const mk_threadcfg_t *threadCfg)
{
	/* Poke the starting address, PSW and other initial register values into the register structure.
	*/
	/* Deviation MISRAC2012-1 <+1> */
	MK_HwSetMain(regs, threadCfg->entry);
	MK_HwSetPs(regs, threadCfg->ps);
	MK_HwSetStackPointer(regs, threadCfg->initialSp);
	/* Deviation MISRAC2012-1 <+1> */
	MK_HwSetReturnAddress(regs, &MK_HwThreadReturn);
	MK_HwSetConstantRegisters(regs);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
