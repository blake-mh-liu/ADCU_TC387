/* Mk_anondata.h - declarations of anonymous data section boundaries
 *
 * This file declares the linker-generated symbols that mark the boundaries of the "anonymous" data/bss
 * sections and the initial value image for the anonymous data section.
 *
 * The symbols are not variables as such. They are start and end markers of sections that contain
 * variables that have not been assigned to any other sections in the linker script.
 *
 * This file is included exactly once, by the function that initializes these sections.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: D4.5 (advisory)
 * Identifiers in the same name space with overlapping visibility should be
 * typographically unambiguous
 *
 * Reason:
 * MK_ANON_IDAT is the default start symbol for the anonymous init data section.
 * The "conflicting" MK_anonIDat is a pointer to it, as only its address matters.
*/

#ifndef MK_ANONDATA_H
#define MK_ANONDATA_H

#include <public/Mk_basic_types.h>
#include <private/Mk_tool.h>

extern mk_int8_t MK_MR_ANON_DATA_START;
extern mk_int8_t MK_MR_ANON_DATA_END;
extern mk_int8_t MK_MR_ANON_BSS_START;
extern mk_int8_t MK_MR_ANON_BSS_END;
extern mk_int8_t MK_MR_CAL_CORE0_DATA_START;
extern mk_int8_t MK_CAL_CORE0_DATA_END;
extern mk_int8_t MK_CAL_CORE0_DATA;
extern mk_int8_t MK_CAL_CORE0_IDAT;
extern mk_int8_t MK_MR_CAL_CORE1_DATA_START;
extern mk_int8_t MK_CAL_CORE1_DATA_END;
extern mk_int8_t MK_CAL_CORE1_DATA;
extern mk_int8_t MK_CAL_CORE1_IDAT;
extern mk_int8_t MK_CDD_DATA_CORE1;
extern mk_int8_t MK_CDD_DATA_CORE1_END;
extern mk_int8_t MK_CDD_DATA_CORE1_IDAT;
extern mk_int8_t MK_MR_PSPR_CORE0_START;
extern mk_int8_t MK_MR_PSPR_CORE0_END;
extern mk_int8_t MK_MR_PSPR_CORE0_IDATA_START;
extern mk_int8_t MK_MR_PSPR_CORE1_START;
extern mk_int8_t MK_MR_PSPR_CORE1_END;
extern mk_int8_t MK_MR_PSPR_CORE1_IDATA_START;

/* Deviation MISRAC2012-1 <+1> */
extern const mk_int8_t * const MK_anonIDat;
extern const mk_int8_t * const MK_cal_Core0_IDat;
extern const mk_int8_t * const MK_cal_Core1_IDat;
extern const mk_int8_t * const MK_cddDataCore1IDat;
extern const mk_int8_t * const MK_pspr_Core0_IDat;
extern const mk_int8_t * const MK_pspr_Core1_IDat;

#if (MK_TOOL == MK_ghs)
/* If GHS is used, tell toolchain that this linker variable resides in the
 * standard data section, even if sda optimization is turned on.
 * Otherwise, the compiler tries to access this ROM address via RAM sda
 * section offset.
 */
#pragma ghs startdata
#endif
/* Deviation MISRAC2012-1 <+1> */
extern const mk_int8_t MK_MR_ANON_IDATA_START;
#if (MK_TOOL == MK_ghs)
#pragma ghs enddata
#endif
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
