/* kern-nullerrorhook.c
 *
 * This file contains the OS_NullErrorHook function.
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

/* OS_NullErrorHook
 *
 * This function does nothing. It is used as a replacement for ErrorHook
 * and ShutdownHook when the configuration specifies no hook.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_NullErrorHook(os_result_t code)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	OS_PARAM_UNUSED(code);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_nullerrorhook_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
