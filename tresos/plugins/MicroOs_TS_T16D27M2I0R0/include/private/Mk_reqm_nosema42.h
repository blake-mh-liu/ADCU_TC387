/* Mk_reqm_nosema42.h
 *
 * This file contains requirements management for derivatives which don't use a
 * Semaphores2 unit (SEMA42) to implement spinlocks.
 * Requirements for the MK's support for SEMA42 spinlocks cannot be fulfilled
 * by derivatives which don't have one.
 * This file shall not be used for derivatives using a SEMA42 unit to implement
 * spinlocks.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_REQM_NOSEMA42_H
#define MK_REQM_NOSEMA42_H

/* Derivatives that do not use the SEMA42 unit, do not need the
 * MK_TrySpinlockSema42() function.
 *
 * !LINKSTO Microkernel.Function.MK_TrySpinlockSema42, 1
*/

#endif /* MK_REQM_NOSEMA42_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
