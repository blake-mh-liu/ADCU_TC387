/* kern-retnapplicationstate.c
 *
 * This file contains the function OS_RetnApplicationState().
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
 * OS_RetnApplicationState
 *
 * This function is used to return the result of GetApplicationState() to its original caller.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_RetnApplicationState(os_message_t * msg)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t const e = (os_errorresult_t)msg->parameter[0];

	/* COVPT-1 */
	if ( e == OS_ERRORCODE_NOCHECK(OS_ERROR_NoError) )
	{
		os_appstate_t * const pstate = (os_appstate_t *)msg->parameter[1];
		*pstate = (os_appstate_t)msg->parameter[2];

#if OS_XC_REPLY_DIRECTLY
		OS_CacheFlush(pstate, sizeof(*pstate));
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
const os_uint8_t OS_dummy_kern_retnapplicationstate_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
