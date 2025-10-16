/* Mk_TRICORE_hwinitinterruptcontroller.c
 *
 * This file contains the function MK_HwInitInterruptController()
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_basic_types.h>
#include <private/Mk_core.h>
#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>
#include <private/TRICORE/Mk_TRICORE_wdt.h>
#include <private/Mk_tool.h>


#if MK_MAXCORES > 1

#if MK_MAXCORES >= 7
#error "TRICORE does not support more than 6 cores yet"
#endif

#ifndef MK_XCORE_IRQ_LIST
/* Keep this assignment here for backwards compatibility but see ASCMICROOS-5536
 * as not all derivatives support these registers
 * Define MK_XCORE_IRQ_LIST in your derivative specific header file if needed
*/

/* MK_COREARRAY expects 8 arguments */
#define MK_XCORE_IRQ_LIST \
	MK_COREARRAY(MK_SRC_GPSR20,		\
				 MK_SRC_GPSR21,		\
				 MK_SRC_GPSR22,		\
				 MK_SRC_GPSR37,		\
				 MK_SRC_GPSR41,		\
				 MK_SRC_GPSR42,		\
				 0,					\
				 0)

#endif

mk_reg32_t* const MK_TricoreXCoreSRC[MK_MAXCORES] = {
	MK_XCORE_IRQ_LIST
};

#endif


/* MK_HwInitInterruptController()
 *
 * This function programs the interrupt table's base address in the respective processor
 * register.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwInitInterruptController, 2
 * !doctype src
*/
void MK_HwInitInterruptController(mk_boolean_t unused_startup)
{
	MK_PARAM_UNUSED(unused_startup);
	/* BIV can only be programmed with ENDINIT disabled.
	*/
	MK_WriteEndinit(0);

	/* Call assembler function to set BIV with corrected table base address.
	*/
	MK_SetupInterruptTable(MK_INTVEC2BIV(&MK_InterruptTable));

	MK_WriteEndinit(1);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
