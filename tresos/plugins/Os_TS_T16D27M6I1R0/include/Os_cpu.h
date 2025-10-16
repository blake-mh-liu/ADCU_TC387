/* Os_cpu.h
 *
 * This file provides characteristics of the current derivative's cpu.
 * It includes the target specific Os_*_cpu.h file.
 *
 * This file is used by the IOC to determine the number of cores provided by the hardware.
*/
#ifndef OS_CPU_H
#define OS_CPU_H

#include <Os_defs.h>

#include <Os_hwsel.h>
#include OS_HWSEL_CPU

/* OS_N_CORES_MAX - The number of cores provided by the hardware.
*/
#ifndef OS_N_CORES_MAX
#error "OS_N_CORES_MAX is undefined."
#endif


#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
