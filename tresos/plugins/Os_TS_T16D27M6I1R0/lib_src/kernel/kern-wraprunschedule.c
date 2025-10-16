/* kern-wraprunschedule.c
 *
 * This file contains the OS_WrapRunSchedule wrapper function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_WrapRunSchedule
 *
 * This function calls the kernel OS_RunSchedule function with
 * a schedule table id as specified in the schedule part of the alarm
 * parameter union.
 *
 * !LINKSTO Kernel.Autosar.ScheduleTable.Hardware, 2
 * !LINKSTO Kernel.Autosar.ScheduleTable.Software, 2
 *
 * Each schedule table has its own alarm that is attached to a counter:
 * !LINKSTO Kernel.Autosar.ScheduleTable.Multiple, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_WrapRunSchedule(const os_alarm_t *a)
OS_TOOL_FUNCTION_ATTRIB_POST
{
#if OS_KERNEL_TYPE!=OS_MICROKERNEL
	os_uint8_t save;
	os_kerneldata_t * const kernel_data = OS_GetKernelData();

	save = kernel_data->inFunction;
	kernel_data->inFunction = OS_ININTERNAL;
#endif

	OS_RunSchedule((os_scheduleid_t)a->object);

#if OS_KERNEL_TYPE!=OS_MICROKERNEL
	kernel_data->inFunction = save;
#endif
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
