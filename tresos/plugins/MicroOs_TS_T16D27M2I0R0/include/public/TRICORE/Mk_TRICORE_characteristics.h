/* Mk_TRICORE_characteristics.h
 *
 * This file defines the processor characteristics for TRICORE.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* !LINKSTO Microkernel.TRICORE.Design.CPU_Characteristics, 1
 * !doctype src
*/
#ifndef MK_TRICORE_CHARACTERISTICS_H
#define MK_TRICORE_CHARACTERISTICS_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

#define MK_HWWORDLENGTH		32
#define MK_HWENDIAN			MK_LITTLEENDIAN
#define MK_HWSTACKGROWS		MK_STACKGROWSDOWN
#define MK_MEMPERM_T		mk_uint32_t

#define MK_HWNEGDIV			MK_NEGDIV_ROUNDTOWARDZERO

/* TRICORE implementation does not have microkernel support for read-modify-write transactions.
*/
#define MK_HW_HAS_TRANSACTION_SUPPORT	0


/* All TRICORE processors so far have a 56-bit timer (STM) that is sufficient for the time stamp.
 * This means that MK_GenericReadTime() and MK_ExtendTimer() are not required.
 *
 * !LINKSTO Microkernel.Function.MK_GenericReadTime, 1
 * !LINKSTO Microkernel.Function.MK_ExtendTimer, 1
 * !doctype src
*/
#define MK_HW_HAS_TIMESTAMP	1

/* TRICORE does not require a heap.
*/
#define MK_HASHEAP			0

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
