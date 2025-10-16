/* Mk_k_ppacontinue.c
 *
 * This file contains the MK_PpaContinue() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_STMT]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  This function exists for reasons of consistency and easy maintainability of
 *  a call table mechanism.
*/
/* Deviation DCG-1 <*> */
#include <private/Mk_core.h>
#include <private/Mk_errorhandling.h>

/* MK_PpaContinue()
 *
 * !LINKSTO Microkernel.Function.MK_PpaContinue, 1
 * !doctype src
*/
void MK_PpaContinue(mk_kernelcontrol_t *unused_coreVars)
{
	/* This function is intentionally empty.
	*/
	MK_PARAM_UNUSED(unused_coreVars);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
