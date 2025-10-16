/* Mk_TRICORE_mpu_tc161.h - Tricore MPU header for tc1.6e/p cores (e.g. Aurix)
 *
 * This file contains definitions for the MPU on processors with the tc1.6e/p cores.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TRICORE_MPU_TC161_H
#define MK_TRICORE_MPU_TC161_H

#include <public/Mk_misra.h>
#include <private/TRICORE/Mk_TRICORE_mpu_common.h>

/* The MPU on the TC1.6E/TC1.6P cores has 16 data protection ranges (each containing a lower
 * and an upper bound register).
 *
*/

#define MK_TRICORE_NDPR				16			/* No of data protection regions */
#define MK_TRICORE_NCPR				8			/* No of code protection regions */
#define MK_TRICORE_MPU_FIXED_BITS	0x7			/* Fixed bits in the address registers */
#define MK_TRICORE_NPRS				4			/* No of protection register sets */


/* Fixed memory partitions
*/
#define MK_MEMPART_KERNEL		1

/* CSFR offsets for the MPU.
*/
#define MK_DPR0_L	0xc000
#define MK_DPR0_U	0xc004
#define MK_DPR1_L	0xc008
#define MK_DPR1_U	0xc00c
#define MK_DPR2_L	0xc010
#define MK_DPR2_U	0xc014
#define MK_DPR3_L	0xc018
#define MK_DPR3_U	0xc01c
#define MK_DPR4_L	0xc020
#define MK_DPR4_U	0xc024
#define MK_DPR5_L	0xc028
#define MK_DPR5_U	0xc02c
#define MK_DPR6_L	0xc030
#define MK_DPR6_U	0xc034
#define MK_DPR7_L	0xc038
#define MK_DPR7_U	0xc03c
#define MK_DPR8_L	0xc040
#define MK_DPR8_U	0xc044
#define MK_DPR9_L	0xc048
#define MK_DPR9_U	0xc04c
#define MK_DPR10_L	0xc050
#define MK_DPR10_U	0xc054
#define MK_DPR11_L	0xc058
#define MK_DPR11_U	0xc05c
#define MK_DPR12_L	0xc060
#define MK_DPR12_U	0xc064
#define MK_DPR13_L	0xc068
#define MK_DPR13_U	0xc06c
#define MK_DPR14_L	0xc070
#define MK_DPR14_U	0xc074
#define MK_DPR15_L	0xc078
#define MK_DPR15_U	0xc07c

#define MK_CPR0_L	0xd000
#define MK_CPR0_U	0xd004
#define MK_CPR1_L	0xd008
#define MK_CPR1_U	0xd00c
#define MK_CPR2_L	0xd010
#define MK_CPR2_U	0xd014
#define MK_CPR3_L	0xd018
#define MK_CPR3_U	0xd01c
#define MK_CPR4_L	0xd020
#define MK_CPR4_U	0xd024
#define MK_CPR5_L	0xd028
#define MK_CPR5_U	0xd02c
#define MK_CPR6_L	0xd030
#define MK_CPR6_U	0xd034
#define MK_CPR7_L	0xd038
#define MK_CPR7_U	0xd03c
#define MK_CPR8_L	0xd040
#define MK_CPR8_U	0xd044

#define MK_CPXE_0	0xe000
#define MK_CPXE_1	0xe004
#define MK_CPXE_2	0xe008
#define MK_CPXE_3	0xe00c

#define MK_DPRE_0	0xe010
#define MK_DPRE_1	0xe014
#define MK_DPRE_2	0xe018
#define MK_DPRE_3	0xe01c

#define MK_DPWE_0	0xe020
#define MK_DPWE_1	0xe024
#define MK_DPWE_2	0xe028
#define MK_DPWE_3	0xe02c


#ifndef MK_ASM

/* mk_mpurwpermission_t
 *
 * This is a struct that contain the permission register values for a
 * data protection register set (DPRE_x and DPWE_x).
 * It leaves out the CPXE-register which is never reprogrammed
 * during runtime. It is used to store the runtime permissions for all partitions
 * in MK_MemoryPartitionPermissions, from where it is loaded into the actual
 * processor registers by MK_cx_WriteDynamicMpuRegisters()
*/
struct mk_mpurwpermission_s
{
	mk_uint32_t dpre;
	mk_uint32_t dpwe;
};
typedef struct mk_mpurwpermission_s mk_mpurwpermission_t;

/* Contains the core-specific base pointers to the MPU partition permissions
 * The PRS1 permission register-values for all partitions are pre-calculated in the
 * referenced arrays
 * Note: the arrays are not const for performance reasons (RAM is faster than flash)
*/
extern mk_mpurwpermission_t * const MK_MemoryPartitionPermissions[];

/* Assembler function that reads dynamic MPU registers.
 *
 * The function has different entry points depending on the number of dynamic regions that
 * needs to be read on the given core.
*/
mk_uint32_t MK_c0_CheckDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
mk_uint32_t MK_c1_CheckDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
mk_uint32_t MK_c2_CheckDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
mk_uint32_t MK_c3_CheckDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);

/* Assembler function that writes dynamic MPU registers.
 *
 * The function has different entry points depending on the number of dynamic regions that
 * needs to be written on the given core.
*/
void MK_c0_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c1_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c2_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c3_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);

/* Contains, for each core, a function pointer to the MK_Read/WriteDynamicMpuRegisters function
 * used on that core.
*/
typedef void (*mk_writedynmpuregsfunc_t)(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
typedef mk_uint32_t (*mk_checkdynmpuregsfunc_t)(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
extern const mk_writedynmpuregsfunc_t MK_writeDynMpuRegs[MK_MAXCORES];
extern const mk_checkdynmpuregsfunc_t MK_checkDynMpuRegs[MK_MAXCORES];

#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
