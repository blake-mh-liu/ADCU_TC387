/* Mk_k_sysgetappmodevoteofcore.c
 *
 * This file contains the function MK_SysGetAppModeVoteOfCore().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>

/* MK_SysGetAppModeVoteOfCore() - returns the app mode of the given core.
 *
 * !LINKSTO Microkernel.Function.MK_SysGetAppModeVoteOfCore, 1
 * !doctype src
*/
void MK_SysGetAppModeVoteOfCore(mk_kernelcontrol_t *coreVars)
{
	mk_appmodeid_t appMode;
	mk_thread_t *caller = coreVars->currentThread;

	/* Intentional deviation from standard system call parameter handling.
	 * See ASCMICROOS-4019 for details.
	*/
	mk_objectid_t coreId = (mk_objectid_t)MK_HwGetParameter1(caller->regs);

	appMode = MK_InternGetAppModeVoteOfCore(coreId);
	MK_HwSetReturnValue1(caller->regs, appMode);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
