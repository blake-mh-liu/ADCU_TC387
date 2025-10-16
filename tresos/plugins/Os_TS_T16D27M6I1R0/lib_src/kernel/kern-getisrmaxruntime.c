/* lib-getisrmaxruntime.c
 *
 * This file contains the OS_GetIsrMaxRuntime function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_acct_api.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetIsrMaxRuntime
 *
 * This library function returns the longest observed run-time for an ISR.
 * It can be called by any trusted application. On some architectures
 * it might be callable from non-trusted applications too.
 *
 * If the ISR ID is out of range, or if the ISR does not have runtime
 * measurement enabled, E_OS_ID is returned. Otherwise, the ISR's
 * longest observed runtime is placed in the out location and E_OK is returned.
 * The error handler ia not called, so no error hook is called.
 *
 * !LINKSTO Kernel.Feature.OsAccounting, 1,
 * !        Kernel.Feature.OsAccounting.API.GetIsrMaxRuntime, 1
 * !doctype SRC
*/

OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_GetIsrMaxRuntime(os_isrid_t i, os_tick_t *out)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t r = OS_E_ID;
	const os_isr_t *isr;
	os_israccounting_t *ia;

	if ( i < OS_nInterrupts )
	{
		isr = &OS_isrTableBase[i];
		ia = OS_GET_ACCT(isr->accounting);

		if ( (isr->flags & OS_ISRF_MEASUREEXEC) != 0u )
		{
			*out = ia->etMax;
			r = OS_E_OK;
		}
	}

	return r;
}

#include <memmap/Os_mm_code_end.h>


#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_getisrmaxruntime_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
