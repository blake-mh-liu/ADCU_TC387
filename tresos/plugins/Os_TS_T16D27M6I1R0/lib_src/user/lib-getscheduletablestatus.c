/* lib-getscheduletablestatus.c
 *
 * This file contains the OS_GetScheduleTableStatus function.
 * The internal OS schedule table status is translated into the equivalent
 * AUTOSAR state and stored where indicated.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 12.3 (required)
 * The comma operator shall not be used.
 *
 * Reason:
 * For function-call kernels, OS API is wrapped in macros. The macro wrappers
 * need to use the comma operator to form an expression evaluating to the
 * correct result.
 *
 *
 * MISRAC2012-2) Deviated Rule: 13.3 (advisory)
 * The increment (++) and decrement (--) operators should not be mixed with
 * other operators in an expression.
 *
 * Reason:
 * For function-call kernels, OS API is wrapped in macros. The macro wrappers
 * need to handle an "in kernel" flag so that the increment operator has to be
 * used in combination with the comma operator.
*/

#include <Os_api.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_tool.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetScheduleTableStatus implements the API GetScheduleTableStatus
 *
 * The system call OS_UserGetScheduleTableStatus() is called. This places
 * the state of the specified schedule table into the caller-specified location,
 * or returns an error code. If all is OK this routine translates the return
 * value into the more limited Autosar form. In any case, the return
 * value from OS_UserGetScheduleTableStatus() is returned.
 *
 * !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus, 2
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
StatusType OS_GetScheduleTableStatus
(	ScheduleTableType s,
	ScheduleTableStatusRefType sr
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	StatusType r;
	ScheduleTableStatusType status;
	ScheduleTableStatusType state;

	/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
	r = OS_UserGetScheduleTableStatus(s, sr);

	if ( r == OS_E_OK )
	{
		status = *sr;
		state = (ScheduleTableStatusType) (status & OS_ST_STATE);

		if ( state == OS_ST_RUNNING )
		{
			if (  (status & OS_ST_SYNCHRONOUS) == 0u )
			{
				/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Asynchronous, 1
				*/
				*sr = SCHEDULETABLE_RUNNING;
			}
			else
			{
				/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Synchronous, 1
				*/
				*sr = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
			}
		}
		else
		if ( state == OS_ST_WAITING )
		{
			/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Waiting, 2
			*/
			*sr = SCHEDULETABLE_WAITING;
		}
		else
		if ( state == OS_ST_CHAINED )
		{
			/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.Next, 1
			*/
			*sr = SCHEDULETABLE_NEXT;
		}
		else
		{
			/* !LINKSTO Kernel.Autosar.API.SystemServices.GetScheduleTableStatus.NotStarted, 2
			*/
			*sr = SCHEDULETABLE_STOPPED;
		}
	}

	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
const os_uint8_t OS_dummy_lib_getscheduletablestatus_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
