/* TRICORE-initcsalist.c
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.9 (advisory)
 * An object should be defined at block scope if its identifier only appears
 * in a single functin.
 *
 * Reason:
 * Must be enclosed by memory mapping headers.
*/

#include <Os.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_tool.h>
#include <board.h>
#include <TRICORE/Os_TRICORE_core.h>
#include <Os_kernel.h>
#include <Os_config.h>

/* Default 6 extra CSAs to handle the "short of CSAs" exception.
*/
#ifdef OS_N_CSA_EXTRA
#if (OS_N_CSA_EXTRA <= 0)
#error "OS_N_CSA_EXTRA must be greater than zero."
#endif /* (OS_N_CSA_EXTRA <= 0) */
#define N_CSA_EXTRA		OS_N_CSA_EXTRA
#else /* ! defined OS_N_CSA_EXTRA */
#define N_CSA_EXTRA		6u
#endif /* defined OS_N_CSA_EXTRA */

struct os_cx_base_s
{
	os_cx_t *base;
	os_uint32_t numCsa;
};

#include <memmap/Os_mm_const_begin.h>
/* Deviation MISRAC2012-1 */
static const struct os_cx_base_s OS_coreCsas[OS_N_CORES_MAX] = { OS_CFG_INITCORECSAS };
#include <memmap/Os_mm_const_end.h>


#include <memmap/Os_mm_code_begin.h>

/* OS_initCsaList() - initialise the free CSA list. DO NOT CALL FROM C!
 *
 * This function initialises the CSA list in internal memory.
 * Each core maintains a separate CSA list.
 *
 * This function is called via a JL instruction from the startup code,
 * and therefore must return with a special instruction (JI A11).
 * No function calls are allowed inside this function. TRICORE_CxFromAddr
 * is therefore a macro.
 *
 * WARNING: inserting code coverage instrumentation in this function might break it.
 *
 * begin is assumed to be 64-byte aligned
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitCsaList(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	register os_coreid_t core = OS_TricoreGetCoreId();
	register os_cx_t *cxarr;
	register os_uint32_t nCx;
	register os_uint32_t cx;
	register os_uint32_t i;

	cxarr = OS_coreCsas[core].base;
	nCx = OS_coreCsas[core].numCsa;

	/* Check that we have enough CSAs available:
	 * - Number of CSAs must be greater than N_CSA_EXTRA so that we have at least
	 *   1 CSA in the main list to work with before we go to exception handling
	*/
	if (nCx <= N_CSA_EXTRA)
	{
		/* can't continue: not enough CSAs */
		OS_ENDLESSLOOP();
	}

	cx = OS_CxFromAddr((os_address_t)cxarr);

	/* Head of the list.
	*/
	OS_MTCR(OS_FCX, cx);

	/* Set limit register (exception occurs when FCX gets here).
	 * This assumes that nCx is greater than N_CSA_EXTRA which is checked above.
	*/
	OS_MTCR(OS_LCX, cx + (nCx - N_CSA_EXTRA));

	/* CSA list, including "normal" CSAs and extra CSAs for handling exceptions.
	 * We initialise 1 CSA fewer than we have in this loop because the final CSA's
	 * link must be zero.
	*/
	for ( i = 0; i < (nCx - 1u); i++ )
	{
		cx++;
		cxarr[i].pcxi = cx;
	}

	/* Tail of list. Another exception occurs when FCX is 0,
	 * but we can't handle it because there are no CSAs!
	*/
	cxarr[i].pcxi = 0;

	OS_RFJL();		/* Special "return" */
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_initcsalist_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
