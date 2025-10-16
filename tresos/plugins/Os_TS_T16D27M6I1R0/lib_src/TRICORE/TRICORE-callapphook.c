/* TRICORE-callapphook.c
 *
 * This file contains the OS_CallAppHook wrapper for TRICORE.
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
 * OS_CallAppHook
 *
 * This wrapper function has the effect of calling an application-specific
 * hook. Such a hook is not called directly, but "started" in a
 * manner similar to a task. When the hook returns, it triggers a PCX==0
 * exception and the trap handler picks up the stored PCXI and RA and returns
 * to the caller of this function.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_CallAppHook
(	const os_appcontext_t *app,
	os_savedcontext_t *ctxt,
	void *hook,
	os_stacklen_t stackLen,
	os_unsigned_t param
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Ensure that the function call is complete before reading PCXI
	*/
	OS_DSYNC();

	ctxt->pcxi = OS_MFCR(OS_PCXI);
	ctxt->ra = OS_MFRA();

	OS_CallHook(app, hook, stackLen, ctxt, param);
	/* Never returns */

	/* Force a CALL to OS_CallHook() instead of a JUMP
	 * Should never get here.
	*/
	OS_ShutdownNoHooks();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_callapphook_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
