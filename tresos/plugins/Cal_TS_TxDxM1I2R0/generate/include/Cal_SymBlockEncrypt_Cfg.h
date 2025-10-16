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

#ifndef CAL_SYMBLOCKENCRYPT_CFG_H
#define CAL_SYMBLOCKENCRYPT_CFG_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>

/*==================[macros]======================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalSymBlockEncrypt/CalSymBlockEncryptConfig/*))"!][!//
#define CAL_SYMBLOCKENCRYPT_ENABLED TRUE
[!ELSE!][!//
#define CAL_SYMBLOCKENCRYPT_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_SYMBLOCKENCRYPT_ENABLED == TRUE)

#define CAL_SYMBLOCKENCRYPT_CTX_BUF_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalSymBlockEncrypt/CalSymBlockEncryptMaxCtxBufByteSize)"!]U)


/* !LINKSTO CAL0026, 1
 */
[!VAR "CalSymBlockEncryptConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalSymBlockEncrypt/CalSymBlockEncryptConfig/*"!][!//
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalSymBlockEncryptConfigIndex)"!]U
[!VAR "CalSymBlockEncryptConfigIndex" = "$CalSymBlockEncryptConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the symmetrical block encryption
 *         service
 */
#define CAL_SYMBLOCKENCRYPT_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalSymBlockEncrypt/CalSymBlockEncryptConfig/*))"!]U


/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYMBLOCKENCRYPT_ENABLED == TRUE) */


#endif /* #ifndef CAL_SYMBLOCKENCRYPT_CFG_H */

