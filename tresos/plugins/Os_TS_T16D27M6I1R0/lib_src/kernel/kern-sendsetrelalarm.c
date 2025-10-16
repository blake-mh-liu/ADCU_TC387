/* kern-sendsetrelalarm.c
 *
 * This file contains the OS_SendSetRelAlarm() function.
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
 * OS_SendSetRelAlarm()
 *
 * Sends a SetRelAlarm() call to the core, on which the alarm 'a' resides.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_SendSetRelAlarm(os_alarmid_t a, const os_alarm_t *as, os_tick_t inc, os_tick_t cyc)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_paramtype_t msgParam[OS_MAXPARAM];

	msgParam[0] = (os_paramtype_t)a;
	msgParam[1] = (os_paramtype_t)inc;
	msgParam[2] = (os_paramtype_t)cyc;

	return OS_SendMessageWait(OS_GetAlarmCoreId(as), OS_XC_OP_SetRelAlarm, msgParam);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sendsetrelalarm_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
