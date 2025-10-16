/* TRICORE-findtasksp.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to
 * object.
 *
 * Reason:
 * A pointer is read from hardware, which doesn't provide C language type
 * information. Hence, a type cast is required.
 *
 * MISRAC2012-2) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 * A value is read from hardware, which essentially represents a pointer.
 * The hardware, though, has no notion of C language types. Hence, the type
 * cast is required.
 */

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/* OS_FindTaskSp() - get a (pending) task's stack pointer.
 *
 * Given a task's context (PCXI), this function returns that stack pointer.
 * The stack pointer can be found in the first upper-context in the given
 * list.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void *OS_FindTaskSp(os_uint32_t pcxi)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t cxi = pcxi;
	os_uppercx_t *cx;
	void *sp = OS_NULL;
	os_boolean_t looking = 1;

	do {
		if ( cxi == 0u )
		{
			/* End of list (unexpected). Just return OS_NULL
			*/
			looking = 0;
		}
		else
		{
			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			cx = (os_uppercx_t *)OS_AddrFromCx(cxi);

			if ( (cxi & OS_PCXI_UL) == 0u )
			{
				/* Lower context. Get the index of the next CSA and
				 * continue. It doesn't matter that our pointer type
				 * is wrong - the next PCXI is always in the same place.
				*/
				cxi = cx->pcxi;
			}
			else
			{
				/* Upper context. Extract the SP and stop looking
				*/
				looking = 0;
				/* Deviation MISRAC2012-2 <+1> */
				sp = (void *)cx->a10;
			}
		}
	} while ( looking );

	return sp;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_findtasksp_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
