/* Mk_u_libscheduleifnecessary.c
 *
 * This file contains the MK_ScheduleIfNecessary() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_autosar.h>
#include <public/Mk_public_api.h>

/* MK_ScheduleIfNecessary()
 *
 * This function calls Schedule() in case a rescheduling is anticipated as indicated by MK_IsScheduleNecessary().
 *
 * !LINKSTO      Microkernel.Function.ScheduleIfNecessary, 2
 * !doctype      src
*/
StatusType MK_ScheduleIfNecessary(void)
{
	StatusType errorCode = E_OS_NOFUNC;

	if ( MK_IsScheduleNecessary() )
	{
		errorCode = Schedule();
	}
	else
	{
		errorCode = E_OK;
	}


	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
