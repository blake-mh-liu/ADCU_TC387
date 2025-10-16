/* Mk_memoryprotection.h - memory protection configuration and handling
 *
 * This file contains definitions for the hardware-independent part of configuration
 * and handling of memory protection. It also includes the hardware-specific part.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.10 (advisory)
 *  The # and ## preprocessor operators should not be used.
 *
 * Reason:
 *  Automatic construction of symbols in a consistent manner.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_020]
 *  The conditional operator ?: shall not be used.
 *
 * Reason:
 *  The macro is intended to be used for initializing constants, so neither an if ... else construct
 *  nor a function call is possible.
*/
#ifndef MK_MEMORYPROTECTION_H
#define MK_MEMORYPROTECTION_H

#include <public/Mk_hwsel.h>

#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <public/Mk_error.h>
#include <private/Mk_types_forward.h>

#include MK_HWSEL_PRV_MEMORYPROTECTION

/* Fill patterns for memory regions.
*/
#define MK_BSSFILL		0x0u			/* bss ("uninitialized" global C variables) fill pattern */
#if MK_WORDLENGTH==32
#define MK_STACKFILL	0xEBEBEBEBu		/* stack fill pattern */
#elif MK_WORDLENGTH==64
#define MK_STACKFILL	0xEBEBEBEBEBEBEBEBuL	/* stack fill pattern */
#else
#error "MK_STACKFILL not adapted for this value of MK_WORDLENGTH"
#endif

#ifndef MK_ASM

#ifndef MK_MEMPERM_T
#error "MK_MEMPERM_T is not defined."
#endif
typedef MK_MEMPERM_T	mk_memperm_t;

/* A memory partition contains a number of regions defined by an array of region mappings
*/
struct mk_memorypartition_s
{
	const mk_memoryregionmap_t *regionMap;	/* Pointer to an array of nRegions region references. */
	mk_objquantity_t nRegions;				/* No. of regions in this partition */
};

/* A memory region mapping contains a pointer to a region, and permissions for that region.
 * For checking purposes it could also contain a partition id or reference, but this implementation doesn't.
*/
struct mk_memoryregionmap_s
{
	const mk_memoryregion_t *region;			/* The memory region descriptor for this mapping. */
	mk_memperm_t mrm_permissions;				/* Permissions for the above region */
#if MK_HAS_CPUFAMILYMEMORYREGIONMAP_T
	mk_cpufamily_memoryregionmap_t mrm_hwextra;	/* Hardware-specific memory region map configuration. */
#endif
};

/* A memory region is simply an address range. All addresses are such that startaddr <= a < limitaddr are in
 * the region. The region also has initialization information.
 *
 * Note: the "limit address" actually held in the region structure might be the last address of the region
 * or the first address outside the region, depending on how the memory protection hardware works.
 * This is done to avoid performing arithmetic on constants (+1 or -1) when writing to the MPU, which
 * is time-critical.
 * Preconditions:
 *	- the linker always provides the first address outside the region
 *	- the value in the structure is always the value that is programmed into the MPU
 *	- three macros are provided:
 *		-- MK_LastAddressOfRegion() adjusts a limit address downwards if necessary
 *		-- MK_FirstAddressAboveRegion() adjusts a limit address upwards if necessary
 *		-- MK_AdjustLinkerAddressForLimit() converts the linker address to the correct limit address
 *	- the architecture/derivative defines the macro MK_HWMPUUSESLASTADDRESSOFREGION to 0 or 1
*/
struct mk_memoryregion_s
{
	mk_machineword_t *mr_startaddr;		/* Start address of the region */
	mk_machineword_t *mr_bstartaddr;	/* Start address of zero-initialized ("bss") part of region */
	mk_machineword_t *mr_limitaddr;		/* Limit address of the region (see above!) */
	const mk_machineword_t *mr_idata;	/* Address of initialization data */
	mk_machineword_t mr_fillpattern;	/* Initialization value for the implicitly-initialized part of memory region */
	mk_objectid_t	mr_initcore;		/* The core on which this region is initialized, -1 means on every core */

#if MK_HAS_CPUFAMILYMEMORYREGION_T
	mk_cpufamily_memoryregion_t mr_hwextra;		/* Hardware-specific memory region configuration */
#endif

};

#endif /* MK_ASM */

#ifndef MK_HWMPUUSESLASTADDRESSOFREGION
#error "CPU family has not defined MK_HWMPUUSESLASTADDRESSOFREGION"
#endif

#if MK_HWMPUUSESLASTADDRESSOFREGION
#define MK_LastAddressOfRegion(x)			((x)->mr_limitaddr)
#define MK_FirstAddressAboveRegion(x)		((mk_machineword_t *)(((mk_address_t)((x)->mr_limitaddr))+1u))
#define MK_AdjustLinkerAddressForLimit(x)	((mk_machineword_t *)(((mk_address_t)(x))-1u))
#else
#define MK_LastAddressOfRegion(x)			((mk_machineword_t *)(((mk_address_t)((x)->mr_limitaddr))-1u))
#define MK_FirstAddressAboveRegion(x)		((x)->mr_limitaddr)
#define MK_AdjustLinkerAddressForLimit(x)	(x)
#endif

#ifndef MK_ASM
extern const mk_objquantity_t MK_nMemoryPartitions;
extern const mk_objquantity_t MK_nMemoryRegions;
extern const mk_memorypartition_t * const MK_memoryPartitions;
extern const mk_memoryregion_t * const MK_memoryRegions;

/* Core-local memory partition range.
 * Used to select a range of memory partitions for a certain core.
*/
struct mk_memorypartitionrange_s
{
	mk_objectid_t		mpr_begin;
	mk_objquantity_t	mpr_size;
};
typedef struct mk_memorypartitionrange_s mk_memorypartitionrange_t;

extern const mk_memorypartitionrange_t MK_memoryPartitionRanges[MK_MAXCORES];
#endif /* MK_ASM */

#define MK_GetMemoryPartitionsOfCore(coreId)	\
	(&MK_memoryPartitions[MK_memoryPartitionRanges[(coreId)].mpr_begin])

/* Define a memory partition - used by the configuration.
 *
 * Parameters:
 *	- r = index of first memory region mapping in MK_memoryRegionMap[] array
 *	- n = no. of (consecutive) regions that belong to this partition.
 *
 * If n==0, r is not used.
*/
/* Deviation DCG-1 */
#define MK_MEMORYPARTITION(r,n)		{((n)==0)?MK_NULL:&MK_memRegionMap[(r)], (n)}

/* Define a memory region mapping - used by the configuration.
 *
 * Parameters:
 *	p	= partition index (currently not used: for documentation)
 *	r	= index of memory region in MK_memoryRegion[] array
 *	per	= permissions (non-legacy mode)
 *	sel	= additional hardware-specific selection criteria (non-legacy mode)
*/

#if MK_HAS_CPUFAMILYMEMORYREGIONMAP_T
#define MK_MEMORYREGIONMAP(p, r, per, sel) \
{	&MK_memRegion[(r)],					\
	(per),								\
	MK_CPUFAMILYMEMORYREGIONMAP(sel)	\
}
#else
#define MK_MEMORYREGIONMAP(p, r, per, sel) \
{	&MK_memRegion[(r)],					\
	(per)								\
}
#endif

/* Define a memory partition range - used by the configuration.
 *
 * Parameters:
 *	- b = first partition which is part of this range
 *	- n = number of partitions which are part of this range
*/
#define MK_MEMORYPARTITIONRANGE(b,n)	{ (b), (n) }

/* MK_MEMORYREGION - Define a memory region - used by the configuration.
 *
 * Parameters:
 *	start	- is the first address of the region
 *	bstart	- is the first address of the zero-initialized (".bss") part of the region
 *	limit	- is the limit address of the region (i.e. the first address ABOVE the region)
 *	idata	- is the address of the initialization data for the initialized (".data") part of the region
 *	fill	- is the value to initialize the implicitly-initialized part of the region with
 *	icore	- is the id of the core that will initialize the region, or -1 for all cores
 *	perms	- is the permissions granted for this region; combination of MK_MPERM_* defined by the architecture.
 *	select	- additional hardware-specific selection criteria
 *
 * MK_MR_INIT, MK_MR_STACK and MK_MR_NOINIT are simplified forms where the addresses are derived from the name of the
 * region using MK_RSA/MK_BSA/MK_RLA/MK_RDA prefixes.
*/

#if MK_HAS_CPUFAMILYMEMORYREGION_T
#define MK_MEMORYREGION(start,bstart,limit,idata,fill,icore,hwextra) \
{	(start),								\
	(bstart),								\
	MK_AdjustLinkerAddressForLimit(limit),	\
	(idata),								\
	(fill),									\
	(icore),								\
	MK_CPUFAMILYMEMORYREGION(hwextra)		\
}

#else /* no architecture specific extension for a memory region */

#define MK_MEMORYREGION(start,bstart,limit,idata,fill,icore,hwextra) \
{	(start),								\
	(bstart),								\
	MK_AdjustLinkerAddressForLimit(limit),	\
	(idata),								\
	(fill),									\
	(icore)									\
}
#endif

#ifndef MK_INITDATA
#define MK_INITDATA 1
#endif


/* preprocessor macros for different initialization types of provided memory
 * regions
 *
 * For each provided app, task or isr name an underscore is added to avoid
 * collisions between the preprocessor mapping of user defined names.
*/
/* Deviation MISRAC2012-1 <START> */

#if MK_INITDATA

#define MK_MR_INIT(name, icore, hwextra)  \
	MK_MEMORYREGION(                      \
			&MK_MR_START_ADR(_ ## name),  \
			&MK_MR_BSTART_ADR(_ ## name), \
			&MK_MR_LIMIT_ADR(_ ## name),  \
			&MK_MR_IDATA_ADR(_ ## name),  \
			MK_BSSFILL, (icore), hwextra)

#else
/* .data sections are already initialized by a bootloader or an equivalent
 * mechanism that runs before the MK is even started.
*/

#define MK_MR_INIT(name, icore, hwextra)  \
	MK_MEMORYREGION(                      \
			&MK_MR_START_ADR(_ ## name),  \
			&MK_MR_BSTART_ADR(_ ## name), \
			&MK_MR_LIMIT_ADR(_ ## name),  \
			MK_NULL,                      \
			MK_BSSFILL, (icore), hwextra)

#endif

#define MK_MR_STACK(name, icore, hwextra) \
	MK_MEMORYREGION(                      \
			&MK_MR_START_ADR(_ ## name),  \
			&MK_MR_START_ADR(_ ## name),  \
			&MK_MR_LIMIT_ADR(_ ## name),  \
			MK_NULL,                      \
			MK_STACKFILL, (icore), hwextra)

#define MK_MR_NOINIT(name, hwextra)      \
	MK_MEMORYREGION(                     \
			&MK_MR_START_ADR(_ ## name), \
			MK_NULL,                     \
			&MK_MR_LIMIT_ADR(_ ## name), \
			MK_NULL,                     \
			0u, -1, hwextra)

/* Deviation MISRAC2012-1 <STOP> */

/* Memory protection functions.
*/
#ifndef MK_ASM
void MK_InitMemoryProtection(mk_kernelcontrol_t *);
void MK_InitMemoryRegion(const mk_memoryregion_t *);
void MK_HwInitMemoryProtection(mk_kernelcontrol_t *);
#endif /* MK_ASM */

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)

/* Align up address to last valid address of page.
*/
#define MK_MMU_PAGE_LAST_ADDRESS_ALIGNUP(x)	\
		(((mk_address_t) (x)) | MK_HWMIN_PAGE_ALIGN_MASK)

#ifndef MK_ASM

/* Represent a flat memory region to be used during page-map generation.
*/
typedef struct mk_flatmemregion_s mk_flatmemregion_t;
struct mk_flatmemregion_s
{
	mk_machineword_t	*start;	/* First address inside of region. */
	mk_machineword_t	*end;	/* Last address inside of region. */
	mk_hwmmuflags_t		flags;	/* Page descriptor flags for permissions and mem type. */
};

#define MK_FLATMEMREGION_START(x)	((mk_address_t)(x)->start)
#define MK_FLATMEMREGION_END(x)		((mk_address_t)(x)->end)

#define MK_FLATMEMREGION_NEXT_ADDRESS(r)	\
		((MK_FLATMEMREGION_END(r) + 1u))

extern mk_objquantity_t MK_GenerateFlatPartitionMap(mk_flatmemregion_t *,
												mk_objquantity_t, mk_objectid_t, mk_objectid_t);
extern mk_boolean_t MK_CheckRegionAlignment(const mk_flatmemregion_t *, mk_objquantity_t);

#endif

#endif



#if (MK_MEM_PROT == MK_MEM_PROT_MMU)
#ifndef MK_ASM
/* Two-dimensional array to store the descriptors of all the generated page tables of all cores.
 * First index is the core, second index is the core local memory partition index.
*/
extern mk_pagetabledescriptor_t * const MK_corePageTables[MK_MAXCORES];
#endif
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
