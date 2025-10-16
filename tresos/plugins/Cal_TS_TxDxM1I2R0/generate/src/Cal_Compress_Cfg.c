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

/* !LINKSTO EB_CAL_0801_011, 1
 */

/*==================[includes]====================================================================*/

#include <Cal_Types.h>

#include <Cal_Compress.h>
#include <Cal_Compress_Cfg.h>



#if (CAL_COMPRESS_ENABLED == STD_ON)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalCompress/CalCompressConfig/*,'node:value(./CalCompressPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalCompressPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalCompressPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalCompressPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CAL_0806_003, 1
 */
/* !LINKSTO EB_CAL_0806_500, 1
 */
/** \brief  Array of configuration structure type elements which contains the configuration of all
 **          stated compression services.
 **/
CONST(Cal_CompressConfigType, CAL_CONST) Cal_CompressConfigurations[CAL_COMPRESS_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalCompress/CalCompressConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalCompressPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalCompressPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalCompressPrimitiveName)"!]Finish,
    &([!"node:value(./CalCompressInitConfiguration)"!])
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

#else /* #if (CAL_COMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no compression
 **         configuration.
 **/
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_COMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

