/* Ioc_RH850_compiler.h
 *
 * This file includes the appropriate Ioc_RH850_compiler_xxx.h include file depending on the chosen toolchain.
 *
 * Macros are defined that permit the same source files to be processed by the compilers of
 * all toolchains when using features such as in-line assembly language.
 *
 * The Makefiles must ensure that the IOC_TOOL macro is defined appropriately on the command line.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef IOC_RH850_COMPILER_H
#define IOC_RH850_COMPILER_H

#include <public/Ioc_defs.h>

/* Include the appropriate abstraction file for the toolchain
*/
#if (IOC_TOOL==IOC_ghs)
#include <private/RH850/Ioc_RH850_compiler_ghs.h>
#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
