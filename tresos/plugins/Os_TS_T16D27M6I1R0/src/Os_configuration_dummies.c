/* Os_configuration_dummies.c
 *
 * This file contains some dummy constants to keep the linker happy
 * then the build method is "link everything and hope for the best".
 *
 * Do not include this file into the file lists for the OS. When a library build is used,
 * this file is unnecessary and simply adds to the ROM footprint.
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#include <Os_types.h>
#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_tool.h>
#include <Os_configuration.h>
#include <Os_syscalls.h>
#include <Os_kernel.h>
#include <board.h>
#include <Os_api.h>
#include <Os_messagequeue.h>
#include <Os_configuration_decls.h>

/*!
 * OS_startModeAlarms
 * OS_autoStartAlarms
 *
 * Dummy arrays with a single invalid entry each.
*/

#ifndef OS_STARTMODEALARMS

#include <memmap/Os_mm_const16_begin.h>
const os_uint16_t OS_startModeAlarms[1] = { 0xffff };
#include <memmap/Os_mm_const16_end.h>

#include <memmap/Os_mm_const_begin.h>
const os_autoalarm_t OS_autoStartAlarms[] = { {0x00, 0x00, 0x00, 0x00} };
#include <memmap/Os_mm_const_end.h>

#endif /* OS_STARTMODEALARMS */


/*!
 * OS_startModeSchedules
 * OS_autoStartSchedules
 *
 * Dummy arrays with a single invalid entry each.
*/
#ifndef OS_STARTMODESCHEDULES

#include <memmap/Os_mm_const16_begin.h>
const os_uint16_t OS_startModeSchedules[1] = { 0xffff };
#include <memmap/Os_mm_const16_end.h>

#include <memmap/Os_mm_const_begin.h>
const os_autoschedule_t OS_autoStartSchedules[1] = { {0x00, 0x00, 0x00} };
#include <memmap/Os_mm_const_end.h>

#endif /* OS_STARTMODESCHEDULES */

/*!
 * OS_startModeTasks
 * OS_autoStartTasks
 *
 * Dummy arrays with a single invalid entry each.
*/
#ifndef OS_STARTMODETASKS

#include <memmap/Os_mm_const16_begin.h>
const os_uint16_t OS_startModeTasks[1] = { 0xffff };
#include <memmap/Os_mm_const16_end.h>

#include <memmap/Os_mm_const_begin.h>
const os_taskid_t OS_autoStartTasks[1] = { INVALID_TASK };
#include <memmap/Os_mm_const_end.h>

#endif /* OS_STARTMODETASKS */

/*!
 * OS_alarmCallback
 *
 * A dummy array with a single invalid entry.
 *
 * Most of the alarm arrays use the base pointer method.
*/
#if OS_NALARMCALLBACKS == 0
#include <memmap/Os_mm_const_begin.h>
const os_alarmcallback_t OS_alarmCallback[1] = { OS_NULL };
#include <memmap/Os_mm_const_end.h>
#endif

/*!
 * OS_rateIndex
 * OS_rateTimer
 *
 * Dummy arrays with a single invalid entry each.
*/
#if OS_NRATEMONS == 0

#if (OS_N_CORES == 1)
#include <memmap/Os_mm_var_begin.h>
os_rateindex_t OS_rateIndex[1];
#include <memmap/Os_mm_var_end.h>
#else
#include <memmap/Os_mm_const_begin.h>
os_rateindex_t * const OS_rateIndex_ptr[1] = { OS_NULL };
#include <memmap/Os_mm_const_end.h>
#endif /* OS_N_CORES == 1 */

#endif /* OS_NRATEMONS != 0 */

/*!
 * OS_rateMonitor
 *
 * A dummy array with a single invalid entry.
*/
#if OS_NRATEMONS == 0

#include <memmap/Os_mm_const_begin.h>
const os_ratemonitor_t OS_rateMonitor[1] = { {OS_NULL, 0x00, 0x00} };
#include <memmap/Os_mm_const_end.h>

#endif /* OS_NRATEMONS == 0 */



/*!
 * OS_startupCheckFunc
 *
 * A dummy array with a single invalid entry.
*/
#if (OS_CONFIGMODE & OS_STARTUPCHECK) == 0

#include <memmap/Os_mm_const_begin.h>
os_schkfunc_t const OS_startupCheckFunc[1] = { OS_NULL };
#include <memmap/Os_mm_const_end.h>

#endif /* OS_CONFIGMODE & OS_STARTUPCHECK */

/* Define this to ensure that this file is a valid C compilation unit
 * in the cases where all of the above are used and defined normally in Os_condiguration.c
*/
#if \
 defined(OS_STARTMODEALARMS)				&& \
 defined(OS_STARTMODESCHEDULES)				&& \
 defined(OS_STARTMODETASKS)					&& \
 (OS_NALARMCALLBACKS != 0)					&& \
 (OS_NRATEMONS != 0)						&& \
 ((OS_CONFIGMODE & OS_STARTUPCHECK) != 0)
#include <Os_dummies.h>
const os_uint8_t OS_dummy_Os_configuration_dummies_c = 0xeb;
#endif

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_Os_configuration_dummies_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
