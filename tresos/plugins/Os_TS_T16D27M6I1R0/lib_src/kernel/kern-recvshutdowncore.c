/* kern-recshutdowncore.c
 *
 * This file contains the function OS_RecvShutdownCore().
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
 * OS_RecvShutdownCore
 *
 * Handles cross-core ShutdownCore() calls.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvShutdownCore(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	OS_Shutdown((os_result_t)msg->parameter[0], OS_TRUE);
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_recvshutdowncore_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
