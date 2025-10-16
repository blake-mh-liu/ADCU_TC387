/* Mk_c0_errorhook_stack.c
 *
 * This file contains the error-hook stack for core 0.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c0_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if MK_CFG_C0_HAS_ERRORHOOK
/* The errorhook stack for core 0.
*/
mk_stackelement_t MK_c0_errorhookStack[MK_CFG_C0_ERRORHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

const mk_uint8_t MK_c0_noErrorHookStack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
