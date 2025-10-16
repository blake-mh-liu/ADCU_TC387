/* Mk_configuration_addon.c
 *
 * This file contains the configured add-on table for the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_addon.h>
#include <Mk_gen_addons.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

const mk_objquantity_t MK_nAddOns = MK_CFG_NADDONS;

#if MK_CFG_NADDONS <= 0

/* A dummy add-on table. This avoids the need for an indirection pointer.
*/
const mk_addondescriptor_t * const MK_addOnTable[1] = { MK_NULL };

#else

const mk_addondescriptor_t * const MK_addOnTable[MK_CFG_NADDONS] = { MK_CFG_ADDONCONFIG	};

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
