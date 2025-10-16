/* Mk_configuration_protectionaction.c
 *
 * This file contains the configuration for protection actions.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_errorhandling.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* This array contains function pointers to all available protection actions.
 * These are selected by the return value of the protection hook and started from
 * MK_PerformProtectionAction().
 *
 * Note: The members of this array must correspond to enum mk_protectionaction_e.
*/
const mk_ppafunction_t MK_ppaFunctions[MK_PRO_INVALIDACTION + 1] =
{
	MK_PpaContinue,						/* action for MK_PRO_CONTINUE */
	MK_PpaInvalidProtectionAction,		/* action for PRO_IGNORE */
	MK_PpaTerminateTaskIsr,				/* action for PRO_TERMINATETASKISR */
	MK_PpaTerminateApplication,			/* action for PRO_TERMINATEAPPL */
	MK_PpaTerminateApplicationRestart,	/* action for PRO_TERMINATEAPPL_RESTART */
	MK_PpaShutdown,						/* action for PRO_SHUTDOWN */
	MK_PpaTerminateThread,				/* action for MK_PRO_TERMINATE */
	MK_PpaInvalidProtectionAction,		/* action for MK_PRO_TERMINATEALL (not supported) */
	MK_PpaInvalidProtectionAction,		/* action for MK_PRO_QUARANTINE (not supported) */
	MK_PpaPanic,						/* action for MK_PRO_PANIC */
	MK_PpaPanicStop,					/* action for MK_PRO_PANICSTOP */
	MK_PpaInvalidProtectionAction		/* invalid action */
};

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
