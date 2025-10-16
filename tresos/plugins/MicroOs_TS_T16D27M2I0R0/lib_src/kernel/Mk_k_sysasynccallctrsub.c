/* Mk_k_sysasynccallctrsub.c
 *
 * This file contains the MK_SysAsyncCallCtrSub() function.
 *
 * This system call provides the possibility to run a counter subsystem function in its own thread.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_ctrsubindex.h>
#include <private/Mk_core.h>
#include <private/Mk_ctrsub.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_syscall.h>

/* MK_SysAsyncCallCtrSub() starts a thread to run the given counter subsystem function with up to three parameters.
 *
 * !LINKSTO Microkernel.Function.MK_SysAsyncCallCtrSub, 1
 * !doctype src
*/
void MK_SysAsyncCallCtrSub(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t functionIndex = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_serviceid_t sid = MK_sid_CallCtrSub;
	mk_errorid_t errorCode = MK_eid_Unknown;

	if ( functionIndex >= MK_N_CTRSUBCALLS )
	{
		errorCode = MK_eid_InvalidCtrSubFunction;
	}
	else
	{
		sid = MK_ctrsubService[functionIndex].sid;
		if ( MK_ctrsubService[functionIndex].onlySync )
		{
			errorCode = MK_eid_SyncServiceCalledAsync;
		}
		else
		{
			errorCode = MK_InternCallCtrSub(coreVars, (mk_objectid_t)functionIndex, MK_xcore_AsyncCallCtrSub);
		}
	}

	if ( (errorCode == MK_eid_TryAgain) && (caller == coreVars->aux1Thread) )
	{
		/* Convert "try again" to "wrong context" if the caller was the counter subsystem thread.
		 * This is because trying again in this case would simply fail again.
		*/
		errorCode = MK_eid_CtrSubCallFromWrongContext;
	}

	if ( errorCode < MK_eid_FirstError )
	{
		/* Not a real error; just return the StatusType equivalent.
		*/
		osekError = MK_ErrorInternalToOsek(errorCode);
	}
	else
	{
		osekError = MK_InternReportError(coreVars, sid, errorCode, caller, MK_NULL);
	}

	MK_HwSetReturnValue1(caller->regs, osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
