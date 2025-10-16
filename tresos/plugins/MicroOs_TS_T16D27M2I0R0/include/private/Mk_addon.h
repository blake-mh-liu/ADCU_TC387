/* Mk_addon.h - add-on framework configuration and handling
 *
 * This file contains definitions for configuration and handling optional modules (Add-Ons).
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_ADDON_H
#define MK_ADDON_H

#include <public/Mk_public_types.h>
#include <private/Mk_types_forward.h>

#ifndef MK_ASM

/* Forward definition of descriptor structure type.
*/
typedef struct mk_addondescriptor_s mk_addondescriptor_t;

/* Function pointer type for the add-on's control function.
*/
typedef mk_statusandvalue_t (*mk_addoncontrolfunc_t)(mk_kernelcontrol_t *, const mk_addondescriptor_t *,
														mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

/* Function pointer type for the add-on's initialization function.
*/
typedef void (*mk_addoninitfunc_t)(mk_kernelcontrol_t *, const mk_addondescriptor_t *);

/* The add-on descriptor structure. Every add-on module provides one of these.
*/
struct mk_addondescriptor_s
{
	const mk_char_t *name;
	mk_objectid_t addonId;
	mk_addoncontrolfunc_t ctrlFunc;
	mk_addoninitfunc_t initFunc;
	void *addonData;
};

/* Configuration items.
 *	MK_nAddOns		-- no. of add-on modules in use.
 *	MK_addOnTable	-- table of pointers to the descriptors of the modules in use.
 *
 * If there are no modules, MK_addOnTable should contain a single entry of MK_NULL
*/
extern const mk_objquantity_t MK_nAddOns;
extern const mk_addondescriptor_t * const MK_addOnTable[];

/* A macro to initialise the descriptor declared by the module.
*/
#define MK_ADDONCONFIG(name, id, ctrlfunc, initfunc, data) \
	{	(name),			\
		(id),			\
		(ctrlfunc),		\
		(initfunc),		\
		(void *)(data)	\
	}

/* Initialize the add-on handler and all the configured add-on modules.
*/
void MK_InitAddOn(mk_kernelcontrol_t *);

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
