/* Mk_TRICORE_board_setupcache.c
 *
 * This file contains the TRICORE function Tmpl_SetupCache()
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_setupcache.c 22171 2016-02-09 14:06:06Z mist8519 $
*/
#include <Mk_TRICORE_board_setupcache.h>
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

/* Tmpl_SetupCache
 *
 * This function sets the default cache bits and enables the cache for data and code.
 * ENDINIT protection must be turned off before this function is called.
*/
void Tmpl_SetupCache(void)
{
	mk_uint32_t conval;

	/* Set default cache enable bits. */
	/* data */
	MK_MTCR(MK_PMA0, TMPL_CACHE_ENABLE_BITS);
	/* instructions */
	MK_MTCR(MK_PMA1, TMPL_CACHE_ENABLE_BITS);

	/* Enable data cache. */
	conval = MK_MFCR(MK_DCON0);
	conval &= ~((mk_uint32_t)TMPL_DCON0_CACHE_BYPASS);
	MK_MTCR(MK_DCON0, conval);

	/* Enable instruction cache. */
	conval = MK_MFCR(MK_PCON0);
	conval &= ~((mk_uint32_t)TMPL_PCON0_CACHE_BYPASS);
	MK_MTCR(MK_PCON0, conval);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
