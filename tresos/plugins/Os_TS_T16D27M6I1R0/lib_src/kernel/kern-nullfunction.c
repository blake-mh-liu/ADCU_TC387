/* kern-nullfunction.c
 *
 * This file contains the OS_NullFunction function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_VOCF]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  The intentionally empty function OS_NullFunction is used as a placeholder function.
 *  For empty function the VOCF metric is defined as 0.
*/

#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_NullFunction
 *
 * This function does nothing. It is used wherever a dummy function call
 * is required, in particular for OS_NULL entries in the initialisation
 * functions table, to avoid having to test for a OS_NULL pointer.
*/
/* Deviation DCG-1 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_NullFunction(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
