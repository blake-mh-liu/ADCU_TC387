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

#ifndef CAL_SIGNATUREVERIFY_CFG_H
#define CAL_SIGNATUREVERIFY_CFG_H


/*==[Includes]================================================================*/


#include <Cal_Types.h>

/*==[Macros]==================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalSignatureVerify/CalSignatureVerifyConfig/*))"!][!//
#define CAL_SIG_VRFY_ENABLED TRUE
[!ELSE!][!//
#define CAL_SIG_VRFY_ENABLED FALSE
[!ENDIF!][!//


#if (CAL_SIG_VRFY_ENABLED == TRUE)

/* !LINKSTO CAL0026, 1
 */
[!VAR "CalSignatureVerifyConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalSignatureVerify/CalSignatureVerifyConfig/*"!][!//

/** \brief Identifier of a signature verification service configuration.
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalSignatureVerifyConfigIndex)"!]U

[!VAR "CalSignatureVerifyConfigIndex" = "$CalSignatureVerifyConfigIndex + 1"!][!//
[!ENDLOOP!][!//


/** \brief size of the context buffer required for signature verification.
 */
#define CAL_SIGNATUREVERIFY_CONTEXT_BUFFER_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalSignatureVerify/CalSignatureVerifyMaxCtxBufByteSize)"!]UL)

/** \brief Macro defining the amount of existing configurations for the signature verification
 *         service
 */
#define CAL_SIGVRFY_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalSignatureVerify/CalSignatureVerifyConfig/*))"!]U


/*==[Types]===================================================================*/


/*==[Constants with external linkage]=========================================*/


/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/

#endif /* #if (CAL_SIG_VRFY_ENABLED == TRUE) */

#endif /* #ifndef CAL_SIGNATUREVERIFY_CFG_H */

