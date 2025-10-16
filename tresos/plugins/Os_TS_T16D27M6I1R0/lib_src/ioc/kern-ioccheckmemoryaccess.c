/* kern-ioccheckmemoryaccess.c
 *
 * This file contains the IOC helper function OS_KernIocCheckMemoryAccess
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_types.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_kernel.h>
#include <Os_userkernel.h>
#include <Ioc/Ioc_kern.h>

OS_TOOL_FUNCTION_ATTRIB_PRE
os_memoryaccess_t OS_KernIocCheckMemoryAccess( const void *data, os_size_t len )
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_memoryaccess_t access;
	os_uint8_t const inFunction = OS_GetKernelData()->inFunction;

	/* check data pointer */
	/* COVPT-1 */
	if ( inFunction == OS_INTASK )
	{
		os_task_t const * const current_task = OS_GetKernelData()->taskCurrent;
		access = OS_KernCheckTaskMemoryAccess(current_task->taskId, data, len);
	}
	/* COVPT-2 */
	else if ( inFunction == OS_INCAT2 )
	{
		os_isrid_t const current_isr = OS_GetKernelData()->isrCurrent;
		access = OS_KernCheckIsrMemoryAccess(current_isr, data, len);
	}
	else
	{
		access = 0;
	}

	return access;
}

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
const os_uint8_t OS_dummy_kern_ioccheckmemoryaccess_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
