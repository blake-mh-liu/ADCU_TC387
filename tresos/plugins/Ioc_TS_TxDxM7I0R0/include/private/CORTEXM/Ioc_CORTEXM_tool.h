/* Ioc_CORTEXM_tool.h - CORTEXM tool-specific definitions.
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
#ifndef IOC_CORTEXM_TOOL_H
#define IOC_CORTEXM_TOOL_H

#include <public/Ioc_libconfig.h>
#include <private/Ioc_tool.h>

/* Deviation DCG-1 <+1> */
#ifdef EB_STATIC_CHECK
#define IOC_MBAR() do { /* nothing */ } while (0)
#else

#if (IOC_LCFG_KERNEL_TYPE == IOC_AUTOCOREOS)
/* Get tool-specific macros from OS headers: */
#define IOC_MBAR()	OS_DSB()
#elif (IOC_LCFG_KERNEL_TYPE == IOC_MICROKERNEL)

#include <private/CORTEXM/Mk_CORTEXM_tool.h>

#define IOC_MBAR()	MK_CORTEXM_DSB()

#else /* IOC_LCFG_KERNEL_TYPE  */
#error "Unknown kernel type."
#endif /* IOC_LCFG_KERNEL_TYPE */

#endif /* EB_STATIC_CHECK */

#endif /* IOC_CORTEXM_TOOL_H */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
