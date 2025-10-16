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

#ifndef CAL_SYMBLOCKDECRYPT_CFG_H
#define CAL_SYMBLOCKDECRYPT_CFG_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>

/*==================[macros]======================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptConfig/*))"!][!//
#define CAL_SYMBLOCKDECRYPT_ENABLED TRUE
[!ELSE!][!//
#define CAL_SYMBLOCKDECRYPT_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE)

#define CAL_SYMBLOCKDECRYPT_CTX_BUF_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptMaxCtxBufByteSize)"!]U)

/* !LINKSTO CAL0026, 1
 */
[!VAR "CalSymBlockDecryptConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptConfig/*"!][!//

#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalSymBlockDecryptConfigIndex)"!]U
[!VAR "CalSymBlockDecryptConfigIndex" = "$CalSymBlockDecryptConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the symmetrical block decryption
 *         service
 */
#define CAL_SYMBLOCKDECRYPT_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptConfig/*))"!]U


/*==================[type definitions]============================================================*/


/*==================[external function declarations]==============================================*/


/*==================[external constants]==========================================================*/


/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE) */

#endif /* #ifndef CAL_SYMBLOCKDECRYPT_CFG_H */

