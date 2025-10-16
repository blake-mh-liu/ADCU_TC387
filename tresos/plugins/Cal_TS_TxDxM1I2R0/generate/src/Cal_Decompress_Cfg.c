/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO EB_CAL_0801_016, 1
 */

/*==================[includes]====================================================================*/

#include <Cal_Types.h>

#include <Cal_Decompress.h>
#include <Cal_Decompress_Cfg.h>



#if (CAL_DECOMPRESS_ENABLED == STD_ON)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalDecompress/CalDecompressConfig/*,'node:value(./CalDecompressPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalDecompressPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalDecompressPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalDecompressPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CAL_0806_013, 1
 */
/* !LINKSTO EB_CAL_0806_505, 1
 */
/** \brief  Array of configuration structure type elements which contains the configuration of all
 **          stated decompression services.
 **/
CONST(Cal_DecompressConfigType, CAL_CONST) Cal_DecompressConfigurations[CAL_DECOMPRESS_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalDecompress/CalDecompressConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalDecompressPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalDecompressPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalDecompressPrimitiveName)"!]Finish,
    &([!"node:value(./CalDecompressInitConfiguration)"!])
  },
[!ENDLOOP!][!//
};

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#else /* #if (CAL_DECOMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no decompression
 **         configuration.
 **/
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_DECOMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

