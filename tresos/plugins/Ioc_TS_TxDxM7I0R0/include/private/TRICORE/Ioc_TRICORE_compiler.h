/* Ioc_TRICORE_compiler.h
 *
 * This file includes the appropriate Ioc_TRICORE_compiler_xxx.h include file depending on the chosen toolchain.
 *
 * Macros are defined that permit the same source files to be processed by the compilers of
 * all toolchains when using features such as in-line assembly language.
 *
 * The Makefiles must ensure that the IOC_TOOL macro is defined appropriately on the command line.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef IOC_TRICORE_COMPILER_H
#define IOC_TRICORE_COMPILER_H

#include <public/Ioc_defs.h>

/* Include the appropriate abstraction file for the toolchain
*/
#if (IOC_TOOL==IOC_tasking)
#include <private/TRICORE/Ioc_TRICORE_compiler_tasking.h>
#elif (IOC_TOOL==IOC_gnu)
#include <private/TRICORE/Ioc_TRICORE_compiler_gnu.h>
#elif (IOC_TOOL==IOC_diab)
#include <private/TRICORE/Ioc_TRICORE_compiler_diab.h>
#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif

#ifndef IOC_ASM
/* IOC_TestAndTestAndSet() atomically sets the value stored at memory location 'addr' to 1,
 * after it tested that the value is 0.
 * If a call changes the value from 0 to 1, this call returns MK_TRUE.
 * Otherwise MK_FALSE is returned.
 *
 * The DSYNC is here to make sure that this function has acquire semantics concerning memory ordering.
 *
 * !LINKSTO IOC.Function.IOC_TestAndTestAndSet, 2
*/
IOC_QUAL_INLINE ioc_boolean_t IOC_TestAndTestAndSet(volatile ioc_uint32_t *) IOC_ATTR_INLINE;
IOC_QUAL_INLINE ioc_boolean_t IOC_TestAndTestAndSet(volatile ioc_uint32_t *addr)
{
	ioc_uint32_t value;

	value = *addr;
	if (value == 0u)
	{
		value = IOC_AtomicSwap(addr, 1u);
	}
	IOC_DSYNC();
	return (value == 0u);
}
#endif

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
