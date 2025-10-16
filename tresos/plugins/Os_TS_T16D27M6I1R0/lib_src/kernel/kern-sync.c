/* kern-sync.c
 *
 * Synchronization of 2 or more cores during startup.
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.9 (advisory)
 * An object shall be defined at block scope if its identifier only appears in
 * a single function.
 *
 * Reason:
 * Required by AUTOSAR memory mapping (see document ID 128: AUTOSAR_SWS_MemoryMapping).
 *
 *
 * MISRAC2012-3) Deviated Rule: 17.2 (required)
 *   Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *   OS_SyncHere() might call itself indirectly via OS_Panic().
 *   OS_Panic() detects recursive calls by means of the core-local variable
 *   panicCode. If OS_Panic() is entered a second time, it calls
 *   OS_ShutdownNoHooks() which doesn't call OS_Panic() again. Instead, it
 *   stops the system, and, therefore, the maximum nesting level is two calls.
 *
 *
 * MISRAC2012-4) Deviated Rule: 5.5 (required)
 * Identifiers shall be distinct from macro names.
 *
 * Reason:
 * For performance reasons, the OS_SyncHere function is replaced by an empty function like macro,
 * if only one core is used.
 *
 *
 * MISRAC2012-5) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * For performance reasons, the OS_SyncHere function is replaced by an empty function like macro,
 * if only one core is used.
 */

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/
#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_tool.h>
#include <Os_panic.h>
#include <Os_spinlock.h>

#include <memmap/Os_mm_var_begin.h>
/* Deviation MISRAC2012-1 <START> */
/* CHECK: NOPARSE */
static
OS_SECTION_PRAGMA(OS_syncArray, .bss.shared.os.OS_syncArray)
os_sw_syncspot_t
	OS_SECTION_ATTRIB_PRE(.bss.shared.os.OS_syncArray)
	OS_syncArray[OS_N_CORES_MAX]
	OS_BSS_SECTION_ATTRIB_POST(.bss.shared.os.OS_syncArray);
/* CHECK: PARSE */
/* Deviation MISRAC2012-1 <STOP> */
#include <memmap/Os_mm_var_end.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_SyncHere()
 *
 * This function performs barrier-style synchronization for all cores.
 *
 * It depends on
 *   - a properly initialized C-environment, i.e., the OS_syncArray is completely
 *     initialized to zeroes before this function is first invoked on any core.
 *   - the hardware being able to atomically write a value to an os_syncspot_t
 *     (hardware dependent type!)
 *   - called no more often than the highest positive number os_syncspot_t can
 *     represent (hardware dependent)
 *
 * How it works:
 *
 * Every core "owns" one element of the OS_syncArray and is the only one writing
 * to this element. At the beginning of the function, each core increments his
 * array element. Then it repeatedly checks if the other cores have done the same
 * by looking at their values in turn.
 *
 * Even though every core only writes to its entry in the array, synchronization
 * is needed because the cache flush operation may actually also write the entries
 * owned by other cores.
 *
 * When all cores have incremented their elements, all cores will recognize this
 * within the next iteration of the check loop. Then all cores proceed further.
*/
/* Deviation MISRAC2012-3 <+2>, MISRAC2012-4 <+2>, MISRAC2012-5 <+2> */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_SyncHere (void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_coreid_t const me = OS_GetMyCoreId();
	os_size_t newval;
	os_uint_t i;
	os_int_t all;
	os_intstatus_t is;

	/* Increment the core's own entry in the sync array */
	is = OS_TakeInternalLock(OS_SYNCHERE_LOCKID);
	OS_CacheInvalidate(&OS_syncArray[me], sizeof(OS_syncArray[me]));
	newval = OS_syncArray[me] + 1u;
	OS_syncArray[me] = newval;
	OS_CacheFlush(&OS_syncArray[me], sizeof(OS_syncArray[me]));
	OS_DropInternalLock(OS_SYNCHERE_LOCKID, is);

	do {
		/* Core waits here until all cores have arrived here.
		*/
		all = 1;
		OS_CacheInvalidate(OS_syncArray, sizeof(OS_syncArray));
		for ( i = 0; i < OS_N_CORES_MAX; i++ )
		{
			if ( OS_CoreIsInUse(i) )
			{
				if ( OS_syncArray[i] < newval )
				{
					all = 0;
				}
			}
		}
		/* COVPT-1 */
		if ( OS_syncArray[me] != newval )
		{
			/* Somehow our syncArray-element changed. This really shouldn't happen.
			   If it happens anyway, there likely is a problem with the memory arbiter
			   or the cache coherency unit
			*/
			/* Deviation MISRAC2012-3 <+1> */
			(void) OS_PANIC(OS_PANIC_SyncArrayCorrupted);
		}
	} while ( all == 0 );
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sync_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
