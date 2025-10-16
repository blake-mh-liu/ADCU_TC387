/* Mk_configuration_application.c
 *
 * This file contains the configuration for applications.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_application.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

const mk_objquantity_t MK_nApps = MK_CFG_NAPPLICATIONS;

#if MK_CFG_NAPPLICATIONS > 0

/* MK_appCfgTable is an array that contains the configuration for each OS-Application.
 * MK_appCfg is the base address if this array, which can be NULL if no OS-Applications are configured.
*/
static const mk_appcfg_t MK_appCfgTable[MK_CFG_NAPPLICATIONS] = { MK_CFG_APPLIST };
const mk_appcfg_t * const MK_appCfg = MK_appCfgTable;

#else

/* No OS-Applications have been configured.
*/
const mk_appcfg_t * const MK_appCfg = MK_NULL;

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
