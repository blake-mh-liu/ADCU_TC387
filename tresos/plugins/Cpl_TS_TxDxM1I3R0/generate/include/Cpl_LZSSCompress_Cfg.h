#ifndef CPL_LZSSCOMPRESS_CFG_H
#define CPL_LZSSCOMPRESS_CFG_H

/*================================================================================================*/

/** \file        Cpl_LZSSCompress_Cfg.h
 **
 ** \brief       Cpl LZSS compression interface.
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

/* !LINKSTO EB_CPL_0801_040, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_042, 1
 */
#include <Std_Types.h>
#include <Cpl_Version.h>

/*==================[macros]======================================================================*/

/* !LINKSTO EB_CPL_0806_000, 1
 */
/** \brief  This macro encodes whether the LZSSCompress primitive is configured.
 **/
[!IF "num:i(0) != num:i(count(as:modconf('Cpl')/CplLzssCompress/CplLzssCompressConfig/*))"!][!//
#define  CPL_LZSSCOMPRESS_ENABLED          STD_ON
[!ELSE!][!//
#define  CPL_LZSSCOMPRESS_ENABLED          STD_OFF
[!ENDIF!][!//

[!VAR "CplMinBitsOfLength" = "'16'"!][!//
[!LOOP "as:modconf('Cpl')/CplLzssCompress/CplLzssCompressConfig/*"!][!//
[!INDENT "0"!][!//
  [!IF "./CplLzssCompressLengthBitsPerBlock < $CplMinBitsOfLength"!][!VAR "CplMinBitsOfLength" = "./CplLzssCompressLengthBitsPerBlock"!][!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDLOOP!][!//
/** \brief  This macro encodes the maximum necessary look-back (LB) buffer size
 **/
#define  CPL_LZSSCOMPRESS_BUF_LB_MAX_SIZE  [!"num:i(bit:shl(1,16-$CplMinBitsOfLength)-1)"!]U

[!VAR "CplMaxBitsOfLength" = "'0'"!][!//
[!LOOP "as:modconf('Cpl')/CplLzssCompress/CplLzssCompressConfig/*"!][!//
[!INDENT "0"!][!//
  [!IF "./CplLzssCompressLengthBitsPerBlock > $CplMaxBitsOfLength"!][!VAR "CplMaxBitsOfLength" = "./CplLzssCompressLengthBitsPerBlock"!][!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDLOOP!][!//
/** \brief  This macro encodes the maximum necessary look-ahead (LA) buffer size
 **/
#define  CPL_LZSSCOMPRESS_BUF_LA_MAX_SIZE  [!"num:i(bit:shl(1,$CplMaxBitsOfLength)-1)"!]U

/*==================[type definitions]============================================================*/

/* !LINKSTO EB_CPL_0806_500, 1
 */
/** \brief  Type for representing a LZSSCompress configuration.
 **/
typedef struct
{
  uint16 shftLength;
  uint16 maskLength;
  uint16 maskOffset;
  uint32 sizeBufLookBack;
  uint32 sizeBufLookAhead;
  uint32 iterBeforeInterruption;
}
Cpl_LZSSCompressConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplLzssCompress/CplLzssCompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* !LINKSTO EB_CPL_0806_500, 1
 */
[!LOOP "as:modconf('Cpl')/CplLzssCompress/CplLzssCompressConfig/*"!][!//
extern CONST(Cpl_LZSSCompressConfigType, CPL_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

[!ELSE!][!//

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CPL_LZSSCOMPRESS_CFG_H */

/*==================[end of file]=================================================================*/
