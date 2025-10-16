/* mka-getscheduletablestatus.c
 *
 * This file contains the GetScheduleTableStatus function.
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
 * GetScheduleTableStatus() places the schedule table status into the referenced variable.
 *
 * WARNING: this function cannot be ASIL because it calls a QM function in the OS.
 *
 * This function is functionally identical to the OS_GetScheduleTableStatus library function
 * used in the standalone OS, except that it calls OS_KernGetScheduleTableStatus() directly
 * instead of over a system call. This behaviour relies on the global readability of
 * OS variables.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
StatusType GetScheduleTableStatus(ScheduleTableType scheduleId, ScheduleTableStatusRefType out)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	StatusType returnValue;
	os_schedulestatus_t internalStatus;

	/* COVPT-1 */
	returnValue = OS_KernGetScheduleTableStatus((os_scheduleid_t) scheduleId, &internalStatus);

	/* COVPT-2 */
	if ( returnValue == OS_E_OK )
	{
		/* COVPT-3 */
		if ( (internalStatus & OS_ST_STATE) == OS_ST_RUNNING )
		{
			/* COVPT-4 */
			if (  (internalStatus & OS_ST_SYNCHRONOUS) == 0u )
			{
				/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Asynchronous, 1
				*/
				*out = SCHEDULETABLE_RUNNING;
			}
			else
			{
				/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Synchronous, 1
				*/
				*out = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
			}
		}
		/* COVPT-5 */
		else if ( (internalStatus & OS_ST_STATE) == OS_ST_WAITING )
		{
			/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Waiting, 2
			*/
			*out = SCHEDULETABLE_WAITING;
		}
		/* COVPT-6 */
		else if ( (internalStatus & OS_ST_STATE) == OS_ST_CHAINED )
		{
			/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Next, 1
			*/
			*out = SCHEDULETABLE_NEXT;
		}
		else
		{
			/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.NotStarted, 2
			*/
			*out = SCHEDULETABLE_STOPPED;
		}
	}

	return returnValue;
}

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mka_getscheduletablestatus_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
