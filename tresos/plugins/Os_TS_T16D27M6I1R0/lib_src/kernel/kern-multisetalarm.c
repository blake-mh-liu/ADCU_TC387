/* kern-multisetalarm.c
 *
 * This file contains the OS_MultiSetAlarm function.
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
 * OS_MultiSetAlarm is used to implement SetAlarm on multi-core systems.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_MultiSetAlarm(
	os_alarmid_t a,
	const os_alarm_t *as,
	const os_counter_t *cs,
	os_tick_t val,
	os_tick_t cyc,
	os_boolean_t rel)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t e;
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	if (OS_GetAlarmCoreId(as) == OS_GetMyCoreId())
	{
		e = OS_LocalSetAlarm(a, as, cs, val, cyc, rel);
	}
	else
	{
		if (rel)
		{
			/* !LINKSTO Kernel.Autosar.Multicore.SetRelAlarm.CrossCore, 1
			*/
			e = OS_SendSetRelAlarm(a, as, val, cyc);
		}
		else
		{
			/* !LINKSTO Kernel.Autosar.Multicore.SetAbsAlarm.CrossCore, 1
			*/
			e = OS_SendSetAbsAlarm(a, as, val, cyc);
		}
	}

	return e;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_multisetalarm_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
