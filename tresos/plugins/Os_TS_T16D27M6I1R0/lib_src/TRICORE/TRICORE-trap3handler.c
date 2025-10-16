/* TRICORE-trap3handler.c
 *
 * This file contains the OS_Trap3Handler function.
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
 * OS_Trap3Handler()
 *
 * This function handles TRICORE class 3 traps.
 *
 * Class 3 traps are all to do with context management or call depth
 * counting. The action taken depends on the trap identification
 * number:
 *
 *  1: (FCX == LCX)           --- Fatal exception
 *  2: (Call depth overflow)  --- Nonfatal exception
 *  3: (Call depth underflow) --- Nonfatal exception
 *  4: (FCX == 0)             --- Fatal exception (but won't get here!)
 *  5: (PCX == 0)             --- Special (see below), or fatal exception
 *  6: (PCXI.UL wrong)        --- Non-fatal exception
 *  7: (CDC != 0 on RFE)      --- Non-fatal exception
 *
 * Exception 5 (PCX == 0) is used to detect when user code returns from the lowest call level of a protectable
 * context. If the context is a task, the OS's error handling routine for "return-from-task" is called.
 * If the context is an ISR or an application-hook function, it is processed as a return-to-kernel from this
 * context and, provided a return is possible, no error is reported. Any other cases are reported as a fatal
 * exception.
 *
 * !LINKSTO Kernel.Autosar.Protection.HardwareProtection.CPU.Exception, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_Trap3Handler(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uppercx_t *ucx;
	os_uint32_t pcxi;
	os_isrdynamic_t *id;
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
	OS_PH_SAVE_PARAMETER_N(1, 3);
	OS_PH_SAVE_PARAMETER_N(2, ucx->d15);

	switch ( ucx->d15 )
	{
	case 1:		/* Free context list depleted (FCX==LCX) */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
		break;

	case 2:		/* Call depth overflow */
	case 3:		/* Call depth underflow */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_NonfatalException, OS_PH_GET_PARAMETER_VAR());
		break;

	case 4:		/* Free context list underflow (FCX==0) - not reachable! */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
		break;

	case 5:		/* PCXI == 0 exception - used for returng from tasks etc. */
		{
		os_kerneldata_t * const kernel_data = OS_GetKernelData();
		const os_uint8_t inFunction= kernel_data->inFunction;
		if ( inFunction == OS_INTASK )
		{
			/* If this is caused by a task, it means that the task has returned
			 * from its main function. The Autosar specification defines what
			 * happens here, so we call the arch-independent function that
			 * does the job. When it returns, we drop back out through the
			 * dispatcher as normal.
			*/
			OS_KernTaskReturn();
		}
		else
		if ( inFunction == OS_INCAT2 )
		{
			const os_isrid_t isrCurrent = kernel_data->isrCurrent;

			/* If this is caused by a Cat2 ISR, it means that the
			 * ISR has returned, and we need to get back to the point of call.
			 * So we need to discard the context list that got us here, and
			 * restore the pcxi value and RA that were saved when the ISR was
			 * called.
			 * Then the return from this function will return from the ISR
			 * wrapper.
			*/
			id = OS_isrTableBase[isrCurrent].dynamic;

			if ( (isrCurrent >= OS_nInterrupts) || (id->c.pcxi == 0u) )
			{
				/* Something wrong; treat as error */
				/* can't propagate the return value of OS_ERROR -> ignore it */
				(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
			}
			else
			{
				/* Caused by return from a Cat2 interrupt. We need to discard
				 * the CSAs that we collected on the way here, then "return"
				 * to the place in the interrupt entry function where the
				 * ISR was "called" from. The register values from that context
				 * are in the first CSA of the reloaded list.
				 * We have to frig the current PSW to make the RFE possible.
				 * An alternative, reprogramming the ICR, would take longer.
				*/
				OS_FreeCxList(pcxi);
				OS_MTCR(OS_PCXI, id->c.pcxi);
				/* Deviation MISRAC2012-3 <+1> */
				OS_MTRA((void *)(id->c.ra));
				OS_MTCR(OS_PSW, OS_PSW_CDC_6|OS_PSW_CDE|OS_PSW_GW|OS_PSW_IS|OS_PSW_IO_SU|OS_PSW_PRS_0);
				OS_RFE();
			}
		}
		else
		if ( inFunction == OS_INERRORHOOK )
		{
			if ( kernel_data->eHookContext.c.pcxi == 0u )
			{
				/* Something wrong; treat as error */
				/* can't propagate the return value of OS_ERROR -> ignore it */
				(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
			}
			else
			{
				/* Caused by return from an (application-specific)
				 * startup or shutdown hook. We need to discard
				 * the CSAs that we collected on the way here, then "return"
				 * to the place in the startup function where the
				 * hook was "called" from. The register values from that
				 * context are in the first CSA of the reloaded list.
				 * We have to frig the current PSW to make the RFE possible.
				 * An alternative, reprogramming the ICR, would take longer.
				*/
				OS_FreeCxList(pcxi);
				OS_MTCR(OS_PCXI, kernel_data->eHookContext.c.pcxi);
				/* Deviation MISRAC2012-3 <+1> */
				OS_MTRA((void *)(kernel_data->eHookContext.c.ra));
				OS_MTCR(OS_PSW, OS_PSW_CDC_6|OS_PSW_CDE|OS_PSW_GW|OS_PSW_IS|OS_PSW_IO_SU|OS_PSW_PRS_0);
				OS_RFE();
			}
		}
		else
		if ( (inFunction == OS_INSTARTUPHOOK) || (inFunction == OS_INSHUTDOWNHOOK) )
		{
			if ( kernel_data->sHookContext.c.pcxi == 0u )
			{
				/* Something wrong; treat as error */
				/* can't propagate the return value of OS_ERROR -> ignore it */
				(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
			}
			else
			{
				/* Caused by return from an (application-specific)
				 * startup or shutdown hook. We need to discard
				 * the CSAs that we collected on the way here, then "return"
				 * to the place in the startup function where the
				 * hook was "called" from. The register values from that
				 * context are in the first CSA of the reloaded list.
				 * We have to frig the current PSW to make the RFE possible.
				 * An alternative, reprogramming the ICR, would take longer.
				*/
				OS_FreeCxList(pcxi);
				OS_MTCR(OS_PCXI, kernel_data->sHookContext.c.pcxi);
				/* Deviation MISRAC2012-3 <+1> */
				OS_MTRA((void *)(kernel_data->sHookContext.c.ra));
				OS_MTCR(OS_PSW, OS_PSW_CDC_6|OS_PSW_CDE|OS_PSW_GW|OS_PSW_IS|OS_PSW_IO_SU|OS_PSW_PRS_0);
				OS_RFE();
			}
		}
		else
		{
			/* can't propagate the return value of OS_ERROR -> ignore it */
			(void) OS_ERROR(OS_ERROR_FatalException, OS_PH_GET_PARAMETER_VAR());
		}
		break;
		}
	case 6:		/* Context type error: PCXI.UL wrong */
	case 7:		/* Nesting error: RFE with CDC != 0 */
		/* can't propagate the return value of OS_ERROR -> ignore it */
		(void) OS_ERROR(OS_ERROR_NonfatalException, OS_PH_GET_PARAMETER_VAR());
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
const os_uint8_t OS_dummy_TRICORE_trap3handler_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
