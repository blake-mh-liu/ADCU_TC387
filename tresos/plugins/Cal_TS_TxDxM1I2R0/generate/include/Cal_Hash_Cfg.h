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

#ifndef CAL_HASH_CFG_H
#define CAL_HASH_CFG_H


/*==[Includes]================================================================*/

#include <Cal_Types.h>


/*==[Macros]==================================================================*/
[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalHash/CalHashConfig/*))"!][!//
#define CAL_HASH_ENABLED TRUE
[!ELSE!][!//
#define CAL_HASH_ENABLED FALSE
[!ENDIF!][!//

#if (CAL_HASH_ENABLED == TRUE)

/** \brief length of the hash context buffers, in elements of type ::Cal_AlignType
 */
#define CAL_HASH_CONTEXT_BUFFER_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalHash/CalHashMaxCtxBufByteSize)"!]U)

/* !LINKSTO CAL0026, 1
 */
[!VAR "CalHashConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalHash/CalHashConfig/*"!][!//

/** \brief One of the numbers which are used to uniquely identify a hash service
 *  configuration.
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalHashConfigIndex)"!]U

[!VAR "CalHashConfigIndex" = "$CalHashConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the Hash service
 */
#define CAL_HASH_CONFIG_COUNT [!"num:i(count(as:modconf('Cal')/CalHash/CalHashConfig/*))"!]U

/*==[Types]===================================================================*/


/*==[Constants with external linkage]=========================================*/


/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/
#endif /* #if (CAL_HASH_ENABLED == TRUE) */

#endif /* #ifndef CAL_HASH_CFG_H */

