/* kern-startupchecksassembleroffsets.c
 *
 * This file contains the code to validate the various structure offset values defined in this code.
 * Such offset values are used by assembly language code to access the respective structure members.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: PointlessComparison
 *  Condition is always false/true.
 *
 * Reason:
 *  OS_StartupChecksAssemblerOffsets checks the offsets of those fields of certain structs,
 *  which are referenced in assembler code. The compiler can evaluate this at compile time.
 *  That is not an issue.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.9 (required)
 * The macro NULL shall be the only permitted form of integer null pointer
 * constant.
 *
 * Reason:
 * The macro OFFSETOF() must use the literal constant '0' for its calculations.
 * This constant is interpreted as pointer to determine the offset of a
 * structure member.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_VOCF]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  This completely readable function is merely a development
 *  aid. The chained evaluation statements seem to lead to a
 *  high VOCF value.
*/
/* Deviation DCG-1 <*> */

#include <Os_kernel.h>
#include <Os_tool.h>
#include <Os_panic.h>
#include <Os_types.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_StartupChecksAssemblerOffsets
 *
 * There are several definitions of macros OS_T_* in this source code. Each such macro denotes the offset in bytes
 * relative to the start of a structure to one of its members. These macros are used in assembly language code
 * to access those members. This function validates these OS_T_* macros.
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_StartupChecksAssemblerOffsets(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t result = OS_E_OK;
	os_boolean_t offsets_ok = OS_TRUE;

	/* Checks for os_kerneldata_t. */
	/* Deviation MISRAC2012-1 <START> */
	/* Possible diagnostic TOOLDIAG-1 <START> */
#if (OS_KERNEL_TYPE != OS_MICROKERNEL)
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, taskQueueHead) == OS_T_TASKQHEAD) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, taskCurrent) == OS_T_TASKCURRENT) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, iSpInitial) == OS_T_ISPINITIAL) && offsets_ok;
#ifdef OS_TYPEOF_ININTERRUPT
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, inInterrupt) == OS_T_ININTERRUPT) && offsets_ok;
#endif
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, inKernel) == OS_T_INKERNEL) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, idleMode) == OS_T_IDLEMODE) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, inFunction) == OS_T_INFUNCTION) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_kerneldata_t, tfCalledFrom) == OS_T_TFCALLEDFROM) && offsets_ok;
#endif /* OS_KERNEL_TYPE != OS_MICROKERNEL */

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)
	/* Checks for os_task_t. */
	offsets_ok = (OS_OFFSETOF(os_task_t, dynamic) == OS_T_DYNA) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_task_t, runPrio) == OS_T_RPRIO) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_task_t, flags) == OS_T_FLAGS) && offsets_ok;

	/* Checks for os_taskdynamic_t. */
	offsets_ok = (OS_OFFSETOF(os_taskdynamic_t, context) == OS_T_CTXT) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_taskdynamic_t, prio) == OS_T_PRIO) && offsets_ok;
	offsets_ok = (OS_OFFSETOF(os_taskdynamic_t, state) == OS_T_STAT) && offsets_ok;

#endif
	/* Possible diagnostic TOOLDIAG-1 <STOP> */
	/* Deviation MISRAC2012-1 <STOP> */

	/* COVPT-1 +2 */
	/* Possible diagnostic TOOLDIAG-1 <+1> */
#pragma warning 549
	if (!offsets_ok)
#pragma warning default
	{
		result = OS_PANIC(OS_PANIC_SCHK_InvalidStructureOffsetValue);
	}

	return result;
}


#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
