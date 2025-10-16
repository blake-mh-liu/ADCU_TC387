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

#ifndef CAL_MACVERIFY_CFG_H
#define CAL_MACVERIFY_CFG_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>

/*==================[macros]======================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalMacVerify/CalMacVerifyConfig/*))"!][!//
#define CAL_MAC_VERIFY_ENABLED TRUE
[!ELSE!][!//
#define CAL_MAC_VERIFY_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_MAC_VERIFY_ENABLED == TRUE)

/** \brief size of the context buffer required for the Mac verification.
 */
#define CAL_MACVERIFY_CONTEXT_BUFFER_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalMacVerify/CalMacVerifyMaxCtxBufByteSize)"!]U)


/* !LINKSTO CAL0026, 1
 */
[!VAR "CalMacVerifyConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalMacVerify/CalMacVerifyConfig/*"!][!//

#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalMacVerifyConfigIndex)"!]U
[!VAR "CalMacVerifyConfigIndex" = "$CalMacVerifyConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the Mac verification service
 */
#define CAL_MACVRFY_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalMacVerify/CalMacVerifyConfig/*))"!]U


/*==================[type definitions]============================================================*/


/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_MAC_VERIFY_ENABLED == TRUE) */

#endif /* #ifndef CAL_MACVERIFY_CFG_H */

