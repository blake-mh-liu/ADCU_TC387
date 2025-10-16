/* Ioc_RH850_core.h - RH850 core header
 *
 * This file contains definitions for features that are common across all
 * the RH850 derivatives.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef IOC_RH850_CORE_H
#define IOC_RH850_CORE_H

#include <public/Ioc_basic_types.h>
#include <private/Ioc_types_forward.h>
#include <private/RH850/Ioc_RH850_compiler.h>
#include <private/Ioc_hw_characteristics.h>

/* ioc_extinput_t contains a pointer, therefore it must be aligned to four byte boundaries.
 *
 * !LINKSTO IOC.RH850.Macro.IOC_HwWellAlignedExtInput, 1
*/
#define IOC_HwWellAlignedExtInput(address)	((((ioc_address_t)(address)) & 3u) == 0u)

/* IOC_HwMemoryBarrier()
 *
 * Currently we assume that reordering could be observed on all multi-core machines.
 *
 * !LINKSTO IOC.RH850.Macro.IOC_HwMemoryBarrier, 1
*/
#define IOC_HW_HAS_WEAK_MEM_ORDERING 1
#if (IOC_MAXCORES > 1)
#define IOC_HwMemoryBarrier()	IOC_SYNCM()
#else /* IOC_MAXCORES */
#define IOC_HwMemoryBarrier()	do { /* nothing */ } while (0)
#endif /* IOC_MAXCORES */

#endif /* IOC_RH850_CORE_H */
