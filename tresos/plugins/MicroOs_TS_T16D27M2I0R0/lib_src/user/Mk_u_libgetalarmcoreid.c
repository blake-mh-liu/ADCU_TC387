/* Mk_u_libgetalarmcoreid.c
 *
 * This file contains the MK_LibGetAlarmCoreId() function.
 *
 * This function yields the ID of the core, on which the given alarm runs.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_ctrsub.h>
#include <public/Mk_public_api.h>

#if MK_MAXCORES <= 1
#error "MK_LibGetAlarmCoreId() is not needed for single-core operation. Check your makefiles!"
#endif

/* MK_LibGetAlarmCoreId() - Gets the core ID of the given alarm.
 *
 * This function yields the logical ID of the core on which the given alarm runs.
 * If an invalid alarm ID is passed, the result is MK_OBJECTID_INVALID.
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_objectid_t MK_LibGetAlarmCoreId(mk_objectid_t alarmId)
{
	mk_objectid_t coreId;
	if ((alarmId < 0) || (alarmId >= MK_nAlarms))
	{
		coreId = MK_OBJECTID_INVALID;
	}
	else
	{
		mk_objectid_t coreIdPhy = MK_AlarmPropertyTable[alarmId].coreIndex;
		coreId = MK_GetLogicalCoreId(coreIdPhy);
	}
	return coreId;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
