/* Mk_c0_cfg.h
 *
 * This file contains the declaration of the configuration for core 0.
 *
 * If core 0 is not in use, all its configuration items map to MK_NULL.
 *
 * If core 0 is in use, its configuration items map to the appropriate structures etc. The optional items
 * are defined as MK_NULL if not enabled.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_C0_CFG_H
#define MK_C0_CFG_H		1

#include <Mk_kconfig.h>

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_task.h>
#include <private/Mk_isr.h>
#include <private/Mk_lock.h>
#include <private/Mk_message.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_trustedfunction.h>
#include <private/Mk_application.h>
#include <private/Mk_sst.h>

#if MK_HASHEAP
#include <private/Mk_heap.h>
#endif

#include <Mk_Cfg.h>

#if (MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) != 0
#include <configuration/Mk_c0_defaults.h>
#endif

#ifndef MK_CFG_C0_NSSTS
#define MK_CFG_C0_NSSTS 0
#endif

#if (MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) == 0

/* Core 0 is not in use - define all pointers as NULL and all other parameters as harmless values.
*/
#define MK_CFG_C0_COREVARS					MK_NULL
#define MK_CFG_C0_SYNCSPOT					MK_NULL
#define MK_CFG_C0_KERNSPINITIAL				MK_NULL
#define MK_CFG_C0_PROPERTIES				0u

#define MK_CFG_C0_THRCFG_IDLE				MK_NULL
#define MK_CFG_C0_THRCFG_SHUTDOWN			MK_NULL
#define MK_CFG_C0_THRCFG_BOOT				MK_NULL
#define MK_CFG_C0_THRCFG_INIT				MK_NULL

#define MK_CFG_C0_THREAD_IDLE				MK_NULL
#define MK_CFG_C0_THREAD_AUX1				MK_NULL
#define MK_CFG_C0_THREAD_AUX2				MK_NULL

#define MK_CFG_C0_THRCFG_CTRSUB				MK_NULL
#define MK_CFG_C0_THRCFG_TRUSTEDFUNCTION	MK_NULL

#define MK_CFG_C0_THRCFG_ERRORHOOK			MK_NULL
#define MK_CFG_C0_THREAD_ERRORHOOK			MK_NULL

#define MK_CFG_C0_THRCFG_PROTECTIONHOOK		MK_NULL
#define MK_CFG_C0_THREAD_PROTECTIONHOOK		MK_NULL

#define MK_CFG_C0_THRCFG_SHUTDOWNHOOK		MK_NULL

#define MK_CFG_C0_ERRORINFO					MK_NULL
#define MK_CFG_C0_PROTECTIONINFO			MK_NULL
#define MK_CFG_C0_EXCEPTIONINFO				MK_NULL
#define MK_CFG_C0_PANICEXCEPTIONINFO		MK_NULL

#define MK_CFG_C0_NLOCKS					0
#define MK_CFG_C0_LOCKTABLE					MK_NULL

#define MK_CFG_C0_NJOBQUEUES				0
#define MK_CFG_C0_JOBQUEUE					MK_NULL
#define MK_CFG_C0_JOBQUEUECFG				MK_NULL
#define MK_CFG_C0_JOBQUEUEBUFLEN			0
#define MK_CFG_C0_JOBQUEUEBUFFER			MK_NULL

#define MK_CFG_C0_ORTI_RUNNING_THREAD		MK_NULL

#define MK_CFG_C0_NMEMORYPARTITIONS			0
#define MK_CFG_C0_FIRST_MEMORYPARTITION		0

#ifndef MK_CFG_C0_MSG_INVALIDHANDLER
#define MK_CFG_C0_MSG_INVALIDHANDLER		MK_NULL
#endif

#ifndef MK_CFG_C0_HAS_ERRORHOOK
#define MK_CFG_C0_HAS_ERRORHOOK				0
#endif

#ifndef MK_CFG_C0_HAS_PROTECTIONHOOK
#define MK_CFG_C0_HAS_PROTECTIONHOOK		0
#endif

#ifndef MK_CFG_C0_HAS_CTRSUB
#define MK_CFG_C0_HAS_CTRSUB				0
#endif

#ifndef MK_CFG_C0_HAS_SHUTDOWNHOOK
#define MK_CFG_C0_HAS_SHUTDOWNHOOK			0
#endif

#ifndef MK_CFG_C0_HAS_TRUSTEDFUNCTION
#define MK_CFG_C0_HAS_TRUSTEDFUNCTION		0
#endif

/* These declarations just exist to avoid violating MISRA-C:2012 rule 8.4. */
#ifndef MK_ASM
extern const mk_uint8_t MK_c0_NOT_USED;
extern const mk_uint8_t MK_c0_noAux1Stack;
extern const mk_uint8_t MK_c0_noAux2Stack;
extern const mk_uint8_t MK_c0_sst_NOT_USED;
extern const mk_uint8_t MK_c0_noIdleShutdownStack;
extern const mk_uint8_t MK_c0_noKernelStack;
extern const mk_uint8_t MK_c0_noErrorHookStack;
extern const mk_uint8_t MK_c0_noProtectionHookStack;
#endif

#define MK_C0_PTR_INITTEST_DATA				MK_NULL
#define MK_C0_PTR_INITTEST_BSS				MK_NULL

#if MK_HASHEAP
#define MK_C0_HEAP							MK_NULL
#endif

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)
#define MK_CFG_C0_COREPAGETABLES			MK_NULL
#endif

#else

/* Core 0 is in use - define all pointers as required
*/

#define MK_CFG_C0_COREVARS					&MK_c0_coreVars
#define MK_CFG_C0_SYNCSPOT					&MK_c0_syncSpot
#define MK_CFG_C0_KERNSPINITIAL				&MK_c0_kernelStack[MK_CFG_C0_KERNEL_STACK_NELEMENTS]

#define MK_CFG_C0_THRCFG_IDLE				&MK_c0_idleThreadConfig
#define MK_CFG_C0_THRCFG_SHUTDOWN			&MK_c0_shutdownThreadConfig
#define MK_CFG_C0_THRCFG_BOOT				&MK_c0_bootThreadConfig
#define MK_CFG_C0_THRCFG_INIT				&MK_c0_initThreadConfig

#define MK_CFG_C0_THREAD_IDLE				&MK_c0_idleThread
#define MK_CFG_C0_THREAD_AUX1				&MK_c0_aux1Thread
#define MK_CFG_C0_THREAD_AUX2				&MK_c0_aux2Thread

#if MK_CFG_C0_HAS_CTRSUB
#define MK_CFG_C0_THRCFG_CTRSUB				&MK_c0_ctrsubThreadConfig
#else
#define MK_CFG_C0_THRCFG_CTRSUB				MK_NULL
#endif

#if MK_CFG_C0_HAS_TRUSTEDFUNCTION
#define MK_CFG_C0_THRCFG_TRUSTEDFUNCTION	&MK_c0_trustedFunctionThreadConfig
#else
#define MK_CFG_C0_THRCFG_TRUSTEDFUNCTION	MK_NULL
#endif

#if MK_CFG_C0_HAS_ERRORHOOK
#define MK_CFG_C0_THRCFG_ERRORHOOK			&MK_c0_errorHookThreadConfig
#define MK_CFG_C0_THREAD_ERRORHOOK			&MK_c0_errorHookThread
#else
#define MK_CFG_C0_THRCFG_ERRORHOOK			MK_NULL
#define MK_CFG_C0_THREAD_ERRORHOOK			MK_NULL
#endif

#if MK_CFG_C0_HAS_PROTECTIONHOOK
#define MK_CFG_C0_THRCFG_PROTECTIONHOOK		&MK_c0_protectionHookThreadConfig
#define MK_CFG_C0_THREAD_PROTECTIONHOOK		&MK_c0_protectionHookThread
#else
#define MK_CFG_C0_THRCFG_PROTECTIONHOOK		MK_NULL
#define MK_CFG_C0_THREAD_PROTECTIONHOOK		MK_NULL
#endif

#if MK_CFG_C0_HAS_SHUTDOWNHOOK
#define MK_CFG_C0_THRCFG_SHUTDOWNHOOK		&MK_c0_shutdownHookThreadConfig
#else
#define MK_CFG_C0_THRCFG_SHUTDOWNHOOK		MK_NULL
#endif

#define MK_CFG_C0_ERRORINFO					&MK_c0_errorInfo
#define MK_CFG_C0_PROTECTIONINFO			&MK_c0_protectionInfo

#define MK_CFG_C0_EXCEPTIONINFO				&MK_c0_exceptionInfo
#define MK_CFG_C0_PANICEXCEPTIONINFO		&MK_c0_panicExceptionInfo

#if MK_CFG_C0_NLOCKS > 0
#define MK_CFG_C0_LOCKTABLE					MK_c0_lockTable
#else
#define MK_CFG_C0_LOCKTABLE					MK_NULL
#endif

#if MK_CFG_C0_NJOBQUEUES > 0
#define MK_CFG_C0_JOBQUEUE					MK_c0_jobQueue
#define MK_CFG_C0_JOBQUEUECFG				MK_c0_jobQueueCfg
#define MK_CFG_C0_JOBQUEUEBUFFER			MK_c0_jobQueueBuffer
#else
#define MK_CFG_C0_JOBQUEUE					MK_NULL
#define MK_CFG_C0_JOBQUEUECFG				MK_NULL
#define MK_CFG_C0_JOBQUEUEBUFLEN			0
#define MK_CFG_C0_JOBQUEUEBUFFER			MK_NULL
#endif

#if MK_USE_ORTI_TRACE
#define MK_CFG_C0_ORTI_RUNNING_THREAD	&MK_c0_ortiRunningThread
#ifndef MK_ASM
extern volatile mk_uint32_t MK_c0_ortiRunningThread;
#endif
#else
#define MK_CFG_C0_ORTI_RUNNING_THREAD	MK_NULL
#endif

/* Stack configuration for core 0
*/
#ifndef MK_ASM
extern mk_stackelement_t MK_c0_kernelStack[MK_CFG_C0_KERNEL_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The idle and shutdown threads use the same stack. The size is the larger of the two.
*/
#if MK_CFG_C0_IDLE_STACK_NELEMENTS > MK_CFG_C0_SHUTDOWN_STACK_NELEMENTS
#define MK_CFG_C0_IDLESHUTDOWN_STACK_NELEMENTS	MK_CFG_C0_IDLE_STACK_NELEMENTS
#else
#define MK_CFG_C0_IDLESHUTDOWN_STACK_NELEMENTS	MK_CFG_C0_SHUTDOWN_STACK_NELEMENTS
#endif

#ifndef MK_ASM
extern mk_stackelement_t MK_c0_idleshutdownStack[MK_CFG_C0_IDLESHUTDOWN_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The error hook thread has a private stack
*/
#ifndef MK_ASM
#if MK_CFG_C0_HAS_ERRORHOOK
extern mk_stackelement_t MK_c0_errorhookStack[MK_CFG_C0_ERRORHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else
extern const mk_uint8_t MK_c0_noErrorHookStack;
#endif
#endif

/* The protection hook thread has a private stack
*/
#ifndef MK_ASM
#if MK_CFG_C0_HAS_PROTECTIONHOOK
extern mk_stackelement_t MK_c0_protectionHookStack[MK_CFG_C0_PROTECTIONHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else
extern const mk_uint8_t MK_c0_noProtectionHookStack;
#endif
#endif

#define MK_CFG_C0_AUX1_STACK_NELEMENTS	MK_CFG_C0_CTRSUB_STACK_NELEMENTS

#ifndef MK_ASM
extern mk_stackelement_t MK_c0_aux1Stack[MK_CFG_C0_AUX1_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The aux2 thread runs trusted function, init, startup hook and shutdown hook threads. Its stack is therefore
 * the largest of the four.
*/
#if MK_CFG_C0_INIT_STACK_NELEMENTS > MK_CFG_C0_TF_STACK_NELEMENTS
#define MK_CFG_C0_AUX2A_STACK_NELEMENTS	MK_CFG_C0_INIT_STACK_NELEMENTS
#else
#define MK_CFG_C0_AUX2A_STACK_NELEMENTS	MK_CFG_C0_TF_STACK_NELEMENTS
#endif

#if MK_CFG_C0_HAS_SHUTDOWNHOOK
#ifndef MK_CFG_C0_SHUTDOWNHOOK_STACK_NELEMENTS
#error "MK_CFG_C0_SHUTDOWNHOOK_STACK_NELEMENTS must be defined"
#endif
#else
#ifndef MK_CFG_C0_SHUTDOWNHOOK_STACK_NELEMENTS
#define MK_CFG_C0_SHUTDOWNHOOK_STACK_NELEMENTS	0
#endif
#endif

#if MK_CFG_C0_AUX2A_STACK_NELEMENTS > MK_CFG_C0_SHUTDOWNHOOK_STACK_NELEMENTS
#define MK_CFG_C0_AUX2_STACK_NELEMENTS	MK_CFG_C0_AUX2A_STACK_NELEMENTS
#else
#define MK_CFG_C0_AUX2_STACK_NELEMENTS	MK_CFG_C0_SHUTDOWNHOOK_STACK_NELEMENTS
#endif

#ifndef MK_ASM
extern mk_stackelement_t MK_c0_aux2Stack[MK_CFG_C0_AUX2_STACK_NELEMENTS + MK_HW_STACK_EXTRA];

#if (MK_MAXCORES > 1)
extern mk_kernelcontrol_t MK_c0_coreVars;
#endif
extern volatile mk_syncspot_t MK_c0_syncSpot;

extern const mk_threadcfg_t MK_c0_idleThreadConfig;
extern const mk_threadcfg_t MK_c0_shutdownThreadConfig;
extern const mk_threadcfg_t MK_c0_bootThreadConfig;
extern const mk_threadcfg_t MK_c0_initThreadConfig;
extern const mk_threadcfg_t MK_c0_errorHookThreadConfig;
extern const mk_threadcfg_t MK_c0_protectionHookThreadConfig;
extern const mk_threadcfg_t MK_c0_shutdownHookThreadConfig;
extern mk_threadcfg_t MK_c0_ctrsubThreadConfig;
extern mk_threadcfg_t MK_c0_trustedFunctionThreadConfig;

extern mk_thread_t MK_c0_idleThread;
extern mk_thread_t MK_c0_aux1Thread;
extern mk_thread_t MK_c0_aux2Thread;
extern mk_thread_t MK_c0_errorHookThread;
extern mk_thread_t MK_c0_protectionHookThread;

extern mk_errorinfo_t MK_c0_errorInfo;
extern mk_protectioninfo_t MK_c0_protectionInfo;

extern mk_hwexceptioninfo_t MK_c0_exceptionInfo;
extern mk_hwexceptioninfo_t MK_c0_panicExceptionInfo;

#if MK_CFG_C0_NTASKS > 0
extern mk_task_t MK_c0_taskDynamic[MK_CFG_C0_NTASKS];
#endif

#if MK_CFG_C0_NTASKTHREADS > 0
extern mk_thread_t MK_c0_taskThreads[MK_CFG_C0_NTASKTHREADS];
#endif

#if MK_CFG_C0_NTASKREGISTERS > 0
extern mk_threadregisters_t MK_c0_taskRegisters[MK_CFG_C0_NTASKREGISTERS];
#endif

#if MK_CFG_C0_NETASKS > 0
extern mk_eventstatus_t MK_c0_eventStatus[MK_CFG_C0_NETASKS];
#endif

#if MK_CFG_C0_NISRS > 0
extern mk_isr_t MK_c0_isrDynamic[MK_CFG_C0_NISRS];
#endif

#if MK_CFG_C0_NISRTHREADS > 0
extern mk_thread_t MK_c0_isrThreads[MK_CFG_C0_NISRTHREADS];
#endif

#if MK_CFG_C0_NISRREGISTERS > 0
extern mk_threadregisters_t MK_c0_isrRegisters[MK_CFG_C0_NISRREGISTERS];
#endif

#if MK_CFG_C0_NLOCKS > 0
extern mk_lock_t MK_c0_lockTable[MK_CFG_C0_NLOCKS];
#endif

#if MK_CFG_C0_NJOBQUEUES > 0
extern mk_jobqueue_t MK_c0_jobQueue[MK_CFG_C0_NJOBQUEUES];
extern const mk_jobqueuecfg_t MK_c0_jobQueueCfg[MK_CFG_C0_NJOBQUEUES];
extern mk_jobelement_t MK_c0_jobQueueBuffer[MK_CFG_C0_JOBQUEUEBUFLEN];
#endif

#if MK_CFG_C0_NAPPLICATIONS > 0
extern mk_app_t MK_c0_appDynamic[MK_CFG_C0_NAPPLICATIONS];
#endif

#if ( 0 != 0 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) != 0
extern mk_message_t MK_c0_c0_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c0_removePtr;
extern mk_msgptrfield_t MK_c0_c0_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c0_queue;
#endif
#endif

#if ( 0 != 1 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) != 0
extern mk_message_t MK_c0_c1_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c1_removePtr;
extern mk_msgptrfield_t MK_c0_c1_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c1_queue;
#endif
#endif

#if ( 0 != 2 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) != 0
extern mk_message_t MK_c0_c2_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c2_removePtr;
extern mk_msgptrfield_t MK_c0_c2_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c2_queue;
#endif
#endif

#if ( 0 != 3 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) != 0
extern mk_message_t MK_c0_c3_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c3_removePtr;
extern mk_msgptrfield_t MK_c0_c3_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c3_queue;
#endif
#endif

#if ( 0 != 4 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C4 & MK_COREMAPBIT_C4) != 0
extern mk_message_t MK_c0_c4_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c4_removePtr;
extern mk_msgptrfield_t MK_c0_c4_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c4_queue;
#endif
#endif

#if ( 0 != 5 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C5 & MK_COREMAPBIT_C5) != 0
extern mk_message_t MK_c0_c5_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c5_removePtr;
extern mk_msgptrfield_t MK_c0_c5_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c5_queue;
#endif
#endif

#if ( 0 != 6 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C6 & MK_COREMAPBIT_C6) != 0
extern mk_message_t MK_c0_c6_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c6_removePtr;
extern mk_msgptrfield_t MK_c0_c6_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c6_queue;
#endif
#endif

#if ( 0 != 7 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C7 & MK_COREMAPBIT_C7) != 0
extern mk_message_t MK_c0_c7_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c0_c7_removePtr;
extern mk_msgptrfield_t MK_c0_c7_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c0_c7_queue;
#endif
#endif


#if (MK_MAXCORES > 1)
extern mk_uint32_t MK_c0_initTestData;
extern mk_uint32_t MK_c0_initTestBss;
#define MK_C0_PTR_INITTEST_DATA	(&MK_c0_initTestData)
#define MK_C0_PTR_INITTEST_BSS	(&MK_c0_initTestBss)
#endif /* (MK_MAXCORES > 1) */

#if MK_HASHEAP
#define MK_C0_HEAP (&MK_c0_heap)
extern mk_heap_t MK_c0_heap;
#endif

#if (MK_CFG_C0_NSSTS > 0)
extern mk_sstcounter_t MK_c0_sstCounters[MK_CFG_C0_NSSTS];
#else /* MK_CFG_C0_NSSTS */
/* This declaration just exists to avoid violating MISRA-C:2012 rule 8.4. */
extern const mk_uint8_t MK_c0_sst_NOT_USED;
#endif /* MK_CFG_C0_NSSTS */

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)
#define MK_CFG_C0_COREPAGETABLES	MK_c0_partitionToPageTable
extern mk_pagetabledescriptor_t MK_c0_partitionToPageTable[MK_CFG_C0_NMEMORYPARTITIONS];
#endif

#endif /* MK_ASM */

#endif /* MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0 */

/* Define default ALCI mapping for backwards compatibility if no generator is used */
#ifndef MK_CFG_C0_ALCI_PHY_TO_LOG
#define MK_CFG_C0_ALCI_PHY_TO_LOG 0
#endif
#ifndef MK_CFG_C0_ALCI_LOG_TO_PHY
#define MK_CFG_C0_ALCI_LOG_TO_PHY 0
#endif

/* Some derivatives might have timers for EBM that are core-specific, with different frequencies */
#ifndef MK_ExecutionNsToTicks_c0
#define MK_ExecutionNsToTicks_c0 MK_ExecutionNsToTicks
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
