/* Mk_u_libgettaskcoreid.c
 *
 * This file contains the MK_LibGetTaskCoreId() function.
 *
 * This function yields the ID of the core, on which the given task runs.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_task.h>
#include <public/Mk_public_api.h>

#if MK_MAXCORES <= 1
#error "MK_LibGetTaskCoreId() is not needed for single-core operation. Check your makefiles!"
#endif

/* MK_LibGetTaskCoreId() - Gets the logical core ID of the given task.
 *
 * This function yields the logical ID of the core, on which the given task runs.
 * If an invalid task ID is passed, the result is MK_OBJECTID_INVALID.
 *
 * !LINKSTO      Microkernel.Function.CtrSubHelpers, 1
 * !doctype      src
*/
mk_objectid_t MK_LibGetTaskCoreId(mk_objectid_t taskId)
{
	mk_objectid_t coreId;
	if ((taskId < 0) || (taskId >= MK_nTasks))
	{
		coreId = MK_OBJECTID_INVALID;
	}
	else
	{
		mk_objectid_t coreIdPhy = MK_taskCfg[taskId].threadCfg.coreIndex;
		coreId = MK_GetLogicalCoreId(coreIdPhy);
	}
	return coreId;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
