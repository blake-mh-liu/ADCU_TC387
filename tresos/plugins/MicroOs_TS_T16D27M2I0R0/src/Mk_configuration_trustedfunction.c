/* Mk_configuration_trustedfunction.c
 *
 * This file contains the configuration for trusted functions.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_trustedfunction.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* Number of trusted functions configured by the user
*/
const mk_objquantity_t MK_nTrustedFunctions   = MK_CFG_NTRUSTEDFUNCTIONS;

/* Array of trusted functions defined by the user
*/
#if MK_CFG_NTRUSTEDFUNCTIONS > 0
static const mk_trustedfunctioncfg_t MK_trustedFunctionsTable[MK_CFG_NTRUSTEDFUNCTIONS]
																				= { MK_CFG_TRUSTEDFUNCTIONLIST };
const mk_trustedfunctioncfg_t * const MK_trustedFunctionCfg = MK_trustedFunctionsTable;
#else
const mk_trustedfunctioncfg_t * const MK_trustedFunctionCfg = MK_NULL;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
