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

#ifndef CAL_KEYEXCHANGE_CFG_H
#define CAL_KEYEXCHANGE_CFG_H


/*==[Includes]================================================================*/


#include <Cal_Types.h>



/*==[Macros]==================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValConfig/*))"!][!//
#define CAL_KEYEXCHANGE_PUBVAL_ENABLED TRUE
[!ELSE!][!//
#define CAL_KEYEXCHANGE_PUBVAL_ENABLED FALSE
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretConfig/*))"!][!//
#define CAL_KEYEXCHANGE_SECRET_ENABLED TRUE
[!ELSE!][!//
#define CAL_KEYEXCHANGE_SECRET_ENABLED FALSE
[!ENDIF!][!//

#if ((CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE) || (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE))


/** \brief size of the context buffer required for key exchange protocol.
 */
#define CAL_KEYEXCHANGE_CONTEXT_BUFFER_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretMaxCtxBufByteSize)"!]U)



[!VAR "CalKeyExchangePubValConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValConfig/*"!][!//

/** \brief Identifier for a public value calcultaion configuration in a key exchange protocol.
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalKeyExchangePubValConfigIndex)"!]U

[!VAR "CalKeyExchangePubValConfigIndex" = "$CalKeyExchangePubValConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/* !LINKSTO CAL0026, 1
 */
[!VAR "CalKeyExchangeSecretConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretConfig/*"!][!//

/** \brief Identifier for a secret calcultaion configuration in a key exchange protocol.
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalKeyExchangeSecretConfigIndex)"!]U

[!VAR "CalKeyExchangeSecretConfigIndex" = "$CalKeyExchangeSecretConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the public value calculation of
 *         the key exchange service
 */
#define CAL_KEYEXPUBVAL_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValConfig/*))"!]U

/** \brief Macro defining the amount of existing configurations for the secret calculation of the
 *         key exchange service
 */
#define CAL_KEYEXSECRET_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretConfig/*))"!]U


/*==[Types]===================================================================*/


/*==[Constants with external linkage]=========================================*/


/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /*#if ((CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE)||(CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE))*/


#endif /* #ifndef CAL_KEYEXCHANGE_CFG_H */

