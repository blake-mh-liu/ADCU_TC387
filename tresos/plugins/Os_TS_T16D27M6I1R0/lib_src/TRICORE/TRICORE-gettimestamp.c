/* TRICORE-gettimestamp.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <TRICORE/Os_TRICORE_core.h>
#include <TRICORE/Os_TRICORE_stm.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_TricoreGetTimestamp
 *
 * Places the current value of the STM (56/64 bits) into the indicated os_timestamp_t (64-bit) location
 *
 * Assumptions:
 *  - None. In particular, no assumption is made about interrupts being disabled.
 *
 * Parameters: currentTime points to the os_timestamp_t output location
 *
 * In this function, the loop terminates when the lower-part of the STM counter is read between two
 * identical values from the upper part.
 *
 * Termination: in theory, the loop might never terminate. However, this would require a very carefully-crafted
 * interrupt, or an interrupt load so high that in practice whatever called this function would never do
 * any processing anyway.
 *
*/

/* OS_TricoreGetTimestamp
 *
 * Places the current value of the STM into the indicated os_timestamp_t (64-bit) location.
 * The value of the counter is temporarily stored in a 64-bit location.
 * An upcast and downcast of the counter variable generate low and high fields expected
 * by os_timestamp_t.
 *
 * Assumptions:
 *  - None. In particular, no assumption is made about interrupts being disabled.
 *
 */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_TricoreGetTimestamp(os_timestamp_t *currentTime)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_uint32_t high1;
	os_uint32_t high2;
	os_uint32_t low;

	do
	{
        high1 = OS_StmReadTimeHigh32(OS_timestampStm);
        low = OS_StmReadTimeLow32(OS_timestampStm);
        high2 = OS_StmReadTimeHigh32(OS_timestampStm);
	} while ( high1 != high2 );

	currentTime->tsLo = low;
	currentTime->tsHi = high1;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_gettimestamp_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
