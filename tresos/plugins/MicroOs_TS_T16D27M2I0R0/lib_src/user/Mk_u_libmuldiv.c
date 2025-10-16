/* Mk_u_libmuldiv.c
 *
 * This file contains the MK_MulDiv() function, which multiplies a 32-bit input value by an
 * at most 16-bit multiplier, then divides the result by an at most 16-bit divider. The
 * calculation is performed using 48-bit arithmetic so that minimal loss of accuracy is
 * achieved without the risk of an overflow. If the final result is greater than the
 * largest possible 32-bit value, the result "saturates" at the maximum value of 0xffffffff.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_basic_types.h>
#include <public/Mk_public_api.h>

#if MK_HAS_INT64
#error "32-bit version of MK_MulDiv() used with a 64-bit architecture."
#endif

/* MK_MulDiv() - performs a multiplication followed by a division, without overflow.
 *
 * The function uses paper and pencil long multiplication of a 2 digit number by a 1 digit number,
 * except in this case the digits are in base 65536.
 *
 * Paper and pencil multiplication:
 * The two-digit number is A1 A0, the single digit multiplier is B
 * The low digit of the product is the low digit of A0*B
 * The middle digit of the product is the low digit of A1*B plus the high digit of A0*B, with possible carry out.
 * The high digit of the product is the high digit of A1*B, plus the carry from the middle digit.
 * By calculating the middle and high digits as a single 32-bit number the processor does the carry for us.
 *
 * Implementation used:
 * Low: (A0*B) & 0xffff --> lower digit (= low)
 * Mid/high: (A1*B) + ((A0*B) >> 16) --> upper two digits (= high)
 *
 * Paper and pencil division:
 * The three-digit product (from above) is P2 P1 P0, the single-digit divisor is C
 * First step: P2/C. Quotient is upper digit of result, remainder R1 is carried, giving two-digit number R1 P1
 * Second step: R1 P1 / C. Quotient is the middle digit of the result, remainder is carried giving R0 P0
 * Third step: R0 P0 / C. Quotient is the low digit of the result, remainder is discarded.
 *
 * If the upper-digit of result is non-zero the result is too large to fit into the result,
 * so the result becomes the saturation value 0xffffffff.
 *
 * Implementation used:
 * The first and second steps are combined:
 * P2 P1 / C --> result. If upper digit (16 bits) of result is non-zero --> stop and saturate.
 * Lower digit of result shifted to upper digit.
 * Remainder of P2 P1 / C shifted high and added to P0. This is then divided by C and added to the
 * result.
 *
 * !LINKSTO      Microkernel.Function.MK_MulDiv, 2
 * !doctype      src
*/
mk_uint32_t MK_MulDiv(mk_uint32_t in, mk_uint16_t m, mk_uint16_t d)
{
	mk_uint32_t result;
	mk_uint32_t low = (in & 0xffffu) * m;
	mk_uint32_t high = ((in >> 16) * m) + (low >> 16);

	low &= 0xffffu;

	result = high / d;

	if ( (result & 0xffff0000u) == 0u )
	{
		result = (result << 16) + ( (((high % d) << 16) + low) / d );
	}
	else
	{
		result = 0xffffffffu;
	}

	return result;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
