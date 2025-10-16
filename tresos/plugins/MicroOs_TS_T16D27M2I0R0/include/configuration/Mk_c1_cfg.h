/* Mk_c1_cfg.h
 *
 * This file contains the declaration of the configuration for core 1.
 *
 * If core 1 is not in use, all its configuration items map to MK_NULL.
 *
 * If core 1 is in use, its configuration items map to the appropriate structures etc. The optional items
 * are defined as MK_NULL if not enabled.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_C1_CFG_H
#define MK_C1_CFG_H		1

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

#if (MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) != 0
#include <configuration/Mk_c1_defaults.h>
#endif

#ifndef MK_CFG_C1_NSSTS
#define MK_CFG_C1_NSSTS 0
#endif

#if (MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) == 0

/* Core 1 is not in use - define all pointers as NULL and all other parameters as harmless values.
*/
#define MK_CFG_C1_COREVARS					MK_NULL
#define MK_CFG_C1_SYNCSPOT					MK_NULL
#define MK_CFG_C1_KERNSPINITIAL				MK_NULL
#define MK_CFG_C1_PROPERTIES				0u

#define MK_CFG_C1_THRCFG_IDLE				MK_NULL
#define MK_CFG_C1_THRCFG_SHUTDOWN			MK_NULL
#define MK_CFG_C1_THRCFG_BOOT				MK_NULL
#define MK_CFG_C1_THRCFG_INIT				MK_NULL

#define MK_CFG_C1_THREAD_IDLE				MK_NULL
#define MK_CFG_C1_THREAD_AUX1				MK_NULL
#define MK_CFG_C1_THREAD_AUX2				MK_NULL

#define MK_CFG_C1_THRCFG_CTRSUB				MK_NULL
#define MK_CFG_C1_THRCFG_TRUSTEDFUNCTION	MK_NULL

#define MK_CFG_C1_THRCFG_ERRORHOOK			MK_NULL
#define MK_CFG_C1_THREAD_ERRORHOOK			MK_NULL

#define MK_CFG_C1_THRCFG_PROTECTIONHOOK		MK_NULL
#define MK_CFG_C1_THREAD_PROTECTIONHOOK		MK_NULL

#define MK_CFG_C1_THRCFG_SHUTDOWNHOOK		MK_NULL

#define MK_CFG_C1_ERRORINFO					MK_NULL
#define MK_CFG_C1_PROTECTIONINFO			MK_NULL
#define MK_CFG_C1_EXCEPTIONINFO				MK_NULL
#define MK_CFG_C1_PANICEXCEPTIONINFO		MK_NULL

#define MK_CFG_C1_NLOCKS					0
#define MK_CFG_C1_LOCKTABLE					MK_NULL

#define MK_CFG_C1_NJOBQUEUES				0
#define MK_CFG_C1_JOBQUEUE					MK_NULL
#define MK_CFG_C1_JOBQUEUECFG				MK_NULL
#define MK_CFG_C1_JOBQUEUEBUFLEN			0
#define MK_CFG_C1_JOBQUEUEBUFFER			MK_NULL

#define MK_CFG_C1_ORTI_RUNNING_THREAD		MK_NULL

#define MK_CFG_C1_NMEMORYPARTITIONS			0
#define MK_CFG_C1_FIRST_MEMORYPARTITION		0

#ifndef MK_CFG_C1_MSG_INVALIDHANDLER
#define MK_CFG_C1_MSG_INVALIDHANDLER		MK_NULL
#endif

#ifndef MK_CFG_C1_HAS_ERRORHOOK
#define MK_CFG_C1_HAS_ERRORHOOK				0
#endif

#ifndef MK_CFG_C1_HAS_PROTECTIONHOOK
#define MK_CFG_C1_HAS_PROTECTIONHOOK		0
#endif

#ifndef MK_CFG_C1_HAS_CTRSUB
#define MK_CFG_C1_HAS_CTRSUB				0
#endif

#ifndef MK_CFG_C1_HAS_SHUTDOWNHOOK
#define MK_CFG_C1_HAS_SHUTDOWNHOOK			0
#endif

#ifndef MK_CFG_C1_HAS_TRUSTEDFUNCTION
#define MK_CFG_C1_HAS_TRUSTEDFUNCTION		0
#endif

/* These declarations just exist to avoid violating MISRA-C:2012 rule 8.4. */
#ifndef MK_ASM
extern const mk_uint8_t MK_c1_NOT_USED;
extern const mk_uint8_t MK_c1_noAux1Stack;
extern const mk_uint8_t MK_c1_noAux2Stack;
extern const mk_uint8_t MK_c1_sst_NOT_USED;
extern const mk_uint8_t MK_c1_noIdleShutdownStack;
extern const mk_uint8_t MK_c1_noKernelStack;
extern const mk_uint8_t MK_c1_noErrorHookStack;
extern const mk_uint8_t MK_c1_noProtectionHookStack;
#endif

#define MK_C1_PTR_INITTEST_DATA				MK_NULL
#define MK_C1_PTR_INITTEST_BSS				MK_NULL

#if MK_HASHEAP
#define MK_C1_HEAP							MK_NULL
#endif

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)
#define MK_CFG_C1_COREPAGETABLES			MK_NULL
#endif

#else

/* Core 1 is in use - define all pointers as required
*/

#define MK_CFG_C1_COREVARS					&MK_c1_coreVars
#define MK_CFG_C1_SYNCSPOT					&MK_c1_syncSpot
#define MK_CFG_C1_KERNSPINITIAL				&MK_c1_kernelStack[MK_CFG_C1_KERNEL_STACK_NELEMENTS]

#define MK_CFG_C1_THRCFG_IDLE				&MK_c1_idleThreadConfig
#define MK_CFG_C1_THRCFG_SHUTDOWN			&MK_c1_shutdownThreadConfig
#define MK_CFG_C1_THRCFG_BOOT				&MK_c1_bootThreadConfig
#define MK_CFG_C1_THRCFG_INIT				&MK_c1_initThreadConfig

#define MK_CFG_C1_THREAD_IDLE				&MK_c1_idleThread
#define MK_CFG_C1_THREAD_AUX1				&MK_c1_aux1Thread
#define MK_CFG_C1_THREAD_AUX2				&MK_c1_aux2Thread

#if MK_CFG_C1_HAS_CTRSUB
#define MK_CFG_C1_THRCFG_CTRSUB				&MK_c1_ctrsubThreadConfig
#else
#define MK_CFG_C1_THRCFG_CTRSUB				MK_NULL
#endif

#if MK_CFG_C1_HAS_TRUSTEDFUNCTION
#define MK_CFG_C1_THRCFG_TRUSTEDFUNCTION	&MK_c1_trustedFunctionThreadConfig
#else
#define MK_CFG_C1_THRCFG_TRUSTEDFUNCTION	MK_NULL
#endif

#if MK_CFG_C1_HAS_ERRORHOOK
#define MK_CFG_C1_THRCFG_ERRORHOOK			&MK_c1_errorHookThreadConfig
#define MK_CFG_C1_THREAD_ERRORHOOK			&MK_c1_errorHookThread
#else
#define MK_CFG_C1_THRCFG_ERRORHOOK			MK_NULL
#define MK_CFG_C1_THREAD_ERRORHOOK			MK_NULL
#endif

#if MK_CFG_C1_HAS_PROTECTIONHOOK
#define MK_CFG_C1_THRCFG_PROTECTIONHOOK		&MK_c1_protectionHookThreadConfig
#define MK_CFG_C1_THREAD_PROTECTIONHOOK		&MK_c1_protectionHookThread
#else
#define MK_CFG_C1_THRCFG_PROTECTIONHOOK		MK_NULL
#define MK_CFG_C1_THREAD_PROTECTIONHOOK		MK_NULL
#endif

#if MK_CFG_C1_HAS_SHUTDOWNHOOK
#define MK_CFG_C1_THRCFG_SHUTDOWNHOOK		&MK_c1_shutdownHookThreadConfig
#else
#define MK_CFG_C1_THRCFG_SHUTDOWNHOOK		MK_NULL
#endif

#define MK_CFG_C1_ERRORINFO					&MK_c1_errorInfo
#define MK_CFG_C1_PROTECTIONINFO			&MK_c1_protectionInfo

#define MK_CFG_C1_EXCEPTIONINFO				&MK_c1_exceptionInfo
#define MK_CFG_C1_PANICEXCEPTIONINFO		&MK_c1_panicExceptionInfo

#if MK_CFG_C1_NLOCKS > 0
#define MK_CFG_C1_LOCKTABLE					MK_c1_lockTable
#else
#define MK_CFG_C1_LOCKTABLE					MK_NULL
#endif

#if MK_CFG_C1_NJOBQUEUES > 0
#define MK_CFG_C1_JOBQUEUE					MK_c1_jobQueue
#define MK_CFG_C1_JOBQUEUECFG				MK_c1_jobQueueCfg
#define MK_CFG_C1_JOBQUEUEBUFFER			MK_c1_jobQueueBuffer
#else
#define MK_CFG_C1_JOBQUEUE					MK_NULL
#define MK_CFG_C1_JOBQUEUECFG				MK_NULL
#define MK_CFG_C1_JOBQUEUEBUFLEN			0
#define MK_CFG_C1_JOBQUEUEBUFFER			MK_NULL
#endif

#if MK_USE_ORTI_TRACE
#define MK_CFG_C1_ORTI_RUNNING_THREAD	&MK_c1_ortiRunningThread
#ifndef MK_ASM
extern volatile mk_uint32_t MK_c1_ortiRunningThread;
#endif
#else
#define MK_CFG_C1_ORTI_RUNNING_THREAD	MK_NULL
#endif

/* Stack configuration for core 1
*/
#ifndef MK_ASM
extern mk_stackelement_t MK_c1_kernelStack[MK_CFG_C1_KERNEL_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The idle and shutdown threads use the same stack. The size is the larger of the two.
*/
#if MK_CFG_C1_IDLE_STACK_NELEMENTS > MK_CFG_C1_SHUTDOWN_STACK_NELEMENTS
#define MK_CFG_C1_IDLESHUTDOWN_STACK_NELEMENTS	MK_CFG_C1_IDLE_STACK_NELEMENTS
#else
#define MK_CFG_C1_IDLESHUTDOWN_STACK_NELEMENTS	MK_CFG_C1_SHUTDOWN_STACK_NELEMENTS
#endif

#ifndef MK_ASM
extern mk_stackelement_t MK_c1_idleshutdownStack[MK_CFG_C1_IDLESHUTDOWN_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The error hook thread has a private stack
*/
#ifndef MK_ASM
#if MK_CFG_C1_HAS_ERRORHOOK
extern mk_stackelement_t MK_c1_errorhookStack[MK_CFG_C1_ERRORHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else
extern const mk_uint8_t MK_c1_noErrorHookStack;
#endif
#endif

/* The protection hook thread has a private stack
*/
#ifndef MK_ASM
#if MK_CFG_C1_HAS_PROTECTIONHOOK
extern mk_stackelement_t MK_c1_protectionHookStack[MK_CFG_C1_PROTECTIONHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else
extern const mk_uint8_t MK_c1_noProtectionHookStack;
#endif
#endif

#define MK_CFG_C1_AUX1_STACK_NELEMENTS	MK_CFG_C1_CTRSUB_STACK_NELEMENTS

#ifndef MK_ASM
extern mk_stackelement_t MK_c1_aux1Stack[MK_CFG_C1_AUX1_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The aux2 thread runs trusted function, init, startup hook and shutdown hook threads. Its stack is therefore
 * the largest of the four.
*/
#if MK_CFG_C1_INIT_STACK_NELEMENTS > MK_CFG_C1_TF_STACK_NELEMENTS
#define MK_CFG_C1_AUX2A_STACK_NELEMENTS	MK_CFG_C1_INIT_STACK_NELEMENTS
#else
#define MK_CFG_C1_AUX2A_STACK_NELEMENTS	MK_CFG_C1_TF_STACK_NELEMENTS
#endif

#if MK_CFG_C1_HAS_SHUTDOWNHOOK
#ifndef MK_CFG_C1_SHUTDOWNHOOK_STACK_NELEMENTS
#error "MK_CFG_C1_SHUTDOWNHOOK_STACK_NELEMENTS must be defined"
#endif
#else
#ifndef MK_CFG_C1_SHUTDOWNHOOK_STACK_NELEMENTS
#define MK_CFG_C1_SHUTDOWNHOOK_STACK_NELEMENTS	0
#endif
#endif

#if MK_CFG_C1_AUX2A_STACK_NELEMENTS > MK_CFG_C1_SHUTDOWNHOOK_STACK_NELEMENTS
#define MK_CFG_C1_AUX2_STACK_NELEMENTS	MK_CFG_C1_AUX2A_STACK_NELEMENTS
#else
#define MK_CFG_C1_AUX2_STACK_NELEMENTS	MK_CFG_C1_SHUTDOWNHOOK_STACK_NELEMENTS
#endif

#ifndef MK_ASM
extern mk_stackelement_t MK_c1_aux2Stack[MK_CFG_C1_AUX2_STACK_NELEMENTS + MK_HW_STACK_EXTRA];

#if (MK_MAXCORES > 1)
extern mk_kernelcontrol_t MK_c1_coreVars;
#endif
extern volatile mk_syncspot_t MK_c1_syncSpot;

extern const mk_threadcfg_t MK_c1_idleThreadConfig;
extern const mk_threadcfg_t MK_c1_shutdownThreadConfig;
extern const mk_threadcfg_t MK_c1_bootThreadConfig;
extern const mk_threadcfg_t MK_c1_initThreadConfig;
extern const mk_threadcfg_t MK_c1_errorHookThreadConfig;
extern const mk_threadcfg_t MK_c1_protectionHookThreadConfig;
extern const mk_threadcfg_t MK_c1_shutdownHookThreadConfig;
extern mk_threadcfg_t MK_c1_ctrsubThreadConfig;
extern mk_threadcfg_t MK_c1_trustedFunctionThreadConfig;

extern mk_thread_t MK_c1_idleThread;
extern mk_thread_t MK_c1_aux1Thread;
extern mk_thread_t MK_c1_aux2Thread;
extern mk_thread_t MK_c1_errorHookThread;
extern mk_thread_t MK_c1_protectionHookThread;

extern mk_errorinfo_t MK_c1_errorInfo;
extern mk_protectioninfo_t MK_c1_protectionInfo;

extern mk_hwexceptioninfo_t MK_c1_exceptionInfo;
extern mk_hwexceptioninfo_t MK_c1_panicExceptionInfo;

#if MK_CFG_C1_NTASKS > 0
extern mk_task_t MK_c1_taskDynamic[MK_CFG_C1_NTASKS];
#endif

#if MK_CFG_C1_NTASKTHREADS > 0
extern mk_thread_t MK_c1_taskThreads[MK_CFG_C1_NTASKTHREADS];
#endif

#if MK_CFG_C1_NTASKREGISTERS > 0
extern mk_threadregisters_t MK_c1_taskRegisters[MK_CFG_C1_NTASKREGISTERS];
#endif

#if MK_CFG_C1_NETASKS > 0
extern mk_eventstatus_t MK_c1_eventStatus[MK_CFG_C1_NETASKS];
#endif

#if MK_CFG_C1_NISRS > 0
extern mk_isr_t MK_c1_isrDynamic[MK_CFG_C1_NISRS];
#endif

#if MK_CFG_C1_NISRTHREADS > 0
extern mk_thread_t MK_c1_isrThreads[MK_CFG_C1_NISRTHREADS];
#endif

#if MK_CFG_C1_NISRREGISTERS > 0
extern mk_threadregisters_t MK_c1_isrRegisters[MK_CFG_C1_NISRREGISTERS];
#endif

#if MK_CFG_C1_NLOCKS > 0
extern mk_lock_t MK_c1_lockTable[MK_CFG_C1_NLOCKS];
#endif

#if MK_CFG_C1_NJOBQUEUES > 0
extern mk_jobqueue_t MK_c1_jobQueue[MK_CFG_C1_NJOBQUEUES];
extern const mk_jobqueuecfg_t MK_c1_jobQueueCfg[MK_CFG_C1_NJOBQUEUES];
extern mk_jobelement_t MK_c1_jobQueueBuffer[MK_CFG_C1_JOBQUEUEBUFLEN];
#endif

#if MK_CFG_C1_NAPPLICATIONS > 0
extern mk_app_t MK_c1_appDynamic[MK_CFG_C1_NAPPLICATIONS];
#endif

#if ( 1 != 0 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) != 0
extern mk_message_t MK_c1_c0_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c0_removePtr;
extern mk_msgptrfield_t MK_c1_c0_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c0_queue;
#endif
#endif

#if ( 1 != 1 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) != 0
extern mk_message_t MK_c1_c1_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c1_removePtr;
extern mk_msgptrfield_t MK_c1_c1_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c1_queue;
#endif
#endif

#if ( 1 != 2 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) != 0
extern mk_message_t MK_c1_c2_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c2_removePtr;
extern mk_msgptrfield_t MK_c1_c2_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c2_queue;
#endif
#endif

#if ( 1 != 3 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) != 0
extern mk_message_t MK_c1_c3_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c3_removePtr;
extern mk_msgptrfield_t MK_c1_c3_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c3_queue;
#endif
#endif

#if ( 1 != 4 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C4 & MK_COREMAPBIT_C4) != 0
extern mk_message_t MK_c1_c4_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c4_removePtr;
extern mk_msgptrfield_t MK_c1_c4_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c4_queue;
#endif
#endif

#if ( 1 != 5 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C5 & MK_COREMAPBIT_C5) != 0
extern mk_message_t MK_c1_c5_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c5_removePtr;
extern mk_msgptrfield_t MK_c1_c5_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c5_queue;
#endif
#endif

#if ( 1 != 6 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C6 & MK_COREMAPBIT_C6) != 0
extern mk_message_t MK_c1_c6_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c6_removePtr;
extern mk_msgptrfield_t MK_c1_c6_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c6_queue;
#endif
#endif

#if ( 1 != 7 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C7 & MK_COREMAPBIT_C7) != 0
extern mk_message_t MK_c1_c7_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c1_c7_removePtr;
extern mk_msgptrfield_t MK_c1_c7_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c1_c7_queue;
#endif
#endif


#if (MK_MAXCORES > 1)
extern mk_uint32_t MK_c1_initTestData;
extern mk_uint32_t MK_c1_initTestBss;
#define MK_C1_PTR_INITTEST_DATA	(&MK_c1_initTestData)
#define MK_C1_PTR_INITTEST_BSS	(&MK_c1_initTestBss)
#endif /* (MK_MAXCORES > 1) */

#if MK_HASHEAP
#define MK_C1_HEAP (&MK_c1_heap)
extern mk_heap_t MK_c1_heap;
#endif

#if (MK_CFG_C1_NSSTS > 0)
extern mk_sstcounter_t MK_c1_sstCounters[MK_CFG_C1_NSSTS];
#else /* MK_CFG_C1_NSSTS */
/* This declaration just exists to avoid violating MISRA-C:2012 rule 8.4. */
extern const mk_uint8_t MK_c1_sst_NOT_USED;
#endif /* MK_CFG_C1_NSSTS */

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)
#define MK_CFG_C1_COREPAGETABLES	MK_c1_partitionToPageTable
extern mk_pagetabledescriptor_t MK_c1_partitionToPageTable[MK_CFG_C1_NMEMORYPARTITIONS];
#endif

#endif /* MK_ASM */

#endif /* MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1 */

/* Define default ALCI mapping for backwards compatibility if no generator is used */
#ifndef MK_CFG_C1_ALCI_PHY_TO_LOG
#define MK_CFG_C1_ALCI_PHY_TO_LOG 1
#endif
#ifndef MK_CFG_C1_ALCI_LOG_TO_PHY
#define MK_CFG_C1_ALCI_LOG_TO_PHY 1
#endif

/* Some derivatives might have timers for EBM that are core-specific, with different frequencies */
#ifndef MK_ExecutionNsToTicks_c1
#define MK_ExecutionNsToTicks_c1 MK_ExecutionNsToTicks
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
