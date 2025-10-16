/* Os_defs_TRICORE.h - Tricore definitions for derivative selection etc.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#ifndef OS_DEFS_TRICORE_H
#define OS_DEFS_TRICORE_H

/* CPUs. OS_CPU must be one of these.
 *
 * CAVEAT:
 * The existence of a TRICORE derivative in this list does not imply a
 * commitment or intention to support the derivative.
*/
#define OS_TC1798       0x10b
#define OS_TC1791       0x10c
#define OS_TC1793       0x10d

#define OS_TC27XT       0x202
#define OS_TC23XL       0x203
#define OS_TC29XT       0x205
#define OS_TC22XL       0x206
#define OS_TC39XX       0x301
#define OS_TC38XQ       0x302
#define OS_TC38XT       0x303
#define OS_TC35XT       0x304
#define OS_TC37XT       0x305
#define OS_TC36XD       0x306
#define OS_TC33XL       0x307
#define OS_TC32XL       0x309
#define OS_TC3EXQ       0x30A

#define OS_TC49XXVDK    0x401
#define OS_TC49XXSTEPA  0x402
#define OS_TC4DXX       0x403

/* Architectures of the TriCore family
 * The values used must be suitable for comparing architecture versions
 *
 * Note: architecture versions prior to 1.6E/1.6P are not supported
 */
#define OS_TRICOREARCH_16EP       161  /* Aurix */
#define OS_TRICOREARCH_162        162  /* Aurix 2G (TC3X, TC 1.6.2) */
#define OS_TRICOREARCH_18         180  /* Aurix 3G (TC4X, TC 1.8) */

#define OS_SRNVERSION_16          16
#define OS_SRNVERSION_18          18   /* SRE moved. TOS grew. */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
