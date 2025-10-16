/* Mk_TRICORE_exceptioninfo.h - public TRICORE exception information
 *
 * This file contains the public definitions and declarations for
 * the exception information structure on TRICORE processors.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * Type is used in some translation units.
*/

#ifndef MK_TRICORE_EXCEPTIONINFO_H
#define MK_TRICORE_EXCEPTIONINFO_H

#include <public/Mk_basic_types.h>

/* MK_ExceptionClasssTinToType() converts an exception class/TIN combination to a unique
 * enumeration in mk_exceptiontype_t
 *
 * !LINKSTO	Microkernel.TRICORE.ExceptionHandling.ExceptionInfo, 3
 * !doctype src
*/
#define MK_ExceptionClassTinToTypeBits(c,t)	((((mk_uint32_t)(c)) << 8u) | ((mk_uint32_t)(t)))
#define MK_ExceptionClassTinToType(c,t)		((mk_exceptiontype_t) MK_ExceptionClassTinToTypeBits((c), (t)))

#ifndef MK_ASM
/* mk_exceptionclass_e enumerates all the different classes of exception on the TriCore processor family.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_exceptionclass_e
{
	MK_exc_VirtualAddress = 0,
	MK_exc_InternalProtection = 1,
	MK_exc_InstructionError = 2,
	MK_exc_ContextManagement = 3,
	MK_exc_SystemBus = 4,
	MK_exc_Assertion = 5,
	MK_exc_Syscall = 6,
	MK_exc_NMI = 7,

	/* This is the interrupt pseudo exception class.
	 * In the type bits, the lower byte contains the vector code.
	 * Make sure that this number never collides with a real exception class.
	*/
	MK_exc_Interrupt = 15
};
#endif

/* TINs of exception class 0 - Virtual Address
*/
#define MK_TIN_VirtualAddressFill					MK_U(0)
#define MK_TIN_VirtualAddressProtection				MK_U(1)

/* TINs of exception class 1 - Internal Protection Traps
*/
#define MK_TIN_PrivilegedInstruction				MK_U(1)
#define MK_TIN_MemoryProtectionRead					MK_U(2)
#define MK_TIN_MemoryProtectionWrite				MK_U(3)
#define MK_TIN_MemoryProtectionExecution			MK_U(4)
#define MK_TIN_MemoryProtectionPeripheralAccess		MK_U(5)
#define MK_TIN_MemoryProtectionNullAddress			MK_U(6)
#define MK_TIN_GlobalRegisterWriteProtection		MK_U(7)

/* TINs of exception class 2 - Instruction Errors
*/
#define MK_TIN_IllegalOpcode						MK_U(1)
#define MK_TIN_UnimplementedOpcode					MK_U(2)
#define MK_TIN_InvalidOperandspecification			MK_U(3)
#define MK_TIN_DataAddressAlignment					MK_U(4)
#define MK_TIN_InvalidLocalMemoryAddress			MK_U(5)

/* TINs of exception class 3 - Context Management
*/
#define MK_TIN_FreeContextListDepletionFcxEqLcx		MK_U(1)
#define MK_TIN_CallDepthOverflow					MK_U(2)
#define MK_TIN_CallDepthUnderflow					MK_U(3)
#define MK_TIN_FreeContextListUnderflowFcxEq0		MK_U(4)
#define MK_TIN_CallStackUnderflowPcxEq0				MK_U(5)	/* Handled as thread termination by return, no error */
#define MK_TIN_ContextTypePcxiUlWrong				MK_U(6)
#define MK_TIN_NestingErrorRfeNonZeroCallDepth		MK_U(7)

/* TINs of exception class 4 - System Bus and Peripheral Errors
*/
#define MK_TIN_ProgramFetchSynchronousError			MK_U(1)
#define MK_TIN_DataAccessSynchronousError			MK_U(2)
#define MK_TIN_DataAccessAsynchronousError			MK_U(3)
#define MK_TIN_CoprocessorTrapAsynchronousError		MK_U(4)
#define MK_TIN_ProgramMemoryIntegrityError			MK_U(5)
#define MK_TIN_DataMemoryIntegrityError				MK_U(6)
#define MK_TIN_TemporalAsynchronousError			MK_U(7)

/* TINs of exception class 5 - Assertion Traps
*/
#define MK_TIN_ArithmeticOverflow					MK_U(1)
#define MK_TIN_StickyArithmeticOverflow				MK_U(2)

/* TINs of exception class 7 - Non-Maskable Interrupt
*/
#define MK_TIN_NonMaskableInterrupt					MK_U(0)

#ifndef MK_ASM
/* mk_exceptiontype_e enumerates all the different types of exception on the Tricore processor family.
 *
 * This is intended to display the trap class and TIN combination symbolically in the debugger.
 * For use in software it is better to use the trap class and TIN identifications.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_exceptiontype_e
{
	MK_ex_VirtualAddressFill				= 0x000,
	MK_ex_VirtualAddressProtection			= 0x001,

	MK_ex_PrivilegedInstruction				= 0x101,
	MK_ex_MemoryProtectionRead				= 0x102,
	MK_ex_MemoryProtectionWrite				= 0x103,
	MK_ex_MemoryProtectionExecution			= 0x104,
	MK_ex_MemoryProtectionPeripheralAccess	= 0x105,
	MK_ex_MemoryProtectionNullAddress		= 0x106,
	MK_ex_GlobalRegisterWriteProtection		= 0x107,

	MK_ex_IllegalOpcode						= 0x201,
	MK_ex_UnimplementedOpcode				= 0x202,
	MK_ex_InvalidOperandspecification		= 0x203,
	MK_ex_DataAddressAlignment				= 0x204,
	MK_ex_InvalidLocalMemoryAddress			= 0x205,

	MK_ex_FreeContextListDepletionFcxEqLcx	= 0x301,
	MK_ex_CallDepthOverflow					= 0x302,
	MK_ex_CallDepthUnderflow				= 0x303,
	MK_ex_FreeContextListUnderflowFcxEq0	= 0x304,
	MK_ex_CallStackUnderflowPcxEq0			= 0x305,	/* Handled as thread termination by return; never reported */
	MK_ex_ContextTypePcxiUlWrong			= 0x306,
	MK_ex_NestingErrorRfeNonZeroCallDepth	= 0x307,

	MK_ex_ProgramFetchSynchronousError		= 0x401,
	MK_ex_DataAccessSynchronousError		= 0x402,
	MK_ex_DataAccessAsynchronousError		= 0x403,
	MK_ex_CoprocessorTrapAsynchronousError	= 0x404,
	MK_ex_ProgramMemoryIntegrityError		= 0x405,
	MK_ex_DataMemoryIntegrityError			= 0x406,
	MK_ex_TemporalAsynchronousError			= 0x407,

	MK_ex_ArithmeticOverflow				= 0x501,
	MK_ex_StickyArithmeticOverflow			= 0x502,

	MK_ex_SystemCall						= 0x600,	/* For completeness; never reported */
	MK_ex_NonMaskableInterrupt				= 0x700,	/* upcoming versions may be split this to be more detailed */
	MK_ex_Interrupt							= 0xf00,	/* For completeness; never reported */

	MK_ex_UnknownClassTinCombination		= 0xfff
};

typedef enum mk_exceptionclass_e mk_exceptionclass_t;
typedef mk_uint32_t mk_exceptiontin_t;
typedef enum mk_exceptiontype_e mk_exceptiontype_t;
/* Deviation MISRAC2012-1 <+1> */
typedef mk_exceptiontype_t mk_hwexceptiontype_t;

/* mk_exceptioninfo_s - exception info structure
 *
 * excClass and excTin are defined by Infineon:
 * - excClass is the class (the vector number)
 * - excTin is the Trap Identification Number (TIN) that is provided in D15.
 *
 * type is constructed by combining the class and TIN to give a unique number.
*/
typedef struct mk_exceptioninfo_s mk_hwexceptioninfo_t;

/*
 * Exception info structure
 *
 * The Tricore implementation of this structure contains the following fields:
 *
 * type:		The type of trap, its encoded value encodes both the trap class and the trap identification number.
 * excClass:	Contains the trap class.
 * excTin:		Contains the trap identification number (TIN), that identifies the trap within its class
 *
 * The following fields are named after the registers whose values they store. They only contain meaningful values for
 * some types of traps. This is dependent on the particular Tricore implementation. Refer to the processor manual for
 * details.
 *
 * dstr:	Data Synchronous Error Trap Register, may contain information on the type of data synchronous
 *			error
 * datr:	Data Asynchronous Error Trap Register, may contain information on the type of data asynchronous
 *			error
 * deadd:	Data Error Address Register, may contain information on the location of the data error
 * pstr:	Program Synchronous Error Trap Register, may contain information on the type of program synchronous error
 * dietr:	Data Integrity Error Trap Register, may contain information allowing software to localize the source of the
 *			last detected data memory integrity error
 * diear:	Data Integrity Error Address Register, contains the address accessed by the last operation that caused a
 *			data memory integrity error
 * pietr:	Program Integrity Error Trap Register, contains information allowing software to localize the source of the
 *			last detected program memory integrity error
 * piear:	Program Integrity Error Address Register, contains the address accessed by the last operation that caused a
 *			program memory integrity error
 *
 * !LINKSTO	Microkernel.TRICORE.ExceptionHandling.ExceptionInfo, 3
 * !doctype src
*/
struct mk_exceptioninfo_s
{
	/* Hardware-independent fields */
	mk_exceptiontype_t type;		/* Exception type (Unique: combines class and TIN) */
	/* Hardware-dependent fields */
	mk_exceptionclass_t excClass;	/* Exception class (Identifies vector) */
	mk_exceptiontin_t excTin;		/* Exception detail (TIN from D15) */

	/* Additional exception information fields */
	mk_uint32_t dstr;
	mk_uint32_t datr;
	void * deadd;

	mk_uint32_t pstr;
	mk_uint32_t dietr;
	void * diear;
	mk_uint32_t pietr;
	void * piear;

	/* Registers at the time of the exception.
	 * These pointers are only valid for panic exception infos.
	 * If these pointers are NULL, no context information is available.
	 * For regular exception infos, these pointers become invalid
	 * the latest, when the thread which caused the exception is terminated.
	*/
	mk_lowerctx_t *lowerCtx;
	mk_upperctx_t *upperCtx;
};
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
