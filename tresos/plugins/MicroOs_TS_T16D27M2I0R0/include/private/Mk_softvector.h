/* Mk_softvector.h - software interrupt vectoring
 *
 * This file contains definitions for the hardware-independent part of configuration
 * and handling of the software interrupt vector table. It also includes the
 * hardware-specific part.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *  Conversions shall not be performed between a pointer to a function and
 *  any other type.
 *
 * Reason:
 *  The ISR prototype of internal interrupts is binary compatible with mk_interruptfunc_t.
 *  It has different parameter types, so the user code is not required to include kernel headers.
*/

#ifndef MK_SOFTVECTOR_H
#define MK_SOFTVECTOR_H

#include <public/Mk_hwsel.h>
#include <public/Mk_public_types.h>
#include <private/Mk_interrupt.h>

/* Include the hardware-specific interrupt controller header
*/
#include MK_HWSEL_PRV_INTERRUPTCONTROLLER

#ifndef MK_ASM

typedef struct mk_softvector_s mk_softvector_t;

struct mk_softvector_s
{
	mk_interruptfunc_t func;
	mk_objectid_t param;
};

/* The software vector table contains an extra (unused) entry to act as a marker.
 * There is a check at startup that verifies that the vector table has been initialized
 * with the correct number of entries.
*/
extern const mk_softvector_t MK_softwareVectorTable[MK_HWN_INTERRUPTVECTORS+1];

/* These are initializer macros for the software interrupt-vector table
*/
/* Deviation MISRAC2012-1 <+1> */
#define MK_VECTOR(f,n)			{ (f), (n) }
#define MK_VECTOR_XCORE(n)		MK_VECTOR(MK_CrossCoreMessageHandler, (n))
#define MK_VECTOR_UNKNOWN(n)	MK_VECTOR(MK_UnknownInterrupt, (n))
#define MK_VECTOR_DEMUX(n)		MK_VECTOR(MK_DispatchInterruptDemux, (n))

#ifndef MK_VECTOR_ISR
#define MK_VECTOR_ISR(n)		MK_VECTOR(MK_StartThreadForIsr, (n))
#endif

#ifndef MK_VECTOR_CTRSUBISR
#define MK_VECTOR_CTRSUBISR(n)	MK_VECTOR(MK_StartThreadForCtrSubIsr, (n))
#endif

#define MK_VECTOR_INTERNAL(f,n)	MK_VECTOR((f), (n))

/* These macros are used to create the end marker of the software interrupt vector table.
*/
#define MK_VECTOR_LASTMARK		(32767)									/* 0x7fff */
#define MK_VECTOR_LAST			MK_VECTOR_UNKNOWN(MK_VECTOR_LASTMARK)

void MK_DispatchInterruptSoft(mk_hwvectorcode_t);
void MK_DispatchInterruptDemux(mk_kernelcontrol_t *, mk_objectid_t, mk_hwvectorcode_t);

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
