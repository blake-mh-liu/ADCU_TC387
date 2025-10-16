/* Mk_configuration_memoryprotection.c
 *
 * This file contains the configuration for memory protection.
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
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 *  A project shall not contain unreachable code.
 *
 * Reason:
 *  Configuration dependent.
 *
 *
 * MISRAC2012-3) Deviated Rule: 10.8 (required)
 *  The value of a composite expression shall not be cast to a different essential
 *  type category or a wider essential type.
 *
 * Reason:
 *  Depending on the used MPU, the macro like function MK_FirstAddressAboveRegion
 *  performs casts between mk_machineword_t* and mk_address_t.
 *  Per design, mk_address_t has the same size as a pointer, so this is not an issue.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_memoryprotection.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* Memory regions and region-to-partition mappings.
 *
 * The region table might exist even if the partition table doesn't exist, because
 * of the need to initialize the data/bss sections.
 *
 * For the region table table, if the base pointer MK_memoryRegions is NULL the size
 * MK_nMemoryRegions is zero. This fact is used in the code.
*/
const mk_objquantity_t MK_nMemoryRegions = MK_CFG_NMEMORYREGIONS;

#if MK_CFG_NMEMORYREGIONS > 0

/* Deviation MISRAC2012-3 <+1> */
static const mk_memoryregion_t MK_memRegion[MK_CFG_NMEMORYREGIONS] = { MK_CFG_MEMORYREGIONCONFIG };

const mk_memoryregion_t * const MK_memoryRegions = MK_memRegion;

#else

const mk_memoryregion_t * const MK_memoryRegions = MK_NULL;

#endif

/* Memory partitions
 *
 * If the base pointer MK_memoryPartitions is NULL the size MK_nMemoryPartitions is zero.
 * This fact is used in the code.
 * This file assumes that the region map table is not empty if the partition table is not empty.
*/
const mk_objquantity_t MK_nMemoryPartitions = MK_CFG_NMEMORYPARTITIONS;

#if MK_CFG_NMEMORYPARTITIONS > 0

static const mk_memoryregionmap_t MK_memRegionMap[MK_CFG_NMEMORYREGIONMAPS] = { MK_CFG_MEMORYREGIONMAPCONFIG };
/* Deviation MISRAC2012-2 <+1> */
static const mk_memorypartition_t MK_memPart[MK_CFG_NMEMORYPARTITIONS] = { MK_CFG_MEMORYPARTITIONCONFIG };

const mk_memorypartition_t * const MK_memoryPartitions = MK_memPart;

#if MK_CFG_NMEMORYREGIONS <= 0
#error "Memory partitions are configured but no memory regions. Check your configuration!"
#endif

#else

const mk_memorypartition_t * const MK_memoryPartitions = MK_NULL;

#endif

/* Core-local memory partition ranges.
 *
 * These ranges are used to select memory partitions for the respective core.
*/
const mk_memorypartitionrange_t MK_memoryPartitionRanges[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 */
	MK_COREARRAY(
		MK_MEMORYPARTITIONRANGE(MK_CFG_C0_FIRST_MEMORYPARTITION, MK_CFG_C0_NMEMORYPARTITIONS),
		MK_MEMORYPARTITIONRANGE(MK_CFG_C1_FIRST_MEMORYPARTITION, MK_CFG_C1_NMEMORYPARTITIONS),
		MK_MEMORYPARTITIONRANGE(MK_CFG_C2_FIRST_MEMORYPARTITION, MK_CFG_C2_NMEMORYPARTITIONS),
		MK_MEMORYPARTITIONRANGE(MK_CFG_C3_FIRST_MEMORYPARTITION, MK_CFG_C3_NMEMORYPARTITIONS),
		MK_MEMORYPARTITIONRANGE(MK_CFG_C4_FIRST_MEMORYPARTITION, MK_CFG_C4_NMEMORYPARTITIONS),
		MK_MEMORYPARTITIONRANGE(MK_CFG_C5_FIRST_MEMORYPARTITION, MK_CFG_C5_NMEMORYPARTITIONS),
		MK_MEMORYPARTITIONRANGE(MK_CFG_C6_FIRST_MEMORYPARTITION, MK_CFG_C6_NMEMORYPARTITIONS),
		MK_MEMORYPARTITIONRANGE(MK_CFG_C7_FIRST_MEMORYPARTITION, MK_CFG_C7_NMEMORYPARTITIONS)
	)
};

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
