/* Mk_k_startup.c
 *
 * This file contains the MK_Startup() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_CALLS]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *  In function MK_HandleContextTrap: Value 8.0 of metric "calls" is out of bounds (0..7)
 *
 * Reason:
 *  MK_Startup doesn't contain more calls than necessary. MK_Startup executes the start-up sequence,
 *  which requires that this sequence of initialization functions is called.
*/
/* Deviation DCG-1 <*> */
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_callout.h>
#include <private/Mk_startup.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>

/* MK_Startup
 *
 * The MK_InitHardwareBeforeData() function is called before data initialization. This function
 * performs initialization that has not already been done by the "entry" code but must be done
 * before initializing the data. Typically this will be processor clock initialization to ensure
 * that the data initialization loops run at full speed. Watchdog initialization could also be done
 * here.
 *
 * The MK_InitHardwareAfterData() function is called after data initialization. This function
 * initializes any remaining hardware that the kernel needs.
 *
 * Call MK_StartKernel() which should never return.
 *
 * NOTE: This function is called by the assembly-language "entry"
 * code. At this point there isn't a full C environment available;
 * the .data and .bss sections have not been initialized, so
 * we cannot rely on the content of any variables with global lifetime.
 *
 * !LINKSTO Microkernel.Function.MK_Startup, 2
 * !doctype src
*/
void MK_Startup(mk_uint32_t p1, mk_uint32_t p2, mk_uint32_t p3, mk_uint32_t p4)
{
	/* This effectively compares each one of the key parameters for equality ("==")
	 * with its respective MK_MIDDLEKEY value.
	*/
	if ( ( (p1 ^ MK_MIDDLEKEY_1) | (p2 ^ MK_MIDDLEKEY_2) | (p3 ^ MK_MIDDLEKEY_3) | (p4 ^ MK_MIDDLEKEY_4) ) == 0u )
	{

		/* Before we call the first MK_SyncHere, we have to check, whether this core's sync spot has been initialized.
		*/
		MK_StartupCheckSyncHere();
		MK_SyncHere();

		MK_InitHardwareBeforeData();

		/* Initialize data sections and take care of synchronization.
		*/
		MK_StartupInitDataSections();

		MK_SyncHere();

		MK_InitHardwareAfterData();

		MK_SyncHere();

		MK_StartKernel(p2^MK_U(MK_TRANSKEY_1), p3^MK_U(MK_TRANSKEY_2), p4^MK_U(MK_TRANSKEY_3), p1^MK_U(MK_TRANSKEY_4));
	}
	else
	{
		MK_StartupPanic(MK_panic_IncorrectStartupKey);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
