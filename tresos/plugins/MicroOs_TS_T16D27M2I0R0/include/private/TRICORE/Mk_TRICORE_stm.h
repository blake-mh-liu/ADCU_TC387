/* Mk_TRICORE_stm.h - hardware module description for Tricore STM
 *
 * This header file contains a data structure that models the registers of the
 * System Timer Module on Tricore.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TRICORE_STM_H
#define MK_TRICORE_STM_H

#include <public/Mk_basic_types.h>
#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>

#ifndef MK_ASM

/* System Timer Module for Tricore
 *
 * History:
 *	Early Tricore microcontrollers had an STM without any interrupt-generating features - simply a time stamp
 *	timer. Starting with TC1796, two compare registers and associated control registers were added, including
 *	two "service request nodes" for controlling the generation of interrupts. The first versions with the
 *	interrupt capability had an error in the hardware that caused the connections from the timers to the service
 *	request nodes to be crossed. This error was corrected in version 6 of the STM.
 *
 * Description:
 *	The STM is a 64-bit counter that is driven by the peripheral clock, so the raw frequency is usually
 *	under 100 MHz. Additionally, a further prescaler can be applied to the clock control register. The
 *	speed of the clock also determines the speed of access to the registers.
 *	The STM has registers that are mapped to various ranges of the 64-bit timer, for example bits 0 to 31,
 *	bits 4 to 35, etc.
 *	The capture register latches bits 32 to 63 of the counter, so that ripple-free reading can be achieved.
 *	However, this only works if it can be guaranteed that no interruption can also read the timer. For
 *	operation with interrupts enabled, a software approach to ripple-free reading is still necessary.
 *
 *	The compare registers can be programmed with any 32-bit value, and the range of bits against which
 *	the registers are compared can be individually programmed. When a match is detected by the
 *	comparator, an interrupt can be generated.
 *
 *	On TC1.6.1 microcontrollers, the service request nodes use for controlling the interrupt priorities
 *	etc. are not within the address range of the STM, so they must be represented by a different software
 *	module (probably the interrupt controller)
 *
 *
 * Software representation:
 *	The STM is represented by a data structure with structure members representing the registers
 *	and the unused address
*/
typedef struct mk_tricorestm_s mk_tricorestm_t;

struct mk_tricorestm_s
{
	mk_reg32_t	stm_clc;		/* Clock control register */
	mk_uint32_t	reserved0[1];
	mk_uint32_t	id;				/* Module identification register (constant, so not marked volatile) */
	mk_uint32_t	reserved1[1];
	mk_reg32_t	stm_tim0;		/* bits 31..0 */
	mk_reg32_t	stm_tim1;		/* bits 35..4 */
	mk_reg32_t	stm_tim2;		/* bits 39..8 */
	mk_reg32_t	stm_tim3;		/* bits 43..12 */
	mk_reg32_t	stm_tim4;		/* bits 47..16 */
	mk_reg32_t	stm_tim5;		/* bits 51..20 */
	mk_reg32_t	stm_tim6;		/* bits 63..32 */
	mk_reg32_t	stm_cap;		/* capture register for bits 63..32 */
	mk_reg32_t	stm_cmp[2];		/* compare registers */
	mk_reg32_t	stm_cmcon;		/* compare control */
	mk_reg32_t	stm_icr;		/* interrupt control */
	mk_reg32_t	stm_iscr;		/* interrupt set/clear */
	mk_uint32_t	reserved2[3];
	mk_reg32_t	stm_tim0sv;		/* timer 0 (bits 31..0) second value */
	mk_reg32_t	stm_capsv;		/* capture register (bits 63..32) second value */
	mk_uint32_t	reserved3[36];
	mk_reg32_t	stm_ocs;		/* debug control register */
	mk_reg32_t	stm_krstclr;    /* reset status clear */
	mk_reg32_t	stm_krst1;      /* reset control 1 */
	mk_reg32_t	stm_krst0;      /* reset control 0 */
	mk_reg32_t	stm_accen1;     /* access enable 1 */
	mk_reg32_t	stm_accen0;     /* access enable 0 */
};

/* The pointer MK_timestampStm points to the STM configured as time stamp source, if the derivative
 * has multiple STMs. If there is only one STM, it is optimized to a Macro
*/
extern mk_tricorestm_t * const MK_timestampStm;

#endif


#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
