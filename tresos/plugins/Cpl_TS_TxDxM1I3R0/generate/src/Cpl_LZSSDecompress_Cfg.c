/** \file        Cpl_LZSSDecompress_Cfg.c
 **
 ** \brief       Cpl LZSS decompression interface.
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

/* !LINKSTO EB_CPL_0801_051, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_053, 1
 */
#include <Cpl_LZSSDecompress_Cfg.h>



#if (CPL_LZSSDECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplLzssDecompress/CplLzssDecompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CPL_0806_505, 1
 */

[!LOOP "as:modconf('Cpl')/CplLzssDecompress/CplLzssDecompressConfig/*"!][!//
CONST(Cpl_LZSSDecompressConfigType, CPL_CONST) [!"node:name(.)"!] =
{
  [!"num:i(16-node:value(./CplLzssDecompressLengthBitsPerBlock))"!]U,
  [!"translate( num:inttohex(num:i(bit:shl(1,   node:value(./CplLzssDecompressLengthBitsPerBlock))-1),8), 'abcdef', 'ABCDEF' )"!]U,
  [!"translate( num:inttohex(num:i(bit:shl(1,16-node:value(./CplLzssDecompressLengthBitsPerBlock))-1),8), 'abcdef', 'ABCDEF' )"!]U,
  [!"                        num:i(bit:shl(1,16-node:value(./CplLzssDecompressLengthBitsPerBlock))-1)"!]U
};

[!ENDLOOP!][!//
[!//
#define CPL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//

[!ENDIF!][!//
/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#else /* #if (CPL_LZSSDECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_LzssDecompressConfig_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_LZSSDECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
