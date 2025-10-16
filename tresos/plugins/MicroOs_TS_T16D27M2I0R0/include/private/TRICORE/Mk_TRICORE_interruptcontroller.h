/* Mk_TRICORE_interruptcontroller.h - TRICORE interrupt handling
 *
 * This file contains the TRICORE-specific part of the definitions for
 * interrupt handling.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.2 (required)
 * There shall be no dead code.
 *
 * Reason:
 * This code is required by the hardware protocol.
 */

#ifndef MK_TRICORE_INTERRUPTCONTROLLER_H
#define MK_TRICORE_INTERRUPTCONTROLLER_H

#include <public/Mk_hw_characteristics.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_startup.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <public/Mk_public_types.h>

/* We use 8-byte vectoring mode for the interrupt table, and a single interrupt vector that
 * is placed at an address that has bits [10:3] set to 1, so all priorities yield the same vector
 * address. This address is 2040 bytes beyond a 2048-byte aligned address.
 *
 * The interrupt sources are controlled by a set of "service request nodes". On some
 * processors they are placed in the address range of the peripherals with which they
 * are associated. On others they are gathered together in an array.
*/
#define   MK_BIV_VSS			1u

/* Defines which bits are checked on src readback
 * The lower 16 bits cover SRE, TOS and SRPN for all supported processors
*/
#if ((MK_TRICORE_CORE == MK_TRICORE_TC161) || (MK_TRICORE_CORE == MK_TRICORE_TC162))
#define MK_SRC_CHECK_MASK		0x0000ffffu
#else
#error "MK_SRC_CHECK_MASK needs to be defined for this core architecture."
#endif

/* Calculate the BIV value from the address by setting the VSS bit
*/
#define MK_INTVEC2BIV(table)	(((mk_uint32_t)(table)) | MK_BIV_VSS)

/* No. of interrupt vectors.
*/
#define MK_HWN_INTERRUPTVECTORS		255

/* Level at which all interrupts are enabled/disabled.
*/
#define MK_HWENABLEALLLEVEL			0
#define MK_HWONLYXCORELEVEL			254
#define MK_HWDISABLEALLLEVEL		255

/* SRN: The SRC register
 *
 * Configures interrupt priority and service provider. Additionally provides bits to
 * enable, disable, trigger, and clear the interrupt request.
*/

#define MK_SRC_SRPN_MASK	MK_U(0x000000ff)	/* Service request priority */
#define MK_SRC_SETR			MK_U(0x04000000)	/* Request set bit */
#define MK_SRC_CLRR			MK_U(0x02000000)	/* Request clear bit */
#define MK_SRC_SRR			MK_U(0x01000000)	/* Service request bit */
#define MK_SRC_SRE			MK_U(0x00000400)	/* Service request enable */
#define MK_SRC_SRPN			MK_U(0x000000ff)	/* Priority */
#define MK_SRC_SWSCLR		MK_U(0x40000000)	/* Clear SW sticky bit */

#if (MK_TRICORE_CORE == MK_TRICORE_TC161)
#define MK_SRC_TOS_MASK	MK_U(0x00001800)		/* Type of service aka interrupt target */
#define MK_SRC_ECC_MASK	MK_U(0x003f0000)		/* The ECC field */
#elif (MK_TRICORE_CORE == MK_TRICORE_TC162)
#define MK_SRC_TOS_MASK	MK_U(0x00003800)		/* Type of service aka interrupt target */
#define MK_SRC_ECC_MASK	MK_U(0x001f0000)		/* The ECC field */
#else
#error "Unexpected MK_TRICORE_CORE"
#endif
#define MK_SRC_TOS_SHIFT	MK_U(11)			/* Number of bits to shift core id to get TOS */
#define MK_SRC_ECC_SHIFT	MK_U(16)

#define MK_GetSrcSrpn(src) ((src) & MK_SRC_SRPN_MASK)
#define MK_GetSrcEcc(src)  (((src) & MK_SRC_ECC_MASK) >> MK_SRC_ECC_SHIFT)


/* MK_IR_INT_BASE - The base address of the interrupt controller on all currently supported derivatives. */
#define MK_IR_INT_BASE		MK_U(0xf0037000)

#ifndef MK_ASM
extern mk_reg32_t* const MK_TricoreXCoreSRC[MK_MAXCORES];
extern mk_uint32_t MK_TC3XX_GetCoreIrqTos(void);
#endif

/* MK_HwNotifyCore notifies the given core 'c' of incoming cross-core messages.
 * Argument c must be a valid core index.
 *
 * We don't expect lost update problems, since SRPN (priority),
 * SRE (enable), TOS ("service provider") aren't modified after startup,
 * because cross core interrupts can't be disabled and enabled during "runtime".
 * Other fields can't be written or are always read as 0.
 * Otherwise we must use AtomicOr (LDMST instruction) to set SETR.
 *
 * !LINKSTO Microkernel.TRICORE.Design.InterCoreNotification, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <+1> */
#define MK_HwNotifyCore(c)										\
	do {														\
		mk_reg32_t *hwNotifyCoreSrc = MK_TricoreXCoreSRC[(c)];	\
		*hwNotifyCoreSrc |= MK_SRC_SETR;						\
		/* read back the SRC register */						\
		*hwNotifyCoreSrc;										\
	} while (0)

/* There's nothing to do. SRR is automatically reset by hardware.
*/
#define MK_HwSignalEndOfInterrupt(vectorCode) do { } while(0)

#ifndef MK_ASM
typedef mk_uint32_t mk_hwvectorcode_t;
typedef mk_reg32_t  *mk_hwirqctrlreg_t;
#endif

/* The interrupt stub passes pcxi to the TRICORE interrupt dispatcher.
 *
 * MK_TricoreDispatchInterruptSoft() saves the pcxi to the current thread's register store,
 * then calls the generic soft interrupt dispatcher.
*/
#ifndef MK_ASM
void MK_TricoreDispatchInterruptSoft(mk_uint32_t);
#endif

#define MK_HwVectorCodeToInt(v)		(v)


/* MK_GetCoreIrqTos() yields the TOS (type of service) of the current core.
*/
#if (MK_TRICORE_CORE == MK_TRICORE_TC161)

#if MK_HWMAXCORES == 1
#define MK_GetCoreIrqTos()	0u
#else
#define MK_GetCoreIrqTos()	((mk_uint32_t)(((mk_uint32_t)MK_HwGetCoreIndex()) << MK_SRC_TOS_SHIFT))
#endif

#elif (MK_TRICORE_CORE == MK_TRICORE_TC162)

#if MK_HWMAXCORES == 1
#define MK_GetCoreIrqTos()	0u
#else
#define MK_GetCoreIrqTos()	MK_TC3XX_GetCoreIrqTos()
#endif

#else
#error "unsupported TriCore version"
#endif


/* ICU handling.
*/
#ifndef MK_ASM
typedef struct mk_int_icu_s mk_int_icu_t;
struct mk_int_icu_s
{
	const mk_reg32_t   lwsr;       /*< 0x00: Last winning service request. */
	const mk_reg32_t   lasr;       /*< 0x04: Last acknowledged service request. */
	mk_reg32_t         ecr;        /*< 0x08: Error capture register. */
	const mk_reg32_t   reserved0c; /*< 0x0c: reserved */
};
#endif

#if (MK_TRICORE_CORE == MK_TRICORE_TC161)
#define MK_INT_ICU_OFFS	MK_U(0x100)
#elif (MK_TRICORE_CORE == MK_TRICORE_TC162)
#define MK_INT_ICU_OFFS	MK_U(0x200)
#else
#error "Unsupported TriCore core"
#endif

#define MK_GetIcuRegsFromTosUnchecked(tos) (&(((mk_int_icu_t *)(MK_IR_INT_BASE + MK_INT_ICU_OFFS))[(tos)]))

/* MK_HAS_INVALID_TOS_VALUES - tells whether this derivative can have invalid TOS values.
 * MK_IsValidTosValue(value) - tells a value value` which was read using MK_SRC_TOS_MASK is a valid TOS value.
*/
#if (MK_TRICORE_CORE == MK_TRICORE_TC161)
/* On TC2xx value must be in 0 to 3, when it was read using MK_SRC_TOS_MASK. */
#if (MK_HWMAXCORES == 2)
/* On TC2xxs having two cores, valid TOS values are:
 * 0: CPU0
 * 1: CPU1
 * 3: DMA
*/
#define MK_HAS_INVALID_TOS_VALUES MK_TRUE
#define MK_IsValidTosValue(value) ((value) != 2u)
#else /* MK_HWMAXCORES */
/* On TC2xxs having one core, bit 12 of the TOS is always read as 0 and the valid TOS values are:
 * 0: CPU0
 * 1: DMA
 * On TC2xxs having three cores all values from 0 to 3 are valid TOS values:
 * 0: CPU0
 * 1: CPU1
 * 2: CPU2
 * 3: DMA
*/
#define MK_HAS_INVALID_TOS_VALUES MK_FALSE
#endif /* MK_HWMAXCORES */
#elif (MK_TRICORE_CORE == MK_TRICORE_TC162)
/* On TC3xx there's one TOS for each core and one for the DMA.
 * So the TOS value must be below `MK_HWMAXCORES + 1` to be valid.
*/
#define MK_HAS_INVALID_TOS_VALUES MK_TRUE
#define MK_IsValidTosValue(value) ((value) < (mk_unsigned_t)(MK_HWMAXCORES + 1))
#else /* MK_TRICORE_CORE */
#error "Unsupported TriCore core"
#endif /* MK_TRICORE_CORE */

/* MK_WaitForSrcUpdateInLwsrOfTos(tos, oldVal)
 * Calls MK_WaitForSrcUpdateInLwsr() if the TOS is valid. Otherwise there is nothing to wait for.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_WaitForSrcUpdateInLwsrOfTos, 1
*/
#if MK_HAS_INVALID_TOS_VALUES
#ifndef MK_ASM
/* This function checks the TOS value, which would result in unreachable branch and a compiler warning
 * on derivatives which don't have invalid TOS values.
*/
void MK_WaitForSrcUpdateInLwsrOfTos(mk_uint32_t, mk_uint32_t);
#endif
#else
/* If there are no invalid TOS values, we don't need a check.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_WaitForSrcUpdateInLwsrOfTos.InvalidTos, 1
*/
#define MK_WaitForSrcUpdateInLwsrOfTos(tos, oldVal)	\
	MK_WaitForSrcUpdateInLwsr(MK_GetIcuRegsFromTosUnchecked(tos), (oldVal))
#endif


#define MK_INT_LWSR_STAT_VALID_BIT  MK_U(0x80000000)
#define MK_INT_LWSR_PN_MASK         MK_U(0xff)
#if (MK_TRICORE_CORE == MK_TRICORE_TC161)
#define MK_INT_LWSR_ECC_MASKR       MK_U(0x3f)	/* The mask of the ECC field, shifted to the right. */
#elif (MK_TRICORE_CORE == MK_TRICORE_TC162)
#define MK_INT_LWSR_ECC_MASKR       MK_U(0x1f)	/* The mask of the ECC field, shifted to the right. */
#else
#error "Unsupported TriCore core"
#endif
#define MK_INT_LWSR_ECC_SHIFT       MK_U(10)
#define MK_INT_LWSR_ECC_MASK        (MK_ShiftLeftU32(MK_INT_LWSR_ECC_MASKR, MK_INT_LWSR_ECC_SHIFT))
#define MK_GetLwsrSrpn(lwsr)        ((lwsr) & MK_INT_LWSR_PN_MASK)
#define MK_GetLwsrEcc(lwsr)         (((lwsr) >> MK_INT_LWSR_ECC_SHIFT) & MK_INT_LWSR_ECC_MASKR)


/* Interrupt configuration.
*/
#ifndef MK_ASM
typedef void (*mk_init_irq_fn_t)(mk_reg32_t *, mk_uint32_t);
typedef void (*mk_enable_irq_fn_t)(mk_reg32_t *);
typedef void (*mk_disable_irq_fn_t)(mk_reg32_t *);

/* This structure holds the function pointers which are used to configure an individual interrupt source
 * in interrupt-controller hardware.
 * It might be overridden by the Embedded Hypervisor to para-virtualize the interrupt controller.
*/
typedef struct mk_int_ir_config_driver_s mk_int_ir_config_driver_t;
struct mk_int_ir_config_driver_s
{
	mk_init_irq_fn_t initIrq;
	mk_enable_irq_fn_t enableIrq;
	mk_disable_irq_fn_t disableIrq;
};
#define MK_InitIntIrConfigDriver(setup, enable, disable) { (setup), (enable), (disable) }

extern const mk_int_ir_config_driver_t MK_intIrConfigDriver;
void MK_InitIrq(mk_reg32_t *, mk_uint32_t);
void MK_EnableIrq(mk_reg32_t *);
void MK_DisableIrq(mk_reg32_t *);
#endif

/* Initialize the SRN by setting SRPN to the configured level, TOS to CPU, SRE to disabled (==zero).
 * Clears pending interrupt request using CLRR and SWSCLR.
*/
#define MK_HwInitIrq(irq) \
	do { \
		MK_intIrConfigDriver.initIrq((irq)->ctrlReg, (((irq)->level & MK_SRC_SRPN_MASK) | MK_GetCoreIrqTos() \
		                                        | MK_SRC_CLRR | MK_SRC_SWSCLR )); \
	} while (0)

#define MK_HwEnableIrq(irq) \
	do { \
		MK_intIrConfigDriver.enableIrq((irq)->ctrlReg); \
	} while (0)
#define MK_EnableIrqImpl(srnsrc) \
	do { \
		MK_SetAndCheckSrcValue((srnsrc), (*(srnsrc) | MK_SRC_SRE)); \
	} while (0)

#define	MK_HwDisableIrq(irq) \
	do { \
		MK_intIrConfigDriver.disableIrq((irq)->ctrlReg); \
	} while (0)
/* The (mk_uint32_t)-cast in the following macro is totally redundant on TRICORE, because
 * the bitmask is treated as 32-bit anyway. Its sole purpose is to fix MISRAs "underlying
 * type" for the bit-negation's operand to uint32.
*/
#define	MK_DisableIrqImpl(srnsrc) \
	do { \
		MK_SetAndCheckSrcValue((srnsrc), (*(srnsrc) & ~((mk_uint32_t)MK_SRC_SRE))); \
	} while (0)

#ifndef MK_ASM
void MK_SetupInterruptTable(mk_uint32_t);
void MK_HwInitInterruptController(mk_boolean_t);
void MK_SetAndCheckSrcValue(mk_hwirqctrlreg_t, mk_uint32_t);

void MK_ReconfigureSrnSrc(mk_reg32_t *, mk_uint32_t);
void MK_WaitForSrcUpdateInLwsr(mk_int_icu_t *, mk_uint32_t);
#endif

/* The generator assigns a unique level to each interrupt source and thus each vector is associated
 * with at most one interrupt source. Therefore the function MK_DispatchInterruptDemux is not required.
 * We link to the requirement here to show that we considered the requirement.
 *
 * !LINKSTO Microkernel.Function.MK_DispatchInterruptDemux, 1
 * !doctype src
*/

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
