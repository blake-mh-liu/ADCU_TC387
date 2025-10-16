/* Ioc_PA_core.h - PA core header
 *
 * This file contains definitions for features that are common across all
 * the PA architectures.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef IOC_PA_CORE_H
#define IOC_PA_CORE_H

#include <public/Ioc_basic_types.h>
#include <private/Ioc_hw_characteristics.h>
#include <private/PA/Ioc_PA_tool.h>

/* ioc_extinput_t contains a pointer, therefore it must be aligned to four byte boundaries.
 *
 * !LINKSTO IOC.PA.Macro.IOC_HwWellAlignedExtInput, 1
*/
#define IOC_HwWellAlignedExtInput(address)	((((ioc_address_t)(address)) & 3u) == 0u)

/* IOC_HwMemoryBarrier()
 *
 * Currently we assume that reordering could be observed on all multi-core machines.
 *
 * !LINKSTO IOC.PA.Macro.IOC_HwMemoryBarrier, 2
*/
#define IOC_HW_HAS_WEAK_MEM_ORDERING 1
#if (IOC_MAXCORES > 1)
#define IOC_HwMemoryBarrier()	IOC_MBAR()
#else /* IOC_MAXCORES */
#define IOC_HwMemoryBarrier()	do { /* nothing */ } while (0)
#endif /* IOC_MAXCORES */
#endif /* IOC_PA_CORE_H */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
