/* Mk_u_libgetcountervalue.c
 *
 * This file contains the GetCounterValue() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>

/* GetCounterValue() - Implements the AUTOSAR service.
 *
 * This function calls the GetCounterValue API of the counter subsystem via the microkernel's delegation interface.
 * If the returned status code is E_OK, the requested value is placed in the referenced TickType variable.
 * The function returns the status code.
 *
 * !LINKSTO      Microkernel.Function.CtrSubInterfaceFunctions, 1
 * !doctype      src
*/
StatusType GetCounterValue(CounterType counterId, TickRefType tickRef)
{
	mk_statusandvalue_t syscallReturn;

	do
	{
		syscallReturn = MK_UsrCallCtrSub2V(MK_ctrsub_GetCounterValue, (mk_parametertype_t)counterId,
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
