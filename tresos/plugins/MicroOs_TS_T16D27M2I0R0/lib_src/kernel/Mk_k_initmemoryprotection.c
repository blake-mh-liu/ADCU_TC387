/* Mk_k_initmemoryprotection.c
 *
 * This file contains the function MK_InitMemoryProtection().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_memoryprotection.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>

/* MK_InitMemoryProtection() initializes the memory protection subsystem.
 *
 * On entry:
 *	- memory protection is disabled
 * On exit (provided memory protection is configured):
 *	- global region descriptors are programmed into MPU
 *	- memory protection is enabled
 *
 * !LINKSTO Microkernel.Function.MK_InitMemoryProtection, 1
 * !doctype src
*/
void MK_InitMemoryProtection(mk_kernelcontrol_t *coreVars)
{
	coreVars->currentMemoryPartition = -1;
	if ( MK_nMemoryPartitions > 0 )
	{
		MK_HwInitMemoryProtection(coreVars);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
