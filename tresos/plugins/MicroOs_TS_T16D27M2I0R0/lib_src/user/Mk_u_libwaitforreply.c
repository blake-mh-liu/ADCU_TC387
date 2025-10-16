/* Mk_u_libwaitforreply.c
 *
 * This file contains the MK_WaitForReply() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_autosar.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>

#if MK_MAXCORES <= 1
#error "MK_WaitForReply() is not needed for single-core support."
#endif

/* MK_WaitForReply() - wait (if necessary) until a reply is received
 *
 * !LINKSTO      Microkernel.Function.MK_WaitForReply, 1
 * !doctype      src
*/
StatusType MK_WaitForReply(mk_parametertype_t statusFromSyscall)
{
	mk_parametertype_t result = statusFromSyscall;

	if ( result == (mk_parametertype_t)MK_E_WAITFORREPLY )
	{
		/* Deviation MISRAC2012-1 <+1> */
		mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
		mk_thread_t *currThread = coreVars->currentThread;
		volatile mk_parametertype_t *sc = (volatile mk_parametertype_t *)&currThread->xcoreReply.statusCode;

		do
		{
			/* Wait until the reply arrives.
			*/
			result = *sc;
		} while ( result == (mk_parametertype_t)MK_E_WAITFORREPLY );
	}

	return (StatusType)result;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
