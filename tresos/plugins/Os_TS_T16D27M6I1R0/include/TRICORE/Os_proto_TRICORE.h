/* Os_proto_TRICORE.h
 *
 * This file is the architecture-dependent prototype file for TRICORE
 *
 * The prototypes of kernel functions are in a separate file because they
 * are included in the Os_kernel.h file AFTER the generic types
 * have been defined, whereas the architecture-dependent types file is
 * included BEFORE the generic types are defined.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.2 (required)
 * There shall be no dead code.
 *
 * Reason:
 * This code is required by the hardware protocol. The intent is to flush
 * the instruction pipeline.
 */

#ifndef OS_PROTO_TRICORE_H
#define OS_PROTO_TRICORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Os_timestamp.h>

/* TRICORE kernel function prototypes
*/
#ifndef OS_ASM

void OS_StartTask(const os_task_t *) OS_ATTR_NO_INLINE;

void OS_TricoreCallIsr(const os_isr_t *, os_isrdynamic_t *);

void OS_Trap0Handler(void);
void OS_Trap1Handler(void);
void OS_Trap2Handler(void);
void OS_Trap3Handler(void);
void OS_Trap4Handler(void);
void OS_Trap5Handler(void);
void OS_Trap7Handler(void);

void OS_TricoreTakeSpinlock(os_syncspot_t *spinlockAddr);
void OS_TricoreStartCore(os_coreid_t);
void OS_InitCsaList(void);
#if (OS_TRICOREARCH==OS_TRICOREARCH_18)
void OS_KickStartCoreAurixTC18(void);
#endif
/* Function to initialise the local variables of SetProtection
*/
void OS_SetProtectionInit(void);

/* inline functions to deal with interrupt locking */

/* OS_IntEnable() sets the ICR to the "enable" state (IE=1, CCPN=0)
 * and returns the previous state.
*/
OS_QUAL_INLINE os_intstatus_t OS_IntEnable(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_intstatus_t OS_IntEnable(void)
{
	register os_uint32_t oldIcr = OS_MFCR(OS_ICR);
	OS_MTCR(OS_ICR, ((oldIcr & ~((os_uint32_t)OS_ICR_CCPN)) | OS_ICR_IE));
	return (os_intstatus_t) oldIcr;
}

/* OS_IntDisable() sets the ICR to the "disable" state (from the
 * constant OS_kernDisableLevel) and returns the previous state.
*/
#define OS_IntDisable() OS_TricoreIntDisableLevel(OS_kernDisableLevel)

OS_QUAL_INLINE os_intstatus_t OS_TricoreIntDisableLevel(os_intstatus_t dislevel) OS_ATTR_INLINE;
OS_QUAL_INLINE os_intstatus_t OS_TricoreIntDisableLevel(os_intstatus_t dislevel)
{
	register os_uint32_t oldIcr = OS_MFCR(OS_ICR);
	OS_MTCR(OS_ICR, ((oldIcr & ~(((os_uint32_t)OS_ICR_IE) | ((os_uint32_t)OS_ICR_CCPN))) | dislevel));
	return (os_intstatus_t) oldIcr;
}

/* OS_IntDisableConditional() sets the ICR to the "disable" state (from the
 * constant OS_kernDisableLevel) provided that by doing so the level does not get reduced,
 * and returns the previous state.
*/
OS_QUAL_INLINE os_intstatus_t OS_IntDisableConditional(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_intstatus_t OS_IntDisableConditional(void)
{
	register os_uint32_t macroTmpOldIcr = OS_MFCR(OS_ICR);
	if ( (macroTmpOldIcr & OS_ICR_CCPN) < (((os_uint32_t) OS_kernDisableLevel) & OS_ICR_CCPN) )
	{
		OS_MTCR(OS_ICR, ((macroTmpOldIcr & ~(((os_uint32_t)OS_ICR_IE) | ((os_uint32_t)OS_ICR_CCPN))) | OS_kernDisableLevel));
	}
	return (os_intstatus_t)macroTmpOldIcr;
}

/* OS_IntEnableXcore() sets the ICR to the "disable kernel but not cross-core" state (from the
 * constant OS_kernOnlyXcoreLevel) provided that by doing so the level does not get increased,
 * and returns the previous state.
*/
OS_QUAL_INLINE os_intstatus_t OS_IntEnableXcore(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_intstatus_t OS_IntEnableXcore(void)
{
	register os_uint32_t macroTmpOldIcr = OS_MFCR(OS_ICR);
	if ( (macroTmpOldIcr & OS_ICR_CCPN) > (((os_uint32_t) OS_kernOnlyXcoreLevel) & OS_ICR_CCPN) )
	{
		OS_MTCR(OS_ICR, ((macroTmpOldIcr & ~( ((os_uint32_t)OS_ICR_IE) | ((os_uint32_t)OS_ICR_CCPN))) | OS_kernOnlyXcoreLevel));
	}
	return (os_intstatus_t)macroTmpOldIcr;
}

/* OS_IntDisableAll() sets the ICR to the "disable" state (from the
 * constant OS_intDisableLevelAll) and returns the previous state.
*/
#define OS_IntDisableAll() OS_TricoreIntDisableLevel(OS_intDisableLevelAll)

/* OS_IntDisableMax() sets the ICR to the "disable" state (from the
 * constant OS_intDisableLevelMax) and returns the previous state.
*/
#define OS_IntDisableMax() OS_TricoreIntDisableLevel(OS_intDisableLevelMax)


/* OS_IntRestore() restores a previously-saved IE/CCPN status.
 * No value is returned.
*/
#define OS_IntRestore(p) \
	OS_MTCR(OS_ICR, ((OS_MFCR(OS_ICR) & ~(((os_uint32_t)OS_ICR_IE) | ((os_uint32_t)OS_ICR_CCPN))) | ( ((os_uint32_t)(p)) & (OS_ICR_IE | OS_ICR_CCPN))))

typedef void (*os_setup_interrupt_fn_t)(os_reg32_t *, os_uint32_t);
typedef void (*os_enable_interrupt_fn_t)(os_reg32_t *);
typedef void (*os_disable_interrupt_fn_t)(os_reg32_t *);
typedef void (*os_clear_interrupt_fn_t)(os_reg32_t *);

typedef struct os_int_ir_config_driver_s os_int_ir_config_driver_t;
struct os_int_ir_config_driver_s
{
	os_setup_interrupt_fn_t setupInterrupt;
	os_enable_interrupt_fn_t enableInterrupt;
	os_disable_interrupt_fn_t disableInterrupt;
	os_clear_interrupt_fn_t clearInterrupt;
};
#define OS_InitIntIrConfigDriver(setup, enable, disable, clear) { (setup), (enable), (disable), (clear) }

extern const os_int_ir_config_driver_t OS_intIrConfigDriver;
extern void OS_SetupIsrImpl(os_reg32_t *, os_uint32_t);
extern void OS_EnableIsrImpl(os_reg32_t *);
extern void OS_DisableIsrImpl(os_reg32_t *);
extern void OS_ClearIsrImpl(os_reg32_t *);

/* inline functions dealing with ISRs */
OS_QUAL_INLINE void OS_SetupIsrFn(const os_isr_t *isr) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_SetupIsrFn(const os_isr_t *isr)
{
	os_uint32_t coreId = (os_uint32_t)OS_TricoreGetCoreId();
	OS_intIrConfigDriver.setupInterrupt(isr->arch.srn, OS_SRN_TOSval(coreId) | isr->arch.arbPrio);
}

OS_QUAL_INLINE void OS_EnableIsrFn(const os_isr_t *isr) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_EnableIsrFn(const os_isr_t *isr)
{
	OS_intIrConfigDriver.enableInterrupt(isr->arch.srn);
}

OS_QUAL_INLINE void OS_DisableIsrFn(const os_isr_t *isr) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_DisableIsrFn(const os_isr_t *isr)
{
	OS_intIrConfigDriver.disableInterrupt(isr->arch.srn);
}

OS_QUAL_INLINE void OS_ClearIsrFn(const os_isr_t *isr) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_ClearIsrFn(const os_isr_t *isr)
{
	OS_intIrConfigDriver.clearInterrupt(isr->arch.srn);
}

OS_QUAL_INLINE void OS_TriggerIsrFn(const os_isr_t *isr) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_TriggerIsrFn(const os_isr_t *isr)
{
	*(isr->arch.srn) |= OS_SRN_SETR;
	/* Deviation MISRAC2012-1 <+1> */
	*(isr->arch.srn);
}

#endif

#ifdef __cplusplus
}
#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
