/* Mk_sst.h
 *
 * Private API for the simple schedule table (SST) feature.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_SST_H
#define MK_SST_H

#include <public/Mk_defs.h>
#include <public/Mk_public_api.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_addon.h>
#include <private/Mk_core.h>

#include MK_HWSEL_PRV_SST

#ifndef MK_ASM

/* Enumerates SST counter states.
*/
enum mk_sststate_e
{
	MK_SST_STOPPED,
	MK_SST_STARTING,
	MK_SST_RUNNING
};
typedef enum mk_sststate_e mk_sststate_t;

/* The mk_sstaction_t structure specifies a counter value and what to do when the counter
 * reaches that value.
 * The only actions are ActivateTask and SetEvent, which can be specified by a task ID and an event word.
 * If the event word is zero the task is activated. A separate action selector is not required.
*/
struct mk_sstaction_s
{
	mk_tick_t counterValue;
	mk_objectid_t taskId;
	mk_uint32_t events;
};
typedef struct mk_sstaction_s mk_sstaction_t;

#define MK_SSTACTIONCONFIG(ct, task, evt) \
	{	(ct),		\
		(task),		\
		(evt)		\
	}

/* The mk_sstcounter_t structure is held in RAM. It contains all the configuration,
 * plus the dynamic status of the SST.
*/
struct mk_sstcounter_s
{
	mk_tick_t counterModulus;
	const mk_sstaction_t *actionTable;
	mk_objquantity_t nActions;
	mk_objectid_t tickerId;
	mk_tick_t reloadInterval;
	mk_sststate_t state;
	mk_tick_t currentCount;
	mk_objectid_t nextAction;			/* < 0 if the counter is not active */
};
typedef struct mk_sstcounter_s mk_sstcounter_t;

/* The mk_sstcountercfg_t structure contains the configured values and a pointer to the
 * runtime structure.
*/
struct mk_sstcountercfg_s
{
	mk_sstcounter_t *counter;			/* Address of the runtime structure */
	mk_tick_t counterModulus;			/* Wrap value (MaxAllowedValue+1) */
	const mk_sstaction_t *actionTable;	/* Base address of the global action table */
	mk_objquantity_t nActions;			/* No of action points in the global action table */
	mk_objectid_t tickerId;				/* Id of the ticker that's driving this SST (-1 if pure software) */
	mk_tick_t reloadInterval;			/* A reload interval for configuring the ticker, in hardware ticks! */
#if MK_MAXCORES > 1
	mk_objectid_t coreIndex;			/* The core on which the SST lives. */
#endif
};
typedef struct mk_sstcountercfg_s mk_sstcountercfg_t;

#if MK_MAXCORES > 1
#define MK_SSTCOUNTERCONFIG(ctr, mod, act, nact, tkr, rel, core) \
	{	(ctr),		\
		(mod),		\
		(act),		\
		(nact),		\
		(tkr),		\
		(rel),		\
		(core)		\
	}
#else
#define MK_SSTCOUNTERCONFIG(ctr, mod, act, nact, tkr, rel, core) \
	{	(ctr),		\
		(mod),		\
		(act),		\
		(nact),		\
		(tkr),		\
		(rel)		\
	}
#endif

extern const mk_objquantity_t MK_nSsts;
extern mk_sstcountercfg_t const * const MK_sstConfigsBase;

/* These are the private API functions of the SST feature.
*/
extern mk_errorid_t MK_LocalSstStartCounter(mk_sstcounter_t *, mk_tick_t);
extern mk_errorid_t MK_LocalSstStopCounter(mk_sstcounter_t *);
extern mk_errorid_t MK_LocalSstAdvanceCounter(mk_sstcounter_t *, mk_tick_t);
extern void MK_SstTickerInterruptHandler(mk_kernelcontrol_t *, mk_objectid_t, mk_hwvectorcode_t);
extern void MK_SstInit(const mk_kernelcontrol_t *);

#endif /* MK_ASM */
#endif /* MK_SST_H */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
