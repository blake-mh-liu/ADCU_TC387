/* Mk_TRICORE_hwclearcorevars.c
 *
 * This file contains the function MK_HwClearCoreVars() for TRICORE derivatives.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_core.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_memoryprotection.h>

/* MK_HwClearCoreVars - Sanitizes the TriCore kernel control variables during shutdown.
 *
 * This function assumes that the coreIndex field of the given mk_kernelcontrol_t instance is valid.
 *
 * !LINKSTO Microkernel.TRICORE.FunctionSpec.MK_HwClearCoreVars, 1
 * !doctype src
*/
void MK_HwClearCoreVars(mk_kernelcontrol_t *coreVars)
{
	const mk_objectid_t coreId = coreVars->coreIndex;

	coreVars->hwControl.mpuRegCache = MK_MpuRegCaches[coreId];
	coreVars->hwControl.nStaticPartitions = MK_nStaticPartitions[coreId];
	coreVars->hwControl.lastDynamicPartition = -1; /* Causes the dynamic MPU registers to be rewritten. */
	coreVars->hwControl.memPartitionPermissions = MK_MemoryPartitionPermissions[coreId];
}
