/* Mk_configuration_task.c
 *
 * This file contains the configuration for tasks.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_task.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* The task tables
 *
 * If there are no tasks, the task dynamic array, the threads and the register stores are not needed.
 *
 * Note: if MK_taskCfg is NULL, MK_nTasks is <= 0. This fact is used in the code.
*/
const mk_objquantity_t MK_nTasks = MK_CFG_NTASKS;

#if MK_CFG_NTASKS > 0

static const mk_taskcfg_t MK_taskCfgTable[MK_CFG_NTASKS] = { MK_CFG_TASKLIST };
const mk_taskcfg_t * const MK_taskCfg = MK_taskCfgTable;

#else

const mk_taskcfg_t * const MK_taskCfg = MK_NULL;

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
