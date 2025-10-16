/* Mk_event.h - event handling
 *
 * This file contains definitions for the microkernel's event handling.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_EVENT_H
#define MK_EVENT_H

#include <public/Mk_public_types.h>

#ifndef MK_ASM

typedef mk_uint32_t mk_eventmask_t;
typedef struct mk_eventstatus_s mk_eventstatus_t;

/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_waitingstate_e
{
	MK_NO_WAIT,
	MK_WAIT,
	MK_WAITGETCLEAR
};
typedef enum mk_waitingstate_e mk_waitingstate_t;

struct mk_eventstatus_s
{
	mk_eventmask_t pendingEvents;
	mk_eventmask_t awaitedEvents;
	mk_waitingstate_t waitingState;
};

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
