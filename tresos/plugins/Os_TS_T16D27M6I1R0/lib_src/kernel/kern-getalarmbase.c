/* kern-getalarmbase.c
 *
 * This file contains the OS_KernGetAlarmBase function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * If there is no memory protection available, some archtictures replace OS_ArchCanWrite()
 * with the function-like macro OS_ArchMisalignedData() or even a constant.
 * As the size of the data object is known at compile-time, not all branches of the 
 * OS_ArchMisalignedData() check can be reached.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if "calling context checks" are not excluded.
 *
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if "interrupt enable checks" are not excluded.
 *
 * TOOLDIAG-3) Possible diagnostic: StatementIsUnreachable
 *   statement not reached
 *
 * Reason:
 *  This warning depends on the OS configuration and library optimization.
 *  The statement can be reached, if EXTENDED status is used.
 *
 * TOOLDIAG-4) Possible diagnostic: CastFromPtrToIntOfEqualSize
 *   Conversion from pointer to same-sized integral type
 *
 * Reason: The casted value is used for address calculations only and the code
 *   is well-aware of the type conversion in the implementation.
*/

#define OS_SID	OS_SID_GetAlarmBase
#define OS_SIF	OS_svc_GetAlarmBase

#include <Os_kernel.h>

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernGetAlarmBase
 *
 * The alarm base characterisitics for the alarm are written to the
 * indicated location.
 *
 * !LINKSTO Kernel.API.Alarms.GetAlarmBase.API, 1
 *
 * !LINKSTO Kernel.API.Alarms.GetAlarmBase.Hook, 1
 *		OS_KernGetAlarmBase() returns constant values, so the
 *		only thing that might limit the context in which it can be called
 *		might be the write permission function OS_ArchCanWrite().
 * !LINKSTO Kernel.Autosar.Multicore.GetAlarmBase.CrossCore, 1
 *		no restrictions based on the core the alarm is bound to.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_KernGetAlarmBase
(	os_alarmid_t a,
	os_alarmbase_t *out
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	
	os_result_t r = OS_E_OK;
	const os_counter_t *c;
	OS_PARAMETERACCESS_DECL
	/* Possible diagnostic TOOLDIAG-4 */
	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)a);
	OS_SAVE_PARAMETER_N(1,(os_paramtype_t)out);

	OS_TRACE_GETALARMBASE_ENTRY(a);

	if ( !OS_CallingContextCheck() )
	{
		/* Possible diagnostic TOOLDIAG-1 <+1> */
		r = OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_InterruptEnableCheck(OS_IEC_AUTOSAR) )
	{
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		r = OS_ERROR(OS_ERROR_InterruptDisabled, OS_GET_PARAMETER_VAR());
	}
	else
	/* Deviation MISRAC2012-1 <+1> */
	if ( OS_ArchCanWrite(out, sizeof(*out)) == 0 )
	{
		r = OS_ERROR(OS_ERROR_WriteProtect, OS_GET_PARAMETER_VAR());
	}
	else
	if ( ! OS_IsValidAlarmId( a ) )
	{
		/* !LINKSTO Kernel.API.Alarms.GetAlarmBase.InvalidAlarm, 1
		*/
		/* Possible diagnostic TOOLDIAG-3 <+1> */
		r = OS_ERROR(OS_ERROR_InvalidAlarmId, OS_GET_PARAMETER_VAR());
	}
	else
	if ( !OS_APPISACCESSIBLE(OS_alarmTableBase[a].app) )
	{
		r = OS_ERROR(OS_ERROR_ApplicationNotAccessible, OS_GET_PARAMETER_VAR());
	}
	else
	{
		/* !LINKSTO Kernel.API.Alarms.GetAlarmBase.Info, 1
		*/
		c = &OS_counterTableBase[OS_alarmTableBase[a].counter];
		out->maxallowedvalue = c->maxallowedvalue;
		out->ticksperbase = c->ticksperbase;
		out->mincycle = c->mincycle;
	}

	OS_TRACE_GETALARMBASE_EXIT_P(r,a);
	return r;
}


#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
