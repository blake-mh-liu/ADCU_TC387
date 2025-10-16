/* Mk_TRICORE_core.h - Tricore core header
 *
 * This file contains definitions for features that are common across all
 * the Tricore architectures.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The core variables may be stored in memory to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#ifndef MK_TRICORE_CORE_H
#define MK_TRICORE_CORE_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>
#include <public/Mk_public_types.h>
#include <private/Mk_tool.h>
#include <private/Mk_types_forward.h>
#include <private/TRICORE/Mk_TRICORE_mpu.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>

/* Using the compiler-specific MK_MFCR and MK_MTCR macros might results in a MISRA violation at that location.
 * By defining inline functions we can justify all violations here.
*/
#ifndef MK_ASM

/* MK_MFPSW() and MK_MTPSW() read from and write to the PSW register.
*/
#define MK_MFPSW()		(MK_MFCR(MK_PSW))
#define MK_MTPSW(val)	do { MK_MTCR(MK_PSW, (val)); } while (0)

/* MK_MTFCX() writes the content of the specified variable to the FCX register.
*/
#define MK_MTFCX(val)			\
	do	{						\
		MK_DSYNC();				\
		MK_MTCR(MK_FCX, (val));	\
	} while (0)

/* MK_MTLCX() writes the content of the specified variable to the LCX register.
*/
#define MK_MTLCX(val)			\
	do	{						\
		MK_DSYNC();				\
		MK_MTCR(MK_LCX, (val));	\
	} while (0)

/* MK_MTTPS_CON() writes the content of the specified variable to the TPS_CON register.
*/
#define MK_MTTPS_CON(val)			\
	do	{							\
		MK_MTCR(MK_TPS_CON, (val));	\
	} while (0)

/* MK_MTTPS_TIMER0() writes the content of the specified variable to the TPS_TIMER0 register.
*/
#define MK_MTTPS_TIMER0(val)			\
	do	{								\
		MK_MTCR(MK_TPS_TIMER0, (val));	\
	} while (0)


/* MK_TricoreGetCoreIndex() reads the content of the CORE_ID core special function register.
 *
 * The CORE_ID register is 32 bit wide, so we read it as uint32.
 * Bits 31 down to 3 are "reserved", so we can't be sure they are read as 0, hence, we mask them.
*/
#if (MK_MAXCORES > 5)
MK_ATTR_NO_STACKPROT mk_uint32_t MK_TricoreGetCoreIndex(void);
#else
MK_QUAL_INLINE mk_uint32_t MK_TricoreGetCoreIndex(void) MK_ATTR_INLINE;
MK_QUAL_INLINE mk_uint32_t MK_TricoreGetCoreIndex(void)
{
	mk_uint32_t coreId = MK_MFCR(MK_CORE_ID) & 7u;
	return coreId;
}
#endif


/* On Aurix caches must not be used for shared variables (SM_AURIX_16).
 * Shared variables must be mapped to uncached memory segments.
 * Therefore no cache flush or invalidate is needed.
 * However these macros must form a compiler memory barrier,
 * so memory accesses before and after them are not reordered.
 * Moreover a DSYNC instruction is issued, to make sure that the processor
 * also does not reorder these memory accesses.
 *
 * CacheFlush is used to publish all previously done modifications to other cores.
 * CacheInvalidate is used before reading a variable which could have been written by other cores.
*/
#define MK_HwCacheFlush(a, l) do { \
		MK_CompilerMemBarrier(a); \
		MK_DSYNC(); \
	} while (0)
#define MK_HwCacheInvalidate(a, l) do { \
		MK_DSYNC(); \
		MK_CompilerMemBarrier(a); \
	} while (0)

#endif /* MK_ASM */


#ifndef MK_ASM

/* TRICORE specific kernel control variables
 *
 * !LINKSTO Microkernel.TRICORE.HwAbstraction.MK_HW_HAS_KERNELCONTROL, 1
*/
#define MK_HW_HAS_KERNELCONTROL		1
typedef struct mk_hwkernelcontrol_s mk_hwkernelcontrol_t;
struct mk_hwkernelcontrol_s
{
	/* Points to this core's MPU region cache. */
	mk_mpubounds_t *mpuRegCache;
	/* Number of static partitions on this core .*/
	mk_objquantity_t nStaticPartitions;
	/* Index of the last used dynamic partition. */
	mk_objectid_t lastDynamicPartition;
	/* Points to this core's partition permission array */
	const mk_mpurwpermission_t *memPartitionPermissions;
};

/* The lock level is only 8 bits but we define it to be 32 bits
 * for efficiency
*/
typedef mk_uint32_t mk_hwlocklevel_t;

/* Define lowerctx and upperctx.
 * Note that mk_lowerctx_t and mk_upperctx_t are declared in a public header,
 * because they are referenced by public structs.
*/

/* Registers in the lower context (as saved by RSLCX and BISR instructions)
*/
struct mk_lowerctx_s
{
	mk_uint32_t pcxi;
	mk_uint32_t pc;			/* a11: pc where the exception occurred */
	mk_uint32_t a2;
	mk_uint32_t a3;
	mk_uint32_t d0;
	mk_uint32_t d1;
	mk_uint32_t d2;
	mk_uint32_t d3;
	mk_uint32_t a4;
	mk_uint32_t a5;
	mk_uint32_t a6;
	mk_uint32_t a7;
	mk_uint32_t d4;
	mk_uint32_t d5;
	mk_uint32_t d6;
	mk_uint32_t d7;
};

/* Registers in the upper context (as saved by the CALL instruction and by traps and interrupts)
*/
struct mk_upperctx_s
{
	mk_uint32_t pcxi;
	mk_uint32_t psw;
	mk_uint32_t sp;			/* a10 */
	mk_uint32_t ra;			/* a11: return address of the caller or interrupted function! */
	mk_uint32_t d8;
	mk_uint32_t d9;
	mk_uint32_t d10;
	mk_uint32_t d11;
	mk_uint32_t a12;
	mk_uint32_t a13;
	mk_uint32_t a14;
	mk_uint32_t a15;
	mk_uint32_t d12;
	mk_uint32_t d13;
	mk_uint32_t d14;
	mk_uint32_t d15;
};

typedef struct mk_panicexceptionctx_s mk_panicexceptionctx_t;
struct mk_panicexceptionctx_s
{
	mk_lowerctx_t lower;
	mk_upperctx_t upper;
};
extern mk_panicexceptionctx_t * const MK_panicExceptionCtxs[MK_MAXCORES];

/* MK_AllocateTwoCsas() - grab two CSAs from the free list (assembly language)
*/
mk_uint32_t MK_AllocateTwoCsas(void);

/* MK_SwapFcx() - inserts a CSA list into the free list (assembly language)
*/
void MK_SwapFcx(mk_uint32_t, mk_uint32_t *);

/* MK_HwGetCoreVars()/MK_HwGetCoreVarsStartup()/MK_HwGetCoreVarsFromThread()
 *
 * MK_HwGetCoreVars() and MK_HwGetCoreVarsFromThread() retrieve the address
 * of the current core's kernel control data from register A9.
 *
 * MK_HwGetCoreVarsStartup() determines the address of the current core's
 * kernel control data during startup (before A9 has been set).
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwGetCoreVars, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1> */
#define MK_HwGetCoreVars()				((mk_kernelcontrol_t*)MK_MFA9())
#define MK_HwGetCoreVarsStartup()		MK_GenericGetCoreVarsStartup()
/* Deviation MISRAC2012-1 <+1> */
#define MK_HwGetCoreVarsFromThread()	((mk_kernelcontrol_t*)MK_MFA9())

/* MK_TricoreGetCoreVarsException() - check and get the core variables while entering an exception handler.
 *
 * This function makes sure that the core variables (in A9) are correct.
 * This can be done by checking or overriding them.
 * Call this function before any other function that uses the core variables,
 * if you expect the core variables to be corrupted.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_TricoreGetCoreVarsException, 1
 * !doctype src
*/
#define MK_TricoreGetCoreVarsException()	MK_GetCoreVarsStartup()

/* MK_HwSetCoreVars()
 *
 * !LINKSTO Microkernel.TRICORE.FunctionSpec.MK_HwSetCoreVars, 1
 * !doctype src
*/
extern void MK_HwSetCoreVars(mk_kernelcontrol_t *);

/* MK_HwGetCoreIndex
 *
 * Get the core index of the calling core.
 * If the respective derivative has only one core, we know at compile time
 * that the index is always zero.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwGetCoreIndex, 3
 * !doctype src
*/
#if (MK_HWMAXCORES > 1)
#define MK_HwGetCoreIndex()				((mk_objectid_t)MK_TricoreGetCoreIndex())
#else
#define MK_HwGetCoreIndex()				((mk_objectid_t)0)
#endif

#endif

/* The PCXI register
 *
 * This register (and the copies of it in the lower and upper contexts)
 * has the following bit fields:
*/
#define MK_PCX_PCXO				0x0000ffffu			/* Index of CSA in the "array" located at the segment base */
#define MK_PCX_PCXO_SHFT		6					/* No. of bits to shift PCXO to make a pointer */
#define MK_PCX_PCXS				0x000f0000u			/* Segment base, shifted right 12 bits */
#define MK_PCX_PCXS_SHFT		12					/* No. of bits to shift PCXS to make a pointer */
#define MK_PCX_CSA_MASK			(MK_PCX_PCXO|MK_PCX_PCXS)	/* All bits used to get the address of a CSA */

#define MK_CSA_MASK				0xf03fffc0u			/* Bits of an address used to identify a CSA */

#define	MK_PCX_PCPN				0x3fc00000u
#define MK_PCX_PCPN_SHFT		MK_U(22)
#define MK_PCX_PIE				0x00200000u
#define MK_PCX_PIE_SHFT			MK_U(21)
#define MK_PCX_UL				0x00100000u
#define MK_PCX_UL_SHFT			MK_U(20)

#ifndef MK_ASM
/* MK_PcxToAddr() converts the segment/index parts of a PCXI value to an address
 * MK_AddrToPcx() converts an address to the segment/index parts of a PCXI value
*/
#define MK_PcxToAddr(pcx)				MK_TricorePcxToAddr(pcx)
#define MK_AddrToPcx(addr)				MK_TricoreAddrToPcx(addr)

MK_QUAL_INLINE mk_address_t MK_TricorePcxToAddr(mk_uint32_t) MK_ATTR_INLINE;
MK_QUAL_INLINE mk_address_t MK_TricorePcxToAddr(mk_uint32_t pcx)
{
	return ( ( (pcx & MK_PCX_PCXS) << MK_PCX_PCXS_SHFT ) | ( (pcx & MK_PCX_PCXO) << MK_PCX_PCXO_SHFT ) );
}
MK_QUAL_INLINE mk_uint32_t MK_TricoreAddrToPcx(mk_address_t) MK_ATTR_INLINE;
MK_QUAL_INLINE mk_uint32_t MK_TricoreAddrToPcx(mk_address_t addr)
{
	return ( ( ( addr >> MK_PCX_PCXS_SHFT) & MK_PCX_PCXS ) | ( (addr >> MK_PCX_PCXO_SHFT) & MK_PCX_PCXO ) );
}
#endif

#define MK_GetPcpnFromPcxi(pcxi)	(((pcxi)&MK_PCX_PCPN) >> MK_PCX_PCPN_SHFT)
#define MK_SetPcpnInPcxi(pcxi,lvl)	(((pcxi)&~MK_PCX_PCPN) | (((mk_uint32_t)(lvl))<<MK_PCX_PCPN_SHFT))

/* Sets the part of the PCXI-register which is stored in an mk_hwps_t into a "real"
 * PCXI of a (mostly lower context) CSA
*/
#define MK_SetPsInPcxi(pcxi, pspscxi)  (((pcxi)&(~(MK_PCX_PCPN|MK_PCX_PIE))) | (pspscxi))

/* The PSW register
*/
#define MK_PSW_PRS			MK_U(0x00003000)	/* Protection register set (0..3; 2 and 3 are not used by the MK) */
#define MK_PSW_PRS_0		MK_U(0x00000000)	/* PRS 0 is used for the kernel */
#define MK_PSW_PRS_1		MK_U(0x00001000)	/* PRS 1 is used for threads */
#define MK_PSW_PRS_2		MK_U(0x00002000)	/* PRS 2 is used for fast partitions */
#define MK_PSW_PRS_3		MK_U(0x00003000)	/* PRS 3 is used for fast partitions */
#if MK_TRICORE_CORE == MK_TRICORE_TC162
#define MK_PSW_PRS_4		MK_U(0x00008000)	/* PRS 4 is used for fast partitions */
#define MK_PSW_PRS_5		MK_U(0x00009000)	/* PRS 5 is used for fast partitions */
#endif
#define MK_PSW_S			MK_U(0x00004000)	/* Safe task identifier */
#define MK_PSW_IO			MK_U(0x00000c00)	/* Access privilege (0..3; 3 is reserved) */
#define MK_PSW_IO_U0		MK_U(0x00000000)	/* User-0 mode (least privileged) */
#define MK_PSW_IO_U1		MK_U(0x00000400)	/* User-1 mode (more privileged) */
#define MK_PSW_IO_S			MK_U(0x00000800)	/* Supervisor mode */
#define MK_PSW_IS			MK_U(0x00000200)	/* Interrupt stack */
#define MK_PSW_GW			MK_U(0x00000100)	/* Global register write */
#define MK_PSW_CDE			MK_U(0x00000080)	/* Call depth counter enable */
#define MK_PSW_CDC			MK_U(0x0000007f)	/* Call depth counter mask */
#define MK_PSW_CDC_6		MK_U(0x00000000)	/* 6 bit CDC */
#define MK_PSW_CDC_5		MK_U(0x00000040)	/* 5 bit CDC */
#define MK_PSW_CDC_4		MK_U(0x00000060)	/* 4 bit CDC */
#define MK_PSW_CDC_3		MK_U(0x00000070)	/* 3 bit CDC */
#define MK_PSW_CDC_2		MK_U(0x00000078)	/* 2 bit CDC */
#define MK_PSW_CDC_1		MK_U(0x0000007c)	/* 1 bit CDC */
#define MK_PSW_CDC_T		MK_U(0x0000007e)	/* CDC trace mode */
#define MK_PSW_CDC_DIS		MK_U(0x0000007f)	/* CDC disabled */

/* The rounding mode resides in bits 24 and 25 of the PSW.
*/
#define MK_PSW_RM_ROUNDTONEAREST		MK_U(0x00000000)	/* Round to nearest. */
#define MK_PSW_RM_ROUNDTOWARDPLUSINF	MK_U(0x01000000)	/* Round towards positive infinity. */
#define MK_PSW_RM_ROUNDTOWARDMINUSINF	MK_U(0x02000000)	/* Round towards negative infinity. */
#define MK_PSW_RM_ROUNDTOWARDZERO		MK_U(0x03000000)	/* Round towards zero. */

/* PSW used in Mk_TRICORE_entry2
*/
#define MK_INITIAL_PSW		(MK_PSW_PRS_0 | MK_PSW_IO_S | MK_PSW_GW | MK_PSW_CDC_DIS )

/* The ICR register
*/
#define MK_ICR_CCPN			MK_U(0x000000ff)	/* Current CPU priority, 0..255 */
#define MK_ICR_IE			MK_U(0x00008000)	/* Interrupts enabled (global) */

/* The SYSCON register
 * (Note: this is the SYSCON CSFR, not the SCU.SYSCON register!)
*/
#define MK_SYSCON_FCDSF		MK_U(0x00000001)	/* Free context list depleted sticky flag */
#define MK_SYSCON_PROTEN	MK_U(0x00000002)	/* Memory protection enable */
#define MK_SYSCON_TPROTEN	MK_U(0x00000004)	/* Temporal protection enable */

/* The exception vector table
*/
#define MK_EXCVEC_MASK		0xffffff00u


#ifndef MK_ASM

/* Note: Spinlock variables must not be mapped to cached segments on Aurix (SM_AURIX_16)
 *
 * !LINKSTO Microkernel.TRICORE.Design.Spinlock.Types, 1
 * !doctype src
 */
typedef volatile mk_uint32_t mk_hwspinlockvar_t;
typedef mk_hwspinlockvar_t *mk_hwspinlock_t;
typedef mk_hwspinlockvar_t *mk_hwspinlockcfg_t;

/*
 * !LINKSTO Microkernel.TRICORE.Design.Spinlock.Configure, 1
 * !doctype src
*/
#define MK_HwLockHasSpinlock(r)		((r)->spinlock != MK_NULL)

/* MK_HwConfigureSpinlock
 *
 * Initializes the spinlock according to the given configuration.
 * Note: This function doesn't check the alignment of spinlock variables.
 * Note: On Aurix spinlocks must not reside in cached memory segments (SM_AURIX_16).
 *  It is the responsibility of the user to map them to suitable segments.
 *  This function doesn't check, whether caches are enabled on the containing segment
 *  (this would have to be done on every core).
 *  This function doesn't try to map the spinlock to an uncached segment.
 *
 * !LINKSTO Microkernel.TRICORE.Design.Spinlock.Configure, 1
 * !doctype src
*/
#define MK_HwConfigureSpinlock(res, rcfg)		\
	do {										\
		(res)->spinlock = (rcfg)->spinlockCfg;	\
	} while (0)

/* MK_TestAndTestAndSet() atomically sets the value stored at memory location 'addr' to 1,
 * after it tested that the value is 0. The value is tested before attempting the swap
 * operation as the swap operation induces a bus lock and therefore may impact performance
 * of other cores, if while waiting for a spinlock to be released this function is called
 * repeatedly in short intervals.
 *
 * If a call changes the value from 0 to 1, this call returns MK_TRUE.
 * Otherwise MK_FALSE is returned.
*/
MK_QUAL_INLINE mk_boolean_t MK_TestAndTestAndSet(volatile mk_uint32_t *) MK_ATTR_INLINE;
MK_QUAL_INLINE mk_boolean_t MK_TestAndTestAndSet(volatile mk_uint32_t *addr)
{
	mk_uint32_t value;

	value = *addr;
	if (value == 0u)
	{
		value = MK_AtomicSwap(addr, 1u);
	}
	return (value == 0u);
}


/* MK_HwTrySpinlock
 *
 * Tries to take spinlock 'l' once.
 * There's no need to invalidate cache-lines on Aurix (SM_AURIX_16)
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwTrySpinlock, 1
 * !doctype src
*/
#define MK_HwTrySpinlock(l)				MK_TestAndTestAndSet(l)

/* MK_HwDropSpinlock
 *
 * Releases spinlock 'l'.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwDropSpinlock, 1
 * !doctype src
*/
#define MK_HwDropSpinlock(l)			do { *(l) = 0u; } while(0)

/* MK_tcSpinlock
 *
 * Configuration dependent spinlock array.
*/
extern mk_hwspinlockvar_t MK_tcSpinlock[];

/* MK_HwGetSpinlockCfg
 *
 * Get the configuration value (see mk_hwspinlockcfg_t) of the i-th spinlock.
 *
 * !LINKSTO Microkernel.TRICORE.Design.Spinlock.Configure, 1
 * !doctype src
*/
#define MK_HwGetSpinlockCfg(i)			(&MK_tcSpinlock[(i)])

/* No additional stack needed */
#define MK_HW_STACK_EXTRA 0


/* MK_HwClearCoreVars - Sanitizes the TriCore kernel control variables during shutdown.
 *
 * !LINKSTO Microkernel.TRICORE.FunctionSpec.MK_HwClearCoreVars, 1
 * !doctype src
*/
void MK_HwClearCoreVars(mk_kernelcontrol_t *);

#endif /* MK_ASM */

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
