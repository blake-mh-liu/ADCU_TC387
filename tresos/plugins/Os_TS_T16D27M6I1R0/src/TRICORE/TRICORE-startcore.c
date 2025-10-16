/* TRICORE-startcore.c
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: Dir 4.6 (advisory)
 * Typedefs that indicate size and signedness should be used in place of the
 * basic numerical types.
 *
 * Reason:
 * main shall be defined with a return type of int.
 *
 * MISRAC2012-2) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and any
 * other type.
 *
 * Reason:
 * The pointer is passed to hardware, which is only interested in its value
 * and not in its type.
 *
 * MISRAC2012-3) Deviated Rule: 8.5 (required)
 * An external object or function shall be declared once in one and only one file.
 *
 * Reason:
 * This is the only place within AutoCoreOS, where main is declared.
 * It may be declared in the application or board files as well,
 * but since these are not part of the OS, this can be considered as a false positive.
 */

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES_MAX != 1))

#include <Os_tool.h>
#include <TRICORE/Os_TRICORE_core.h>
#include <Os_configuration.h>

#include <memmap/Os_mm_code_begin.h>

#if (OS_TRICOREARCH == OS_TRICOREARCH_16EP)

#define OS_BOOTREG		OS_DBGSR
#define OS_BOOTMASK		OS_DBGSR_HALT_MASK
#define OS_BOOTHALTED	OS_DBGSR_HALT_HALTED
#define OS_BOOTRELEASE	(OS_DBGSR_HALT_WE | OS_DBGSR_HALT_RUNNING | OS_DBGSR_DE_ENABLE)

#elif (OS_TRICOREARCH == OS_TRICOREARCH_162)

#define OS_BOOTREG		OS_SYSCON
#define OS_BOOTMASK		OS_SYSCON_BHALT
#define OS_BOOTHALTED	OS_SYSCON_BHALT
#define OS_BOOTRELEASE	0u

#elif (OS_TRICOREARCH == OS_TRICOREARCH_18)

#define OS_BOOTREG		OS_BOOTCON
#define OS_BOOTMASK		OS_BOOTCON_BHALT
#define OS_BOOTHALTED	OS_BOOTCON_BHALT
#define OS_BOOTRELEASE	0u

#else /* OS_TRICOREARCH */
#error "Unexpected TRICORE architecture in OS_TRICOREARCH"
#endif /* OS_TRICOREARCH */

/* Deviation MISRAC2012-1, MISRAC2012-3 */
extern int main(void);
extern void OS_CoreStartupEntry(void);


#if (OS_TRICOREARCH==OS_TRICOREARCH_18)
/** OS_KickStartCoreAurixTC18
 *
 *  Sets up core registers and transfers control to main().
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_KickStartCoreAurixTC18(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kdata = OS_GetKernelData();

	/* Initialise PCXI so that the context list has an end.
	*/
	OS_MTCR(OS_PCXI, 0);

	/* Initialise the registers that point to the trap and interrupt
	 * tables and the interrupt stack pointer.
	 */

	/* The TC49XXVDK simulator seems not to require modification of the PROT registers.
	 * This may be required on real hardware.
	*/
	/* Deviation MISRAC2012-2 <+1> */
	OS_MTCR(OS_BTV, (os_uint32_t)&OS_startupTrapTable);
	OS_MTCR(OS_BIV, 0);
	OS_MTCR(OS_ISP, ((os_uint32_t)(kdata->iSpInitial)));

	/* now call main() - this should never return */
	(void)main();

	/* even if main() returns, this function may not */
	OS_ENDLESSLOOP();
}
#else

/** OS_KickStartCore
 *
 *  Sets up ENDINIT-protected core registers and transfers control to main().
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_KickStartCore(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kdata = OS_GetKernelData();

	/*  Initialise PCXI so that the context list has an end.
	*/
	OS_MTCR(OS_PCXI, 0);

	/* Initialise the registers that point to the trap and interrupt
	 * tables and the interrupt stack pointer. */

	OS_WriteEndinit(0);
	/* Deviation MISRAC2012-2 <+1> */
	OS_MTCR(OS_BTV, (os_uint32_t)&OS_startupTrapTable);
	OS_MTCR(OS_BIV, 0);
	OS_MTCR(OS_ISP, ((os_uint32_t)(kdata->iSpInitial)));
	OS_WriteEndinit(1);
	/* now call main() - this should never return */
	(void)main();

	/* even if main() returns, this function may not */
	OS_ENDLESSLOOP();
}
#endif

/* OS_TricoreStartCore()
 *
 * Initialises another core on a TRICORE multicore system.
 *
 * This is done in multiple steps:
 *
*/

OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_TricoreStartCore(os_coreid_t core)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t cfsrBase = OS_CPUCSFR(core);
	os_uint32_t bootreg;

	/* check if core is really halted; core is only set up if it is not running */
	bootreg = OS_MFCCR(cfsrBase, (os_uint32_t)OS_BOOTREG);
	if ( (bootreg & OS_BOOTMASK) == OS_BOOTHALTED )
	{

		/* Core startup procedure is architecture dependent */
#if (OS_TRICOREARCH==OS_TRICOREARCH_18)
		/* OS_CoreStartupEntry should set A10, PSW and A8. */
		/* Deviation MISRAC2012-2 <+2> */
		OS_MTCCR(cfsrBase, (os_uint32_t)OS_PC, (os_uint32_t)&OS_CoreStartupEntry);
#else
		/* Initialise the stack pointer to interrupt stack */
		OS_MTCCR(cfsrBase, (os_uint32_t)OS_A10, ((os_uint32_t)(OS_kernel_ptr[core]->iSpInitial)));

		/* Set PSW and tell the CPU that we're running on the interrupt stack.
		*/
		OS_MTCCR(cfsrBase, (os_uint32_t)OS_PSW, OS_INITIAL_PSW | OS_PSW_IS);

		/* initialize global address register to kernel data struct */
		OS_MTCCR(cfsrBase, (os_uint32_t)OS_A8, (os_uint32_t)OS_kernel_ptr[core]);

		/* Endinit-protected stuff has to be handled on the target core itself */
		/* The core starts its execution in OS_InitCsaList, which exits through a simple
		 * jump to A11, resuming in OS_KickStartCore
		 */
		/* Deviation MISRAC2012-2 <+2> */
		OS_MTCCR(cfsrBase, (os_uint32_t)OS_PC, (os_uint32_t)&OS_InitCsaList);
		OS_MTCCR(cfsrBase, (os_uint32_t)OS_A11, (os_uint32_t)&OS_KickStartCore);
#endif

		/* Reset Halt */
		bootreg = (bootreg & (~((os_uint32_t)OS_BOOTMASK))) | OS_BOOTRELEASE;
		OS_MTCCR(cfsrBase, (os_uint32_t)OS_BOOTREG, bootreg);
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES_MAX != 1))) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_startcore_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES_MAX != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
