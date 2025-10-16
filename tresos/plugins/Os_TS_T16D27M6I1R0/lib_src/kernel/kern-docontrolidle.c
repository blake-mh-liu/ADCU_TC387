/* kern-docontrolidle.c
 *
 * This file contains the OS_DoControlIdle() function.
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#define OS_SID	OS_SID_ControlIdle
#define OS_SIF	OS_svc_ControlIdle

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_DoControlIdle
 *
 * This function implements part of ControlIdle().
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.ControlIdle, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_DoControlIdle(os_idlemode_t mode)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t result = OS_ERRORCODE_NOCHECK(OS_ERROR_NoError);
	os_kerneldata_t * const kernel_data = OS_GetKernelData();

	kernel_data->idleMode = mode;

	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_docontrolidle_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
