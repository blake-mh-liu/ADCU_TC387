/* Mk_c0_idleshutdown_stack.c
 *
 * This file contains the idle/shutdown stack for core 0.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c0_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if (MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) != 0
/* The idle/shutdown stack for core 0.
*/
mk_stackelement_t MK_c0_idleshutdownStack[MK_CFG_C0_IDLESHUTDOWN_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

const mk_uint8_t MK_c0_noIdleShutdownStack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
