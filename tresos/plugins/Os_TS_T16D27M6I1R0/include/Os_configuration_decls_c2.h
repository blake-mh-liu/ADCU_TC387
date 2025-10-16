/* Os_configuration_c2_defaults.h
 *
 * This file provides configuration dependent declarations
 * and macro definitions for core C2.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#ifndef OS_CONFIGURATION_DECLS_C2_H
#define OS_CONFIGURATION_DECLS_C2_H

#include <Os_configuration_decls.h>

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)
#include <Os_panic.h>
#endif /* OS_KERNEL_TYPE == OS_MICROKERNEL */

/* If no core properties are defined, we assume, that this core isn't used.
*/
#ifndef OS_PROPERTIES_CORE2
#define OS_PROPERTIES_CORE2 OS_U(0)
#endif


/* Define default values in case this core is not active.
*/
#if ((OS_PROPERTIES_CORE2 & OS_COREPROP_USED_BIT) != OS_COREPROP_USED_BIT)

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#ifndef OS_NAPPS_CORE2
#define OS_NAPPS_CORE2 OS_U(0)
#endif

#ifndef OS_NTASKACCOUNTING_CORE2
#define OS_NTASKACCOUNTING_CORE2 OS_U(0)
#endif

#ifndef OS_NTASKS_CORE2
#define OS_NTASKS_CORE2 OS_U(0)
#endif

#ifndef OS_NPRIORITIES_CORE2
#define OS_NPRIORITIES_CORE2 OS_U(0)
#endif

#ifndef OS_NPRIORITYQUEUEDYNAMICS_CORE2
#define OS_NPRIORITYQUEUEDYNAMICS_CORE2 OS_U(0)
#endif

#ifndef OS_NPRIORITYSLOTS_CORE2
#define OS_NPRIORITYSLOTS_CORE2 OS_U(0)
#endif

#ifndef OS_NTASKACTIVATIONS_CORE2
#define OS_NTASKACTIVATIONS_CORE2 OS_U(0)
#endif

#ifndef OS_NRESOURCES_CORE2
#define OS_NRESOURCES_CORE2 OS_U(0)
#endif

#ifndef OS_NISRACCOUNTING_CORE2
#define OS_NISRACCOUNTING_CORE2 OS_U(0)
#endif

#ifndef OS_NINTERRUPTS_CORE2
#define OS_NINTERRUPTS_CORE2 OS_U(0)
#endif

#ifndef OS_NRATEMONS_CORE2
#define OS_NRATEMONS_CORE2 OS_U(0)
#endif

#ifndef OS_NRATETIMERS_CORE2
#define OS_NRATETIMERS_CORE2 OS_U(0)
#endif

#endif /* OS_KERNEL_TYPE != OS_MICROKERNEL */

#ifndef OS_NCOUNTERS_CORE2
#define OS_NCOUNTERS_CORE2 OS_U(0)
#endif

#ifndef OS_NALARMS_CORE2
#define OS_NALARMS_CORE2 OS_U(0)
#endif

#ifndef OS_NSCHEDULES_CORE2
#define OS_NSCHEDULES_CORE2 OS_U(0)
#endif

#ifndef OS_NHWTIMERS_CORE2
#define OS_NHWTIMERS_CORE2 OS_U(0)
#endif

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)
#define OS_CTRSUB_PANICCODE_PTR_CORE2 OS_NULL
#endif /* OS_KERNEL_TYPE == OS_MICROKERNEL */

#endif /* not USED */


/* Deduced configuration constants.
*/

#if (2 == OS_SHAREDHWCOUNTERTIMESTAMP_COREID)
#define OS_NSHAREDHWCOUNTERTIMESTAMP_CORE2 1
#else
#define OS_NSHAREDHWCOUNTERTIMESTAMP_CORE2 0
#endif

#define OS_TOTALALARMS_CORE2 (OS_NALARMS_CORE2 + OS_NSCHEDULES_CORE2 + OS_NSHAREDHWCOUNTERTIMESTAMP_CORE2)

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#define OS_MAXPRIO_CORE2 ((OS_NPRIORITIES_CORE2 == 0) ? 0 : (OS_NPRIORITIES_CORE2 - 1))

#if (OS_NTASKS == 0)
#define OS_TASKACT_CORE2		OS_NULL
#else /* OS_NTASKS != 0 */
#define OS_TASKACT_CORE2		OS_NULL,OS_TASKACTIVATIONS_CORE2
#endif /* OS_NTASKS == 0 */

#endif /* OS_KERNEL_TYPE != OS_MICROKERNEL */


/* Choose symbols for single-core optimization.
*/
#if ((OS_N_CORES == 1) && (2 == OS_INITCORE))
#define OS_KERNELDATA_OBJ_CORE2			OS_kernelData
#define OS_TASKPTRS_OBJ_CORE2			OS_taskPtrs
#define OS_TASKACTIVATIONS_OBJ_CORE2	OS_taskActivations
#define OS_PRIORITYQUEUE_OBJ_CORE2		OS_priorityQueue
#define OS_PRIORITYSLOT_OBJ_CORE2		OS_prioritySlot
#define OS_SLAVEPRIOWORD_OBJ_CORE2		OS_slavePrioWord
#else
#define OS_KERNELDATA_OBJ_CORE2			OS_kernelData_core2
#define OS_TASKPTRS_OBJ_CORE2			OS_taskPtrs_core2
#define OS_TASKACTIVATIONS_OBJ_CORE2	OS_taskActivations_core2
#define OS_PRIORITYQUEUE_OBJ_CORE2		OS_priorityQueue_core2
#define OS_PRIORITYSLOT_OBJ_CORE2		OS_prioritySlot_core2
#define OS_SLAVEPRIOWORD_OBJ_CORE2		OS_slavePrioWord_core2
#endif


/* Declare core local symbols.
*/
#ifndef OS_ASM
#if ((OS_PROPERTIES_CORE2 & OS_COREPROP_USED_BIT) != OS_COREPROP_USED_BIT)

extern os_uint8_t OS_unused_configuration_c2;
#define OS_SLAVEWORDPTR_CORE2			OS_NULL
#define OS_PRIOSLOTPTR_CORE2			OS_NULL
#define OS_PRIOTITYQUEUEPTR_CORE2		OS_NULL
#define OS_PTASKPTRS_CORE2				OS_NULL
#define OS_TASKACTIVATIONSPTR_CORE2		OS_NULL
#define OS_MESSAGEQUEUEPTR_CORE2		OS_NULL
#define OS_KERNELDATAPTR_CORE2			OS_NULL

#else /* USED */

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#if (OS_NAPPS_CORE2 != 0)
extern os_appdynamic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.appDynamic)
		OS_appDynamic_core2[OS_NAPPS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.appDynamic);
#endif
#if (OS_NTASKACCOUNTING_CORE2 != 0)
extern os_taskaccounting_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.taskAccounting)
		OS_taskAccounting_core2[OS_NTASKACCOUNTING_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.taskAccounting);
#endif
#if (OS_NTASKS_CORE2 != 0)
extern os_taskdynamic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.taskDynamic)
		OS_taskDynamic_core2[OS_NTASKS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.taskDynamic);
#endif

#if (OS_NTASKACTIVATIONS_CORE2 == 0)
#define OS_PTASKPTRS_CORE2 OS_NULL
#else
#if (OS_N_CORES != 1)
extern const os_task_t * const OS_taskPtrs_core2[OS_NTASKACTIVATIONS_CORE2 + 1];
#endif
#define OS_PTASKPTRS_CORE2 (&OS_TASKPTRS_OBJ_CORE2[0])
#endif
#if (OS_NTASKACTIVATIONS_CORE2 == 0)
#define OS_TASKACTIVATIONSPTR_CORE2 OS_NULL
#else
#if (OS_N_CORES != 1)
extern os_tasklink_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.taskActivations)
		OS_taskActivations_core2[OS_NTASKACTIVATIONS_CORE2 + 1]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.taskActivations);
#endif
#define OS_TASKACTIVATIONSPTR_CORE2 (&OS_TASKACTIVATIONS_OBJ_CORE2[0])
#endif

#if (OS_NRESOURCES_CORE2 != 0)
extern os_resourcedynamic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.resourceDynamic)
		OS_resourceDynamic_core2[OS_NRESOURCES_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.resourceDynamic);
#endif
#if (OS_NISRACCOUNTING != 0)
#if (OS_NISRACCOUNTING_CORE2 != 0)
extern os_israccounting_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.isrAccounting)
		OS_isrAccounting_core2[OS_NISRACCOUNTING_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.isrAccounting);
#endif
#endif /* OS_NISRACCOUNTING!=0 */
#if (OS_NINTERRUPTS_CORE2 != 0)
extern os_isrdynamic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.isrDynamic)
		OS_isrDynamic_core2[OS_NINTERRUPTS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.isrDynamic);
#endif

#if (OS_NRATEMONS != 0)
#if (OS_NRATEMONS_CORE2 != 0)
extern os_rateindex_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.rateIndex)
		OS_rateIndex_core2[OS_NRATEMONS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.rateIndex);
#endif
#if (OS_NRATETIMERS_CORE2 != 0)
extern os_timestamp_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.rateTimer)
		OS_rateTimer_core2[OS_NRATETIMERS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.rateTimer);
#endif
#endif /* OS_NRATEMONS != 0 */

#if (OS_N_CORES > 1)
extern os_messagequeue_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.shared.core2.messageQueue)
		OS_messageQueue_core2
		OS_SECTION_ATTRIB_POST_DECL(.bss.shared.core2.messageQueue);
#define OS_MESSAGEQUEUEPTR_CORE2 (&OS_messageQueue_core2)
#endif

#if (OS_N_CORES != 1)
extern os_kerneldata_t
		OS_SECTION_ATTRIB_PRE_DECL(.data.core2.kernelData)
		OS_kernelData_core2
		OS_SECTION_ATTRIB_POST_DECL(.data.core2.kernelData);
#endif
#define OS_KERNELDATAPTR_CORE2 (&OS_KERNELDATA_OBJ_CORE2)

#endif /* OS_KERNEL_TYPE != OS_MICROKERNEL */

#if (OS_NCOUNTERS_CORE2 != 0)
extern os_counterdynamic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.counterDynamic)
		OS_counterDynamic_core2[OS_NCOUNTERS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.counterDynamic);
#endif
#if (OS_TOTALALARMS_CORE2 != 0)
extern os_alarmdynamic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.alarmDynamic)
		OS_alarmDynamic_core2[OS_TOTALALARMS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.alarmDynamic);
#endif
#if (OS_NSCHEDULES_CORE2 != 0)
extern os_scheduledynamic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.scheduleDynamic)
		OS_scheduleDynamic_core2[OS_NSCHEDULES_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.scheduleDynamic);
#endif
#if (OS_NHWTIMERS_CORE2 != 0)
extern os_timervalue_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.hwtLastValue)
		OS_hwtLastValue_core2[OS_NHWTIMERS_CORE2]
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.hwtLastValue);
#endif

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)
extern volatile os_panic_t
		OS_SECTION_ATTRIB_PRE_DECL(.bss.core2.panicCode)
		OS_panicCode_core2
		OS_SECTION_ATTRIB_POST_DECL(.bss.core2.panicCode);
#define OS_CTRSUB_PANICCODE_PTR_CORE2 (&OS_panicCode_core2)
#endif /* OS_KERNEL_TYPE == OS_MICROKERNEL */

#endif /* USED */
#endif /* ASM */

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
