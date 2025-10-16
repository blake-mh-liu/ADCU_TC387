/* Mk_board.h - board specific ASIL header file for the TriboardTC397 board
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board_tc3.h 32971 2018-05-24 10:54:30Z mist9353 $
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: D4.6 (advisory)
 * Typedefs that indicate size and signedness should be used in place of the basic types.
 *
 * Reason:
 * main shall be defined with a return type of int.
*/

#ifndef MK_BOARD_TC3_H
#define MK_BOARD_TC3_H

#include <public/Mk_timeconversion.h>
#include "Mk_board_tpsticks.h"

#define BOARD_STM_FREQ_HZ 100000000

#if BOARD_STM_FREQ_HZ == 50000000
#define MK_ExecutionNsToTicks(ns)	MK_NsToTicks_50000000((ns))
#elif BOARD_STM_FREQ_HZ == 100000000
#define MK_ExecutionNsToTicks(ns)	MK_NsToTicks_100000000((ns))
#else
#error "A definition of MK_ExecutionNsToTicks() for the configured clock frequency is needed."
#endif

/*
 * Conversion macros for the timestamp. The STM's free-running counter is used as timestamp timer.
 *
 * MK_TimestampNsToTicks() converts the parameter (time in nanoseconds) to
 * ticks of the timebase/decrementer.
 * MK_TimestampTicksToNs(0 converts the parameter (no. of ticks) to
 * nanoseconds. If the time would be larger
 * than can be represented by a 32-bit unsigned number, the maximum possible
 * (Oxffffffff) is returned.
 *
 * Both of the above conversions are performed using integer arithmetic, so
 * can be used to initialise constants.
 *
 * MK_TimestampNsToTicksF() and MK_TimestampTicksToNsF() perform the
 * equivalent conversions using a function
 * call and 48-bit integer arithmetic. The advantage is better accuracy, at
 * the cost of slightly more CPU time.
*/
#if BOARD_STM_FREQ_HZ == 50000000
#define MK_TimestampNsToTicks(ns)	MK_NsToTicks_50000000((ns))
#define MK_TimestampNsToTicksF(ns)	MK_NsToTicksF_50000000((ns))
#define MK_TimestampTicksToNs(ns)	MK_TicksToNs_50000000((ns))
#define MK_TimestampTicksToNsF(ns)	MK_TicksToNsF_50000000((ns))

/* Factors for timestamp timer conversion: How many ticks have
 * 100, 10 and 1 microseconds?
*/
#define MK_TIMESTAMPCLOCKFACTOR100U 5000u
#define MK_TIMESTAMPCLOCKFACTOR10U  500u
#define MK_TIMESTAMPCLOCKFACTOR1U   50u

#elif BOARD_STM_FREQ_HZ == 100000000
#define MK_TimestampNsToTicks(ns)	MK_NsToTicks_100000000((ns))
#define MK_TimestampNsToTicksF(ns)	MK_NsToTicksF_100000000((ns))
#define MK_TimestampTicksToNs(ns)	MK_TicksToNs_100000000((ns))
#define MK_TimestampTicksToNsF(ns)	MK_TicksToNsF_100000000((ns))
#define MK_TIMESTAMPCLOCKFACTOR100U 10000u
#define MK_TIMESTAMPCLOCKFACTOR10U  1000u
#define MK_TIMESTAMPCLOCKFACTOR1U   100u

#else
#error "A definition of timestamp conversion macros and constants for the configured clock frequency is needed."
#endif

#define MK_HAS_TIMESTAMPCLOCKFACTOR100U     1
#define MK_HAS_TIMESTAMPCLOCKFACTOR10U      1
#define MK_HAS_TIMESTAMPCLOCKFACTOR1U       1

#ifndef MK_ASM
/*
 * Prototype for main()
 *
 * The microkernel will actually not use the returned value, but this prototype
 * was chosen, because it is also one of (hosted) C's standard prototypes.
*/
/* Deviation MISRAC2012-1 <1> */
extern int main(void);
#endif

#endif
/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/
