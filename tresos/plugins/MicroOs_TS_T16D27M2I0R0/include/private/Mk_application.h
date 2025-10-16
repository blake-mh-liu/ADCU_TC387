/* Mk_application.h - application configuration and handling
 *
 * This file contains definitions for the hardware-independent part of
 * configuration and handling of OS-applications.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_APPLICATION_H
#define MK_APPLICATION_H

#include <public/Mk_basic_types.h>
#include <private/Mk_types_forward.h>
#include <private/Mk_core.h>

#ifndef MK_ASM

#define MK_MAXAPPLICATIONS	32

/* 32 application flags per accessing app word.
*/
typedef mk_uint32_t	mk_accessingapp_t;
#define MK_NACCESSINGAPPWORDS	((MK_MAXAPPLICATIONS+31)/32)
#define MK_ACCINDEX(i)			((i)/32u)
#define MK_ACCMASK(i)			(1u<<((i)%32u))

/* global permissions
*/
#define MK_PERMIT_SHUTDOWNOS		1u
#define MK_PERMIT_SHUTDOWNALLCORES	2u

/* Application properties configuration.
*/
typedef struct mk_app_s mk_app_t;

struct mk_appcfg_s
{
	mk_app_t *dynamic;				/* A pointer to the dynamic state structure in the appropriate core's array */
	mk_accessingapp_t accessingApps[MK_NACCESSINGAPPWORDS];	/* Applications that are allowed to access this one. */
	mk_accessingapp_t accessAppMask;	/* The mask to use when examining object permissions for this application. */
	mk_uint32_t globalPermissions;	/* The set of global permissions assigned to this OS-Application. */
	mk_objectid_t accessAppIndex;	/* The index to use when examining object permissions for this application. */
	mk_objectid_t coreIndex;		/* The application's core */
	mk_objectid_t restartTask;		/* The application's restart task */
};

/* OS-Application dynamic state.
 * At the moment this contains only a single state variable (running/terminated etc.) but is
 * declared as a structure to simplify further extensions if they become necessary.
*/
struct mk_app_s
{
	mk_appstate_t appState;
};

extern const mk_objquantity_t MK_nApps;
extern const mk_appcfg_t * const MK_appCfg;

#define MK_APPCONFIG(id, dyn, cor, rt, gperm, aa) \
	{ (dyn), aa, MK_ACCMASK((id)), (gperm), MK_ACCINDEX((id)), (cor), (rt) }

/* Function prototypes for application handling
*/
void MK_InitApplications(mk_objectid_t);
void MK_RestartApplication(mk_kernelcontrol_t *, mk_objectid_t);
void MK_TerminateApplication(mk_kernelcontrol_t *, mk_objectid_t, mk_boolean_t);
mk_boolean_t MK_AppStateOk(mk_objectid_t, mk_objectid_t);

/* MK_LocalTerminateApplication() - internal kernel function to terminate a given application.
*/
mk_errorid_t MK_LocalTerminateApplication(mk_kernelcontrol_t *, mk_objectid_t, mk_objectid_t, mk_boolean_t);

#if MK_MAXCORES > 1
/* MK_MultiTerminateApplication() - internal kernel function to terminate a given application on any core.
 * Only available on multi-core systems.
*/
mk_errorid_t MK_MultiTerminateApplication(mk_kernelcontrol_t *, mk_objectid_t, mk_objectid_t, mk_boolean_t);

/* MK_InternTerminateApplication() -  the multi-core case.
 *
 * !LINKSTO Microkernel.Function.MK_InternTerminateApplication, 2
 * !doctype src
*/
#define MK_InternTerminateApplication(cv, app, cApp, rst)		MK_MultiTerminateApplication(cv, app, cApp, rst)

#else

/* MK_InternTerminateApplication() -  the single-core case.
 *
 * !LINKSTO Microkernel.Function.MK_InternTerminateApplication, 2
 * !doctype src
*/
#define MK_InternTerminateApplication(cv, app, cApp, rst)		MK_LocalTerminateApplication(cv, app, cApp, rst)

#endif

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
