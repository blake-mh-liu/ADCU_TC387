/* Mk_u_libcallctrsub1.c
 *
 * This file contains the MK_LibCallCtrSub1() function.
 *
 * This function is called from a thread to call a counter subsystem function synchronously.
 * The return value of MK_E_TRYAGAIN is handled by this function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>

/* MK_LibCallCtrSub1() - Implements synchronous counter subsystem calls with one parameter.
 *
 * !LINKSTO      Microkernel.Function.CallCtrSub1, 1
 * !doctype      src
*/
StatusType MK_LibCallCtrSub1(mk_objectid_t ctrsubId, mk_parametertype_t p1)
{
	StatusType returnValue;

	do
	{
		returnValue = MK_WAITFORREPLY(MK_UsrCallCtrSub1(ctrsubId, p1));

	} while ( returnValue == (StatusType)MK_E_TRYAGAIN );

	return returnValue;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
