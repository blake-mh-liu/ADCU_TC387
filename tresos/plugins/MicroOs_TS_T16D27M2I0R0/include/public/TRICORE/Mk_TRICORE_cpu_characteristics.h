/* Mk_TRICORE_cpu_characteristics.h - Tricore CPU header file
 *
 * This file defines the CPU characteristics for TRICORE.
 *
 * (c) Elektrobit Automotive GmbH
*/
/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 1.3 (required)
 *  There shall be no occurrence of undefined or critical unspecified behaviour.
 *
 * Reason:
 *  Information hiding. For example, the structure should be visible in a debugger but not in the
 *  application source code, or a pointer type is declared before the structure can be fully defined.
 *  Note: MISRA-C:2012 Dir 4.8 advises that incomplete declarations should be used where possible
 *
 * MISRAC2012-2) Deviated Rule: 5.7 (required)
 *  A tag name shall be a unique identifier.
 *
 * Reason:
 *  False positive because the struct is used in a forward type definition.
 *
*/
#ifndef MK_TRICORE_CPU_CHARACTERISTICS_H
#define MK_TRICORE_CPU_CHARACTERISTICS_H

#include <public/Mk_defs.h>
#include <public/TRICORE/Mk_TRICORE_defs.h>

/* Include the appropriate header file for the derivative.
*/
#if (MK_CPU == MK_TC27XT)
#include <public/TRICORE/TC27XT/Mk_TC27XT.h>
#elif (MK_CPU == MK_TC23XL)
#include <public/TRICORE/TC23XL/Mk_TC23XL.h>
#elif (MK_CPU == MK_TC29XT)
#include <public/TRICORE/TC29XT/Mk_TC29XT.h>
#elif (MK_CPU == MK_TC22XL)
#include <public/TRICORE/TC22XL/Mk_TC22XL.h>
#elif (MK_CPU == MK_TC39XX)
#include <public/TRICORE/TC39XX/Mk_TC39XX.h>
#elif (MK_CPU == MK_TC39XQ)
#include <public/TRICORE/TC39XQ/Mk_TC39XQ.h>
#elif (MK_CPU == MK_TC38XQ)
#include <public/TRICORE/TC38XQ/Mk_TC38XQ.h>
#elif (MK_CPU == MK_TC38XT)
#include <public/TRICORE/TC38XT/Mk_TC38XT.h>
#elif (MK_CPU == MK_TC37XT)
#include <public/TRICORE/TC37XT/Mk_TC37XT.h>
#elif (MK_CPU == MK_TC36XD)
#include <public/TRICORE/TC36XD/Mk_TC36XD.h>
#elif (MK_CPU == MK_TC35XT)
#include <public/TRICORE/TC35XT/Mk_TC35XT.h>
#elif (MK_CPU == MK_TC33XL)
#include <public/TRICORE/TC33XL/Mk_TC33XL.h>
#elif (MK_CPU == MK_TC32XL)
#include <public/TRICORE/TC32XL/Mk_TC32XL.h>
#else
#error "MK_CPU is not properly defined. Check your makefiles!"
#endif

/* CSFR register offsets
 *
 * Only those that are used get defined here.
*/
#define MK_PCXI			0xfe00
#define MK_PSW			0xfe04
#define MK_SYSCON		0xfe14
#define MK_CORE_ID		0xfe1c
#define MK_BIV			0xfe20
#define MK_BTV			0xfe24
#define MK_ISP			0xfe28
#define MK_ICR			0xfe2c
#define MK_FCX			0xfe38
#define MK_LCX			0xfe3c
#define MK_COMPAT		0x9400
#define MK_TPS_CON		0xe400
#define MK_TPS_TIMER0	0xe404
#define MK_TPS_TIMER1	0xe408
#define MK_TPS_TIMER2	0xe40C
#define MK_PMA0			0x8100
#define MK_PMA1			0x8104
#define MK_PCON0		0x920c
#define MK_PCON1		0x9204
#define MK_DCON0		0x9040
#define MK_DSTR			0x9010
#define MK_DATR			0x9018
#define MK_DEADD		0x901c
#define MK_DIEAR		0x9020
#define MK_DIETR		0x9024
#define MK_PSTR			0x9200
#define MK_PIEAR		0x9210
#define MK_PIETR		0x9214

/* Forward declaration of incomplete TRICORE-specific structures
 * which are referenced by public APIs or structures as opaque types.
 * These structures can be used for debugging.
*/
/* Deviation MISRAC2012-1 <START>, MISRAC2012-2 <START> */
#ifndef MK_ASM
typedef struct mk_lowerctx_s mk_lowerctx_t;
typedef struct mk_upperctx_s mk_upperctx_t;
#endif
/* Deviation MISRAC2012-1 <STOP>, MISRAC2012-2 <STOP> */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
