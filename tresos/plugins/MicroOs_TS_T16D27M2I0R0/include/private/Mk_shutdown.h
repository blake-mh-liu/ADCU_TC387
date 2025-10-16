/* Mk_shutdown.h
 *
 * This file contains the declaration of the shutdown function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_SHUTDOWN_H
#define MK_SHUTDOWN_H

#include <public/Mk_public_types.h>
#include <public/Mk_error.h>
#include <private/Mk_types_forward.h>

/* Hardware-independent shutdown function
*/
void MK_Shutdown(mk_osekerror_t);

/* Handler for rejected shutdown requests
*/
void MK_RejectShutdown(mk_kernelcontrol_t *, mk_serviceid_t);

/* Checks whether the given thread is allowed to request the respective shutdown.
*/
mk_boolean_t MK_IsAllowedToShutdown(mk_thread_t *, mk_uint32_t);

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
