/* Mk_k_initdatasections.c
 *
 * This file contains the MK_InitDataSections function from the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 18.3 (required)
 *  The relational operators >, >=, < and <= shall not be applied to objects of
 *  pointer type, except where they point into the same object.
 *
 * Reason:
 *  This loop initializes an entire memory region between two addresses specified
 *  in the linker script. There is no single object.
 *
 *
 * MISRAC2012-2) Deviated Rule: 1.3 (required)
 *  There shall be no occurrence of undefined or critical unspecified behaviour.
 *
 * Reason:
 *  The behaviour in question is the pointer comparision, which is already deviatied
 *  with rule 18.3:
 *  This loop initializes an entire memory region between two addresses specified
 *  in the linker script. There is no single object.
*/

#include <public/Mk_public_types.h>
#include <private/Mk_memoryprotection.h>
#include <private/Mk_startup.h>
#include <private/Mk_anondata.h>

/* MK_InitDataSections() - initialize all .data and .bss sections at startup
 *
 * This function initializes all memory regions by calling MK_InitMemoryRegion() for each
 * region that is configured.
 * In a fully memory-protected system all variables should be allocated to a memory region
 * somewhere. However, support is provided for "anonymous" .data and .bss sections.
 *
 * Note: this function is a *restricted C function*, i.e. it must not rely on the content
 * of global variables.
 *
 * !LINKSTO Microkernel.Function.MK_InitDataSections, 1
 * !doctype src
*/
void MK_InitDataSections(void)
{
	mk_objectid_t i;
	mk_uint32_t j;
	register mk_int8_t const *src;	/* Source of data to copy */
	register mk_int8_t *dst;		/* Destination of data to initialize */

	mk_objectid_t coreId = MK_HwGetCoreIndex();

	/* Initialize all configured memory regions
	 *
	 * Note: MK_memoryRegions could be NULL here, but if it is, MK_nMemoryRegions is 0,
	 * so the loop body is not executed and the null pointer is not dereferenced.
	*/
	for ( i = 0; i < MK_nMemoryRegions; i++ )
	{
		if ( (MK_memoryRegions[i].mr_initcore == coreId) || (MK_memoryRegions[i].mr_initcore == -1) )
		{
			MK_InitMemoryRegion(&MK_memoryRegions[i]);
		}
	}

	/* Core id value needs to be restored into respective core variables after all bss sections are zeroed out */
#if MK_COREID_VALUE_RESTORE_REQUIRED
	(MK_coreTable[coreId])->coreIndex = coreId;
#endif

	if ( coreId == MK_hwMasterCoreIndex )
	{
		/* Initialize the "anonymous" .data section by copying its content from ROM into RAM.
		*/
		j = 0;
		dst = &MK_MR_ANON_DATA_START;
		src = MK_anonIDat;

		if ( src != MK_NULL )
		{
			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			while ( &(dst[j]) < &MK_MR_ANON_DATA_END )
			{
				dst[j] = src[j];
				j++;
			}
		}

		/* Clear the anonymous .bss section. ".bss" section contains "uninitialized" C variables, which
		 * must have an initial value of zero according to the C standard.
		 */
		j = 0;
		dst = &MK_MR_ANON_BSS_START;
		/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
		while ( &(dst[j]) < &MK_MR_ANON_BSS_END )
		{
			dst[j] = 0;
			j++;
		}

		j = 0;
		dst = &MK_MR_CAL_CORE0_START;
		src = MK_cal_Core0_IDat;
		if ( src != MK_NULL )
		{
			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			while ( &(dst[j]) < &MK_MR_CAL_CORE0_DATA_END )
			{
				dst[j] = src[j];
				j++;
			}
		}

		j = 0;
		dst = &MK_MR_PSPR_CORE0_START;
		src = MK_pspr_Core0_IDat;
		if ( src != MK_NULL )
		{
			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			while ( &(dst[j]) < &MK_MR_PSPR_CORE0_END )
			{
				dst[j] = src[j];
				j++;
			}
		}
	}
	else if ( coreId == 1 )
	{
		j = 0;
		dst = &MK_MR_CAL_CORE1_START;
		src = MK_cal_Core1_IDat;
		if ( src != MK_NULL )
		{
			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			while ( &(dst[j]) < &MK_MR_CAL_CORE1_DATA_END )
			{
				dst[j] = src[j];
				j++;
			}
		}
		
		j = 0;
		dst = &MK_MR_CDD_DATA_CORE1_START;
		src = MK_cddDataCore1IDat;
		if ( src != MK_NULL )
		{
			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			while ( &(dst[j]) < &MK_MR_CDD_DATA_CORE1_END )
			{
				dst[j] = src[j];
				j++;
			}
		}

		j = 0;
		dst = &MK_MR_PSPR_CORE1_START;
		src = MK_pspr_Core1_IDat;
		if ( src != MK_NULL )
		{
			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			while ( &(dst[j]) < &MK_MR_PSPR_CORE1_END )
			{
				dst[j] = src[j];
				j++;
			}
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
