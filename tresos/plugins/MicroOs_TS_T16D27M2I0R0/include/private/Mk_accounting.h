/* Mk_accounting.h - execution budgeting and time stamp timer
 *
 * This file contains definitions for the hardware-independent part of
 * execution budgeting and the time stamp timer. It also includes the
 * hardware-specific part.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_ACCOUNTING_H
#define MK_ACCOUNTING_H

#ifndef MK_ASM

#include <public/Mk_hwsel.h>
#include <public/Mk_public_types.h>
#include <public/Mk_error.h>
#include <private/Mk_types_forward.h>

#include MK_HWSEL_PRV_ACCOUNTING

/* An "infinite" execution time budget
*/
#define MK_EXECBUDGET_INFINITE		MK_MAXTICK

/* Data types for accounting.
*/
typedef struct mk_accounting_s mk_accounting_t;
typedef struct mk_accountingcfg_s mk_accountingcfg_t;
typedef struct mk_extendedtime_s mk_extendedtime_t;

/* The accounting structure.
*/
struct mk_accounting_s
{
	const mk_accountingcfg_t *acctCfg;	/* Accounting configuration */
	mk_tick_t timeRemaining;			/* Time remaining */
};

/* The accounting configuration structure
*/
struct mk_accountingcfg_s
{
	mk_tick_t execBudget;				/* Execution budget for this thread */
};

/* The extended time stamp structure, for hardware that doesn't have a "long" hardware timer
*/
struct mk_extendedtime_s
{
	mk_time_t timestamp;				/* The value of the long time at the last update */
	mk_tick_t lastReadTime;				/* The value of the short timer at the last update */
};

/* Global variable. The extended timer is only present if the hardware has no "long" timer.
*/
extern mk_extendedtime_t MK_extendedTimer;

/* MK_ExtendTimer extends a hardware timer to 64 bits.
*/
void MK_ExtendTimer(void);

/* Functions and variables for controlling the execution budget monitor.
*/
void MK_InitExecutionBudgetMonitor(mk_kernelcontrol_t *);
mk_boolean_t MK_IsExecutionBudgetConfigured(mk_objectid_t);

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
