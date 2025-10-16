/* Mk_k_sysstartcore.c
 *
 * This file contains the MK_SysStartCore() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_error.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_message.h>

#if MK_MAXCORES <= 1
#error "This file is not needed for single-core systems."
#endif

/*
 * MK_SysStartCore() handles StartCore API
 *
 * This function is the kernel-side part of the "StartCore()" API.
 *
 * !LINKSTO Microkernel.Function.MK_SysStartCore, 1
 * !doctype src
*/
void MK_SysStartCore(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t coreToStart = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_parametertype_t p[MK_MSG_MAXPARAM];
	mk_errorid_t errorCode = MK_eid_Unknown;

	if ( coreToStart < (mk_parametertype_t) MK_MAXCORES )
	{
		if ( coreToStart == (mk_parametertype_t) coreVars->coreIndex )
		{
			errorCode = MK_eid_CoreIsAlreadyStarted;       /* Core ID == self */
		}
		else
		if ( MK_coreTable[coreToStart] == MK_NULL )
		{
			errorCode = MK_eid_CoreIsNotConfigured;       /* Core ID specifies a non-Autosar core */
		}
		else
		{
			p[0] = 0;
			p[1] = 0;
			p[2] = 0;
			p[3] = 0;

			errorCode = MK_SendMessage(coreVars, coreToStart,
			                           MK_xcore_StartCore, MK_NULLCOOKIE, p);

			if ( errorCode == MK_eid_NoError )
			{
				/* Set up the mechanism for waiting for and receiving the reply.
				*/
				caller->xcoreReply.statusCode = MK_E_WAITFORREPLY;
				caller->xcoreReply.requestedValue = MK_WAITCOOKIE(coreVars->cookieGen, coreToStart);
				errorCode = MK_eid_WaitForReply;
			}
		}
	}
	else
	{
		errorCode = MK_eid_CoreIdOutOfRange;		/* Core ID out of range */
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not an error; just set the return value.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, MK_sid_StartCore, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
