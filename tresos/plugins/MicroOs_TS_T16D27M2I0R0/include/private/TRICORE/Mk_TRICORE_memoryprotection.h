/* Mk_TRICORE_memoryprotection.h - TRICORE memory protection
 *
 * This file provides the interface between the hardware-independent microkernel
 * and the processor- (and perhaps derivative-) specific memory protection for
 * Tricore architecture processors.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TRICORE_MEMORYPROTECTION_H
#define MK_TRICORE_MEMORYPROTECTION_H

#include <public/Mk_basic_types.h>
#include <private/Mk_types_forward.h>
#include <private/TRICORE/Mk_TRICORE_mpu.h>
#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

#ifndef MK_ASM

/* The MPU cache
 * --------------
 * This array contains for every partition - minus the global and kernel partitions - a
 * pre-constructed image of all dynamic MPU region registers of bank 1.
 * It is filled at startup by MK_HwSetStaticMemoryPartition().
*/
extern mk_mpubounds_t * const MK_MpuRegCaches[MK_MAXCORES];

/* Number of static partitions in configuration.
*/
extern const mk_objquantity_t MK_nStaticPartitions[MK_MAXCORES];

/* MK_nDynRegionsMax - stores the size of the largest dynamic partition per core
*/
extern const mk_objquantity_t MK_nDynRegionsMax[MK_MAXCORES];

/* MK_HwEnableMemoryProtection activates hardware memory protection.
*/
void MK_HwEnableMemoryProtection(void);

/* MK_HwSetStaticPartition() writes the specified partition to the static portion of the MPU.
*/
void MK_HwSetStaticMemoryPartition(mk_kernelcontrol_t *);

/* MK_HwSetDynamicPartition() writes the specified partition to the dynamic portion of the MPU.
*/
void MK_HwSetDynamicMemoryPartition(mk_kernelcontrol_t *, mk_objectid_t);

/* TRICORE has no architecture specific memory region or region map members.
*/
#define MK_HAS_CPUFAMILYMEMORYREGION_T		0
#define MK_HAS_CPUFAMILYMEMORYREGIONMAP_T	0

#endif /* MK_ASM */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
