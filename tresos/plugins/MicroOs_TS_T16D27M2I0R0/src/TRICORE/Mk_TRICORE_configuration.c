/* Mk_TRICORE_configuration.c
 *
 * Configuration constants for the TRICORE-specific part of the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 *  Expressions resulting from the expansion of macro parameters shall be
 *  enclosed in parentheses.
 *
 * Reason:
 *  The lack of parentheses is intentional, because they would lead to syntax
 *  errors in the constructed initializer.
*/

#include <public/Mk_public_types.h>
#include <private/TRICORE/Mk_TRICORE_memoryprotection.h>
#include <private/TRICORE/Mk_TRICORE_stm.h>
#include <private/TRICORE/Mk_TRICORE_wdt.h>
#include <private/TRICORE/Mk_TRICORE_Cfg.h>
#include <Mk_Cfg.h>
#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

mk_tricorestm_t * const MK_timestampStm = ((mk_tricorestm_t *)MK_TRICORE_TIMESTAMPSTMBASE);

/* MK_coreCsas - stores the address ranges, in which CSAs are allocated.
 * There is one range per core.
*/
const mk_tricorecsaentry_t MK_coreCsas[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(	MK_TRICORE_CSA_ENTRY_C0,
					MK_TRICORE_CSA_ENTRY_C1,
					MK_TRICORE_CSA_ENTRY_C2,
					MK_TRICORE_CSA_ENTRY_C3,
					MK_TRICORE_CSA_ENTRY_C4,
					MK_TRICORE_CSA_ENTRY_C5,
					MK_TRICORE_CSA_ENTRY_C6,
					MK_TRICORE_CSA_ENTRY_C7	)
};

/* MK_nStaticPartitions - stores the number of static partitions on the respective core.
*/
const mk_objquantity_t MK_nStaticPartitions[MK_MAXCORES] =
{
	MK_COREARRAY(	MK_CFG_C0_NSTATICPARTITIONS,
					MK_CFG_C1_NSTATICPARTITIONS,
					MK_CFG_C2_NSTATICPARTITIONS,
					MK_CFG_C3_NSTATICPARTITIONS,
					MK_CFG_C4_NSTATICPARTITIONS,
					MK_CFG_C5_NSTATICPARTITIONS,
					MK_CFG_C6_NSTATICPARTITIONS,
					MK_CFG_C7_NSTATICPARTITIONS	)
};

/* MK_nDynRegionsMax - stores the size of the largest dynamic partition per core
*/
const mk_objquantity_t MK_nDynRegionsMax[MK_MAXCORES] =
{
	MK_COREARRAY(	MK_CFG_C0_DYNREGIONS_MAX,
					MK_CFG_C1_DYNREGIONS_MAX,
					MK_CFG_C2_DYNREGIONS_MAX,
					MK_CFG_C3_DYNREGIONS_MAX,
					MK_CFG_C4_DYNREGIONS_MAX,
					MK_CFG_C5_DYNREGIONS_MAX,
					MK_CFG_C6_DYNREGIONS_MAX,
					MK_CFG_C7_DYNREGIONS_MAX	)
};

/* MK_cx_MemoryPartitionPermissions - stores the MPU permissions for the partitions
*/
mk_mpurwpermission_t * const MK_MemoryPartitionPermissions[MK_MAXCORES] =
{
	MK_COREARRAY(	MK_C0_MPUPERMISSONS,
					MK_C1_MPUPERMISSONS,
					MK_C2_MPUPERMISSONS,
					MK_C3_MPUPERMISSONS,
					MK_C4_MPUPERMISSONS,
					MK_C5_MPUPERMISSONS,
					MK_C6_MPUPERMISSONS,
					MK_C7_MPUPERMISSONS	)
};

/* MK_MpuRegCaches - stores pointers to each cores MPU region cache.
*/
mk_mpubounds_t * const MK_MpuRegCaches[MK_MAXCORES] =
{
	MK_COREARRAY(	MK_C0_MPUREGCACHE,
					MK_C1_MPUREGCACHE,
					MK_C2_MPUREGCACHE,
					MK_C3_MPUREGCACHE,
					MK_C4_MPUREGCACHE,
					MK_C5_MPUREGCACHE,
					MK_C6_MPUREGCACHE,
					MK_C7_MPUREGCACHE	)
};

/* MK_writeDynMpuRegs - stores pointers to the function for writing the dynamic regions'
 * MPU registers for each core.
*/
const mk_writedynmpuregsfunc_t MK_writeDynMpuRegs[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(	&MK_c0_WriteDynamicMpuRegisters,
					&MK_c1_WriteDynamicMpuRegisters,
					&MK_c2_WriteDynamicMpuRegisters,
					&MK_c3_WriteDynamicMpuRegisters,
					&MK_c4_WriteDynamicMpuRegisters,
					&MK_c5_WriteDynamicMpuRegisters,
					&MK_c6_WriteDynamicMpuRegisters,
					&MK_c7_WriteDynamicMpuRegisters	)
};

#if (MK_MPU_REGISTER_CHECK == 1)
/* MK_writeDynMpuRegs - stores pointers to the function for writing the dynamic regions'
 * MPU registers for each core, or MK_NULL if no readback is configured for a core.
*/
const mk_checkdynmpuregsfunc_t MK_checkDynMpuRegs[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-1 <+8> */
	MK_COREARRAY(	MK_C0_MPU_REGISTER_CHECK_FN,
					MK_C1_MPU_REGISTER_CHECK_FN,
					MK_C2_MPU_REGISTER_CHECK_FN,
					MK_C3_MPU_REGISTER_CHECK_FN,
					MK_C4_MPU_REGISTER_CHECK_FN,
					MK_C5_MPU_REGISTER_CHECK_FN,
					MK_C6_MPU_REGISTER_CHECK_FN,
					MK_C7_MPU_REGISTER_CHECK_FN	)
};
#endif

#if (MK_CFG_NSPINLOCKS > 0u)
/* Definition of spinlock variables:
 *
 * !LINKSTO Microkernel.TRICORE.Design.Spinlock.Types, 1
 * !doctype src
*/
mk_hwspinlockvar_t MK_tcSpinlock[MK_CFG_NSPINLOCKS];
#endif

mk_panicexceptionctx_t * const MK_panicExceptionCtxs[MK_MAXCORES] =
{
	MK_COREARRAY(	MK_C0_PANICEXCEPTIONCTX,
					MK_C1_PANICEXCEPTIONCTX,
					MK_C2_PANICEXCEPTIONCTX,
					MK_C3_PANICEXCEPTIONCTX,
					MK_C4_PANICEXCEPTIONCTX,
					MK_C5_PANICEXCEPTIONCTX,
					MK_C6_PANICEXCEPTIONCTX,
					MK_C7_PANICEXCEPTIONCTX	)
};

/* !LINKSTO Microkernel.TRICORE.IntIr.MK_CFG_OVERRIDE_INT_IR_CONFIG_DRIVER, 1
 * !doctype src
*/
#ifndef MK_CFG_OVERRIDE_INT_IR_CONFIG_DRIVER
#define MK_CFG_OVERRIDE_INT_IR_CONFIG_DRIVER 0
#endif
#if (!MK_CFG_OVERRIDE_INT_IR_CONFIG_DRIVER)
/* !LINKSTO Microkernel.TRICORE.IntIr.MK_intIrConfigDriver, 1
 * !doctype src
*/
const mk_int_ir_config_driver_t MK_intIrConfigDriver = MK_InitIntIrConfigDriver(
	&MK_ReconfigureSrnSrc, &MK_EnableIrq, &MK_DisableIrq);
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
