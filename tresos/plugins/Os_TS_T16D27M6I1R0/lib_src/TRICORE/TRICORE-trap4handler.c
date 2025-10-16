/* TRICORE-trap4handler.c
 *
 * This file contains the OS_Trap4Handler function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-2) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to
 * object.
 *
 * Reason:
 * A pointer is read from hardware, which doesn't provide C language type
 * information. Hence, a type cast is required.
 *
 * MISRAC2012-3) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 * A value is read from hardware, which essentially represents a pointer.
 * The hardware, though, has no notion of C language types. Hence, the type
 * cast is required.
 */

#define OS_SID OS_SID_ArchTrapHandler
#define OS_SIF OS_svc_ArchTrapHandler

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_Trap4Handler()
 *
 * This function handles TRICORE class 4 traps.
 *
 * Class 4 traps occur when code attempts to access memory that
 * is physically not present.
 *
 * The trap is therefore handled as a non-fatal exception, which
 * causes termination/quarantine of the task that caused the error.
 *
 * WARNING: the asynchronous traps in this class are caused by attempted
 * writes, and don't get trapped until the write gets through the pipeline.
 * This means that the exception PC is nearly always wrong.
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Violation, 1
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.Peripherals.NontrustedApps, 2
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.CPU.ControlRegisters, 2
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.CPU.Exception, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_Trap4Handler(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uppercx_t *ucx;
	os_uint32_t pcxi;
	OS_PH_PARAMETERACCESS_DECL

	/* Ensure that the function call is complete before reading PCXI
	*/
	OS_DSYNC();

	pcxi = OS_MFCR(OS_PCXI);

	/* If either of the cx values turns out to be OS_NULL, we have a serious
	 * problem.
	*/
	/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
	ucx = (os_uppercx_t *)OS_AddrFromCx(pcxi);

	/* The OS_TrapEntry routine places important information
	 * into the upper context, like the old value of the inKernel flag.
	 * The trap identification number is also there.
	 * The exception PC (return address for the trap handler) is in
	 * the lower context that is the next in the list.
	*/
	/* Deviation MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
	OS_PH_SAVE_PARAMETER_N(0, OS_GetTrapPCFromUpperCx(ucx));
	OS_PH_SAVE_PARAMETER_N(1, 4);
	OS_PH_SAVE_PARAMETER_N(2, ucx->d15);

	switch ( ucx->d15 )
	{
	case 1:		/* Program fetch bus error */
	case 2:		/* Data access bus error */
	case 3:		/* Data access bus error */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_MemoryProtection, OS_PH_GET_PARAMETER_VAR());
		break;
	case 4:		/* Coprocessor trap asynchronous error */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_NonfatalException, OS_PH_GET_PARAMETER_VAR());
		break;

	case 5:		/*  Program memory integrity error */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
		break;

	case 6:		/* Data memory integrity error */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
		break;

	default:	/* Unknown - not reachable? */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
		break;
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_trap4handler_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
