/* Mk_TRICORE_hwsetstaticmemorypartition_tc161.c
 *
 * This file contains the function MK_HwSetStaticMemoryPartition() for Tricore.
 * The function programs the static memory partitions into the hardware.
 * This file is only used for Tricore Processors with a TC1.6E/P core architecture.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_basic_types.h>
#include <public/Mk_misra.h>
#include <private/Mk_memoryprotection.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>
#include <private/TRICORE/Mk_TRICORE_mpu.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <private/TRICORE/Mk_TRICORE_core.h>


/* Declaration of static functions.
*/

static mk_int_t MK_AddPartToDpr(const mk_memorypartition_t *, mk_int_t, mk_int_t);
static mk_int_t MK_AddPartToCpr(const mk_memorypartition_t *, mk_int_t, mk_int_t);

static void MK_AddMpuRwxPerms(mk_int_t, mk_int_t);
static void MK_XorMpuRwxPerms(mk_int_t, mk_int_t);

static void MK_FillMpuCache(mk_int_t);
static mk_uint32_t MK_GetStaticRegionMask(mk_objquantity_t, const mk_memoryregion_t *);
static void MK_ClearMpuPrsRegisters(void);

static mk_uint32_t MK_CheckMpuRegisterIndex(mk_int_t, mk_uint32_t);
static void MK_CheckMpuRegisterWriteResult(mk_uint32_t);

/* MPU register access functions are safety wrappers for those declared in Mk_TRICORE_mpu.h.
*/
static void MK_SetCpr(mk_int_t, mk_address_t, mk_address_t);
static void MK_SetCpxe(mk_int_t, mk_uint32_t);
static void MK_SetDpr(mk_int_t, mk_address_t, mk_address_t);
static void MK_SetDprwe(mk_int_t, mk_uint32_t, mk_uint32_t);
static mk_uint32_t MK_GetCpxe(mk_int_t);
static mk_mpurange_t MK_GetDpr(mk_int_t);
static mk_mpurwpermission_t MK_GetDprwe(mk_int_t);


/* Definition of static functions.
*/

/* MK_CheckMpuRegisterIndex - Panics, if a given register index is not in range. Returns the register index.
*/
static mk_uint32_t MK_CheckMpuRegisterIndex(mk_int_t sindex, mk_uint32_t limit)
{
	mk_uint32_t uindex = (mk_uint32_t) sindex;

	if (uindex >= limit)
	{
		MK_StartupPanic(MK_panic_InvalidMpuConfiguration);
	}

	return uindex;
}

/* MK_CheckMpuRegisterWriteResult - Panics, if the given value is non-zero.
*/
static void MK_CheckMpuRegisterWriteResult(mk_uint32_t mpuRegisterWriteFailure)
{
	if (mpuRegisterWriteFailure != 0u)
	{
		MK_StartupPanic(MK_panic_UnexpectedHardwareResponse);
	}
}


/* These MPU register access functions are safety wrappers for those declared in Mk_TRICORE_mpu.h.
 * They check whether the given register indices are in the valid range.
 * They check whether write accesses to the registers succeeded.
 * If one of these checks fails, they panic.
*/

static void MK_SetCpr(mk_int_t aIndex, mk_address_t lower, mk_address_t upper)
{
	mk_uint32_t writeFailure;
	mk_uint32_t index = MK_CheckMpuRegisterIndex(aIndex, MK_TRICORE_NCPR);

	writeFailure = MK_DoSetCpr(index, lower, upper);
	MK_CheckMpuRegisterWriteResult(writeFailure);
}

static void MK_SetCpxe(mk_int_t aPrsIndex, mk_uint32_t xe)
{
	mk_uint32_t writeFailure;
	mk_uint32_t prsIndex = MK_CheckMpuRegisterIndex(aPrsIndex, MK_TRICORE_NPRS);

	writeFailure = MK_DoSetCpxe(prsIndex, xe);
	MK_CheckMpuRegisterWriteResult(writeFailure);
}

static void MK_SetDpr(mk_int_t aIndex, mk_address_t lower, mk_address_t upper)
{
	mk_uint32_t writeFailure;
	mk_uint32_t index = MK_CheckMpuRegisterIndex(aIndex, MK_TRICORE_NDPR);

	writeFailure = MK_DoSetDpr(index, lower, upper);
	MK_CheckMpuRegisterWriteResult(writeFailure);
}

static void MK_SetDprwe(mk_int_t aPrsIndex, mk_uint32_t re, mk_uint32_t we)
{
	mk_uint32_t writeFailure;
	mk_uint32_t prsIndex = MK_CheckMpuRegisterIndex(aPrsIndex, MK_TRICORE_NPRS);

	writeFailure = MK_DoSetDprwe(prsIndex, re, we);
	MK_CheckMpuRegisterWriteResult(writeFailure);
}

static mk_uint32_t MK_GetCpxe(mk_int_t prsIndex)
{
	return MK_DoGetCpxe(MK_CheckMpuRegisterIndex(prsIndex, MK_TRICORE_NPRS));
}

static mk_mpurange_t MK_GetDpr(mk_int_t index)
{
	return MK_DoGetDpr(MK_CheckMpuRegisterIndex(index, MK_TRICORE_NDPR));
}

static mk_mpurwpermission_t MK_GetDprwe(mk_int_t prsIndex)
{
	return MK_DoGetDprwe(MK_CheckMpuRegisterIndex(prsIndex, MK_TRICORE_NPRS));
}

/* MK_GetStaticRegionMask
 *
 * This function checks if region boundaries which equals the given region's boundaries are already part of the
 * previously programmed DPRs, and reuses the entry if this is the case. This optimizes region usage for regions that
 * are part of a static partition and occur in several partitions.
*/
static mk_uint32_t MK_GetStaticRegionMask(mk_objquantity_t nAlreadyProgrammedDprs, const mk_memoryregion_t *region)
{
	mk_objquantity_t i;
	mk_uint32_t mask = 0u;

	for (i = 0; i < nAlreadyProgrammedDprs; i++)
	{
		mk_mpurange_t dpr;
		mk_uint32_t start, limit;

		dpr = MK_GetDpr(i);
		start = (mk_uint32_t) region->mr_startaddr;
		limit = (mk_uint32_t) region->mr_limitaddr;
		if ((dpr.lower == start) && (dpr.upper == limit))
		{
			mask = MK_ShiftLeftU32(1u, (mk_uint32_t)i);
			break;
		}
	}

	return mask;
}



/* MK_FillMpuCache() - Fills the MPU cache
 *
 * This function caches all dynamic MPU region registers for each thread memory partition (i.e., all but the
 * global and kernel partitions)
 *
 * After filling the cache the TRICORE specific core control variables are set.
 * The calling core's mpuRegCache points to the core-local MPU region cache.
 * Its lastDynamicPartition is set to -1 (which is no valid partition Id).
 * nStaticPartitions is set to the number of static partitions.
 *
 * This function is empty when the configuration excludes dynamic MPU switching.
*/
static void MK_FillMpuCache(mk_int_t nStaticRegions)
{
	const mk_objectid_t coreId = MK_HwGetCoreIndex();
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t * const coreVars = MK_GetCoreVars();
	const mk_int_t nStaticParts = coreVars->hwControl.nStaticPartitions;
	const mk_int_t mprSize = MK_memoryPartitionRanges[coreId].mpr_size;
	mk_mpubounds_t * const mpuRegCache = MK_MpuRegCaches[coreId];
	mk_mpurwpermission_t *coreMemoryPartitionPermissions = MK_MemoryPartitionPermissions[coreId];
	mk_objectid_t p;
	mk_objectid_t cacheIndex = 0;

	/* Check that MK_nDynRegionsMax is in range.
	*/
	if ((nStaticRegions + MK_nDynRegionsMax[coreId]) > MK_TRICORE_NDPR)
	{
		MK_StartupPanic(MK_panic_MemoryPartitionIsTooLarge);
	}

	/* Fill cache
	*/
	for ( p = nStaticParts; p < mprSize; ++p )
	{
		const mk_memorypartition_t * const mempart = &(MK_GetMemoryPartitionsOfCore(coreId)[p]);
		mk_mpubounds_t * const partCache = &mpuRegCache[cacheIndex];
		mk_objectid_t dr = 0;
		mk_objectid_t sr;
		/* The dynamic regions are filled into the MPU top-down, i.e. starting
		 * with the last region is filled first.
		*/
		mk_uint32_t pMask = MK_ShiftLeftU32(1u, (MK_U(MK_TRICORE_NDPR) - 1u));

		for ( sr=0; sr < mempart->nRegions; sr++ )
		{
			const mk_memoryregion_t * const region = mempart->regionMap[sr].region;
			mk_uint32_t dpsMask = MK_GetStaticRegionMask(nStaticRegions, region);
			mk_uint32_t perms;

			/* dpsMask != 0 means that the region is part of a static partition
			 * and needs not be programmed dynamically.
			*/
			if ( dpsMask == 0u )
			{
				/* Check that there are enough MPU region registers to hold the region.
				*/
				if ((dr >= MK_nDynRegionsMax[coreId]) || ((nStaticRegions + dr) >= MK_TRICORE_NDPR))
				{
					MK_StartupPanic(MK_panic_MemoryPartitionIsTooLarge);
				}

				dpsMask = pMask;
				partCache[dr].lower = (mk_uint32_t)region->mr_startaddr;
				partCache[dr].upper = (mk_uint32_t)region->mr_limitaddr;

				dr++;
				pMask >>= 1u;
			}

			perms = mempart->regionMap[sr].mrm_permissions;

			if ( (perms & MK_TRICORE_PERM_READ) != 0u )
			{
				coreMemoryPartitionPermissions[p].dpre |= dpsMask;
			}
			if ( (perms & MK_TRICORE_PERM_WRITE) != 0u )
			{
				coreMemoryPartitionPermissions[p].dpwe |= dpsMask;
			}

			/* Also add permissions of the global partition.
			*/
			coreMemoryPartitionPermissions[p].dpre |= coreMemoryPartitionPermissions[0].dpre;
			coreMemoryPartitionPermissions[p].dpwe |= coreMemoryPartitionPermissions[0].dpwe;
		}

		cacheIndex += MK_nDynRegionsMax[coreId];
	}

	coreVars->hwControl.mpuRegCache = mpuRegCache;
	coreVars->hwControl.lastDynamicPartition = -1;
}


static mk_int_t MK_AddPartToDpr(
	const mk_memorypartition_t *partition,
	mk_int_t prsIndex,
	mk_int_t startIdx
)
{
	mk_int_t i;
	mk_int_t nextIdx = startIdx;

	for ( i = 0;  i < partition->nRegions; i++ )
	{
		const mk_memoryregion_t * const region = partition->regionMap[i].region;
		mk_uint32_t perms = partition->regionMap[i].mrm_permissions;

		/* Check if region is a data region.
		*/
		if ( ((perms & MK_TRICORE_PERM_RWMASK) != 0u ) )
		{
			mk_uint32_t dpsMask = MK_GetStaticRegionMask(nextIdx, region);
			mk_mpurwpermission_t dp;

			if ( dpsMask == 0u )
			{
				mk_address_t start, limit;

				if ( nextIdx >= MK_TRICORE_NDPR )
				{
					MK_StartupPanic(MK_panic_MemoryPartitionIsTooLarge);
				}

				/* Use next region.
				*/
				start = (mk_address_t) region->mr_startaddr;
				limit = (mk_address_t) region->mr_limitaddr;
				MK_SetDpr(nextIdx, start, limit);
				dpsMask = MK_ShiftLeftU32(1u, (mk_uint32_t)nextIdx);

				nextIdx++;
			}

			dp = MK_GetDprwe(prsIndex);
			if ( (perms & MK_TRICORE_PERM_READ) != 0u )
			{
				dp.dpre |= dpsMask;
			}
			if ( (perms & MK_TRICORE_PERM_WRITE) != 0u )
			{
				dp.dpwe |= dpsMask;
			}
			MK_SetDprwe(prsIndex, dp.dpre, dp.dpwe);
		}
	}

	return nextIdx;
}

static mk_int_t MK_AddPartToCpr
(
	const mk_memorypartition_t *partition,
	mk_int_t prsIndex,
	mk_int_t startIdx
)
{
	mk_int_t i;
	mk_int_t nextIdx = startIdx;

	for ( i = 0;  i < partition->nRegions; i++ )
	{
		const mk_memoryregion_t * const region = partition->regionMap[i].region;
		mk_uint32_t perms = partition->regionMap[i].mrm_permissions;

		/* Check if region is a code region.
		*/
		if ( (perms & MK_TRICORE_PERM_EXECUTE) != 0u )
		{
			mk_address_t start, limit;
			mk_uint32_t cpxeVal;

			if ( nextIdx >= MK_TRICORE_NCPR )
			{
				MK_StartupPanic(MK_panic_MemoryPartitionIsTooLarge);
			}

			start = (mk_address_t) region->mr_startaddr;
			limit = (mk_address_t) region->mr_limitaddr;
			MK_SetCpr(nextIdx, start, limit);
			cpxeVal = MK_GetCpxe(prsIndex) | MK_ShiftLeftU32(1u, (mk_uint32_t)nextIdx);
			MK_SetCpxe(prsIndex, cpxeVal);

			nextIdx++;
		}
	}

	return nextIdx;
}

/* MK_AddMpuRwxPerms(perms,dest,src) adds the RWX MPU permissions of 'src' to 'dest'.
*/
static void MK_AddMpuRwxPerms(mk_int_t destPrsIndex, mk_int_t srcPrsIndex)
{
	mk_uint32_t srcCpxe, destCpxe;
	mk_mpurwpermission_t srcDp, destDp;

	srcDp = MK_GetDprwe(srcPrsIndex);
	srcCpxe = MK_GetCpxe(srcPrsIndex);

	destDp = MK_GetDprwe(destPrsIndex);
	destCpxe = MK_GetCpxe(destPrsIndex);

	MK_SetDprwe(destPrsIndex, (srcDp.dpre | destDp.dpre), (srcDp.dpwe | destDp.dpwe));
	MK_SetCpxe(destPrsIndex, (srcCpxe | destCpxe));
}

/* MK_XorMpuRwxPerms(perms,dest,src) xors the RWX MPU permissions of 'src' to 'dest'.
*/
static void MK_XorMpuRwxPerms(mk_int_t destPrsIndex, mk_int_t srcPrsIndex)
{
	mk_uint32_t srcCpxe, destCpxe;
	mk_mpurwpermission_t srcDp, destDp;

	srcDp = MK_GetDprwe(srcPrsIndex);
	srcCpxe = MK_GetCpxe(srcPrsIndex);

	destDp = MK_GetDprwe(destPrsIndex);
	destCpxe = MK_GetCpxe(destPrsIndex);

	MK_SetDprwe(destPrsIndex, (srcDp.dpre ^ destDp.dpre), (srcDp.dpwe ^ destDp.dpwe));
	MK_SetCpxe(destPrsIndex, (srcCpxe ^ destCpxe));
}

/* MK_ClearMpuPrsRegisters
 *
 * Sets all DPRE, DPWE and CPXE registers to zero.
*/
static void MK_ClearMpuPrsRegisters(void)
{
	mk_int_t i;

	for (i = 0; i < MK_TRICORE_NPRS; i++)
	{
		MK_SetCpxe(i, 0u);
		MK_SetDprwe(i, 0u, 0u);
	}
}

/* MK_HwSetStaticMemoryPartition() - programs the static memory partitions into the hardware.
 *
 * !LINKSTO Microkernel.TRICORE.MPU.GlobalPartition, 3,
 * !        Microkernel.TRICORE.MPU.KernelPartition, 2,
 * !        Microkernel.TRICORE.MPU.GlobalCodeProtection, 1,
 * !        Microkernel.TRICORE.Function.MK_HwSetStaticMemoryPartition, 6,
 * !        Microkernel.TRICORE.MPU.ProtectionRegisterSets, 4
 * !doctype src
*/
void MK_HwSetStaticMemoryPartition(mk_kernelcontrol_t *coreVars)
{
	const mk_objectid_t coreId = coreVars->coreIndex;
	const mk_memorypartition_t *coreMemoryPartitions;
	mk_mpurwpermission_t *coreMemoryPartitionPermissions;
	mk_int_t nStaticRegions = 0;
	mk_int_t nextCprIdx = 0;
	mk_int_t i;
	const mk_memorypartition_t *partition;

	/* Clear the current core's MPU PRS registers.
	*/
	MK_ClearMpuPrsRegisters();

	/* Get the current core's memory partition table.
	*/
	coreMemoryPartitions = MK_GetMemoryPartitionsOfCore(coreId);
	coreMemoryPartitionPermissions = MK_MemoryPartitionPermissions[coreId];
	coreVars->hwControl.memPartitionPermissions = coreMemoryPartitionPermissions;

	/* Initialize this core's nStaticPartitions variable.
	 * Even if it is not needed in future calculations, its value should be correct.
	*/
	coreVars->hwControl.nStaticPartitions = MK_nStaticPartitions[coreId];

	/* Parse global Partition and add respective regions to CPR/DPR.
	*/
	for ( i = 0; i < MK_nStaticPartitions[coreId]; i++ )
	{
		mk_mpurwpermission_t dp;

		partition = &coreMemoryPartitions[i];
		nStaticRegions = MK_AddPartToDpr(partition, i, nStaticRegions);
		nextCprIdx = MK_AddPartToCpr(partition, i, nextCprIdx);

		/* Add global partition to fast partition.
		*/
		if ( i > MK_MEMPART_KERNEL )
		{
			MK_AddMpuRwxPerms(i, 0);
		}

		dp = MK_GetDprwe(i);
		coreMemoryPartitionPermissions[i].dpre = dp.dpre;
		coreMemoryPartitionPermissions[i].dpwe = dp.dpwe;
	}

	/* PRS[0] needs to contain both global (currently PRS[0]) and kernel (currently PRS[1]) regions.
	*/
	MK_AddMpuRwxPerms(0, 1);

	/* PRS[1] now contains the kernel's regions, but PRS[1] should only contain the global permissions, so the
	 * global permissions need to be set and the kernel permissions need to be cleared. This is conveniently achieved
	 * using XOR with PRS[0] which already contains permissions for both partitions.
	*/
	MK_XorMpuRwxPerms(1, 0);

	/* Prepare MPU cache.
	*/
	MK_FillMpuCache(nStaticRegions);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
