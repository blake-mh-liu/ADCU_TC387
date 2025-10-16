/* Mk_error.h
 *
 * This file contains definitions for the error codes returned by
 * kernel API functions, and the error codes used by the kernel internally,
 * since these are available via the error status API.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_ERROR_H
#define MK_ERROR_H

#include <public/Mk_hw_characteristics.h>
#include <public/Mk_public_types.h>
#include <public/Mk_syscallindex.h>
#include <public/Mk_ctrsubindex.h>
#include <public/Mk_exceptioninfo.h>

#ifndef MK_ASM

/* Internal error codes, made visible by the error-status API.
 *
 * The order is as follows:
 *	- MK_eid_NoError is first (enum value 0)
 *  - MK errors follow in alphabetical order as defined by sort(1)
 *  - OS errors (Mk_OsBla) follow in alphabetical order
 *	- MK_eid_Unknown is last
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_errorid_e
{
	MK_eid_NoError = 0,					/* Not an error */
	MK_eid_TryAgain,					/* Not an error */
	MK_eid_WaitForReply,				/* Not an error */
	MK_eid_FirstError,					/* Range marker - not used as an error code */
	/*34567890123456789012345678901		31-character symbol length */
	MK_eid_AlignmentException,
	MK_eid_AppNotRestarting,
	MK_eid_ArithmeticException,
	MK_eid_CallFromNonApplication,
	MK_eid_CallFromTrustedFunction,
	MK_eid_CallNestingException,
	MK_eid_DebugEventException,
	MK_eid_ExecutionBudgetExceeded,
	MK_eid_HardwareUnavailableException,
	MK_eid_IllegalInstructionException,
	MK_eid_InvalidErrorId,
	MK_eid_InvalidInterruptConfiguration,
	MK_eid_InvalidIsrId,
	MK_eid_InvalidMpuConfiguration,
	MK_eid_InvalidOsApplication,
	MK_eid_InvalidCtrSubFunction,
	MK_eid_InvalidCtrSubObjectId,
	MK_eid_InvalidLockId,
	MK_eid_InvalidRestartParameter,
	MK_eid_InvalidTaskId,
	MK_eid_InvalidAddOnId,
	MK_eid_InvalidTrustedFunctionId,
	MK_eid_InvalidServiceId,
	MK_eid_InvalidSstId,
	MK_eid_InvalidSstDelta,
	MK_eid_InvalidPrbcMode,
	MK_eid_LockBudgetExceeded,
	MK_eid_MaxActivationsExceeded,
	MK_eid_MemoryProtectionException,
	MK_eid_ProcessorSpecificException,
	MK_eid_CtrSubCallFromWrongContext,
	MK_eid_Quarantined,
	MK_eid_LockAlreadyOccupied,
	MK_eid_LockNestingLimitExceeded,
	MK_eid_LockNotOccupied,
	MK_eid_LockNotOccupiedByCaller,
	MK_eid_LockReleaseSequenceError,
	MK_eid_LockConfiguredForDifferentCore,
	MK_eid_TaskIsNotExtended,
	MK_eid_TFCallFromWrongContext,
	MK_eid_TFCallFromWrongCore,
	MK_eid_ThreadIsNotATask,
	MK_eid_ThreadIsNotIdle,
	MK_eid_ThreadOccupiesLock,
	MK_eid_UnimplementedCtrSubFunction,
	MK_eid_WatchdogException,
	MK_eid_WithoutPermission,
	MK_eid_CoreIdOutOfRange,
	MK_eid_CoreIsNotConfigured,
	MK_eid_CoreIsNotRunning,
	MK_eid_CoreIsAlreadyStarted,
	MK_eid_CoreIsAutonomous,
	MK_eid_CoreIsAnAutosarCore,
	MK_eid_StartOsWhileCtrSubBusy,
	MK_eid_SyncServiceCalledAsync,
	MK_eid_UnsupportedXCoreRequest,
	MK_eid_TargetCoreCorrupted,

	/* The MK_eid_Os* error codes below this point are for use in the counter subsystem.
	 * They should not be used in the microkernel.
	*/
	MK_eid_OsAlarmInUse,
	MK_eid_OsAlarmNotInQueue,
	MK_eid_OsAlarmNotInUse,
	MK_eid_OsCounterIsHw,
	MK_eid_OsDifferentCounters,
	MK_eid_OsImplicitSyncStartRel,
	MK_eid_OsIncrementZero,
	MK_eid_OsInterruptDisabled,
	MK_eid_OsInvalidAlarmId,
	MK_eid_OsInvalidAlarmState,
	MK_eid_OsInvalidApplication,
	MK_eid_OsInvalidCounterId,
	MK_eid_OsInvalidScheduleId,
	MK_eid_OsInvalidStartMode,
	MK_eid_OsNotChained,
	MK_eid_OsNotRunning,
	MK_eid_OsNotStopped,
	MK_eid_OsNotSyncable,
	MK_eid_OsParameterOutOfRange,
	MK_eid_OsPermission,
	MK_eid_OsQuarantined,
	MK_eid_OsScheduleTableNotIdle,
	MK_eid_OsUnknownSystemCall,
	MK_eid_OsWriteProtect,
	MK_eid_OsWrongContext,
	MK_eid_SstInThePast,

	MK_eid_Unknown,					/* Must be the last of the sequentially-allocated error IDs */

	/* Sentinel value which guarantees that this type can represent a certain range of
	 * user-defined values. This sentinel value must not exceed 16 bit.
	*/
	MK_eid_Sentinel = 32767
};

typedef enum mk_errorid_e mk_errorid_t;

/* AUTOSAR-defined error codes
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_osekerror_e
{
	MK_E_OK = 0,					/* == E_OK, but we cannot define that! */
	E_OS_ACCESS = 1,				/* Value defined by OSEK/VDX */
	E_OS_CALLEVEL = 2,				/* Value defined by OSEK/VDX */
	E_OS_ID = 3,					/* Value defined by OSEK/VDX */
	E_OS_LIMIT = 4,					/* Value defined by OSEK/VDX */
	E_OS_NOFUNC = 5,				/* Value defined by OSEK/VDX */
	E_OS_RESOURCE = 6,				/* Value defined by OSEK/VDX */
	E_OS_STATE = 7,					/* Value defined by OSEK/VDX */
	E_OS_VALUE = 8,					/* Value defined by OSEK/VDX */

	E_OS_SERVICEID = 9,				/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_ILLEGAL_ADDRESS = 10,		/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_MISSINGEND = 11,			/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_DISABLEDINT = 12,			/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_STACKFAULT = 13,			/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_PROTECTION_MEMORY = 14,	/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_PROTECTION_TIME = 15,		/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_PROTECTION_ARRIVAL = 16,	/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_PROTECTION_LOCKED = 17,	/* Defined by AUTOSAR, value is implementation-defined */
	E_OS_PROTECTION_EXCEPTION = 18,	/* Defined by AUTOSAR, value is implementation-defined */

	MK_E_INTERNAL = 19,				/* Defined by EB */

	MK_E_THREADQUEUEEMPTY = 20,		/* Defined by EB. Shutdown only. */
	MK_E_PANIC = 21,				/* Defined by EB. Shutdown only. */

	MK_E_KILLED = 22,				/* Defined by EB. Request could not be performed, thread was killed */
	MK_E_TRYAGAIN = 23,				/* Defined by EB. Not an error; indicates that the call should be retried. */
	MK_E_WAITFORREPLY = 24,			/* Defined by EB. Not an error; indicates that the caller should wait for reply. */
	MK_E_INTHEPAST = 25,			/* Defined by EB. Indicates, ticker can't keep up with real-time. */
	MK_E_ERROR = 26,				/* Must be the last error code. */

	/* Enum sentinel: This type must be able to correctly store all StatusType (uint8) values.
	 * Moreover, values which are stored in this type mustn't be greater than the sentinel,
	 * so mk_osekerror_t can be converted to StatusType (uint8) without loss.
	*/
	MK_OSEKERROR_ENUM_SENTINEL = 255
};

typedef enum mk_osekerror_e mk_osekerror_t;

/* Protection-hook return values
 *
 * The EB-defined values have the MK_ prefix to prevent naming clashes.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_protectionaction_e
{
	MK_PRO_CONTINUE = 0,			/* Continue and perform the request anyway. */
	PRO_IGNORE = 1,					/* Do not perform the offending request, but take no other action. */
	PRO_TERMINATETASKISR = 2,		/* Terminate the task or ISR, shutdown if offender is neither. */
	PRO_TERMINATEAPPL = 3,			/* Terminate the application */
	PRO_TERMINATEAPPL_RESTART = 4,	/* Terminate and restart the application */
	PRO_SHUTDOWN = 5,				/* Perform an orderly shut down */
	MK_PRO_TERMINATE = 6,			/* Terminate the offending thread no matter what it is */
	MK_PRO_TERMINATEALL = 7,		/* Terminate the offending thread and all queued instances of same
									   executable object
									*/
	MK_PRO_QUARANTINE = 8,			/* Terminate the offending thread, ensure that it cannot ever be restarted.
									   Implies MK_PRO_TERMINATEALL.
									*/
	MK_PRO_PANIC = 9,				/* Try to shutdown the microkernel */
	MK_PRO_PANICSTOP = 10,			/* Go to emergency stop state */
	MK_PRO_INVALIDACTION = 11		/* Fallback value */
};

typedef enum mk_protectionaction_e mk_protectionaction_t;

/* Service IDs
 *
 * These are defined in terms of the system call indexes so that the OS system call index can
 * be used as a service ID without a translation table.
 * Service IDs that are not system calls come afterwards.
*/
/* !LINKSTO Microkernel.Interface.API.ServiceId, 1,
 * !        Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_serviceid_e
{
	/* Microkernel system calls. These are assigned explicitly so that they are
	 * guaranteed to match the SC indexes that are used in assembly language files.
	*/
	MK_sid_TerminateSelf			= MK_SC_TerminateSelf,
	MK_sid_ActivateTask				= MK_SC_ActivateTask,
	MK_sid_ChainTask				= MK_SC_ChainTask,
	MK_sid_Schedule					= MK_SC_Schedule,
	MK_sid_AcquireLock				= MK_SC_AcquireLock,
	MK_sid_ReleaseLock				= MK_SC_ReleaseLock,
	MK_sid_Shutdown					= MK_SC_Shutdown,
	MK_sid_StartOs					= MK_SC_StartOs,
	MK_sid_SetEvent					= MK_SC_SetEvent,
	MK_sid_ClearEvent				= MK_SC_ClearEvent,
	MK_sid_WaitEvent				= MK_SC_WaitEvent,
	MK_sid_WaitGetClearEvent		= MK_SC_WaitGetClearEvent,
	MK_sid_GetTaskId				= MK_SC_GetTaskId,
	MK_sid_GetTaskState				= MK_SC_GetTaskState,
	MK_sid_GetIsrId					= MK_SC_GetIsrId,
	MK_sid_ReportError				= MK_SC_ReportError,
	MK_sid_CallCtrSub					= MK_SC_CallCtrSub,
	MK_sid_AllowAccess				= MK_SC_AllowAccess,
	MK_sid_CallTrustedFunction		= MK_SC_CallTrustedFunction,
	MK_sid_TerminateApplication		= MK_SC_TerminateApplication,
	MK_sid_EnableInterruptSource	= MK_SC_EnableInterruptSource,
	MK_sid_DisableInterruptSource	= MK_SC_DisableInterruptSource,
	MK_sid_AddOnControl				= MK_SC_AddOnControl,
	MK_sid_AsyncActivateTask		= MK_SC_AsyncActivateTask,
	MK_sid_AsyncSetEvent			= MK_SC_AsyncSetEvent,
	MK_sid_AsyncCallCtrSub			= MK_SC_AsyncCallCtrSub,
	MK_sid_StartCore				= MK_SC_StartCore,
	MK_sid_ShutdownAllCores			= MK_SC_ShutdownAllCores,
	MK_sid_SstStartCounter			= MK_SC_SstStartCounter,
	MK_sid_SstAdvanceCounter		= MK_SC_SstAdvanceCounter,
	MK_sid_SstStopCounter			= MK_SC_SstStopCounter,
	MK_sid_GetAppModeVoteOfCore		= MK_SC_GetAppModeVoteOfCore,

	/* Threaded counter subsystem calls. These (and the rest of the service IDs are assigned sequentially by
	 * the compiler, starting at MK_NSYSCALL, which is always 1 greater than the highest system-call index.
	*/
	MK_sid_UnconfiguredOsCall		= MK_NSYSCALL,
	MK_sid_SetRelAlarm,
	MK_sid_SetAbsAlarm,
	MK_sid_CancelAlarm,
	MK_sid_IncrementCounter,
	MK_sid_StartScheduleTable,
	MK_sid_StartScheduleTableSynchron,
	MK_sid_NextScheduleTable,
	MK_sid_StopScheduleTable,
	MK_sid_SyncScheduleTable,
	MK_sid_SetScheduleTableAsync,
	MK_sid_SimTimerAdvance,
	MK_sid_GetCounterValue,
	MK_sid_GetAlarm,
	MK_sid_UpdateCounter,
	MK_sid_OS_TerminateApplication,
	MK_sid_OS_StartOs,

	/* Counter subsystem pseudo-services that are not directly called.
	*/
	MK_sid_StartScheduleTableAbs,			/* Variable SID for StartScheduleTable */
	MK_sid_StartScheduleTableRel,			/* Variable SID for StartScheduleTable */
	MK_sid_KillAlarm,
	MK_sid_RunSchedule,

	/* Counter subsystem library functions
	*/
	MK_sid_GetAlarmBase,
	MK_sid_GetScheduleTableStatus,

	/* Microkernel library functions
	*/
	MK_sid_GetApplicationId,
	MK_sid_GetApplicationState,
	MK_sid_GetEvent,

	/* Microkernel pseudo-services
	*/
	MK_sid_ExceptionHandling,
	MK_sid_UnknownService,
	MK_sid_InvalidServiceId,
	MK_sid_nsid,

	/* Sentinel value which guarantees that this type can represent a certain range of
	 * user-defined values. This sentinel value must not exceed 16 bit.
	*/
	MK_sid_Sentinel = 32767
};

typedef enum mk_serviceid_e mk_serviceid_t;

/* Panic codes
 *
 * These values are passed as parameters to MK_Panic and therefore to MK_PanicStop
 *
 * MK_Panic sets the panicReason (in the core variables) to the first panic that occurs.
 *
 * The values can also be passed to MK_StartupPanic and therefore to MK_USERPANICSTOP. In this
 * case the panicReason does not get modified.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_panic_e
{
	MK_panic_None = 0,
	/*34567890123456789012345678901		31-character symbol length */
	MK_panic_DataSectionsNotInitialized,
	MK_panic_ExceptionNoThread,							/* MK_ExceptionIsSaneXxx */
	MK_panic_ExceptionCurrentThreadNotAtHeadOfQueue,	/* MK_ExceptionIsSaneXxx */
	MK_panic_ExceptionFromKernel,						/* MK_ExceptionIsSaneXxx */
	MK_panic_UnexpectedSystemCall,
	MK_panic_UnexpectedInterrupt,
	MK_panic_UnexpectedThreadWithParent,
	MK_panic_InterruptNoThread,
	MK_panic_CurrentThreadNotAtHeadOfQueue,
	MK_panic_ThreadNotFoundInQueue,
	MK_panic_JobIsNotTask,
	MK_panic_ThreadHasNoJobQueue,
	MK_panic_IncorrectJobSize,
	MK_panic_JobQueueIsFull,
	MK_panic_JqUnexpectedJobQueue,
	MK_panic_UnknownJobType,
	MK_panic_ExpectedHardwareNotFound,					/* Startup */
	MK_panic_ProtectionFaultInProtectionHook,
	MK_panic_PanicFromProtectionHook,
	MK_panic_MemoryPartitionIsTooLarge,					/* Startup */
	MK_panic_IncorrectStartupKey,						/* Startup */
	MK_panic_MpuNotInitializedCorrectly,				/* Startup */
	MK_panic_StartupCheckFailed,						/* Startup */
	MK_panic_InvalidMpuConfiguration,					/* Startup */
	MK_panic_VectorTableIncorrectlyInitialized,			/* Startup */
	MK_panic_CoreNotConfigured,							/* Startup */
	MK_panic_UndocumentedException,
	MK_panic_RegisterStoreIsNotClean,
	MK_panic_ProcessorLimitExceeded,
	MK_panic_MisalignedVectorTable,
	MK_panic_MisalignedSymbol,
	MK_panic_UnexpectedTaskActivationFailure,
	MK_panic_UnexpectedOsApplication,					/* MK_InitApplications */
	MK_panic_InvalidTaskIdInConfiguration,				/* MK_InitApplications */
	MK_panic_InvalidInterruptLevel,						/* ARM / VIM-specific */
	MK_panic_FaultVimDetected,							/* ARM / VIM-specific */
	MK_panic_UnexpectedExceptionLevel,					/* RH850-specific */
	MK_panic_UnexpectedHardwareResponse,
	MK_panic_InsufficientResources,
	MK_panic_InsufficientSpaceInJobQueueBuffer,
	MK_panic_InvalidMessageQueueConfiguration,
	MK_panic_InvalidLockConfiguration,
	MK_panic_SyncNotInitializedCorrectly,
	MK_panic_InvalidApplicationState,
	MK_panic_ApplicationRunningWhileTerminated,
	MK_panic_InvalidCrossCoreMessage,
	MK_panic_InvalidSstConfiguration,
	MK_panic_HeapInsufficient,
	MK_panic_HeapWrongMemType,
	MK_panic_PageMapGenerationError,
	MK_panic_InvalidExecBudgetConfiguration,			/* ARM64 / v-timer usage limitation */
	MK_panic_UnexpectedInterruptPriority,				/* CORTEXM-specific */
	MK_panic_IllegalPendSvException,					/* CORTEXM-specific */
	MK_panic_InvalidInterruptRouterConfiguration,		/* CORTEXM-specific */
	Mk_panic_IncorrectTimerConfiguration,



	MK_panic_Unknown	/* Must be last */
};

typedef enum mk_panic_e mk_panic_t;

/* Error information structures.
*/
#define MK_MAXPARAMS	4

typedef struct mk_errorinfo_s mk_errorinfo_t;
typedef struct mk_protectioninfo_s mk_protectioninfo_t;
typedef mk_thread_t *mk_culprit_t;

struct mk_errorinfo_s
{
	mk_serviceid_t serviceId;
	mk_errorid_t errorId;
	mk_osekerror_t osekError;
	mk_objectid_t culpritId;
	mk_objecttype_t culpritType;
	const mk_char_t *culpritName;
	mk_culprit_t culprit;
	mk_parametertype_t parameter[MK_MAXPARAMS];
};

#define MK_ERRORINFO_PARAMETER_INIT	{ 0u, 0u, 0u, 0u }

struct mk_protectioninfo_s
{
	mk_serviceid_t serviceId;
	mk_errorid_t errorId;
	mk_osekerror_t osekError;
	mk_culprit_t culprit;
	mk_objectid_t culpritApplicationId;
};

/* Error information structures
*/
extern mk_errorinfo_t * const MK_errorInfo[MK_MAXCORES];
extern mk_protectioninfo_t * const MK_protectionInfo[MK_MAXCORES];

/* Error code conversion - internal to external
*/
mk_osekerror_t MK_ErrorInternalToOsek(mk_errorid_t);

/* Retrieve service-ID from error-info structure
 *
 * !LINKSTO Microkernel.Function.MK_ErrorGetServiceId, 1
 * !LINKSTO Microkernel.Function.MK_ErrorGetServiceIdForCore, 2
 * !doctype src
*/
mk_serviceid_t MK_ErrorGetServiceIdForCore(mk_objectid_t);
#define MK_ErrorGetServiceId()		MK_ErrorGetServiceIdForCore(-1)

/* Retrieve parameters from error-info structure
 *
 * !LINKSTO Microkernel.Function.MK_ErrorGetParameter, 2
 * !LINKSTO Microkernel.Function.MK_ErrorGetParameterForCore, 3
 * !doctype src
*/
#define MK_ErrorGetParameter(p)		MK_ErrorGetParameterForCore(-1, (p))
mk_parametertype_t MK_ErrorGetParameterForCore(mk_objectid_t, mk_int_t);

/* Get the addresses of the error and protection info structures.
 *
 * !LINKSTO Microkernel.Function.MK_GetErrorInfoForCore, 2
 * !LINKSTO Microkernel.Function.MK_GetProtectionInfoForCore, 2
 * !doctype src
*/
mk_errorinfo_t *MK_GetErrorInfoForCore(mk_objectid_t);
mk_protectioninfo_t *MK_GetProtectionInfoForCore(mk_objectid_t);

#define MK_GetErrorInfo()			MK_GetErrorInfoForCore(-1)
#define MK_GetProtectionInfo()		MK_GetProtectionInfoForCore(-1)

/* Get the panic reason.
 *
 * !LINKSTO Microkernel.Function.MK_GetPanicReasonForCore, 2
 * !doctype src
*/
mk_panic_t MK_GetPanicReasonForCore(mk_objectid_t);

#define MK_GetPanicReason()			MK_GetPanicReasonForCore(-1)

/* Configurable function to call if there's a panic during startup.
*/
typedef void (*mk_paniccallout_t)(mk_panic_t);

#endif

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
