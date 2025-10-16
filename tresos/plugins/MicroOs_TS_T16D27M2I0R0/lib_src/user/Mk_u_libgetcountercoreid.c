/* Mk_u_libgetcountercoreid.c
 *
 * This file contains the MK_LibGetCounterCoreId() function.
 *
 * This function yields the ID of the core, on which the given counter lives.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_ctrsub.h>
#include <public/Mk_public_api.h>

#if (MK_MAXCORES <= 1)
#error "MK_LibGetCounterCoreId() is not needed for single-core operation. Check your makefiles!"
#endif

/* MK_LibGetCounterCoreId() - Gets the core ID of the given counter.
 *
 * This function yields the logical ID of the core, on which the given counter lives.
 * If an invalid counter ID is passed, the result is MK_OBJECTID_INVALID.
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_objectid_t MK_LibGetCounterCoreId(mk_objectid_t counterId)
{
	mk_objectid_t coreId;
	if ((counterId < 0) || (counterId >= MK_nCounters))
	{
		coreId = MK_OBJECTID_INVALID;
	}
	else
	{
		mk_objectid_t coreIdPhy = MK_CounterPropertyTable[counterId].coreIndex;
		coreId = MK_GetLogicalCoreId(coreIdPhy);
	}
	return coreId;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
