/* Mk_public_api.h
 *
 * This file declares the public API that the user may use (directly or
 * indirectly) to call the microkernel or the OS that runs under it.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_PUBLIC_API_H
#define MK_PUBLIC_API_H

#include <public/Mk_hwsel.h>
#include <public/Mk_public_types.h>
#include <public/Mk_statustype.h>
#include <public/Mk_error.h>
#include <public/Mk_usr_api.h>

#include MK_HWSEL_PUB_API

#ifndef MK_ASM
/* !LINKSTO Microkernel.Function.AcquireLock, 1
 * !doctype src
*/
#define MK_AcquireLock(l)		MK_UsrAcquireLock((l))

/* !LINKSTO Microkernel.Function.ReleaseLock, 1
 * !doctype src
*/
#define MK_ReleaseLock(l)		MK_UsrReleaseLock((l))

/* !LINKSTO Microkernel.Function.ConditionalGetResource, 3
 * !doctype src
*/
StatusType MK_ConditionalGetResource(mk_lockid_t);

/* !LINKSTO Microkernel.Function.IsScheduleNecessary, 2
 * !doctype src
*/
mk_boolean_t MK_IsScheduleNecessary(void);

/* !LINKSTO Microkernel.Function.ScheduleIfNecessary, 2
 * !doctype src
*/
StatusType MK_ScheduleIfNecessary(void);

/* !LINKSTO Microkernel.Function.Async_ActivateTask, 2
 * !doctype src
*/
#define MK_AsyncActivateTask(t)					((StatusType)MK_UsrAsyncActivateTask(t))

/* !LINKSTO Microkernel.Function.Async_SetEvent, 2
 * !doctype src
*/
#define MK_AsyncSetEvent(t, e)					((StatusType)MK_UsrAsyncSetEvent(t, e))

#define MK_TerminateSelf()						(MK_UsrTerminateSelf())
#define MK_TerminateSelfWithResult(r)			(MK_UsrTerminateSelfWithResult((r))
#define MK_TerminateSelfWithValue(r, v)			(MK_UsrTerminateSelfWithValue((r), (v))

#define MK_AddOnControl(a)						(MK_UsrAddOnControl((a)))
#define MK_AddOnControl1(a, p1)					(MK_UsrAddOnControl1((a), (p1)))
#define MK_AddOnControl2(a, p1, p2)				(MK_UsrAddOnControl2((a), (p1), (p2)))
#define MK_AddOnControl3(a, p1, p2, p3)			(MK_UsrAddOnControl3((a), (p1), (p2), (p3)))

/* !LINKSTO Microkernel.Function.AsyncCtrSubInterfaceFunctions, 1
 * !doctype src
*/
#define MK_AsyncCancelAlarm(a)					(MK_LIBASYNCCALLCTRSUB1(MK_ctrsub_CancelAlarm, a))
#define MK_AsyncIncrementCounter(c)				(MK_LIBASYNCCALLCTRSUB1(MK_ctrsub_IncrementCounter, c))
#define MK_AsyncNextScheduleTable(s1, s2)		(MK_LIBASYNCCALLCTRSUB2(MK_ctrsub_NextScheduleTable, s1, s2))
#define MK_AsyncSetAbsAlarm(a, i, c)			(MK_LIBASYNCCALLCTRSUB3(MK_ctrsub_SetAbsAlarm, a, i, c))
#define MK_AsyncSetRelAlarm(a, i, c)			(MK_LIBASYNCCALLCTRSUB3(MK_ctrsub_SetRelAlarm, a, i, c))
#define MK_AsyncSetScheduleTableAsync(s)		(MK_LIBASYNCCALLCTRSUB1(MK_ctrsub_SetScheduleTableAsync, s))
#define MK_AsyncStartScheduleTableAbs(s, t)		(MK_LIBASYNCCALLCTRSUB3(MK_ctrsub_StartScheduleTable, s, t, MK_FALSE))
#define MK_AsyncStartScheduleTableRel(s, t)		(MK_LIBASYNCCALLCTRSUB3(MK_ctrsub_StartScheduleTable, s, t, MK_TRUE))
#define MK_AsyncStartScheduleTableSynchron(s)	(MK_LIBASYNCCALLCTRSUB1(MK_ctrsub_StartScheduleTableSynchron, s))
#define MK_AsyncStopScheduleTable(s)			(MK_LIBASYNCCALLCTRSUB1(MK_ctrsub_StopScheduleTable, s))
#define MK_AsyncSyncScheduleTable(s, g1)		(MK_LIBASYNCCALLCTRSUB2(MK_ctrsub_SyncScheduleTable, s, g1))

#define MK_ReportError(sid, eid, p1, p2)		(MK_UsrReportError((sid), (eid), (p1), (p2)))

void MK_ResumeInterrupts(mk_lockid_t);
void MK_SuspendInterrupts(mk_lockid_t);

/* The microkernel's "time" API.
 *
 * If the hardware has direct support for a long-duration timer, the microkernel uses it.
 * Otherwise a short-duration timer is extended using the generic function.
 *
 * With the exception of MK_ElapsedMicroseconds and the macros that use it, all times are in units of ticks
 * of the hardware timer. For absolute time these are "ticks since counting began", which is processor-
 * dependent (usually the time of the last reset).
 *
 * These functions are all normal library functions that can be called from any thread that has read access
 * to the timer.
*/

/* !LINKSTO Microkernel.Function.ReadTime, 2
 * !doctype src
*/
#if MK_HW_HAS_TIMESTAMP
#define MK_ReadTime(t)	MK_HwReadTime(t)
#else
#define MK_ReadTime(t)	MK_GenericReadTime(t)
#endif

/* !LINKSTO Microkernel.Function.DiffTime, 2
 * !doctype src
*/
#if MK_HAS_INT64
#define MK_DiffTime(diffTime, newTime, oldTime)	(*(diffTime) = *(newTime) - *(oldTime))
#else
void MK_DiffTime(mk_time_t *, const mk_time_t *, const mk_time_t *);
#endif

/* !LINKSTO Microkernel.Function.ElapsedTime, 2
 * !doctype src
*/
void MK_ElapsedTime(mk_time_t *, mk_time_t *);

/* !LINKSTO Microkernel.Function.DiffTime32, 3
 * !doctype src
*/
mk_uint32_t MK_DiffTime32(const mk_time_t *, const mk_time_t *);

/* !LINKSTO Microkernel.Function.ElapsedTime32, 3
 * !doctype src
*/
mk_uint32_t MK_ElapsedTime32(mk_time_t *);

/* !LINKSTO Microkernel.Function.ElapsedMicroseconds, 3
 * !doctype src
*/
void MK_ElapsedMicroseconds(mk_uint32_t *, mk_uint32_t *, mk_uint16_t);

/* MK_ElapsedTime100u, -10u, -1u
 *
 * These macros provide the time that has elapsed since the last call (using the same "prev" variable) in
 * units of 100us, 10us and 1us respectively.
 *
 * In all three cases, both parameters are pointers to mk_uint32_t variables and should not point to
 * the same variable.
 *
 * !LINKSTO Microkernel.Function.ElapsedTime100u, 3
 * !LINKSTO Microkernel.Function.ElapsedTime10u, 3
 * !LINKSTO Microkernel.Function.ElapsedTime1u, 3
 * !doctype src
*/
#define MK_ElapsedTime100u(prev, elapsed)		MK_ElapsedMicroseconds(prev, elapsed, MK_timestampClockFactor100u)
#define MK_ElapsedTime10u(prev, elapsed)		MK_ElapsedMicroseconds(prev, elapsed, MK_timestampClockFactor10u)
#define MK_ElapsedTime1u(prev, elapsed)			MK_ElapsedMicroseconds(prev, elapsed, MK_timestampClockFactor1u)

/* !LINKSTO Microkernel.Function.MK_MulDiv, 2
 * !doctype src
*/
#if MK_HAS_INT64
mk_uint64_t MK_MulDiv(mk_uint64_t, mk_uint32_t, mk_uint32_t);
#else
mk_uint32_t MK_MulDiv(mk_uint32_t, mk_uint16_t, mk_uint16_t);
#endif

/* MK_WaitGetClearEvent() - a combined WaitEvent, GetEvent and ClearEvent API
 *
 * !LINKSTO Microkernel.Function.WaitGetClearEvent, 2
 * !doctype src
*/
#define MK_HAS_WAITGETCLEAREVENT	1
StatusType MK_WaitGetClearEvent(mk_uint32_t, mk_uint32_t *);

/* !LINKSTO Microkernel.Function.GetClearEvent, 2
 * !doctype src
*/
#define MK_HAS_GETCLEAREVENT		1
#define MK_GetClearEvent(ep)		MK_WaitGetClearEvent(0u, (ep))

#define MK_EnableInterruptSource(isrId)		MK_UsrEnableInterruptSource(isrId)
#define MK_DisableInterruptSource(isrId)	MK_UsrDisableInterruptSource(isrId)

/* Simple schedule table API
*/

/* !LINKSTO Microkernel.Function.MK_SstStartCounter, 1
 * !doctype src
*/
#define MK_SstStartCounter(c, d)	((StatusType)MK_UsrSstStartCounter((c), (d)))
/* !LINKSTO Microkernel.Function.MK_SstAdvanceCounter, 1
 * !doctype src
*/
#define MK_SstAdvanceCounter(c, t)	((StatusType)MK_UsrSstAdvanceCounter((c), (t)))
/* !LINKSTO Microkernel.Function.MK_SstStopCounter, 1
 * !doctype src
*/
#define MK_SstStopCounter(c)		((StatusType)MK_UsrSstStopCounter(c))

/* API to the the app mode of a given core.
*/
#define MK_GetAppModeVoteOfCore(c)	((mk_appmodeid_t)MK_UsrGetAppModeVoteOfCore(c))

/* Used to initialize sync spots before MK_Entry2 is entered.
*/
void MK_InitSyncHere(void);

#if MK_MAXCORES > 1
/* API to map core ids.
*/
mk_objectid_t MK_GetPhysicalCoreId(mk_objectid_t);
mk_objectid_t MK_GetLogicalCoreId(mk_objectid_t);
#else

/* !LINKSTO      Microkernel.Function.MK_GetPhysicalCoreId, 2
 * !doctype      src
*/
#define MK_GetPhysicalCoreId(logCoreId)		(logCoreId)

/* !LINKSTO      Microkernel.Function.MK_GetLogicalCoreId, 2
 * !doctype      src
*/
#define MK_GetLogicalCoreId(phyCoreId)		(phyCoreId)

#endif /* MK_MAXCORES > 1 */

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
