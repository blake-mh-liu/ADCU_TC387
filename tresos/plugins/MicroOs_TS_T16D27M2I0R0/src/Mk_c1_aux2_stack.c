/* Mk_c1_aux2_stack.c
 *
 * This file contains the aux2 stack for core 1.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c1_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if (MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) != 0
/* The aux2 stack for core 1
*/
mk_stackelement_t MK_c1_aux2Stack[MK_CFG_C1_AUX2_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else
/* This constant ensures that this file is a valid C compilation unit. */
const mk_uint8_t MK_c1_noAux2Stack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
