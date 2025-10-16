/* Mk_board_tpsticks.h - defines conversion between STM and TPS ticks
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board_tpsticks.h 27411 2017-02-07 17:47:09Z mist9353 $
*/
#ifndef MK_BOARD_TPSTICKS_H
#define MK_BOARD_TPSTICKS_H

/* For execution budget monitoring, the microkernel uses the TPS module of the processor to create
 * exceptions when a thread exceeds its budget.
 *
 * The macro MK_BOARD_STMTPSMUL defines the multiplication factor to convert from STM ticks to
 * CPU ticks. If the different CPU cores run at different core clocks, the macro will need to
 * check the current core id to do the proper conversion.
 *
 * Note: this calculation may overflow, but we expect the typical execution budget
 *       of a task to stay within the bounds of the mk_uint32.
 *
 *       If the value actually _does_ overflow, it will lead to an early invocation
 *       of the microkernel, which will then see that the thread still has budget.
 *       The thread will then be allowed to execute further.
*/
#define MK_BOARD_STMTPSMUL 2u
#define MK_ExecutionTicksToTpsTicks(ticks)	((ticks) * MK_BOARD_STMTPSMUL);

#endif

/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/

