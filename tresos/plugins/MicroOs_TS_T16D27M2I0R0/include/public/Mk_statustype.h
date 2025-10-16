/* Mk_statustype.h
 *
 * This header file defines StatusType and E_OK as required by Autosar (OSEK Binding Specification)
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_020]
 *  #ifndef SOME_MACRO shall only be used when the then-branch contains either
 *  #define SOME_MACRO or #error. It shall not have an else-branch.
 *
 * Reason:
 *  This conditional compilation section actually does contain a definition of the macro whose defined-ness
 *  was tested. However, another related definition is also made. This particular construct is required by
 *  the OSEK Binding Specification.
*/
#ifndef MK_STATUSTYPE_H
#define MK_STATUSTYPE_H	1

#include <public/Mk_basic_types.h>

#ifndef MK_ASM

/* Deviation DCG-1 */
#ifndef STATUSTYPEDEFINED
/* Conformant with OSEK Binding Specification.
*/
#define STATUSTYPEDEFINED   1
typedef mk_uint8_t StatusType;
#endif

/* Definition of E_OK, compatible with the OSEK Binding Specification
*/
#ifndef E_OK
#define E_OK            MK_U(0)
#endif

#if ( E_OK != 0 )
#error "E_OK is non-zero. This is not AUTOSAR-conformant"
#endif

#endif

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
