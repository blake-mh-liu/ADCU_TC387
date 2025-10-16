/* kern-sendcontrolidle.c
 *
 * This file contains the OS_SendControlIdle() function.
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
 * OS_SendControlIdle()
 *
 * Sends a request to set the idle mode to its respective core.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_SendControlIdle(os_coreid_t c, os_idlemode_t mode)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_paramtype_t msgParam[OS_MAXPARAM];

	msgParam[0] = (os_paramtype_t)c;
	msgParam[1] = (os_paramtype_t)mode;

	return OS_SendMessageWait(c, OS_XC_OP_ControlIdle, msgParam);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sendcontrolidle_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
