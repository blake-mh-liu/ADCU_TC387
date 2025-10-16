/* Mk_TRICORE_board_startupautosarcores.c
 *
 * This file contains the TRICORE startup function Tmpl_StartupAutosarCores()
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_board_startupautosarcores.c 30109 2017-08-21 12:50:54Z vaka852 $
*/
#include <private/TRICORE/Mk_TRICORE_startup.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/Mk_core.h>
#include <Mk_TRICORE_board_startup.h>


#if (MK_MAXCORES < 2)
#error "Mk_TRICORE_board_startupautosarcores.c is not used in single-core systems. Check your makefiles!"
#endif

/* CSFR IDs/offsets */
#define TMPL_DBGSR	0xfd00	/* Debug status register */
#define TMPL_PC		0xfe08	/* Program counter */
#define TMPL_D0		0xff00	/* Data Register 0 */
#define TMPL_D1		0xff04	/* Data Register 1 */
#define TMPL_D2		0xff08	/* Data Register 2 */
#define TMPL_D3		0xff0c	/* Data Register 3 */
#define TMPL_D4		0xff10	/* Data Register 4 */
#define TMPL_D5		0xff14	/* Data Register 5 */
#define TMPL_D6		0xff18	/* Data Register 6 */
#define TMPL_D7		0xff1c	/* Data Register 7 */
#define TMPL_D8		0xff20	/* Data Register 8 */
#define TMPL_D9		0xff24	/* Data Register 9 */
#define TMPL_D10	0xff28	/* Data Register 10 */
#define TMPL_D11	0xff2c	/* Data Register 11 */
#define TMPL_D12	0xff30	/* Data Register 12 */
#define TMPL_D13	0xff34	/* Data Register 13 */
#define TMPL_D14	0xff38	/* Data Register 14 */
#define TMPL_D15	0xff3c	/* Data Register 15 */
#define TMPL_A0		0xff80	/* Address Register 0 */
#define TMPL_A1		0xff84	/* Address Register 1 */
#define TMPL_A2		0xff88	/* Address Register 2 */
#define TMPL_A3		0xff8c	/* Address Register 3 */
#define TMPL_A4		0xff90	/* Address Register 4 */
#define TMPL_A5		0xff94	/* Address Register 5 */
#define TMPL_A6		0xff98	/* Address Register 6 */
#define TMPL_A7		0xff9c	/* Address Register 7 */
#define TMPL_A8		0xffa0	/* Address Register 8 */
#define TMPL_A9		0xffa4	/* Address Register 9 */
#define TMPL_A10	0xffa8	/* Address Register 10 */
#define TMPL_A11	0xffac	/* Address Register 11 */
#define TMPL_A12	0xffb0	/* Address Register 12 */
#define TMPL_A13	0xffb4	/* Address Register 13 */
#define TMPL_A14	0xffb8	/* Address Register 14 */
#define TMPL_A15	0xffbc	/* Address Register 15 */

/* Bit definitions for DBGSR. */
#define TMPL_DBGSR_DE_MASK		MK_U(0x00000001)	/* mask to get the DE-field */
#define TMPL_DBGSR_HALT_MASK	MK_U(0x00000006)	/* mask to get the HALT-field */

#define TMPL_DBGSR_DE_DISABLE	MK_U(0x00000000)	/* disable DE flag */
#define TMPL_DBGSR_DE_ENABLE	MK_U(0x00000001)	/* enable DE flag */
#define TMPL_DBGSR_HALT_HALTED	MK_U(0x00000002)	/* processor halted */
#define TMPL_DBGSR_HALT_RUNNING	MK_U(0x00000000)	/* processor running */
#define TMPL_DBGSR_HALT_WE		MK_U(0x00000004)	/* enable change of HALT-bit on write */

/* TMPL_MTCCR
 *
 * Writes a value to a CR of another core using the memory mapped mirror of the core registers
*/
#define TMPL_MTCCR(csfrBase, csfrId, val) (*((volatile mk_uint32_t *)(((mk_uint32_t)(csfrBase))+(csfrId)))=(val))

/* TMPL_MFCCR
 *
 * Reads the value from a CR of another core using the memory mapped mirror of the core registers
*/
#define TMPL_MFCCR(csfrBase, csfrId) (*((volatile mk_uint32_t *)(((mk_uint32_t)(csfrBase))+(csfrId))))

/* Base addresses for the memory mapped mirror of the core registers
*/
#define TMPL_CPUSFR_0	MK_U(0xF8800000)
#define TMPL_CPUCSFR_0	MK_U(0xF8810000)
#define TMPL_CPUSFR_1	MK_U(0xF8820000)
#define TMPL_CPUCSFR_1	MK_U(0xF8830000)
#define TMPL_CPUSFR_2	MK_U(0xF8840000)
#define TMPL_CPUCSFR_2	MK_U(0xF8850000)
#define TMPL_CPUCSFR(coreid) \
	(((coreid)==1) ? ((mk_uint32_t)TMPL_CPUCSFR_1) \
	               : (((coreid)==2) ? ((mk_uint32_t)TMPL_CPUCSFR_2) \
	                                : ((mk_uint32_t)TMPL_CPUCSFR_0) \
	                 ) \
	)

/* Tmpl_StartupAutosarCores
 *
 * This function is used by the demo, to start all cores, which are configured to run under
 * control of this OS.
*/
void Tmpl_StartupAutosarCores(void)
{
	register mk_uint32_t const myOwnCoreId = (mk_uint32_t) MK_HwGetCoreIndex();
	register mk_uint32_t coreId;
	for (coreId = 0; coreId < MK_MAXCORES; ++coreId)
	{
		if ((coreId != myOwnCoreId) && ((MK_coreProperties[coreId] & MK_COREPROP_STARTMASK) != MK_COREPROP_NOTUSED))
		{
			register mk_uint32_t dbgsr;
			register mk_uint32_t cfsrBase = TMPL_CPUCSFR(coreId);

			/* check if core is really halted; core is only set up if it is not running */
			dbgsr = TMPL_MFCCR(cfsrBase, TMPL_DBGSR);
			if ( (dbgsr & TMPL_DBGSR_HALT_MASK) == TMPL_DBGSR_HALT_HALTED )
			{
				/* Set the PSW */
				TMPL_MTCCR(cfsrBase, MK_PSW, MK_INITIAL_PSW);

				/* Let the core start in MK_Entry, which performs some preparations
				 * and then jumps to MK_Entry2, which starts the microkernel.
				*/
				TMPL_MTCCR(cfsrBase, TMPL_PC, (mk_uint32_t)&MK_Entry);

				/* MK_Entry is not meant to return */
				TMPL_MTCCR(cfsrBase, TMPL_A11, 0u);

				/* Reset Halt */
				dbgsr = (dbgsr & (~((mk_uint32_t)TMPL_DBGSR_HALT_MASK)))
						| TMPL_DBGSR_HALT_WE | TMPL_DBGSR_HALT_RUNNING | TMPL_DBGSR_DE_ENABLE;
				TMPL_MTCCR(cfsrBase, TMPL_DBGSR, dbgsr);
			}
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
