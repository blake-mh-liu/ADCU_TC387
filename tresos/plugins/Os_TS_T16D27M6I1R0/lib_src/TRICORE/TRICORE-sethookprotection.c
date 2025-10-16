/* TRICORE-sethookprotection.c
 *
 * This file contains the OS_SetHookProtection function for TRICORE.
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
 * DPR1 - used for task/ISR data/bss segment, therefore not used here.
 * DPR2 - used for task/ISR stack segment, therefore READ/WRITE.
 * DPR3 - used for constant segment in ROM, therefore READONLY.
 * DPR4 - used for constant segment in RAM, therefore READONLY.
 *
 * The CPRM value is configurable to permit debugging of protected applications.
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Application.Data.Owner, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Application.Data.Read, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Application.Data.Write, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Data.WriteSameApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Data.WriteOtherApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Stack.WriteSameApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.TaskISR.Stack.WriteOtherApp, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Kernel.DataStack.Write, 2
*/
#define DPR0_ACCESS  (OS_DPM_RE0 | OS_DPM_WE0)
#define DPR1_ACCESS  (OS_DPM_RE1)
#define DPR2_ACCESS  (OS_DPM_RE2 | OS_DPM_WE2)
#define DPR3_ACCESS  (OS_DPM_RE3)
#define DPR4_ACCESS  (OS_DPM_RE4)

#define DPRM_VALUE   (DPR0_ACCESS|DPR1_ACCESS|DPR2_ACCESS|DPR3_ACCESS|DPR4_ACCESS)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_SetHookProtection
 *
 * This function loads the protection parameters for the given hook
 * into the memory protection unit.
 *
 * Protection register set 1 is used for hooks of non-privileged
 * applications. The code protection registers are initialized
 * by default.
 *
 * For TC2*: The data protection registers are initialized as follows:
 *
 * DPR0: application data (read/write)
 * DPR1: not used
 * DPR2: stack (read/write)
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection, 1
 *
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_SetHookProtection
(	const os_appcontext_t *app,
	os_sethookprot_arg2t ctxt,
	os_size_t stackLen
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* If the application is a privileged application, it will be running
	 * in protection register set 0. If this is the case, there's no need
	 * to load PRS1
	*/
	if ( !OS_AppIsTrusted(app) )
	{
		/* Program protection ranges 0 to 2
		*/

		OS_MTCR(OS_DPR0_L, (os_uint32_t)app->dataStart);
		OS_MTCR(OS_DPR0_U, (os_uint32_t)app->dataEnd);

		OS_MTCR(OS_DPR1_L, 0u);
		OS_MTCR(OS_DPR1_U, 0u);

		OS_MTCR(OS_DPR2_L, (os_uint32_t)ctxt->stackLimit - stackLen);
		OS_MTCR(OS_DPR2_U, (os_uint32_t)ctxt->stackLimit);
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_sethookprotection_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
