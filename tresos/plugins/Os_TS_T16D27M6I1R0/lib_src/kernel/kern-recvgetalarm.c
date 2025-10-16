/* kern-recvgetalarm.c
 *
 * This file contains the function OS_RecvGetAlarm().
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
 * OS_RecvGetAlarm()
 *
 * Handles cross-core GetAlarm() calls.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvGetAlarm(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_alarmid_t const aid = (os_alarmid_t)msg->parameter[0];
	/* COVPT-1 */
	if (OS_IsValidAlarmId(aid) && (msg->result != OS_NULL))
	{
		os_paramtype_t replyParams[OS_MAXPARAM];
		os_tick_t ticks;

		replyParams[0] = (os_paramtype_t)OS_LocalGetAlarm(aid, &OS_alarmTableBase[aid], &ticks);
		replyParams[1] = msg->parameter[1];
		replyParams[2] = (os_paramtype_t)ticks;

#if OS_XC_REPLY_DIRECTLY
		msg->parameter[0] = replyParams[0];
		msg->parameter[1] = replyParams[1];
		msg->parameter[2] = replyParams[2];
		OS_RetnTick(msg);
#else
		OS_SendMessage(msg->from, OS_XC_OP_ReturnTick, msg->result, replyParams);
#endif
	}
	else
	{
		(void)OS_PANIC(OS_PANIC_CrosscoreCommunicationError);
	}
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_recvgetalarm_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
