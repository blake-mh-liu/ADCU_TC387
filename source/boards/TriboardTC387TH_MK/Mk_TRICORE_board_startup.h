/* Mk_TRICORE_board_startup.h
 *
 * This file declares TRICORE startup functions.
 * These functions are for demonstration purpose only (no ASIL).
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_startup.h 37368 2019-08-23 14:17:57Z miwi261726 $
*/
#ifndef MK_TRICORE_BOARD_STARTUP_H
#define MK_TRICORE_BOARD_STARTUP_H

#include <public/Mk_misra.h>
#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>
#include <private/Mk_tool.h>

/* Watchdog timer disable bit.
*/
#if (MK_TRICORE_CORE == MK_TRICORE_TC162)
#define TMPL_SCU_WDTCON1_DR		MK_U(0x00000008)
#else
#error "Unknown TRICORE core."
#endif

#ifndef MK_ASM
MK_ATTR_NO_STACKPROT void Tmpl_StartupAutosarCores(void);
MK_ATTR_NO_STACKPROT void Tmpl_DemoStartup(void);

/* MK_Entry()
 *
 * MK_Entry is a demo function written in assembler.
 * It performs some preparations and then jumps to MK_Entry2.
 * MK_Entry2 is the actual entry of the microkernel.
*/
void MK_Entry(void);
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
