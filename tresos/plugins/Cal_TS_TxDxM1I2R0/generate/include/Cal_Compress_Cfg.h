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

#ifndef CAL_COMPRESS_CFG_H
#define CAL_COMPRESS_CFG_H

/*================================================================================================*/

/* !LINKSTO EB_CAL_0801_010, 1
 */

[!//
[!VAR "spacepool"="string('                                                                ')"!][!//
[!VAR "maxidflen"="'25'"!][!//
[!//
[!LOOP "as:modconf('Cal')/CalCompress/CalCompressConfig/*"!][!//
[!IF "string-length(node:name(.)) > $maxidflen"!][!VAR "maxidflen"="string-length(node:name(.))"!][!ENDIF!][!//
[!ENDLOOP!][!//
[!//
[!MACRO "SetAlign", "idflen"!][!//
[!"substring($spacepool,1,num:i($maxidflen)-num:i($idflen))"!][!//
[!ENDMACRO!][!//
[!//
/*==================[includes]====================================================================*/

#include <Cal_Types.h>

/*==================[macros]======================================================================*/

/* !LINKSTO EB_CAL_0806_000, 1
 */
/** \brief  Macro indicates whether the compression service is configured.
 **/
[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalCompress/CalCompressConfig/*))"!][!//
#define  CAL_COMPRESS_ENABLED[!CALL "SetAlign", "idflen"="20"!]  STD_ON
[!ELSE!][!//
#define  CAL_COMPRESS_ENABLED[!CALL "SetAlign", "idflen"="20"!]  STD_OFF
[!ENDIF!][!//



#if (CAL_COMPRESS_ENABLED == STD_ON)

/* !LINKSTO EB_CAL_0806_001, 1
 */
/** \brief  Macro defining the number of existing configurations for the compression service.
 **/
#define  CAL_COMPRESS_CONFIG_COUNT[!CALL "SetAlign", "idflen"="25"!]  [!"num:i(count(as:modconf('Cal')/CalCompress/CalCompressConfig/*))"!]U

/* !LINKSTO EB_CAL_0806_002, 1
 */
/** \brief  The size of the context buffer required for the compression.
 **/
#define  CAL_COMPRESS_CTX_BUF_SIZE[!CALL "SetAlign", "idflen"="25"!]  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalCompress/CalCompressMaxCtxBufByteSize)"!]U)

/* !LINKSTO EB_CAL_0806_003, 1
 */
[!LOOP "as:modconf('Cal')/CalCompress/CalCompressConfig/*"!][!//
/** \brief  Macro defining the index of configuration [!"node:name(.)"!] in Cal_CompressConfigurations
 **/
#define  [!"node:name(.)"!][!CALL "SetAlign", "idflen"="string-length(node:name(.))"!]  (Cal_ConfigIdType)[!"num:i(@index)"!]U

[!ENDLOOP!][!//
[!//
/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_COMPRESS_ENABLED == STD_ON) */

#endif /* #ifndef CAL_COMPRESS_CFG_H */

/*==================[end of file]=================================================================*/

