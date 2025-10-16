/* Mk_public_types.h
 *
 * This file declares the public data types used by the kernel.
 * Public types are always visible to the user.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 1.3 (required)
 *  There shall be no occurrence of undefined or critical unspecified behaviour.
 *
 * Reason:
 *  Information hiding. The structure should be visible in a debugger but not in
 *  the application source code.
 *
 * MISRAC2012-2) Deviated Rule: 20.7 (required)
 *  Expressions resulting from the expansion of macro parameters shall be
 *  enclosed in parentheses.
 *
 * Reason:
 *  The macro parameters of MK_OFFSETOF denote a type name and a structure member name.
 *  Parentheses are not applicable in these cases.
 *
 * MISRAC2012-3) Deviated Rule: 5.7 (required)
 *  A tag name shall be a unique identifier.
 *
 * Reason:
 *  False positive: struct is legally used in type definition.
 *
 * MISRAC2012-4) Deviated Rule: 11.1 (required)
 *  Conversions shall not be performed between a pointer to a function and any
 *  other type.
 *
 * Reason:
 *  The macro 'MK_OFFSETOF()' must convert function pointers to integers,
 *  because the offset of their structure members, where they are stored,
 *  shall be determined. This offset is an integer number.
 *
 * MISRAC2012-5) Deviated Rule: 11.9 (required)
 *  The macro NULL shall be the only permitted form of integer null pointer
 *  constant.
 *
 * Reason:
 *  The macro 'MK_OFFSETOF' uses the literal constant '0' as pointer to a
 *  non-existent  object to determine offsets of its members. This pointer,
 *  though, is never dereferenced.
 *
 * MISRAC2012-6) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * Native types for the OS, required for Dir 4.6.
 * Unused typedefs are either present for completeness or are used by certain architectures.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef and the defined-preprocessor operator shall not be used.
 *
 * Reason:
 *  These constructs are necessary here because the macros EB_STATIC_CHECK and
 *  EB_SEMANTIC_CHECK are provided by external tooling outside the control of
 *  the microkernel build. These macros are used to hide tool specific extensions
 *  which would otherwise mislead a MISRA-C checker. The corresponding #else
 *  is used to prevent the repetition of the criticized constructs.
*/

#ifndef MK_PUBLIC_TYPES_H
#define MK_PUBLIC_TYPES_H

#include <public/Mk_basic_types.h>
#include <public/Mk_misra.h>

/* MK_NULL
 *
 * A null pointer constant
*/
#define MK_NULL		((void *) 0)

/* mk_boolean_t
 *
 * A boolean type with values MK_TRUE and MK_FALSE.
 * For use where efficiency is more important than size.
 * Not for use in data structures where size is important.
*/
#define MK_FALSE	0
#define MK_TRUE		1

#ifndef MK_ASM
typedef mk_int_t	mk_boolean_t;
#endif

/* mk_parametertype_t
 *
 * A scalar type that's large enough to hold a system-service parameter or a result code.
*/
#ifndef MK_ASM
typedef mk_address_t	mk_parametertype_t;
#endif

#define MK_PARAMETERTYPE_INVALID	0xffffffffu
#define MK_NULLCOOKIE				0x0u

/* mk_statusandvalue_t
 *
 * A structure type that holds a dual return value (status code and requested value)
*/
#ifndef MK_ASM
typedef struct mk_statusandvalue_s mk_statusandvalue_t;

struct mk_statusandvalue_s
{
	mk_parametertype_t statusCode;
	mk_parametertype_t requestedValue;
};
#endif

/* mk_reg8_t, mk_reg16_t, mk_reg32_t, mk_reg64_t
 *
 * Types for hardware registers; volatile uint types.
*/
/* Deviation MISRAC2012-6 <START> */
#ifndef MK_ASM
typedef volatile mk_uint8_t mk_reg8_t;
typedef volatile mk_uint16_t mk_reg16_t;
typedef volatile mk_uint32_t mk_reg32_t;
#if MK_HAS_INT64
typedef volatile mk_uint64_t mk_reg64_t;
#endif /* MK_HAS_INT64 */
#endif
/* Deviation MISRAC2012-6 <STOP> */

/* Task states. One of these values is returned by GetTaskState(). Casting to the appropriate
 * type in the debugger will reveal the symbol
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
#ifndef MK_ASM
enum mk_taskstate_e
{
	MK_TS_INVALID,
	SUSPENDED,
	READY,
	RUNNING,
	WAITING
};
typedef enum mk_taskstate_e mk_taskstate_t;
#endif

/* Object ID type. Used for TaskType etc. and internally for things like partition indexes.
 *
 * The object id is signed for two reasons:
 * - permit the use of (-1) for unknown/invalid etc.
 * - reduce the amount of MISRA-mandated typecasting and suffixes
 *
 * Object quantity is simply an integer large enough to hold the number of any type of object.
 *
 * Object type. Used publicly in the error and protection information structures to identify
 * the object type (task, isr etc.)
*/
#ifndef MK_ASM
typedef mk_int_t	mk_objectid_t;
typedef mk_int_t	mk_objquantity_t;

/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_objecttype_e
{
	MK_OBJTYPE_KERNEL,			/* Objects belonging to the microkernel */
	MK_OBJTYPE_TASK,			/* Task objects belonging to the user */
	MK_OBJTYPE_ISR,				/* ISR objects belonging to the user */
	MK_OBJTYPE_CTRSUB,			/* API objects belonging to the counter subsystem */
	MK_OBJTYPE_CTRSUBISR,		/* ISR objects belonging to the counter subsystem */
	MK_OBJTYPE_SHUTDOWNHOOK,	/* A shutdown-hook */
	MK_OBJTYPE_ERRORHOOK,		/* An error-hook */
	MK_OBJTYPE_PROTECTIONHOOK,	/* The protection-hook */
	MK_OBJTYPE_TRUSTEDFUNCTION,	/* A trusted function */
	MK_OBJTYPE_UNKNOWN			/* Must be last */
};

typedef enum mk_objecttype_e mk_objecttype_t;
#endif

#define MK_OBJECTID_INVALID		(-1)

#ifndef MK_ASM

/* A lock ID contains the index and the core ID packed into a 32-bit word.
*/
typedef mk_uint32_t mk_lockid_t;

/* A macro to pack a lock index and core index into a lock ID
*/
#if MK_MAXCORES > 1
#define MK_MakeLockId(c, i)		(MK_ShiftLeftU32((c), 16) | (mk_uint32_t)(i))
#else
#define MK_MakeLockId(c, i)		((mk_uint32_t)(i))
#endif

/* mk_appstatetype_e provides an enumeration type containing all states an OS-Application can be in
 * Used to quarantine OS-Applications.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_appstate_e
{
	APPLICATION_ACCESSIBLE,
	APPLICATION_RESTARTING,
	APPLICATION_TERMINATED
};
typedef enum mk_appstate_e mk_appstate_t;

/* mk_corestate_e provides an enumeration type containing all core states.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_corestate_e
{
	MK_coreState_Init = 0,		/* Initial value at startup */
	MK_coreState_Startup,		/* Microkernel is running but core has not yet been "started" */
	MK_coreState_Run,			/* Microkernel is running, core has been "started" */
	MK_coreState_OsRun,			/* Microkernel is running, StartOS has been called */
	MK_coreState_Down,			/* Microkernel is running, core has been shut down */
	MK_coreState_PanicStop,		/* Microkernel is not running. Double panic */
	MK_coreState_Invalid		/* Must be last */
};
typedef enum mk_corestate_e mk_corestate_t;

#endif

/* Invalid task and ISR IDs.
*/
#define MK_INVALID_TASK		MK_OBJECTID_INVALID
#define MK_INVALID_ISR		MK_OBJECTID_INVALID
#define MK_APPL_NONE		MK_OBJECTID_INVALID

/* Incomplete definitions of the thread structure.
 * This is needed:
 *  - for the cross-referencing between structures
 *  - for public error handling structures (to make objects visible in the debugger without exposing their internals)
*/
#ifndef MK_ASM
/* Deviation MISRAC2012-1, MISRAC2012-3 */
typedef struct mk_thread_s mk_thread_t;
/* Note: MISRA-C:2012 Dir 4.8 advises that incomplete declarations should be used where possible
*/
#endif

/* MK_OFFSETOF(type, member) - determine the offset of structure member "member" of type "type".
 *
 * MISRA note:
 * The 0 cast to a pointer isn't a NULL dereference, since we only take the address and then cast
 * it to mk_address_t.
 */
/* Deviation MISRAC2012-2 <+6>, MISRAC2012-4 <+6>, DCG-1 <+1> */
#if defined(EB_SEMANTIC_CHECK) && (EB_SEMANTIC_CHECK!=0)
#define MK_OFFSETOF(type, member)		(((mk_address_t)&((type *)0xdeadbeef)->member)-0xdeadbeef)
#else
/* Deviation MISRAC2012-5 <+1> */
#define MK_OFFSETOF(type, member)		((mk_address_t)&((type *)0)->member)
#endif

/* mk_tick_t and mk_time_t
 *
 * These data types are used by the time stamp functions and other timing features provided by the microkernel.
 *
 * mk_tick_t is a (at least) 32-bit unsigned variable that can be used for short intervals
 * mk_time_t is a 64-bit unsigned variable (implemented using a struct on 32-bit processors). It can be used for
 *           absolute time and long intervals.
 * MK_MAXTICK is the largest value an mk_tick_t can hold. It is sometimes used to represent "infinite"
 *
 * Note: mk_tick_t must have the same type (size) as os_tick_t.
*/
#if MK_HAS_INT64
#define MK_MAXTICK		0xffffffffffffffffuL
#else
#define MK_MAXTICK		0xffffffffu
#endif

#ifndef MK_ASM

#if MK_HAS_INT64
/* mk_tick_t for 64-bit processors. */
typedef mk_uint64_t mk_tick_t;

/* mk_time_t for 64-bit processors. */
typedef mk_uint64_t mk_time_t;

#else
/* mk_tick_t for 32-bit processors. */
typedef mk_uint32_t mk_tick_t;

/* mk_time_t for 32-bit processors.
 * Note that the order of the words follows the endianness of the hardware.
*/
typedef struct mk_time_s mk_time_t;

struct mk_time_s
{
#if MK_ENDIAN == MK_BIGENDIAN
	mk_uint32_t timeHi;
	mk_uint32_t timeLo;
#else
	mk_uint32_t timeLo;
	mk_uint32_t timeHi;
#endif
};
#endif /* MK_HAS_INT64 */

#endif

/* Offsets for low-/high word in mk_time_s for usage in assembly files.
*/
#if MK_ENDIAN == MK_BIGENDIAN
#define MK_TIME_LOW		4
#define MK_TIME_HIGH	0
#else
#define MK_TIME_LOW		0
#define MK_TIME_HIGH	4
#endif

/* Initial value and data type for OsAppMode.
 * Note: The counter subsystem must make sure that OS_INCONSISTENT_APPMODE (defined by the counter subsystem)
 *       equals MK_UNINITIALIZED_APPMODE.
*/
#define MK_UNINITIALIZED_APPMODE		MK_U(254)

/* To provide an Autosar API, the MK must offer DONOTCARE.
 * Note: The counter subsystem must make sure that OS_NULLAPPMODE (defined by the counter subsystem)
 *       equals MK_DONOTCARE_APPMODE.
*/
#define MK_DONOTCARE_APPMODE			MK_U(255)

#ifndef MK_ASM
typedef mk_uint8_t mk_appmodeid_t;
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
