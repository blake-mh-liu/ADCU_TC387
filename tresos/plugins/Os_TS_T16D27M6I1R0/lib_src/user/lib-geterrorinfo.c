/* lib-geterrorinfo.c
 *
 * This file contains the OS_GetErrorInfo function.
 * It retrieves the error status information for the current core.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <Os_api.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_error.h>
#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetErrorInfo - return error status information.
 * Comment: This function is not called OS_GetErrorStatus, since
 * this was a macro in 5.1.
*/

/*
 * !LINKSTO Kernel.Feature.ErrorStatus.API.GetErrorInfo, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
const os_errorstatus_t * OS_GetErrorInfo(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	return &(OS_GetKernelData()->errorStatus);
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
const os_uint8_t OS_dummy_lib_geterrorinfo_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
