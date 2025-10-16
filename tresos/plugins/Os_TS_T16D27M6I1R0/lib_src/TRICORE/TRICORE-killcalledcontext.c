/* TRICORE-killcalledcontext.c
 *
 * This file contains OS_KillCalledContext for TRICORE
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 * A value, which essentially represents a pointer, is written to hardware.
 * The access function expects a C languate pointer, though, and this makes
 * a type cast necessary.
 */

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KillCalledContext
 *
 * A called context is a context such as an ISR or a hook function that
 * is called, and normall returns, in a properly nested fashion. That
 * means that the information about the call (return address, etc)
 * is normally held in the processor's call stack or equivalent.
 *
 * On TRICORE, the called context is killed by discarding the current
 * PCXI list as far as the pcxi value stored in the ISR's state structure.
 * Then the stored pcxi and a11 values are loaded, some other registers are
 * frigged, and execution resumes by means of RFE just after the ISR was
 * called.
 *
 * Or so it is hoped ;-)
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KillCalledContext(os_savedcontext_t *sc)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t pcxi;

	/* We need to discard all the CSAs from here to the call to the ISR.
	 * In some cases the list is 0-terminated, in others it isn't (for
	 * example, if the ISR is trusted, it might be called directly)
	 *
	 * Then we "return" to the context that was saved by OS_TricoreCallIsr().
	 * The register values from that context are in the first CSA of the
	 * reloaded list.
	 * We have to frig the current PSW to make the RFE possible.
	 * An alternative, reprogramming the ICR, would take longer.
	*/
	if ( sc->pcxi != 0u )
	{
		/* Ensure that the function call is complete before reading PCXI
		*/
		OS_DSYNC();

		pcxi = OS_MFCR(OS_PCXI);

		OS_FreeCxListTo(pcxi, sc->pcxi);
		OS_MTCR(OS_PCXI, sc->pcxi);
		/* Deviation MISRAC2012-1 <+1> */
		OS_MTRA((void *)(sc->ra));
		OS_MTCR(OS_PSW, OS_PSW_CDC_6|OS_PSW_CDE|OS_PSW_GW|OS_PSW_IS|OS_PSW_IO_SU|OS_PSW_PRS_0);
		OS_RFE();
	}

	/* If we get here, we can't kill the called context. Returning some code
	 * other than OS_E_OK indicates this.
	*/
	return OS_E_INTERNAL;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_killcalledcontext_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
