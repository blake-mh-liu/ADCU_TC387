[!/**
 * \file
 *
 * \brief AUTOSAR LinIf
 *
 * This file contains the implementation of the AUTOSAR
 * module LinIf.
 *
 * \version 5.8.50
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/* *** multiple inclusion protection ***
*/!][!IF "not(var:defined('LINIF_CHECKS_M'))"!][!/*
*/!][!VAR "LINIF_CHECKS_M"="'true'"!][!/*
*/!][!INCLUDE "LinIf_Macros.m"!][!/*

*** Channel Id needs to be zero-based consecutive ***
*** TS_LINIF_20919 ***
*** TS_LINIF_20920 ***
*/!][!VAR "id"="0"!][!/*
*/!][!LOOP "util:distinct(node:order(LinIfGlobalConfig/*[1]/LinIfChannel/*, 'LinIfChannelId'))"!][!/*
   */!][!ASSERT "LinIfChannelId = num:i($id)"!][!/*
      */!]LinIfGlobalConfig/LinIfChannel/LinIfChannelId needs to be zero-based and consecutive. Id [!"num:i($id)"!] is missing.[!/*
   */!][!ENDASSERT!][!/*
   */!][!VAR "id"="$id + 1"!][!/*
*/!][!ENDLOOP!][!/*

*/!][!/*
**********************************************************************
*/!][!ENDIF!][!/*
*/!][!//
