#if (!defined PLATFORMS_TSPLATFORMS_H)
#define PLATFORMS_TSPLATFORMS_H
/**
 * \file
 *
 * \brief AUTOSAR Application_Can
 *
 * This file contains the implementation of the AUTOSAR
 * module Application_Can.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[type definitions]=======================================*/

/*==================[macros]=================================================*/

/*------------------[derivate names]----------------------------------------*/

#define TS_TC10GP     1
#define TS_TC1775     2
#define TS_TC1775B    3
#define TS_TC1766     4
#define TS_TC1796     5
#define TS_TC1797     6
#define TS_TC1767     7
#define TS_TC1387     8
#define TS_TC1782     9
#define TS_TC1798     10
#define TS_TC1791     11
#define TS_TC1793     12
#define TS_TC27XFPGA  13
#define TS_TC2D5      14
#define TS_TC277      15
#define TS_TC275      16
#define TS_TC1784     17
#define TS_TC26XD     19
#define TS_TC23XL     22
#define TS_TC29XT     23
#define TS_TC22XL     24
#define TS_TC39XX     26
#define TS_TC38XQ     27

/*------------------[core architecture]----------------------------------------*/
/* because we cannot assume the presence of the OS, and the AutoCore build environment
 * does not seem to provide it, we need to determine the architecture ourselves from
 * the TS_ARCH_DERIVATE setting.
 */
#if   /* TC 1.6EP cores (Aurix) */ \
	(TS_ARCH_DERIVATE)==(TS_TC2D5)     || \
	(TS_ARCH_DERIVATE)==(TS_TC27XFPGA) || \
	(TS_ARCH_DERIVATE)==(TS_TC277)     || \
	(TS_ARCH_DERIVATE)==(TS_TC275)     || \
	(TS_ARCH_DERIVATE)==(TS_TC26XD)    || \
    (TS_ARCH_DERIVATE)==(TS_TC29XT)    || \
    (TS_ARCH_DERIVATE)==(TS_TC23XL)    || \
    (TS_ARCH_DERIVATE)==(TS_TC22XL)

#define TS_TC_CORE_ARCHITECTURE 161u

#elif /* TC 1.6.2 cores */ \
(TS_ARCH_DERIVATE)==(TS_TC39XX)     || \
	(TS_ARCH_DERIVATE)==(TS_TC38XQ)

#define TS_TC_CORE_ARCHITECTURE 162u

#elif /* TC 1.6 cores */ \
	(TS_ARCH_DERIVATE)==(TS_TC1791) || \
	(TS_ARCH_DERIVATE)==(TS_TC1793) || \
	(TS_ARCH_DERIVATE)==(TS_TC1798)
#define TS_TC_CORE_ARCHITECTURE 160u

#else /* fallback to TC 1.3 */
#define TS_TC_CORE_ARCHITECTURE 130u
#endif

#endif /* if (!defined TSPLATFORMS_H)*/
