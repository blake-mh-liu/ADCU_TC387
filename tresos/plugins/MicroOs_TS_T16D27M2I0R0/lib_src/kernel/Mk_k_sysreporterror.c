/* Mk_k_sysreporterror.c
 *
 * This file contains the MK_SysReportError() function.
 *
 * This function is called by the system call function whenever the ReportError system call is made.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * The system call mechanism translates parameters to fixed length type based on register size.
 * The service handler then needs to translate them back.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_VOCF]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  Parts of this function look repetitive or similar because of the necessary sanity checks
 *  and distinctions (e.g. core id) in order to report the error correctly. Splitting up
 *  these parts into separate functions would not improve maintainability,
 *  because they form a logical unit with the rest of the code.
 *
 *
 * DCG-2) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <public/Mk_error.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_message.h>

#if MK_MAXPARAMS != 4
#error "The handling of parameter lists in this file needs attention"
#endif

/* Helper function to fill parameter array from a thread's register store.
 *
 * The name suffix avoids a MISRA violation; there's an identical function in another file.
 * The function is defined locally to encourage the compiler to inline it.
*/
static void MK_LoadParams_Sys(mk_parametertype_t p[MK_MAXPARAMS], mk_thread_t *thr)
{
	p[0] = MK_HwGetParameter1(thr->regs);
	p[1] = MK_HwGetParameter2(thr->regs);
	p[2] = MK_HwGetParameter3(thr->regs);
	p[3] = MK_HwGetParameter4(thr->regs);
}

/*
 * MK_SysReportError() reports an error
 *
 * This function is present in the system call table and is called whenever a thread makes
 * a "ReportError" system call.
 *
 * The parameters to the system call are:
 *	- service ID
 *	- internal error code
 *	- parameter block
 *
 * If the caller is an OS thread, the thread is terminated and the culprit becomes the thread's
 * parent. Otherwise the culprit is the calling thread.
 *
 * Error checking:
 *	The error is reported "as is", however, mk_serviceid_t and mk_errorid_t
 *	must be able to hold the given values.
 *
 * !LINKSTO Microkernel.Function.MK_SysReportError, 2
 * !doctype src
*/
/* Deviation DCG-1, DCG-2 */
void MK_SysReportError(mk_kernelcontrol_t *coreVars)
{
	mk_thread_t *caller = coreVars->currentThread;
	mk_parametertype_t sidArg = MK_ELIMINATE_UNDEFINED_BITS(mk_serviceid_t, MK_HwGetParameter1(caller->regs));
	mk_parametertype_t eidArg = MK_ELIMINATE_UNDEFINED_BITS(mk_errorid_t, MK_HwGetParameter2(caller->regs));
	mk_serviceid_t sid = MK_sid_InvalidServiceId;
	mk_errorid_t eid = MK_eid_Unknown;
	mk_thread_t *culprit;
	mk_thread_t *parent;
	mk_objectid_t fromCore;
	mk_osekerror_t osekError = MK_E_ERROR;
	mk_hwlocklevel_t lockLevel;
	mk_parametertype_t p[MK_MAXPARAMS];

	/* If the arguments aren't valid, let this ReportError call report that it wasn't called correctly.
	*/
	if (sidArg > (mk_parametertype_t)MK_sid_Sentinel)
	{
		sid = MK_sid_ReportError;
		eid = MK_eid_InvalidServiceId;
		MK_LoadParams_Sys(p, caller);
	}
	else if (eidArg > (mk_parametertype_t)MK_eid_Sentinel)
	{
		sid = MK_sid_ReportError;
		eid = MK_eid_InvalidErrorId;
		MK_LoadParams_Sys(p, caller);
	}
	else
	{
		/* Deviation MISRAC2012-1 <+2> */
		sid = (mk_serviceid_t) sidArg;
		eid = (mk_errorid_t) eidArg;
		p[0] = MK_HwGetParameter3(caller->regs);
		p[1] = MK_HwGetParameter4(caller->regs);
		p[2] = MK_PARAMETERTYPE_INVALID;
		p[3] = MK_PARAMETERTYPE_INVALID;
	}

	if ( caller->objectType == MK_OBJTYPE_CTRSUB )
	{
		/* Determine the culprit, i.e. the thread that called the counter subsystem API.
		 *
		 * Caution: culprit may be NULL, if the thread that called the counter subsystem API was
		 * terminated while the counter subsystem API was in progress.
		 * For asynchronous calls the culprit might no longer be available.
		*/
		parent = caller->parentThread;
		fromCore = caller->parentCore;
		if ( fromCore < 0 )
		{
			/* Asynchronous call - the culprit cannot be informed of the error.
			*/
			culprit = MK_NULL;
		}
		else
		{
			culprit = parent;
		}

		/* Dequeue the counter-subsystem thread from the head of the thread queue.
		 * This is a precondition for MK_TerminateThread().
		*/
		coreVars->threadQueueHead = caller->next;
		caller->next = MK_NULL;

		/* Reporting the error is done *after* dequeueing the counter-subsystem thread because an error-hook
		 * thread might get enqueued and make the dequeueing more complicated.
		*/
		osekError = MK_InternReportError(coreVars, sid, eid, culprit, p);

		/* Terminate the counter subsystem thread
		*/
		lockLevel = MK_HwGetIntLevel(caller->regs);
		MK_HwFreeThreadRegisters(caller->regs);
		MK_TerminateThread(coreVars, caller, lockLevel);

		if ( fromCore >= 0 )
		{
			/* This is a synchronous call. Pass the OSEK error code back to the original caller.
			*/
			if ( fromCore == coreVars->coreIndex )
			{
				/* For a same-core call we pass the error code back to the parent, if the parent still exists.
				*/
				if ( parent != MK_NULL )
				{
					MK_HwSetReturnValue1(parent->regs, osekError);
				}
			}
			else
			{
				/* For an inter-core call we need to send the error code back.
				*/
#if (MK_MAXCORES > 1)
				mk_parametertype_t reply[MK_MSG_MAXPARAM];
				reply[0] = (mk_parametertype_t)MK_ErrorInternalToOsek(eid);
				reply[1] = 0u;
				reply[2] = 0u;
				reply[3] = 0u;
				(void)MK_SendMessage(coreVars, fromCore, MK_xcore_Reply, caller->parentCookie, reply);
#else
				/* We can't send cross core messages in a single-core system.
				 * fromCore or coreIndex field must be corrupted.
				*/
				MK_Panic(MK_panic_CoreNotConfigured);
#endif
			}
		}

		/* A thread has been terminated. If there are no more threads the problem needs to be handled.
		*/
		if ( coreVars->threadQueueHead == MK_NULL )
		{
			MK_ThreadQueueEmpty();
		}
	}
	else
	{
		/* Some other thread reported an error.
		 * In this case the first 2 parameters to the service
		 * are taken from parameters 3 and 4 to the system call.
		 * Other parameters are not available.
		*/
		osekError = MK_InternReportError(coreVars, sid, eid, caller, p);
		MK_HwSetReturnValue1(caller->regs, osekError);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
