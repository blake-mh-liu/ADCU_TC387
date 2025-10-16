/* Mk_c2_aux1_stack.c
 *
 * This file contains the aux1 stack for core 2.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c2_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if (MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) != 0
/* The aux1 stack for core 2
*/
mk_stackelement_t MK_c2_aux1Stack[MK_CFG_C2_AUX1_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

/* This constant ensures that this file is a valid C compilation unit. */
const mk_uint8_t MK_c2_noAux1Stack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
