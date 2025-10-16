/* Mk_lock.h - lock handling
 *
 * This file contains definitions for configuration and handling of locks. The abstract object "lock"
 * implements resources, spinlocks and interrupt locks.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_LOCK_H
#define MK_LOCK_H

#include <public/Mk_public_types.h>
#include <private/Mk_interrupt.h>	/* for mk_hwlocklevel_t */
#include <private/Mk_thread.h>
#include <private/Mk_types_forward.h>

#ifndef MK_ASM

/* Macros to extract lock index and core index from a lock ID
*/
#if MK_MAXCORES > 1
#define MK_LockIdToIndex(r)			((mk_lockid_t)((r) & 0xffffu))
#define MK_LockIdToCoreIndex(r)		((mk_lockid_t)((r) >> 16))
#else
#define MK_LockIdToIndex(r)			((mk_lockid_t)(r))
#define MK_LockIdToCoreIndex(r)		((mk_lockid_t)0u)
#endif

/* mk_lockcfgcommon_t contains all common fields of mk_lock_s and mk_lockcfg_s.
 * So it's that part of the configuration that is simply copied to RAM.
*/
typedef struct mk_lockcfgcommon_s mk_lockcfgcommon_t;
struct mk_lockcfgcommon_s
{
	mk_threadprio_t ceilingPriority;
	mk_hwlocklevel_t lockLevel;
	mk_int_t maxCount;
};

struct mk_lock_s
{
	mk_lockcfgcommon_t cfg;
#if MK_MAXCORES > 1
	mk_hwspinlock_t spinlock;
#endif

	mk_int_t count;
	mk_threadprio_t savedPrio;
	mk_hwlocklevel_t savedLevel;
	mk_lock_t *previousTaken;
	mk_thread_t *owner;
};

struct mk_lockcfg_s
{
	mk_lockcfgcommon_t common;
#if MK_MAXCORES > 1
	mk_hwspinlockcfg_t spinlockCfg;
#endif
	mk_objectid_t coreIndex;
	mk_objectid_t lockIndex;		/* Index into core's lock array. */
};

/* MK_LOCKCFG() - initialization macro for a lock config structure
 *
 * This macro should be used wherever a lockcfg is initialized, to permit changes
 * in the structure to be easily identified and fixed, and to permit
 * optimizations of the structure if necessary.
*/
#if MK_MAXCORES > 1
#define MK_LOCKCFG(cpri, lvl, maxc, sl, cor, idx) \
{				\
	{			\
		(cpri),	\
		(lvl),	\
		(maxc)	\
	},			\
	(sl),		\
	(cor),		\
	(idx)		\
}
#else
#define MK_LOCKCFG(cpri, lvl, maxc, sl, cor, idx) \
{				\
	{			\
		(cpri),	\
		(lvl),	\
		(maxc)	\
	},			\
	(cor),		\
	(idx)		\
}
#endif

/* Global configuration constants.
*/
extern const mk_objquantity_t MK_nLocksTotal;				/* Total number of locks in the config table. */
extern const mk_objquantity_t MK_nGlobalLocks;				/* Number of global locks. */
extern const mk_lockcfg_t MK_lockCfg[];						/* Array of MK_nLocksTotal lock configurations. */

extern const mk_objquantity_t MK_nLocks[MK_MAXCORES];		/* No of locks on each core */
extern mk_lock_t * const MK_lockTables[MK_MAXCORES];		/* Lock arrays (one per core) */

void MK_InitLocks(mk_objectid_t);
mk_hwlocklevel_t MK_ClearLockList(mk_lock_t *);
void MK_ClearLocks(void);

/* MK_ClearSpinlocks helps MK_ClearLocks to clear spinlocks.
 * For single-core machines, there's nothing to do.
*/
#if MK_MAXCORES > 1
void MK_ClearSpinlocks(const mk_kernelcontrol_t *);
#else
#define MK_ClearSpinlocks(coreVars) do { } while (0)
#endif

/* MK_GetLockObjectFromId gets the actual lock object belonging to the given index (helper).
*/
#if MK_MAXCORES > 1
#define MK_GetLockObjectFromId MK_GetLockObjectFromIdMulti
mk_lock_t *MK_GetLockObjectFromIdMulti(const mk_kernelcontrol_t *, mk_lockid_t, mk_errorid_t *);
#else
#define MK_GetLockObjectFromId(coreVars, lockId, pError) MK_GetLockObjectFromIdSingle((lockId),(pError))
mk_lock_t *MK_GetLockObjectFromIdSingle(mk_lockid_t, mk_errorid_t *);
#endif

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
