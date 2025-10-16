/* TRICORE-callnontrustedisr.c
 *
 * This file contains the OS_CallNontrustedIsr interrupt handler wrapper
 * for TRICORE. It is in a separate file to prevent the Tasking compiler
 * from inlining it :-(
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and any
 * other type.
 *
 * Reason:
 * The pointer is passed to hardware, which is only interested in its value
 * and not in its type.
 *
 * MISRAC2012-2) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to
 * object.
 *
 * Reason:
 * A pointer is read from hardware, which doesn't provide C language type
 * information. Hence, a type cast is required.
 *
 * MISRAC2012-3) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 * A value is read from hardware, which essentially represents a pointer.
 * The hardware, though, has no notion of C language types. Hence, the type
 * cast is required.
 */

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_CallNontrustedIsr()
 *
 * This function sets up its own return address and CSA so that an
 * RFE instruction will jump to the first instruction of the ISR
 * with the registers in the expected state. In particular, the register
 * PCXI (in the ISR) must be zero so that the ISR can get back into the kernel.
 * when it returns.
 * The function never returns!
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_CallNontrustedIsr
(	const os_isr_t *isr,
	os_isrdynamic_t *id
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t pcxi;
	os_uppercx_t *cx;
	const os_appcontext_t *a = OS_GET_APP(isr->app);

	/* Ensure that the function call is complete before reading PCXI
	*/
	OS_DSYNC();

	pcxi = OS_MFCR(OS_PCXI);
	/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
	cx = (os_uppercx_t *)OS_AddrFromCx(pcxi);

	/* Eventually align stack */
	OS_ALIGN_STACK(cx->a10);
	id->c.stackLimit = (os_uint8_t *)cx->a10;

	OS_SETISRPROTECTION(isr, id);

	/* Load application's PSW. Ensure trace mode is off and that
	 * we use the interrupt stack.
	*/
	cx->psw = a->archapp.psw | OS_PSW_IS | 1u;	/* trace mode -> off */
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
	/*RES 31:3 - Reserved , PPRS 2:0 rwh Previous PRS*/
	OS_MTCR(OS_PPRS,OS_PSW_GET_PPRS(cx->psw));
#endif
	/* Deviation MISRAC2012-1 <+1> */
	cx->a11 = (os_uint32_t)&OS_NullFunction;
	cx->pcxi = 0;
	pcxi = (pcxi & (OS_CX_CX|OS_PCXI_UL)) | OS_PCXI_PIE | ((os_uint32_t)isr->arch.runPrio << OS_PCXI_PCPN_BIT);
	OS_MTCR(OS_PCXI,pcxi);
	OS_MTRA_FUNCPTR(isr->func);
	OS_MTCR(OS_PSW, OS_PSW_CDC_6|OS_PSW_CDE|OS_PSW_GW|OS_PSW_IS|OS_PSW_IO_SU|OS_PSW_PRS_0);
	OS_RFE();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_callnontrustedisr_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
