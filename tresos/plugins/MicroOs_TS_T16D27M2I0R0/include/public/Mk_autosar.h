/* Mk_autosar.h
 *
 * This header file defines the AUTOSAR system in terms of the microkernel's
 * public interface, as far as possible.
 *
 * This file is included by MicroOs.h. It is also included by any public functions that
 * need to use AUTOSAR types.
 *
 * This file contains type definition for functionality implemented as ASIL or non-ASIL.
 * It is impossible to move non-ASIL definitions out of the microkernel, because the calls
 * to counter subsystem functions are ASIL as long as the OS threads aren't running.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.10 (advisory)
 *  The # and ## preprocessor operators should not be used.
 *
 * Reason:
 *  This construct is mandated by the AUTOSAR OS specification.
 *
 *
 * MISRAC2012-2) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * Required API types.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_NEG_010]
 *  Symbol names shall not contain a negative in the name.
 *
 * Reason:
 *  The name is mandated by AUTOSAR.
*/

/* !LINKSTO Microkernel.Design.Mk_autosar.h, 1
 * !doctype src
*/

#ifndef MK_AUTOSAR_H
#define MK_AUTOSAR_H

#include <Mk_kconfig.h>
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_usr_api.h>
#include <public/Mk_ctrsubindex.h>
#include <public/Mk_error.h>
#include <public/Mk_statustype.h>

#ifndef MK_ASM

/* mk_scheduletablestatustype_e provides an enumeration type containing the states of a schedule table
 *
 * !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_scheduletablestatustype_e
{
	SCHEDULETABLE_UNKNOWNSTATE = 0,
	SCHEDULETABLE_STOPPED = 1,
	SCHEDULETABLE_NEXT = 2,
	SCHEDULETABLE_WAITING = 3,
	SCHEDULETABLE_RUNNING = 4,
	SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS = 5
};


/* mk_objecttypetype_e provides an enumeration type containing all the different kinds of object in AUTOSAR
 * (for use in GetObjectOwnership etc.)
 *
 * !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_objecttypetype_e
{
	OBJECT_TASK,
	OBJECT_ISR,
	OBJECT_ALARM,
	OBJECT_RESOURCE,
	OBJECT_COUNTER,
	OBJECT_SCHEDULETABLE
};


/* These defines are used by RestartType, which is used as one of the parameters to TerminateApplication.
*/
/* Deviation DCG-1 */
#define NO_RESTART		MK_FALSE
#define RESTART			MK_TRUE


/* These defines are used by AccessType, which is used as the return value from GetObjectAccess.
*/
/* Deviation DCG-1 */
#define NO_ACCESS		MK_FALSE
#define ACCESS			MK_TRUE


/* Complete list of all AUTOSAR (including OSEK) types
 * The list is sorted alphabetically unless where impossible (reference type follow their base)
*/
/* Deviation MISRAC2012-2 <START> */
typedef mk_boolean_t						AccessType;
typedef mk_objectid_t						AlarmType;
typedef struct mk_alarmbase_s				AlarmBaseType;
typedef AlarmBaseType					   *AlarmBaseRefType;
typedef mk_objectid_t						ApplicationType;
typedef mk_appstate_t						ApplicationStateType;
typedef ApplicationStateType			   *ApplicationStateRefType;
typedef mk_objectid_t						AppModeType;
typedef mk_objectid_t						CounterType;
typedef mk_uint32_t							EventMaskType;
typedef EventMaskType					   *EventMaskRefType;
typedef mk_objectid_t						ISRType;
typedef mk_boolean_t						ObjectAccessType;
typedef enum mk_objecttypetype_e			ObjectTypeType;
typedef mk_serviceid_t						OSServiceIdType;
typedef mk_size_t							MemorySizeType;
typedef void							   *MemoryStartAddressType;
#if MK_HAS_INT64
typedef mk_uint64_t							PhysicalTimeType;
#else
typedef mk_uint32_t							PhysicalTimeType;
#endif
typedef mk_protectionaction_t				ProtectionReturnType;
typedef mk_lockid_t							ResourceType;
typedef mk_boolean_t						RestartType;
typedef enum mk_scheduletablestatustype_e	ScheduleTableStatusType;
typedef ScheduleTableStatusType			   *ScheduleTableStatusRefType;
typedef mk_objectid_t						ScheduleTableType;
/*											StatusType is in Mk_statustype.h */
typedef mk_taskstate_t						TaskStateType;
typedef TaskStateType					   *TaskStateRefType;
typedef mk_objectid_t						TaskType;
typedef TaskType						   *TaskRefType;
#if MK_HAS_INT64
typedef mk_uint64_t							TickType;
#else
typedef mk_uint32_t							TickType;
#endif
typedef TickType						   *TickRefType;
typedef mk_objectid_t						TrustedFunctionIndexType;
typedef void							   *TrustedFunctionParameterRefType;
/* Deviation MISRAC2012-2 <STOP> */


/* mk_alarmbase_s is used for the AUTOSAR AlarmBase type
*/
struct mk_alarmbase_s
{
	TickType maxallowedvalue;
	TickType ticksperbase;
	TickType mincycle;
};


/* Complete list of all AUTOSAR (including OSEK) services
 * This is sorted alphabetically.
*/

/* !LINKSTO Microkernel.Function.ActivateTask, 2
 * !doctype src
*/
#define ActivateTask(t)				(MK_WAITFORREPLY(MK_UsrActivateTask(t)))

/* !LINKSTO Microkernel.Function.AllowAccess, 1
 * !doctype src
*/
#define AllowAccess()				((StatusType)MK_UsrAllowAccess())

/* !LINKSTO Microkernel.Function.CallTrustedFunction, 2
 * !doctype src
*/
StatusType CallTrustedFunction(TrustedFunctionIndexType, TrustedFunctionParameterRefType);

/* !LINKSTO Microkernel.Function.ChainTask, 2
 * !doctype src
*/
#define ChainTask(t)				((StatusType)MK_UsrChainTask(t))

/* CheckISRMemoryAccess				not implemented */
/* CheckObjectAccess				not implemented */
/* CheckObjectOwnership				not implemented */
/* CheckTaskMemoryAccess			not implemented */

/* !LINKSTO Microkernel.Function.ClearEvent, 2
 * !doctype src
*/
#define ClearEvent(e)				((StatusType)MK_UsrClearEvent(e))

#ifndef MK_USE_INT_LOCKING_CALLOUTS
#define MK_USE_INT_LOCKING_CALLOUTS 0
#endif

/* !LINKSTO Microkernel.Function.DisableAllInterrupts, 3,
 * !        Microkernel.Function.MK_SuspendCallout, 1
 * !doctype src
*/
#if MK_USE_INT_LOCKING_CALLOUTS
#define DisableAllInterrupts()		(MK_SuspendCallout(MK_resLockCat1))
#else
#define DisableAllInterrupts()		(MK_SuspendInterrupts(MK_resLockCat1))
#endif

/* !LINKSTO Microkernel.Function.EnableAllInterrupts, 3,
 * !        Microkernel.Function.MK_ResumeCallout, 1
 * !doctype src
*/
#if MK_USE_INT_LOCKING_CALLOUTS
#define EnableAllInterrupts()		(MK_ResumeCallout(MK_resLockCat1))
#else
#define EnableAllInterrupts()		(MK_ResumeInterrupts(MK_resLockCat1))
#endif

/* GetActiveApplicationMode - Implemented by the counter subsystem.
*/
AppModeType GetActiveApplicationMode(void);

/* !LINKSTO Microkernel.Function.GetApplicationID, 2
 * !doctype src
*/
ApplicationType GetApplicationID(void);

/* !LINKSTO Microkernel.Function.GetCurrentApplicationID, 1
 * !doctype src
*/
ApplicationType GetCurrentApplicationID(void);

/* !LINKSTO Microkernel.Function.GetApplicationState, 2
 * !doctype src
*/
StatusType GetApplicationState(ApplicationType, ApplicationStateRefType);

/* !LINKSTO Microkernel.Function.GetEvent, 2
 * !doctype src
*/
StatusType GetEvent(TaskType, EventMaskRefType);

/* !LINKSTO Microkernel.Function.GetISRID, 2
 * !doctype src
*/
#define GetISRID()					((ISRType)MK_UsrGetIsrId())

/* !LINKSTO Microkernel.Function.GetResource, 2
 * !doctype src
*/
#define GetResource(r)				((StatusType)MK_UsrAcquireLock(r))

/* !LINKSTO Microkernel.Function.GetTaskID, 2
 * !doctype src
*/
StatusType GetTaskID(TaskRefType);

/* !LINKSTO Microkernel.Function.GetTaskState, 2
 * !doctype src
*/
StatusType GetTaskState(TaskType, TaskStateRefType);

/* !LINKSTO Microkernel.Function.ReleaseResource, 2
 * !doctype src
*/
#define ReleaseResource(r)			((StatusType)MK_UsrReleaseLock(r))

/* !LINKSTO Microkernel.Function.ResumeAllInterrupts, 3,
 * !        Microkernel.Function.MK_SuspendCallout, 1
 * !doctype src
*/
#if MK_USE_INT_LOCKING_CALLOUTS
#define ResumeAllInterrupts()		(MK_ResumeCallout(MK_resLockCat1))
#else
#define ResumeAllInterrupts()		(MK_ResumeInterrupts(MK_resLockCat1))
#endif

/* !LINKSTO Microkernel.Function.ResumeOSInterrupts, 3,
 * !        Microkernel.Function.MK_ResumeCallout, 1
 * !doctype src
*/
#if MK_USE_INT_LOCKING_CALLOUTS
#define ResumeOSInterrupts()		(MK_ResumeCallout(MK_resLockCat2))
#else
#define ResumeOSInterrupts()		(MK_ResumeInterrupts(MK_resLockCat2))
#endif

/* !LINKSTO Microkernel.Function.Schedule, 2
 * !doctype src
*/
#define Schedule()					((StatusType)MK_UsrSchedule())

/* !LINKSTO Microkernel.Function.SetEvent, 2
 * !doctype src
*/
#define SetEvent(t, e)				(MK_WAITFORREPLY(MK_UsrSetEvent(t, e)))

/* !LINKSTO Microkernel.Function.ShutdownOS, 2
 * !doctype src
*/
#define ShutdownOS(e)				((void)MK_UsrShutdown(e))

/* !LINKSTO Microkernel.Function.StartOS, 2
 * !doctype src
*/
#define StartOS(am)					((void)MK_UsrStartOs(am))

/* !LINKSTO Microkernel.Function.SuspendAllInterrupts, 3,
 * !        Microkernel.Function.MK_SuspendCallout, 1
 * !doctype src
*/
#if MK_USE_INT_LOCKING_CALLOUTS
#define SuspendAllInterrupts()		(MK_SuspendCallout(MK_resLockCat1))
#else
#define SuspendAllInterrupts()		(MK_SuspendInterrupts(MK_resLockCat1))
#endif

/* !LINKSTO Microkernel.Function.SuspendOSInterrupts, 3,
 * !        Microkernel.Function.MK_ResumeCallout, 1
 * !doctype src
*/
#if MK_USE_INT_LOCKING_CALLOUTS
#define SuspendOSInterrupts()		(MK_SuspendCallout(MK_resLockCat2))
#else
#define SuspendOSInterrupts()		(MK_SuspendInterrupts(MK_resLockCat2))
#endif

/* !LINKSTO Microkernel.Function.TerminateApplication, 2
 * !doctype src
*/
#define TerminateApplication(a, r)	(MK_WAITFORREPLY(MK_UsrTerminateApplication(a, r)))

/* !LINKSTO Microkernel.Function.TerminateTask, 2
 * !doctype src
*/
#define TerminateTask()				((StatusType)MK_UsrTerminateSelf())

/* !LINKSTO Microkernel.Function.WaitEvent, 2
 * !doctype src
*/
#define WaitEvent(e)				((StatusType)MK_UsrWaitEvent(e))

/* Interface to the counter subsystem
*/
/* GetElapsedCounterValue - Implemented by the counter subsystem.
*/
StatusType GetElapsedCounterValue(CounterType, TickRefType, TickRefType);

/* !LINKSTO Microkernel.Function.CtrSubInterfaceFunctions, 1
 * !doctype src
*/
#define CancelAlarm(a)				(MK_LIBCALLCTRSUB1(MK_ctrsub_CancelAlarm, a))
StatusType GetAlarm(AlarmType, TickRefType);
StatusType GetAlarmBase(AlarmType, AlarmBaseRefType);
StatusType GetCounterValue(CounterType, TickRefType);
StatusType GetScheduleTableStatus(ScheduleTableType, ScheduleTableStatusRefType);
#define IncrementCounter(c)			(MK_LIBCALLCTRSUB1(MK_ctrsub_IncrementCounter, c))
#define NextScheduleTable(s1, s2)	(MK_LIBCALLCTRSUB2(MK_ctrsub_NextScheduleTable, s1, s2))
#define SetAbsAlarm(a, i, c)		(MK_LIBCALLCTRSUB3(MK_ctrsub_SetAbsAlarm, a, i, c))
#define SetRelAlarm(a, i, c)		(MK_LIBCALLCTRSUB3(MK_ctrsub_SetRelAlarm, a, i, c))
#define SetScheduleTableAsync(s)	(MK_LIBCALLCTRSUB1(MK_ctrsub_SetScheduleTableAsync, s))
#define StartScheduleTableAbs(s, t)	(MK_LIBCALLCTRSUB3(MK_ctrsub_StartScheduleTable, s, t, MK_FALSE))
#define StartScheduleTableRel(s, t)	(MK_LIBCALLCTRSUB3(MK_ctrsub_StartScheduleTable, s, t, MK_TRUE))
#define StartScheduleTableSynchron(s)	(MK_LIBCALLCTRSUB1(MK_ctrsub_StartScheduleTableSynchron, s))
#define StopScheduleTable(s)		(MK_LIBCALLCTRSUB1(MK_ctrsub_StopScheduleTable, s))
#define SyncScheduleTable(s, g1)	(MK_LIBCALLCTRSUB2(MK_ctrsub_SyncScheduleTable, s, g1))

/* CoreIdType - AUTOSAR type for storing core identifiers.
*/
/* Deviation MISRAC2012-2 <+1> */
typedef mk_objectid_t CoreIdType;

/* !LINKSTO Microkernel.Function.GetCoreID, 3
 * !doctype src
*/
#if (MK_MAXCORES > 1)
CoreIdType GetCoreID(void);
#else
#define GetCoreID() ((CoreIdType)0)
#endif /* MK_MAXCORES */


/* The spinlock API only exist on processors with more than one core, and only then
 * provided that the microkernel has multi-core support.
*/
#if (MK_MAXCORES > 1)

#define TRYTOGETSPINLOCK_SUCCESS	MK_TRUE
#define TRYTOGETSPINLOCK_NOSUCCESS	MK_FALSE

typedef mk_lockid_t SpinlockIdType;
typedef mk_boolean_t TryToGetSpinlockType;

/* !LINKSTO Microkernel.Function.GetSpinlock, 2
 * !doctype src
*/
StatusType GetSpinlock(SpinlockIdType);

/* !LINKSTO Microkernel.Function.TryToGetSpinlock, 2
 * !doctype src
*/
StatusType TryToGetSpinlock(SpinlockIdType, TryToGetSpinlockType *);

/* !LINKSTO Microkernel.Function.ReleaseSpinlock, 2
 * !doctype src
*/
#define ReleaseSpinlock(s)			((StatusType)MK_UsrReleaseLock(s))

#endif /* MK_MAXCORES */


/* !LINKSTO Microkernel.Function.StartCore, 3
 * !doctype src
*/
#define StartCore(core, presult)													\
	do {																			\
		*(presult) = MK_WAITFORREPLY(MK_UsrStartCore(MK_GetPhysicalCoreId(core)));	\
	} while (0)

/* !LINKSTO Microkernel.Function.ShutdownAllCores, 2
 * !doctype src
*/
#define ShutdownAllCores(s)			((void)MK_UsrShutdownAllCores(s))

/* These macros are not useful. The IDs of the tasks etc. are defined as macros that expand to
 * literal constants.
 * We define these macros as a harmless function prototype to swallow the semicolon without
 * annoying some compilers.
*/
#define DeclareTask(t)		void MK_Idle(void)
#define DeclareEvent(t)		void MK_Idle(void)
#define DeclareResource(t)	void MK_Idle(void)
#define DeclareAlarm(t)		void MK_Idle(void)

/* If C++ support is ever needed, these macros will need defining with an "extern C" qualifier
 * for C++ modules.
*/
/* Deviation MISRAC2012-1 <+3> */
#define TASK(x)				void OS_TASK_##x(void)
#define ALARMCALLBACK(x)	void OS_ACB_##x(void)
#define ISR(x)				void OS_ISR_##x(void)

/* Some constants required by the AUTOSAR standard
*/
#define INVALID_TASK			((TaskType)MK_INVALID_TASK)
#define INVALID_ISR				((ISRType)MK_INVALID_ISR)
#define INVALID_OSAPPLICATION	((ApplicationType)MK_APPL_NONE)
#define MK_INVALID_SERVICEID	((OSServiceIdType)MK_sid_InvalidServiceId)

/* Complete list of Service IDs defined by AUTOSAR for error-reporting purposes.
 * The list is sorted alphabetically.
 *
 * !LINKSTO Microkernel.Interface.API.ServiceId, 1
 * !doctype src
 */
#define OSServiceId_ActivateTask					MK_sid_ActivateTask
#define OSServiceId_CallTrustedFunction				MK_sid_CallTrustedFunction
#define OSServiceId_CancelAlarm						MK_sid_CancelAlarm
#define OSServiceId_ChainTask						MK_sid_ChainTask
#define OSServiceId_CheckISRMemoryAccess			MK_INVALID_SERVICEID		/* Not implemented */
#define OSServiceId_CheckObjectAccess				MK_INVALID_SERVICEID		/* Not implemented */
#define OSServiceId_CheckObjectOwnership			MK_INVALID_SERVICEID		/* Not implemented */
#define OSServiceId_CheckTaskMemoryAccess			MK_INVALID_SERVICEID		/* Not implemented */
#define OSServiceId_ClearEvent						MK_sid_ClearEvent
#define OSServiceId_DisableAllInterrupts			MK_INVALID_SERVICEID		/* Identifies as AcquireLock */
#define OSServiceId_EnableAllInterrupts				MK_INVALID_SERVICEID		/* Identifies as ReleaseLock */
#define OSServiceId_GetActiveApplicationMode		MK_INVALID_SERVICEID		/* Direct call to asc_Os; no errors */
#define OSServiceId_GetAlarm						MK_sid_GetAlarm
#define OSServiceId_GetAlarmBase					MK_sid_GetAlarmBase
#define OSServiceId_GetApplicationID				MK_INVALID_SERVICEID		/* Never reports errors */
#define OSServiceId_GetCurrentApplicationID			MK_INVALID_SERVICEID		/* Never reports errors */
#define OSServiceId_GetApplicationState				MK_sid_GetApplicationState
#define OSServiceId_GetCounterValue					MK_sid_GetCounterValue
#define OSServiceId_GetElapsedCounterValue			MK_INVALID_SERVICEID		/* Identifies as GetCounterValue */
#define OSServiceId_GetEvent						MK_sid_GetEvent
#define OSServiceId_GetISRID						MK_sid_GetIsrId
#define OSServiceId_GetResource						MK_sid_AcquireLock
#define OSServiceId_GetScheduleTableStatus			MK_sid_GetScheduleTableStatus
#define OSServiceId_GetTaskID						MK_sid_GetTaskId
#define OSServiceId_GetTaskState					MK_sid_GetTaskState
#define OSServiceId_IncrementCounter				MK_sid_IncrementCounter
#define OSServiceId_NextScheduleTable				MK_sid_NextScheduleTable
#define OSServiceId_ReleaseResource					MK_sid_ReleaseLock
#define OSServiceId_ResumeAllInterrupts				MK_INVALID_SERVICEID		/* Identifies as ReleaseLock */
#define OSServiceId_ResumeOSInterrupts				MK_INVALID_SERVICEID		/* Identifies as ReleaseLock */
#define OSServiceId_Schedule						MK_sid_Schedule
#define OSServiceId_SetAbsAlarm						MK_sid_SetAbsAlarm
#define OSServiceId_SetEvent						MK_sid_SetEvent
#define OSServiceId_SetRelAlarm						MK_sid_SetRelAlarm
#define OSServiceId_SetScheduleTableAsync			MK_sid_SetScheduleTableAsync
#define OSServiceId_ShutdownOS						MK_sid_Shutdown
#define OSServiceId_SuspendAllInterrupts			MK_INVALID_SERVICEID		/* Identifies as AcquireLock */
#define OSServiceId_SuspendOSInterrupts				MK_INVALID_SERVICEID		/* Identifies as AcquireLock */
#define OSServiceId_StartOS							MK_sid_StartOs
#define OSServiceId_StartScheduleTableAbs			MK_sid_StartScheduleTableAbs
#define OSServiceId_StartScheduleTableRel			MK_sid_StartScheduleTableRel
#define OSServiceId_StartScheduleTableSynchron		MK_sid_StartScheduleTableSynchron
#define OSServiceId_StopScheduleTable				MK_sid_StopScheduleTable
#define OSServiceId_SyncScheduleTable				MK_sid_SyncScheduleTable
#define OSServiceId_TerminateApplication			MK_sid_TerminateApplication
#define OSServiceId_TerminateTask					MK_sid_TerminateSelf
#define OSServiceId_WaitEvent						MK_sid_WaitEvent


#define OSErrorGetServiceId()						((OSServiceIdType)MK_ErrorGetServiceId())


/* Parameter access macros. The values are only guaranteed if the caller is the error hook function
 *
 * !LINKSTO Microkernel.Function.OSError, 2
 * !doctype src
 *
 * Many of these macros are longer than the MISRA-specified limit of 31 characters.
 *      1234567890123456789012345678901
*/
#define OSError_ActivateTask_TaskID()						((TaskType)			MK_ErrorGetParameter(1))
#define OSError_CallTrustedFunction_FunctionIndex()			((TrustedFunctionIndexType)MK_ErrorGetParameter(1))
#define OSError_CallTrustedFunction_FunctionParams()		((TrustedFunctionParameterRefType)MK_ErrorGetParameter(2))
#define OSError_ChainTask_TaskID()							((TaskType)			MK_ErrorGetParameter(1))
#define OSError_GetTaskID_TaskID()							((TaskRefType)		MK_ErrorGetParameter(1))
#define OSError_GetTaskState_TaskID()						((TaskType)			MK_ErrorGetParameter(1))
#define OSError_GetTaskState_State()						((TaskStateRefType)	MK_ErrorGetParameter(2))
#define OSError_GetResource_ResID()							((ResourceType)		MK_ErrorGetParameter(1))
#define OSError_ReleaseResource_ResID()						((ResourceType)		MK_ErrorGetParameter(1))
#define OSError_SetEvent_TaskID()							((TaskType)			MK_ErrorGetParameter(1))
#define OSError_SetEvent_Mask()								((EventMaskType)	MK_ErrorGetParameter(2))
#define OSError_ClearEvent_Mask()							((EventMaskType)	MK_ErrorGetParameter(1))
#define OSError_WaitEvent_Mask()							((EventMaskType)	MK_ErrorGetParameter(1))
#define OSError_GetEvent_TaskID()							((TaskType)			MK_ErrorGetParameter(1))
#define OSError_GetEvent_Event()							((EventMaskRefType)	MK_ErrorGetParameter(2))
#define OSError_GetAlarm_AlarmID()							((AlarmType)		MK_ErrorGetParameter(1))
#define OSError_GetAlarm_Tick()								((TickRefType)		MK_ErrorGetParameter(2))
#define OSError_GetAlarmBase_AlarmID()						((AlarmType)		MK_ErrorGetParameter(1))
#define OSError_GetAlarmBase_Info()							((AlarmBaseRefType)	MK_ErrorGetParameter(2))
#define OSError_SetRelAlarm_AlarmID()						((AlarmType)		MK_ErrorGetParameter(1))
#define OSError_SetRelAlarm_increment()						((TickType)			MK_ErrorGetParameter(2))
#define OSError_SetRelAlarm_cycle()							((TickType)			MK_ErrorGetParameter(3))
#define OSError_SetAbsAlarm_AlarmID()						((AlarmType)		MK_ErrorGetParameter(1))
#define OSError_SetAbsAlarm_start()							((TickType)			MK_ErrorGetParameter(2))
#define OSError_SetAbsAlarm_cycle()							((TickType)			MK_ErrorGetParameter(3))
#define OSError_CancelAlarm_AlarmID()						((AlarmType)		MK_ErrorGetParameter(1))
#define OSError_StartOS_Mode()								((AppModeType)		MK_ErrorGetParameter(1))
#define OSError_ShutdownOS_Error()							((StatusType)		MK_ErrorGetParameter(1))
#define OSError_IncrementCounter_CounterID()				((CounterType)		MK_ErrorGetParameter(1))
#define OSError_StartScheduleTableRel_ScheduleTableID()		((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_StartScheduleTableRel_Offset()				((TickType)			MK_ErrorGetParameter(2))
#define OSError_StartScheduleTableAbs_ScheduleTableID()		((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_StartScheduleTableAbs_Tickvalue()			((TickType)			MK_ErrorGetParameter(2))
#define OSError_StartScheduleTableSynchron_ScheduleTableID()	((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_StopScheduleTable_ScheduleTableID()			((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_SyncScheduleTable_SchedTableID()			((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_SyncScheduleTable_GlobalTime()				((TickType)			MK_ErrorGetParameter(2))
#define OSError_SetScheduleTableAsync_ScheduleID()			((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_GetCounterValue_CounterID()					((CounterType)		MK_ErrorGetParameter(1))
#define OSError_GetCounterValue_Value()						((TickRefType)		MK_ErrorGetParameter(2))
#define OSError_TerminateApplication_Application()			((ApplicationType)	MK_ErrorGetParameter(1))
#define OSError_TerminateApplication_RestartOption()		((RestartType)		MK_ErrorGetParameter(2))
#define OSError_NextScheduleTable_SchedTableID_current()	((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_NextScheduleTable_SchedTableID_next()		((ScheduleTableType)MK_ErrorGetParameter(2))
#define OSError_GetScheduleTableStatus_ScheduleID()			((ScheduleTableType)MK_ErrorGetParameter(1))
#define OSError_GetScheduleTableStatus_ScheduleStatus()		((ScheduleTableStatusRefType)MK_ErrorGetParameter(2))
#define OSError_GetElapsedCounterValue_CounterID()			((CounterType)		MK_ErrorGetParameter(1))
#define OSError_GetElapsedCounterValue_PreviousValue()		((TickRefType)		MK_ErrorGetParameter(2))
#define OSError_GetElapsedCounterValue_Value()				((TickRefType)		MK_ErrorGetParameter(3))
#define OSError_GetSpinlock_SpinlockId()					((SpinlockIdType)	MK_ErrorGetParameter(1))
#define OSError_TryToGetSpinlock_SpinlockId()				((SpinlockIdType)	MK_ErrorGetParameter(1))
/* OSError_TryToGetSpinlock_Success can't be implemented, because this parameter is not passed to the system call. */
#define OSError_ReleaseSpinlock_SpinlockId()				((SpinlockIdType)	MK_ErrorGetParameter(1))

#define DONOTCARE	MK_DONOTCARE_APPMODE

#endif

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
