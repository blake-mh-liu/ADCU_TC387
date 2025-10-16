/* Mk_board.c - board specific startup file for TriboardTC297
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board.c 27098 2017-01-19 09:45:29Z mist9353 $
*/
#include <public/Mk_public_types.h>
#include <QM/Mk_qmdonothing.h>
#include <private/TRICORE/Mk_TRICORE_wdt.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <Mk_TRICORE_board_pll.h>
#include <Mk_qmboard.h>
#include <Mk_Cfg.h>
#include <Mk_TRICORE_board_setstmdebugmode.h>
#include <Mk_TRICORE_board_setupcache.h>

#ifndef MK_BOARD_DISABLE_WATCHDOG
#define MK_BOARD_DISABLE_WATCHDOG 0
#endif

#ifndef USE_TASKING_CINIT
#define USE_TASKING_CINIT	0
#endif

#if USE_TASKING_CINIT
extern void _c_init(void);  /* tasking C initialization function; Note: ASIL unknown! */
#endif

/* MK_InitHardwareBeforeData()
 *
 * MK_InitHardwareBeforeData() is called during startup before the .data and .bss sections
 * have been initialised. The initial values of non-automatic variables must not be relied
 * upon here. Values written to such variables will be lost after this function returns.
 *
 * External RAM, ROM, FLASH etc. can be set up here.
 * PLL initialisation should go here so that the RAM initialisation runs at full speed.
*/
void MK_InitHardwareBeforeData(void)
{
	if (MK_HwGetCoreIndex() == MK_CFG_HWMASTERCOREINDEX)
	{
		/* Setup PLL and clocks
		*/
		Tmpl_SetupClocks(MK_QMBOARD_PLLCON0, MK_QMBOARD_PLLCON1, MK_QMBOARD_CCUCON0, MK_QMBOARD_CCUCON1);

		/* Disable watchdogs - use specific value to prevent accidential activation
		*/
#if MK_BOARD_DISABLE_WATCHDOG == 0xa4420810
		MK_WriteEndinit(0);
		MK_WriteSafetyEndinit(0);

		MK_GetScuWdtCpuCon()->wdtxcon1 |= TMPL_SCU_WDTCON1_DR;
		MK_scu_wdtscon->wdtxcon1 |= TMPL_SCU_WDTCON1_DR;

		MK_WriteSafetyEndinit(1);
		MK_WriteEndinit(1);
#endif

		/* Set STM debug mode.
		*/
		Tmpl_SetStmDebugMode();
	}

	/* Setup the cache. This is done once per core.
	*/
	MK_WriteEndinit(0);
	Tmpl_SetupCache();
	MK_WriteEndinit(1);

	MK_QmDoNothing();		/* QM marker for binary */
}

/* MK_InitHardwareAfterData()
 *
 * MK_InitHardwareAfterData() is called during startup after the .data and .bss sections
 * have been initialized (so global variables can
 * now be used). The BoardInit() can be used to start up drivers etc.
*/
void MK_InitHardwareAfterData(void)
{
#if USE_TASKING_CINIT
	/* Call the Tasking compilers initialization routine.
	 *
	 * This is done in MK_InitHardwareAfterData() before any other action, because the
	 * microkernel just initialized all data, but perhaps incorrectly.
	*/
	_c_init();
#endif

	MK_QmDoNothing();		/* QM marker for binary */
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
