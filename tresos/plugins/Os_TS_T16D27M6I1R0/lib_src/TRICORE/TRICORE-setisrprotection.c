/* TRICORE-setisrprotection.c
 *
 * This file contains the OS_SetIsrProtection function for TRICORE.
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection, 1
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/*!
 * DPRn_ACCESS
 *
 * These macros define the access modes for data protection registers
 *
 * DPR0 - used for application data/bss segment, therefore READ/WRITE.
 * DPR1 - used for task/ISR data/bss segment, therefore READ/WRITE.
 * DPR2 - used for task/ISR stack segment, therefore READ/WRITE.
 * DPR3 - used for constant segment in ROM, therefore READONLY.
 * DPR4 - used for constant segment in RAM, therefore READONLY.
 *
 * The CPRM value is configurable to permit debugging of protected applications.
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Application.Data.Owner, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Application.Data.Read, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Application.Data.Write, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Data.Owner, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Data.WriteSameApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Data.WriteOtherApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Stack.Owner, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Stack.WriteSameApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Stack.WriteOtherApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Kernel.DataStack.Write, 2
*/
#define DPR0_ACCESS  (OS_DPM_RE0 | OS_DPM_WE0)
#define DPR1_ACCESS  (OS_DPM_RE1 | OS_DPM_WE1)
#define DPR2_ACCESS  (OS_DPM_RE2 | OS_DPM_WE2)
#define DPR3_ACCESS  (OS_DPM_RE3)
#define DPR4_ACCESS  (OS_DPM_RE4)

#define DPRM_VALUE   (DPR0_ACCESS|DPR1_ACCESS|DPR2_ACCESS|DPR3_ACCESS|DPR4_ACCESS)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_SetIsrProtection
 *
 * This function loads the protection parameters for the given ISR
 * into the memory protection unit.
 *
 * Protection register set 1 is used for ISRs of non-privileged
 * applications. The code protection registers are initialized
 * by default.
 *
 * For TC2*: The data protection registers are initialized as follows:
 *
 * DPR0: application data (read/write)
 * DPR1: task/isr private data (read/write)
 * DPR2: stack (read/write)
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_SetIsrProtection(const os_isr_t *isr, os_isrdynamic_t *id)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_appcontext_t *a = OS_GET_APP(isr->app);

	/* If the application is a privileged application, it will be running
	 * in protection register set 0. If this is the case, there's no need
	 * to load PRS1
	*/
	if ( !OS_AppIsTrusted(a) )
	{
		/* Program protection ranges 0 to 2
		 */

		OS_MTCR(OS_DPR0_L, (os_uint32_t)a->dataStart);
		OS_MTCR(OS_DPR0_U, (os_uint32_t)a->dataEnd);

		OS_MTCR(OS_DPR1_L, (os_uint32_t)isr->dataStart);
		OS_MTCR(OS_DPR1_U, (os_uint32_t)isr->dataEnd);

		OS_MTCR(OS_DPR2_L, (os_uint32_t)id->c.stackLimit - isr->stackLen);
		OS_MTCR(OS_DPR2_U, (os_uint32_t)id->c.stackLimit);
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_setisrprotection_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
