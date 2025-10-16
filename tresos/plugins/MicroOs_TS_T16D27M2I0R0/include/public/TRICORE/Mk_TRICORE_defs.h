/* Mk_TRICORE_defs.h - TRICORE definitions for derivative selection etc.
 *
 * This file defines the derivative and core definitions for TRICORE.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_DEFS_H
#define MK_TRICORE_DEFS_H

/* CPUs. MK_CPU must be one of these.
 *
 * CAVEAT:
 * The existence of a TRICORE derivative in this list does not imply a
 * commitment or intention to support the derivative.
*/
#define MK_TC27XT	0x202
#define MK_TC23XL	0x203
/* Reserved: 0x204 (old id of deleted TC275; do not reuse) */
#define MK_TC29XT	0x205
#define MK_TC22XL	0x206
#define MK_TC26XD	0x207

#define MK_TC39XX	0x301
#define MK_TC38XQ	0x302
#define MK_TC38XT	0x303
#define MK_TC35XT	0x304
#define MK_TC37XT	0x305
#define MK_TC36XD	0x306
#define MK_TC33XL	0x307
#define MK_TC39XQ	0x308
#define MK_TC32XL	0x309

/* MK_TRICORE_CORE is set in the derivative-specific header.
 * It can take one of the following values.
 *
 * CAVEAT:
 * The existence of a core in the list below does not imply a
 * commitment or intention to support this core.
*/
#define MK_TRICORE_TC161		161 /* i.e., TC 1.6P & TC1.6E */
#define MK_TRICORE_TC162		162 /* Aurix 2G */

/* MK_TRICORE_SCU is set in the derivative-specific header.
 * It can take one of the following values.
*/
#define MK_SCU_TC2XX			0x02
#define MK_SCU_TC3XX			0x03

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
