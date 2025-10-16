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

#ifndef CAL_ASYMPUBLICKEYEXTRACT_CFG_H
#define CAL_ASYMPUBLICKEYEXTRACT_CFG_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>

/*==================[macros]======================================================================*/

/** \brief Macro indicating whether there is any AsymPublicKeyExtract service configured.
 */
[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractConfig/*))"!][!//
#define CAL_ASYM_PUB_KEY_EXTRACT_ENABLED TRUE
[!ELSE!][!//
#define CAL_ASYM_PUB_KEY_EXTRACT_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE)

/** \brief size in bytes of the context buffer configured for symmetrical key extraction.
*/
#define CAL_ASYMPUBKEYEXTRACT_CTX_BUF_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractMaxCtxBufByteSize)"!]U)

/* !LINKSTO CAL0026, 1
 */
[!VAR "CalAsymPubKeyExtractConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractConfig/*"!][!//

/** \brief Identifier of an AsymPublicKeyExtract service.
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalAsymPubKeyExtractConfigIndex)"!]U
[!VAR "CalAsymPubKeyExtractConfigIndex" = "$CalAsymPubKeyExtractConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the asymmetrical public key
 *         extraction service.
 */
#define CAL_ASYMPUBKEYEXTRACT_CFG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractConfig/*))"!]U

/*==================[type definitions]============================================================*/


/*==================[external function declarations]==============================================*/


/*==================[external constants]==========================================================*/


/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE) */


#endif /* #ifndef CAL_ASYMPUBLICKEYEXTRACT_CFG_H */

