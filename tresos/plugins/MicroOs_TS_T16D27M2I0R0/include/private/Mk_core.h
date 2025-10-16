/* Mk_core.h - core definitions and data structures
 *
 * This file defines core related macros and data structures. It also contains function prototypes
 * and constant/variable declarations that are related to the processor core(s).
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_CORE_H
#define MK_CORE_H

#include <public/Mk_public_types.h>
#include <public/Mk_hwsel.h>
#include MK_HWSEL_PRV_CORE
#include <private/Mk_core_master_index.h>
#include <private/Mk_thread.h>
#include <private/Mk_panic.h>
#include <private/Mk_types_forward.h>
#include <private/Mk_tool.h>
#if MK_HASHEAP
#include <private/Mk_heap.h>
#endif

/* The microkernel can be configured to run on any combination of the cores on a microcontroller.
 * The configuration macros MK_CFG_COREMAP_x inform the microkernel which cores are in use.
 *
 * This mechanism supports up to 32 cores per macro, but in principle there can be as many macros
 * as we need. The macros MK_COREMAPWORD_Cn and MK_COREMAPBIT_Cn tell the microkernel which bit of which
 * coremap macro is the enable bit for core n.
*/
#define MK_COREMAPWORD_C0		MK_CFG_COREMAP_0
#define MK_COREMAPWORD_C1		MK_CFG_COREMAP_0
#define MK_COREMAPWORD_C2		MK_CFG_COREMAP_0
#define MK_COREMAPWORD_C3		MK_CFG_COREMAP_0
#define MK_COREMAPWORD_C4		MK_CFG_COREMAP_0
#define MK_COREMAPWORD_C5		MK_CFG_COREMAP_0
#define MK_COREMAPWORD_C6		MK_CFG_COREMAP_0
#define MK_COREMAPWORD_C7		MK_CFG_COREMAP_0
#define MK_COREMAPBIT_C0		0x1u
#define MK_COREMAPBIT_C1		0x2u
#define MK_COREMAPBIT_C2		0x4u
#define MK_COREMAPBIT_C3		0x8u
#define MK_COREMAPBIT_C4		0x10u
#define MK_COREMAPBIT_C5		0x20u
#define MK_COREMAPBIT_C6		0x40u
#define MK_COREMAPBIT_C7		0x80u

/* MK_COREARRAY() - create an initializer array
 *
 * This macro expands to the correct number of elements for the number of physical cores
 * that are present on the hardware.
*/
#if (MK_MAXCORES < 1u)
#error "The microkernel needs at least one core to run on!"
#endif
#if MK_MAXCORES == 1u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0
#elif MK_MAXCORES == 2u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0, c1
#elif MK_MAXCORES == 3u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0, c1, c2
#elif MK_MAXCORES == 4u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0, c1, c2, c3
#elif MK_MAXCORES == 5u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0, c1, c2, c3, c4,
#elif MK_MAXCORES == 6u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0, c1, c2, c3, c4, c5
#elif MK_MAXCORES == 7u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0, c1, c2, c3, c4, c5, c6
#elif MK_MAXCORES == 8u
#define MK_COREARRAY(c0, c1, c2, c3, c4, c5, c6, c7)	c0, c1, c2, c3, c4, c5, c6, c7
#else
#error "Microcontrollers with more than 8 cores are not supported."
#endif

#ifndef MK_ASM

/* mk_syncspot_t
 *
 * A type for the syncspot variables.
*/
typedef mk_uint8_t mk_syncspot_t;

/* mk_kernelcontrol_t
 *
 * A structure containing all the kernel control variables that have one copy per core.
 * mk_kernelcontrol_t is defined in <private/Mk_types_forward.h>.
*/
struct mk_kernelcontrol_s
{
	mk_thread_t *currentThread;					/* Currently-running thread */
	mk_stackelement_t *kernelStackTop;			/* Top of kernel stack */
	mk_thread_t *threadQueueHead;				/* Head of thread queue */
	mk_objectid_t currentMemoryPartition;		/* Index of current (dynamic) memory partition */
	mk_objectid_t coreIndex;					/* The core index (for use with rom arrays) */
	mk_objectid_t coreIndexLogical;				/* The logical core index (for use with rom arrays) */
	mk_corestate_t coreState;					/* Core state - up/down etc. */
	mk_tick_t dispatchTime;						/* Time of last dispatch */
	mk_panic_t panicReason;						/* The panic reason */
	mk_threadprio_t ctrsubBasePrio;				/* The lowest priority for counter subsystem threads. */
	mk_threadprio_t ctrsubCallerMaxPrio;		/* Threads with a higher priority must not call the ctr subsystem. */
	mk_uint32_t nDroppedMessages;				/* The number of cross-core messages that have been dropped. */
	mk_uint32_t nDroppedJobs;					/* The number of cross-core requests that have been dropped. */
	mk_boolean_t execBudgetIsConfigured;		/* One or more objects on this core has an execution budget */

	mk_thread_t *aux1Thread;					/* The 1st auxiliary thread */
	mk_thread_t *aux2Thread;					/* The 2nd auxiliary thread */

	/* The following thread configs are not const because the MK pokes various parameters (function, memory partition
	 * etc.) into the config structure before starting the thread.
	*/
	mk_threadcfg_t *ctrsubThreadConfig;			/* Configuration for counter subsystem threads */
	mk_threadcfg_t *tfThreadConfig;				/* Configuration for Trusted Function threads */

	mk_appmodeid_t ctrsubAppMode;				/* The OsAppMode proposal of the current core. */

#if MK_MAXCORES > 1
	mk_uint32_t cookieGen;						/* Cookie generation */
#endif

#if MK_HASHEAP
	mk_heap_t *heap;							/* Head of core-local heap's free list */
#endif

#if MK_HW_HAS_KERNELCONTROL
	mk_hwkernelcontrol_t hwControl;				/* Hardware-specific kernel control variables */
#endif
};

#endif

/* Offsets for assembly language
*/
#if (MK_HWWORDLENGTH == 32)

/* Offsets for 32-bit processors
*/
#define MK_CV_CURRTHREAD		MK_U(0)
#define MK_CV_KSTACKTOP			MK_U(4)
#define MK_CV_CURRMEMPAR		MK_U(12)

#elif (MK_HWWORDLENGTH == 64)

/* Offsets for 64-bit processors
*/
#define MK_CV_CURRTHREAD		MK_U(0)
#define MK_CV_KSTACKTOP			MK_U(8)
#define MK_CV_CURRMEMPAR		MK_U(24)

#else

#error "Offsets for other hardware types need to be defined."

#endif


#ifndef MK_ASM
/* MK_GetCoreVars() - return the (address of) the core variables for the core we're running on
 *
 * The implementation depends on whether the system is a multi-core system:
 *	- on multi-core hardware we must get the core ID and validate it
 *	- on single-core hardware (or if configured for single-core operation), MK_c0_coreVars always exists.
*/
#if (MK_MAXCORES > 1u)

/* On multi-core hardware configured for multi-core operation, MK_GetCoreVars returns
 * a valid mk_kernelcontrol_t pointer.
 *
 * !LINKSTO Microkernel.Function.MK_GetCoreVars, 1
 * !LINKSTO Microkernel.Function.MK_GetCoreVarsStartup, 1
 * !LINKSTO Microkernel.Function.MK_GetCoreVarsFromThread, 1
 * !doctype src
*/
#define MK_GetCoreVars()			MK_HwGetCoreVars()
#define MK_GetCoreVarsStartup()		MK_HwGetCoreVarsStartup()
#define MK_GetCoreVarsFromThread()	MK_HwGetCoreVarsFromThread()

#else

extern mk_kernelcontrol_t MK_c0_coreVars;

#define MK_GetCoreVars()			(&MK_c0_coreVars)
#define MK_GetCoreVarsStartup()		(&MK_c0_coreVars)
#define MK_GetCoreVarsFromThread()	(&MK_c0_coreVars)

#endif /* MK_MAXCORES > 1u */

/* MK_StartupCheckCoreVars - Check structure offsets of mk_kernelcontrol_t
 * with offset definitions for assembly language.
*/
void MK_StartupCheckCoreVars(void);

/* Bit fields in MK_coreProperties[i]
*/
#define MK_COREPROP_STARTMASK		0x03u		/* BitMask used to find startup type:[not used, manual, auto]. */
#define MK_COREPROP_NOTUSED			0x00u		/* Core is not used by this OS instance */
#define MK_COREPROP_STARTMANUAL		0x01u		/* Core must be started my means of StartCore */
#define MK_COREPROP_STARTAUTO		0x02u		/* Core starts automatically - StartCore must not be used. */

/* Generic corevars function. This can be used by the HW implementation if needed.
 *
 * !LINKSTO Microkernel.Function.MK_GenericGetCoreVarsStartup, 1
 * !doctype src
*/
mk_kernelcontrol_t *MK_GenericGetCoreVarsStartup(void);

extern mk_kernelcontrol_t * const MK_coreTable[MK_MAXCORES];
extern const mk_uint32_t MK_coreProperties[MK_MAXCORES];
extern volatile mk_syncspot_t * const MK_syncSpots[MK_MAXCORES];


/* The dispatcher and other prototypes.
*/
void MK_Dispatch(mk_kernelcontrol_t *) MK_ATTR_NORETURN;
void MK_InitCoreVars(mk_kernelcontrol_t *);
void MK_ClearCoreVars(mk_kernelcontrol_t *);
mk_threadprio_t MK_CalculateCtrSubCallerMaxPrio(const mk_kernelcontrol_t *);

mk_appmodeid_t MK_InternGetAppModeVoteOfCore(mk_objectid_t);

/* Synchronization barriers:
 *
 * - MK_SyncHere acts as a synchronization barrier for all cores.
 *   If there's only one core, there is nothing to do.
 * - MK_StartupCheckSyncHere is a helper function for MK_Startup, which checks whether the current core's
 *   sync spot has been initialized correctly. If there's only one core, there is nothing to do.
*/
#if (MK_MAXCORES > 1u)
void MK_SyncHere(void);
void MK_StartupCheckSyncHere(void);
#else
#define MK_SyncHere() do { } while (0)
#define MK_StartupCheckSyncHere() do { } while (0)
#endif

#if (MK_MAXCORES > 1u)
/* ALCI look-up tables - If there's only one core, these mappings are not required. */
extern const mk_objectid_t MK_alciPhyToLog[MK_MAXCORES];
extern const mk_objectid_t MK_alciLogToPhy[MK_MAXCORES];
#endif

#ifndef MK_COREID_VALUE_RESTORE_REQUIRED
#define MK_COREID_VALUE_RESTORE_REQUIRED		0
#endif

#endif /* MK_ASM */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
