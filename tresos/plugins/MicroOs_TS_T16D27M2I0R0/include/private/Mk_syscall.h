/* Mk_syscall.h - system call handling
 *
 * This file contains definitions for the microkernel's software system call handling.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_SYSCALL_H
#define MK_SYSCALL_H

#include <public/Mk_syscallindex.h>
#include <private/Mk_core.h>

/* This macro specifies the system call number which is used
 * for non-implemented system calls (or calls not implemented
 * as system calls but functions).
*/
#define MK_SC_NOT_IMPLEMENTED			MK_NSYSCALL

/* These are not implemented as system calls!
*/
#define MK_SC_GetActiveApplicationMode	MK_SC_NOT_IMPLEMENTED
#define MK_SC_GetAlarmBase				MK_SC_NOT_IMPLEMENTED	/* Implemented as OS function */
#define MK_SC_GetElapsedCounterValue	MK_SC_NOT_IMPLEMENTED	/* Implemented as function calling GetCounterValue */
#define MK_SC_GetScheduleTableStatus	MK_SC_NOT_IMPLEMENTED

#define MK_SC_GetStackInfo				MK_SC_NOT_IMPLEMENTED
#define MK_SC_InitCpuLoad				MK_SC_NOT_IMPLEMENTED
#define MK_SC_GetCpuLoad				MK_SC_NOT_IMPLEMENTED

#define MK_SC_CheckIsrMemoryAccess		MK_SC_NOT_IMPLEMENTED
#define MK_SC_CheckTaskMemoryAccess		MK_SC_NOT_IMPLEMENTED
#define MK_SC_CheckObjectAccess			MK_SC_NOT_IMPLEMENTED
#define MK_SC_CheckObjectOwnership		MK_SC_NOT_IMPLEMENTED

#ifndef MK_ELIMINATE_UNDEFINED_BITS
/* Macro to eliminate undefined bits, i.e. replace them with defined values, when reading a system
 * call parameter that holds a value of a (typically smaller) data type.
 * The default implementation assumes no undefined bits and therefore does not change the value.
*/
#define MK_ELIMINATE_UNDEFINED_BITS(type, value)		(value)
#endif

#ifndef MK_ASM

/* Type and global constant for the software system call table
*/
typedef void (* mk_syscallfptr_t)(mk_kernelcontrol_t *);

extern mk_syscallfptr_t const MK_syscallTable[MK_NSYSCALL+1];

/* The system call handler. This is normally called by the
 * kernel entry code (assembly language)
*/
void MK_Syscall(void);

/* Error handler for unknown system calls.
 * Is called from the system call handler if the index is out of range, and
 * can also be used for unused entries in the table.
*/
void MK_UnknownSyscall(mk_kernelcontrol_t *);

/* These are the individual system call functions
*/
void MK_SysActivateTask(mk_kernelcontrol_t *);
void MK_SysCallTrustedFunction(mk_kernelcontrol_t *);
void MK_SysChainTask(mk_kernelcontrol_t *);
void MK_SysClearEvent(mk_kernelcontrol_t *);
void MK_SysGetIsrId(mk_kernelcontrol_t *);
void MK_SysAcquireLock(mk_kernelcontrol_t *);
void MK_SysGetTaskId(mk_kernelcontrol_t *);
void MK_SysGetTaskState(mk_kernelcontrol_t *);
void MK_SysReleaseLock(mk_kernelcontrol_t *);
void MK_SysReportError(mk_kernelcontrol_t *);
void MK_SysSchedule(mk_kernelcontrol_t *);
void MK_SysSetEvent(mk_kernelcontrol_t *);
void MK_SysShutdown(mk_kernelcontrol_t *);
void MK_SysCallCtrSub(mk_kernelcontrol_t *);
void MK_SysStartOs(mk_kernelcontrol_t *);
void MK_SysTerminateApplication(mk_kernelcontrol_t *);
void MK_SysAllowAccess(mk_kernelcontrol_t *);
void MK_SysTerminateSelf(mk_kernelcontrol_t *);
void MK_SysWaitEvent(mk_kernelcontrol_t *);
void MK_SysEnableInterruptSource(mk_kernelcontrol_t *);
void MK_SysDisableInterruptSource(mk_kernelcontrol_t *);
void MK_SysStartCore(mk_kernelcontrol_t *);
void MK_SysAddOnControl(mk_kernelcontrol_t *);
void MK_SysShutdownAllCores(mk_kernelcontrol_t *);

void MK_SysAsyncActivateTask(mk_kernelcontrol_t *);
void MK_SysAsyncSetEvent(mk_kernelcontrol_t *);
void MK_SysAsyncCallCtrSub(mk_kernelcontrol_t *);

void MK_SysSstStartCounter(mk_kernelcontrol_t *);
void MK_SysSstAdvanceCounter(mk_kernelcontrol_t *);
void MK_SysSstStopCounter(mk_kernelcontrol_t *);

void MK_SysGetAppModeVoteOfCore(mk_kernelcontrol_t *);

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
