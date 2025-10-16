/* kern-recvclearpendinginterrupt.c
 *
 * This file contains the function OS_RecvClearPendingInterrupt().
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#define OS_SID OS_SID_ClearPendingInterrupt
#define OS_SIF OS_svc_ClearPendingInterrupt

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>
#include <Os_panic.h>

/*!
 * OS_RecvClearPendingInterrupt
 *
 * Handles cross-core ClearPendingInterrupt() calls.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvClearPendingInterrupt(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_isrid_t const isrId = (os_isrid_t)msg->parameter[0];
	/* COVPT-1 */
	if (OS_IsValidIsrId(isrId) && (msg->result != OS_NULL))
	{
		os_paramtype_t replyParams[OS_MAXPARAM];
		replyParams[0] = (os_paramtype_t)OS_LocalClearPendingInterrupt(&OS_isrTableBase[isrId]);
#if OS_XC_REPLY_DIRECTLY
		OS_WriteMessageResult(msg, replyParams[0]);
#else
		OS_SendMessage(msg->from, OS_XC_OP_ReturnResult, msg->result, replyParams);
#endif
	}
	else
	{
		(void)OS_PANIC(OS_PANIC_CrosscoreCommunicationError);
	}
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_recvclearpendinginterrupt_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
