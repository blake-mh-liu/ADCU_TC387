/* Mk_c1_kernel_stack.c
 *
 * This file contains the kernel stack for core 1.
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
/* The kernel stack for core 1.
*/
mk_stackelement_t MK_c1_kernelStack[MK_CFG_C1_KERNEL_STACK_NELEMENTS + MK_HW_STACK_EXTRA];
#else

const mk_uint8_t MK_c1_noKernelStack = 0u;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
