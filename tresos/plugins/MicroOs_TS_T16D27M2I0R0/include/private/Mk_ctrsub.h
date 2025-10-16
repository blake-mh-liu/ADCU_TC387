/* Mk_ctrsub.h - private header for activation of counter subsystem threads
 *
 * This file contains definitions for the microkernel's handling of counter subsystem threads.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_CTRSUB_H
#define MK_CTRSUB_H

#include <public/Mk_public_types.h>
#include <private/Mk_types_forward.h>
#include <public/Mk_ctrsubindex.h>
#include <private/Mk_thread.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>

#ifndef MK_ASM

/* MK_CSJ_SIZE - size of a counter subsystem job.
*/
#define	MK_CSJ_SIZE		7

#if MK_CSJ_SIZE > MK_BJ_MAX
#error "Development error: a counter subsystem job won't fit into a standard job buffer!"
#endif

/* Typedef for object properties.
*/
typedef struct mk_ctrsubobjprops_s mk_ctrsubobjprops_t;


/* Prototype for the counter subsystem wrapper function that calls the counter subsystem kernel function in the thread.
*/
typedef mk_parametertype_t (*mk_ctrsubfunc_t)(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

/* The counter subsystem service descriptor informs the microkernel about a counter subsystem service.
*/
struct mk_ctrsubservicedescriptor_s
{
	mk_ctrsubfunc_t ctrsubFunction;		/* Address of counter subsystem function. */
	const mk_ctrsubobjprops_t *props;	/* Base of the object properties table. */
	mk_objquantity_t nObjects;			/* No. of objects that exist that the function handles.
										 * Length of the array pointed to by props (unless NULL).
										*/
	mk_serviceid_t sid;					/* Service ID for error reporting. */
	mk_boolean_t onlySync;				/* If TRUE, the call *must* be synchronous (i.e. it returns information) */
};

#define MK_CSSVC(f, n, props, sid, sy)		{ (f), (props), (n), (sid), (sy) }

/* Counter subsystem object properties. This structure contains everything the microkernel needs to know about
 * the configuration of a counter subsystem object:
 *
 *	- coreIndex is the core on which the object "runs"; the APIs run on that core too!
 *	- applicationId	is the OS-Application that owns the object; for application termination etc.
*/
struct mk_ctrsubobjprops_s
{
	mk_objectid_t coreIndex;			/* Core on which the object resides. */
	mk_objectid_t applicationId;		/* OS-Application to which the object belongs. */
};

#define MK_CSPROP(c, a)						{ (c), (a) }

/* MK_ctrsubService is a table of counter subsystem service descriptors
 *
 * The table has one entry per service (including the hybrid services).
*/
extern const mk_ctrsubservicedescriptor_t MK_ctrsubService[MK_N_CTRSUBFUNCS];

/* MK_LocalCallCtrSub - call a counter subsystem function on the local core
*/
mk_errorid_t MK_LocalCallCtrSub(mk_kernelcontrol_t *, mk_objectid_t,
												const mk_ctrsubservicedescriptor_t *, mk_parametertype_t, mk_xcall_t);

#if MK_MAXCORES > 1
/* MK_MultiCallCtrSub() - internal kernel function to activate given counter subsystem function on any core.
 * Only available on multi-core systems.
 * Returns error code.
*/
#ifndef MK_ASM
mk_errorid_t MK_MultiCallCtrSub(mk_kernelcontrol_t *, mk_objectid_t, mk_xcall_t);
#endif

/* MK_InternCallCtrSub() - multi-core version
 *
 * !LINKSTO Microkernel.Function.MK_InternCallCtrSub, 1
 * !doctype src
*/
#define MK_InternCallCtrSub(cv, fi, mc)		MK_MultiCallCtrSub((cv), (fi), (mc))

#ifndef MK_ASM
mk_boolean_t MK_AddXcoreCtrSubJob(mk_kernelcontrol_t *, mk_msgptr_t, mk_objectid_t);
#endif

#else /* MK_MAXCORES */

/* MK_InternCallCtrSub() - single-core version
 *
 * !LINKSTO Microkernel.Function.MK_InternCallCtrSub, 1
 * !doctype src
*/
#define MK_InternCallCtrSub(cv, fi, mc) \
	MK_LocalCallCtrSub((cv), (fi), &MK_ctrsubService[(fi)], MK_HwGetParameter2((cv)->currentThread->regs), (mc));

#endif /* MK_MAXCORES */

/* MK_StartCtrSubTerminateApplication - internal function to start the counter subsystem part of TerminateApplication
*/
mk_errorid_t MK_StartCtrSubTerminateApplication(mk_kernelcontrol_t *, mk_objectid_t, mk_boolean_t);

/* Prototypes of wrapper functions that the counter subsystem must provide.
*/
mk_parametertype_t OS_MkwSetRelAlarm(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwSetAbsAlarm(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwCancelAlarm(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwGetAlarm(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

mk_parametertype_t OS_MkwIncrementCounter(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwGetCounterValue(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwUpdateCounter(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

mk_parametertype_t OS_MkwSimTimerAdvance(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

mk_parametertype_t OS_MkwStartScheduleTable(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwStartScheduleTableSynchron(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwNextScheduleTable(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwStopScheduleTable(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwSyncScheduleTable(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwSetScheduleTableAsync(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

mk_parametertype_t OS_MkwTerminateApplication(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);
mk_parametertype_t OS_MkwStartOs(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

/* MK_UnknownCtrSubCall() - microkernel function for unconfigured or optimized-away counter subsystem services.
 *
 * The configuration uses this microkernel function in place of the wrapper provided by the
 * counter subsystem for services that are deselected or optimized away. Using a microkernel function rather
 * than an OS function means that the counter subsystem can be completely eliminated in microkernel-only
 * configurations.
*/
mk_parametertype_t MK_UnknownCtrSubCall(mk_parametertype_t, mk_parametertype_t, mk_parametertype_t);

/* These constants are used to get the coreID (or application ID) of a counter subsystem object.
 * MK_n* is the number of these objects.
 * MK_*PropertyTable points to the begin of the property table or is null if the resp. MK_n* equals 0.
 * NOTE Currently the counter subsystem stores the application ID of its objects.
 *      If this application ID can be mapped to a core ID these constants
 *      (and the resp. getter functions like MK_LibGetAlarmCoreId (Mk_public_api.h)) are obsolete.
*/
extern const mk_objquantity_t MK_nAlarms;
extern const mk_objquantity_t MK_nCounters;
extern const mk_objquantity_t MK_nScheduleTables;
extern const mk_ctrsubobjprops_t * const MK_AlarmPropertyTable;
extern const mk_ctrsubobjprops_t * const MK_CounterPropertyTable;
extern const mk_ctrsubobjprops_t * const MK_ScheduleTablePropertyTable;

#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
