/* Os_error.h
 *
 * Error handling.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.4 (advisory)
 * A project should not contain unused tag declarations.
 *
 * Reason:
 * While the os_enum_e is not used directly, its values are used for readability.
*/

#ifndef OS_ERROR_H
#define OS_ERROR_H

#include <Os_types.h>

/*!
 * OS_SID_xxx
 *
 * Service IDs for all system services and other areas that can generate
 * errors.
 *
 * os_serviceid_t is the data type that holds one of these.
 *
 * These OS_SID_ macros are parsed by asc_Os/tools/errdb-to-c.pl, so their values
 * must be in one of two formats:
 *  - a literal decimal number, without parenthesis or type suffix
 *  - a simple expression of the form (sid+number), where sid is a
 *    previously-defined OS_SID_ macro, and number is a literal
 *    decimal number, without parenthesis or type suffix
*/
/* AUTOSAR-defined service ids */
#define OS_SID_GetApplicationId				OS_U(0)
#define OS_SID_GetIsrId						OS_U(1)
#define OS_SID_CallTrustedFunction			OS_U(2)
#define OS_SID_CheckIsrMemoryAccess			OS_U(3)
#define OS_SID_CheckTaskMemoryAccess		OS_U(4)
#define OS_SID_CheckObjectAccess			OS_U(5)
#define OS_SID_CheckObjectOwnership			OS_U(6)
#define OS_SID_StartScheduleTableRel		OS_U(7)
#define OS_SID_StartScheduleTableAbs		OS_U(8)
#define OS_SID_StopScheduleTable			OS_U(9)
#define OS_SID_ChainScheduleTable			OS_U(10)
#define OS_SID_StartScheduleTableSynchron	OS_U(11)
#define OS_SID_SyncScheduleTable			OS_U(12)
#define OS_SID_SetScheduleTableAsync		OS_U(13)
#define OS_SID_GetScheduleTableStatus		OS_U(14)
#define OS_SID_IncrementCounter				OS_U(15)
#define OS_SID_GetCounterValue				OS_U(16)
#define OS_SID_GetElapsedCounterValue		OS_U(17)
#define OS_SID_TerminateApplication			OS_U(18)
#define OS_SID_AllowAccess					OS_U(19)
#define OS_SID_GetApplicationState			OS_U(20)
/* OSEK API and others */
#define OS_SID_UnknownSyscall				OS_U(21)
#define OS_SID_ActivateTask					OS_U(22)
#define OS_SID_TerminateTask				OS_U(23)
#define OS_SID_ChainTask					OS_U(24)
#define OS_SID_Schedule						OS_U(25)
#define OS_SID_GetTaskId					OS_U(26)
#define OS_SID_GetTaskState					OS_U(27)
#define OS_SID_SuspendInterrupts			OS_U(28)
#define OS_SID_ResumeInterrupts				OS_U(29)
#define OS_SID_GetResource					OS_U(30)
#define OS_SID_ReleaseResource				OS_U(31)
#define OS_SID_SetEvent						OS_U(32)
#define OS_SID_ClearEvent					OS_U(33)
#define OS_SID_GetEvent						OS_U(34)
#define OS_SID_WaitEvent					OS_U(35)
#define OS_SID_GetAlarmBase					OS_U(36)
#define OS_SID_GetAlarm						OS_U(37)
#define OS_SID_SetRelAlarm					OS_U(38)
#define OS_SID_SetAbsAlarm					OS_U(39)
#define OS_SID_CancelAlarm					OS_U(40)
#define OS_SID_GetActiveApplicationMode		OS_U(41)
#define OS_SID_StartOs						OS_U(42)
#define OS_SID_ShutdownOs					OS_U(43)
#define OS_SID_GetStackInfo					OS_U(44)
#define OS_SID_DisableInterruptSource		OS_U(45)
#define OS_SID_EnableInterruptSource		OS_U(46)
#define OS_SID_TryToGetSpinlock				OS_U(47)
#define OS_SID_ReleaseSpinlock				OS_U(48)
#define OS_SID_ShutdownAllCores				OS_U(49)
#define OS_SID_ActivateTaskAsyn				OS_U(50)
#define OS_SID_SetEventAsyn					OS_U(51)
#define OS_SID_ClearPendingInterrupt		OS_U(52)
#define OS_SID_ControlIdle					OS_U(53)
#define OS_SID_GetCurrentApplicationId		OS_U(54)
/* Insert additional system services here and adjust OS_SID_XXX to match */
#define OS_SID_XXX							OS_U(55)
#define OS_SID_Dispatch						(OS_SID_XXX+(OS_U(0)))
#define OS_SID_TrapHandler					(OS_SID_XXX+(OS_U(1)))
#define OS_SID_IsrHandler					(OS_SID_XXX+(OS_U(2)))
#define OS_SID_RunSchedule					(OS_SID_XXX+(OS_U(3)))
#define OS_SID_KillAlarm					(OS_SID_XXX+(OS_U(4)))
#define OS_SID_TaskReturn					(OS_SID_XXX+(OS_U(5)))
#define OS_SID_HookHandler					(OS_SID_XXX+(OS_U(6)))
#define OS_SID_ArchTrapHandler				(OS_SID_XXX+(OS_U(7)))
#define OS_SID_MemoryManagement				(OS_SID_XXX+(OS_U(8)))
/* Insert additional internal functions here and adjust OS_N_SIDS to match */
#define OS_N_SIDS							(OS_SID_XXX+(OS_U(9)))

/*!
 * OS_ERROR_xxx
 *
 * Error conditions. Multiple services can use the same error
 * condition, but any one service must use a unique error condition
 * for each error detected.
 *
 * os_error_t is the data type that holds one of these.
 * os_errorresult_t is the data type that holds one of these but must also be capable of holding the same range of
 *                  values as os_result_t because the code might get translated.
*/
#ifndef OS_ASM
/* Deviation MISRAC2012-1 <+1> */
enum os_error_e
{
	OS_ERROR_NoError = 0,			/* Same as UnknownError */
	OS_ERROR_UnknownError = 0,
	OS_ERROR_UnknownSystemCall = 1,
	OS_ERROR_InvalidTaskId = 2,
	OS_ERROR_Quarantined = 3,
	OS_ERROR_MaxActivations = 4,
	OS_ERROR_WriteProtect = 5,
	OS_ERROR_InvalidAlarmId = 6,
	OS_ERROR_InvalidAlarmState = 7,
	OS_ERROR_AlarmNotInUse = 8,
	OS_ERROR_WrongContext = 9,
	OS_ERROR_HoldsResource = 10,
	OS_ERROR_NoEvents = 11,
	OS_ERROR_TaskNotExtended = 12,
	OS_ERROR_InvalidCounterId = 13,
	OS_ERROR_ParameterOutOfRange = 14,
	OS_ERROR_AlarmInUse = 15,
	OS_ERROR_InvalidStartMode = 16,
	OS_ERROR_AlarmNotInQueue = 17,
	OS_ERROR_InvalidResourceId = 18,
	OS_ERROR_ResourceInUse = 19,
	OS_ERROR_ResourcePriorityError = 20,
	OS_ERROR_ResourceNestingError = 21,
	OS_ERROR_TaskSuspended = 22,
	OS_ERROR_NestingUnderflow = 23,
	OS_ERROR_NestingOverflow = 24,
	OS_ERROR_NonfatalException = 25,
	OS_ERROR_FatalException = 26,
	OS_ERROR_TaskTimeBudgetExceeded = 27,
	OS_ERROR_IsrTimeBudgetExceeded = 28,
	OS_ERROR_Permission = 29,
	OS_ERROR_ImplicitSyncStartRel = 30,
	OS_ERROR_CounterIsHw = 31,
	OS_ERROR_InvalidScheduleId = 32,
	OS_ERROR_NotRunning = 33,
	OS_ERROR_NotStopped = 34,
	OS_ERROR_InvalidObjectType = 35,
	OS_ERROR_InvalidObjectId = 36,
	OS_ERROR_InvalidApplicationId = 37,
	OS_ERROR_InvalidIsrId = 38,
	OS_ERROR_InvalidMemoryRegion = 39,
	OS_ERROR_NotChained = 40,
	OS_ERROR_InvalidFunctionId = 41,
	OS_ERROR_NotSyncable = 42,
	OS_ERROR_StackError = 43,
	OS_ERROR_RateLimitExceeded = 44,
	OS_ERROR_InterruptDisabled = 45,
	OS_ERROR_ReturnFromTask = 46,
	OS_ERROR_InsufficientStack = 47,
	OS_ERROR_ArithmeticTrap = 48,
	OS_ERROR_MemoryProtection = 49,
	OS_ERROR_NotTrusted = 50,
	OS_ERROR_TaskResLockTimeExceeded = 51,
	OS_ERROR_IsrResLockTimeExceeded = 52,
	OS_ERROR_TaskIntLockTimeExceeded = 53,
	OS_ERROR_IsrIntLockTimeExceeded = 54,
	OS_ERROR_IncrementZero = 55,
	OS_ERROR_DifferentCounters = 56,
	OS_ERROR_ScheduleTableNotIdle = 57,
	OS_ERROR_InvalidRestartOption = 58,
	OS_ERROR_KernelStackOverflow = 59,
	OS_ERROR_TaskStackOverflow = 60,
	OS_ERROR_UnknownException = 61,
	OS_ERROR_UndefinedInstruction = 62,
	OS_ERROR_NMI = 63,
	OS_ERROR_DebugInterface = 64,
	OS_ERROR_FpuException = 65,
	OS_ERROR_PrefetchAbort = 66,
	OS_ERROR_DataAbort = 67,
	OS_ERROR_IllegalSupervisorCall = 68,
	OS_ERROR_IllegalInterrupt = 69,

	/* error codes for Cortex-M exceptions */
	OS_ERROR_NonMaskableInterrupt = 70,
	OS_ERROR_HardFault = 71,
	OS_ERROR_MemoryManagement = 72,
	OS_ERROR_BusFault = 73,
	OS_ERROR_UsageFault = 74,
	OS_ERROR_ReservedException_1 = 75,
	OS_ERROR_ReservedException_2 = 76,
	OS_ERROR_ReservedException_3 = 77,
	OS_ERROR_ReservedException_4 = 78,
	OS_ERROR_SupervisorCall = 79,
	OS_ERROR_DebugMonitor = 80,
	OS_ERROR_ReservedException_5 = 81,
	OS_ERROR_PendingSupervisorCall = 82,
	OS_ERROR_SystemTick = 83,
	
	/* error codes for RH850 */
	OS_ERROR_SysErr = 84,
	OS_ERROR_HVTrap = 85,
	OS_ERROR_FETrap = 86,
	OS_ERROR_Trap = 87,
	OS_ERROR_ReservedInstruction = 88,
	OS_ERROR_CoprocessorUnusable = 89,
	OS_ERROR_PrivilegedInstruction = 90,
	OS_ERROR_MisalignedAccess = 91,
	OS_ERROR_FEINT = 92,
	
	OS_ERROR_InvalidSpinlockId = 93,
	OS_ERROR_InvalidSpinlockNesting = 94,
	OS_ERROR_SpinlockAlreadyHeld = 95,
	OS_ERROR_SpinlockInterferenceDeadlock = 96,
	OS_ERROR_CoreIsDown = 97,
	OS_ERROR_InvalidCoreId = 98,
	OS_ERROR_ApplicationNotAccessible = 99,
	OS_ERROR_ApplicationNotRestarting = 100,
	OS_ERROR_HoldsLock = 101,
	OS_ERROR_SpinlockNotOccupied = 102,
	OS_ERROR_CallTrustedFunctionCrosscore = 103,

	/* error codes for ARC exceptions */
	OS_ERROR_MemoryError = 104,
	OS_ERROR_InstructionError = 105,
	OS_ERROR_EV_MachineCheck = 106,
	OS_ERROR_EV_TLBMissI = 107,
	OS_ERROR_EV_TLBMissD = 108,
	OS_ERROR_EV_ProtV = 109,
	OS_ERROR_EV_PrivilegeV = 110,
	OS_ERROR_EV_SWI = 111,
	OS_ERROR_EV_Trap = 112,
	OS_ERROR_EV_Extension = 113,
	OS_ERROR_EV_DivZero = 114,
	OS_ERROR_EV_DCError = 115,
	OS_ERROR_EV_Misaligned = 116,
	OS_ERROR_EV_VecUnit = 117,

	/* error codes for 4.4 */
	OS_ERROR_ISRAlreadyDisabled = 118,
	OS_ERROR_ISRAlreadyEnabled = 119,
	OS_ERROR_InvalidIdleMode = 120
};

typedef os_uint8_t os_error_t;
typedef os_uint8_t os_errorresult_t;
#endif

/*!
 * OS_ACTION_*
 *
 * Error actions
 *
 * os_erroraction_t is the data type that holds one of these
*/
#define OS_ACTION_MASK			OS_U(0x0f)	/* Mask for the Action field */
#define OS_ACTION_IGNORE		OS_U(0x00)	/* Ignore totally - return OK */
#define OS_ACTION_RETURN		OS_U(0x01)	/* Return result to caller */
#define OS_ACTION_KILL			OS_U(0x02)	/* Kill task or ISR */
#define OS_ACTION_QUARANTINE	OS_U(0x03)	/* Quarantine task or ISR */
#define OS_ACTION_QUARANTINEAPP	OS_U(0x04)	/* Quarantine Application */
#define OS_ACTION_RESTART		OS_U(0x05)	/* Kill and restart application */
#define OS_ACTION_SHUTDOWN		OS_U(0x06)	/* Shut down OS */
#define OS_ACTION_DONOTHING		OS_U(0xfe)	/* "Do nothing". Only for use as return value from ProtectionHook */
#define OS_ACTION_DEFAULT		OS_U(0xff)	/* Use default action. Only for use as return value from ProtectionHook */

#define OS_ActionIsValid(act)	((act)<=OS_ACTION_SHUTDOWN)

#define OS_ACTION_HOOK				OS_U(0xe0)	/* Mask for all autosar hooks */
#define OS_ACTION_HOOK_EB			OS_U(0xf0)	/* Mask for all hooks, including EB extensions */
#define OS_ACTION_NOHOOK			OS_U(0x00)	/* Use no hooks ;-) */
#define OS_ACTION_PROTECTIONHOOK	OS_U(0x80)	/* Call ProtectionHook */
#define OS_ACTION_ERRORHOOK			OS_U(0x40)	/* Call global ErrorHook */
#define OS_ACTION_ERRORHOOK_APP		OS_U(0x20)	/* Call application's ErrorHook */
#define OS_ACTION_ERRORHOOK_EB		OS_U(0x10)	/* Call global ErrorHook, only when EB extension is configured */

#ifndef OS_ASM
typedef os_uint8_t os_erroraction_t;

/* Configuration constant - which error hooks really get called, etc.
*/
extern const os_erroraction_t OS_hookSelection;
#endif

/*!
 * os_errorentry_t
 *
 * This is the data structure that drives the OS error handling
 * mechanism. The fields are in a strange order to optimise the
 * size of the struct, since we'll have rather a lot of them.
*/
#ifndef OS_ASM
typedef struct os_errorentry_s os_errorentry_t;

struct os_errorentry_s
{
	os_result_t			result;		/* result code for hooks and return */
	os_error_t			condition;	/* error condition */
	os_erroraction_t	action;		/* action to take */
};

#endif

/*!
 * os_errorstatus_t
 *
 * This structure is used by the kernel to store all the information
 * about the most recent error. The error hook function can use
 * OS_GetKernelData()->errorStatus to copy its contents into a user-
 * supplied area.
*/
#define OS_MAXPARAM		OS_U(3)		/* Largest no. of parameters to a service */

#ifndef OS_ASM
typedef struct os_errorstatus_s os_errorstatus_t;

struct os_errorstatus_s
{
	os_paramtype_t parameter[OS_MAXPARAM];		/* Parameters */
	os_result_t result;			/* return value from service */
	os_erroraction_t action;	/* Action to take */
	os_uint8_t calledFrom;		/* INTASK, INCAT1 etc. */
	os_serviceid_t serviceId;	/* OS_SID_xxx */
	os_error_t errorCondition;	/* OS_ERROR_xxx */
};
#define OS_ERRORSTATUS_INIT					\
	{										\
		{ 0u, 0u, 0u },	/*parameter*/		\
		0u,				/*result*/			\
		0u,				/*action*/			\
		0u,				/*calledFrom*/		\
		0u,				/*serviceId*/		\
		0u				/*errorCondition*/	\
	}

#endif

/*!
 * os_serviceinfo_t
 *
 * This structure is used when calling OS_Error to pass the service ID and
 * the associated error table to the error handler.
*/
#ifndef OS_ASM
typedef struct os_serviceinfo_s os_serviceinfo_t;

struct os_serviceinfo_s
{
	os_errorentry_t const *errorTable;
	os_serviceid_t sid;
	os_uint8_t nErrors;
};

extern const os_serviceinfo_t OS_svc_ActivateTask;
extern const os_serviceinfo_t OS_svc_ActivateTaskAsyn;
extern const os_serviceinfo_t OS_svc_AllowAccess;
extern const os_serviceinfo_t OS_svc_IncrementCounter;
extern const os_serviceinfo_t OS_svc_CallTrustedFunction;
extern const os_serviceinfo_t OS_svc_CancelAlarm;
extern const os_serviceinfo_t OS_svc_ChainScheduleTable;
extern const os_serviceinfo_t OS_svc_ChainTask;
extern const os_serviceinfo_t OS_svc_CheckIsrMemoryAccess;
extern const os_serviceinfo_t OS_svc_CheckObjectAccess;
extern const os_serviceinfo_t OS_svc_CheckObjectOwnership;
extern const os_serviceinfo_t OS_svc_CheckTaskMemoryAccess;
extern const os_serviceinfo_t OS_svc_ClearPendingInterrupt;
extern const os_serviceinfo_t OS_svc_ClearEvent;
extern const os_serviceinfo_t OS_svc_ControlIdle;
extern const os_serviceinfo_t OS_svc_DisableInterruptSource;
extern const os_serviceinfo_t OS_svc_Dispatch;
extern const os_serviceinfo_t OS_svc_EnableInterruptSource;
extern const os_serviceinfo_t OS_svc_GetActiveApplicationMode;
extern const os_serviceinfo_t OS_svc_GetAlarm;
extern const os_serviceinfo_t OS_svc_GetAlarmBase;
extern const os_serviceinfo_t OS_svc_GetApplicationId;
extern const os_serviceinfo_t OS_svc_GetApplicationState;
extern const os_serviceinfo_t OS_svc_GetCounterValue;
extern const os_serviceinfo_t OS_svc_GetCurrentApplicationId;
extern const os_serviceinfo_t OS_svc_GetElapsedCounterValue;
extern const os_serviceinfo_t OS_svc_GetEvent;
extern const os_serviceinfo_t OS_svc_GetIsrId;
extern const os_serviceinfo_t OS_svc_GetResource;
extern const os_serviceinfo_t OS_svc_GetScheduleTableStatus;
extern const os_serviceinfo_t OS_svc_GetStackInfo;
extern const os_serviceinfo_t OS_svc_GetTaskId;
extern const os_serviceinfo_t OS_svc_GetTaskState;
extern const os_serviceinfo_t OS_svc_HookHandler;
extern const os_serviceinfo_t OS_svc_IsrHandler;
extern const os_serviceinfo_t OS_svc_KillAlarm;
extern const os_serviceinfo_t OS_svc_MemoryManagement;
extern const os_serviceinfo_t OS_svc_ReleaseResource;
extern const os_serviceinfo_t OS_svc_ReleaseSpinlock;
extern const os_serviceinfo_t OS_svc_ResumeInterrupts;
extern const os_serviceinfo_t OS_svc_RunSchedule;
extern const os_serviceinfo_t OS_svc_Schedule;
extern const os_serviceinfo_t OS_svc_SetAbsAlarm;
extern const os_serviceinfo_t OS_svc_SetEvent;
extern const os_serviceinfo_t OS_svc_SetEventAsyn;
extern const os_serviceinfo_t OS_svc_SetRelAlarm;
extern const os_serviceinfo_t OS_svc_SetScheduleTableAsync;
extern const os_serviceinfo_t OS_svc_ShutdownAllCores;
extern const os_serviceinfo_t OS_svc_ShutdownOs;
extern const os_serviceinfo_t OS_svc_StartOs;
extern const os_serviceinfo_t OS_svc_StartScheduleTableRel;
extern const os_serviceinfo_t OS_svc_StartScheduleTableAbs;
extern const os_serviceinfo_t OS_svc_StartScheduleTableSynchron;
extern const os_serviceinfo_t OS_svc_StopScheduleTable;
extern const os_serviceinfo_t OS_svc_SuspendInterrupts;
extern const os_serviceinfo_t OS_svc_SyncScheduleTable;
extern const os_serviceinfo_t OS_svc_TaskReturn;
extern const os_serviceinfo_t OS_svc_TerminateApplication;
extern const os_serviceinfo_t OS_svc_TerminateTask;
extern const os_serviceinfo_t OS_svc_TrapHandler;
extern const os_serviceinfo_t OS_svc_TryToGetSpinlock;
extern const os_serviceinfo_t OS_svc_UnknownSID;
extern const os_serviceinfo_t OS_svc_UnknownSyscall;
extern const os_serviceinfo_t OS_svc_WaitEvent;

extern const os_serviceinfo_t OS_svc_ArchTrapHandler;

#endif /* OS_ASM */

#endif /* OS_ERROR_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
