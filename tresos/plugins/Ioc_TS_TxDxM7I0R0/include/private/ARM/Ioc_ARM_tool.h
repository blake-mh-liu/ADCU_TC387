/* Ioc_ARM_tool.h - ARM and tool-specific definitions.
 *
 * This file defines tool-specific macros, etc.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef IOC_ARM_TOOL_H
#define IOC_ARM_TOOL_H


#include <public/Ioc_libconfig.h>
#include <private/Ioc_tool.h>

/* OS specific includes: */
#if (IOC_LCFG_KERNEL_TYPE == IOC_MICROKERNEL)
#include <private/ARM/Mk_ARM_tool.h>
#elif (IOC_LCFG_KERNEL_TYPE == IOC_AUTOCOREOS)
/* No additional header required at the moment. */
#else /* IOC_LCFG_KERNEL_TYPE  */
#error "Unknown kernel type."
#endif /* IOC_LCFG_KERNEL_TYPE */


/* Get tool-specific macros from OS headers.
*/
#if (IOC_LCFG_KERNEL_TYPE == IOC_MICROKERNEL)
#define IOC_ARM_DSB() MK_ARM_DSB()
#elif (IOC_LCFG_KERNEL_TYPE == IOC_AUTOCOREOS)
#define IOC_ARM_DSB() OS_ARM_DSB_SY()
#endif /* IOC_LCFG_KERNEL_TYPE  */


#endif /* IOC_ARM_TOOL_H */
