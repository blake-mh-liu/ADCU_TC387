/* Mk_TC3XXX.h - Description of Tricore (AURIX) variant TC3XXX
 *
 * Description of common properties of all Aurix derivatives having three cores.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TC3XXX_H
#define MK_TC3XXX_H

/* TC3XXX has up to six Tricore 1.6.2 cores.
*/
#define MK_TRICORE_CORE		MK_TRICORE_TC162

/* The SCU on TC3XXX can be found @ 0xF0036000 (ends @ 0xF00363FF)
*/
#define MK_MODBASE_SCU		0xf0036000u
#define MK_TRICORE_SCU		MK_SCU_TC3XX

/* The base address of the STM modules (used for the time stamp feature).
*/
#define MK_STM0_BASE	0xf0001000u
#define MK_STM1_BASE	0xf0001100u
#define MK_STM2_BASE	0xf0001200u
#define MK_STM3_BASE	0xf0001300u
#define MK_STM4_BASE	0xf0001400u
#define MK_STM5_BASE	0xf0001500u

/* COMPAT register fields
*/
#define MK_COMPAT_RESERVED	0xffffffe7
#define MK_COMPAT_SP		0x00000010	/* Syscon Safety Protection */
#define MK_COMPAT_RM		0x00000008	/* Rounding Mode Compatibility */

/* The COMPAT register value is checked during startup:
 * - MK_COMPAT_MASK  contains all bits which shall be checked.
 * - MK_COMPAT_VALUE contains the value which the extracted bits shall have.
 * So we check "(compat & MK_COMPAT_MASK) == MK_COMPAT_VALUE".
*/
#define MK_COMPAT_MASK		MK_COMPAT_SP
#define MK_COMPAT_VALUE		MK_COMPAT_SP

/* Cache operations privileges.
*/
#define MK_CACHEOP_PRIVILEGE	MK_CACHEOP_USER

#endif
/* Editor settings: DO NOT DELETE
 * vi: set ts=4:
*/
