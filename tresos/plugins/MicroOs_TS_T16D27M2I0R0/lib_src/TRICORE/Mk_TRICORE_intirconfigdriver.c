/* Mk_TRICORE_intirconfigdriver.c
 *
 * This file contains interrupt controller configuration functions.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  This function can call itself again indirectly via MK_Panic. This happens if an error is
 *  detected here and MK_Panic is called to shut down the system. During shutdown, MK_InitInterrupts
 *  is invoked, which calls this function again. If the error persists, MK_Panic will be called
 *  again, but will detect this and as a consequence call MK_PanicStop to halt the system
 *  immediately. So there is a maximum nesting of two calls to this function possible.
 *  Note:
 *  This deviation is actually not found by the MISRA checker because of the use of function
 *  pointers. It is only here to document that this violation is justified anyway.
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  This file contains the functions which are meant to be referenced by
 *  MK_intIrConfigDriver. Either all of them need to go to the binary or none of them.
*/
/* Deviation DCG-1 <*> */

#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>

/* These functions only exist so we can have function pointers to them. */
void MK_EnableIrq(mk_reg32_t *srnsrc)
{
	MK_EnableIrqImpl(srnsrc);
}
void MK_DisableIrq(mk_reg32_t *srnsrc)
{
	MK_DisableIrqImpl(srnsrc);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
