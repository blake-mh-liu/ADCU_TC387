/* Mk_TRICORE_accounting.h - TRICORE execution budgeting and time stamp timer
 *
 * This file contains the TRICORE-specific part of the definitions for
 * execution budgeting and the time stamp timer.
 *
 * (c) Elektrobit Automotive GmbH
*/
/* !LINKSTO Microkernel.TRICORE.HwAccounting.Mk_TRICORE_accounting, 1
 * !doctype src
*/
#ifndef MK_TRICORE_ACCOUNTING_H
#define MK_TRICORE_ACCOUNTING_H

#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_stm.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>

/* TPS_TIMER is always cleared on kernel entry, therefore MK_HwUpdateExecutionTimeAlarm() needs to
 * be identical to MK_HwSetExecutionTimeAlarm().
 *
 * !LINKSTO Microkernel.TRICORE.Hw_Accounting.MK_HwUpdateExecutionTimeAlarm, 1
 * !doctype src
*/
#define MK_HwUpdateExecutionTimeAlarm(x)			MK_HwSetExecutionTimeAlarm(x)

/* Low word of STM doubles as execution timer
 *
 * !LINKSTO Microkernel.TRICORE.HwAccounting.MK_HwReadExecutionTimer, 1
 * !doctype src
*/
#define MK_HwReadExecutionTimer()					(MK_timestampStm->stm_tim0)

/* Nothing to do: TPS_TIMER is always cleared on kernel entry
 *
 * !LINKSTO Microkernel.TRICORE.HwAccounting.MK_HwDispatcherClearExecutionTimeAlarm, 1
 * !doctype src
*/
#define MK_HwDispatcherClearExecutionTimeAlarm()	do { } while (0)

/* Convert ticks and write to TPS_TIMER0
 *
 * !LINKSTO Microkernel.TRICORE.HwAccounting.MK_HwSetExecutionTimeAlarm, 1
 * !doctype src
*/
#define MK_HwSetExecutionTimeAlarm(x)				\
	do {											\
		MK_MTTPS_TIMER0(MK_ExecTickConvert(x));		\
	} while (0)

/* 32-bit unsigned subtraction. Wraps perfectly.
 *
 * !LINKSTO Microkernel.TRICORE.HwAccounting.MK_HwExecutionTimeDelta, 1
 * !doctype src
*/
#define MK_HwExecutionTimeDelta(now, prev)			( (now) - (prev) )

/* Activates the TPS (temporal protection system) module
 *
 * !LINKSTO Microkernel.TRICORE.HwAccounting.MK_HwInitExecutionTimer, 1
 * !doctype src
*/
#define MK_HwInitExecutionTimer()					do { MK_EnableTps(); } while (0)


/* Value chosen to represent 5us at 100MHz - a bigger value might
 * make sense for slower clocks, but then it would need to depend
 * on the board file, which we need to avoid for the library
*/
#define MK_MIN_EXECUTIONTIME						MK_U(500)


/* Conversion function
*/
extern mk_tick_t MK_ExecTickConvert(mk_tick_t);

/* Enable TPS
*/
extern void MK_EnableTps(void);

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
