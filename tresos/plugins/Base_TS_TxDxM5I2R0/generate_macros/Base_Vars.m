[!/**
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
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('BASE_VARS_M'))"!][!/*
*/!][!VAR "BASE_VARS_M"="'true'"!]
  [!VAR "FrChannelAValue" = "num:i(0)"!]
  [!IF "node:exists(as:modconf('FrIf')[1]/FrIfGeneral/VendorSpecific/FrDriverAutosarVersion) and
                   (as:modconf('FrIf')[1]/FrIfGeneral/VendorSpecific/FrDriverAutosarVersion = 'ASR_44')"!]
    [!VAR "FrChannelAValue" = "num:i(1)"!]
  [!ENDIF!]
[!ENDIF!]
