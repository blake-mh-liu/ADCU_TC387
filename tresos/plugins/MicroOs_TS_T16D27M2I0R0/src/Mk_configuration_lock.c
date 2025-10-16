/* Mk_configuration_lock.c
 *
 * This file contains the configuration for locks.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_lock.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* The Lock table
 *
 * This is the table of all external locks. i.e. those that can be acquired by calling
 * MK_UsrAcquireLock(). This includes standard resources, linked resources, RES_SCHEDULER, spinlocks and
 * the two interrupt locks. Internal locks do not appear in the table.
 *
 * Note: it is assumed that there is at least one lock (an interrupt lock),
 * so no provision is made for an empty lock table.
 *
 * The table contains locks for all cores. The initialization function copies the
 * values from this table to the per-core lock tables. For global locks there is
 * a copy for each core, thus permitting each core to have its own ceiling priorities and levels
 * for these locks.
*/
const mk_objquantity_t MK_nLocksTotal = MK_CFG_NLOCKS;
const mk_objquantity_t MK_nGlobalLocks = MK_CFG_NGLOBALLOCKS;
const mk_lockcfg_t MK_lockCfg[MK_CFG_NLOCKS] = { MK_CFG_LOCKLIST };

const mk_lockid_t MK_resLockCat1 = MK_RESCAT1;
const mk_lockid_t MK_resLockCat2 = MK_RESCAT2;

/* The per-core no-of-locks and lock tables (in RAM).
*/
const mk_objquantity_t MK_nLocks[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_NLOCKS,
				 MK_CFG_C1_NLOCKS,
				 MK_CFG_C2_NLOCKS,
				 MK_CFG_C3_NLOCKS,
				 MK_CFG_C4_NLOCKS,
				 MK_CFG_C5_NLOCKS,
				 MK_CFG_C6_NLOCKS,
				 MK_CFG_C7_NLOCKS)
};

mk_lock_t * const MK_lockTables[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_LOCKTABLE,
				 MK_CFG_C1_LOCKTABLE,
				 MK_CFG_C2_LOCKTABLE,
				 MK_CFG_C3_LOCKTABLE,
				 MK_CFG_C4_LOCKTABLE,
				 MK_CFG_C5_LOCKTABLE,
				 MK_CFG_C6_LOCKTABLE,
				 MK_CFG_C7_LOCKTABLE)
};

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
