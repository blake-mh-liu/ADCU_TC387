/* kern-nullprotectionhook.c
 *
 * This file contains the OS_NullProtectionHook function.
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

/* OS_NullProtectionHook
 *
 * This function does nothing but return OS_ACTION_SHUTDOWN (==PRO_SHUTDOWN).
 * The function is used as the protection hook when no user protection hook
 * is configured and strict Autosar * conformance is required.
 *
 * !LINKSTO Kernel.Autosar.Protection.ProtectionHook.NoHook, 2
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_erroraction_t OS_NullProtectionHook(os_result_t err)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	OS_PARAM_UNUSED(err);
	return OS_ACTION_SHUTDOWN;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_nullprotectionhook_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
