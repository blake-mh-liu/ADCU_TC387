/* Mk_k_ppashutdown.c
 *
 * This file contains the MK_PpaShutdown() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_error.h>
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_shutdown.h>

/* MK_PpaShutdown() shuts the microkernel down with the error code given by the MK_protectionInfo structure.
 *
 * !LINKSTO Microkernel.Function.MK_PpaShutdown, 1
 * !doctype src
*/
void MK_PpaShutdown(mk_kernelcontrol_t *coreVars)
{
	mk_protectioninfo_t *protectionInfo = MK_protectionInfo[coreVars->coreIndex];
	mk_osekerror_t osekError = protectionInfo->osekError;

	MK_Shutdown(osekError);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
