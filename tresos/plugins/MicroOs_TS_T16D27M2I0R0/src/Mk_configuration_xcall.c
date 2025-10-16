/* Mk_configuration_xcall.c
 *
 * This file contains the configured cross-core call table for the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_message.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* Cross-core call table
 *
 * At the moment this table contains fixed entries, i.e. all cross-core calls are
 * populated.
*/
mk_xcallfunction_t const MK_xcallTable[MK_MAX_OPCODE+1] =
{
	MK_XcoreActivateTask,
	MK_XcoreShutdown,
	MK_XcoreSetEvent,
	MK_XcoreCallCtrSub,
	MK_XcoreGetTaskState,
	MK_XcoreShutdown,					/* placeholder for MK_XcoreGetEvent */
	MK_XcoreShutdown,					/* placeholder for MK_XcoreDisableInterruptSource */
	MK_XcoreShutdown,					/* placeholder for MK_XcoreEnableInterruptSource */
	MK_XcoreTerminateApplication,
	MK_XcoreAsyncActivateTask,
	MK_XcoreAsyncActivateTask,			/* This is a ChainTask activation - identical apart from the service ID. */
	MK_XcoreAsyncSetEvent,
	MK_XcoreAsyncCallCtrSub,
	MK_XcoreStartCore,
	MK_XcoreReply
};

/* Handler functions for invalid cross-core messages
*/
const mk_invalidmessagehandler_t MK_invalidMessageHandler[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_MSG_INVALIDHANDLER,
				 MK_CFG_C1_MSG_INVALIDHANDLER,
				 MK_CFG_C2_MSG_INVALIDHANDLER,
				 MK_CFG_C3_MSG_INVALIDHANDLER,
				 MK_CFG_C4_MSG_INVALIDHANDLER,
				 MK_CFG_C5_MSG_INVALIDHANDLER,
				 MK_CFG_C6_MSG_INVALIDHANDLER,
				 MK_CFG_C7_MSG_INVALIDHANDLER)
};

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
