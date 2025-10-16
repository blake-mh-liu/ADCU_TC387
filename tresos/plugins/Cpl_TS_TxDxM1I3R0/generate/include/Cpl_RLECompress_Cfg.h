#ifndef CPL_RLECOMPRESS_CFG_H
#define CPL_RLECOMPRESS_CFG_H

/*================================================================================================*/

/** \file        Cpl_RLECompress_Cfg.h
 **
 ** \brief       Cpl RLE compression interface.
 **
 ** \project     Crypto Primitive Library
 ** \author      Danny Block <Danny.Block@elektrobit.com>
 ** \author      EB Automotive GmbH, 91058 Erlangen, Germany
 **
 ** \controller  independent
 ** \compiler    independent
 ** \hardware    independent
 **
 ** Copyright 2012 by EB Automotive GmbH
 ** All rights exclusively reserved for EB Automotive GmbH,
 ** unless expressly agreed to otherwise
 **/

/* !LINKSTO EB_CPL_0801_060, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_062, 1
 */
#include <Std_Types.h>
#include <Cpl_Version.h>
#include <Cpl_Common.h>

/*==================[macros]======================================================================*/

/* !LINKSTO EB_CPL_0806_020, 1
 */
/** \brief  This macro encodes whether the RLECompress primitive is configured.
 **/
[!IF "num:i(0) != num:i(count(as:modconf('Cpl')/CplRleCompress/CplRleCompressConfig/*))"!][!//
#define  CPL_RLECOMPRESS_ENABLED          STD_ON
[!ELSE!][!//
#define  CPL_RLECOMPRESS_ENABLED          STD_OFF
[!ENDIF!][!//

/* !LINKSTO EB_CPL_0806_021, 1
 */
/** \brief  This macros encodes whether a specific RLE type is enabled.
 ** \addtogroup  RLE type enabled macros
 ** @{ */
[!//
[!VAR "CplRleCompressVariant8Bit"     = "'false'"!][!//
[!VAR "CplRleCompressVariantCtrlBit"  = "'false'"!][!//
[!LOOP "as:modconf('Cpl')/CplRleCompress/CplRleCompressConfig/*"!][!//
[!INDENT "0"!][!//
  [!IF "./CplRleCompressVariant = 'CPL_RLE_VARIANT_8BIT'    "!][!VAR "CplRleCompressVariant8Bit"    = "'true'"!][!ENDIF!][!//
  [!IF "./CplRleCompressVariant = 'CPL_RLE_VARIANT_CTRLBIT' "!][!VAR "CplRleCompressVariantCtrlBit" = "'true'"!][!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDLOOP!][!//
[!//
[!IF "$CplRleCompressVariant8Bit = 'true'"!][!//
#define  CPL_RLECOMPRESS_VARIANT_8BIT     STD_ON
[!ELSE!][!//
#define  CPL_RLECOMPRESS_VARIANT_8BIT     STD_OFF
[!ENDIF!][!//
[!//
[!IF "$CplRleCompressVariantCtrlBit = 'true'"!][!//
#define  CPL_RLECOMPRESS_VARIANT_CTRLBIT  STD_ON
[!ELSE!][!//
#define  CPL_RLECOMPRESS_VARIANT_CTRLBIT  STD_OFF
[!ENDIF!][!//
[!//
/** @} doxygen end group definition */

/*==================[type definitions]============================================================*/

/* !LINKSTO EB_CPL_0806_510, 1
 */
/** \brief  Type for representing a RLECompress configuration.
 **/
typedef struct
{
  Cpl_RleVariantType Variant;
}
Cpl_RLECompressConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplRleCompress/CplRleCompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* !LINKSTO EB_CPL_0806_510, 1
 */
[!LOOP "as:modconf('Cpl')/CplRleCompress/CplRleCompressConfig/*"!][!//
extern CONST(Cpl_RLECompressConfigType, CPL_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

[!ELSE!][!//

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CPL_RLECOMPRESS_CFG_H */

/*==================[end of file]=================================================================*/
