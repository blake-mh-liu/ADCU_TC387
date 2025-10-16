/* Mk_c1_errorhook_stack.c
 *
 * This file contains the error-hook stack for core 1.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c1_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if MK_CFG_C1_HAS_ERRORHOOK
/* The errorhook stack for core 1.
*/
mk_stackelement_t MK_c1_errorhookStack[MK_CFG_C1_ERRORHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

const mk_uint8_t MK_c1_noErrorHookStack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
