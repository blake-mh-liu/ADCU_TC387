/* kern-recvgetevent.c
 *
 * This file contains the function OS_RecvGetEvent().
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
#include <Os_panic.h>

/*!
 * OS_RecvGetEvent()
 *
 * Handles cross-core GetEvent() requests.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvGetEvent(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_taskid_t const tid = (os_taskid_t)msg->parameter[0];
	/* COVPT-1 */
	if (OS_IsValidTaskId(tid) && (msg->result != OS_NULL))
	{
		os_paramtype_t replyParams[OS_MAXPARAM];
		os_eventmask_t evtmask;

		replyParams[0] = (os_paramtype_t)OS_LocalGetEvent(&OS_taskTableBase[tid], &evtmask);
		replyParams[1] = msg->parameter[1];		/* points to where evtmask shall be stored to */
		replyParams[2] = (os_paramtype_t)evtmask;

#if OS_XC_REPLY_DIRECTLY
		msg->parameter[0] = replyParams[0];
		msg->parameter[1] = replyParams[1];
		msg->parameter[2] = replyParams[2];
		OS_RetnEvent(msg);
#else
		OS_SendMessage(msg->from, OS_XC_OP_ReturnEvent, msg->result, replyParams);
#endif
	}
	else
	{
		(void)OS_PANIC(OS_PANIC_CrosscoreCommunicationError);
	}
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_recvgetevent_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
