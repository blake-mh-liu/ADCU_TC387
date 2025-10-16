/* TRICORE-callisr.c
 *
 * This file contains the OS_TricoreCallIsr interrupt handler wrapper for TRICORE.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_TricoreCallIsr
 *
 * This wrapper function has the effect of calling an ISR. An ISR is not
 * called directly, but "started" in a manner similar to a task. When the
 * ISR returns, it triggers a PCX==0 exception and the trap handler
 * picks up the stored PCXI and RA and returns to the cat2entry
 * function.
 *
 * The reason for all this is that we have to ensure that the timelimit
 * timeout interrupt cannot occur between the ISR returning and
 * the disable interrupts statement just after the return. If this
 * were to occur, the saved PCXI value would no longer be valid and
 * a crash would occur.
 *
 * This routine enables interrupts by setting the required level in the
 * dummy PCXI. The RFE instruction restores this level.
 *
 * If the ISR is trusted, we *could* call it directly ...
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_TricoreCallIsr
(	const os_isr_t *isr,
	os_isrdynamic_t *id
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Ensure that the function call is complete before reading PCXI
	*/
	OS_DSYNC();

	id->c.pcxi = OS_MFCR(OS_PCXI);
	id->c.ra = OS_MFRA();

	if ( OS_IsrIsTrusted(isr) )
	{
		os_uint32_t oldIcr;

		id->c.stackLimit = (os_uint8_t *) OS_MFSP();
		oldIcr = OS_MFCR(OS_ICR);
		OS_MTCR(OS_ICR, (oldIcr & (os_uint32_t) ~((os_uint32_t) OS_ICR_CCPN)) | isr->arch.runPrio);

		(*(isr->func))();

		OS_MTCR(OS_ICR, oldIcr);
	}
	else
	{
		OS_CallNontrustedIsr(isr, id);	/* Never returns */

		/* Force a CALL to OS_CallNontrustedIsr() instead of a JUMP
		 * Should never get here.
		*/
		OS_ShutdownNoHooks();
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_callisr_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
