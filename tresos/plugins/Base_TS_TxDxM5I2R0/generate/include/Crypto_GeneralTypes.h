/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \version 5.2.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!AUTOSPACING!][!//

#ifndef CRYPTO_GENERALTYPES_H
#define CRYPTO_GENERALTYPES_H
[!IF "not(node:exists(as:modconf('Base')/GeneralTypes/Crypto_GeneralTypes))"!]
  [!SKIPFILE!]
[!ELSE!]
  [!INCLUDE "?concat('Crypto_', text:split(node:name(as:modconf('Base')/GeneralTypes/Crypto_GeneralTypes), "_")[3], '_GeneralTypes.m')"!]
[!ENDIF!]

#endif /* #ifndef CRYPTO_GENERALTYPES_H */

/*==================[end of file]=================================================================*/

