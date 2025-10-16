/* Mk_basic_types.h
 *
 * This file declares the basic data types used by the kernel. These types are those that are used to define
 * kernel-specific data types.
 * Basic types are always visible to the user.
 * The names of the basic types are chosen in line with POSIX conventions, but prefixed with mk_.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * Native types for the OS, required for Dir 4.6.
 * Unused typedefs are either present for completeness or are used by certain architectures.
*/

#ifndef MK_BASIC_TYPES_H
#define MK_BASIC_TYPES_H

/* Microkernel version. MK 1.x doesn't define this, so if it's undefined, assume 1.
*/
#define MK_VERSION		2

#include <public/Mk_hw_characteristics.h>

#ifndef MK_ASM

/* MISRA-proof aliases for standard C types. These should only be used where absolutely necessary,
 * for example to define other fixed- or minimum-width types.
 * The #defined type definitions in Mk_hw_characteristics.h  and the hardware-specific headers
 * assume the existence of these types.
 *
 * mk_char_t is only to be used for real characters.
*/
typedef char				mk_char_t;		/* Could be signed or unsigned depending on compiler. */
typedef signed char			mk_schar_t;
typedef unsigned char		mk_uchar_t;
typedef short				mk_short_t;
typedef unsigned short		mk_ushort_t;
typedef int					mk_int_t;
typedef unsigned int		mk_unsigned_t;
typedef long				mk_long_t;
typedef unsigned long		mk_ulong_t;

/* Deviation MISRAC2012-1 <START> */
/* Standard fixed-length signed types
*/
typedef MK_INT8_T			mk_int8_t;
typedef MK_INT16_T			mk_int16_t;
typedef MK_INT32_T			mk_int32_t;
#if MK_HAS_INT64
typedef MK_INT64_T			mk_int64_t;
#endif

/* Standard fixed-length unsigned types
*/
typedef MK_UINT8_T			mk_uint8_t;
typedef MK_UINT16_T			mk_uint16_t;
typedef MK_UINT32_T			mk_uint32_t;
#if MK_HAS_INT64
typedef MK_UINT64_T			mk_uint64_t;
#endif
/* Deviation MISRAC2012-1 <STOP> */

/* Standard types for memory management
*/
typedef MK_ADDRESS_T		mk_address_t;
typedef MK_MACHINEWORD_T	mk_machineword_t;
typedef MK_SIZE_T			mk_size_t;
typedef MK_STACKELEMENT_T	mk_stackelement_t;

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
