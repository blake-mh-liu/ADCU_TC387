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

/*==[Includes]================================================================*/

#include <Cal_Types.h>

#include <Cal_KeyExchange.h>
#include <Cal_KeyExchange_Cfg.h>

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValConfig/*,'node:value(./CalKeyExchangeCalcPubValPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalKeyExchangeCalcPubValPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalKeyExchangeCalcPubValPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalKeyExchangeCalcPubValPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "node:order(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretConfig/*,'node:value(./CalKeyExchangeCalcSecretPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalKeyExchangeCalcSecretPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalKeyExchangeCalcSecretPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalKeyExchangeCalcSecretPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//


/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/



/*==[Declaration of functions with internal linkage]==========================*/



/*==[Constants with internal linkage]=========================================*/



/*==[Variables with internal linkage]=========================================*/



/*==[Variables with external linkage]=========================================*/



/*==[Constants with external linkage]=========================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE)
CONST(Cal_KeyExchangePubValConfigType, CAL_CONST)
  Cal_KeyExPubValConfigurations[CAL_KEYEXPUBVAL_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalKeyExchangeCalcPubValPrimitiveName)"!],
    &([!"node:value(./CalKeyExchangeCalcPubValInitConfiguration)"!])
  },
[!ENDLOOP!][!//
};
#endif /* #if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE) */

#if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE)
CONST(Cal_KeyExchangeSecretConfigType, CAL_CONST)
  Cal_KeyExSecretConfigurations[CAL_KEYEXSECRET_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalKeyExchangeCalcSecretPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalKeyExchangeCalcSecretPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalKeyExchangeCalcSecretPrimitiveName)"!]Finish,
    &([!"node:value(./CalKeyExchangeCalcSecretInitConfiguration)"!])
},
[!ENDLOOP!][!//
};

#else /* #if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no KeyExchange
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE) #else */

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>



/*==[Definition of functions with external linkage]===========================*/


/*==[Definition of functions with internal linkage]===========================*/

