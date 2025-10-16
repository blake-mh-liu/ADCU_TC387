/**
 * \file
 *
 * \brief AUTOSAR Tm
 *
 * This file contains the implementation of the AUTOSAR
 * module Tm.
 *
 * \version 1.0.11
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef TM_CFG_H
#define TM_CFG_H

/* This file contains the generated Tm module configuration. */

/*==[Includes]================================================================*/

/*==[Macros]==================================================================*/

#if (defined TM_DEV_ERROR_DETECT)
#error TM_DEV_ERROR_DETECT already defined
#endif /* #if (defined TM_DEV_ERROR_DETECT) */
/* !LINKSTO Tm.swdd.Parameter.TmDevErrorDetect,1 */
/** \brief Enables development error detection */
#define TM_DEV_ERROR_DETECT                 [!//
[!IF "node:existsAndTrue(TmGeneral/TmDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined TM_VERSION_INFO_API)
#error TM_VERSION_INFO_API already defined
#endif
/* !LINKSTO Tm.swdd.Parameter.TmVersionInfoApi,1 */
/** \brief Enables Tm module version API */
#define TM_VERSION_INFO_API                 [!//
[!IF "node:existsAndTrue(TmGeneral/TmVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined TM_ENABLE_PREDEF_TIMER_1US_16BIT)
#error TM_ENABLE_PREDEF_TIMER_1US_16BIT already defined
#endif
/* !LINKSTO Tm.swdd.Parameter.TmEnablePredefTimer1us16bit,1, Tm.EB_Ref.SWS_Tm_00026.1us16bit,1, Tm.EB_Ref.SWS_Tm_00027.1us16bit,1 */
/** \brief Enables APIs for timer on 16 bits with 1us resolution */
#define TM_ENABLE_PREDEF_TIMER_1US_16BIT    [!//
[!IF "node:existsAndTrue(TmGeneral/TmEnablePredefTimer1us16bit)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined TM_ENABLE_PREDEF_TIMER_1US_24BIT)
#error TM_ENABLE_PREDEF_TIMER_1US_24BIT already defined
#endif
/* !LINKSTO Tm.swdd.Parameter.TmEnablePredefTimer1us24bit,1, Tm.EB_Ref.SWS_Tm_00026.1us24bit,1, Tm.EB_Ref.SWS_Tm_00027.1us24bit,1 */
/** \brief Enables APIs for timer on 24 bits with 1us resolution */
#define TM_ENABLE_PREDEF_TIMER_1US_24BIT     [!//
[!IF "node:existsAndTrue(TmGeneral/TmEnablePredefTimer1us24bit)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined TM_ENABLE_PREDEF_TIMER_1US_32BIT)
#error TM_ENABLE_PREDEF_TIMER_1US_32BIT already defined
#endif
/* !LINKSTO Tm.swdd.Parameter.TmEnablePredefTimer1us32bit,1, Tm.EB_Ref.SWS_Tm_00026.1us32bit,1, Tm.EB_Ref.SWS_Tm_00027.1us32bit,1 */
/** \brief Enables APIs for timer on 32 bits with 1us resolution */
#define TM_ENABLE_PREDEF_TIMER_1US_32BIT    [!//
[!IF "node:existsAndTrue(TmGeneral/TmEnablePredefTimer1us32bit)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined TM_ENABLE_PREDEF_TIMER_100US_32BIT)
#error TM_ENABLE_PREDEF_TIMER_100US_32BIT already defined
#endif
/* !LINKSTO Tm.swdd.Parameter.TmEnablePredefTimer100us32bit,1, Tm.EB_Ref.SWS_Tm_00026.100us32bit,1 */
/** \brief Enables APIs for timer on 32 bits with 100us resolution */
#define TM_ENABLE_PREDEF_TIMER_100US_32BIT  [!//
[!IF "node:existsAndTrue(TmGeneral/TmEnablePredefTimer100us32bit)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]




[!SELECT "TmGeneral"!][!//

#if (defined TM_DET_RUNTIME_CHECKS)
#error TM_DET_RUNTIME_CHECKS is already defined
#endif
/** \brief DET runtime checks reporting
 **
 ** En- or disables the reporting of the DET runtime checks */
#define TM_DET_RUNTIME_CHECKS   [!//
[!IF "TmDetRuntimeChecks = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//


/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* ifndef TM_CFG_H */

