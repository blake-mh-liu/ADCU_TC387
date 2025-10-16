/* Mk_TRICORE_hwinitmemoryprotection.c
 *
 * This file contains the function MK_HwInitMemoryProtection() for TRICORE processors
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_memoryprotection.h>
#include <private/TRICORE/Mk_TRICORE_memoryprotection.h>

/* MK_HwInitMemoryProtection() initializes the hardware's memory protection subsystem, including the MPU
 *
 * This function is called on all cores. There is no external synchronization.
 * This function does not return if the memory protection configuration is invalid. Instead it
 * calls MK_StartupPanic.
 *
 * On entry:
 *	- the MPU is in the state defined by the low-level startup code
 *	- the core variable currentMemoryPartition (on each core) is set to -1 and will not get
 *		re-initialized afterwards.
 *
 * On exit:
 *	- the memory protection configuration is valid.
 *	- hardware-specific variables controlling the memory protection are initialized.
 *  - the MPU is enabled with the normal runtime restrictions for the kernel in place.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwInitMemoryProtection, 1
 * !doctype src
*/
void MK_HwInitMemoryProtection(mk_kernelcontrol_t *coreVars)
{
	mk_objquantity_t nPartitions;
	mk_objquantity_t nStaticPartitions;

	/* Setup static memory partitions.
	*/
	MK_HwSetStaticMemoryPartition(coreVars);

	/* Get the core-local partition array.
	*/
	nPartitions = MK_memoryPartitionRanges[coreVars->coreIndex].mpr_size;
	nStaticPartitions = coreVars->hwControl.nStaticPartitions;

	/* There must not be more static partitions than there are partitions at all.
	*/
	if (nStaticPartitions > nPartitions)
	{
		MK_StartupPanic(MK_panic_MemoryPartitionIsTooLarge);
	}

	MK_HwEnableMemoryProtection();
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
