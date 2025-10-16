/* TRICORE-setupcache.c
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <TRICORE/Os_TRICORE_core.h>
#include <Os_tool.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_SetupCache()
 *
 * NOTE: This function is meant to be called early during core startup and
 * hence assumes that ENDINIT protection is OFF.
 *
 * Sets up the instruction and data cache for the current core.
 *
 * Some core types (TC1.6E) do not have a data cache. For those, the cache
 * remains disabled through the physical memory attributes configured, though
 * the bypass flag in DCON0 is disabled.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_SetupCache(os_boolean_t enableInsnCache, os_boolean_t enableDataCache)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_coreid_t myCoreId = OS_GetMyCoreId();
	os_uint32_t pma0;
	os_uint32_t pma1;
	os_uint32_t pcon0 = OS_MFCR(OS_PCON0);
	os_uint32_t dcon0 = OS_MFCR(OS_DCON0);

	/* myCoreId is not used with all variants of CACHExABLED macros */
	OS_PARAM_UNUSED(myCoreId);

	if(enableInsnCache)
	{
		pma1 = OS_PMA1_CACHEENABLED(myCoreId);
		pcon0 &= ~((os_uint32_t)PCON0_CACHE_BYPASS);
	}
	else
	{
		pma1 = OS_PMA1_CACHEDISABLED(myCoreId);
		pcon0 |= (PCON0_CACHE_BYPASS);
	}

	if(enableDataCache)
	{
		pma0 = OS_PMA0_CACHEENABLED(myCoreId);
		dcon0 &= ~((os_uint32_t)DCON0_CACHE_BYPASS);
	}
	else
	{
		pma0 = OS_PMA0_CACHEDISABLED(myCoreId);
		dcon0 |= (DCON0_CACHE_BYPASS);
	}

	OS_MTCR(OS_PMA0, pma0);
	OS_MTCR(OS_PMA1, pma1);
	OS_MTCR(OS_DCON0, dcon0);
	OS_MTCR(OS_PCON0, pcon0);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_setupcache_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
