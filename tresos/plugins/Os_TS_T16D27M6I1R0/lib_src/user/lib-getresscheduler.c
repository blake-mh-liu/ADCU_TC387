/* lib-getresscheduler.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_api.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetResScheduler implements the API RES_SCHEDULER for multi-core systems.
 *
 * It returns the RES_SCHEDULER resource of the current core.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.GetResScheduler, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_resourceid_t OS_GetResScheduler(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	return OS_resSchedulerMap[OS_ArchGetCoreId()];
}
#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
const os_uint8_t OS_dummy_lib_getresscheduler_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
