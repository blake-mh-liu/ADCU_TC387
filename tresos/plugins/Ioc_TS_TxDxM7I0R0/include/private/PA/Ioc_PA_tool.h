/* Ioc_PA_tool.h - PA and tool-specific definitions.
 *
 * This file defines tool-specific macros, etc.
 *
 * (c) Elektrobit Automotive GmbH
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef directives are not permitted.
 *
 * Reason:
 *  We must use #ifdef here, because the macro EB_STATIC_CHECK is provided by
 *  external tooling outside the control of the IOC build.
 *  EB_STATIC_CHECK is used to hide tool specific extensions
 *  which would otherwise break the MISRA checker run.
*/
#ifndef IOC_PA_TOOL_H
#define IOC_PA_TOOL_H

#include <public/Ioc_libconfig.h>
#include <private/Ioc_tool.h>

/* Deviation DCG-1 <+1> */
#ifdef EB_STATIC_CHECK
extern void IOC_MBAR(void);
#else

#if (IOC_LCFG_KERNEL_TYPE == IOC_AUTOCOREOS)
/* Get tool-specific macros from OS headers: */
#define IOC_MBAR()	do { OS_TOOL_ASM_KEYWORD("mbar");} while (0)

#elif (IOC_LCFG_KERNEL_TYPE == IOC_MICROKERNEL)

/* There's no assembler abstraction in the microkernel,
 * so it must be defined here.
*/
#if (IOC_TOOL == IOC_diab) || (IOC_TOOL == IOC_ghs)
#define IOC_MBAR()	do { __asm("mbar"); } while (0)
#elif (IOC_TOOL == IOC_gnu)
#define IOC_MBAR()	do { __asm__("mbar"); } while (0)
#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif

#else /* IOC_LCFG_KERNEL_TYPE  */
#error "Unknown kernel type."
#endif /* IOC_LCFG_KERNEL_TYPE */

#endif /* EB_STATIC_CHECK */

#endif /* IOC_PA_TOOL_H */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
