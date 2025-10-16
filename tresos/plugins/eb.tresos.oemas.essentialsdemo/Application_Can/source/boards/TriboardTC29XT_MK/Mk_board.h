/* Mk_board.h - board specific ASIL header file for the TriboardTC297 board
 *
 * (c) by Elektrobit Automotive Software
 *
 * $Id: Mk_board.h 28186 2017-04-03 07:27:15Z dh $
*/

/* MISRA-C:2004 Deviation List
 *
 * MISRA-1) Deviated Rule: 6.3 (advisory)
 * Typedefs that indicate size and signedness should be used in place of the basic types.
 *
 * Reason:
 * main shall be defined with a return type of int.
*/

#ifndef MK_BOARD_H
#define MK_BOARD_H

#include <public/Mk_timeconversion.h>
#include "Mk_board_tpsticks.h"

#define BOARD_STM_FREQ_HZ 50000000

#if BOARD_STM_FREQ_HZ == 50000000
#define MK_ExecutionNsToTicks(ns)	MK_NsToTicks_50000000((ns))
#else
#error "A definition of MK_ExecutionNsToTicks() for the configured clock frequency is needed."
#endif

/*
 * Conversion macros for the timestamp. RTI is used as timestamp timer.
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
 * call and 48-bit integer arithmentic. The advantage is better accuracy, at
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

#define MK_HAS_TIMESTAMPCLOCKFACTOR100U     1
#define MK_HAS_TIMESTAMPCLOCKFACTOR10U      1
#define MK_HAS_TIMESTAMPCLOCKFACTOR1U       1

#else
#error "A definition of timestamp conversion macros and constants for the configured clock frequency is needed."
#endif

/* TC29x processors have 3 cores.
 *
 * Core 1 has a lockstep partner.
 *
 * Cores 0 and 2 is have no lockstep partners, so they need the MPU register check according to the
 * Infineon safety manual.
*/
#define MK_CFG_C0_MPU_REGISTER_CHECK	1
#define MK_CFG_C2_MPU_REGISTER_CHECK	1

#ifndef MK_ASM
/*
 * Prototype for main()
 *
 * The microkernel will actually not use the returned value, but this prototype
 * was chosen, because it is also one of (hosted) C's standard prototypes.
*/
/* Deviation MISRA-1 */
extern int main(void);
#endif

#endif
/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/
