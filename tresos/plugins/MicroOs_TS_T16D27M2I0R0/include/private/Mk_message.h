/* Mk_message.h
 *
 * Definitions for an inter-core message queue.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: Dir 4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
 *
 *
 * MISRAC2012-2) Deviated Rule: D4.5 (advisory)
 *  Identifiers in the same name space with overlapping visibility should be
 *  typographically unambiguous.
 *
 * Reason:
 *  The function's purpose is to handle the cross-core call to a MK function.
 *  To perform these cross-core calls, a message is sent and the function that
 *  shall be called is encoded using a constant. This constant is named
 *  similarly to this function, as it is designed to reference this function in
 *  a cross-core call message. Thus, the similarity in name is on purpose here,
 *  as both entities are closely related to one another.
*/

#ifndef MK_MESSAGE_H
#define MK_MESSAGE_H

#include <public/Mk_basic_types.h>
#include <private/Mk_types_forward.h>
#include <private/Mk_core.h>
#include <public/Mk_error.h>

#ifndef MK_ASM
/* Inter-core message queue.
 *
 * Each core has an outgoing message queue for each of the other cores. The queue consists of:
 *	- a message buffer.
 *	- an "insert" pointer that contains the address of the next free slot in the message buffer.
 *	- a "withdraw" pointer that contains the address of the first full slot in the message buffer.
 *
 * The message buffer and the insert pointer are writeable by the sender and read-only by the receiver.
 * The withdraw pointer is writeable by the receiver and read-only by the sender.
 *
 * The queue is empty when the insert pointer and the withdraw pointer are the same.
 * The queue is full when incrementing the insert pointer would cause it to be the same as the withdraw pointer.
 *
 * The message buffer is an array of n+1 message structures, where n is the largest number of
 * messages that can be queued at any time. This array is written by the sender and read by the
 * receiver.
 *
 * Messages:
 *
 * Each message in the queue contains a system-call identifier, an array of parameters and parameters, the
 * index of the core that sent the message and a cookie to identify the caller on the requesting core.
 *
 * Cookies:
 *
 * When a synchronous operations is initiated, a 16-bit cookie is created for the operation and stored in two places,
 * with different 32-bit encodings.
 *
 * Firstly, a "message cookie" is sent as part of the message. The encoding of the message cookie is such that the
 * bitwise-inverse of the 16-bit cookie is again stored in the upper half of the 32-bit message cookie. The message
 * cookie is sent back by the target core along with the result of the operation. The encoding provides some guard
 * against spurious messages received from a malfunctioning core.
 *
 * Secondly, while waiting for the answer, a "wait cookie" is stored on the sending core. The encoding  of the wait
 * cookie is such that the upper-half of the 32-bit value is used to store the core id of the target core. When a
 * reply is received for the cookie id, the core id can be checked against the id of the core the reply was
 * received from.
 *
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
/* Deviation MISRAC2012-1 <START>, MISRAC2012-2 <START> */
enum mk_xcall_e
{
	MK_xcore_ActivateTask = 0,
	MK_xcore_Shutdown,
	MK_xcore_SetEvent,
	MK_xcore_CallCtrSub,
	MK_xcore_GetTaskState,
	MK_xcore_GetEvent,
	MK_xcore_EnableInterruptSource,
	MK_xcore_DisableInterruptSource,
	MK_xcore_TerminateApplication,
	MK_xcore_AsyncActivateTask,
	MK_xcore_AsyncChainTask,
	MK_xcore_AsyncSetEvent,
	MK_xcore_AsyncCallCtrSub,
	MK_xcore_StartCore,
	MK_xcore_Reply					/* Must be last, otherwise MK_MAX_OPCODE (below) is wrong */
};
typedef enum mk_xcall_e mk_xcall_t;
/* Deviation MISRAC2012-1 <STOP>, MISRAC2012-2 <STOP> */

#define MK_MAX_OPCODE	MK_xcore_Reply

/* A single message. This buffer is read-only by the receiving core and write-only by the sending core.
 * A message buffer is an array of these.
*/
#define MK_MSG_MAXPARAM	4

struct mk_message_s
{
	mk_parametertype_t from;							/* Which core (for sending a reply) */
	mk_parametertype_t callerCookie;					/* Cookie for identifying the waiting thread for replies. */
	mk_parametertype_t opcode;							/* Which API to perform (mk_xcall_t) */
	mk_parametertype_t parameter[MK_MSG_MAXPARAM];		/* Parameters for that API */
};
#define MK_MisalignedMessage(buffer, ptr)	\
	((((mk_address_t)(ptr) - (mk_address_t)(buffer)) % sizeof(mk_message_t)) != 0u)

/* A raw cookie is a number in the range 1 to 65534.
 * A message cookie contains the cookie and its bitwise inverse. Neither the cookie nor its inverse can be zero.
 * The cookie in a waiting thread contains the raw cookie and the index of the core we sent the request to.
 * A null cookie is zero (defined in Mk_public_types.h)
*/
#define MK_MINCOOKIE				0x0001u
#define MK_MAXCOOKIE				0xfffeu
#define MK_COOKIEMASK				0xffffu

/* cookies are unsigned, so no mask needed after right shift in the following macros */
#define MK_GET_MSGCOOKIE_VALUE(keks)	((keks) & MK_COOKIEMASK)
#define MK_MSGCOOKIE(keks)				((mk_parametertype_t)(keks) | (((mk_parametertype_t)(keks) ^ 0xffffu) << 16))
#define MK_WAITCOOKIE(keks, core)		((((mk_parametertype_t) (core)) << 16) | (keks))
#define MK_GET_WAITCOOKIE_VALUE(keks)	((keks) & MK_COOKIEMASK)
#define MK_CHECK_WAITCOOKIE(keks)		( MK_GET_WAITCOOKIE_VALUE(keks) == (((keks) >> 16) ^ 0xffffu) )

/* mk_msgqueuedescriptor_s - message queue descriptor
 *
 * This structure (const) specifies where the queue variables can be found.
*/
struct mk_msgqueuedescriptor_s
{
	mk_msgptr_t      buffer;
	mk_msgptr_t      limit;
	mk_msgptrfield_t *insert;
	mk_msgptrfield_t *withdraw;
};

/* mk_queuepair_s - message queue descriptor
 *
 * This structure (const) specifies where the queue variables can be found.
*/
struct mk_msgqueuepair_s
{
	const mk_msgqueuedescriptor_t *output;
	const mk_msgqueuedescriptor_t *input;
};

/* mk_xcallfunction_t - function pointer type for cross-core calls
*/
typedef void (*mk_xcallfunction_t)(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);

/* Deviation MISRAC2012-1 <START>, MISRAC2012-2 <START> */
void MK_XcoreActivateTask(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreSetEvent(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreCallCtrSub(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreGetTaskState(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreAsyncActivateTask(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreAsyncSetEvent(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreAsyncCallCtrSub(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreStartCore(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreShutdown(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreTerminateApplication(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
void MK_XcoreReply(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
/* Deviation MISRAC2012-1 <STOP>, MISRAC2012-2 <STOP> */

extern mk_xcallfunction_t const MK_xcallTable[MK_MAX_OPCODE+1];


/* mk_invalidmessagehandler_t - function pointer type for "invalid message"-handlers
*/
typedef void (*mk_invalidmessagehandler_t)(mk_kernelcontrol_t *, mk_constmsgptr_t);

void MK_IgnoreInvalidXcoreMessage(mk_kernelcontrol_t *, mk_constmsgptr_t);
void MK_CountInvalidXcoreMessage(mk_kernelcontrol_t *, mk_constmsgptr_t);
void MK_PanicInvalidXcoreMessage(mk_kernelcontrol_t *, mk_constmsgptr_t);

extern const mk_invalidmessagehandler_t MK_invalidMessageHandler[MK_MAXCORES];

/* Error handler for invalid cross-core messages. Calls the function configured for the
 * respective core.
*/
#define MK_HandleInvalidXcoreMessage(cv, m) \
	do { \
		MK_invalidMessageHandler[(cv)->coreIndex]((cv), (m)); \
	} while (0)

/* Tables of message queue pairs for bidirectional communication between cores.
 * There is one table per core, each with MK_MAXCORES entries.
 * Each entry is a queue pair (output/input). Any individual message queue will be referenced
 * from two queue pairs; once as an input queue, once as an output queue.
*/
extern const mk_msgqueuepair_t MK_c0_queues[MK_MAXCORES];
extern const mk_msgqueuepair_t MK_c1_queues[MK_MAXCORES];
extern const mk_msgqueuepair_t MK_c2_queues[MK_MAXCORES];
extern const mk_msgqueuepair_t MK_c3_queues[MK_MAXCORES];
extern const mk_msgqueuepair_t MK_c4_queues[MK_MAXCORES];
extern const mk_msgqueuepair_t MK_c5_queues[MK_MAXCORES];
extern const mk_msgqueuepair_t MK_c6_queues[MK_MAXCORES];
extern const mk_msgqueuepair_t MK_c7_queues[MK_MAXCORES];

/* This is the list of all the queue pair tables - an array of arrays.
*/
extern const mk_msgqueuepair_t * const MK_messageQueues[MK_MAXCORES];

mk_objquantity_t MK_HandleMessagesFrom(mk_kernelcontrol_t *, mk_objectid_t, const mk_msgqueuepair_t *);
mk_errorid_t MK_SendMessage
(	mk_kernelcontrol_t *,
	mk_objectid_t, mk_xcall_t,
	mk_parametertype_t,
	mk_parametertype_t const *);
void MK_InitMessageQueues(mk_kernelcontrol_t *);

/* Error-handling function for use when asynchronous cross-core job cannot be handled.
*/
void MK_ReportDroppedXcoreRequest(mk_kernelcontrol_t *);


#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
