/* Mk_u_libgetalarm.c
 *
 * This file contains the GetAlarm() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>

/* GetAlarm() - Implements the AUTOSAR service.
 *
 * This function calls the GetAlarm API of the counter subsystem via the microkernel's delegation interface.
 * If the returned status code is E_OK, the requested value is placed in the referenced TickType variable.
 * The function returns the status code.
 *
 * !LINKSTO      Microkernel.Function.CtrSubInterfaceFunctions, 1
 * !doctype      src
*/
StatusType GetAlarm(AlarmType alarmId, TickRefType tickRef)
{
	mk_statusandvalue_t syscallReturn;

	do
	{
		syscallReturn = MK_UsrCallCtrSub2V(MK_ctrsub_GetAlarm,
										   (mk_parametertype_t)alarmId,
										   (mk_parametertype_t)tickRef);
#if MK_MAXCORES > 1
		if ( syscallReturn.statusCode == (mk_parametertype_t)MK_E_WAITFORREPLY )
		{
			syscallReturn = MK_WaitForReplyAndValue();
		}
#endif
	} while ( syscallReturn.statusCode == (mk_parametertype_t)MK_E_TRYAGAIN );

	if ( syscallReturn.statusCode == E_OK )
	{
		*tickRef = (TickType)syscallReturn.requestedValue;
	}

	return (StatusType)syscallReturn.statusCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
