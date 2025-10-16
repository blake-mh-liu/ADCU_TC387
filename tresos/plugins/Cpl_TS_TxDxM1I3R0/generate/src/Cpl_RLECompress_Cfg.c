/** \file        Cpl_RLECompress_Cfg.c
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

/* !LINKSTO EB_CPL_0801_061, 1
 */

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO EB_CPL_0801_063, 1
 */
#include <Cpl_RLECompress_Cfg.h> 



#if (CPL_RLECOMPRESS_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cpl')/CplRleCompress/CplRleCompressConfig/*) > 0"!][!//

#define CPL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CPL_0806_510, 1
 */

[!LOOP "as:modconf('Cpl')/CplRleCompress/CplRleCompressConfig/*"!][!//
CONST(Cpl_RLECompressConfigType, CPL_CONST) [!"node:name(.)"!] =
{
  [!"node:value(./CplRleCompressVariant)"!]
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

#else /* #if (CPL_RLECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no primitive
 **         configuration.
 **/
typedef void Cpl_RleCompressConfig_PrvntEmptyTranslationUnit_t;

#endif /* #if (CPL_RLECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
