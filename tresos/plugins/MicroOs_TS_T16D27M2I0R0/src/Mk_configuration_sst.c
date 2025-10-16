/* Mk_configuration_sst.c - configuration for the SST feature
 *
 * This file contains the configuration for the simple schedule table feature.
 *
 * Configuration items:
 *	- a table of SST counter configuration structures
 *	- a table of SST action points (time/task-id/events-to-set)
 *	- a table of SST run-time counter structures (one table for each core that uses SSTs)
 *
 * (c) Elektrobit Automotive GmbH
*/
/* !LINKSTO Microkernel.Data.Configuration, 1
*/

#include <public/Mk_public_types.h>
#include <private/Mk_sst.h>
#include <Mk_Cfg.h>

/* The total number of SSTs.
*/
const mk_objquantity_t MK_nSsts = MK_CFG_NSSTS;

#if MK_CFG_NSSTS > 0

/* This table contains all the action points for all the simple schedule tables.
 * Each counter has a base pointer into this array and knows how many actions starting from
 * there belong to it.
*/
static const mk_sstaction_t MK_sstActions[MK_CFG_NSSTACTIONS] = { MK_CFG_SSTACTIONTABLE };

/* This table contains the configuration for all the SST counters.
 * Each configuration has a reference to a runtime counter structure.
*/
static const mk_sstcountercfg_t MK_sstConfigs[MK_CFG_NSSTS] = { MK_CFG_SSTCOUNTERTABLE };

mk_sstcountercfg_t const * const MK_sstConfigsBase = &MK_sstConfigs[0];

#else /* MK_CFG_NSST == 0 */

mk_sstcountercfg_t const * const MK_sstConfigsBase = MK_NULL;

#endif /*  MK_CFG_NSST > 0 */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
