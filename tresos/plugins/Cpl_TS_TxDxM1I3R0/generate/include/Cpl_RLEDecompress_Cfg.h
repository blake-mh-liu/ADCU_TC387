#ifndef CPL_RLEDECOMPRESS_CFG_H
#define CPL_RLEDECOMPRESS_CFG_H

/*================================================================================================*/

/** \file        Cpl_RLEDecompress_Cfg.h
 **
 ** \brief       Cpl RLE decompression interface.
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

/* !LINKSTO EB_CPL_0801_070, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_072, 1
 */
#include <Std_Types.h>
#include <Cpl_Version.h>
#include <Cpl_Common.h>

/*==================[macros]======================================================================*/

/* !LINKSTO EB_CPL_0806_030, 1
 */
/** \brief  This macro encodes whether the RLEDecompress primitive is configured.
 **/
[!IF "num:i(0) != num:i(count(as:modconf('Cpl')/CplRleDecompress/CplRleDecompressConfig/*))"!][!//
#define  CPL_RLEDECOMPRESS_ENABLED          STD_ON
[!ELSE!][!//
#define  CPL_RLEDECOMPRESS_ENABLED          STD_OFF
[!ENDIF!][!//

/* !LINKSTO EB_CPL_0806_031, 1
 */
/** \brief  This macros encodes whether a specific RLE type is enabled.
 ** \addtogroup  RLE type enabled macros
 ** @{ */
[!//
[!VAR "CplRleDecompressVariant8Bit"     = "'false'"!][!//
[!VAR "CplRleDecompressVariantCtrlBit"  = "'false'"!][!//
[!LOOP "as:modconf('Cpl')/CplRleDecompress/CplRleDecompressConfig/*"!][!//
[!INDENT "0"!][!//
  [!IF "./CplRleDecompressVariant = 'CPL_RLE_VARIANT_8BIT'    "!][!VAR "CplRleDecompressVariant8Bit"    = "'true'"!][!ENDIF!][!//
  [!IF "./CplRleDecompressVariant = 'CPL_RLE_VARIANT_CTRLBIT' "!][!VAR "CplRleDecompressVariantCtrlBit" = "'true'"!][!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDLOOP!][!//
[!//
[!IF "$CplRleDecompressVariant8Bit = 'true'"!][!//
#define  CPL_RLEDECOMPRESS_VARIANT_8BIT     STD_ON
[!ELSE!][!//
#define  CPL_RLEDECOMPRESS_VARIANT_8BIT     STD_OFF
[!ENDIF!][!//
[!//
[!IF "$CplRleDecompressVariantCtrlBit = 'true'"!][!//
#define  CPL_RLEDECOMPRESS_VARIANT_CTRLBIT  STD_ON
[!ELSE!][!//
#define  CPL_RLEDECOMPRESS_VARIANT_CTRLBIT  STD_OFF
[!ENDIF!][!//
[!//
/** @} doxygen end group definition */

/*==================[type definitions]============================================================*/

/* !LINKSTO EB_CPL_0806_515, 1
 */
/** \brief  Type for representing a RLEDecompress configuration.
 **/
typedef struct
{
  Cpl_RleVariantType Variant;
}
Cpl_RLEDecompressConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplRleDecompress/CplRleDecompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* !LINKSTO EB_CPL_0806_515, 1
 */
[!LOOP "as:modconf('Cpl')/CplRleDecompress/CplRleDecompressConfig/*"!][!//
extern CONST(Cpl_RLEDecompressConfigType, CPL_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

[!ELSE!][!//

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CPL_RLEDECOMPRESS_CFG_H */

/*==================[end of file]=================================================================*/
