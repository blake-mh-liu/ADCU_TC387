/* Ioc_ARM_core.h - ARM core header
 *
 * This file contains definitions for features that are common across all
 * the ARM architectures.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_020]
 *  An #ifndef is not permitted to have an #else statement!
 *
 * Reason:
 *  We must use #else here, because the macro EB_STATIC_CHECK is provided by
 *  external tooling outside the control of the IOC build.
 *  EB_STATIC_CHECK is used to hide tool specific extensions
 *  which would otherwise break the MISRA checker run.
*/

#ifndef IOC_ARM_CORE_H
#define IOC_ARM_CORE_H

#include <public/Ioc_basic_types.h>
#include <private/Ioc_types_forward.h>
#include <private/Ioc_hw_characteristics.h>
#include <private/ARM/Ioc_ARM_tool.h>


/* ioc_extinput_t contains a pointer, therefore it must be aligned to four byte boundaries.
 *
 * !LINKSTO IOC.ARM.Macro.IOC_HwWellAlignedExtInput, 1
*/
#define IOC_HwWellAlignedExtInput(address)	((((ioc_address_t)(address)) & 3u) == 0u)

/* IOC_HwMemoryBarrier()
 *
 * Currently we assume that reordering could be observed on all multi-core machines.
 *
 * !LINKSTO IOC.ARM.Macro.IOC_HwMemoryBarrier, 1
*/
#define IOC_HW_HAS_WEAK_MEM_ORDERING 1
#if (IOC_MAXCORES > 1)
/* Deviation DCG-1 <+5> */
#ifndef EB_STATIC_CHECK
#define IOC_HwMemoryBarrier()	IOC_ARM_DSB()
#else
#define IOC_HwMemoryBarrier()	do { /* nothing */ } while (0)
#endif
#else /* IOC_MAXCORES */
#define IOC_HwMemoryBarrier()	do { /* nothing */ } while (0)
#endif /* IOC_MAXCORES */


#endif /* IOC_ARM_CORE_H */
