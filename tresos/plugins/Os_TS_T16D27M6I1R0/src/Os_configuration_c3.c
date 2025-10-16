/* Os_configuration_c3.c
 *
 * This file contains the architecture-independent kernel configuration data for core C3.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* CHECK: NOPARSE */
#include <Os_types.h>
#include <Os_tool.h>
#include <Os_configuration.h>
#include <Os_kernel.h>
#include <Os_configuration_decls.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)
#include <Os_syscalls.h>
#include <board.h>
#include <Os_api.h>
#include <Os_messagequeue.h>
#endif /* OS_KERNEL_TYPE != OS_MICROKERNEL */

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)
#include <Mk_qmboard.h>
#endif /* OS_KERNEL_TYPE == OS_MICROKERNEL */



#if ((OS_PROPERTIES_CORE3 & OS_COREPROP_USED_BIT) != OS_COREPROP_USED_BIT)
#include <memmap/Os_mm_var_begin.h>
os_uint8_t OS_unused_configuration_c3;
#include <memmap/Os_mm_var_end.h>
#else

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)
/*!
 * OS_appDynamic_core3
 *
 * Application state of applications on core C3.
*/
#include <memmap/Os_mm_var_begin.h>
#if (OS_NAPPS_CORE3 != 0)
OS_SECTION_PRAGMA(OS_appDynamic_core3, .bss.core3.appDynamic)
os_appdynamic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.appDynamic)
		OS_appDynamic_core3[OS_NAPPS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.appDynamic);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * OS_taskAccounting_core3
 *
 * The accounting information for tasks, one entry per task that needs it.
 * They are only accessible via the pointer os_task_t::accounting.
*/
#if (OS_NTASKACCOUNTING != 0)
#include <memmap/Os_mm_var_begin.h>
#if (OS_NTASKACCOUNTING_CORE3 != 0)
OS_SECTION_PRAGMA(OS_taskAccounting_core3, .bss.core3.taskAccounting)
os_taskaccounting_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.taskAccounting)
		OS_taskAccounting_core3[OS_NTASKACCOUNTING_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.taskAccounting);
#endif
#include <memmap/Os_mm_var_end.h>
#endif

/*!
 * OS_taskDynamic_core3
 *
 * The dynamic status of tasks, one entry per task. Note: this is not the
 * context of the task, though it may contain it.
*/
#include <memmap/Os_mm_var_begin.h>
#if (OS_NTASKS_CORE3 != 0)
OS_SECTION_PRAGMA(OS_taskDynamic_core3, .bss.core3.taskDynamic)
os_taskdynamic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.taskDynamic)
		OS_taskDynamic_core3[OS_NTASKS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.taskDynamic);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * Linked list scheduling algorithm.
 *
 * OS_taskActivations
 *
 * The links in the linked list of the task queue. Each slot contains the
 * index of the next slot in the queue. The corresponding (same index)
 * entry in OS_taskPtrs[] contains the address of the task that owns
 * the slot. There is always at least 1 entry in this array.
 * The first entry (index 0) is used to store the index of the current
 * activation of the currently running task or 0, if there is none.
 */
#include <memmap/Os_mm_const_begin.h>
#if ((OS_NTASKACTIVATIONS_CORE3 != 0) || (OS_N_CORES == 1))
const os_task_t * const OS_TASKPTRS_OBJ_CORE3[OS_NTASKACTIVATIONS_CORE3 + 1] = { OS_TASKACT_CORE3 };
#endif
#include <memmap/Os_mm_const_end.h>

#include <memmap/Os_mm_var_begin.h>
#if ((OS_NTASKACTIVATIONS_CORE3 != 0) || (OS_N_CORES == 1))
OS_SECTION_PRAGMA(OS_TASKACTIVATIONS_OBJ_CORE3, .bss.core3.taskActivations)
os_tasklink_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.taskActivations)
		OS_TASKACTIVATIONS_OBJ_CORE3[OS_NTASKACTIVATIONS_CORE3 + 1]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.taskActivations);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * Resources
*/
#include <memmap/Os_mm_var_begin.h>
#if (OS_NRESOURCES_CORE3 != 0)
OS_SECTION_PRAGMA(OS_resourceDynamic_core3, .bss.core3.resourceDynamic)
os_resourcedynamic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.resourceDynamic)
		OS_resourceDynamic_core3[OS_NRESOURCES_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.resourceDynamic);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * OS_isrAccounting_core3
 *
 * The accounting information for ISRs, one entry per ISR that needs it.
 * It's accessible via the pointer os_isr_t::accounting.
*/
#if (OS_NISRACCOUNTING != 0)
#include <memmap/Os_mm_var_begin.h>
#if (OS_NISRACCOUNTING_CORE3 != 0)
OS_SECTION_PRAGMA(OS_isrAccounting_core3, .bss.core3.isrAccounting)
os_israccounting_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.isrAccounting)
		OS_isrAccounting_core3[OS_NISRACCOUNTING_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.isrAccounting);
#endif
#include <memmap/Os_mm_var_end.h>
#endif /* OS_NISRACCOUNTING!=0 */

/*!
 * Interrupts
 */
#include <memmap/Os_mm_var_begin.h>
#if (OS_NINTERRUPTS_CORE3 != 0)
OS_SECTION_PRAGMA(OS_isrDynamic_core3, .bss.core3.isrDynamic)
os_isrdynamic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.isrDynamic)
		OS_isrDynamic_core3[OS_NINTERRUPTS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.isrDynamic);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * OS_rateIndex_core3
 * OS_rateTimer_core3
 *
 * The dynamic state of all rate-monitors. The index array (one per
 * rate-monitor) is the index into the rate-monitor's own ring buffer.
 * The timer array is the aggregated ring buffer array, COUNTLIMIT
 * entries per rate-monitor.
*/
#if (OS_NRATEMONS != 0)
#include <memmap/Os_mm_var_begin.h>
#if (OS_NRATEMONS_CORE3 != 0)
OS_SECTION_PRAGMA(OS_rateIndex_core3, .bss.core3.rateIndex)
os_rateindex_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.rateIndex)
		OS_rateIndex_core3[OS_NRATEMONS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.rateIndex);
#endif
#if (OS_NRATETIMERS_CORE3 != 0)
OS_SECTION_PRAGMA(OS_rateTimer_core3, .bss.core3.rateTimer)
os_timestamp_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.rateTimer)
		OS_rateTimer_core3[OS_NRATETIMERS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.rateTimer);
#endif
#include <memmap/Os_mm_var_end.h>
#endif /* OS_NRATEMONS != 0 */

/*!
 * OS_crosscoreMessageQueue_ptr
 *
 * Inter-core message queues.
 */
#if (OS_N_CORES > 1)
#include <memmap/Os_mm_var_begin.h>
OS_SECTION_PRAGMA(OS_messageQueue_core3, .bss.shared.core3.messageQueue)
os_messagequeue_t
		OS_SECTION_ATTRIB_PRE(.bss.shared.core3.messageQueue)
		OS_messageQueue_core3
		OS_BSS_SECTION_ATTRIB_POST(.bss.shared.core3.messageQueue);
#include <memmap/Os_mm_var_end.h>
#endif /* OS_N_CORES > 1 */

/*!
 * OS kernel data.
 *
 * OS kernel data local to each core. Hence, each core has its own instance,
 * which needs not to be synchronized with the ones of the other cores (if any).
 */
#include <memmap/Os_mm_var_begin.h>
OS_SECTION_PRAGMA(OS_KERNELDATA_OBJ_CORE3, .data.core3.kernelData)
os_kerneldata_t
		OS_SECTION_ATTRIB_PRE(.data.core3.kernelData)
		OS_KERNELDATA_OBJ_CORE3
		OS_DATA_SECTION_ATTRIB_POST(.data.core3.kernelData) = { OS_KERNELDATA_INIT_CORE3 };
#include <memmap/Os_mm_var_end.h>

#endif /* OS_KERNEL_TYPE != OS_MICROKERNEL */

/*!
 * Counters
*/
#include <memmap/Os_mm_var_begin.h>
#if (OS_NCOUNTERS_CORE3 != 0)
OS_SECTION_PRAGMA(OS_counterDynamic_core3, .bss.core3.counterDynamic)
os_counterdynamic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.counterDynamic)
		OS_counterDynamic_core3[OS_NCOUNTERS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.counterDynamic);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * Alarms
*/
#include <memmap/Os_mm_var_begin.h>
#if (OS_TOTALALARMS_CORE3 != 0)
OS_SECTION_PRAGMA(OS_alarmDynamic_core3, .bss.core3.alarmDynamic)
os_alarmdynamic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.alarmDynamic)
		OS_alarmDynamic_core3[OS_TOTALALARMS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.alarmDynamic);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * ScheduleTables
*/
#include <memmap/Os_mm_var_begin.h>
#if (OS_NSCHEDULES_CORE3 != 0)
OS_SECTION_PRAGMA(OS_scheduleDynamic_core3, .bss.core3.scheduleDynamic)
os_scheduledynamic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.scheduleDynamic)
		OS_scheduleDynamic_core3[OS_NSCHEDULES_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.scheduleDynamic);
#endif
#include <memmap/Os_mm_var_end.h>

/*!
 * HardwareTimers
 *
 * OS_hwtLastValue: An array of values associated timers had the last time they were updated.
*/
#if (OS_NHWTIMERS_CORE3 != 0)
#include <memmap/Os_mm_var_begin.h>
OS_SECTION_PRAGMA(OS_hwtLastValue_core3, .bss.core3.hwtLastValue)
os_timervalue_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.hwtLastValue)
		OS_hwtLastValue_core3[OS_NHWTIMERS_CORE3]
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.hwtLastValue);
#include <memmap/Os_mm_var_end.h>
#endif


/*!
 * counter-subsystem specific core-local variables.
*/
#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <memmap/Os_mm_var_begin.h>
OS_SECTION_PRAGMA(OS_panicCode_core3, .bss.core3.panicCode)
volatile os_panic_t
		OS_SECTION_ATTRIB_PRE(.bss.core3.panicCode)
		OS_panicCode_core3
		OS_BSS_SECTION_ATTRIB_POST(.bss.core3.panicCode);
#include <memmap/Os_mm_var_end.h>


#endif /* OS_KERNEL_TYPE == OS_MICROKERNEL */


#endif /* USED */
/* CHECK: PARSE */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
