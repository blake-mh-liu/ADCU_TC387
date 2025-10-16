/* Mk_u_libasynccallctrsub2.c
 *
 * This file contains the MK_LibAsyncCallCtrSub2() function.
 *
 * This function is called from a thread to call a counter subsystem function asynchronously.
 * The return value of MK_E_TRYAGAIN is handled by this function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>

/* MK_LibAsyncCallCtrSub2() - Implements asynchronous counter subsystem calls with two parameters.
 *
 * !LINKSTO      Microkernel.Function.AsyncCallCtrSub2, 1
 * !doctype      src
*/
StatusType MK_LibAsyncCallCtrSub2(mk_objectid_t ctrsubId, mk_parametertype_t p1, mk_parametertype_t p2)
{
	StatusType returnValue;

	do
	{
		returnValue = (StatusType)MK_UsrAsyncCallCtrSub2(ctrsubId, p1, p2);
	} while ( returnValue == (StatusType)MK_E_TRYAGAIN );

	return returnValue;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
