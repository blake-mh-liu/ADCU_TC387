/* Mk_configuration_interrupt.c
 *
 * This file contains the configuration for interrupt sources and ISRs.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_isr.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* Interrupt sources
 *
 * The set of configured interrupt sources is not necessarily the same as the set of ISRs because
 * interrupts can be handled directly by the microkernel.
 *
 * Note: MK_irqCfg can only be NULL if MK_nIrqs <= 0. This fact is used in the source code.
*/
const mk_objquantity_t MK_nIrqs = MK_CFG_NIRQS;
#if MK_CFG_NIRQS > 0
static const mk_irq_t MK_irqCfgTable[MK_CFG_NIRQS] = { MK_CFG_IRQLIST };
const mk_irq_t * const MK_irqCfg = MK_irqCfgTable;
#else
const mk_irq_t * const MK_irqCfg = MK_NULL;
#endif

/* ISRs
 *
 * The set of configured ISRs corresponds to a subset of the set of configured interrupt sources.
 * These are the ISRs defined by AUTOSAR.
 *
 * Note: MK_isrCfg can only be NULL if MK_nIsrs <= 0. This fact is used in the source code.
*/
const mk_objquantity_t MK_nIsrs = MK_CFG_NISRS;

#if MK_CFG_NISRS > 0
static const mk_isrcfg_t MK_isrCfgTable[MK_CFG_NISRS] = { MK_CFG_ISRLIST };
const mk_isrcfg_t * const MK_isrCfg = MK_isrCfgTable;
#else
const mk_isrcfg_t * const MK_isrCfg = MK_NULL;
#endif


/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
