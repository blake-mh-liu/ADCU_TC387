/* Mk_k_initaddon.c
 *
 * This file contains the function MK_InitAddOn().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_addon.h>
#include <private/Mk_core.h>

/* MK_InitAddOn() initializes all the configured add-on modules.
 *
 * !LINKSTO Microkernel.Function.MK_InitAddOn, 1
 * !doctype src
*/
void MK_InitAddOn(mk_kernelcontrol_t *coreVars)
{
	mk_objectid_t i;

	/* Call the init function for each add-on that advertises one.
	*/
	for ( i = 0; i < MK_nAddOns; i++ )
	{
		if ( MK_addOnTable[i]->initFunc != MK_NULL )
		{
			(*MK_addOnTable[i]->initFunc)(coreVars, MK_addOnTable[i]);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
