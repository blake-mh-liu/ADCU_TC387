/* Mk_kconfig.h - microkernel static configuration header
 *
 * This file is included by anything that needs to see the static microkernel configuration.
 *
 * This header file (and possibly the processor-specific files that it includes) can
 * be used to permanently enable/disable microkernel features, especially features that
 * are intended for use by the microkernel development team.
 *
 * It is not intended to be modified by customers. Doing so invalidates the safety certification.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_KCONFIG_H
#define MK_KCONFIG_H

/* Use external trace tool.
*/
#ifndef MK_USE_TRACE
#define MK_USE_TRACE	0
#endif

/* Use magic ORTI tracing function.
*/
#ifndef MK_USE_ORTI_TRACE
#define MK_USE_ORTI_TRACE	0
#endif

/* Sanity check to avoid misconfigurations.
*/
#if !MK_USE_TRACE && MK_USE_ORTI_TRACE
#error "MK_USE_ORTI_TRACE must not be true if MK_USE_TRACE is false"
#endif

/* Use external trace tool if selected.
 *
 * !LINKSTO Microkernel.Function.MK_TRACE_STATE_THREAD,2
 * !doctype src
*/
#if MK_USE_TRACE

#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>

/* Use internal ORTI trace function if selected.
 *
 * !LINKSTO Microkernel.Function.MK_OrtiTraceThreadChange,1
 * !doctype src
*/
#if MK_USE_ORTI_TRACE

/* MK_OrtiTraceThreadChange() is called by the microkernel whenever a thread changes its state.
 *
 * This function is directly called from inside the microkernel. Its implementation is supplied by
 * the microkernel and is enabled by setting MK_USE_TRACE and MK_USE_ORTI_TRACE to a non-zero value.
 *
 * Parameters:
 *  objTyp:		Type of the thread (e.g., MK_OBJTYPE_TASK, MK_OBJTYPE_ISR)
 *  objId:		Id of the thread
 *  newState:	The new state of the thread
*/
#ifndef MK_ASM
extern volatile mk_uint32_t * const MK_ortiRunningThread[MK_MAXCORES];

extern void MK_OrtiTraceThreadChange
(
	mk_objecttype_t,
	mk_objectid_t,
	mk_threadstate_t
);
#endif

#define MK_TRACE_STATE_THREAD(typ, id, name, old, new)	MK_OrtiTraceThreadChange(typ, id, new)

#else /* MK_USE_ORTI_TRACE */

/* MK_QmTraceStateThreadChange() is called by the microkernel whenever a thread changes its state.
 *
 * This function is directly called from inside the microkernel. It has to be implemented by the user in
 * case the trace hook is enabled by setting MK_USE_TRACE to a non-zero value
 * and MK_USE_ORTI_TRACE to zero.
 *
 * Parameters:
 *  objTyp:		Type of the thread (e.g., MK_OBJTYPE_TASK, MK_OBJTYPE_ISR)
 *  objId:		Id of the thread
 *  objName:	C string containing the name of the object
 *  oldState:	The previous state of the thread
 *  newState:	The new state of the thread
*/
#ifndef MK_ASM
extern void MK_QmTraceStateThreadChange
(
	mk_objecttype_t,
	mk_objectid_t,
	const char *,
	mk_threadstate_t,
	mk_threadstate_t
);
#endif

#define MK_TRACE_STATE_THREAD(typ, id, name, old, new)	MK_QmTraceStateThreadChange(typ, id, name, old, new)

#endif /* MK_USE_ORTI_TRACE */

#else /* MK_USE_TRACE */

#define MK_TRACE_STATE_THREAD(typ, id, name, old, new)		do { } while(0)

#endif /* MK_USE_TRACE */

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
