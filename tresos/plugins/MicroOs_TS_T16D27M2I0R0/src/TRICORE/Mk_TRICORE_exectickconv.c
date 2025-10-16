/* Mk_TRICORE_exectickconv.c
 *
 * This file contains the function MK_ExecTickConvert. This function is called in the dispatcher
 * to convert STM ticks to TPS ticks for execution budget protection.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_accounting.h>
#include <Mk_board.h>

/* MK_ExecTickConvert()
 *
 * Converts ticks of the STM (which is used for measuring the execution time used) into
 * ticks of the temporal-protection system, which is used to regain control if a thread
 * runs for too long without system calls or interrupts.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_ExecTickConvert, 2
 * !doctype src
*/
mk_tick_t MK_ExecTickConvert(mk_tick_t stmTicks)
{
	mk_tick_t tpsTicks;

	/* Use the user defined conversion macro. */
	tpsTicks = MK_ExecutionTicksToTpsTicks(stmTicks);

	return tpsTicks;
}
