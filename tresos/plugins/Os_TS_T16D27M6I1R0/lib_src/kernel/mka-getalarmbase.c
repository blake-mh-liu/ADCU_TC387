/* mka-getalarmbase.c
 *
 * This file contains the GetAlarmBase function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_autosar.h>
#include <Os_api_microkernel.h>

/*
 * GetAlarmBase() places the values of the configuration parameters for the specified alarm
 * into the referenced variable.
 *
 * WARNING: this function cannot be ASIL because it calls a QM function in the OS.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
StatusType GetAlarmBase(AlarmType alarmId, AlarmBaseRefType albase)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* COVPT-1 */
	return OS_KernGetAlarmBase((os_alarmid_t) alarmId, albase);
}

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mka_getalarmbase_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
