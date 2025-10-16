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

#ifndef CAL_SYMDECRYPT_CFG_H
#define CAL_SYMDECRYPT_CFG_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>

/*==================[macros]======================================================================*/

/** \brief This macro indicates whether there is a symmetrical decryption configured or not.
 */
[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalSymDecrypt/CalSymDecryptConfig/*))"!][!//
#define CAL_SYM_DECRYPT_ENABLED TRUE
[!ELSE!][!//
#define CAL_SYM_DECRYPT_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_SYM_DECRYPT_ENABLED == TRUE)

/** \brief size in bytes of the context buffer configured for symmetrical decryption.
*/
#define CAL_SYMDECRYPT_CTX_BUF_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalSymDecrypt/CalSymDecryptMaxCtxBufByteSize)"!]U)


/* !LINKSTO CAL0026, 1
 */
[!VAR "CalSymDecryptConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalSymDecrypt/CalSymDecryptConfig/*"!][!//

/** \biref Identifier for a SymDecrypt configuration
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalSymDecryptConfigIndex)"!]U
[!VAR "CalSymDecryptConfigIndex" = "$CalSymDecryptConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the symmetrical decryption
 *         service
 */
#define CAL_SYMDECRYPT_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalSymDecrypt/CalSymDecryptConfig/*))"!]U

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYM_DECRYPT_ENABLED == TRUE) */

#endif /* #ifndef CAL_SYMDECRYPT_CFG_H */

