/* Mk_ctrsubindex.h - indexes for the counter subsystem services
 *
 * The services from the start of the list up to the commented place are directly
 * callable by threads. Those after the comment are the counter subsystem parts of hybrid system
 * calls and are called by the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * While the mk_ctrsubindex_t is not used directly, its enum values are used for readability.
*/
#ifndef MK_CTRSUBINDEX_H
#define MK_CTRSUBINDEX_H

#include <public/Mk_public_types.h>

#ifndef MK_ASM

/* mk_ctrsubindex_t - an enumerated type listing all the counter subsystem functions.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_ctrsubindex_e
{
	MK_ctrsub_SetRelAlarm = 0,
	MK_ctrsub_SetAbsAlarm,
	MK_ctrsub_CancelAlarm,
	MK_ctrsub_IncrementCounter,
	MK_ctrsub_StartScheduleTable,
	MK_ctrsub_StartScheduleTableSynchron,
	MK_ctrsub_NextScheduleTable,
	MK_ctrsub_StopScheduleTable,
	MK_ctrsub_SyncScheduleTable,
	MK_ctrsub_SetScheduleTableAsync,
	MK_ctrsub_SimTimerAdvance,
	MK_ctrsub_GetCounterValue,
	MK_ctrsub_GetAlarm,
	MK_ctrsub_UpdateCounter,

/* From here, the services cannot be called directly by the user.
 * The definition of MK_N_CTRSUBCALLS uses MK_ctrsub_TerminateApplication as the reference point,
 * so if you insert more "internal" services, either put them after MK_ctrsub_TerminateApplication or
 * change the definition of MK_N_CTRSUBCALLS.
*/
	MK_ctrsub_TerminateApplication,
	MK_ctrsub_StartOs,
	MK_ctrsub_nCtrsubFuncs
};

/* Deviation MISRAC2012-1 <+1> */
typedef enum mk_ctrsubindex_e mk_ctrsubindex_t;

/* MK_N_CTRSUBCALLS is the number of directly-callable counter subsystem functions.
*/
#define MK_N_CTRSUBCALLS	((mk_parametertype_t)MK_ctrsub_TerminateApplication)

/* MK_N_CTRSUB is the total number of counter subsystem functions, including those that are part of the hybrid services.
*/
#define MK_N_CTRSUBFUNCS	(MK_ctrsub_nCtrsubFuncs)

#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
