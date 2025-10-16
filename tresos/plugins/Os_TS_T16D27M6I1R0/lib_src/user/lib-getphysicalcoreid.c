/* lib-getphysicalcoreid.c
 *
 * This file contains the OS_GetPhysicalCoreId function.
 * It returns the physical ID of the given logical ID
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_alci.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_USE_LOGICAL_CORE_IDS == 1))

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetPhysicalCoreId returns the physical ID of the given logical ID
 *
 * !LINKSTO Kernel.Misc.OS_GetPhysicalCoreId, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_coreid_t OS_GetPhysicalCoreId(os_coreid_t core)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* COVPT-1 +2 */
	/* COVPT-2 */
	if (core >= OS_N_CORES_MAX)
	{
		return core;
	}
	else
	{
		return OS_alciLogToPhy[core];
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_USE_LOGICAL_CORE_IDS == 1))) */
const os_uint8_t OS_dummy_lib_getphysicalcoreid_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_USE_LOGICAL_CORE_IDS == 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/

