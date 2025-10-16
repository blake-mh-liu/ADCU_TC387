/* Mk_k_initapplications.c
 *
 * This file contains the function MK_InitApplications().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>
#include <private/Mk_application.h>
#include <private/Mk_task.h>
#include <private/Mk_isr.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_panic.h>

static void MK_InitCheckAppId(mk_objectid_t);
static void MK_InitCheckRestartTask(mk_objectid_t);

/* MK_InitCheckAppId() checks, whether the given application id is valid.
*/
static void MK_InitCheckAppId(mk_objectid_t appId)
{
	if ( (appId < MK_APPL_NONE) || (appId >= MK_nApps) )
	{
		MK_StartupPanic(MK_panic_UnexpectedOsApplication);
	}
}

/* MK_InitCheckRestartTask() checks the restart task of the given application.
*/
static void MK_InitCheckRestartTask(mk_objectid_t appId)
{
	mk_objectid_t taskId = MK_appCfg[appId].restartTask;

	if ( (taskId < MK_INVALID_TASK) || (taskId >= MK_nTasks) )
	{
		MK_StartupPanic(MK_panic_InvalidTaskIdInConfiguration);
	}

	if ( (taskId > MK_INVALID_TASK) && (MK_taskCfg[taskId].threadCfg.applicationId != appId) )
	{
		MK_StartupPanic(MK_panic_UnexpectedOsApplication);
	}
}

/* MK_InitApplications() performs startup-checks related to OS-Applications.
 *
 * The startup-check ensures that if no OS-Applications are configured, there must not be any task or ISR
 * that belongs to an OS-Application.
 * It also checks that the task ids of restart tasks are in range.
 *
 * There is no need to check threads coming from Mk_configuration.c, because these have no OS-Application Id assigned
 * and they are constant.
 *
 * !LINKSTO Microkernel.Function.MK_InitApplications, 2
 * !doctype src
*/
void MK_InitApplications(mk_objectid_t coreIndex)
{
	mk_objquantity_t i;

	/* Range-check on all OS-Application Ids on tasks
	*/
	for (i = 0; i < MK_nTasks; i++)
	{
		MK_InitCheckAppId(MK_taskCfg[i].threadCfg.applicationId);
	}

	/* Range-check on all OS-Application Ids on ISRs
	*/
	for (i = 0; i < MK_nIsrs; i++)
	{
		MK_InitCheckAppId(MK_isrCfg[i].threadCfg.applicationId);
	}

	/* Range-check on all task ids of OS-Applications with restart tasks.
	*/
	for (i = 0; i < MK_nApps; i++)
	{
		MK_InitCheckRestartTask((mk_objectid_t)i);

		if ( MK_appCfg[i].coreIndex == coreIndex )
		{
			MK_appCfg[i].dynamic->appState = APPLICATION_ACCESSIBLE;
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
