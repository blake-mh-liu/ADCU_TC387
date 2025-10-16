/* Os_api_nosyscall.h
 *
 * This file defines the OS User API as direct function calls for architectures with no system-call mechanism
 * (or where the system-call mechanism isn't used).
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_API_NOSYSCALL_H
#define OS_API_NOSYSCALL_H

#include <Os_userkernel.h>

#define OS_UserActivateTask(t)					OS_CALL(os_result_t,		OS_KernActivateTask(t))
#define OS_UserActivateTaskAsyn(t)				OS_CALL(os_result_t,		OS_KernActivateTaskAsyn(t))
#define OS_UserTerminateTask()					OS_CALL(os_result_t,		OS_KernTerminateTask())
#define OS_UserChainTask(t)						OS_CALL(os_result_t,		OS_KernChainTask(t))
#define OS_UserSchedule()						OS_CALL(os_result_t,		OS_KernSchedule())
#define OS_UserGetTaskId(tr)					OS_CALL(os_result_t,		OS_KernGetTaskId(tr))
#define OS_UserGetTaskState(t, s)				OS_CALL(os_result_t,		OS_KernGetTaskState(t, s))
#define OS_UserGetResource(r)					OS_CALL(os_result_t,		OS_KernGetResource(r))
#define OS_UserReleaseResource(r)				OS_CALL(os_result_t,		OS_KernReleaseResource(r))
#define OS_UserSetEvent(t, e)					OS_CALL(os_result_t,		OS_KernSetEvent(t, e))
#define OS_UserSetEventAsyn(t, e)				OS_CALL(os_result_t,		OS_KernSetEventAsyn(t, e))
#define OS_UserClearEvent(e)					OS_CALL(os_result_t,		OS_KernClearEvent(e))
#define OS_UserGetEvent(t, e)					OS_CALL(os_result_t,		OS_KernGetEvent(t, e))
#define OS_UserWaitEvent(e)						OS_CALL(os_result_t,		OS_KernWaitEvent(e))
#define OS_UserGetAlarmBase(a, b)				OS_CALL(os_result_t,		OS_KernGetAlarmBase(a, b))
#define OS_UserGetAlarm(a, t)					OS_CALL(os_result_t,		OS_KernGetAlarm(a, t))
#define OS_UserSetRelAlarm(a, i, c)				OS_CALL(os_result_t,		OS_KernSetRelAlarm(a, i, c))
#define OS_UserSetAbsAlarm(a, i, c)				OS_CALL(os_result_t,		OS_KernSetAbsAlarm(a, i, c))
#define OS_UserCancelAlarm(a)					OS_CALL(os_result_t,		OS_KernCancelAlarm(a))
#define OS_UserGetActiveApplicationMode()		OS_CALL(os_appmodeid_t,		OS_KernGetActiveApplicationMode())
#define OS_UserGetApplicationState(a, out)		OS_CALL(os_result_t,		OS_KernGetApplicationState(a, out))
#define OS_UserIncrementCounter(c)				OS_CALL(os_result_t,		OS_KernIncrementCounter(c))
#define OS_UserGetStackInfo(t, s)				OS_CALL(os_result_t,		OS_KernGetStackInfo(t, s))
#define OS_UserStartScheduleTable(s, t, r)		OS_CALL(os_result_t,		OS_KernStartScheduleTable(s, t, r))
#define OS_UserStartScheduleTableSynchron(s)	OS_CALL(os_result_t,		OS_KernStartScheduleTableSynchron(s))
#define OS_UserChainScheduleTable(s1, s2)		OS_CALL(os_result_t,		OS_KernChainScheduleTable(s1, s2))
#define OS_UserStopScheduleTable(s)				OS_CALL(os_result_t,		OS_KernStopScheduleTable(s))
#define OS_UserGetScheduleTableStatus(s, sr)	OS_CALL(os_result_t,		OS_KernGetScheduleTableStatus(s, sr))
#define OS_UserSetScheduleTableAsync(s)			OS_CALL(os_result_t,		OS_KernSetScheduleTableAsync(s))
#define OS_UserTerminateApplication(a,r)		OS_CALL(os_result_t,		OS_KernTerminateApplication(a, r))
#define OS_UserGetApplicationId()				OS_CALL(os_applicationid_t,	OS_KernGetApplicationId())
#define OS_UserCheckObjectOwnership(ot, o)		OS_CALL(os_applicationid_t,	OS_KernCheckObjectOwnership(ot, o))
#define OS_UserCheckObjectAccess(a, ot, o)		OS_CALL(os_boolean_t,		OS_KernCheckObjectAccess(a, ot, o))
#define OS_UserGetIsrId()						OS_CALL(os_isrid_t,			OS_KernGetIsrId())
#define OS_UserCheckIsrMemoryAccess(i, m, s)	OS_CALL(os_memoryaccess_t,	OS_KernCheckIsrMemoryAccess(i, m, s))
#define OS_UserCheckTaskMemoryAccess(t, m, s)	OS_CALL(os_memoryaccess_t,	OS_KernCheckTaskMemoryAccess(t, m, s))
#define OS_UserCallTrustedFunction(f, p)		OS_CALL(os_result_t,		OS_KernCallTrustedFunction(f, p))
#define OS_UserSyncScheduleTable(s, g1)			OS_CALL(os_result_t,		OS_KernSyncScheduleTable(s, g1))
#define OS_UserDisableInterruptSource(i)		OS_CALL(os_result_t,		OS_KernDisableInterruptSource(i))
#define OS_UserEnableInterruptSource(i, f)		OS_CALL(os_result_t,		OS_KernEnableInterruptSource(i, f))
#define OS_UserClearPendingInterrupt(i)			OS_CALL(os_result_t,		OS_KernClearPendingInterrupt(i))
#define OS_UserGetCounterValue(c, v)			OS_CALL(os_result_t,		OS_KernGetCounterValue(c, v))
#define OS_UserGetElapsedCounterValue(c, p, v)	OS_CALL(os_result_t,		OS_KernGetElapsedCounterValue(c, p, v))
#define OS_UserSimTimerAdvance(t, i)			OS_CALL(os_result_t,		OS_KernSimTimerAdvance(t, i))
#define OS_UserAllowAccess()					OS_CALL(os_result_t,		OS_KernAllowAccess())
#define OS_UserControlIdle(c,m)					OS_CALL(os_result_t,		OS_KernControlIdle(c, m))
#define OS_UserGetCurrentApplicationId()		OS_CALL(os_applicationid_t,		OS_KernGetCurrentApplicationId())

#define OS_UserStartOs(am)						OS_VOIDCALL(OS_KernStartOs(am))
#define OS_UserShutdownOs(e)					OS_VOIDCALL(OS_KernShutdownOs(e))
#define OS_UserSuspendInterrupts(l)				OS_VOIDCALL(OS_KernSuspendInterrupts(l))
#define OS_UserResumeInterrupts(l)				OS_VOIDCALL(OS_KernResumeInterrupts(l))

#if (OS_N_CORES > 1)
#define OS_UserTryToGetSpinlock(sl, out)		OS_CALL(os_result_t,		OS_KernTryToGetSpinlock(sl, out))
#define OS_UserReleaseSpinlock(sl)				OS_CALL(os_result_t,		OS_KernReleaseSpinlock(sl))
#define OS_UserShutdownAllCores(result)			OS_VOIDCALL(OS_KernShutdownAllCores(result))
#endif /* OS_N_CORES > 1 */

#define OS_UserIocWrite(id, data)				OS_CALL(os_result_t,		IOC_SysWrite((id), (data)))
#define OS_UserIocSend(id, data)				OS_CALL(os_result_t,		IOC_SysSend((id), (data)))
#define OS_UserIocEmptyQueue(id)				OS_CALL(os_result_t,		IOC_SysEmptyQueue((id)))
#define OS_UserIocAddonExt(fn, id, data)		OS_CALL(os_result_t,		IOC_SysOsExtDemux((fn), (id), (data)))

#endif
/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/
