/* MicroOs.h
 *
 * This file is included by the application when it needs to use OS services.
 *
 * Note: This file will be included by Os.h, but application code that needs a high
 * level of safety integrity must include this file instead of Os.h!
 *
 * (c) Elektrobit Automotive GmbH
*/
/* !LINKSTO		Microkernel.Interface.PublicHeader,1
 * !doctype		src
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_STYLE_013]
 *	In the EB tresos Safety OS project, all source code file names shall start with a
 *	file name prefix as defined in Appendix A, Prefixes and Definitions.
 *
 * Reason:
 *	The name of the file MicroOs.h was chosen to be similar to the file Os.h. It is
 *	the file that is included by application source code in order to gain access to the
 *	safety-related part of the Safety OS without accessing the features that are not
 *	permitted to be used in code that has a high integrity level. Its name was chosen
 *	very early in the project, before the naming conventions were finalized, and is
 *	retained for reasons of compatibility.
*/

/* Deviation DCG-1 <*> */
#ifndef MICROOS_H
#define MICROOS_H

/* Include the microkernel API headers
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_error.h>
#include <public/Mk_autosar.h>
#include <public/Mk_callout.h>

/* Include the generator's output file.
*/
#include <Mk_gen_user.h>

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
