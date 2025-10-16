/* Mk_TRICORE_c2_cfg.h
 *
 * This file contains the declaration of the TRICORE specific configuration for Core 2
 *
 * If core 2 is not in use, all its configuration items map to a null value.
 *
 * If core 2 is in use, its configuration items map to the appropriate structures etc. The optional items
 * are defined as MK_NULL if not enabled.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_C2_CFG_H
#define MK_TRICORE_C2_CFG_H		1

#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_memoryprotection.h>
#include <Mk_Cfg.h>
#include <private/Mk_tool.h>


/* The following macro defines defaults for the use of the MPU register
 * readback on the different cores. These are meant to be overridden by the
 * user.
 * MK_MPU_REGISTER_CHECK is derived from these macros.
 */
#ifndef MK_CFG_C2_MPU_REGISTER_CHECK
#define MK_CFG_C2_MPU_REGISTER_CHECK	0
#endif

/* MK_C2_MPU_REGISTER_CHECK_FN points to the register check function of core C2.
*/
#if (MK_CFG_C2_MPU_REGISTER_CHECK == 1)
#define MK_C2_MPU_REGISTER_CHECK_FN	&MK_c2_CheckDynamicMpuRegisters
#else
#define MK_C2_MPU_REGISTER_CHECK_FN	MK_NULL
#endif


/* Definitions and declarations in case core C2 is inactive.
*/
#if ((MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) == 0)

extern mk_uint8_t MK_c2_unusedTRICOREConfig;

#define MK_TRICORE_CSA_ENTRY_C2 { 0u, 0u }

#ifndef MK_CFG_C2_NSTATICPARTITIONS
#define MK_CFG_C2_NSTATICPARTITIONS 0
#endif

#ifndef MK_CFG_C2_NMEMORYPARTITIONS
#define MK_CFG_C2_NMEMORYPARTITIONS 0
#endif

#ifndef MK_CFG_C2_DYNREGIONS_MAX
#define MK_CFG_C2_DYNREGIONS_MAX 0
#endif

#define MK_C2_MPUPERMISSONS MK_NULL
#define MK_C2_MPUREGCACHE MK_NULL

#define MK_C2_PANICEXCEPTIONCTX MK_NULL

#else
/* Definitions and declarations in case core C2 is active.
*/

/* Context Save Areas
 * These areas must be defined by the linker.
*/
#define MK_TRICORE_CSA_ENTRY_C2 {				\
	(mk_uint32_t) &MK_MR_START_ADR(_MK_Csa_C2), \
	(mk_uint32_t) &MK_MR_LIMIT_ADR(_MK_Csa_C2) }


/* MK_CFG_C2_NMEMORYPARTITIONS must be defined for active cores.
*/
#ifndef MK_CFG_C2_NMEMORYPARTITIONS
#error "MK_CFG_C2_NMEMORYPARTITIONS must be defined for active core C2"
#error "If memory protection is disabled, set MK_CFG_C2_NMEMORYPARTITIONS to zero"
#endif

/* MK_c2_MemoryPartitionPermissions
 * stores the permissions of core C2's memory partitions.
*/
#if (MK_CFG_C2_NMEMORYPARTITIONS > 0)
extern mk_mpurwpermission_t MK_c2_MemoryPartitionPermissions[MK_CFG_C2_NMEMORYPARTITIONS];
#define MK_C2_MPUPERMISSONS MK_c2_MemoryPartitionPermissions
#else
#define MK_C2_MPUPERMISSONS MK_NULL
#endif

/* MK_c2_MpuRegCache - Core-local MPU region cache.
*/
#define MK_C2_MPUREGCACHE_NENTRIES	(MK_CFG_C2_NMEMORYPARTITIONS - MK_CFG_C2_NSTATICPARTITIONS)
#if (MK_C2_MPUREGCACHE_NENTRIES > 0)
#define MK_C2_MPUREGCACHE_SIZE	(MK_C2_MPUREGCACHE_NENTRIES*MK_CFG_C2_DYNREGIONS_MAX)
#else
#define MK_C2_MPUREGCACHE_SIZE	0
#endif

#if (MK_C2_MPUREGCACHE_SIZE > 0)
extern mk_mpubounds_t MK_c2_MpuRegCache[MK_C2_MPUREGCACHE_SIZE];
#define MK_C2_MPUREGCACHE MK_c2_MpuRegCache
#else
#define MK_C2_MPUREGCACHE MK_NULL
#endif

/* Panic exception information.
*/
extern mk_panicexceptionctx_t MK_c2_panicExceptionCtx;
#define MK_C2_PANICEXCEPTIONCTX (&MK_c2_panicExceptionCtx)

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
