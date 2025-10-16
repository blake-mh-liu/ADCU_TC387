/* Mk_interrupt.h - interrupt handling
 *
 * This file contains definitions for the hardware-independent part of the
 * microkernel's interrupt handling. It also includes the hardware-specific
 * part.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_INTERRUPT_H
#define MK_INTERRUPT_H

#include <public/Mk_hwsel.h>
#include <public/Mk_public_types.h>
#include <private/Mk_types_forward.h>

#include MK_HWSEL_PRV_INTERRUPTCONTROLLER

#ifndef MK_ASM
typedef void (*mk_interruptfunc_t)(mk_kernelcontrol_t *, mk_objectid_t, mk_hwvectorcode_t);

struct mk_irq_s
{
	mk_hwirqctrlreg_t ctrlReg;
	mk_hwlocklevel_t level;
	mk_objectid_t coreIndex;
	mk_uint32_t flags;
};

/* Macro defining a control register.
 * This value can be updated in respective interrupt header file as required.
*/
#ifndef MK_HWIRQCTRLREG
#define MK_HWIRQCTRLREG(c)	(c)
#endif

/* Macro for defining an IRQ
*/
#define MK_IRQCFG(ctrlreg, level, coreIndex, flags) \
{	MK_HWIRQCTRLREG(ctrlreg),		\
	(level),		\
	(coreIndex),	\
	(flags)			\
}

/* Bits in flags
*/
#define MK_IRQ_ENABLE	0x00000001u		/* Enabled at startup */

/* Function prototypes
*/
void MK_UnknownInterrupt(mk_kernelcontrol_t *, mk_objectid_t, mk_hwvectorcode_t);
void MK_StartThreadForIsr(mk_kernelcontrol_t *, mk_objectid_t, mk_hwvectorcode_t);
void MK_StartThreadForCtrSubIsr(mk_kernelcontrol_t *, mk_objectid_t, mk_hwvectorcode_t);
void MK_CrossCoreMessageHandler(mk_kernelcontrol_t *, mk_objectid_t, mk_hwvectorcode_t);
void MK_InitInterrupts(mk_objectid_t, mk_boolean_t);

/* Global constants
*/
extern const mk_irq_t * const MK_irqCfg;
extern const mk_objquantity_t MK_nIrqs;

/* Cross-core notification macro
 * (empty by default).
*/
#ifndef MK_HwNotifyCoreClear
#define MK_HwNotifyCoreClear(coreVars)	do { } while (0)
#endif

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
