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

#ifndef CAL_KEYDERIVE_CFG_H
#define CAL_KEYDERIVE_CFG_H


/*==================[includes]====================================================================*/

#include <Cal_Types.h>

/*==================[macros]======================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalKeyDerive/CalKeyDeriveConfig/*))"!][!//
#define CAL_KEY_DERIVE_ENABLED TRUE
[!ELSE!][!//
#define CAL_KEY_DERIVE_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_KEY_DERIVE_ENABLED == TRUE)

/** \brief size in bytes of the context buffer configured for key derivation.
*/
#define CAL_KEYDERIVE_CONTEXT_BUFFER_SIZE CAL_LEN_IN_ALIGN_TYPE \
  ([!"node:value(as:modconf('Cal')/CalKeyDerive/CalKeyDeriveMaxCtxBufByteSize)"!]U)


/* !LINKSTO CAL0026, 1
 */
[!VAR "CalKeyDeriveConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalKeyDerive/CalKeyDeriveConfig/*"!][!//

/** \brief Identifier of an KeyDerive service configuration.
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalKeyDeriveConfigIndex)"!]U
[!VAR "CalKeyDeriveConfigIndex" = "$CalKeyDeriveConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the key derivation service
 */
#define CAL_KEYDERIVE_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalKeyDerive/CalKeyDeriveConfig/*))"!]U


/*==================[type definitions]============================================================*/


/*==================[external function declarations]==============================================*/


/*==================[external constants]==========================================================*/


/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_KEY_DERIVE_ENABLED == TRUE) */


#endif /* #ifndef CAL_KEYDERIVE_CFG_H */

