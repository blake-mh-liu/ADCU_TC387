/* lib-getunusedtaskstack.c
 *
 * This file contains the OS_GetUnusedTaskStack function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 12.3 (required)
 * The comma operator shall not be used.
 *
 * Reason:
 * For function-call kernels, OS API is wrapped in macros. The macro wrappers
 * need to use the comma operator to form an expression evaluating to the
 * correct result.
 *
 *
 * MISRAC2012-2) Deviated Rule: 13.3 (advisory)
 * The increment (++) and decrement (--) operators should not be mixed with
 * other operators in an expression.
 *
 * Reason:
 * For function-call kernels, OS API is wrapped in macros. The macro wrappers
 * need to handle an "in kernel" flag so that the increment operator has to be
 * used in combination with the comma operator.
 *
 *
 * MISRAC2012-3) Deviated Rule: 13.2 (required)
 * The value of an expression and its persistent side effects shall be the same
 * under all permitted evaluation orders
 *
 * Reason:
 * For function-call kernels, OS API functions are wrapped inside a macro using
 * the coma operator. Polyspace complains that the value of info depends on the
 * order of evaluation. For the comma operator, the order of evaluation is
 * defined by the C standard and the calculation of the content of the struct
 * pointed to by info does not depend on the left operand of the coma operator
 * at all. Thus, there is a strong indication that this is likely a false
 * positive warning by Polyspace.
*/

#include <Os_api.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_tool.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetUnusedTaskStack implements the API getUnusedTaskStack
 *
 * The system call OS_UserGetStackInfo is called, first setting the
 * info structure's current SP to 0. The answer is then computed.
 * If anything goes wrong, 0 is returned.
 *
 * !LINKSTO Kernel.Feature.StackCheck.API.getUnusedTaskStack, 1
*/

OS_TOOL_FUNCTION_ATTRIB_PRE
os_size_t OS_GetUnusedTaskStack(os_taskid_t t)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_size_t answer = 0;
	os_stackinfo_t info;

	info.stackPointer = 0;

	/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1>, MISRAC2012-3 <+1> */
	if ( OS_UserGetStackInfo(OS_TaskToTOI((os_taskorisr_t)t), &info) == OS_E_OK )
	{
		answer = info.stackClean;
	}

	return answer;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
const os_uint8_t OS_dummy_lib_getunusedtaskstack_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
