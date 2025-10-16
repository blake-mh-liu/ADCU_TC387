/* TRICORE-initarchtricore.c
 *
 * This file contains the OS_InitArchTricore function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and any
 * other type.
 *
 * Reason:
 * The pointer is passed to hardware, which is only interested in its value
 * and not in its type.
 */

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_InitArchTricore()
 *
 * This function performs the parts of the hardware initialization that
 * are architecture-specific, OS-related and independent of the
 * board package.
 *
 * For Tricore the following hardware needs to be initialised:
 *
 * PSW (processor status word)
 * Stack pointer
 * Context save areas
 * PLL (phase-locked loop - sets CPU frequency
 * Timers (including prescalers)
 * PCXI (zero)
 * BTV (trap vector base)
 * BIV (interrupt vector base)
 * ISP (interrupt stack pointer)
 * RAM (global data and bss sections)
 * ICR (interrupt level (disabled))
 *
 * With the exception of BTV and BIV, these must all be set to working
 * values before calling StartOS, otherwise StartOS cannot be called.
 * So we program the two vector base registers here.
 *
 * This also permits the startup code to use a different trap table
 * from the normal OS. AutosarOS 1.5 requires that, should a processor
 * exception occur before StartOS, the handler enters an endless loop.
 * This can be implemented easily by building a special startup trap
 * table and using this during startup. The system call entry in this
 * table must naturally still jump to the system-call handler, otherwise
 * StartOS cannot be called.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitArchTricore(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* By the time we get here we are running with all known
	 * interrupts disabled (i.e. at the "lock all" level) but
	 * the global interrupt enable bit is set (enabled).
	 * We leave the level intact but set the disable bit.
	 * Then, after the vector registers are programmed we
	 * simply ENABLE.
	*/
	OS_DISABLE();

#if (OS_TRICOREARCH!=OS_TRICOREARCH_18)
	OS_WriteEndinit(0);
#endif

	/* Deviation MISRAC2012-1 <+2> */
	OS_MTCR(OS_BTV, (os_uint32_t)&OS_trapTable);
	OS_MTCR(OS_BIV, (os_uint32_t)&OS_interruptTable);

#if (OS_TRICOREARCH!=OS_TRICOREARCH_18)
	OS_WriteEndinit(1);
#endif

	OS_ENABLE();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_initarchtricore_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
