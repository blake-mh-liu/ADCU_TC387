/* Mk_TRICORE_exceptionfunctions.h - prototypes for exception handling functions.
 *
 * This file contains prototypes for the exception functions that are called by
 * the kernel entry code in the exception vectors.
 *
 * None of these functions can be called from normal C code, so they don't really need
 * prototypes.
 *
 * This file exists to keep code checkers happy. It should only be included by the files
 * that contain exception functions.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_EXCEPTIONFUNCTIONS_H
#define MK_TRICORE_EXCEPTIONFUNCTIONS_H

#include <public/Mk_basic_types.h>

/* Eight trap handler functions (one per trap vector)
 *
 * The parameters are:
 *	D4 - pcxi value after SVLCX
 *  D5 - d15 value
*/
void MK_HandleVirtualAddressTrap(mk_uint32_t, mk_uint32_t);
void MK_HandleProtectionTrap(mk_uint32_t, mk_uint32_t);
void MK_HandleInstructionTrap(mk_uint32_t, mk_uint32_t);
void MK_HandleContextTrap(mk_uint32_t, mk_uint32_t);
void MK_HandleBusErrorTrap(mk_uint32_t, mk_uint32_t);
void MK_HandleAssertionTrap(mk_uint32_t, mk_uint32_t);
void MK_TricoreSyscall(mk_uint32_t, mk_uint32_t);
void MK_HandleNmi(mk_uint32_t, mk_uint32_t);

/* Other functions that can only be called from the assembly-language entry points
*/
MK_ATTR_NO_STACKPROT void MK_InitCsaList(mk_uint32_t, mk_uint32_t);

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
