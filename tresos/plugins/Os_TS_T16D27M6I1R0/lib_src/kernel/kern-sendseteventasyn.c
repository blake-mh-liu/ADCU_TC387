/* kern-sendseteventasyn.c
 *
 * This file contains the OS_SendSetEventAsyn() function.
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
 * OS_SendSetEventAsyn()
 *
 * Sends a request to set an event to its respective core.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_SendSetEventAsyn(os_taskid_t tid, const os_task_t *tp, os_eventmask_t eventmask)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_paramtype_t msgParam[OS_MAXPARAM];
	os_errorresult_t e = OS_E_OK;
	msgParam[0] = (os_paramtype_t)tid;
	msgParam[1] = (os_paramtype_t)eventmask;

	/* !LINKSTO Kernel.Autosar.Multicore.SetEventAsyn.Asynchronous, 1
	*/
	OS_SendMessage(OS_GetTaskCoreId(tp), OS_XC_OP_SetEventAsyn, (os_paramtype_t *)OS_NULL, msgParam);
	return e;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sendseteventasyn_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
