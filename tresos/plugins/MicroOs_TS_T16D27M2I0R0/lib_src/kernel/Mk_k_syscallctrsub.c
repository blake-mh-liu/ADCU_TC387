/* Mk_k_syscallctrsub.c
 *
 * This file contains the MK_SysCallCtrSub() function.
 *
 * This system call provides the possibility to run a counter subsystem function in its own thread.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_ctrsubindex.h>
#include <private/Mk_core.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_message.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_syscall.h>

/* MK_SysCallCtrSub() starts a thread to run the given counter subsystem function with up to three parameters.
 *
 * !LINKSTO Microkernel.Function.MK_SysCallCtrSub, 1
 * !doctype src
*/
void MK_SysCallCtrSub(mk_kernelcontrol_t *coreVars)
{
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t functionIndex = MK_ELIMINATE_UNDEFINED_BITS(mk_objectid_t, MK_HwGetParameter1(caller->regs));
	mk_serviceid_t sid = MK_sid_CallCtrSub;
	mk_errorid_t errorCode = MK_eid_Unknown;

	if (caller == coreVars->aux1Thread)
	{
		errorCode = MK_eid_CtrSubCallFromWrongContext;
	}
	else
	if ( functionIndex >= MK_N_CTRSUBCALLS )
	{
		errorCode = MK_eid_InvalidCtrSubFunction;
	}
	else
	{
		sid = MK_ctrsubService[functionIndex].sid;		/* For error reporting.	*/

		errorCode = MK_InternCallCtrSub(coreVars, (mk_objectid_t)functionIndex, MK_xcore_CallCtrSub);
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
