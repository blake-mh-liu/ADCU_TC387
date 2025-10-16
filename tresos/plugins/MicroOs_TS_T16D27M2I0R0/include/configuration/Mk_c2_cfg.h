/* Mk_c2_cfg.h
 *
 * This file contains the declaration of the configuration for core 2.
 *
 * If core 2 is not in use, all its configuration items map to MK_NULL.
 *
 * If core 2 is in use, its configuration items map to the appropriate structures etc. The optional items
 * are defined as MK_NULL if not enabled.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_C2_CFG_H
#define MK_C2_CFG_H		1

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

#if (MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) != 0
#include <configuration/Mk_c2_defaults.h>
#endif

#ifndef MK_CFG_C2_NSSTS
#define MK_CFG_C2_NSSTS 0
#endif

#if (MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) == 0

/* Core 2 is not in use - define all pointers as NULL and all other parameters as harmless values.
*/
#define MK_CFG_C2_COREVARS					MK_NULL
#define MK_CFG_C2_SYNCSPOT					MK_NULL
#define MK_CFG_C2_KERNSPINITIAL				MK_NULL
#define MK_CFG_C2_PROPERTIES				0u

#define MK_CFG_C2_THRCFG_IDLE				MK_NULL
#define MK_CFG_C2_THRCFG_SHUTDOWN			MK_NULL
#define MK_CFG_C2_THRCFG_BOOT				MK_NULL
#define MK_CFG_C2_THRCFG_INIT				MK_NULL

#define MK_CFG_C2_THREAD_IDLE				MK_NULL
#define MK_CFG_C2_THREAD_AUX1				MK_NULL
#define MK_CFG_C2_THREAD_AUX2				MK_NULL

#define MK_CFG_C2_THRCFG_CTRSUB				MK_NULL
#define MK_CFG_C2_THRCFG_TRUSTEDFUNCTION	MK_NULL

#define MK_CFG_C2_THRCFG_ERRORHOOK			MK_NULL
#define MK_CFG_C2_THREAD_ERRORHOOK			MK_NULL

#define MK_CFG_C2_THRCFG_PROTECTIONHOOK		MK_NULL
#define MK_CFG_C2_THREAD_PROTECTIONHOOK		MK_NULL

#define MK_CFG_C2_THRCFG_SHUTDOWNHOOK		MK_NULL

#define MK_CFG_C2_ERRORINFO					MK_NULL
#define MK_CFG_C2_PROTECTIONINFO			MK_NULL
#define MK_CFG_C2_EXCEPTIONINFO				MK_NULL
#define MK_CFG_C2_PANICEXCEPTIONINFO		MK_NULL

#define MK_CFG_C2_NLOCKS					0
#define MK_CFG_C2_LOCKTABLE					MK_NULL

#define MK_CFG_C2_NJOBQUEUES				0
#define MK_CFG_C2_JOBQUEUE					MK_NULL
#define MK_CFG_C2_JOBQUEUECFG				MK_NULL
#define MK_CFG_C2_JOBQUEUEBUFLEN			0
#define MK_CFG_C2_JOBQUEUEBUFFER			MK_NULL

#define MK_CFG_C2_ORTI_RUNNING_THREAD		MK_NULL

#define MK_CFG_C2_NMEMORYPARTITIONS			0
#define MK_CFG_C2_FIRST_MEMORYPARTITION		0

#ifndef MK_CFG_C2_MSG_INVALIDHANDLER
#define MK_CFG_C2_MSG_INVALIDHANDLER		MK_NULL
#endif

#ifndef MK_CFG_C2_HAS_ERRORHOOK
#define MK_CFG_C2_HAS_ERRORHOOK				0
#endif

#ifndef MK_CFG_C2_HAS_PROTECTIONHOOK
#define MK_CFG_C2_HAS_PROTECTIONHOOK		0
#endif

#ifndef MK_CFG_C2_HAS_CTRSUB
#define MK_CFG_C2_HAS_CTRSUB				0
#endif

#ifndef MK_CFG_C2_HAS_SHUTDOWNHOOK
#define MK_CFG_C2_HAS_SHUTDOWNHOOK			0
#endif

#ifndef MK_CFG_C2_HAS_TRUSTEDFUNCTION
#define MK_CFG_C2_HAS_TRUSTEDFUNCTION		0
#endif

/* These declarations just exist to avoid violating MISRA-C:2012 rule 8.4. */
#ifndef MK_ASM
extern const mk_uint8_t MK_c2_NOT_USED;
extern const mk_uint8_t MK_c2_noAux1Stack;
extern const mk_uint8_t MK_c2_noAux2Stack;
extern const mk_uint8_t MK_c2_sst_NOT_USED;
extern const mk_uint8_t MK_c2_noIdleShutdownStack;
extern const mk_uint8_t MK_c2_noKernelStack;
extern const mk_uint8_t MK_c2_noErrorHookStack;
extern const mk_uint8_t MK_c2_noProtectionHookStack;
#endif

#define MK_C2_PTR_INITTEST_DATA				MK_NULL
#define MK_C2_PTR_INITTEST_BSS				MK_NULL

#if MK_HASHEAP
#define MK_C2_HEAP							MK_NULL
#endif

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)
#define MK_CFG_C2_COREPAGETABLES			MK_NULL
#endif

#else

/* Core 2 is in use - define all pointers as required
*/

#define MK_CFG_C2_COREVARS					&MK_c2_coreVars
#define MK_CFG_C2_SYNCSPOT					&MK_c2_syncSpot
#define MK_CFG_C2_KERNSPINITIAL				&MK_c2_kernelStack[MK_CFG_C2_KERNEL_STACK_NELEMENTS]

#define MK_CFG_C2_THRCFG_IDLE				&MK_c2_idleThreadConfig
#define MK_CFG_C2_THRCFG_SHUTDOWN			&MK_c2_shutdownThreadConfig
#define MK_CFG_C2_THRCFG_BOOT				&MK_c2_bootThreadConfig
#define MK_CFG_C2_THRCFG_INIT				&MK_c2_initThreadConfig

#define MK_CFG_C2_THREAD_IDLE				&MK_c2_idleThread
#define MK_CFG_C2_THREAD_AUX1				&MK_c2_aux1Thread
#define MK_CFG_C2_THREAD_AUX2				&MK_c2_aux2Thread

#if MK_CFG_C2_HAS_CTRSUB
#define MK_CFG_C2_THRCFG_CTRSUB				&MK_c2_ctrsubThreadConfig
#else
#define MK_CFG_C2_THRCFG_CTRSUB				MK_NULL
#endif

#if MK_CFG_C2_HAS_TRUSTEDFUNCTION
#define MK_CFG_C2_THRCFG_TRUSTEDFUNCTION	&MK_c2_trustedFunctionThreadConfig
#else
#define MK_CFG_C2_THRCFG_TRUSTEDFUNCTION	MK_NULL
#endif

#if MK_CFG_C2_HAS_ERRORHOOK
#define MK_CFG_C2_THRCFG_ERRORHOOK			&MK_c2_errorHookThreadConfig
#define MK_CFG_C2_THREAD_ERRORHOOK			&MK_c2_errorHookThread
#else
#define MK_CFG_C2_THRCFG_ERRORHOOK			MK_NULL
#define MK_CFG_C2_THREAD_ERRORHOOK			MK_NULL
#endif

#if MK_CFG_C2_HAS_PROTECTIONHOOK
#define MK_CFG_C2_THRCFG_PROTECTIONHOOK		&MK_c2_protectionHookThreadConfig
#define MK_CFG_C2_THREAD_PROTECTIONHOOK		&MK_c2_protectionHookThread
#else
#define MK_CFG_C2_THRCFG_PROTECTIONHOOK		MK_NULL
#define MK_CFG_C2_THREAD_PROTECTIONHOOK		MK_NULL
#endif

#if MK_CFG_C2_HAS_SHUTDOWNHOOK
#define MK_CFG_C2_THRCFG_SHUTDOWNHOOK		&MK_c2_shutdownHookThreadConfig
#else
#define MK_CFG_C2_THRCFG_SHUTDOWNHOOK		MK_NULL
#endif

#define MK_CFG_C2_ERRORINFO					&MK_c2_errorInfo
#define MK_CFG_C2_PROTECTIONINFO			&MK_c2_protectionInfo

#define MK_CFG_C2_EXCEPTIONINFO				&MK_c2_exceptionInfo
#define MK_CFG_C2_PANICEXCEPTIONINFO		&MK_c2_panicExceptionInfo

#if MK_CFG_C2_NLOCKS > 0
#define MK_CFG_C2_LOCKTABLE					MK_c2_lockTable
#else
#define MK_CFG_C2_LOCKTABLE					MK_NULL
#endif

#if MK_CFG_C2_NJOBQUEUES > 0
#define MK_CFG_C2_JOBQUEUE					MK_c2_jobQueue
#define MK_CFG_C2_JOBQUEUECFG				MK_c2_jobQueueCfg
#define MK_CFG_C2_JOBQUEUEBUFFER			MK_c2_jobQueueBuffer
#else
#define MK_CFG_C2_JOBQUEUE					MK_NULL
#define MK_CFG_C2_JOBQUEUECFG				MK_NULL
#define MK_CFG_C2_JOBQUEUEBUFLEN			0
#define MK_CFG_C2_JOBQUEUEBUFFER			MK_NULL
#endif

#if MK_USE_ORTI_TRACE
#define MK_CFG_C2_ORTI_RUNNING_THREAD	&MK_c2_ortiRunningThread
#ifndef MK_ASM
extern volatile mk_uint32_t MK_c2_ortiRunningThread;
#endif
#else
#define MK_CFG_C2_ORTI_RUNNING_THREAD	MK_NULL
#endif

/* Stack configuration for core 2
*/
#ifndef MK_ASM
extern mk_stackelement_t MK_c2_kernelStack[MK_CFG_C2_KERNEL_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The idle and shutdown threads use the same stack. The size is the larger of the two.
*/
#if MK_CFG_C2_IDLE_STACK_NELEMENTS > MK_CFG_C2_SHUTDOWN_STACK_NELEMENTS
#define MK_CFG_C2_IDLESHUTDOWN_STACK_NELEMENTS	MK_CFG_C2_IDLE_STACK_NELEMENTS
#else
#define MK_CFG_C2_IDLESHUTDOWN_STACK_NELEMENTS	MK_CFG_C2_SHUTDOWN_STACK_NELEMENTS
#endif

#ifndef MK_ASM
extern mk_stackelement_t MK_c2_idleshutdownStack[MK_CFG_C2_IDLESHUTDOWN_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The error hook thread has a private stack
*/
#ifndef MK_ASM
#if MK_CFG_C2_HAS_ERRORHOOK
extern mk_stackelement_t MK_c2_errorhookStack[MK_CFG_C2_ERRORHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else
extern const mk_uint8_t MK_c2_noErrorHookStack;
#endif
#endif

/* The protection hook thread has a private stack
*/
#ifndef MK_ASM
#if MK_CFG_C2_HAS_PROTECTIONHOOK
extern mk_stackelement_t MK_c2_protectionHookStack[MK_CFG_C2_PROTECTIONHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else
extern const mk_uint8_t MK_c2_noProtectionHookStack;
#endif
#endif

#define MK_CFG_C2_AUX1_STACK_NELEMENTS	MK_CFG_C2_CTRSUB_STACK_NELEMENTS

#ifndef MK_ASM
extern mk_stackelement_t MK_c2_aux1Stack[MK_CFG_C2_AUX1_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#endif

/* The aux2 thread runs trusted function, init, startup hook and shutdown hook threads. Its stack is therefore
 * the largest of the four.
*/
#if MK_CFG_C2_INIT_STACK_NELEMENTS > MK_CFG_C2_TF_STACK_NELEMENTS
#define MK_CFG_C2_AUX2A_STACK_NELEMENTS	MK_CFG_C2_INIT_STACK_NELEMENTS
#else
#define MK_CFG_C2_AUX2A_STACK_NELEMENTS	MK_CFG_C2_TF_STACK_NELEMENTS
#endif

#if MK_CFG_C2_HAS_SHUTDOWNHOOK
#ifndef MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS
#error "MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS must be defined"
#endif
#else
#ifndef MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS
#define MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS	0
#endif
#endif

#if MK_CFG_C2_AUX2A_STACK_NELEMENTS > MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS
#define MK_CFG_C2_AUX2_STACK_NELEMENTS	MK_CFG_C2_AUX2A_STACK_NELEMENTS
#else
#define MK_CFG_C2_AUX2_STACK_NELEMENTS	MK_CFG_C2_SHUTDOWNHOOK_STACK_NELEMENTS
#endif

#ifndef MK_ASM
extern mk_stackelement_t MK_c2_aux2Stack[MK_CFG_C2_AUX2_STACK_NELEMENTS + MK_HW_STACK_EXTRA];

#if (MK_MAXCORES > 1)
extern mk_kernelcontrol_t MK_c2_coreVars;
#endif
extern volatile mk_syncspot_t MK_c2_syncSpot;

extern const mk_threadcfg_t MK_c2_idleThreadConfig;
extern const mk_threadcfg_t MK_c2_shutdownThreadConfig;
extern const mk_threadcfg_t MK_c2_bootThreadConfig;
extern const mk_threadcfg_t MK_c2_initThreadConfig;
extern const mk_threadcfg_t MK_c2_errorHookThreadConfig;
extern const mk_threadcfg_t MK_c2_protectionHookThreadConfig;
extern const mk_threadcfg_t MK_c2_shutdownHookThreadConfig;
extern mk_threadcfg_t MK_c2_ctrsubThreadConfig;
extern mk_threadcfg_t MK_c2_trustedFunctionThreadConfig;

extern mk_thread_t MK_c2_idleThread;
extern mk_thread_t MK_c2_aux1Thread;
extern mk_thread_t MK_c2_aux2Thread;
extern mk_thread_t MK_c2_errorHookThread;
extern mk_thread_t MK_c2_protectionHookThread;

extern mk_errorinfo_t MK_c2_errorInfo;
extern mk_protectioninfo_t MK_c2_protectionInfo;

extern mk_hwexceptioninfo_t MK_c2_exceptionInfo;
extern mk_hwexceptioninfo_t MK_c2_panicExceptionInfo;

#if MK_CFG_C2_NTASKS > 0
extern mk_task_t MK_c2_taskDynamic[MK_CFG_C2_NTASKS];
#endif

#if MK_CFG_C2_NTASKTHREADS > 0
extern mk_thread_t MK_c2_taskThreads[MK_CFG_C2_NTASKTHREADS];
#endif

#if MK_CFG_C2_NTASKREGISTERS > 0
extern mk_threadregisters_t MK_c2_taskRegisters[MK_CFG_C2_NTASKREGISTERS];
#endif

#if MK_CFG_C2_NETASKS > 0
extern mk_eventstatus_t MK_c2_eventStatus[MK_CFG_C2_NETASKS];
#endif

#if MK_CFG_C2_NISRS > 0
extern mk_isr_t MK_c2_isrDynamic[MK_CFG_C2_NISRS];
#endif

#if MK_CFG_C2_NISRTHREADS > 0
extern mk_thread_t MK_c2_isrThreads[MK_CFG_C2_NISRTHREADS];
#endif

#if MK_CFG_C2_NISRREGISTERS > 0
extern mk_threadregisters_t MK_c2_isrRegisters[MK_CFG_C2_NISRREGISTERS];
#endif

#if MK_CFG_C2_NLOCKS > 0
extern mk_lock_t MK_c2_lockTable[MK_CFG_C2_NLOCKS];
#endif

#if MK_CFG_C2_NJOBQUEUES > 0
extern mk_jobqueue_t MK_c2_jobQueue[MK_CFG_C2_NJOBQUEUES];
extern const mk_jobqueuecfg_t MK_c2_jobQueueCfg[MK_CFG_C2_NJOBQUEUES];
extern mk_jobelement_t MK_c2_jobQueueBuffer[MK_CFG_C2_JOBQUEUEBUFLEN];
#endif

#if MK_CFG_C2_NAPPLICATIONS > 0
extern mk_app_t MK_c2_appDynamic[MK_CFG_C2_NAPPLICATIONS];
#endif

#if ( 2 != 0 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) != 0
extern mk_message_t MK_c2_c0_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c0_removePtr;
extern mk_msgptrfield_t MK_c2_c0_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c0_queue;
#endif
#endif

#if ( 2 != 1 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) != 0
extern mk_message_t MK_c2_c1_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c1_removePtr;
extern mk_msgptrfield_t MK_c2_c1_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c1_queue;
#endif
#endif

#if ( 2 != 2 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) != 0
extern mk_message_t MK_c2_c2_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c2_removePtr;
extern mk_msgptrfield_t MK_c2_c2_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c2_queue;
#endif
#endif

#if ( 2 != 3 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) != 0
extern mk_message_t MK_c2_c3_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c3_removePtr;
extern mk_msgptrfield_t MK_c2_c3_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c3_queue;
#endif
#endif

#if ( 2 != 4 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C4 & MK_COREMAPBIT_C4) != 0
extern mk_message_t MK_c2_c4_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c4_removePtr;
extern mk_msgptrfield_t MK_c2_c4_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c4_queue;
#endif
#endif

#if ( 2 != 5 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C5 & MK_COREMAPBIT_C5) != 0
extern mk_message_t MK_c2_c5_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c5_removePtr;
extern mk_msgptrfield_t MK_c2_c5_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c5_queue;
#endif
#endif

#if ( 2 != 6 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C6 & MK_COREMAPBIT_C6) != 0
extern mk_message_t MK_c2_c6_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c6_removePtr;
extern mk_msgptrfield_t MK_c2_c6_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c6_queue;
#endif
#endif

#if ( 2 != 7 )		/* No buffers for communication with self */
#if (MK_COREMAPWORD_C7 & MK_COREMAPBIT_C7) != 0
extern mk_message_t MK_c2_c7_messageBuffer[MK_CFG_MAXMSG+1];
extern mk_msgptrfield_t MK_c2_c7_removePtr;
extern mk_msgptrfield_t MK_c2_c7_insertPtr;
extern const mk_msgqueuedescriptor_t MK_c2_c7_queue;
#endif
#endif


#if (MK_MAXCORES > 1)
extern mk_uint32_t MK_c2_initTestData;
extern mk_uint32_t MK_c2_initTestBss;
#define MK_C2_PTR_INITTEST_DATA	(&MK_c2_initTestData)
#define MK_C2_PTR_INITTEST_BSS	(&MK_c2_initTestBss)
#endif /* (MK_MAXCORES > 1) */

#if MK_HASHEAP
#define MK_C2_HEAP (&MK_c2_heap)
extern mk_heap_t MK_c2_heap;
#endif

#if (MK_CFG_C2_NSSTS > 0)
extern mk_sstcounter_t MK_c2_sstCounters[MK_CFG_C2_NSSTS];
#else /* MK_CFG_C2_NSSTS */
/* This declaration just exists to avoid violating MISRA-C:2012 rule 8.4. */
extern const mk_uint8_t MK_c2_sst_NOT_USED;
#endif /* MK_CFG_C2_NSSTS */

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)
#define MK_CFG_C2_COREPAGETABLES	MK_c2_partitionToPageTable
extern mk_pagetabledescriptor_t MK_c2_partitionToPageTable[MK_CFG_C2_NMEMORYPARTITIONS];
#endif

#endif /* MK_ASM */

#endif /* MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2 */

/* Define default ALCI mapping for backwards compatibility if no generator is used */
#ifndef MK_CFG_C2_ALCI_PHY_TO_LOG
#define MK_CFG_C2_ALCI_PHY_TO_LOG 2
#endif
#ifndef MK_CFG_C2_ALCI_LOG_TO_PHY
#define MK_CFG_C2_ALCI_LOG_TO_PHY 2
#endif

/* Some derivatives might have timers for EBM that are core-specific, with different frequencies */
#ifndef MK_ExecutionNsToTicks_c2
#define MK_ExecutionNsToTicks_c2 MK_ExecutionNsToTicks
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
