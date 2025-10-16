/* TRICORE-intirconfigdriver.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
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
 * This code is required by the hardware protocol. The intent is to
 * synchronize with the interrupt controller.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/* inline functions dealing with ISRs */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_SetupIsrImpl(os_reg32_t *srnsrc, os_uint32_t value)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	*srnsrc = value;
	/* Deviation MISRAC2012-1 <+1> */
	*srnsrc;
}

OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_EnableIsrImpl(os_reg32_t *srnsrc)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	*srnsrc |= OS_SRN_SRE;
	/* Deviation MISRAC2012-1 <+1> */
	*srnsrc;
}

OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_DisableIsrImpl(os_reg32_t *srnsrc)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	*srnsrc &= (os_uint32_t) ~((os_uint32_t)OS_SRN_SRE);
	/* Deviation MISRAC2012-1 <+1> */
	*srnsrc;
}

OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ClearIsrImpl(os_reg32_t *srnsrc)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	*srnsrc |= OS_SRN_CLRR;
	/* Deviation MISRAC2012-1 <+1> */
	*srnsrc;
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
