/* Mk_Cfg.h - microkernel configuration header
 *
 * This file is included by anything that needs to see the microkernel configuration.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_CFG_H
#define MK_CFG_H

#include <public/Mk_hwsel.h>

/* Include the headers that define the types of the variables that we declare here
*/
#include <public/Mk_basic_types.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>

/* This will be needed for the PSW values in the generated headers, among other things
*/
#include MK_HWSEL_PRV_CORE

/* Include the generated headers
*/
#include <Mk_gen_user.h>
#include <Mk_gen_config.h>
#include <Mk_board.h>

/* Include configuration patch file if told to do so
*/
#ifndef MK_INCLUDE_CONFIG_PATCH
#define MK_INCLUDE_CONFIG_PATCH		0
#endif
#if MK_INCLUDE_CONFIG_PATCH
#include <Mk_config_patch.h>
#endif

/* Declarations of configurable-sized arrays that are needed across modules
*/
#ifndef MK_ASM

#endif /* MK_ASM */
/* Time stamp clock factors
 * The board header file, or whatever provides the time stamp conversion macros, should
 * also indicate that the have been provided by defining the corresponding "HAS" macro to 1.
 * If the HAS macro is undefined, no ROM constant will be defined. This is achieved by defining
 * the macros to 0 if they are undefined.
*/
#ifndef MK_HAS_TIMESTAMPCLOCKFACTOR100U
#define MK_HAS_TIMESTAMPCLOCKFACTOR100U		0
#endif

#ifndef MK_HAS_TIMESTAMPCLOCKFACTOR10U
#define MK_HAS_TIMESTAMPCLOCKFACTOR10U		0
#endif

#ifndef MK_HAS_TIMESTAMPCLOCKFACTOR1U
#define MK_HAS_TIMESTAMPCLOCKFACTOR1U		0
#endif

/* Error check for the time stamp conversion macros
*/
#if MK_HAS_TIMESTAMPCLOCKFACTOR100U
#ifndef MK_TIMESTAMPCLOCKFACTOR100U
#error "Configuration claims to provide MK_TIMESTAMPCLOCKFACTOR100U but fails to do so. Please check the configuration."
#endif
#endif

#if MK_HAS_TIMESTAMPCLOCKFACTOR10U
#ifndef MK_TIMESTAMPCLOCKFACTOR10U
#error "Configuration claims to provide MK_TIMESTAMPCLOCKFACTOR10U but fails to do so. Please check the configuration."
#endif
#endif

#if MK_HAS_TIMESTAMPCLOCKFACTOR1U
#ifndef MK_TIMESTAMPCLOCKFACTOR1U
#error "Configuration claims to provide MK_TIMESTAMPCLOCKFACTOR1U but fails to do so. Please check the configuration."
#endif
#endif

/* Default configuration.
 * The following features are not controlled by the generator but
 * can be hand-configured by the system designer if desired.
 * If they are not defined, we assume the feature is enabled.
*/
#ifndef MK_ERRORINFO_ENABLED
#define MK_ERRORINFO_ENABLED		1
#endif

#ifndef MK_PROTECTIONINFO_ENABLED
#define MK_PROTECTIONINFO_ENABLED	1
#endif

/* Include the core configuration header files for each core that is physically present.
*/
#include <configuration/Mk_c0_cfg.h>

#if MK_MAXCORES > 1
#include <configuration/Mk_c1_cfg.h>
#endif
#if MK_MAXCORES > 2
#include <configuration/Mk_c2_cfg.h>
#endif
#if MK_MAXCORES > 3
#include <configuration/Mk_c3_cfg.h>
#endif
#if MK_MAXCORES > 4
#include <configuration/Mk_c4_cfg.h>
#endif
#if MK_MAXCORES > 5
#include <configuration/Mk_c5_cfg.h>
#endif
#if MK_MAXCORES > 6
#include <configuration/Mk_c6_cfg.h>
#endif
#if MK_MAXCORES > 7
#include <configuration/Mk_c7_cfg.h>
#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
