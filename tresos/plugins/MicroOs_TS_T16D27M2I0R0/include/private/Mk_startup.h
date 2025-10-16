/* Mk_startup.h - system start-up
 *
 * This file contains definitions for the hardware-independent part of the
 * system start-up. It also includes the hardware-specific part.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_STARTUP_H
#define MK_STARTUP_H

#include <public/Mk_hwsel.h>
#include <public/Mk_basic_types.h>
#include <public/Mk_hw_characteristics.h>
#include <private/Mk_core.h>

/* Include the hardware-specific startup declarations
*/
#include MK_HWSEL_PRV_STARTUP

#include <public/Mk_misra.h>

/* MK_STARTKEY_x, MK_TRANSKEY_x
 *
 * Two 128-bit "keys" that get passed through the startup phases with transformations.
 * The values were generated randomly (dd if=/dev/random bs=1 count=16 | hd)
 *
 * The MK_STARTKEY_x macros define the starting key (k1-k4).
 * The MK_TRANSKEY_x macros define the intermediate transformation key (k'1-k'4).
 *
 * A transformation is applied at the call to MK_Startup(p1,p2,p3,p4):
 * p1 = k2 ^ k3
 * p2 = k3 ^ k4
 * p3 = k4 ^ k1
 * p4 = k1 ^ k2
 *
 * A further transformation is applied at the call to MK_StartKernel(q1,q2,q3,q4):
 * q1 = p2 ^ k'1
 * q2 = p3 ^ k'2
 * q3 = p4 ^ k'3
 * q4 = p1 ^ k'4
 * ( x ^ x = 0 for all x )
 *
 * MISRA-C: some of the keys are used in assembly-language code so cannot have a 'u' suffix.
 * However, MISRA checkers complain a lot about type mismatches etc., so there are two versions of
 * those keys.
*/
#define	MK_STARTKEY_1		0x752cfab3
#define MK_STARTKEY_2		0x1e73d060
#define MK_STARTKEY_3		0xc28d584e
#define MK_STARTKEY_4		0x33679682

#define MK_MIDDLEKEY_1		(MK_U(MK_STARTKEY_2) ^ MK_U(MK_STARTKEY_3))
#define MK_MIDDLEKEY_2		(MK_U(MK_STARTKEY_3) ^ MK_U(MK_STARTKEY_4))
#define MK_MIDDLEKEY_3		(MK_U(MK_STARTKEY_4) ^ MK_U(MK_STARTKEY_1))
#define MK_MIDDLEKEY_4		(MK_U(MK_STARTKEY_1) ^ MK_U(MK_STARTKEY_2))

#define MK_TRANSKEY_1		0xc48751b7
#define MK_TRANSKEY_2		0xf83def3a
#define MK_TRANSKEY_3		0x9c10e024
#define MK_TRANSKEY_4		0x1643e0c0

#define MK_ENDKEY_1			(MK_U(MK_STARTKEY_3) ^ MK_U(MK_STARTKEY_4) ^ MK_U(MK_TRANSKEY_1))
#define MK_ENDKEY_2			(MK_U(MK_STARTKEY_4) ^ MK_U(MK_STARTKEY_1) ^ MK_U(MK_TRANSKEY_2))
#define MK_ENDKEY_3			(MK_U(MK_STARTKEY_1) ^ MK_U(MK_STARTKEY_2) ^ MK_U(MK_TRANSKEY_3))
#define MK_ENDKEY_4			(MK_U(MK_STARTKEY_2) ^ MK_U(MK_STARTKEY_3) ^ MK_U(MK_TRANSKEY_4))

#ifndef MK_ASM

/* Processor-dependent kernel/processor initialization
*/
void MK_HwInitProcessor(void);

/* Hardware-independent startup functions
*/
void MK_Startup(mk_uint32_t, mk_uint32_t, mk_uint32_t, mk_uint32_t);
void MK_InitDataSections(void);

/* MK_StartupInitDataSections is a helper function for MK_Startup which calls MK_InitDataSections
 *
 * In multi-core systems we have to take care of synchronization variables during memory initialization.
 * In single-core systems no synchronization is required.
*/
#if (MK_MAXCORES > 1)
void MK_StartupInitDataSectionsMulti(void);
#define MK_StartupInitDataSections MK_StartupInitDataSectionsMulti
#else
#define MK_StartupInitDataSections MK_InitDataSections
#endif


/* MK_DataInitCheck()
 * Checks that the .data and .bss sections have been initialized during startup.
*/
#define MK_INITTEST_VALUE	0xEB5AFE05u
#define MK_INITTEST_TRASH	0x0BADC0DEu

extern mk_uint32_t MK_initTestData;
extern mk_uint32_t MK_initTestBss;
void MK_DataInitCheck(mk_uint32_t, mk_uint32_t, mk_uint32_t, mk_uint32_t);

#if (MK_MAXCORES > 1)
extern mk_uint32_t * const MK_initTestDataTable[MK_MAXCORES];
extern mk_uint32_t * const MK_initTestBssTable[MK_MAXCORES];
#endif

/* MK_startupControl - used on multi-core systems for controlling the startup sequence.
*/
extern volatile mk_objectid_t MK_startupControl;

/* MK_kernelStackTop
 *
 * This constant defines the initial stack pointer for the microkernel.
*/
extern mk_stackelement_t * const MK_kernelStackTop[MK_MAXCORES];

#endif

#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
