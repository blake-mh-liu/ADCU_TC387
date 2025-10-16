/* kern-killisr.c
 *
 * This file contains OS_KillIsr
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
 * OS_KillIsr
 *
 * The ISR is killed by calling the architecture specific function
 * or macro OS_KillCalledContext() with the ISR's saved
 * context as parameter.
 * Resources are released, and interrupt status restored, in OS_Cat2Entry.
 *
 * !LINKSTO Kernel.Autosar.Protection.ProtectionHook.KillISR, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KillIsr(os_isrid_t i)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_isrdynamic_t * const id = OS_isrTableBase[i].dynamic;

	OS_MarkIsrKilled(id);
	return OS_KillCalledContext(&id->c);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_killisr_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
