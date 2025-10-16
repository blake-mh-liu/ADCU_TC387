/* Mk_errorhandling.h
 *
 * This file contains definitions for the microkernel's error handling.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_ERRORHANDLING_H
#define MK_ERRORHANDLING_H

#include <public/Mk_error.h>
#include <private/Mk_thread.h>
#include <private/Mk_types_forward.h>

/* The table for translating internal error codes into AUTOSAR/OSEK StatusType return values.
*/
#define MK_ERRORLOOKUPTABLE \
	MK_ERRORLOOKUP(MK_eid_NoError,							MK_E_OK),							\
	MK_ERRORLOOKUP(MK_eid_TryAgain,							MK_E_TRYAGAIN),						\
	MK_ERRORLOOKUP(MK_eid_WaitForReply,						MK_E_WAITFORREPLY),					\
	MK_ERRORLOOKUP(MK_eid_FirstError,						MK_E_ERROR), /* Marker */			\
	MK_ERRORLOOKUP(MK_eid_AlignmentException,				E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_AppNotRestarting,					E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_ArithmeticException,				E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_CallFromNonApplication,			E_OS_CALLEVEL),                     \
	MK_ERRORLOOKUP(MK_eid_CallFromTrustedFunction,			E_OS_CALLEVEL),                     \
	MK_ERRORLOOKUP(MK_eid_CallNestingException,				E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_DebugEventException,				E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_ExecutionBudgetExceeded,			E_OS_PROTECTION_TIME),				\
	MK_ERRORLOOKUP(MK_eid_HardwareUnavailableException,		E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_IllegalInstructionException,		E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_InvalidErrorId,					MK_E_ERROR),						\
	MK_ERRORLOOKUP(MK_eid_InvalidInterruptConfiguration,	E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_InvalidIsrId,						E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_InvalidMpuConfiguration,			E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_InvalidOsApplication,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_InvalidCtrSubFunction,			E_OS_SERVICEID),					\
	MK_ERRORLOOKUP(MK_eid_InvalidCtrSubObjectId,			E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_InvalidLockId,					E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_InvalidRestartParameter,			E_OS_VALUE),						\
	MK_ERRORLOOKUP(MK_eid_InvalidTaskId,					E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_InvalidAddOnId,					E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_InvalidTrustedFunctionId,			E_OS_SERVICEID),					\
	MK_ERRORLOOKUP(MK_eid_InvalidServiceId,					MK_E_ERROR),						\
	MK_ERRORLOOKUP(MK_eid_InvalidSstId,						E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_InvalidSstDelta,					E_OS_VALUE),						\
	MK_ERRORLOOKUP(MK_eid_InvalidPrbcMode,					E_OS_VALUE),						\
	MK_ERRORLOOKUP(MK_eid_LockBudgetExceeded,				E_OS_PROTECTION_LOCKED),			\
	MK_ERRORLOOKUP(MK_eid_MaxActivationsExceeded,			E_OS_LIMIT),						\
	MK_ERRORLOOKUP(MK_eid_MemoryProtectionException,		E_OS_PROTECTION_MEMORY),			\
	MK_ERRORLOOKUP(MK_eid_ProcessorSpecificException,		E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_CtrSubCallFromWrongContext,		E_OS_CALLEVEL),						\
	MK_ERRORLOOKUP(MK_eid_Quarantined,						E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_LockAlreadyOccupied,				E_OS_ACCESS),						\
	MK_ERRORLOOKUP(MK_eid_LockNestingLimitExceeded,			E_OS_ACCESS),						\
	MK_ERRORLOOKUP(MK_eid_LockNotOccupied,					E_OS_NOFUNC),						\
	MK_ERRORLOOKUP(MK_eid_LockNotOccupiedByCaller,			E_OS_NOFUNC),						\
	MK_ERRORLOOKUP(MK_eid_LockReleaseSequenceError,			E_OS_NOFUNC),						\
	MK_ERRORLOOKUP(MK_eid_LockConfiguredForDifferentCore,	E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_TaskIsNotExtended,				E_OS_ACCESS),						\
	MK_ERRORLOOKUP(MK_eid_TFCallFromWrongContext,			E_OS_CALLEVEL),						\
	MK_ERRORLOOKUP(MK_eid_TFCallFromWrongCore,				E_OS_CALLEVEL),						\
	MK_ERRORLOOKUP(MK_eid_ThreadIsNotATask,					E_OS_CALLEVEL),						\
	MK_ERRORLOOKUP(MK_eid_ThreadIsNotIdle,					E_OS_CALLEVEL),						\
	MK_ERRORLOOKUP(MK_eid_ThreadOccupiesLock,				E_OS_RESOURCE),						\
	MK_ERRORLOOKUP(MK_eid_UnimplementedCtrSubFunction,		E_OS_SERVICEID),					\
	MK_ERRORLOOKUP(MK_eid_WatchdogException,				E_OS_PROTECTION_EXCEPTION),			\
	MK_ERRORLOOKUP(MK_eid_WithoutPermission,				E_OS_ACCESS),						\
	MK_ERRORLOOKUP(MK_eid_CoreIdOutOfRange,					E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_CoreIsNotConfigured,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_CoreIsNotRunning,					E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_CoreIsAlreadyStarted,				E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_CoreIsAutonomous,					E_OS_ACCESS),						\
	MK_ERRORLOOKUP(MK_eid_CoreIsAnAutosarCore,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_StartOsWhileCtrSubBusy,			E_OS_CALLEVEL),						\
	MK_ERRORLOOKUP(MK_eid_SyncServiceCalledAsync,			E_OS_SERVICEID),					\
	MK_ERRORLOOKUP(MK_eid_UnsupportedXCoreRequest,			E_OS_SERVICEID),					\
	MK_ERRORLOOKUP(MK_eid_TargetCoreCorrupted,				MK_E_INTERNAL),						\
	MK_ERRORLOOKUP(MK_eid_OsAlarmInUse,						E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_OsAlarmNotInQueue,				MK_E_INTERNAL),						\
	MK_ERRORLOOKUP(MK_eid_OsAlarmNotInUse,					E_OS_NOFUNC),						\
	MK_ERRORLOOKUP(MK_eid_OsCounterIsHw,					E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsDifferentCounters,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsImplicitSyncStartRel,			E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsIncrementZero,					E_OS_VALUE),						\
	MK_ERRORLOOKUP(MK_eid_OsInterruptDisabled,				E_OS_DISABLEDINT),					\
	MK_ERRORLOOKUP(MK_eid_OsInvalidAlarmId,					E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsInvalidAlarmState,				E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_OsInvalidApplication,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsInvalidCounterId,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsInvalidScheduleId,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsInvalidStartMode,				E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsNotChained,						E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_OsNotRunning,						E_OS_NOFUNC),						\
	MK_ERRORLOOKUP(MK_eid_OsNotStopped,						E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_OsNotSyncable,					E_OS_ID),							\
	MK_ERRORLOOKUP(MK_eid_OsParameterOutOfRange,			E_OS_VALUE),						\
	MK_ERRORLOOKUP(MK_eid_OsPermission,						E_OS_ACCESS),						\
	MK_ERRORLOOKUP(MK_eid_OsQuarantined,					E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_OsScheduleTableNotIdle,			E_OS_STATE),						\
	MK_ERRORLOOKUP(MK_eid_OsUnknownSystemCall,				E_OS_NOFUNC),						\
	MK_ERRORLOOKUP(MK_eid_OsWriteProtect,					E_OS_ILLEGAL_ADDRESS),				\
	MK_ERRORLOOKUP(MK_eid_OsWrongContext,					E_OS_CALLEVEL),						\
	MK_ERRORLOOKUP(MK_eid_SstInThePast,						MK_E_INTHEPAST),					\
	MK_ERRORLOOKUP(MK_eid_Unknown,							MK_E_ERROR)		/* Last entry */

/* Internal functions related to error reporting
*/
mk_osekerror_t MK_InternReportError(mk_kernelcontrol_t *,
									mk_serviceid_t,
									mk_errorid_t,
									mk_thread_t *,
									mk_parametertype_t *);
void MK_ReportProtectionFault(mk_kernelcontrol_t *, mk_serviceid_t, mk_errorid_t);
void MK_PerformProtectionAction(mk_kernelcontrol_t *);

/* Individual protection actions
*/
void MK_PpaContinue(mk_kernelcontrol_t *);
void MK_PpaPanic(mk_kernelcontrol_t *);
void MK_PpaPanicStop(mk_kernelcontrol_t *);
void MK_PpaShutdown(mk_kernelcontrol_t *);
void MK_PpaShutdownAllCores(mk_kernelcontrol_t *);
void MK_PpaTerminateTaskIsr(mk_kernelcontrol_t *);
void MK_PpaTerminateApplication(mk_kernelcontrol_t *);
void MK_PpaTerminateApplicationRestart(mk_kernelcontrol_t *);
void MK_PpaTerminateThread(mk_kernelcontrol_t *);

/* If the desired protection action is invalid or not implemented,
 * shutdown the microkernel.
*/
#define MK_PpaInvalidProtectionAction MK_PpaShutdown

/* Type used for a protection action
*/
typedef void (*mk_ppafunction_t)(mk_kernelcontrol_t *);

/* Array that contains function pointers to all protection actions
*/
extern const mk_ppafunction_t MK_ppaFunctions[MK_PRO_INVALIDACTION + 1];


#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
