/* Mk_TRICORE_hwsetdynamicmemorypartition_tc161.c
 *
 * This file contains the function MK_HwSetDynamicMemoryPartition() for Tricore processors with
 * TC1.6E/P core architectures.
 * The function programs a dynamic memory partition into the hardware.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  This function may call itself indirectly via MK_Panic().
 *  MK_Panic() is an error handling facility that will recurse at most once.
 *  When MK_Panic() detects recursion, it immediately calls MK_PanicStop()
 *  which doesn't return and doesn't recurse.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_STMT]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *  In function MK_HwSetDynamicMemoryPartition: Value 0.0 of metric "stmt" is out of bounds (1..50).
 *
 * Reason:
 *  This function is only empty if there are no dynamic partitions.
 *  Otherwise there are statements in MK_HwSetDynamicMemoryPartition.
 *
 * DCG-2) Deviated Rule: [OS_C_NAMING_070]
 *  Unused parameters shall have their identifiers prefixed with unused_.
 *
 * Reason:
 *  If no dynamic memory regions are configured MK_HwSetDynamicMemoryPartition() is an empty
 *  function and hence the parameters are not used. In other cases the parameters are used.
 *  The macros MK_PARAM_UNUSED() are used in a corresponding preprocessor #else-#endif block.
 *  The CGC cannot identify this.
*/

#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <private/Mk_memoryprotection.h>
#include <private/TRICORE/Mk_TRICORE_mpu.h>
#include <Mk_Cfg.h>
#include <private/TRICORE/Mk_TRICORE_Cfg.h>
#include <private/Mk_tool.h>

#if (MK_MPU_REGISTER_CHECK == 1)
#if (MK_CFG_DYNREGIONS_MAX > 0)
static void MK_CheckDynamicMpuRegisters
(
	const mk_kernelcontrol_t *,
	const mk_mpubounds_t *,
	const mk_mpurwpermission_t *
);

/* MK_CheckDynamicMpuRegisters() - read back and compare the MPU registers of the dynamic partition.
 *
 * If the read back values differ from the supplied values (that were written before), we have an invalid
 * MPU configuration and panic.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_CheckDynamicMpuRegisters, 2
 * !doctype src
*/
/* Deviation MISRAC2012-1 */
static void MK_CheckDynamicMpuRegisters
(
	const mk_kernelcontrol_t *coreVars,
	const mk_mpubounds_t *bounds,
	const mk_mpurwpermission_t *perms
)
{
	const mk_objectid_t coreId = coreVars->coreIndex;

	/* Read back and check the mpu registers.
	*/
	if (MK_checkDynMpuRegs[coreId](bounds, perms) != 0u)
	{
		/* Deviation MISRAC2012-1 <+1> */
		MK_Panic(MK_panic_UnexpectedHardwareResponse);
	}
}
#endif
#endif /* MK_MPU_REGISTER_CHECK */

/* MK_HwSetDynamicMemoryPartition() - programs the dynamic memory partition into the hardware.
 *
 * This version assumes that the dynamic partitions only contain data regions. The code protection
 * registers are not modified. Any execute-access permissions in the regions will be ignored.
 *
 * This function selects the correct entry from the MPU cache. The actual programming will take
 * place in the assembler function that is called at the end. The assembler function will
 * re-programm all available dynamic regions.
 *
 * This function is empty when the configuration excludes dynamic MPU switching.
 *
 * !LINKSTO Microkernel.TRICORE.MPU.GlobalCodeProtection, 1,
 * !        Microkernel.TRICORE.Function.MK_HwSetDynamicMemoryPartition, 4
 * !doctype src
*/
/* Deviation DCG-1 <START> */
/* Deviation MISRAC2012-1 */
void MK_HwSetDynamicMemoryPartition(mk_kernelcontrol_t *coreVars, mk_objectid_t partId)
{
#if (MK_CFG_DYNREGIONS_MAX > 0)
	if ( partId != coreVars->hwControl.lastDynamicPartition )
	{
		const mk_mpurwpermission_t *permissions = MK_NULL;
		const mk_mpubounds_t *boundaryPairs = MK_NULL;
		const mk_mpubounds_t * const mpuRegCache = coreVars->hwControl.mpuRegCache;
		const mk_mpurwpermission_t * const corePermissions = coreVars->hwControl.memPartitionPermissions;
		const mk_objectid_t coreId = coreVars->coreIndex;

		if ( partId <= MK_MEMPART_KERNEL )
		{
			boundaryPairs = &(mpuRegCache[0]); /* doesn't matter */
			permissions = &corePermissions[0]; /* only global regions */
		}
		else if ( partId >= coreVars->hwControl.nStaticPartitions )
		{
			mk_objectid_t partCacheIndex;
			partCacheIndex = (partId - coreVars->hwControl.nStaticPartitions) * MK_nDynRegionsMax[coreId];
			boundaryPairs = &mpuRegCache[partCacheIndex];
			permissions = &corePermissions[partId];
		}
		else
		{
			/* Static partition --> nothing to do.
			*/
		}

		if ( permissions != MK_NULL )
		{
			coreVars->hwControl.lastDynamicPartition = partId;
			MK_writeDynMpuRegs[coreId](boundaryPairs, permissions);

			/* Optional readback for non-lockstep cores
			*/
#if (MK_MPU_REGISTER_CHECK == 1)
			if (MK_checkDynMpuRegs[coreId] != MK_NULL)
			{
				MK_CheckDynamicMpuRegisters(coreVars, boundaryPairs, permissions);
			}
#endif
		}

	}
#else /* MK_CFG_DYNREGIONS_MAX */
	/* Deviation DCG-2 <+2> */
	MK_PARAM_UNUSED(coreVars);
	MK_PARAM_UNUSED(partId);
#endif /* MK_CFG_DYNREGIONS_MAX > 0 */
}
/* Deviation DCG-1 <STOP> */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
