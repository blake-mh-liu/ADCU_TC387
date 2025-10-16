/* kern-multistartscheduletable.c
 *
 * This file contains the OS_MultiStartScheduleTable function.
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
 * OS_MultiStartScheduleTable is used to implement StartScheduleTable on multi-core systems.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_MultiStartScheduleTable(
	os_scheduleid_t s,
	const os_schedule_t *ps,
	os_counterid_t counter,
	os_tick_t offset,
	os_boolean_t rel)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_errorresult_t e;
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	if (OS_GetScheduleTableCoreId(ps) == OS_GetMyCoreId())
	{
		e = OS_LocalStartScheduleTable(ps, counter, offset, rel);
	}
	else
	{
		/* !LINKSTO Kernel.Autosar.API.SystemServices.StartScheduleTableRel.CrossCore, 1
		 * !LINKSTO Kernel.Autosar.API.SystemServices.StartScheduleTableAbs.CrossCore, 1
		*/
		e = OS_SendStartScheduleTable(s, ps, offset, rel);
	}

	return e;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_multistartscheduletable_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
