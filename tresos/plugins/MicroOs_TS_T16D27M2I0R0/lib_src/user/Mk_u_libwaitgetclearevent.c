/* Mk_u_libwaitgetclearevent.c
 *
 * This file contains the MK_WaitGetClearEvent function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>

/* MK_WaitGetClearEvent() - a combined WaitEvent, GetEvent and ClearEvent API
 *
 * !LINKSTO      Microkernel.Function.WaitGetClearEvent, 2
 * !doctype      src
*/
StatusType MK_WaitGetClearEvent(mk_uint32_t events, mk_uint32_t *eventRef)
{
	mk_statusandvalue_t syscallReturn = MK_UsrWaitGetClearEvent(events);

	if ( syscallReturn.statusCode == E_OK )
	{
		*eventRef = (mk_uint32_t)syscallReturn.requestedValue;
	}

	return (StatusType)(syscallReturn.statusCode);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
