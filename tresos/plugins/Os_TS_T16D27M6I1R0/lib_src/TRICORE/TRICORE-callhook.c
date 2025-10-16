/* TRICORE-callhook.c
 *
 * This file contains the OS_CallHook wrapper for TRICORE. It is in a
 * separate file to prevent the Tasking compiler from inlining it :-(
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
 * OS_CallHook()
 *
 * This function sets up its own return address and CSA so that an
 * RFE instruction will jump to the first instruction of the hook
 * with the registers in the expected state. In particular, the register
 * PCXI (in the hook function) must be zero so that the hook can get back
 * into the kernel when it returns.
 *
 * This function never returns!
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_CallHook
(	const os_appcontext_t *app,
	void *hook,
	os_size_t stackLen,
	os_savedcontext_t *ctxt,
	os_unsigned_t param
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t pcxi;
	os_uppercx_t *cx;

	/* Ensure that the function call is complete before reading PCXI
	*/
	OS_DSYNC();

	pcxi = OS_MFCR(OS_PCXI);
	/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
	cx = (os_uppercx_t *)OS_AddrFromCx(pcxi);

	/* eventually align stack */
	OS_ALIGN_STACK(cx->a10);
	ctxt->stackLimit = (os_uint8_t *)cx->a10;

	OS_SetHookProtection(app, ctxt, stackLen);

	/* Load application's PSW. Ensure trace mode is off and that
	 * we use the interrupt stack.
	*/
	cx->psw = app->archapp.psw | OS_PSW_IS | 1u;	/* trace mode -> off */
#if (OS_TRICOREARCH == OS_TRICOREARCH_18)
	/*RES 31:3 - Reserved , PPRS 2:0 rwh Previous PRS*/
	OS_MTCR(OS_PPRS,OS_PSW_GET_PPRS(cx->psw));
#endif
	/* Deviation MISRAC2012-1 <+1> */
	cx->a11 = (os_uint32_t)&OS_NullFunction;
	cx->pcxi = 0;
	OS_MTRA(hook);

	/* Frig the PSW so that we can RFE from here instead of RET
	*/
	OS_MTCR(OS_PSW, OS_PSW_CDC_6|OS_PSW_CDE|OS_PSW_GW|OS_PSW_IS|OS_PSW_IO_SU|OS_PSW_PRS_0);

	/* Load the parameter for the hook function. This assumes that the
	 * parameter can only be of integral type, which is true at the time
	 * of writing.
	*/
	OS_MTD4(param);

	OS_RFE();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_callhook_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
