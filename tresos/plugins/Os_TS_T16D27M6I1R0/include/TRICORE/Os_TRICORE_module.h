/* Os_TRICORE_module.h - Tricore generic hardware module header
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.3 (advisory)
 * A project should not contain unused type declarations.
 *
 * Reason:
 * The type definition is used in macro to refer type specific address.
*/

#ifndef OS_TRICORE_MODULE_H
#define OS_TRICORE_MODULE_H

#include <Os_types.h>

#ifndef OS_ASM
/*! os_tricoremodule_t
 *
 * Data structure for peripheral module header block.
 * Most of the peripheral modules on Tricore contain one of these at the
 * start of their address space, and the module needs initialisation before
 * the device can be used. We can use common code for this.
 *
 * Some peripheral modules don't implement all the registers of the header.
 * Some peripheral modules have register in the 'reserved' location.
 * None of that is of concern to us here.
*/
typedef struct os_tricoremodule_s os_tricoremodule_t;
struct os_tricoremodule_s
{
	os_reg32_t		clc;		/* Clock control register */
	os_reg32_t		reserved;	/* Some modules use this! */
	os_reg32_t		id;			/* Module identification register */
};


#if OS_TRICOREARCH == OS_TRICOREARCH_18
/* ! os_tricoreaccen_t
 *
 * Data structure for peripheral access managemement block.
 * This structure does not implement optional fields RGNLA/RGNUA but their
 * memory location is marked as reserved for structure alignement purpose.
 */
/* Deviation MISRAC2012-1 */
typedef struct os_tricoreaccen_s os_tricoreaccen_t;
struct os_tricoreaccen_s
{
	os_reg32_t		wra;		/* Write access enable register A */
	os_reg32_t		wrb;		/* Write access enable register B */
	os_reg32_t		rda;		/* Read access enable register A */
	os_reg32_t		rdb;		/* Read access enable register B */
	os_reg32_t		vm;			/* VM access enable register */
	os_reg32_t		prs;		/* PRS access enable register */
	os_reg32_t		reserved1;	/* Reserved : Region lower address */
	os_reg32_t		reserved2;	/* Reserved : Region upper address */
} ;
#endif /* OS_TRICOREARCH */




void OS_InitModule(os_tricoremodule_t *, os_uint32_t, os_uint32_t);

#endif /* OS_ASM */

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/

