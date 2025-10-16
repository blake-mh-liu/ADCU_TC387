/* Mk_TRICORE_Cfg.h - TRICORE microkernel configuration header
 *
 * This file is included by anything that needs to see the TRICORE specific
 * microkernel configuration.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TRICORE_CFG_H
#define MK_TRICORE_CFG_H

#include <public/Mk_hwsel.h>

/* Include the core configuration header files for each core that is physically present.
*/
#include <configuration/TRICORE/Mk_TRICORE_c0_cfg.h>

#if MK_MAXCORES > 1
#include <configuration/TRICORE/Mk_TRICORE_c1_cfg.h>
#endif
#if MK_MAXCORES > 2
#include <configuration/TRICORE/Mk_TRICORE_c2_cfg.h>
#endif
#if MK_MAXCORES > 3
#include <configuration/TRICORE/Mk_TRICORE_c3_cfg.h>
#endif
#if MK_MAXCORES > 4
#include <configuration/TRICORE/Mk_TRICORE_c4_cfg.h>
#endif
#if MK_MAXCORES > 5
#include <configuration/TRICORE/Mk_TRICORE_c5_cfg.h>
#endif
#if MK_MAXCORES > 6
#include <configuration/TRICORE/Mk_TRICORE_c6_cfg.h>
#endif
#if MK_MAXCORES > 7
#include <configuration/TRICORE/Mk_TRICORE_c7_cfg.h>
#endif


/* Define default values for MK_CFG_CX_MPU_REGISTER_CHECK
 * in case these cores don't exist for the current derivative.
 * They are needed by MK_MPU_REGISTER_CHECK.
*/
#ifndef MK_CFG_C1_MPU_REGISTER_CHECK
#define MK_CFG_C1_MPU_REGISTER_CHECK	0
#endif
#ifndef MK_CFG_C2_MPU_REGISTER_CHECK
#define MK_CFG_C2_MPU_REGISTER_CHECK	0
#endif
#ifndef MK_CFG_C3_MPU_REGISTER_CHECK
#define MK_CFG_C3_MPU_REGISTER_CHECK	0
#endif
#ifndef MK_CFG_C4_MPU_REGISTER_CHECK
#define MK_CFG_C4_MPU_REGISTER_CHECK	0
#endif
#ifndef MK_CFG_C5_MPU_REGISTER_CHECK
#define MK_CFG_C5_MPU_REGISTER_CHECK	0
#endif
#if (MK_MAXCORES > 6)
#error "Define more default values for MK_CFG_CX_MPU_REGISTER_CHECK and adapt MK_MPU_REGISTER_CHECK."
#endif

/* MK_MPU_REGISTER_CHECK indicates whether the
 * register check is globally used or not used, to eliminate the corresponding
 * code if possible.
 */
#define MK_MPU_REGISTER_CHECK (				\
	(MK_CFG_C0_MPU_REGISTER_CHECK != 0) ||	\
	(MK_CFG_C1_MPU_REGISTER_CHECK != 0) ||	\
	(MK_CFG_C2_MPU_REGISTER_CHECK != 0) ||	\
	(MK_CFG_C3_MPU_REGISTER_CHECK != 0) ||	\
	(MK_CFG_C4_MPU_REGISTER_CHECK != 0) ||	\
	(MK_CFG_C5_MPU_REGISTER_CHECK != 0)		\
)


#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
