/* Mk_TRICORE_c1_configuration.c
 *
 * This file contains tricore specific configuration items for core 1 (MPU region cache etc.)
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_error.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_memoryprotection.h>
#include <private/TRICORE/Mk_TRICORE_Cfg.h>
#include <Mk_Cfg.h>

#if ((MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) == 0)
mk_uint8_t MK_c1_unusedTRICOREConfig;
#else


/* MK_c1_MpuRegCache - Core-local MPU region cache.
*/
#if (MK_C1_MPUREGCACHE_SIZE > 0)
mk_mpubounds_t MK_c1_MpuRegCache[MK_C1_MPUREGCACHE_SIZE];
#endif

#if MK_CFG_C1_NMEMORYPARTITIONS > 0
mk_mpurwpermission_t MK_c1_MemoryPartitionPermissions[MK_CFG_C1_NMEMORYPARTITIONS];
#endif

mk_panicexceptionctx_t MK_c1_panicExceptionCtx;

#endif /* (MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) == 0 */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
