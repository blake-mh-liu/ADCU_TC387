/* Mk_TRICORE_board_setstmdebugmode.c
 *
 * This file contains the TRICORE function Tmpl_SetStmDebugMode()
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_setstmdebugmode.c 36735 2019-06-19 12:17:08Z mist9353 $
*/
#include <Mk_TRICORE_board_setstmdebugmode.h>
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_stm.h>
#include "Tmpl_TRICORE_ocds.h"

static void Tmpl_SetSingleStmDebugMode(mk_tricorestm_t *);

/* Tmpl_SetSingleStmDebugMode
 *
 * This function sets a single STM to debug mode, so it stops, when the CPU is stopped by the debugger.
*/
static void Tmpl_SetSingleStmDebugMode(mk_tricorestm_t *stm)
{
	stm->stm_ocs = (stm->stm_ocs & (mk_uint32_t)~((mk_uint32_t)TMPL_STM_OCS_SUS_MASK))
	                | TMPL_STM_OCS_SUS_WILL_STOP | TMPL_STM_OCS_SUS_WRITE_PROT;
}

/* Tmpl_SetStmDebugMode
 *
 * This function sets all STMs to debug mode, so they stop, when the CPU is stopped by the debugger.
*/
void Tmpl_SetStmDebugMode(void)
{
	/* Due to this if-statement, a slightly different start-up path is executed
	 * depending on whether a debugger is attached or not.
	 * That is:
	 *  - If you start with a debugger attached, you set the STMs to debug mode.
	 *  - If you start without debugger, the STMs aren't touched in this function.
	 * If you don't like this, feel free to remove this function (it's just demo code).
	 * Note, that if you remove this function, the STMs won't stop,
	 * when you stop the processor using the debugger.
	*/
	if (Tmpl_Ocds_MaySetStmsToDebugMode())
	{
		Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM0_BASE);

#if (MK_N_STMS > 1)
		Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM1_BASE);
#endif

#if (MK_N_STMS > 2)
		Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM2_BASE);
#endif

#if (MK_N_STMS > 3)
		Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM3_BASE);
#endif

#if (MK_N_STMS > 4)
		Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM4_BASE);
#endif

#if (MK_N_STMS > 5)
		Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM5_BASE);
#endif

#if (MK_N_STMS > 6)
#error "MK_N_STMS: Unexpected number of STMs"
#endif
	}

}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
