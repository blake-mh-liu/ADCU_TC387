/* Mk_TRICORE_mpu.h - Tricore MPU header
 *
 * This file selects the appropriate MPU header for the core.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_MPU_H
#define MK_TRICORE_MPU_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

#if MK_TRICORE_CORE == MK_TRICORE_TC161
#include <private/TRICORE/Mk_TRICORE_mpu_tc161.h>
#elif MK_TRICORE_CORE == MK_TRICORE_TC162
#include <private/TRICORE/Mk_TRICORE_mpu_tc162.h>
#else
#error "MK_TRICORE_CORE indicates a core for which there is no MPU support. Check your makefiles!"
#endif

/* MPU characteristics
*/
#define MK_HWMPUUSESLASTADDRESSOFREGION		0							/* Upper bound is first non-accessible addr. */

/* The following values are used to select the permission of a memory region.
 * READ and WRITE can be combined.
*/
#define MK_TRICORE_PERM_READ		0x01u
#define MK_TRICORE_PERM_WRITE		0x02u
#define MK_TRICORE_PERM_EXECUTE		0x04u
#define MK_TRICORE_PERM_RWMASK		(MK_TRICORE_PERM_READ|MK_TRICORE_PERM_WRITE)

/* The following defines are used in the configuration and are mapped to Tricore-specific values
*/
#define MK_MPERM_S_RX				(MK_TRICORE_PERM_READ|MK_TRICORE_PERM_EXECUTE)
#define MK_MPERM_S_RW				(MK_TRICORE_PERM_READ|MK_TRICORE_PERM_WRITE)
#define MK_MPERM_S_R				(MK_TRICORE_PERM_READ)
#define MK_MPERM_U_RX				(MK_TRICORE_PERM_READ|MK_TRICORE_PERM_EXECUTE)
#define MK_MPERM_U_RW				(MK_TRICORE_PERM_READ|MK_TRICORE_PERM_WRITE)
#define MK_MPERM_U_R				(MK_TRICORE_PERM_READ)


/* MPU register access functions for the MPU which was introduced with Aurix.
*/
#ifndef MK_ASM

struct mk_mpurange_s
{
	mk_uint32_t lower;
	mk_uint32_t upper;
};
typedef struct mk_mpurange_s mk_mpurange_t;

/* MPU register access functions.
 *
 * MK_DoSetCpr(index, lower, upper) - Sets lower and upper bound of CPR[index]. Returns zero on success.
 * MK_DoSetDpr(index, lower, upper) - Sets lower and upper bound of DPR[index]. Returns zero on success.
 * MK_DoSetCpxe(index, xe)          - Sets execute enable bits for PRS[index]. Returns zero on success.
 * MK_DoSetDprwe(index, re, we)     - Sets read and write enable bits for PRS[index]. Returns zero on success.
 * MK_DoGetCpxe(index)              - Returns the execute enable bits of PRS[index].
 * MK_DoGetDpr(index)               - Returns lower and upper bound of DPR[index].
 * MK_DoGetDprwe(index)             - Returns read and write enable bits of PRS[index].
 *
 * These are assembler helper functions for MK_HwSetStaticMemoryPartition.
 * They must only be called by the respective safety wrappers.
 *
 * The index argument of all functions must be valid, otherwise they return undefined values.
 *
 * These functions are only meant to be used during startup and are not optimized for performance.
 * In case a DoSet* functions is used when the MPU is enabled, perform a DSYNC before calling it.
*/
extern mk_uint32_t MK_DoGetCpxe(mk_uint32_t);
extern mk_mpurange_t MK_DoGetDpr(mk_uint32_t);
extern mk_mpurwpermission_t MK_DoGetDprwe(mk_uint32_t);
extern mk_uint32_t MK_DoSetCpr(mk_uint32_t, mk_address_t, mk_address_t);
extern mk_uint32_t MK_DoSetDpr(mk_uint32_t, mk_address_t, mk_address_t);
extern mk_uint32_t MK_DoSetCpxe(mk_uint32_t, mk_uint32_t);
extern mk_uint32_t MK_DoSetDprwe(mk_uint32_t, mk_uint32_t, mk_uint32_t);

#endif /* MK_ASM */


#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
