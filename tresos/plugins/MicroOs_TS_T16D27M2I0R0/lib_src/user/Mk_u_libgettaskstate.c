/* Mk_u_libgettaskstate.c
 *
 * This file contains the GetTaskState() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * The system call mechanism translates the return value to fixed length type based on register size.
 * The calling API then needs to translate it back.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>

/* GetTaskState() - Implements the AUTOSAR service.
 *
 * This function calls the MK_UsrGetTaskState API of the microkernel.
 * If the returned status code is E_OK, the requested value is placed in the referenced TaskStateType variable
 * The function returns the status code.
 *
 * !LINKSTO      Microkernel.Function.GetTaskState, 2
 * !doctype      src
*/
StatusType GetTaskState(TaskType taskId, TaskStateRefType taskStateRef)
{
	mk_statusandvalue_t syscallReturn = MK_UsrGetTaskState(taskId, (mk_parametertype_t)taskStateRef);

#if MK_MAXCORES > 1
	if ( syscallReturn.statusCode == (mk_parametertype_t)MK_E_WAITFORREPLY )
	{
		syscallReturn = MK_WaitForReplyAndValue();
	}
#endif

	if ( syscallReturn.statusCode == E_OK )
	{
		/* Deviation MISRAC2012-1 <+1> */
		*taskStateRef = (TaskStateType)syscallReturn.requestedValue;
	}

	return (StatusType)syscallReturn.statusCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
