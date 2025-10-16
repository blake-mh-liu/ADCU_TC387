/* Mk_TRICORE_startup.h - TRICORE start-up
 *
 * This file contains the TRICORE-specific part of the definitions for
 * the system start-up.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_STARTUP_H
#define MK_TRICORE_STARTUP_H

#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

/* The vector tables are declared in C as simple constants. They are never used as such.
 * The C code simply takes the address of the table.
*/
#ifndef MK_ASM
extern const mk_uint32_t MK_ExceptionTable;
extern const mk_uint32_t MK_StartupExceptionTable;
extern const mk_uint32_t MK_InterruptTable;
#endif

/* The boundaries of the memory reserved for CSA lists are declared in C as simple variables.
 * They are never used as such. The function that initialises the global CSA list uses these symbols
 * as the start and end of the block of RAM.
 *
 * The number of CSAs reserved for handling the "Free CSA list depleted" exception can be overridden by the
 * derivative header. The default value is 16, which should be more than enough to shut down the microkernel.
*/
#ifndef MK_ASM

/* Initialization of CSA lists.
*/
struct mk_tricorecsaentry_s
{
	mk_uint32_t rsa, rla;
};
typedef struct mk_tricorecsaentry_s mk_tricorecsaentry_t;
extern const mk_tricorecsaentry_t MK_coreCsas[MK_MAXCORES];
#endif /* MK_ASM */


#define MK_NCSAEXTRA	MK_U(16)

/* Minimum number of contexts required for our csa initialization code
 * This is the number of CSAs where we have exactly one CSA that can be
 * used without causing a CSA-list underflow exception.
*/
#define MK_NCSAMIN		(MK_NCSAEXTRA + MK_U(2))

#ifndef MK_ASM
/* The boot code address */
extern void MK_Entry2(void);
#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
