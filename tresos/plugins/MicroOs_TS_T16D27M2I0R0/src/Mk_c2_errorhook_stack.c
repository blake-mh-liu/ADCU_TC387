/* Mk_c2_errorhook_stack.c
 *
 * This file contains the error-hook stack for core 2.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c2_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if MK_CFG_C2_HAS_ERRORHOOK
/* The errorhook stack for core 2.
*/
mk_stackelement_t MK_c2_errorhookStack[MK_CFG_C2_ERRORHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

const mk_uint8_t MK_c2_noErrorHookStack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
