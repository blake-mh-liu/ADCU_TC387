/* Mk_TRICORE_setandchecksrcvalue.c
 *
 * This file contains the function MK_SetAndCheckSrcValue().
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
 *
*/

#include <public/Mk_basic_types.h>
#include <private/Mk_panic.h>
#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>

/* MK_SetAndCheckSrcValue()
 *
 * This function writes a value to an SRC register, reads it back and calls MK_Panic(),
 * if the value is not as expected.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_SetAndCheckSrcValue, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 */
void MK_SetAndCheckSrcValue(mk_hwirqctrlreg_t src, mk_uint32_t value)
{
	mk_uint32_t readback;

	*src = value;

	/* Note: mk_hwirqctrlreg_t is volatile qualified, so this is actually read back
	*/
	readback = *src;

	if ( (readback & MK_SRC_CHECK_MASK) != (value & MK_SRC_CHECK_MASK) )
	{
		/* Deviation MISRAC2012-1 <+1> */
		MK_Panic(MK_panic_UnexpectedHardwareResponse);
	}

}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
