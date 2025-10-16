/* Mk_usr_api.h
 *
 * This file declares the internal API that the user should not use directly,
 * but which needs to be "public" because it is used in macros in the public API.
 *
 *
 * NOTICE
 * The functions etc. declared in this file must not be used directly. Their functionality
 * may not be as expected, and is subject to change without notice.
 * Use the documented API in Mk_public_api.h!
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_USR_API_H
#define MK_USR_API_H

#include <public/Mk_public_types.h>
#include <public/Mk_statustype.h>
#include <public/Mk_error.h>
#ifndef MK_ASM
/* This function is called directly by the startup code in order to set the
 * microkernel running.
*/
void MK_StartKernel(mk_uint32_t, mk_uint32_t, mk_uint32_t, mk_uint32_t);

/* MK_UsrXxx - low-level ABI translation
 *
 * These functions translate the C calling convention to the microkernel's system-call ABI.

 * !LINKSTO Microkernel.Function.UsrInterfaceFunctions, 2
 * !doctype src
*/
mk_parametertype_t MK_UsrTerminateSelf(void);
void MK_UsrTerminateSelfWithResult(mk_parametertype_t);
void MK_UsrTerminateSelfWithValue(mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t MK_UsrActivateTask(mk_objectid_t);
mk_parametertype_t MK_UsrChainTask(mk_objectid_t);
mk_parametertype_t MK_UsrDisableInterruptSource(mk_objectid_t);
mk_parametertype_t MK_UsrEnableInterruptSource(mk_objectid_t);
mk_parametertype_t MK_UsrSchedule(void);
mk_parametertype_t MK_UsrAcquireLock(mk_lockid_t);
mk_parametertype_t MK_UsrReleaseLock(mk_lockid_t);
mk_parametertype_t MK_UsrShutdown(mk_uint8_t);
mk_parametertype_t MK_UsrStartOs(mk_objectid_t);
mk_parametertype_t MK_UsrSetEvent(mk_objectid_t, mk_uint32_t);
mk_parametertype_t MK_UsrClearEvent(mk_uint32_t);
mk_parametertype_t MK_UsrWaitEvent(mk_uint32_t);
mk_statusandvalue_t MK_UsrWaitGetClearEvent(mk_uint32_t);
mk_statusandvalue_t MK_UsrGetTaskId(mk_parametertype_t);
mk_statusandvalue_t MK_UsrGetTaskState(mk_objectid_t, mk_parametertype_t);
mk_parametertype_t MK_UsrGetIsrId(void);
mk_parametertype_t MK_UsrCallTrustedFunction(mk_objectid_t, mk_parametertype_t);
mk_parametertype_t MK_UsrReportError(mk_serviceid_t, mk_errorid_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t MK_UsrTerminateApplication(mk_objectid_t, mk_boolean_t);
mk_parametertype_t MK_UsrAllowAccess(void);

mk_statusandvalue_t MK_UsrAddOnControl(mk_objectid_t);
mk_statusandvalue_t MK_UsrAddOnControl1(mk_objectid_t, mk_parametertype_t);
mk_statusandvalue_t MK_UsrAddOnControl2(mk_objectid_t, mk_parametertype_t, mk_parametertype_t);
mk_statusandvalue_t MK_UsrAddOnControl3(mk_objectid_t, mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

mk_parametertype_t MK_UsrStartCore(mk_objectid_t);
mk_parametertype_t MK_UsrShutdownAllCores(mk_uint8_t);

/* For MK_UsrCallCtrSub(), we need to have four prototypes, depending on how
 * many parameters and return value there are. This avoids warnings from the compiler.
 *
 * There are the normal (synchronous) versions and the asynchronous versions available.
 * Note that the "2V" variant has no asynchronous version; this is because returning information
 * is an inherently synchronous operation.
*/
mk_parametertype_t MK_UsrCallCtrSub1(mk_objectid_t, mk_parametertype_t);
mk_parametertype_t MK_UsrCallCtrSub2(mk_objectid_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t MK_UsrCallCtrSub3(mk_objectid_t, mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_statusandvalue_t MK_UsrCallCtrSub2V(mk_objectid_t, mk_parametertype_t, mk_parametertype_t);

mk_parametertype_t MK_UsrAsyncCallCtrSub1(mk_objectid_t, mk_parametertype_t);
mk_parametertype_t MK_UsrAsyncCallCtrSub2(mk_objectid_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t MK_UsrAsyncCallCtrSub3(mk_objectid_t, mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

/* For counter subsystem calls we need a wrapper that implements the "try again" loop.
 *
 * !LINKSTO Microkernel.Function.CallCtrSub1, 1
 * !LINKSTO Microkernel.Function.CallCtrSub2, 1
 * !LINKSTO Microkernel.Function.CallCtrSub3, 1
 * !LINKSTO Microkernel.Function.AsyncCallCtrSub1, 1
 * !LINKSTO Microkernel.Function.AsyncCallCtrSub2, 1
 * !LINKSTO Microkernel.Function.AsyncCallCtrSub3, 1
 * !doctype src
*/
StatusType MK_LibCallCtrSub1(mk_objectid_t, mk_parametertype_t);
StatusType MK_LibCallCtrSub2(mk_objectid_t, mk_parametertype_t, mk_parametertype_t);
StatusType MK_LibCallCtrSub3(mk_objectid_t, mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
StatusType MK_LibAsyncCallCtrSub1(mk_objectid_t, mk_parametertype_t);
StatusType MK_LibAsyncCallCtrSub2(mk_objectid_t, mk_parametertype_t, mk_parametertype_t);
StatusType MK_LibAsyncCallCtrSub3(mk_objectid_t, mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

/* Provide macro shim to explicitly cast parameters for CtrSub interface.
*/
#define MK_LIBCALLCTRSUB1(id, p1)			MK_LibCallCtrSub1((id), (mk_parametertype_t) (p1))
#define MK_LIBCALLCTRSUB2(id, p1, p2)		MK_LibCallCtrSub2((id),					\
														(mk_parametertype_t) (p1),	\
														(mk_parametertype_t) (p2))
#define MK_LIBCALLCTRSUB3(id, p1, p2, p3)	MK_LibCallCtrSub3((id),					\
														(mk_parametertype_t) (p1),	\
														(mk_parametertype_t) (p2),	\
														(mk_parametertype_t) (p3))

#define MK_LIBASYNCCALLCTRSUB1(id, p1)			MK_LibAsyncCallCtrSub1((id), (mk_parametertype_t) (p1))
#define MK_LIBASYNCCALLCTRSUB2(id, p1, p2)		MK_LibAsyncCallCtrSub2((id),						\
																		(mk_parametertype_t) (p1),	\
																		(mk_parametertype_t) (p2))
#define MK_LIBASYNCCALLCTRSUB3(id, p1, p2, p3)	MK_LibAsyncCallCtrSub3((id),						\
																		(mk_parametertype_t) (p1),	\
																		(mk_parametertype_t) (p2),	\
																		(mk_parametertype_t) (p3))

/* Asynchronous versions of API.
*/
mk_parametertype_t MK_UsrAsyncActivateTask(mk_objectid_t);
mk_parametertype_t MK_UsrAsyncSetEvent(mk_objectid_t, mk_uint32_t);

#if (MK_MAXCORES > 1)

/* Wait for inter-core reply (synchronous API calls only)
*/
#define MK_WAITFORREPLY(s)	MK_WaitForReply((s))
StatusType MK_WaitForReply(mk_parametertype_t);
mk_statusandvalue_t MK_WaitForReplyAndValue(void);

#else

/* No inter-core calls, so no need to wait.
*/
#define MK_WAITFORREPLY(s)	((StatusType)(s))

#endif

void MK_SuspendCallout(mk_lockid_t);
void MK_ResumeCallout(mk_lockid_t);

/* These two constants contain the index of the locks that block Cat2 ISRs and Cat1 ISRs, respectively.
*/
extern const mk_lockid_t MK_resLockCat2;
extern const mk_lockid_t MK_resLockCat1;

/* !LINKSTO Microkernel.Function.CtrSubHelpers, 1
 * !doctype src
*/
mk_objquantity_t MK_LibGetNTasks(void);

#if MK_HW_HAS_TIMESTAMP
void MK_HwReadTime(mk_time_t *);
#else
void MK_GenericReadTime(mk_time_t *);
#endif

/* MK_timestampClockFactor100u, -10u, -1u
 *
 * These constants contain the number of ticks that occur in 100, 10 and 1 microseconds for the
 * hardware timer that is used for the time stamp (MK_HwReadTime).
 *
 * That means they contain the frequency of the hardware clock, in MHz, multiplied by 100, 10 and 1
 *
 * The values must be no greater than 65535
*/
extern const mk_uint16_t MK_timestampClockFactor100u;
extern const mk_uint16_t MK_timestampClockFactor10u;
extern const mk_uint16_t MK_timestampClockFactor1u;

/* MK_GetAppStateForCtrSub() - Gets the state of the given application.
 *
 * This function gets the state of the given application.
 * If an invalid application ID is passed,
 * this function will return APPLICATION_TERMINATED.
 * If MK_APPL_NONE is passed, this function will return APPLICATION_ACCESSIBLE.
 *
 * !LINKSTO Microkernel.Function.CtrSubHelpers, 1
 * !doctype src
*/
mk_appstate_t MK_GetAppStateForCtrSub(mk_objectid_t);

/* Simple schedule table API
*/
mk_parametertype_t MK_UsrSstStartCounter(mk_objectid_t, mk_parametertype_t);
mk_parametertype_t MK_UsrSstAdvanceCounter(mk_objectid_t, mk_parametertype_t);
mk_parametertype_t MK_UsrSstStopCounter(mk_objectid_t);


#if (MK_MAXCORES > 1)
/* MK_LibGetXXXXCoreId
 *
 * Get the core ID of an OS object. For use in the counter subsystem.
 * If an invalid object ID is passed, the result is MK_OBJECTID_INVALID.
 *
 * !LINKSTO Microkernel.Function.CtrSubHelpers, 1
 * !doctype src
*/
mk_objectid_t MK_LibGetTaskCoreId(mk_objectid_t);
mk_objectid_t MK_LibGetAlarmCoreId(mk_objectid_t);
mk_objectid_t MK_LibGetCounterCoreId(mk_objectid_t);
mk_objectid_t MK_LibGetScheduleTableCoreId(mk_objectid_t);

#endif /* if (MK_MAXCORES > 1) */

/* MK_LibGetAppModeVoteOfCore
 *
 * Get the OsAppMode, for which the given core votes.
 * This might be MK_UNINITIALIZED_APPMODE, if the given core hasn't yet
 * suggested an application mode.
 * If the given core index is invalid, this function will also return MK_UNINITIALIZED_APPMODE.
 *
 * !LINKSTO Microkernel.Function.CtrSubHelpers, 1
 * !doctype src
*/
mk_parametertype_t MK_UsrGetAppModeVoteOfCore(mk_objectid_t);
mk_appmodeid_t MK_LibGetAppModeVoteOfCore(mk_objectid_t);

/* MK_LibIsCoreInUse
 *
 * Tells whether the given core is under control of this microkernel.
 * If an invalid core index is passed, this function returns MK_FALSE.
 *
 * !LINKSTO Microkernel.Function.CtrSubHelpers, 1
 * !doctype src
*/
mk_boolean_t MK_LibIsCoreInUse(mk_objectid_t);

#endif /* ifndef MK_ASM */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
