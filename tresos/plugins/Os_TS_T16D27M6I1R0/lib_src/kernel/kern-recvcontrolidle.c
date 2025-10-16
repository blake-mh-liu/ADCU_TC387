/* kern-recvcontrolidle.c
 *
 * This file contains the function OS_RecvControlIdle().
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2004 Deviation List
 *
 * MISRA-1) Deviated Rule: 16.7 (advisory)
 * A pointer parameter in a function prototype should be declared as pointer to const if the
 * pointer is not used to modify the addressed object.
 *
 * Reason:
 * This function must have the same signature as all other OS_Recv* functions, 
 * some of which modify the referenced variable."
 */

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/
#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_panic.h>
#include <Os_messagequeue.h>

/*!
 * OS_RecvControlIdle()
 *
 * Handles cross-core ControlIdle() calls.
 */
/* Deviation MISRA-1 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RecvControlIdle(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_coreid_t const c = (os_coreid_t)msg->parameter[0];
	/* COVPT-1 +2 */
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	if ((c == OS_GetMyCoreId()) && (msg->result != OS_NULL))
	{
		os_paramtype_t replyParams[OS_MAXPARAM];

		replyParams[0] = (os_paramtype_t)OS_DoControlIdle((os_idlemode_t)msg->parameter[1]);

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
const os_uint8_t OS_dummy_kern_recvcontrolidle_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
