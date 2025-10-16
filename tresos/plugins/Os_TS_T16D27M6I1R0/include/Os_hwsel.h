/* Os_hwsel.h
 *
 * This file provides characteristics of the current derivative's cpu.
 * It includes the target specific Os_*_cpu.h file.
*/
#ifndef OS_HWSEL_H
#define OS_HWSEL_H

/* Architecture specific defines */
#define OS_HWSEL_ATOMICS    <TRICORE/Os_atomics_TRICORE.h>
#define OS_HWSEL_API        <TRICORE/Os_api_TRICORE.h>
#define OS_HWSEL_CPU        <TRICORE/Os_TRICORE_cpu.h>
#define OS_HWSEL_DEFS       <TRICORE/Os_defs_TRICORE.h>
#define OS_HWSEL_KERNEL     <TRICORE/Os_kernel_TRICORE.h>
#define OS_HWSEL_MMU        <TRICORE/Os_mmu_TRICORE.h>
#define OS_HWSEL_PROTO      <TRICORE/Os_proto_TRICORE.h>
#define OS_HWSEL_TOOL       <TRICORE/Os_tool_TRICORE.h>
#define OS_HWSEL_TYPES      <TRICORE/Os_types_TRICORE.h>
#define OS_HWSEL_ERRORCODES <TRICORE/Os_errorcodes_TRICORE.h>

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
