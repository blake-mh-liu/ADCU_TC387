/* Mk_configuration_syscall.c
 *
 * This file contains the configured system call table for the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_syscall.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

#if MK_CFG_NTRUSTEDFUNCTIONS <= 0
#define MK_SYSCALLTRUSTEDFUNCTION	MK_UnknownSyscall
#else
#define MK_SYSCALLTRUSTEDFUNCTION	MK_SysCallTrustedFunction
#endif

#if MK_CFG_NADDONS > 0
#define MK_SYSADDONCONTROL			MK_SysAddOnControl
#else
#define MK_SYSADDONCONTROL			MK_UnknownSyscall
#endif

#if MK_MAXCORES <= 1
#define MK_SYSSTARTCORE				MK_UnknownSyscall
#define MK_SYSSHUTDOWNALLCORES		MK_SysShutdown
#define MK_SYSASYNCACTIVATETASK		MK_SysActivateTask
#define MK_SYSASYNCSETEVENT			MK_SysSetEvent
#else
#define MK_SYSSTARTCORE				MK_SysStartCore
#define MK_SYSSHUTDOWNALLCORES		MK_SysShutdownAllCores
#define MK_SYSASYNCACTIVATETASK		MK_SysAsyncActivateTask
#define MK_SYSASYNCSETEVENT			MK_SysAsyncSetEvent
#endif

/* Enable linker optimization: add SST syscalls only, when at least one sst is configured.
*/
#if MK_CFG_NSSTS <= 0
#define MK_SYSSSTSTARTCOUNTER		MK_UnknownSyscall
#define MK_SYSSSTADVANCECOUNTER		MK_UnknownSyscall
#define MK_SYSSSTSTOPCOUNTER		MK_UnknownSyscall
#else
#define MK_SYSSSTSTARTCOUNTER		MK_SysSstStartCounter
#define MK_SYSSSTADVANCECOUNTER		MK_SysSstAdvanceCounter
#define MK_SYSSSTSTOPCOUNTER		MK_SysSstStopCounter
#endif

/* System call table
 *
 * At the moment this table contains fixed entries, i.e. all system calls are
 * populated.
*/
/* !LINKSTO Microkernel.SystemCall.Table, 1
 * !doctype src
*/
mk_syscallfptr_t const MK_syscallTable[MK_NSYSCALL+1] =
{
	MK_SysTerminateSelf,
	MK_SysActivateTask,
	MK_SysChainTask,
	MK_SysSchedule,
	MK_SysAcquireLock,
	MK_SysReleaseLock,
	MK_SysShutdown,
	MK_SysStartOs,
	MK_SysSetEvent,
	MK_SysClearEvent,
	MK_SysWaitEvent,
	MK_SysWaitEvent,		/* Implements MK_WaitGetClearEvent */
	MK_SysGetTaskId,
	MK_SysGetTaskState,
	MK_SysGetIsrId,
	MK_SysReportError,
	MK_SysCallCtrSub,
	MK_SYSCALLTRUSTEDFUNCTION,
	MK_SysAllowAccess,
	MK_SysTerminateApplication,
	MK_SysEnableInterruptSource,
	MK_SysDisableInterruptSource,
	MK_SYSADDONCONTROL,
	MK_SYSASYNCACTIVATETASK,
	MK_SYSASYNCSETEVENT,
	MK_SysAsyncCallCtrSub,
	MK_SYSSTARTCORE,
	MK_SYSSHUTDOWNALLCORES,
	MK_SYSSSTSTARTCOUNTER,
	MK_SYSSSTADVANCECOUNTER,
	MK_SYSSSTSTOPCOUNTER,
	MK_SysGetAppModeVoteOfCore,
	MK_UnknownSyscall				/* Must be last - for checking that the table is full. */
};

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
