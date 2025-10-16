/* Mk_k_clearisrs.c
 *
 * This file contains the MK_ClearIsrs function.
 *
 * This function is used during shutdown to clear the state of all ISRs on the specified core.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>
#include <private/Mk_isr.h>

/*
 * MK_ClearIsrs() clears ISR state (including thread state)
 *
 * !LINKSTO Microkernel.Function.MK_ClearIsrs, 1
 * !doctype src
*/
void MK_ClearIsrs(mk_objectid_t coreIndex)
{
	mk_objectid_t t;

	/* Look at all ISRs.
	*/
	for ( t = 0; t < MK_nIsrs; t++ )
	{
		/* Only clear down ISRs on the specified (calling) core.
		*/
		if ( MK_isrCfg[t].threadCfg.coreIndex == coreIndex )
		{
			/* Clear the associated thread. Shared threads will get cleared more than once - it's harmless.
			*/
			MK_ClearThread(MK_isrCfg[t].thread);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
