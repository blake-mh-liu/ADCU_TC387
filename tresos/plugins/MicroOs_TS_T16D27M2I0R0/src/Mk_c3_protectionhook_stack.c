/* Mk_c3_protectionhook_stack.c
 *
 * This file contains the protection-hook stack for core 3.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c3_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if MK_CFG_C3_HAS_PROTECTIONHOOK
/* The protection-hook stack for core 3.
*/
mk_stackelement_t MK_c3_protectionHookStack[MK_CFG_C3_PROTECTIONHOOK_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

const mk_uint8_t MK_c3_noProtectionHookStack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
