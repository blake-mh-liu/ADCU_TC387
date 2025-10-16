/* kern-retnscheduletablestatus.c
 *
 * This file contains the function OS_RetnScheduleTableStatus().
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
 * OS_RetnScheduleTableStatus
 *
 * This function returns the result of a cross-core GetScheduleTableStatus() call to its original caller.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RetnScheduleTableStatus(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Place expected answer in msg->parameter[2] in the desired location msg->parameter[1],
	 * if error code in msg->parameter[0] indicates no error.
	*/
	os_errorresult_t const e = (os_errorresult_t)msg->parameter[0];
	/* COVPT-1 */
	if (e == OS_ERRORCODE_NOCHECK(OS_ERROR_NoError))
	{
		os_schedulestatus_t * const pstatus = (os_schedulestatus_t *)msg->parameter[1];
		*pstatus = (os_schedulestatus_t)msg->parameter[2];

#if OS_XC_REPLY_DIRECTLY
		OS_CacheFlush(pstatus, sizeof(*pstatus));
#endif
	}

	*(msg->result) = (os_paramtype_t)e;

#if OS_XC_REPLY_DIRECTLY
	OS_CacheFlush(msg->result, sizeof(os_paramtype_t));
#endif
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_retnscheduletablestatus_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
