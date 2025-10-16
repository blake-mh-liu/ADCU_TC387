/* Mk_TRICORE_c0_configuration.c
 *
 * This file contains tricore specific configuration items for core 0 (MPU region cache etc.)
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

#if ((MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) == 0)
mk_uint8_t MK_c0_unusedTRICOREConfig;
#else


/* MK_c0_MpuRegCache - Core-local MPU region cache.
*/
#if (MK_C0_MPUREGCACHE_SIZE > 0)
mk_mpubounds_t MK_c0_MpuRegCache[MK_C0_MPUREGCACHE_SIZE];
#endif

#if MK_CFG_C0_NMEMORYPARTITIONS > 0
mk_mpurwpermission_t MK_c0_MemoryPartitionPermissions[MK_CFG_C0_NMEMORYPARTITIONS];
#endif

mk_panicexceptionctx_t MK_c0_panicExceptionCtx;

#endif /* (MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) == 0 */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
