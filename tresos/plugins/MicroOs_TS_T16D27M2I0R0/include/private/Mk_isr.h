/* Mk_isr.h - ISR configuration
 *
 * This file contains definitions used for the configuration of ISRs.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_ISR_H
#define MK_ISR_H

#include <private/Mk_thread.h>
#include <private/Mk_interrupt.h>
#include <public/Mk_basic_types.h>
#include <public/Mk_error.h>
#include <private/Mk_message.h>

#ifndef MK_ASM

/* Types and struct for ISR configuration and state.
*/
typedef struct mk_isr_s mk_isr_t;
typedef struct mk_isrcfg_s mk_isrcfg_t;

struct mk_isrcfg_s
{
	mk_threadcfg_t threadCfg;
	mk_thread_t *thread;
	mk_stackelement_t *stack;
	const mk_irq_t *irq;
	mk_isr_t *dynamic;
	mk_objectid_t ctrsubHwCounterId;
};

struct mk_isr_s
{
	mk_boolean_t enabled;		/* False (zero) means DISABLED, True (nonzero) means ENABLED */
};

/* Global constants for ISR configuration
*/
extern const mk_objquantity_t	MK_nIsrs;
extern const mk_isrcfg_t * const MK_isrCfg;

/* Construction macro for ISRs of various flavors
*/
#define MK_INTOBJCFG(typ, irq, thr, reg, dyn, name, cor, stk, sp, ent, pm, ilvl,	\
						ie, fpu, hws, qpri, rpri, partIdx, iid, exBgt, lkBgt, aid,	\
						counter)													\
{																					\
	MK_THREADCFG((reg), (name), (cor), (sp), (ent), (pm), (ilvl), (ie), (fpu),		\
					(hws), (qpri), (rpri), (partIdx), (iid), (typ),					\
					(exBgt), (lkBgt), (aid)),										\
	(thr),																			\
	(stk),																			\
	(irq),																			\
	(dyn),																			\
	(counter)																		\
}

#define MK_ISRCFG(irq, thr, reg, dyn, name, cor, stk, sp, ent, pm, ilvl, ie, fpu, hws,			\
						qpri, rpri, partIdx, iid, exBgt, lkBgt, aid)							\
	MK_INTOBJCFG(MK_OBJTYPE_ISR, (irq), (thr), (reg), (dyn), (name), (cor), (stk), (sp),		\
					(ent), (pm), (ilvl), (ie), (fpu), (hws), (qpri), (rpri), (partIdx), (iid),	\
					(exBgt), (lkBgt), (aid), (-1))

#define MK_CTRSUBISRCFG(irq, thr, reg, dyn, name, cor, stk, sp, ent, pm, ilvl, ie, fpu, hws,	\
						qpri, rpri, partIdx, iid, exBgt, lkBgt, aid, counter)					\
	MK_INTOBJCFG(MK_OBJTYPE_CTRSUBISR, (irq), (thr), (reg), (dyn), (name), (cor), (stk), (sp),	\
					(ent), (pm), (ilvl), (ie), (fpu), (hws), (qpri), (rpri), (partIdx), (iid),	\
					(exBgt), (lkBgt), (aid), (counter))

#endif

#ifndef MK_ASM
void MK_ClearIsrs(mk_objectid_t);
mk_errorid_t MK_LocalEnableInterruptSource(const mk_isrcfg_t *, mk_objectid_t);
mk_errorid_t MK_LocalDisableInterruptSource(const mk_isrcfg_t *, mk_objectid_t);

#if (MK_MAXCORES > 1)
/* MK_InternEnableInterruptSource() and MK_InternDisableInterruptSource() - multi-core version
 *
 * !LINKSTO Microkernel.Function.MK_InternEnableInterruptSource, 2
 * !LINKSTO Microkernel.Function.MK_InternDisableInterruptSource, 3
 * !doctype src
*/
mk_errorid_t MK_MultiEnableInterruptSource(mk_kernelcontrol_t *, mk_objectid_t, mk_objectid_t);
mk_errorid_t MK_MultiDisableInterruptSource(mk_kernelcontrol_t *, mk_objectid_t, mk_objectid_t);
#define MK_InternEnableInterruptSource(cv, i, a)		MK_MultiEnableInterruptSource((cv), (i), (a))
#define MK_InternDisableInterruptSource(cv, i, a)		MK_MultiDisableInterruptSource((cv), (i), (a))
#else
/* MK_InternEnableInterruptSource() and MK_InternDisableInterruptSource() - single-core version
 *
 * !LINKSTO Microkernel.Function.MK_InternEnableInterruptSource, 2
 * !LINKSTO Microkernel.Function.MK_InternDisableInterruptSource, 3
 * !doctype src
*/
#define MK_InternEnableInterruptSource(cv, i, a)		MK_LocalEnableInterruptSource(&MK_isrCfg[(i)], (a))
#define MK_InternDisableInterruptSource(cv, i, a)		MK_LocalDisableInterruptSource(&MK_isrCfg[(i)], (a))
#endif
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
