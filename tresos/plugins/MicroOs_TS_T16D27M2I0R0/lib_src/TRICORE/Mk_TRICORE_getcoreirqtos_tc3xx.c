/* Mk_TRICORE_getcoreirqtos_tc3xx.c
 *
 * This file contains the function MK_TC3XX_GetCoreIrqTos() for TRICORE TC3XX
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>

/* MK_TC3XX_GetCoreIrqTos()
 *
 * This function returns the type of service (TOS) of the current core for an IRQ configuration.
*/

mk_uint32_t MK_TC3XX_GetCoreIrqTos(void)
{
	mk_uint32_t core_index = MK_TricoreGetCoreIndex();
	mk_uint32_t ret_tos = 0u;
	if (core_index != 0u)
	{
		ret_tos = ((mk_uint32_t)((core_index & 7u) + 1u)) << MK_SRC_TOS_SHIFT;
	}
	return ret_tos;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
