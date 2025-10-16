/* Mk_reqm_nommu.h
 *
 * This file contains requirements management for derivatives which don't have an MMU.
 * MMU requirements cannot be fulfilled by derivatives which don't have one.
 * This file shall not be used for MMU derivatives.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_REQM_NOMMU_H
#define MK_REQM_NOMMU_H

/* On derivatives without MMU we don't have heaps, page-table and other MMU related code.
 *
 * !LINKSTO Microkernel.Function.MK_HeapAllocate, 1,
 * !        Microkernel.Function.MK_GenerateFlatPartitionMap, 2,
 * !        Microkernel.Function.MK_CheckRegionAlignment, 2
*/

#endif /* MK_REQM_NOMMU_H */
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
