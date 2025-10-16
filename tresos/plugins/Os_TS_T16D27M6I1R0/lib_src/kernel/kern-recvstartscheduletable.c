/* kern-recvstartscheduletable.c
 *
 * This file contains the function OS_RecvStartScheduleTable().
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

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>
#include <Os_panic.h>

/*!
 * OS_RecvStartScheduleTable()
 *
 * Handles cross-core StartScheduleTable() calls.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvStartScheduleTable(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_scheduleid_t const s = (os_scheduleid_t)msg->parameter[0];
	/* COVPT-1 */
	if (OS_IsValidScheduleId(s) && (msg->result != OS_NULL))
	{
		os_paramtype_t replyParams[OS_MAXPARAM];
		os_tick_t const offset			= (os_tick_t)msg->parameter[1];
		/* Deviation MISRAC2012-1 <+1> */
		os_boolean_t const rel			= (os_boolean_t)msg->parameter[2];
		os_schedule_t const * const ss	= &OS_scheduleTableBase[s];
		os_alarm_t const * const as		= &OS_alarmTableBase[ss->alarm];

		replyParams[0] = (os_paramtype_t)OS_LocalStartScheduleTable(ss, as->counter, offset, rel);

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
const os_uint8_t OS_dummy_kern_recvstartscheduletable_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
