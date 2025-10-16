/* kern-initexecutiontiming.c
 *
 * This file contains the OS_InitExecutionTiming function.
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

/* OS_InitExecutionTiming
 *
 * This function initialises the kernel's execution-time monitoring feature.
 * The timer used is initialised using the architecture-dependent function.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitExecutionTiming(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	OS_GetKernelData()->accounting.inFunction = OS_INNOTHING;
	OS_InitExecTimer();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_initexecutiontiming_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
