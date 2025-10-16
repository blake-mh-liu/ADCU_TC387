/* Ioc_hw_characteristics.h - Provides characteristics of the current derivative's cpu.
 *
 * This file defines hardware specific characteristics.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef IOC_HW_CHARACTERISTICS_H
#define IOC_HW_CHARACTERISTICS_H

#include <public/Ioc_libconfig.h>


#if (IOC_LCFG_KERNEL_TYPE == IOC_MICROKERNEL)

#include <public/Mk_hw_characteristics.h>
#define IOC_MAXCORES MK_MAXCORES

#elif (IOC_LCFG_KERNEL_TYPE == IOC_AUTOCOREOS)

#include <Os_cpu.h>
#define IOC_MAXCORES OS_N_CORES_MAX

#else /* IOC_LCFG_KERNEL_TYPE */
#error "Unknown kernel type."
#endif /* IOC_LCFG_KERNEL_TYPE */


/* Perform a sanity check to see whether we assigned IOC_MAXCORES correctly. */
#if (IOC_MAXCORES < 1)
#error "IOC_MAXCORES must not be less than 1."
#endif


#endif /* IOC_HW_CHARACTERISTICS_H */
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
