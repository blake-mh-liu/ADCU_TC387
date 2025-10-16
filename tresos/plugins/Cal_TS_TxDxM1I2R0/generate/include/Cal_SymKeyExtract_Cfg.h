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

#ifndef CAL_SYMKEYEXTRACT_CFG_H
#define CAL_SYMKEYEXTRACT_CFG_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>

/*==================[macros]======================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractConfig/*))"!][!//
#define CAL_SYM_KEY_EXTRACT_ENABLED TRUE
[!ELSE!][!//
#define CAL_SYM_KEY_EXTRACT_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE)

/** \brief size in bytes of the context buffer configured for symmetrical key extraction.
*/
#define CAL_SYMKEYEXTRACT_CONTEXT_BUFFER_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractMaxCtxBufByteSize)"!]U)



/* !LINKSTO CAL0026, 1
 */
[!VAR "CalSymKeyExtractConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractConfig/*"!][!//

/** \brief Identifier of an SymKeyExtract service configuration.
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalSymKeyExtractConfigIndex)"!]U
[!VAR "CalSymKeyExtractConfigIndex" = "$CalSymKeyExtractConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the symmetrical key extraction
 *        service
 */
#define CAL_SYMKEYEX_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractConfig/*))"!]U


/*==================[type definitions]============================================================*/


/*==================[external function declarations]==============================================*/


/*==================[external constants]==========================================================*/


/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE) */


#endif /* #ifndef CAL_SYMKEYEXTRACT_CFG_H */

