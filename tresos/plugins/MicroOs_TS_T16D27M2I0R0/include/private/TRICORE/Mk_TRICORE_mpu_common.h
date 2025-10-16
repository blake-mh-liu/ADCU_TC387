/* Mk_TRICORE_mpu_common.h - Tricore MPU common header
 *
 * This file defines types that are used by all MPU implementations
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_MPU_COMMON_H
#define MK_TRICORE_MPU_COMMON_H

#include <public/Mk_basic_types.h>

#ifndef MK_ASM

/* mk_mpubounds_s - a structure to contain lower and upper boundary values for MPU registers
 *
 * This structure is kept simple because it is used (in the form of an array) in assembly language.
*/
struct mk_mpubounds_s
{
	mk_uint32_t lower;
	mk_uint32_t upper;
};

typedef struct mk_mpubounds_s mk_mpubounds_t;

#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
