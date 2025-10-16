/* Mk_k_startupcheckcorevars.c
 *
 * This file contains the MK_StartupCheckCoreVars() function.
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_startup.h>
#include <private/Mk_panic.h>
#include <private/Mk_core.h>


/* MK_StartupCheckCoreVars
 *
 * Check structure offsets of mk_kernelcontrol_t
 * with offset definitions for assembly language.
*/
void MK_StartupCheckCoreVars(void)
{
	if (   (MK_OFFSETOF(mk_kernelcontrol_t, currentThread) != MK_CV_CURRTHREAD)
		|| (MK_OFFSETOF(mk_kernelcontrol_t, kernelStackTop) != MK_CV_KSTACKTOP)
		|| (MK_OFFSETOF(mk_kernelcontrol_t, currentMemoryPartition) != MK_CV_CURRMEMPAR)
		)
	{
		MK_StartupPanic(MK_panic_StartupCheckFailed);
		/* NOT REACHED */
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
