/* Mk_TRICORE_board_setstmdebugmode.h
 *
 * This file declares the TRICORE Tmpl_SetStmDebugMode function,
 * which switches the STM to debug mode.
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_setstmdebugmode.h 29747 2017-07-14 10:48:04Z aniv261689 $
*/
#ifndef MK_TRICORE_QMSETSTMDEBUGMODE_H
#define MK_TRICORE_QMSETSTMDEBUGMODE_H

#include <public/Mk_misra.h>
#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

#if (MK_TRICORE_CORE == MK_TRICORE_TC162)
#define TMPL_STM_OCS_SUS_MASK		MK_U(0x0F000000)
#define TMPL_STM_OCS_SUS_WILL_STOP	MK_U(0x02000000)
#define TMPL_STM_OCS_SUS_WRITE_PROT	MK_U(0x10000000)
#else
#error "Mk_TRICORE_board_setstmdebugmode.h is only implemented for TC 1.6.2 processors."
#endif

#ifndef MK_ASM
void Tmpl_SetStmDebugMode(void);
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
