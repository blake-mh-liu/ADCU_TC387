/* Mk_TRICORE_board_setupcache.h
 *
 * This file declares the TRICORE cache setup functions.
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_setupcache.h 29747 2017-07-14 10:48:04Z aniv261689 $
*/
#ifndef MK_TRICORE_BOARD_SETUPCACHE_H
#define MK_TRICORE_BOARD_SETUPCACHE_H

#include <public/Mk_misra.h>
#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

#if (MK_TRICORE_CORE == MK_TRICORE_TC162)
#define TMPL_PCON0_CACHE_BYPASS	MK_U(0x2)
#define TMPL_DCON0_CACHE_BYPASS	MK_U(0x2)
/* These are the default cache bits:
 * The caches are enabled on segments 8 (flash) and 9 (LMU).
 * SM_AURIX_16 is fulfilled as long as there is no shared data in segment 9.
*/
#define TMPL_CACHE_ENABLE_BITS	MK_U(0x300)
#else
#error "Mk_TRICORE_board_setupcache.h only supports TC 1.6.2 processors"
#endif

#ifndef MK_ASM
void Tmpl_SetupCache(void);
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
