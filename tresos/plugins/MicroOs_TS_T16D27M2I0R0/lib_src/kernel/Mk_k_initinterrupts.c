/* Mk_k_initinterrupts.c
 *
 * This file contains the function MK_InitInterrupts().
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *  This function is only called during startup, but uses some
 *  hardware-dependent macros to configure interrupt sources.  These macros are
 *  also used after startup, and therefore call MK_Panic() in case a problem is
 *  detected. MK_Panic() will detect a call during startup and invoke
 *  MK_StartupPanic() in this case. Therefore, this MISRA violation is a false
 *  positive, the recursion can actually not happen from here.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_V(G)]
 *  The code shall adhere to the HIS metrics ([HISSRCMETRIC]).
 *
 * Reason:
 *  This function calls several hardware-specific function like macros.
 *  Such macros usually use do { } while(0) constructs.
 *  While not affecting the comprehensibility of the using code, each of these
 *  constructs increases the V(G) value.
*/


#include <public/Mk_public_types.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_isr.h>
#include <private/Mk_softvector.h>
#include <private/Mk_panic.h>

/* MK_InitInterrupts() initializes the interrupt controller and all configured interrupt sources.
 *
 * Hardware-specific functions or macros are used.
 *
 * !LINKSTO Microkernel.Function.MK_InitInterrupts, 2
 * !doctype src
*/
/* Deviation MISRAC2012-1, DCG-1 <+1> */
void MK_InitInterrupts(mk_objectid_t coreIndex, mk_boolean_t enableAtStartup)
{
	mk_objectid_t i;

	/* Ensure that the software vector table has the correct number of elements.
	 * The end marker contains an unknown interrupt with a parameter of MK_VECTOR_LASTMARK.
	 * If this is not the case, the vector table's initializer does not have the correct
	 * number of entries (probably too few).
	*/
	if ( (MK_softwareVectorTable[MK_HWN_INTERRUPTVECTORS].func != &MK_UnknownInterrupt) ||
		 (MK_softwareVectorTable[MK_HWN_INTERRUPTVECTORS].param != MK_VECTOR_LASTMARK) )
	{
		/* The last element of the array is not the end marker.
		*/
		MK_StartupPanic(MK_panic_VectorTableIncorrectlyInitialized);
	}

	/* Initialize the interrupt controller. This disables all interrupt sources.
	*/
	MK_HwInitInterruptController(enableAtStartup);

	/* Initialize the interrupt sources that are configured for the core..
	 *
	 * Note: MK_irqCfg could be NULL here, but if it is, MK_nIrqs is 0,
	 * so the loop body is not executed and the null pointer is not dereferenced.
	*/
	for ( i = 0; i < MK_nIrqs; i++ )
	{
		if ( MK_irqCfg[i].coreIndex == coreIndex )
		{
			MK_HwInitIrq(&MK_irqCfg[i]);

			if ( enableAtStartup && ((MK_irqCfg[i].flags & MK_IRQ_ENABLE) != 0u) )
			{
				MK_HwEnableIrq(&MK_irqCfg[i]);
			}
		}
	}

	/* Initialize the ISR states.
	*/
	for ( i = 0; i < MK_nIsrs; i++ )
	{
		/* Only consider ISRs on my core.
		*/
		if ( MK_isrCfg[i].threadCfg.coreIndex == coreIndex )
		{
			/* Set to ENABLED if the corresponding IRQ is "enable at startup", unless enabling is inhibited.
			*/
			if ( enableAtStartup && ((MK_isrCfg[i].irq->flags & MK_IRQ_ENABLE) != 0u) )
			{
				MK_isrCfg[i].dynamic->enabled = MK_TRUE;
			}
			else
			{
				MK_isrCfg[i].dynamic->enabled = MK_FALSE;
			}
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
