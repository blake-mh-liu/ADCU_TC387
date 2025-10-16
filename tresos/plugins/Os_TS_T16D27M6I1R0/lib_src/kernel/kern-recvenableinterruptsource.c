/* kern-recvenableinterruptsource.c
 *
 * This file contains the function OS_RecvEnableInterruptSource().
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * Boolean type value was required to be stored in fixed length type for cross core messaging.
*/

#define OS_SID OS_SID_EnableInterruptSource
#define OS_SIF OS_svc_EnableInterruptSource

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>
#include <Os_panic.h>

/*!
 * OS_RecvEnableInterruptSource
 *
 * Handles cross-core EnableInterruptSource() calls.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvEnableInterruptSource(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_isrid_t const isrId = (os_isrid_t)msg->parameter[0];
	/* Deviation MISRAC2012-1 <+1> */
	os_boolean_t clearPending = (os_boolean_t)msg->parameter[1];

	/* COVPT-1 */
	if (OS_IsValidIsrId(isrId) && (msg->result != OS_NULL))
	{
		os_paramtype_t replyParams[OS_MAXPARAM];
		replyParams[0] = (os_paramtype_t)OS_LocalEnableInterruptSource(&OS_isrTableBase[isrId], clearPending);
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
const os_uint8_t OS_dummy_kern_recvenableinterruptsource_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
