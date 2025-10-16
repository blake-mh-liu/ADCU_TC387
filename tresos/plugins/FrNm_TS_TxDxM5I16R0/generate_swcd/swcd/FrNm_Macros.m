[!/**
 * \file
 *
 * \brief AUTOSAR FrNm
 *
 * This file contains the implementation of the AUTOSAR
 * module FrNm.
 *
 * \version 5.16.16
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/* These checks were originally present as INVALID checks in FrNm.xdm.
   * Since these inter-module checks involve parameters from different
   * configuration classes, it's no more possible to keep them in FrNm.xdm.
   * Refer ASCFRNM-588 for more details.
   */!]

[!/* *** multiple inclusion protection *** */!]
[!IF "not(var:defined('FRNM_MACROS_M'))"!]
[!VAR "FRNM_MACROS_M" = "'true'"!]


[!/*
*************************************************************************
* MACRO to indicate if PN synchronized shutdown is enabled.
*************************************************************************
*/!][!//
[!NOCODE!][!//
[!MACRO "GetSynchronizedPncShutdownEnabled"!][!//
  [!IF "num:i(count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*[1]/FrNmChannel/eb-list::*[(node:existsAndTrue(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled))])) > 0"!]
    [!VAR "SynchronizedPncShutdownEnabled" = "'true'"!][!//
  [!ELSE!][!//
    [!VAR "SynchronizedPncShutdownEnabled" = "'false'"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//

[!/*
*************************************************************************
* MACRO to count number of PNC-Channel links both for active and passive
* channel types .
*************************************************************************
*/!][!//
[!NOCODE!][!//
[!MACRO "GetPncShutdownChannelsTypeCount"!][!//
  [!VAR "PncShutdownActiveChannels" = "num:i(0)"!][!//
  [!VAR "PncShutdownPassiveChannels" = "num:i(0)"!][!//
  
  [!SELECT "as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*[1]/FrNmChannel/eb-list::*
                [(node:existsAndTrue(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled))]
                [node:exists(node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType) and (node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_ACTIVE')]"!][!//
    [!VAR "PncShutdownActiveChannels" = "num:i($PncShutdownActiveChannels + num:i(count(as:modconf('ComM')[1]/ComMConfigSet/eb-list::*[1]/ComMPnc/eb-list::*/ComMChannelPerPnc/eb-list::*[node:value(.) = node:value(node:current()/FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)])))"!][!//
  [!ENDSELECT!][!//  
  
  [!SELECT "as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*[1]/FrNmChannel/eb-list::*
                [(node:existsAndTrue(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled))]
                [node:exists(node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType) and (node:ref(FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')]"!][!//
    [!VAR "PncShutdownPassiveChannels" = "num:i($PncShutdownPassiveChannels + num:i(count(as:modconf('ComM')[1]/ComMConfigSet/eb-list::*[1]/ComMPnc/eb-list::*/ComMChannelPerPnc/eb-list::*[node:value(.) = node:value(node:current()/FrNmChannelIdentifiers/FrNmComMNetworkHandleRef)])))"!][!//
  [!ENDSELECT!][!//  
[!ENDMACRO!][!//
[!ENDNOCODE!][!//

[!ENDIF!]