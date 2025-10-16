/* Mk_TRICORE_hwsetcorevars.c
 *
 * This file contains the function MK_HwSetCoreVars()
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MK_NULL */
#include <public/Mk_public_types.h>
/* MK_MAXCORES */
#include <public/Mk_hw_characteristics.h>
/* MK_panic_ */
#include <public/Mk_error.h>

#include <private/Mk_core.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>

#if MK_MAXCORES <= 1
#error "Mk_TRICORE_hwsetcorevars.c is not used in single-core systems. Check your makefiles!"
#endif

/* MK_HwSetCoreVars() - Sets A9.
 *
 * Parameters:
 *	- argCoreVars:  The value which shall be written to register A9
 *	                (must be the address of this core's kernel control object).
 * Return:
 *	If this function returns it has written 'argCoreVars' to register A9.
 *
 * The sequence "set GW, set A9" should not appear in code,
 * because this way a broken supervisor thread could accidentally jump there and corrupt A9.
 * Therefore, this function can only set A9 to the respective entry in MK_coreTable:
 *	- Set the GW bit.
 *	- Determine the kernel control object of the current core.
 *	- Let A9 point to the kernel control object, which was just determined.
 *	- Clear the GW bit, so A9 can't be written anymore.
 *	- Check whether the given argument was correct.
 *
 * We set A9 no matter whether the argument is correct, because there is only one valid value for A9.
 *
 * MK_coreTable must not be addressed indirectly via a global address register (like A0, A1, A8),
 * because these registers could be corrupted (this would only happen if the MK used small data areas on TriCore).
 *
 * Registers A8 and A9 are meant for global addresses of the OS.
 * Register A8 is already used by the counter subsystem (currently not needed in the Safety OS).
 *
 * !LINKSTO Microkernel.TRICORE.FunctionSpec.MK_HwSetCoreVars, 1
 * !doctype src
*/
void MK_HwSetCoreVars(mk_kernelcontrol_t *argCoreVars)
{
	mk_kernelcontrol_t *actualCoreVars = MK_NULL;

	/* The code written between setting and clearing the GW bit must not be moved outside of this section.
	 * The assembler statements and the memory barriers prevent the compiler from moving this code.
	 * MK_coreTable must not be addressed indirectly via a global address register (like A0, A1, A8).
	*/
	MK_MTPSW(MK_MFPSW() | ((mk_uint32_t)MK_PSW_GW));
	{
		mk_objectid_t coreId;

		MK_CompilerMemBarrier(MK_coreTable);

		coreId = MK_HwGetCoreIndex();
		actualCoreVars = MK_coreTable[coreId];
		MK_MTA9(actualCoreVars);
	}
	MK_MTPSW(MK_MFPSW() & ~((mk_uint32_t)MK_PSW_GW));

	/* If a wrong argument was passed, we panic.
	*/
	if (argCoreVars != actualCoreVars)
	{
		MK_StartupPanic(MK_panic_StartupCheckFailed);
	}
}
