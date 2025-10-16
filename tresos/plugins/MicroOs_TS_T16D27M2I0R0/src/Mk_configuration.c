/* Mk_configuration.c
 *
 * This file contains the configuration for stacks and threads.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 *  Expressions resulting from the expansion of macro parameters shall be
 *  enclosed in parentheses.
 *
 * Reason:
 *  The lack of parentheses is intentional, because they would lead to syntax
 *  errors in the constructed initializer.
 *
 *
 * MISRAC2012-2) Deviated Rule: D4.5 (advisory)
 * Identifiers in the same name space with overlapping visibility should be
 * typographically unambiguous
 *
 * Reason:
 * MK_ANON_IDAT is the default start symbol for the anonymous init data section.
 * The "conflicting" MK_anonIDat is a pointer to it, as only its address matters.
*/

#include <Mk_kconfig.h>

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_error.h>
#include <public/Mk_callout.h>

#include <private/Mk_core.h>
#include <private/Mk_startup.h>
#include <private/Mk_thread.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_memoryprotection.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_exceptionhandling.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_trustedfunction.h>
#include <private/Mk_anondata.h>
#include <private/Mk_systemcontrol.h>

#if MK_HASHEAP
#include <private/Mk_heap.h>
#endif

#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* The master core.
*/
const mk_objectid_t MK_hwMasterCoreIndex = MK_CFG_HWMASTERCOREINDEX;

/* The constant MK_anonIDat refers to the base address of the ROM image of the
 * anonymous .data section. It is stored in a constant to prevent the compiler
 * from optimizing out a NULL check against this address.
*/
/* Deviation MISRAC2012-2 <+1> */
const mk_int8_t * const MK_anonIDat = &MK_MR_ANON_IDATA_START;
const mk_int8_t * const MK_cal_Core0_IDat = &MK_MR_CAL_CORE0_IDATA_START;
const mk_int8_t * const MK_cal_Core1_IDat = &MK_MR_CAL_CORE1_IDATA_START;
const mk_int8_t * const MK_cddDataCore1IDat = &MK_MR_MK_CDD_DATA_CORE1_IDAT_START;
const mk_int8_t * const MK_pspr_Core0_IDat = &MK_MR_PSPR_CORE0_IDATA_START;
const mk_int8_t * const MK_pspr_Core1_IDat = &MK_MR_PSPR_CORE1_IDATA_START;

/* Core properties (start mode, other properties can also go here.
*/
const mk_uint32_t MK_coreProperties[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_PROPERTIES,
				 MK_CFG_C1_PROPERTIES,
				 MK_CFG_C2_PROPERTIES,
				 MK_CFG_C3_PROPERTIES,
				 MK_CFG_C4_PROPERTIES,
				 MK_CFG_C5_PROPERTIES,
				 MK_CFG_C6_PROPERTIES,
				 MK_CFG_C7_PROPERTIES)
};

/* Synchronization spots
*/
volatile mk_syncspot_t * const MK_syncSpots[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_SYNCSPOT,
				 MK_CFG_C1_SYNCSPOT,
				 MK_CFG_C2_SYNCSPOT,
				 MK_CFG_C3_SYNCSPOT,
				 MK_CFG_C4_SYNCSPOT,
				 MK_CFG_C5_SYNCSPOT,
				 MK_CFG_C6_SYNCSPOT,
				 MK_CFG_C7_SYNCSPOT)
};

/* The core table
*/
mk_kernelcontrol_t * const MK_coreTable[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_COREVARS,
				 MK_CFG_C1_COREVARS,
				 MK_CFG_C2_COREVARS,
				 MK_CFG_C3_COREVARS,
				 MK_CFG_C4_COREVARS,
				 MK_CFG_C5_COREVARS,
				 MK_CFG_C6_COREVARS,
				 MK_CFG_C7_COREVARS)
};

/* Constants for initializing the stack pointer on entry to the kernel.
*/
mk_stackelement_t * const MK_kernelStackTop[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_KERNSPINITIAL,
				 MK_CFG_C1_KERNSPINITIAL,
				 MK_CFG_C2_KERNSPINITIAL,
				 MK_CFG_C3_KERNSPINITIAL,
				 MK_CFG_C4_KERNSPINITIAL,
				 MK_CFG_C5_KERNSPINITIAL,
				 MK_CFG_C6_KERNSPINITIAL,
				 MK_CFG_C7_KERNSPINITIAL)
};

/* Idle thread configuration
*/
const mk_threadcfg_t * const MK_idleThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_IDLE,
				 MK_CFG_C1_THRCFG_IDLE,
				 MK_CFG_C2_THRCFG_IDLE,
				 MK_CFG_C3_THRCFG_IDLE,
				 MK_CFG_C4_THRCFG_IDLE,
				 MK_CFG_C5_THRCFG_IDLE,
				 MK_CFG_C6_THRCFG_IDLE,
				 MK_CFG_C7_THRCFG_IDLE)
};

/* Shutdown thread configuration
*/
const mk_threadcfg_t * const MK_shutdownThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_SHUTDOWN,
				 MK_CFG_C1_THRCFG_SHUTDOWN,
				 MK_CFG_C2_THRCFG_SHUTDOWN,
				 MK_CFG_C3_THRCFG_SHUTDOWN,
				 MK_CFG_C4_THRCFG_SHUTDOWN,
				 MK_CFG_C5_THRCFG_SHUTDOWN,
				 MK_CFG_C6_THRCFG_SHUTDOWN,
				 MK_CFG_C7_THRCFG_SHUTDOWN)
};

/* Counter subsystwm thread configuration
*/
mk_threadcfg_t * const MK_ctrsubThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_CTRSUB,
				 MK_CFG_C1_THRCFG_CTRSUB,
				 MK_CFG_C2_THRCFG_CTRSUB,
				 MK_CFG_C3_THRCFG_CTRSUB,
				 MK_CFG_C4_THRCFG_CTRSUB,
				 MK_CFG_C5_THRCFG_CTRSUB,
				 MK_CFG_C6_THRCFG_CTRSUB,
				 MK_CFG_C7_THRCFG_CTRSUB)
};

/* Trusted function thread configuration
*/
mk_threadcfg_t * const MK_trustedFunctionThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_TRUSTEDFUNCTION,
				 MK_CFG_C1_THRCFG_TRUSTEDFUNCTION,
				 MK_CFG_C2_THRCFG_TRUSTEDFUNCTION,
				 MK_CFG_C3_THRCFG_TRUSTEDFUNCTION,
				 MK_CFG_C4_THRCFG_TRUSTEDFUNCTION,
				 MK_CFG_C5_THRCFG_TRUSTEDFUNCTION,
				 MK_CFG_C6_THRCFG_TRUSTEDFUNCTION,
				 MK_CFG_C7_THRCFG_TRUSTEDFUNCTION)
};

/* Error hook thread configuration
*/
const mk_threadcfg_t * const MK_errorHookThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_ERRORHOOK,
				 MK_CFG_C1_THRCFG_ERRORHOOK,
				 MK_CFG_C2_THRCFG_ERRORHOOK,
				 MK_CFG_C3_THRCFG_ERRORHOOK,
				 MK_CFG_C4_THRCFG_ERRORHOOK,
				 MK_CFG_C5_THRCFG_ERRORHOOK,
				 MK_CFG_C6_THRCFG_ERRORHOOK,
				 MK_CFG_C7_THRCFG_ERRORHOOK)
};

/* Protection hook thread configuration
*/
const mk_threadcfg_t * const MK_protectionHookThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_PROTECTIONHOOK,
				 MK_CFG_C1_THRCFG_PROTECTIONHOOK,
				 MK_CFG_C2_THRCFG_PROTECTIONHOOK,
				 MK_CFG_C3_THRCFG_PROTECTIONHOOK,
				 MK_CFG_C4_THRCFG_PROTECTIONHOOK,
				 MK_CFG_C5_THRCFG_PROTECTIONHOOK,
				 MK_CFG_C6_THRCFG_PROTECTIONHOOK,
				 MK_CFG_C7_THRCFG_PROTECTIONHOOK)
};

/* Dummy boot thread configuration
*/
const mk_threadcfg_t * const MK_bootThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_BOOT,
				 MK_CFG_C1_THRCFG_BOOT,
				 MK_CFG_C2_THRCFG_BOOT,
				 MK_CFG_C3_THRCFG_BOOT,
				 MK_CFG_C4_THRCFG_BOOT,
				 MK_CFG_C5_THRCFG_BOOT,
				 MK_CFG_C6_THRCFG_BOOT,
				 MK_CFG_C7_THRCFG_BOOT)
};

/* Init ("main") thread configuration
*/
const mk_threadcfg_t * const MK_initThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_INIT,
				 MK_CFG_C1_THRCFG_INIT,
				 MK_CFG_C2_THRCFG_INIT,
				 MK_CFG_C3_THRCFG_INIT,
				 MK_CFG_C4_THRCFG_INIT,
				 MK_CFG_C5_THRCFG_INIT,
				 MK_CFG_C6_THRCFG_INIT,
				 MK_CFG_C7_THRCFG_INIT)
};

/* Shutdown hook thread configuration
*/
const mk_threadcfg_t * const MK_shutdownHookThreadConfig[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THRCFG_SHUTDOWNHOOK,
				 MK_CFG_C1_THRCFG_SHUTDOWNHOOK,
				 MK_CFG_C2_THRCFG_SHUTDOWNHOOK,
				 MK_CFG_C3_THRCFG_SHUTDOWNHOOK,
				 MK_CFG_C4_THRCFG_SHUTDOWNHOOK,
				 MK_CFG_C5_THRCFG_SHUTDOWNHOOK,
				 MK_CFG_C6_THRCFG_SHUTDOWNHOOK,
				 MK_CFG_C7_THRCFG_SHUTDOWNHOOK)
};

/* Idle threads
*/
mk_thread_t * const MK_idleThread[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THREAD_IDLE,
				 MK_CFG_C1_THREAD_IDLE,
				 MK_CFG_C2_THREAD_IDLE,
				 MK_CFG_C3_THREAD_IDLE,
				 MK_CFG_C4_THREAD_IDLE,
				 MK_CFG_C5_THREAD_IDLE,
				 MK_CFG_C6_THREAD_IDLE,
				 MK_CFG_C7_THREAD_IDLE)
};

/* Error hook threads
*/
mk_thread_t * const MK_errorHookThread[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THREAD_ERRORHOOK,
				 MK_CFG_C1_THREAD_ERRORHOOK,
				 MK_CFG_C2_THREAD_ERRORHOOK,
				 MK_CFG_C3_THREAD_ERRORHOOK,
				 MK_CFG_C4_THREAD_ERRORHOOK,
				 MK_CFG_C5_THREAD_ERRORHOOK,
				 MK_CFG_C6_THREAD_ERRORHOOK,
				 MK_CFG_C7_THREAD_ERRORHOOK)
};

/* Protection hook threads
*/
mk_thread_t * const MK_protectionHookThread[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THREAD_PROTECTIONHOOK,
				 MK_CFG_C1_THREAD_PROTECTIONHOOK,
				 MK_CFG_C2_THREAD_PROTECTIONHOOK,
				 MK_CFG_C3_THREAD_PROTECTIONHOOK,
				 MK_CFG_C4_THREAD_PROTECTIONHOOK,
				 MK_CFG_C5_THREAD_PROTECTIONHOOK,
				 MK_CFG_C6_THREAD_PROTECTIONHOOK,
				 MK_CFG_C7_THREAD_PROTECTIONHOOK)
};

/* Auxiliary threads
*/
mk_thread_t * const MK_aux1Thread[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THREAD_AUX1,
				 MK_CFG_C1_THREAD_AUX1,
				 MK_CFG_C2_THREAD_AUX1,
				 MK_CFG_C3_THREAD_AUX1,
				 MK_CFG_C4_THREAD_AUX1,
				 MK_CFG_C5_THREAD_AUX1,
				 MK_CFG_C6_THREAD_AUX1,
				 MK_CFG_C7_THREAD_AUX1)
};

mk_thread_t * const MK_aux2Thread[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_THREAD_AUX2,
				 MK_CFG_C1_THREAD_AUX2,
				 MK_CFG_C2_THREAD_AUX2,
				 MK_CFG_C3_THREAD_AUX2,
				 MK_CFG_C4_THREAD_AUX2,
				 MK_CFG_C5_THREAD_AUX2,
				 MK_CFG_C6_THREAD_AUX2,
				 MK_CFG_C7_THREAD_AUX2)
};

/* Error information to be made available to the user
*/
mk_errorinfo_t * const MK_errorInfo[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_ERRORINFO,
				 MK_CFG_C1_ERRORINFO,
				 MK_CFG_C2_ERRORINFO,
				 MK_CFG_C3_ERRORINFO,
				 MK_CFG_C4_ERRORINFO,
				 MK_CFG_C5_ERRORINFO,
				 MK_CFG_C6_ERRORINFO,
				 MK_CFG_C7_ERRORINFO)
};

/* Protection fault information to be made available to the user
*/
mk_protectioninfo_t * const MK_protectionInfo[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_PROTECTIONINFO,
				 MK_CFG_C1_PROTECTIONINFO,
				 MK_CFG_C2_PROTECTIONINFO,
				 MK_CFG_C3_PROTECTIONINFO,
				 MK_CFG_C4_PROTECTIONINFO,
				 MK_CFG_C5_PROTECTIONINFO,
				 MK_CFG_C6_PROTECTIONINFO,
				 MK_CFG_C7_PROTECTIONINFO)
};

/* Hardware-specific exception information to be made available to the user
*/
mk_hwexceptioninfo_t * const MK_exceptionInfo[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_EXCEPTIONINFO,
				 MK_CFG_C1_EXCEPTIONINFO,
				 MK_CFG_C2_EXCEPTIONINFO,
				 MK_CFG_C3_EXCEPTIONINFO,
				 MK_CFG_C4_EXCEPTIONINFO,
				 MK_CFG_C5_EXCEPTIONINFO,
				 MK_CFG_C6_EXCEPTIONINFO,
				 MK_CFG_C7_EXCEPTIONINFO)
};
mk_hwexceptioninfo_t * const MK_panicExceptionInfo[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_PANICEXCEPTIONINFO,
				 MK_CFG_C1_PANICEXCEPTIONINFO,
				 MK_CFG_C2_PANICEXCEPTIONINFO,
				 MK_CFG_C3_PANICEXCEPTIONINFO,
				 MK_CFG_C4_PANICEXCEPTIONINFO,
				 MK_CFG_C5_PANICEXCEPTIONINFO,
				 MK_CFG_C6_PANICEXCEPTIONINFO,
				 MK_CFG_C7_PANICEXCEPTIONINFO)
};

/* Message queues
*/
const mk_msgqueuepair_t * const MK_messageQueues[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_c0_queues,
				 MK_c1_queues,
				 MK_c2_queues,
				 MK_c3_queues,
				 MK_c4_queues,
				 MK_c5_queues,
				 MK_c6_queues,
				 MK_c7_queues)
};

/* Configuration for floating-point unit (if needed)
*/
#if MK_HAS_FPUCRVALUE
/* If the initial value is not configured, zero is assumed.
 * The value is the same for all cores.
*/
#ifndef MK_FPUCRVALUE
#define MK_FPUCRVALUE	0u
#endif

const mk_fpucrvalue_t MK_threadFpuCrValue = MK_FPUCRVALUE;

#endif

/* Time stamp clock factors for the 1u, 10u and 100u conversion functions.
*/
#if MK_HAS_TIMESTAMPCLOCKFACTOR100U
const mk_uint16_t MK_timestampClockFactor100u = MK_TIMESTAMPCLOCKFACTOR100U;
#endif

#if MK_HAS_TIMESTAMPCLOCKFACTOR10U
const mk_uint16_t MK_timestampClockFactor10u = MK_TIMESTAMPCLOCKFACTOR10U;
#endif

#if MK_HAS_TIMESTAMPCLOCKFACTOR1U
const mk_uint16_t MK_timestampClockFactor1u = MK_TIMESTAMPCLOCKFACTOR1U;
#endif

/* A user-defined callout function for MK_StartupPanic().
 * The same function is used on all cores.
*/
#if MK_HAS_USERPANICSTOP
#define MK_CALLOUTSTARTUPPANIC	MK_USERPANICSTOP
#else
#define MK_CALLOUTSTARTUPPANIC	MK_NULL
#endif

const mk_paniccallout_t MK_startupPanicCallout = MK_CALLOUTSTARTUPPANIC;

/* Core-local init test variables:
*/
#if (MK_MAXCORES > 1)
mk_uint32_t * const MK_initTestDataTable[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_C0_PTR_INITTEST_DATA,
				 MK_C1_PTR_INITTEST_DATA,
				 MK_C2_PTR_INITTEST_DATA,
				 MK_C3_PTR_INITTEST_DATA,
				 MK_C4_PTR_INITTEST_DATA,
				 MK_C5_PTR_INITTEST_DATA,
				 MK_C6_PTR_INITTEST_DATA,
				 MK_C7_PTR_INITTEST_DATA)
};
mk_uint32_t * const MK_initTestBssTable[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_C0_PTR_INITTEST_BSS,
				 MK_C1_PTR_INITTEST_BSS,
				 MK_C2_PTR_INITTEST_BSS,
				 MK_C3_PTR_INITTEST_BSS,
				 MK_C4_PTR_INITTEST_BSS,
				 MK_C5_PTR_INITTEST_BSS,
				 MK_C6_PTR_INITTEST_BSS,
				 MK_C7_PTR_INITTEST_BSS)
};
#endif

#if MK_HASHEAP

mk_heap_t * const MK_coreHeaps[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_C0_HEAP,
				 MK_C1_HEAP,
				 MK_C2_HEAP,
				 MK_C3_HEAP,
				 MK_C4_HEAP,
				 MK_C5_HEAP,
				 MK_C6_HEAP,
				 MK_C7_HEAP)
};

#endif

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)

mk_pagetabledescriptor_t * const MK_corePageTables[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_COREPAGETABLES,
				 MK_CFG_C1_COREPAGETABLES,
				 MK_CFG_C2_COREPAGETABLES,
				 MK_CFG_C3_COREPAGETABLES,
				 MK_CFG_C4_COREPAGETABLES,
				 MK_CFG_C5_COREPAGETABLES,
				 MK_CFG_C6_COREPAGETABLES,
				 MK_CFG_C7_COREPAGETABLES)
};

#endif

#if MK_MAXCORES > 1

const mk_objectid_t MK_alciPhyToLog[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_ALCI_PHY_TO_LOG,
				 MK_CFG_C1_ALCI_PHY_TO_LOG,
				 MK_CFG_C2_ALCI_PHY_TO_LOG,
				 MK_CFG_C3_ALCI_PHY_TO_LOG,
				 MK_CFG_C4_ALCI_PHY_TO_LOG,
				 MK_CFG_C5_ALCI_PHY_TO_LOG,
				 MK_CFG_C6_ALCI_PHY_TO_LOG,
				 MK_CFG_C7_ALCI_PHY_TO_LOG)
};
const mk_objectid_t MK_alciLogToPhy[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_ALCI_LOG_TO_PHY,
				 MK_CFG_C1_ALCI_LOG_TO_PHY,
				 MK_CFG_C2_ALCI_LOG_TO_PHY,
				 MK_CFG_C3_ALCI_LOG_TO_PHY,
				 MK_CFG_C4_ALCI_LOG_TO_PHY,
				 MK_CFG_C5_ALCI_LOG_TO_PHY,
				 MK_CFG_C6_ALCI_LOG_TO_PHY,
				 MK_CFG_C7_ALCI_LOG_TO_PHY)
};

#endif

#if MK_USE_ORTI_TRACE
volatile mk_uint32_t * const MK_ortiRunningThread[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(MK_CFG_C0_ORTI_RUNNING_THREAD,
				 MK_CFG_C1_ORTI_RUNNING_THREAD,
				 MK_CFG_C2_ORTI_RUNNING_THREAD,
				 MK_CFG_C3_ORTI_RUNNING_THREAD,
				 MK_CFG_C4_ORTI_RUNNING_THREAD,
				 MK_CFG_C5_ORTI_RUNNING_THREAD,
				 MK_CFG_C6_ORTI_RUNNING_THREAD,
				 MK_CFG_C7_ORTI_RUNNING_THREAD)
};
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
