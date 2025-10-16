/* Ioc_ARM64_core.h - ARM64 core header
 *
 * This file contains definitions for features that are common across all
 * the ARM64 architectures.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef directives are not permitted.
 *
 * Reason:
 *  We must use #ifdef here, because the macro EB_STATIC_CHECK is provided by
 *  external tooling outside the control of the IOC build.
 *  EB_STATIC_CHECK is used to hide tool specific extensions
 *  which would otherwise break the MISRA checker run.
*/

#ifndef IOC_ARM64_CORE_H
#define IOC_ARM64_CORE_H

#include <public/Ioc_basic_types.h>
#include <private/Ioc_types_forward.h>

/* IOC_HW_HAS_WEAK_MEM_ORDERING - the ARM64 has a weak memory ordering.
 *
 * The ARM v8A has weak memory ordering, meaning that additional memory barrier instructions must
 * be added to the code, in order to ensure that data accesses are made in the correct sequence
 * for the used algorithms.
*/
#define IOC_HW_HAS_WEAK_MEM_ORDERING   1

/* ioc_extinput_t contains a pointer, therefore it must be aligned to eight byte boundaries.
 *
 * !LINKSTO IOC.ARM64.Macro.IOC_HwWellAlignedExtInput, 1
*/
#define IOC_HwWellAlignedExtInput(address)	((((ioc_address_t)(address)) & 7u) == 0u)

/* IOC_HwMemoryBarrier()
 *
 * This macro is used to create a memory barrier, memory operations before it to be finished and
 * all later memory operations to wait for the end of the barrier.
 *
 * !LINKSTO IOC.ARM64.Macro.IOC_HwMemoryBarrier, 1
*/
/* Deviation DCG-1 <+5> */
#ifdef EB_STATIC_CHECK
#define IOC_HwMemoryBarrier()       do {} while(0)
#else
#define IOC_HwMemoryBarrier()       do { __asm__ volatile("dmb	sy"); } while(0)
#endif

#endif /* IOC_ARM64_CORE_H */
