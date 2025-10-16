/* Mk_k_data.c
 *
 * This file contains the microkernel data (variables and constants) that don't depend on the configuration.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_startup.h>

#if MK_MAXCORES > 1

volatile mk_objectid_t MK_startupControl;

#endif

/* MK_initTest*
 * These variables permit a simple test (on startup) that the .data and .bss sections
 * have both been initialized. See MK_DataInitCheck().
*/
mk_uint32_t MK_initTestData = MK_INITTEST_VALUE;
mk_uint32_t MK_initTestBss;

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
