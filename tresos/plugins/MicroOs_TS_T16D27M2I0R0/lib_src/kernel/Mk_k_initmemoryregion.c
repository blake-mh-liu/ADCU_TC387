/* Mk_k_initmemoryregion.c
 *
 * This file contains the MK_InitMemoryRegion() function from the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.8 (required)
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

/* MK_InitMemoryRegion() initializes a memory region.
 *
 * This function initializes a memory region. It is called typically in a loop for
 * each configured memory region.
 *
 * A memory region descriptor contains four addresses: a start address, a limit address, a bss start address
 * and an image address.
 *
 * A memory region is bounded below by its start address and above by its limit address.
 *
 * Each region consists of a ".data" portion and a ".bss" portion (either of which could have
 * zero length). The ".data" portion is bounded below by the region start address and above by the bss start address.
 * The ".bss" portion is bounded below by the bss start address and above by the limit address.
 * The ".data" portion contains C variables that have been given explicit initial values. The initial values
 * are obtained from a ROM image created by the linker whose address is given by the image address. The ".bss"
 * portion contains C variable that have not been given explicit initial values and must therefore be initialized
 * to zero. It is also possible to configure an initialization value other than 0 for this region, which can be used
 * to initialize stacks with a magic pattern.
 *
 * It is possible to configure a memory region that does not get initialized by setting both the image address
 * and the bss start address to NULL. Such a region can be used for ROM regions, I/O regions, stack regions,
 * non-volatile memory and memory whose values must be preserved over a reset. It is also possible that the
 * same physical region has two entries in the region table; only one of the entries needs the initialization
 * parameters.
 *
 * It is not possible to specify a region that has both initialized and uninitialized portions.
 *
 * MK_InitMemoryRegion is a restricted C function.
 *
 * Precondition: the parameter mr is a valid memory region. It is never NULL.
 *
 * !LINKSTO Microkernel.Function.MK_InitMemoryRegion, 1
 * !doctype src
*/
void MK_InitMemoryRegion(const mk_memoryregion_t *mr)
{
	const mk_machineword_t *src;	/* Source of data to copy */
	mk_machineword_t *dst;			/* Destination of data to initialize */
	mk_machineword_t *lim;			/* Limit of data to initialize */
	mk_size_t i;

	/* Is there a ROM image to copy over?
	*/
	if ( mr->mr_idata != MK_NULL )
	{
		/* Copy data from the ROM image into the data region.
		*/
		i = 0;
		src = mr->mr_idata;
		dst = mr->mr_startaddr;

		/* Copy up to the start of the ".bss" portion, or the end of the region if there's no ".bss"
		*/
		if ( mr->mr_bstartaddr == MK_NULL )
		{
			/* Deviation MISRAC2012-1 <+1> */
			lim = MK_FirstAddressAboveRegion(mr);
		}
		else
		{
			lim = mr->mr_bstartaddr;
		}

		while ( &(dst[i]) < lim )
		{
			dst[i] = src[i];
			i++;
		}
	}

	/* Is there an implicitly-initialized portion (typically bss)
	 * It is initialized with a configurable initialization value, typically 0 for bss
	*/
	if ( mr->mr_bstartaddr != MK_NULL )
	{
		i = 0;
		dst = mr->mr_bstartaddr;
		/* Deviation MISRAC2012-1 <+1> */
		lim = MK_FirstAddressAboveRegion(mr);

		/* Clear the bss portion.
		*/
		while ( &(dst[i]) < lim )
		{
			dst[i] = mr->mr_fillpattern;
			i++;
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
