/* Mk_TRICORE_mpu_tc162.h - Tricore MPU header for TC1.6.2 cores (e.g. Aurix 2nd Generation)
 *
 * This file contains definitions for the MPU on processors with the TC1.6.2 core.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TRICORE_MPU_TC162_H
#define MK_TRICORE_MPU_TC162_H

#include <public/Mk_misra.h>
#include <private/TRICORE/Mk_TRICORE_mpu_common.h>

/* According to the TC1.6.2 architecture manual, the number of
 * protection registers is implementation dependent.
 * The TC3xx target specification implies that all TC3-derivatives
 * might have 18 data and 10 code protection regions
 * (each containing a lower and an upper bound register).
*/

#define MK_TRICORE_NDPR				18	/* Number of data protection regions */
#define MK_TRICORE_NCPR				10	/* Number of code protection regions */
#define MK_TRICORE_NPRS				6	/* Number of protection register sets */
#define MK_TRICORE_MPU_FIXED_BITS	0x7	/* Fixed bits in the address registers */

/* Fixed memory partitions
*/
#define MK_MEMPART_KERNEL		1

/* CPU Data Protection Ranges, (L)ower bound, (U)pper bound */
#define MK_DPR0_L	0xC000
#define MK_DPR0_U	0xC004
#define MK_DPR1_L	0xC008
#define MK_DPR1_U	0xC00C
#define MK_DPR2_L	0xC010
#define MK_DPR2_U	0xC014
#define MK_DPR3_L	0xC018
#define MK_DPR3_U	0xC01C
#define MK_DPR4_L	0xC020
#define MK_DPR4_U	0xC024
#define MK_DPR5_L	0xC028
#define MK_DPR5_U	0xC02C
#define MK_DPR6_L	0xC030
#define MK_DPR6_U	0xC034
#define MK_DPR7_L	0xC038
#define MK_DPR7_U	0xC03C
#define MK_DPR8_L	0xC040
#define MK_DPR8_U	0xC044
#define MK_DPR9_L	0xC048
#define MK_DPR9_U	0xC04C
#define MK_DPR10_L	0xC050
#define MK_DPR10_U	0xC054
#define MK_DPR11_L	0xC058
#define MK_DPR11_U	0xC05C
#define MK_DPR12_L	0xC060
#define MK_DPR12_U	0xC064
#define MK_DPR13_L	0xC068
#define MK_DPR13_U	0xC06C
#define MK_DPR14_L	0xC070
#define MK_DPR14_U	0xC074
#define MK_DPR15_L	0xC078
#define MK_DPR15_U	0xC07C
#define MK_DPR16_L	0xC080
#define MK_DPR16_U	0xC084
#define MK_DPR17_L	0xC088
#define MK_DPR17_U	0xC08C

/* CPU Code Protection Ranges, (L)ower bound, (U)pper bound */
#define MK_CPR0_L	0xD000
#define MK_CPR0_U	0xD004
#define MK_CPR1_L	0xD008
#define MK_CPR1_U	0xD00C
#define MK_CPR2_L	0xD010
#define MK_CPR2_U	0xD014
#define MK_CPR3_L	0xD018
#define MK_CPR3_U	0xD01C
#define MK_CPR4_L	0xD020
#define MK_CPR4_U	0xD024
#define MK_CPR5_L	0xD028
#define MK_CPR5_U	0xD02C
#define MK_CPR6_L	0xD030
#define MK_CPR6_U	0xD034
#define MK_CPR7_L	0xD038
#define MK_CPR7_U	0xD03C
#define MK_CPR8_L	0xD040
#define MK_CPR8_U	0xD044
#define MK_CPR9_L	0xD048
#define MK_CPR9_U	0xD04c

/* CPU Code Protection eXecute Enable register set */
#define MK_CPXE_0	0xE000
#define MK_CPXE_1	0xE004
#define MK_CPXE_2	0xE008
#define MK_CPXE_3	0xE00C
#define MK_CPXE_4	0xE040
#define MK_CPXE_5	0xE044

/* CPU Data Protection Read Enable register set */
#define MK_DPRE_0	0xE010
#define MK_DPRE_1	0xE014
#define MK_DPRE_2	0xE018
#define MK_DPRE_3	0xE01C
#define MK_DPRE_4	0xE050
#define MK_DPRE_5	0xE054

/* CPU Data Protection Write Enable register set */
#define MK_DPWE_0	0xE020
#define MK_DPWE_1	0xE024
#define MK_DPWE_2	0xE028
#define MK_DPWE_3	0xE02C
#define MK_DPWE_4	0xE060
#define MK_DPWE_5	0xE064

#ifndef MK_ASM

/* mk_mpurwpermission_t contains the permission register values for a
 * protection register set (DPRE_x DPWE_x).
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
mk_uint32_t MK_c4_CheckDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
mk_uint32_t MK_c5_CheckDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);

/* Assembler function that writes dynamic MPU registers.
 *
 * The function has different entry points depending on the number of dynamic regions that
 * needs to be written on the given core.
*/
void MK_c0_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c1_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c2_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c3_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c4_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);
void MK_c5_WriteDynamicMpuRegisters(const mk_mpubounds_t *, const mk_mpurwpermission_t *);

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
