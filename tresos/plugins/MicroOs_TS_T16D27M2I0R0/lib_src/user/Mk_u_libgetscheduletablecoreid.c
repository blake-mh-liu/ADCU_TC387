/* Mk_u_libgetscheduletablecoreid.c
 *
 * This file contains the MK_LibGetScheduleTableCoreId() function.
 *
 * This function yields the ID of the core, on which the given schedule table runs.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_ctrsub.h>
#include <public/Mk_public_api.h>

#if MK_MAXCORES <= 1
#error "MK_LibGetScheduleTableCoreId() is not needed for single-core operation. Check your makefiles!"
#endif

/* MK_LibGetScheduleTableCoreId() - Gets the logical core ID of the given schedule table.
 *
 * This function yields the logical ID of the core, on which the given schedule table runs.
 * If an invalid schedule table ID is passed, the result is MK_OBJECTID_INVALID.
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_objectid_t MK_LibGetScheduleTableCoreId(mk_objectid_t schedId)
{
	mk_objectid_t coreId;
	if ((schedId < 0) || (schedId >= MK_nScheduleTables))
	{
		coreId = MK_OBJECTID_INVALID;
	}
	else
	{
		mk_objectid_t coreIdPhy = MK_ScheduleTablePropertyTable[schedId].coreIndex;
		coreId = MK_GetLogicalCoreId(coreIdPhy);
	}
	return coreId;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
