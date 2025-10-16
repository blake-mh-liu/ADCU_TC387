/* Mk_TRICORE_hwinitprocessor.c
 *
 * This file contains the TRICORE processor initialization function MK_HwInitProcessor()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_startup.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_startup.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <private/Mk_panic.h>
#include <private/Mk_memoryprotection.h>

static void MK_CheckMpuRegionAlignment(void);

/* MK_CheckMpuRegionAlignment()
 *
 * Checks whether all region boundaries are aligned to eight byte boundaries.
 *
 * Note: Each core could only check the regions it uses, however, we would need to search
 *   them beginning from the partition table (and might check regions multiple times).
 *   So iterating over all the regions is simpler and maybe also faster.
*/
static void MK_CheckMpuRegionAlignment(void)
{
	mk_objquantity_t i;

	for (i = 0; i < MK_nMemoryRegions; i++)
	{
		mk_address_t start, limit;

		start = (mk_address_t) MK_memoryRegions[i].mr_startaddr;
		limit = (mk_address_t) MK_memoryRegions[i].mr_limitaddr;
		if (((start & 7u) != 0u) || ((limit & 7u) != 0u))
		{
			MK_StartupPanic(MK_panic_MisalignedSymbol);
		}
	}
}


/* MK_HwInitProcessor()
 *
 * This function is called from MK_StartKernel() before the first thread is started.
 * It performs processor specific initialization.
 *
 * For Tricore processors, no initialization is necessary. However, the startup checks are performed here.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwInitProcessor, 4
 * !doctype src
*/
void MK_HwInitProcessor(void)
{
	MK_CheckMpuRegionAlignment();
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
