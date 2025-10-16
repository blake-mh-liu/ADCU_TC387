/* Mk_timeconversion.h
 *
 * This file defines a collection of time conversion macros (ns-to-ticks and ticks-to-ns)
 * for various frequencies.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_020]
 *  The conditional operator ?: shall not be used.
 *
 * Reason:
 *  The macro is intended to be used for initializing constants, so neither an if ... else construct
 *  nor a function call is possible.
*/
#ifndef MK_TIMECONVERSION_H
#define MK_TIMECONVERSION_H

#include <public/Mk_basic_types.h>
#include <public/Mk_public_api.h>

/* !LINKSTO Microkernel.Timestamp.NsToTicks_Macro, 1,
 * !        Microkernel.Timestamp.TicksToNs_Macro, 1,
 * !        Microkernel.Timestamp.NsToTicks_Function, 1,
 * !        Microkernel.Timestamp.TicksToNs_Function, 1
 * !doctype src
*/

/* Commonly-used macros:
 *
 * MK_DivMulDiv() performs the divide-multiply-divide operation used in many ns-to-ticks calculations.
 * MK_MulDivMul() performs the multiply-divide-multiply operation used in many ticks-to-ns calculations.
 * MK_DivMul() divides and then multiplies. Don't confuse it with MK_MulDiv, which is a function.
 * MK_SatMulDivMul() performs MK_MulDivMul(), but with a saturation test first.
 * MK_SatDivMul() performs MK_DivMul(), but with a saturation test first.
*/
#define MK_DivMulDiv(x, d1, m, d2)				(((((mk_uint32_t)(x))/(d1))*(m))/(d2))
#define MK_MulDivMul(x, m1, d, m2)				(((((mk_uint32_t)(x))*(m1))/(d))*(m2))
#define MK_DivMul(x, d, m)						((((mk_uint32_t)(x))/(d))*(m))
/* Deviation DCG-1 <+2> */
#define MK_SatMulDivMul(x, m1, d, m2, max)		(((x)>(max)) ? 0xffffffffu : MK_MulDivMul((x),(m1),(d),(m2)))
#define MK_SatDivMul(x, d, m, max)				(((x)>(max)) ? 0xffffffffu : MK_DivMul((x),(d),(m)))

/* Clock frequency 10 kHz
*/
#define MK_NsToTicks_10000(ns)					((ns)/100000u)
#define MK_TicksToNs_10000(tx)					(((tx) > 42949u) ? 0xffffffffu : ((tx)*100000u))
#define MK_NsToTicksF_10000(ns)					MK_NsToTicks_10000(ns)
#define MK_TicksToNsF_10000(tx)					MK_TicksToNs_10000(tx)

/* Clock frequency 2 MHz
 *
 * Factor is 2000000/1000000000
 *         = 2/1000
 *         = 1/500
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_2000000(ns)				((ns)/500u)
#define MK_TicksToNs_2000000(tx)				(((tx) > 8589934u) ? 0xffffffffu : ((tx)*500u))
#define MK_NsToTicksF_2000000(ns)				MK_NsToTicks_2000000(ns)
#define MK_TicksToNsF_2000000(tx)				MK_TicksToNs_2000000(tx)

/* Clock frequency 2,08 MHz
 *
 * Factor is 2080000/1000000000
 *         = 208/100000
 *         = 13/6250 = 13/25/250
*/
#define MK_NsToTicks_2080000(ns)				MK_DivMulDiv((ns), 25u, 13u, 250u)
#define MK_TicksToNs_2080000(tx)				MK_SatMulDivMul((tx), 250u, 13u, 25u, 8933531u)
#define MK_NsToTicksF_2080000(ns)				MK_MulDiv((ns), 13u, 6250u)
#define MK_TicksToNsF_2080000(tx)				MK_MulDiv((tx), 6250u, 13u)

/* Clock frequency 4 MHz
 *
 * Factor is 4000000/1000000000
 *         = 4/1000
 *         = 1/250
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_4000000(ns)				((ns)/250u)
#define MK_TicksToNs_4000000(tx)				(((tx) > 17179869u) ? 0xffffffffu : ((tx)*250u))
#define MK_NsToTicksF_4000000(ns)				MK_NsToTicks_4000000(ns)
#define MK_TicksToNsF_4000000(tx)				MK_TicksToNs_4000000(tx)

/* Clock frequency 5 MHz
 *
 * Factor is 5000000/1000000000
 *         = 5/1000
 *         = 1/200
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_5000000(ns)				((ns)/200u)
#define MK_TicksToNs_5000000(tx)				(((tx) > 21474836u) ? 0xffffffffu : ((tx)*200u))
#define MK_NsToTicksF_5000000(ns)				MK_NsToTicks_5000000(ns)
#define MK_TicksToNsF_5000000(tx)				MK_TicksToNs_5000000(tx)

/* Clock frequency 8 MHz
 *
 * Factor is 8000000/1000000000
 *         = 8/1000
 *         = 1/125
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_8000000(ns)				((ns)/125u)
#define MK_TicksToNs_8000000(tx)				(((tx) > 34359738u) ? 0xffffffffu : ((tx)*125u))
#define MK_NsToTicksF_8000000(ns)				MK_NsToTicks_8000000(ns)
#define MK_TicksToNsF_8000000(tx)				MK_TicksToNs_8000000(tx)

/* Clock frequency 12 MHz
 *
 * Factor is 12000000/1000000000
 *         = 12/1000
 *         = 3/250
 * 250 = 5 * 50 and 5 > 3, so 5 is the first division factor
*/
#define MK_NsToTicks_12000000(ns)				MK_DivMulDiv((ns), 5u, 3u, 50u)
#define MK_TicksToNs_12000000(tx)				MK_SatMulDivMul((tx), 50u, 3u, 5u, 51539607u)
#define MK_NsToTicksF_12000000(ns)				MK_MulDiv((ns), 3u, 250u)
#define MK_TicksToNsF_12000000(tx)				MK_MulDiv((tx), 250u, 3u)

/* Clock frequency 16 MHz
 *
 * Factor is 16000000/1000000000
 *         = 16/1000
 *         = 2/125
 * 125 = 5*25 and 5>2, so 5 is the first division factor
*/
#define MK_NsToTicks_16000000(ns)				MK_DivMulDiv((ns), 5u, 2u, 25u)
#define MK_TicksToNs_16000000(tx)				MK_SatMulDivMul((tx), 25u, 2u, 5u, 68719476u)
#define MK_NsToTicksF_16000000(ns)				MK_MulDiv((ns), 2u, 125u)
#define MK_TicksToNsF_16000000(tx)				MK_MulDiv((tx), 125u, 2u)

/* Clock frequency 20 MHz
 *
 * Factor is 20000000/1000000000
 *         = 20/1000
 *         = 1/50
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_20000000(ns)				((ns)/50u)
#define MK_TicksToNs_20000000(tx)				( ((tx) > 85899345u) ? 0xffffffffu : ((tx)*50u) )
#define MK_NsToTicksF_20000000(ns)				MK_NsToTicks_20000000(ns)
#define MK_TicksToNsF_20000000(tx)				MK_TicksToNs_20000000(tx)

/* Clock frequency 24 MHz
 *
 * Factor is 24000000/1000000000
 *         = 24/1000
 *         = 3/125
 * 125 = 5 * 25 with 5 > 3, so 5 is the first division factor.
*/
#define MK_NsToTicks_24000000(ns)				MK_DivMulDiv((ns), 5u, 3u, 25u)
#define MK_TicksToNs_24000000(tx)				MK_SatMulDivMul((tx), 25u, 3u, 5u, 103079215u)
#define MK_NsToTicksF_24000000(ns)				MK_MulDiv((ns), 3u, 125u)
#define MK_TicksToNsF_24000000(tx)				MK_MulDiv((tx), 125u, 3u)

/* Clock frequency 25 MHz
 *
 * Factor is 25000000/1000000000
 *         = 25/1000
 *         = 1/40
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_25000000(ns)				((ns)/40u)
#define MK_TicksToNs_25000000(tx)				(((tx) > 107374182u) ? 0xffffffffu : ((tx)*40u))
#define MK_NsToTicksF_25000000(ns)				MK_NsToTicks_25000000(ns)
#define MK_TicksToNsF_25000000(tx)				MK_TicksToNs_25000000(tx)

/* Clock frequency 26 MHz
 *
 * Factor is 26000000/1000000000
 *         = 26/1000
 *         = 13/500
 * 500 = 20*25 and 20>13, so 20 is the first division factor
*/
#define MK_NsToTicks_26000000(ns)				MK_DivMulDiv((ns), 20u, 13u, 25u)
#define MK_TicksToNs_26000000(tx)				MK_SatMulDivMul((tx), 25u, 13u, 20u, 111669149u)
#define MK_NsToTicksF_26000000(ns)				MK_MulDiv((ns), 13u, 500u)
#define MK_TicksToNsF_26000000(tx)				MK_MulDiv((tx), 500u, 13u)

/* Clock frequency 30 MHz
 *
 * Factor is 30000000/1000000000
 *         = 30/1000
 *         = 3/100
 * 100 = 25*4, and 4>3, so 4 is the first division factor
*/
#define MK_NsToTicks_30000000(ns)				MK_DivMulDiv((ns), 4u, 3u, 25u)
#define MK_TicksToNs_30000000(tx)				MK_SatMulDivMul((tx), 25u, 3u, 4u, 128849018u)
#define MK_NsToTicksF_30000000(ns)				MK_MulDiv((ns), 3u, 100u)
#define MK_TicksToNsF_30000000(tx)				MK_MulDiv((tx), 100u, 3u)

/* Clock frequency 32 MHz
 *
 * Factor is 32000000/1000000000
 *         = 32/1000
 *         = 4/125
 * 125 = 5*25 and 5>4, so 5 is the first division factor
*/
#define MK_NsToTicks_32000000(ns)				MK_DivMulDiv((ns), 5u, 4u, 25u)
#define MK_TicksToNs_32000000(tx)				MK_SatMulDivMul((tx), 25u, 4u, 5u, 137438953u)
#define MK_NsToTicksF_32000000(ns)				MK_MulDiv((ns), 4u, 125u)
#define MK_TicksToNsF_32000000(tx)				MK_MulDiv((tx), 125u, 4u)

/* Clock frequency 33 MHz
 *
 * Factor is 33000000/1000000000
 *         = 33/1000
 * 1000 = 40*25 and 40>33, so 40 is the first division factor
*/
#define MK_NsToTicks_33000000(ns)				MK_DivMulDiv((ns), 40u, 33u, 25u)
#define MK_TicksToNs_33000000(tx)				MK_SatMulDivMul((tx), 25u, 33u, 40u, 141733920u)
#define MK_NsToTicksF_33000000(ns)				MK_MulDiv((ns), 33u, 1000u)
#define MK_TicksToNsF_33000000(tx)				MK_MulDiv((tx), 1000u, 33u)

/* Clock frequency 33,3 MHz
 *
 * Factor is 33300000/1000000000
 *         = 333/10000
*/
#define MK_NsToTicks_33300000(ns)				MK_DivMulDiv((ns), 400u, 333u, 25u)
#define MK_TicksToNs_33300000(tx)				MK_SatMulDivMul((tx), 25u, 333u, 400u, 143022410u)
#define MK_NsToTicksF_33300000(ns)				MK_MulDiv((ns), 333u, 10000u)
#define MK_TicksToNsF_33300000(tx)				MK_MulDiv((tx), 10000u, 333u)


/* Clock frequency 37.5 MHz
 *
 * Factor is 37500000/1000000000
 *         = 375/10000
 *         = 3/80
 * 80 = 4 * 20 and 4>3, so 4 is the first division factor
*/
#define MK_NsToTicks_37500000(ns)				MK_DivMulDiv((ns), 4u, 3u, 20u)
#define MK_TicksToNs_37500000(tx)				MK_SatMulDivMul((tx), 20u, 3u, 4u, 161061273u)
#define MK_NsToTicksF_37500000(ns)				MK_MulDiv((ns), 3u, 80u)
#define MK_TicksToNsF_37500000(tx)				MK_MulDiv((tx), 80u, 3u)

/* Clock frequency 40 MHz
 *
 * Factor is 40000000/1000000000
 *         = 40/1000
 *         = 1/25
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_40000000(ns)				((ns)/25u)
#define MK_TicksToNs_40000000(tx)				( ((tx) > 171798691u) ? 0xffffffffu : ((tx)*25u) )
#define MK_NsToTicksF_40000000(ns)				MK_NsToTicks_40000000(ns)
#define MK_TicksToNsF_40000000(tx)				MK_TicksToNs_40000000(tx)

/* Clock frequency 48 MHz
 *
 * Factor is 48000000/1000000000
 *         = 48/1000
 *         = 6/125
 * 125 = 25*5 and 25>6, so 25 is the first division factor
*/
#define MK_NsToTicks_48000000(ns)				MK_DivMulDiv((ns), 25u, 6u, 5u)
#define MK_TicksToNs_48000000(tx)				MK_SatMulDivMul((tx), 5u, 6u, 25u, 206158430u)
#define MK_NsToTicksF_48000000(ns)				MK_MulDiv((ns), 6u, 125u)
#define MK_TicksToNsF_48000000(tx)				MK_MulDiv((tx), 125u, 6u)

/* Clock frequency 50 MHz
 *
 * Factor is 50000000/1000000000
 *         = 5/100
 *         = 1/20
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_50000000(ns)				((ns)/20u)
#define MK_TicksToNs_50000000(tx)				( ((tx) > 214748364u) ? 0xffffffffu : ((tx)*20u) )
#define MK_NsToTicksF_50000000(ns)				MK_NsToTicks_50000000(ns)
#define MK_TicksToNsF_50000000(tx)				MK_TicksToNs_50000000(tx)

/* Clock frequency 55 MHz
 *
 * Factor is 55000000/1000000000
 *         = 55/1000
 *         = 11/200
 * 200 = 20*10, and 20>11, so 20 is the first division factor
*/
#define MK_NsToTicks_55000000(ns)				MK_DivMulDiv((ns), 20u, 11u, 10u)
#define MK_TicksToNs_55000000(tx)				MK_SatMulDivMul((tx), 10u, 11u, 20u, 236223201u)
#define MK_NsToTicksF_55000000(ns)				MK_MulDiv((ns), 11u, 200u)
#define MK_TicksToNsF_55000000(tx)				MK_MulDiv((tx), 200u, 11u)

/* Clock frequency 60 MHz
 *
 * Factor is 60000000/1000000000
 *         = 60/1000
 *         = 3/50
 * 50 = 25*2, and 25>3, so 25 is the first division factor
*/
#define MK_NsToTicks_60000000(ns)				MK_DivMulDiv((ns), 25u, 3u, 2u)
#define MK_TicksToNs_60000000(tx)				MK_SatMulDivMul((tx), 2u, 3u, 25u, 257698037u)
#define MK_NsToTicksF_60000000(ns)				MK_MulDiv((ns), 3u, 50u)
#define MK_TicksToNsF_60000000(tx)				MK_MulDiv((tx), 50u, 3u)

/* Clock frequency 62.5 MHz
 *
 * Factor is 125000000/2000000000
 *         = 125/2000
 *         = 5/80
 * 80 = 8*10, and 8>5, so 8 is the first division factor
*/
#define MK_NsToTicks_62500000(ns)				MK_DivMulDiv((ns), 8u, 5u, 10u)
#define MK_TicksToNs_62500000(tx)				MK_SatMulDivMul((tx), 10u, 5u, 8u, 268435455u)
#define MK_NsToTicksF_62500000(ns)				MK_MulDiv((ns), 5u, 80u)
#define MK_TicksToNsF_62500000(tx)				MK_MulDiv((tx), 80u, 5u)

/* Clock frequency 64 MHz
 *
 * Factor is 64000000/1000000000
 *         = 64/1000
 *         = 8/125
 * 125 = 25*5 and 25>8, so 25 is the first division factor
*/
#define MK_NsToTicks_64000000(ns)				MK_DivMulDiv((ns), 25u, 8u, 5u)
#define MK_TicksToNs_64000000(tx)				MK_SatMulDivMul((tx), 5u, 8u, 25u, 274877906u)
#define MK_NsToTicksF_64000000(ns)				MK_MulDiv((ns), 8u, 125u)
#define MK_TicksToNsF_64000000(tx)				MK_MulDiv((tx), 125u, 8u)

/* Clock frequency 70 MHz
 *
 * Factor is 70000000/1000000000
 *         = 7/100
 * 100 = 10*10, so there 10 is the first and last divisor.
*/
#define MK_NsToTicks_70000000(ns)				MK_DivMulDiv((ns), 10u, 7u, 10u)
#define MK_TicksToNs_70000000(tx)				MK_SatMulDivMul((tx), 10u, 7u, 10u, MK_NsToTicks_70000000(0xffffffffu))
#define MK_NsToTicksF_70000000(ns)				MK_MulDiv((ns), 7u, 100u)
#define MK_TicksToNsF_70000000(tx)				MK_MulDiv((tx), 100u, 7u)

/* Clock frequency 75 MHz
 *
 * Factor is 75000000/1000000000
 *         = 75/1000
 *         = 3/40
 * 40 = 4*10, and 4>3, so 4 is the first division factor
*/
#define MK_NsToTicks_75000000(ns)				MK_DivMulDiv((ns), 4u, 3u, 10u)
#define MK_TicksToNs_75000000(tx)				MK_SatMulDivMul((tx), 10u, 3u, 4u, 322122547u)
#define MK_NsToTicksF_75000000(ns)				MK_MulDiv((ns), 3u, 40u)
#define MK_TicksToNsF_75000000(tx)				MK_MulDiv((tx), 40u, 3u)

/* Clock frequency 80 MHz
 *
 * Factor is 80000000/1000000000
 *         = 80/1000
 *         = 2/25
 * 25 = 5*5 and 5>2, so 5 is the first division factor
*/
#define MK_NsToTicks_80000000(ns)				MK_DivMulDiv((ns), 5u, 2u, 5u)
#define MK_TicksToNs_80000000(tx)				MK_SatMulDivMul((tx), 5u, 2u, 5u, 343597383u)
#define MK_NsToTicksF_80000000(ns)				MK_MulDiv((ns), 2u, 25u)
#define MK_TicksToNsF_80000000(tx)				MK_MulDiv((tx), 25u, 2u)

/* Clock frequency 84 MHz
 *
 * Factor is 84000000/1000000000
 *         = 84/1000
 *         = 21/250
 * 250 = 25*10 and 25>21, so 25 is the first division factor
*/
#define MK_NsToTicks_84000000(ns)               MK_DivMulDiv((ns), 25u, 21u, 10u)
#define MK_TicksToNs_84000000(tx)               MK_SatMulDivMul((tx), 10u, 21u, 25u, 360777252u)
#define MK_NsToTicksF_84000000(ns)              MK_MulDiv((ns), 21u, 250u)
#define MK_TicksToNsF_84000000(tx)              MK_MulDiv((tx), 250u, 21u)

/* Clock frequency 90 MHz
 *
 * Factor is 90000000/1000000000
 *         = 90/1000
 *         = 9/100
 * 100 = 10*10 and 10>9, so 10 is the first division factor
*/
#define MK_NsToTicks_90000000(ns)				MK_DivMulDiv((ns), 10u, 9u, 10u)
#define MK_TicksToNs_90000000(tx)				MK_SatMulDivMul((tx), 10u, 9u, 10u, 386547056u)
#define MK_NsToTicksF_90000000(ns)				MK_MulDiv((ns), 9u, 100u)
#define MK_TicksToNsF_90000000(tx)				MK_MulDiv((tx), 100u, 9u)

/* Clock frequency 100 MHz
 *
 * Factor is 100000000/1000000000
 *         = 1/10
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_100000000(ns)				((ns)/10u)
#define MK_TicksToNs_100000000(tx)				( ((tx) > 429496729u) ? 0xffffffffu : ((tx)*10u) )
#define MK_NsToTicksF_100000000(ns)				MK_NsToTicks_100000000(ns)
#define MK_TicksToNsF_100000000(tx)				MK_TicksToNs_100000000(tx)

/* Clock frequency 110 MHz
 *
 * Factor is 110000000/1000000000
 *         = 11/100
 * 100 = 20*5, and 20>11, so 20 is the first division factor
 *
 * The limit is calculated by hand because the rounding error in the ns-to-ticks macro gives an incorrect limit.
*/
#define MK_NsToTicks_110000000(ns)				MK_DivMulDiv((ns), 20u, 11u, 5u)
#define MK_TicksToNs_110000000(tx)				MK_SatMulDivMul((tx), 5u, 11u, 20u, 472446402u)
#define MK_NsToTicksF_110000000(ns)				MK_MulDiv((ns), 11u, 100u)
#define MK_TicksToNsF_110000000(tx)				MK_MulDiv((tx), 100u, 11u)

/* Clock frequency 120 MHz
 *
 * Factor is 120000000/1000000000
 *         = 12/100
 *         = 3/25
 * 25 = 5*5, and 5>3, so 5 is the first division factor.
*/
#define MK_NsToTicks_120000000(ns)				MK_DivMulDiv((ns), 5u, 3u, 5u)
#define MK_TicksToNs_120000000(tx)				MK_SatMulDivMul((tx), 5u, 3u, 5u, 515396075u)
#define MK_NsToTicksF_120000000(ns)				MK_MulDiv((ns), 3u, 25u)
#define MK_TicksToNsF_120000000(tx)				MK_MulDiv((tx), 25u, 3u)

/* Clock frequency 133 MHz
 *
 * Factor is 133000000/1000000000
 *         = 133/1000
 * 1000 = 200 * 5, and 200>133, so 200 is the first division factor
*/
#define MK_NsToTicks_133000000(ns)				MK_DivMulDiv((ns), 200u, 133u, 5u)
#define MK_TicksToNs_133000000(tx)				MK_SatMulDivMul((tx), 5u, 133u, 200u, 571230650u)
#define MK_NsToTicksF_133000000(ns)				MK_MulDiv((ns), 133u, 1000u)
#define MK_TicksToNsF_133000000(tx)				MK_MulDiv((tx), 1000u, 133u)

/* Clock frequency 140 MHz
 *
 * Factor is 140000000/1000000000
 *         = 14/100
 *         = 7/50
 * 50 = 10*5, and 10>7, so 10 is the first division factor.
*/
#define MK_NsToTicks_140000000(ns)				MK_DivMulDiv((ns), 10u, 7u, 5u)
#define MK_TicksToNs_140000000(tx)				MK_SatMulDivMul((tx), 5u, 7u, 10u, 601295421u)
#define MK_NsToTicksF_140000000(ns)				MK_MulDiv((ns), 7u, 50u)
#define MK_TicksToNsF_140000000(tx)				MK_MulDiv((tx), 50u, 7u)

/* Clock frequency 160 MHz
 *
 * Factor is 160000000/1000000000
 *         = 16/100
 *         = 4/25
 * 25 = 5*5, and 5>4, so 5 is the first division factor.
*/
#define MK_NsToTicks_160000000(ns)				MK_DivMulDiv((ns), 5u, 4u, 5u)
#define MK_TicksToNs_160000000(tx)				MK_SatMulDivMul((tx), 5u, 4u, 5u, 687194767u)
#define MK_NsToTicksF_160000000(ns)				MK_MulDiv((ns), 4u, 25u)
#define MK_TicksToNsF_160000000(tx)				MK_MulDiv((tx), 25u, 4u)

/* Clock frequency 180 MHz
 *
 * Factor is 180000000/1000000000
 *         = 18/100
 *         = 9/50
 * 50 = 5*10 and 10>9, so 10 is the first division factor
*/
#define MK_NsToTicks_180000000(ns)				MK_DivMulDiv((ns), 10u, 9u, 5u)
#define MK_TicksToNs_180000000(tx)				MK_SatMulDivMul((tx), 5u, 9u, 10u, 773094113u)
#define MK_NsToTicksF_180000000(ns)				MK_MulDiv((ns), 9u, 50u)
#define MK_TicksToNsF_180000000(tx)				MK_MulDiv((tx), 50u, 9u)

/* Clock frequency 200 MHz
 *
 * Factor is 200000000/1000000000
 *         = 1/5
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_200000000(ns)				((ns)/5u)
#define MK_TicksToNs_200000000(tx)				(((tx) > 858993458u) ? 0xffffffffu : ((tx)*5u))
#define MK_NsToTicksF_200000000(ns)				MK_NsToTicks_200000000(ns)
#define MK_TicksToNsF_200000000(tx)				MK_TicksToNs_200000000(tx)

/* Clock frequency 240 MHz
 *
 * Factor is 240000000/1000000000
 *         = 24/100
 *         = 6/25
 * 25 = 5*5, but 5 < 6.
 * See tools/timeconversion.
*/
#define MK_NsToTicks_240000000(ns)				MK_DivMul((ns), 25u, 6u)
#define MK_TicksToNs_240000000(tx)				MK_SatDivMul((tx), 6u, 25u, 1030792150u)
#define MK_NsToTicksF_240000000(ns)				MK_MulDiv((ns), 6u, 25u)
#define MK_TicksToNsF_240000000(tx)				MK_MulDiv((tx), 25u, 6u)

/* Clock frequency 250 MHz
 *
 * Factor is 250000000/1000000000
 *         = 1/4
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_250000000(ns)				((ns)/4u)
#define MK_TicksToNs_250000000(tx)				(((tx) > 1073741823u) ? 0xffffffffu : ((tx)*4u))
#define MK_NsToTicksF_250000000(ns)				MK_NsToTicks_250000000(ns)
#define MK_TicksToNsF_250000000(tx)				MK_TicksToNs_250000000(tx)

/* Clock frequency 300 MHz
 *
 * Factor is 300000000/1000000000
 *         = 3/10
 * 10 = 5*2 and 5>3, so 5 is the first division factor
*/
#define MK_NsToTicks_300000000(ns)				MK_DivMulDiv((ns), 5u, 3u, 2u)
#define MK_TicksToNs_300000000(tx)				MK_SatMulDivMul((tx), 2u, 3u, 5u, 1288490188u)
#define MK_NsToTicksF_300000000(ns)				MK_MulDiv((ns), 3u, 10u)
#define MK_TicksToNsF_300000000(tx)				MK_MulDiv((tx), 10u, 3u)

/* Clock frequency 330 MHz
 *
 * Factor is 330000000/1000000000
 *         = 33/100
 * 100 = 50*2 and 50>33, so 50 is the first division factor
*/
#define MK_NsToTicks_330000000(ns)				MK_DivMulDiv((ns), 50u, 33u, 2u)
#define MK_TicksToNs_330000000(tx)				MK_SatMulDivMul((tx), 2u, 33u, 50u, 1417339207u)
#define MK_NsToTicksF_330000000(ns)				MK_MulDiv((ns), 33u, 100u)
#define MK_TicksToNsF_330000000(tx)				MK_MulDiv((tx), 100u, 33u)

/* Clock frequency 400 MHz
 *
 * Factor is 400000000/1000000000
 *         = 2/5
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_400000000(ns)				MK_DivMul((ns), 5u, 2u)
#define MK_TicksToNs_400000000(tx)				MK_SatDivMul((tx), 2u, 5u, 1717986918u)
#define MK_NsToTicksF_400000000(ns)				MK_MulDiv((ns), 2u, 5u)
#define MK_TicksToNsF_400000000(tx)				MK_MulDiv((tx), 5u, 2u)

/* Clock frequency 800 MHz
 *
 * Factor is 800000000/1000000000
 *         = 4/5
 * No mul-div-mul needed.
*/
#define MK_NsToTicks_800000000(ns)				MK_DivMul((ns), 5u, 4u)
#define MK_TicksToNs_800000000(tx)				MK_SatDivMul((tx), 4u, 5u, 3435973835u)
#define MK_NsToTicksF_800000000(ns)				MK_MulDiv((ns), 4u, 5u)
#define MK_TicksToNsF_800000000(tx)				MK_MulDiv((tx), 5u, 4u)


#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
