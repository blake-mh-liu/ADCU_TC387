/* Ioc_TRICORE_core.h - Tricore core header
 *
 * This file contains definitions for features that are common across all
 * the Tricore architectures.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * Depending on the configuration, this type is used.
*/
#ifndef IOC_TRICORE_CORE_H
#define IOC_TRICORE_CORE_H

#include <public/Ioc_basic_types.h>
#include <private/TRICORE/Ioc_TRICORE_compiler.h>
#include <private/Ioc_hw_characteristics.h>

#ifndef IOC_ASM

/* Note: Spinlock variables must not be mapped to cached segments on Aurix (SM_AURIX_16)
*/
/* Deviation MISRAC2012-1 <+1> */
typedef volatile ioc_uint32_t ioc_hwspinlockvar_t;

/* IOC_HwTrySpinlock
 *
 * Tries to take spinlock 'l' once.
 * There's no need to invalidate cache-lines on Aurix (SM_AURIX_16)
 *
 * !LINKSTO IOC.Macro.IOC_HwTrySpinlock, 2
*/
#define IOC_HwTrySpinlock(l)			IOC_TestAndTestAndSet(l)

/* IOC_HwDropSpinlock
 *
 * Releases spinlock 'l'.
 *
 * !LINKSTO IOC.Macro.IOC_HwDropSpinlock, 2
*/
#define IOC_HwDropSpinlock(l)			do { \
	IOC_DSYNC(); \
	*(l) = 0u; \
} while(0)

/* TRICORE has user-mode spinlocks.
*/
#define IOC_HW_HAS_LOCK_INTER_USER	1

/* ioc_extinput_t contains a pointer, therefore it must be aligned to four byte boundaries.
 *
 * !LINKSTO IOC.Macro.IOC_HwWellAlignedExtInput, 1
*/
#define IOC_HwWellAlignedExtInput(address)	((((ioc_address_t)(address)) & 3u) == 0u)

/* IOC_HwMemoryBarrier()
 *
 * Currently we assume that reordering could be observed on all multi-core machines.
 *
 * !LINKSTO IOC.TRICORE.Macro.IOC_HwMemoryBarrier, 1
*/
#define IOC_HW_HAS_WEAK_MEM_ORDERING 1
#if (IOC_MAXCORES > 1)
#define IOC_HwMemoryBarrier()	IOC_DSYNC()
#else /* IOC_MAXCORES */
#define IOC_HwMemoryBarrier()	do { /* nothing */ } while (0)
#endif /* IOC_MAXCORES */

#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
