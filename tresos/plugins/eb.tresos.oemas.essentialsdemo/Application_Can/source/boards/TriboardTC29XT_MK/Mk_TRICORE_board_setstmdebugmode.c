/* Mk_TRICORE_board_setstmdebugmode.c
 *
 * This file contains the TRICORE function Tmpl_SetStmDebugMode()
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_setstmdebugmode.c 23786 2016-06-17 13:46:29Z mist8519 $
*/
#include <Mk_TRICORE_board_setstmdebugmode.h>
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_stm.h>

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
	Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM0_BASE);
#if (MK_N_STMS > 1)
	Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM1_BASE);
#endif
#if (MK_N_STMS > 2)
	Tmpl_SetSingleStmDebugMode((mk_tricorestm_t *)MK_STM2_BASE);
#endif
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
