/* Mk_hw_characteristics.h
 *
 * This file includes the processor-specific characteristics file and then defines the
 * basic types macros accordingly.
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
 *  These conditional compilation sections actually do contain a definition of the macro whose defined-ness
 *  was tested. However, the definition is dependent on other factors, so strict conformance to the
 *  rule is not possible without adversely affecting the readability of the code.
*/
#ifndef MK_HW_CHARACTERISTICS_H
#define MK_HW_CHARACTERISTICS_H

#include <public/Mk_hwsel.h>
#include MK_HWSEL_PUB_CHARACTERISTICS

/* Sanity checks on the processor-specific values.
*/
#ifndef MK_HWWORDLENGTH
#error "MK_HWWORDLENGTH is not defined. Check the processor's characteristics file!"
#endif
#if (MK_HWWORDLENGTH==16) || (MK_HWWORDLENGTH==32) || (MK_HWWORDLENGTH==64)
/* MK_HWWORDLENGTH has supported value. If you add more to this list you'll need to adapt all the
 * sections that depend on the wordlength below
*/
#else
#error "MK_HWWORDLENGTH has an unsupported value. Check the processor's characteristics file!"
#endif

#ifndef MK_HWENDIAN
#error "MK_HWENDIAN is not defined. Check the processor's characteristics file!"
#endif
#if (MK_HWENDIAN==MK_LITTLEENDIAN) || (MK_HWENDIAN==MK_BIGENDIAN)
/* MK_HWENDIAN has supported value.
*/
#else
#error "MK_HWENDIAN has an unsupported value. Check the processor's characteristics file!"
#endif

#ifndef MK_HWSTACKGROWS
#error "MK_HWSTACKGROWS is not defined. Check the processor's characteristics file!"
#endif
#if MK_HWSTACKGROWS==MK_STACKGROWSDOWN
/* MK_HWSTACKGROWS has supported value.
*/
#elif MK_HWSTACKGROWS==MK_STACKGROWSUP
#error "MK_HWSTACKGROWSUP is known but currently unsupported. If the selection is correct it must be implemented!"
#else
#error "MK_HWSTACKGROWS has an unsupported value. Check the processor's characteristics file!"
#endif

/* !LINKSTO Microkernel.SignedDivision, 1
 * !doctype src
*/
#ifndef MK_HWNEGDIV
#error "MK_HWNEGDIV is not defined. Check the processor's characteristics file!"
#endif
#if (MK_HWNEGDIV==MK_NEGDIV_ROUNDTOWARDZERO) || (MK_HWNEGDIV==MK_NEGDIV_ROUNDTOWARDMINUSINF)
/* MK_HWNEGDIV has supported value.
*/
#else
#error "MK_HWNEGDIV has an unsupported value. Check the processor's characteristics file!"
#endif

/* !LINKSTO Microkernel.TransactionSupport, 1
 * !doctype src
*/
#ifndef MK_HW_HAS_TRANSACTION_SUPPORT
#error "MK_HW_HAS_TRANSACTION_SUPPORT is not defined. Check the processor's characteristics file!"
#endif
#if (MK_HW_HAS_TRANSACTION_SUPPORT==0) || (MK_HW_HAS_TRANSACTION_SUPPORT==1)
/* MK_HW_HAS_TRANSACTION_SUPPORT has supported value.
*/
#else
#error "MK_HW_HAS_TRANSACTION_SUPPORT has an unsupported value. Check the processor's characteristics file!"
#endif

#ifndef MK_HWMAXCORES
#error "MK_HWMAXCORES is not defined. Check the processor's characteristics file!"
#endif

/* Define the hardware-independent macros that are used by the microkernel
 * in terms of the hardware interface macros.
*/
#define MK_WORDLENGTH					MK_HWWORDLENGTH
#define MK_ENDIAN						MK_HWENDIAN
#define MK_STACKGROWS					MK_HWSTACKGROWS
#define MK_HAS_TRANSACTION_SUPPORT		MK_HW_HAS_TRANSACTION_SUPPORT

/* Creating a Safety OS 2.0 that is optimized for single-core operation
 * is not supported for multi-core derivatives.
*/
#define MK_MAXCORES		MK_HWMAXCORES

/* Provide a default value for memory protection: MPU is the norm.
*/
#ifndef MK_MEM_PROT
#define MK_MEM_PROT		MK_MEM_PROT_MPU
#endif

/* Define all the basic types that are not already defined.
*/
#ifndef MK_INT8_T
/* signed char is an 8-bit signed value on most processors and compilers.
 * signed char is used in preference to char because some compilers have switches that change the
 * definition of char to unsigned.
*/
#define MK_INT8_T			mk_schar_t
#endif

#ifndef MK_INT16_T
/* short is a 16-bit signed value on most processors and compilers.
 * K&R2e defines -32767..+32767 as an "acceptable minimum range" for short (Sect. B11)
*/
#define MK_INT16_T			mk_short_t
#endif

/* Deviation DCG-1 <START> */
#ifndef MK_INT32_T
/* long is a 32-bit signed value on most 16- and 32-bit processors and compilers.
 * On processors with longer words, int will be necessary.
*/
#if MK_WORDLENGTH<=32
#define MK_INT32_T			mk_long_t
#else
#define MK_INT32_T			mk_int_t
#endif
#endif
/* Deviation DCG-1 <STOP> */

#ifndef MK_UINT8_T
/* unsigned char is an 8-bit unsigned value on most processors and compilers.
*/
#define MK_UINT8_T			mk_uchar_t
#endif

#ifndef MK_UINT16_T
/* unsigned short is a 16-bit unsigned value on most processors and compilers. K&R2e defines 65535 as
 * an "acceptable minimum magnitude" for unsigned short (Sect. B11)
*/
#define MK_UINT16_T			mk_ushort_t
#endif

/* Deviation DCG-1 <START> */
#ifndef MK_UINT32_T
/* unsigned long is a 32-bit unsigned value on most 16- and 32-bit processors and compilers.
 * On processors with longer words, unsigned int will be necessary.
*/
#if MK_WORDLENGTH<=32
#define MK_UINT32_T			mk_ulong_t
#else
#define MK_UINT32_T			mk_unsigned_t
#endif
#endif
/* Deviation DCG-1 <STOP> */

#ifndef MK_ADDRESS_T
/* On most machines, unsigned long is big enough to hold an address too.
 * On some machines this might have to be model-dependent.
*/
#define MK_ADDRESS_T		mk_ulong_t
#endif

#ifndef MK_MACHINEWORD_T
/* Type matching the natural width of the processor architecture. unsigned long
 * should work for most machines. May need rethinking when including 64 bit
 * processors.
*/
#define MK_MACHINEWORD_T	MK_ADDRESS_T
#endif

#ifndef MK_SIZE_T
/* On most machines, unsigned long is big enough to hold a memory size.
 * On some machines this might have to be model-dependent.
*/
#define MK_SIZE_T			mk_ulong_t
#endif

#ifndef MK_STACKELEMENT_T
/* The smallest stack element is usually the natural word length of the machine.
*/
#define MK_STACKELEMENT_T	MK_MACHINEWORD_T
#endif

/* If the processor doesn't say it has a 64-bit type, assume it doesn't.
*/
#ifndef MK_HAS_INT64
#define MK_HAS_INT64	0
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
