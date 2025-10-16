/* Mk_c3_kernel_stack.c
 *
 * This file contains the kernel stack for core 3.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <configuration/Mk_c3_cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

#if (MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) != 0
/* The kernel stack for core 3.
*/
mk_stackelement_t MK_c3_kernelStack[MK_CFG_C3_KERNEL_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

const mk_uint8_t MK_c3_noKernelStack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
