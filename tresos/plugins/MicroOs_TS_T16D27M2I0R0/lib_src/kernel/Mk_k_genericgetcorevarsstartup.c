/* Mk_k_genericgetcorevarsstartup.c
 *
 * This file contains the MK_GenericGetCoreVarsStartup() function.
 *
 * If the generic mechanism is used, this file is compiled and the the macro MK_HwGetCoreVars
 * is mapped to the function in this file. The hardware specific header code must provide the function
 * or macro MK_HwGetCoreIndex() and the macro MK_HwSetCoreVars().
 *
 * If the hardware has a more efficient mechanism for looking up the core variables, this file is
 * not used. Instead, the hardware-specific code must provide its own analogous function and map it
 * to the macro MK_HwGetCoreVars.
 *
 * It is possible that this function is used at startup (to calculate the address of the core variables
 * and set up the hardware-specific mechanism).
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/Mk_panic.h>

#if MK_MAXCORES <= 1
#error "Mk_k_genericgetcorevarsstartup.c is not used in single-core systems. Check your makefiles!"
#endif

/* MK_GenericGetCoreVarsStartup() - return the core variables for the core that the code is running on.
 *
 * This function is used during startup.
 * It determines the address of the kernel control object of the current core
 * and initializes the hardware specific look-up by calling MK_HwSetCoreVars.
 *
 * The core variables are stored in a structure, Each core has its own structure that is placed in memory
 * that is private to the core. This means:
 *  - there is no cache contention between the cores
 *  - the private memory can be protected against write access from other cores
 *
 * The addresses of the core variables are held in an array with one entry per physical core. This assumes
 * that the core IDs returned by MK_HwGetCoreIndex start at zero and run sequentially. If this is not the
 * case, MK_HwGetCoreIndex must take care of that.
 *
 * If core variables are not available, the function calls MK_StartupPanic() and therefore does not return.
 *
 * !LINKSTO Microkernel.Function.MK_GenericGetCoreVarsStartup, 1
 * !doctype src
*/
mk_kernelcontrol_t *MK_GenericGetCoreVarsStartup(void)
{
	mk_objectid_t coreIndex;
	mk_kernelcontrol_t *coreVars = MK_NULL;

	coreIndex = MK_HwGetCoreIndex();

	if ( coreIndex < (mk_objquantity_t) MK_MAXCORES )
	{
		coreVars = MK_coreTable[coreIndex];

		if ( coreVars == MK_NULL )
		{
			MK_StartupPanic(MK_panic_CoreNotConfigured);
		}
		else
		{
			coreVars->coreIndex = coreIndex;
			coreVars->coreIndexLogical = MK_GetLogicalCoreId(coreIndex);
		}
	}
	else
	{
		MK_StartupPanic(MK_panic_UnexpectedHardwareResponse);
	}

	MK_HwSetCoreVars(coreVars);

	return coreVars;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
