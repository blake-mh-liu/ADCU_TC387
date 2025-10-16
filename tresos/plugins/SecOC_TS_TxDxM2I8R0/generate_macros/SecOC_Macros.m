[!/**
 * \file
 *
 * \brief AUTOSAR SecOC
 *
 * This file contains the implementation of the AUTOSAR
 * module SecOC.
 *
 * \version 2.8.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('SECOC_MACROS_M'))"!][!//
[!VAR "SECOC_MACROS_M"="'true'"!][!/*

--------------------------------------------------------------------------
    Set the values of useful variables use in post-build config
--------------------------------------------------------------------------

*** Determine the Data ID length in bytes ***
*/!][!IF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCDataIdLength) = 'UINT8'"!][!/*
*/!][!VAR "DataIdLen" = "1"!][!/*
*/!][!ELSEIF "node:value(as:modconf('SecOC')/SecOCEbGeneral/SecOCDataIdLength) = 'UINT16'"!][!/*
*/!][!VAR "DataIdLen" = "2"!][!/*
*/!][!ELSE!][!/*
*/!][!VAR "DataIdLen" = "4"!][!/*
*/!][!ENDIF!][!/*

*** Determine whether the secured area with a PDU is used or not ***
*/!][!VAR "SecuredAreaEn" = "node:value(SecOCEbGeneral/SecOCUseSecuredArea)"!][!/*

*** Determine whether SecOCCsmJobRefCallout is enabled ***
*/!][!VAR "UseCsmJobRefCallout" = "node:exists(SecOCEbGeneral/SecOCCsmJobRefCallout)"!][!/*

*** End of file ***
*/!][!ENDIF!][!//