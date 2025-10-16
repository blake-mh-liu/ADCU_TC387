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

#ifndef CAL_RANDOM_CFG_H
#define CAL_RANDOM_CFG_H


/*==[Includes]================================================================*/


#include <Cal_Types.h>



/*==[Macros]==================================================================*/

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalRandomSeed/CalRandomSeedConfig/*))"!][!//
#define CAL_RANDOMSEED_ENABLED TRUE
[!ELSE!][!//
#define CAL_RANDOMSEED_ENABLED FALSE
[!ENDIF!][!//

[!IF "num:i(0) != num:i(count(as:modconf('Cal')/CalRandomGenerate/CalRandomGenerateConfig/*))"!][!//
#define CAL_RANDOMGEN_ENABLED TRUE
[!ELSE!][!//
#define CAL_RANDOMGEN_ENABLED FALSE
[!ENDIF!][!//

#if ((CAL_RANDOMSEED_ENABLED == TRUE) || (CAL_RANDOMGEN_ENABLED == TRUE))


/** \brief size of the context buffer required for random number seeding and generating.
 */
#define CAL_RANDOM_CONTEXT_BUFFER_SIZE \
  CAL_LEN_IN_ALIGN_TYPE([!"node:value(as:modconf('Cal')/CalRandomSeed/CalRandomMaxCtxBufByteSize)"!]U)



[!VAR "CalRandomConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalRandomSeed/CalRandomSeedConfig/*"!][!//

/** \brief Identifier for a Random Service configuration
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalRandomConfigIndex)"!]U

[!VAR "CalRandomConfigIndex" = "$CalRandomConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/* !LINKSTO CAL0026, 1
 */
[!VAR "CalRandomConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cal')/CalRandomGenerate/CalRandomGenerateConfig/*"!][!//

/** \brief Identifier for a Random Service configuration
 */
#define [!"node:name(.)"!] (Cal_ConfigIdType)[!"num:i($CalRandomConfigIndex)"!]U

[!VAR "CalRandomConfigIndex" = "$CalRandomConfigIndex + 1"!][!//
[!ENDLOOP!][!//

/** \brief Macro defining the amount of existing configurations for the Random Seed service
 */
#define CAL_RANDOMSEED_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalRandomSeed/CalRandomSeedConfig/*))"!]U

/** \brief Macro defining the amount of existing configurations for the Random Generate service
 */
#define CAL_RANDOMGEN_CONFIG_COUNT \
  [!"num:i(count(as:modconf('Cal')/CalRandomGenerate/CalRandomGenerateConfig/*))"!]U

#endif /* #if ((CAL_RANDOMSEED_ENABLED == TRUE) || (CAL_RANDOMGEN_ENABLED == TRUE)) */

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/


#endif /* #ifndef CAL_RANDOM_CFG_H */

