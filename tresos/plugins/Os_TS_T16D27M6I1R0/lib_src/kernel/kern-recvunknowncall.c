/* kern-recvunknowncall.c
 *
 * This file contains the function OS_RecvUnknownCall().
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

/*!
 * OS_RecvUnknownCall()
 *
 * Handle unknown calls gracefully.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvUnknownCall(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* COVPT-1 */
	OS_PARAM_UNUSED(msg);
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_recvunknowncall_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
