/* Mk_misra.h
 *
 * This file contains macros to eliminate certain complaints of MISRA-C checkers.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.10 (advisory)
 *  The # and ## preprocessor operators should not be used.
 *
 * Reason:
 *  This macro is used for constructing symbols and constants from a common
 *  stem to guarantee consistency.
*/
#ifndef MK_MISRA_H
#define MK_MISRA_H

/* MK_U - Appends a 'u' suffix to a token (which must be a numerical literal constant)
 *
 * The suffix is not appended if MK_ASM is defined, that means, it is not appended for literals
 * in assembly code, as most assemblers do not understand such suffixes.
*/
#ifndef MK_ASM
#define MK_U(x)			MK_CONCAT(x,u)
#else
#define MK_U(x)			x
#endif

/* MK_CONCAT() - Concatenation macro.
 *
 * Using this macro avoids MISRA-C:2012 violations.
 * See also MK_CAT in the assembly-language include files.
*/
/* Deviation MISRAC2012-1 <+1> */
#define MK_CONCAT(a,b)	a##b

/* Macros to preclude MISRA-C violations for certain common operations.
*/
#define MK_ShiftLeft(type, value, index)	((type)(((type)(value)) << (index)))
#define MK_ShiftRight(type, value, index)	((type)(((type)(value)) >> (index)))

#define MK_ShiftLeftU32(value, index)		MK_ShiftLeft(mk_uint32_t, (value), (index))

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
