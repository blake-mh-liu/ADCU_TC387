/* kern-retnresult.c
 *
 * This file contains the function OS_RetnResult().
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_RetnResult()
 *
 * This function is used to return the result (e.g. error code) of a cross-core call.
 * Note, this function is always executed on the core, which originally initiated the
 * cross-core system call. Hence, no cache management operations are necessary.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RetnResult(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* COVPT-1 */
	*(msg->result) = (os_paramtype_t)msg->parameter[0];
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_retnresult_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
