/* TRICORE-initmodule.c
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.2 (required)
 * There shall be no dead code.
 *
 * Reason:
 * This code is required by the hardware protocol.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <TRICORE/Os_TRICORE_core.h>
#include <Os_tool.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_InitModule()
 *
 * Initialises a Tricore peripheral module
 *
 * Many Tricore peripherals need initialising before they can be
 * used. Failure to do so results in an exception trap when the
 * module registers are accessed.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitModule
(	os_tricoremodule_t *m,
	os_uint32_t divider,
	os_uint32_t switchoff)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t p = 0;
	os_uint32_t clc;

	/* We must set ENDINIT while fiddling with the clock-control
	 * register.
	*/
	OS_ClearEndinit(p);	/* It's a macro! */

	/* Write the divider value to the clock control register. Set the
	 * clock switchoff bit if required (also needs the SBWE bit). Ensure
	 * all other "disable" bits are 0.
	*/
	clc = OS_CLC_RMCval(divider) & OS_CLC_RMC;

	if ( switchoff != 0u )
	{
		clc |= (OS_CLC_SBWE | OS_CLC_SPEN);
	}

	m->clc = clc;


	/* Flush the pipeline by reading the register back.
	 *
	 * This expression should read the location It should not
	 * result in "expression has no effect" or similar warning/error
	 * because the register is volatile.
	*/
	/* Deviation MISRAC2012-1 <+1> */
	m->clc;

	OS_SetEndinit(p);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_initmodule_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
