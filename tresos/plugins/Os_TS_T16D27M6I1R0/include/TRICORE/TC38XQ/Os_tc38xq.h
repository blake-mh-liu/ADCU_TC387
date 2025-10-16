/* Os_tc38xq.h - Description of Tricore TC38XQ (Aurix development vehicle)
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* This file describes the TC38XQ variant of Tricore.
*/

#ifndef OS_TC38XQ_H
#define OS_TC38XQ_H

#include <Os_types.h>

/* Setup architecture */

#define OS_TRICOREARCH			OS_TRICOREARCH_162

/* number of cores available on this derivative */
#define OS_N_CORES_MAX			OS_U(4)

/* Tricore CPU Core SFRs
*/
#include <TRICORE/Os_TRICORE_core.h>
#include <TRICORE/Os_tc38x.h>

/* Peripheral modules that are of interest to the OS
 *
 * The STM is the system timer module and contains the 64-bit free-running counter used for all time measurements.
 * On the TC38XQ we have 6 STM modules and 2 possible interrupts per module.
 *
 * CHECK: RULE 402 OFF	(OS_pwr isn't a constant-like macro; it's a variable-like macros)
*/
#define OS_PWR_BASE			OS_U(0xf0036000)
#include <TRICORE/Os_TRICORE_pwr.h>
#define OS_pwr				(*(os_tricorepwr_t *)OS_PWR_BASE)

/* These are the system timer's (STM[0-5]) base addresses. */
#define OS_N_STM			4
#define OS_STM0_BASE		OS_U(0xf0001000)
#define OS_STM1_BASE		OS_U(0xf0001100)
#define OS_STM2_BASE		OS_U(0xf0001200)
#define OS_STM3_BASE		OS_U(0xf0001300)

/* STM0 is the default system timer. */
#define OS_STM_BASE			OS_STM0_BASE

#define OS_STM_HAS_COMPARE	1

/* OCDS Control and Status Register (OCS) */
#define OS_STM_OCS_OFFSET	OS_U(0xe8)
#define OS_STM0_OCS			(*(os_reg32_t *)(OS_STM0_BASE + OS_STM_OCS_OFFSET))
#define OS_STM1_OCS			(*(os_reg32_t *)(OS_STM1_BASE + OS_STM_OCS_OFFSET))
#define OS_STM2_OCS			(*(os_reg32_t *)(OS_STM2_BASE + OS_STM_OCS_OFFSET))
#define OS_STM3_OCS			(*(os_reg32_t *)(OS_STM3_BASE + OS_STM_OCS_OFFSET))

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
