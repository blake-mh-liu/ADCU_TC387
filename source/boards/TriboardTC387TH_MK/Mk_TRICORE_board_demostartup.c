/* Mk_TRICORE_board_demostartup.c
 *
 * This file contains the TRICORE startup function Tmpl_DemoStartup()
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_demostartup.c 37368 2019-08-23 14:17:57Z miwi261726 $
*/

#include <Mk_TRICORE_board_startup.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/TRICORE/Mk_TRICORE_startup.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <private/TRICORE/Mk_TRICORE_exceptionhandling.h>
#include <private/TRICORE/Mk_TRICORE_wdt.h>
#include "Mk_qmboard.h"

/* Tmpl_StartupAutosarCores
 *
 * This function does some of the preparation which has to be done before jumping to MK_Entry2.
 *
 * Note, that everything done here is not reliable, because our memory (CSA, stack) is not protected
 * from external bus masters.
*/

MK_ATTR_NO_STACKPROT void Tmpl_DemoStartup(void)
{
	mk_objectid_t const coreId = MK_HwGetCoreIndex();

	/* The OS expects that its startup is not continued, if an exception occurs.
	 * For our demo we set the startup exception table.
	*/
	MK_WriteEndinit(0u);
	MK_MTCR(MK_BTV, (mk_uint32_t) &MK_StartupExceptionTable);
	MK_WriteEndinit(1u);

	/* Core 0 is the core that is started by hardware.
	 * If other cores are supposed to run, we have to start them here.
	*/
	if (coreId == 0)
	{
		/* Initialize core synchronization spots, _before_ the other cores are started.
		*/
		MK_InitSyncHere();

		/* Starts all cores which are meant to be controlled by the OS.
		*/
		Tmpl_StartupAutosarCores();
	}

	/* If this core isn't supposed to run during the demo, it shall halt here.
	*/
	if ((MK_coreProperties[coreId] & MK_COREPROP_STARTMASK) == MK_COREPROP_NOTUSED)
	{
		/* This core is not supposed to run.
		 * Before halting we switch off the watchdog of the current core.
		*/
		MK_WriteEndinit(0);
		MK_GetScuWdtCpuCon()->wdtxcon1 |= TMPL_SCU_WDTCON1_DR;
		MK_WriteEndinit(1);

		TMPL_ENDLESSLOOP();
	}
}
