/* kern-multigetalarm.c
 *
 * This file contains the OS_MultiGetAlarm function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
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

#include <Os_messagequeue.h>


#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_MultiGetAlarm is used to implement GetAlarm on multi-core systems.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_MultiGetAlarm(os_alarmid_t a, const os_alarm_t *as, os_tick_t *out)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t e;
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	if (OS_GetAlarmCoreId(as) == OS_GetMyCoreId())
	{
		e = OS_LocalGetAlarm(a, as, out);
	}
	else
	{
		/* !LINKSTO Kernel.Autosar.Multicore.GetAlarm.CrossCore, 1
		*/
		e = OS_SendGetAlarm(a, as, out);
	}

	return e;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_multigetalarm_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
