/* Mk_syscallindex.h
 *
 * This file defines the system call indexes used by the kernel.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_SYSCALLINDEX_H
#define MK_SYSCALLINDEX_H

/* Microkernel system call indexes. These indexes MUST match the positions of the corresponding
 * functions in the system call table.
 * We need these indexes in assembly-language so they must be #defines
 *
 * The first batch contains the indexes for microkernel services.
*/
/*		1234567890123456789012345678901	*/	/* Kernel-side function */
#define MK_SC_TerminateSelf				MK_U(0)		/* MK_SysTerminateSelf */
#define MK_SC_ActivateTask				MK_U(1)		/* MK_SysActivateTask */
#define MK_SC_ChainTask					MK_U(2)		/* MK_SysChainTask */
#define MK_SC_Schedule					MK_U(3)		/* MK_SysSchedule */
#define MK_SC_AcquireLock				MK_U(4)		/* MK_SysAcquireLock */
#define MK_SC_ReleaseLock				MK_U(5)		/* MK_SysReleaseLock */
#define MK_SC_Shutdown					MK_U(6)		/* MK_SysShutdown */
#define MK_SC_StartOs					MK_U(7)		/* MK_SysStartOs */
#define MK_SC_SetEvent					MK_U(8)		/* MK_SysSetEvent */
#define MK_SC_ClearEvent				MK_U(9)		/* MK_SysClearEvent */
#define MK_SC_WaitEvent					MK_U(10)	/* MK_SysWaitEvent */
#define MK_SC_WaitGetClearEvent			MK_U(11)	/* MK_SysWaitEvent (alias) */
#define MK_SC_GetTaskId					MK_U(12)	/* MK_SysGetTaskId */
#define MK_SC_GetTaskState				MK_U(13)	/* MK_SysGetTaskState */
#define MK_SC_GetIsrId					MK_U(14)	/* MK_SysGetIsrId */
#define MK_SC_ReportError				MK_U(15)	/* MK_SysReportError */
#define MK_SC_CallCtrSub				MK_U(16)	/* MK_SysCallCtrSub */
#define MK_SC_CallTrustedFunction		MK_U(17)	/* MK_SysCallTrustedFunction */
#define MK_SC_AllowAccess				MK_U(18)	/* MK_SysAllowAccess */
#define MK_SC_TerminateApplication		MK_U(19)	/* MK_SysTerminateApplication */
#define MK_SC_EnableInterruptSource		MK_U(20)	/* MK_SysEnableInterruptSource */
#define MK_SC_DisableInterruptSource	MK_U(21)	/* MK_SysDisableInterruptSource */
#define MK_SC_AddOnControl				MK_U(22)	/* MK_SysAddOnControl */
#define MK_SC_AsyncActivateTask			MK_U(23)	/* MK_SysAsyncActivateTask */
#define MK_SC_AsyncSetEvent				MK_U(24)	/* MK_SysAsyncSetEvent */
#define MK_SC_AsyncCallCtrSub			MK_U(25)	/* MK_SysAsyncCallCtrSub */
#define MK_SC_StartCore					MK_U(26)	/* MK_SysStartCore */
#define MK_SC_ShutdownAllCores			MK_U(27)	/* MK_SysShutdownAllCores */
#define MK_SC_SstStartCounter			MK_U(28)	/* MK_SysSstStartCounter */
#define MK_SC_SstAdvanceCounter			MK_U(29)	/* MK_SysSstAdvanceCounter */
#define MK_SC_SstStopCounter			MK_U(30)	/* MK_SysSstStopCounter */
#define MK_SC_GetAppModeVoteOfCore		MK_U(31)	/* MK_SysGetAppModeVoteOfCore */

#define MK_NSYSCALL						MK_U(32)	/* Number of direct microkernel system calls */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
