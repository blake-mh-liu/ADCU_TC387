[!/**
 * \file
 *
 * \brief AUTOSAR Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module Nm.
 *
 * \version 5.12.16
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!NOCODE!]
[!AUTOSPACING!]

[!/* multiple inclusion protection */!]
[!IF "not(var:defined('NM_FUNCTIONS_M'))"!]
[!VAR "NM_FUNCTIONS_M"="'true'"!]

[!MACRO "SetupSynchronizedPncShutdownVariables"!]

[!VAR "BusNames" = "''"!]
[!VAR "BusNrOfPassiveChannels" = "''"!]
[!VAR "PnInfoLength" = "num:i(0)"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
  [!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!] 
    [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[(node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and (NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_CANNM')]) > 0"!]
      [!VAR "BusNames" = "concat($BusNames,' CanNm')"!]
      [!VAR "TempPassiveChannels" = "num:i(0)"!]
      [!LOOP "as:modconf('Nm')[1]/NmChannelConfig/eb-list::*"!]
        [!IF "node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType) and (NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_CANNM')"!]
          [!IF "node:exists(node:ref(NmComMChannelRef)/ComMPncGatewayType) and (node:ref(NmComMChannelRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!]
            [!VAR "TempPassiveChannels" = "num:i($TempPassiveChannels + 1)"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!VAR "BusNrOfPassiveChannels" = "concat($BusNrOfPassiveChannels,' ',$TempPassiveChannels)"!]
      [!IF "node:exists(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoLength)"!]
        [!VAR "PnInfoLength" = "num:i(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnInfo/CanNmPnInfoLength)"!]
      [!ENDIF!]
    [!ENDIF!]
    
    
    [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[(node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and (NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_FRNM')]) > 0"!]
      [!VAR "BusNames" = "concat($BusNames,' FrNm')"!]
      [!VAR "TempPassiveChannels" = "num:i(0)"!]
      [!LOOP "as:modconf('Nm')[1]/NmChannelConfig/eb-list::*"!]
        [!IF "node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType) and (NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_FRNM')"!]
          [!IF "node:exists(node:ref(NmComMChannelRef)/ComMPncGatewayType) and (node:ref(NmComMChannelRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!]
            [!VAR "TempPassiveChannels" = "num:i($TempPassiveChannels + 1)"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!VAR "BusNrOfPassiveChannels" = "concat($BusNrOfPassiveChannels,' ',$TempPassiveChannels)"!]
      [!IF "node:exists(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalFeatures/FrNmPnInfo/FrNmPnInfoLength)"!]
        [!VAR "PnInfoLength" = "num:i(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalFeatures/FrNmPnInfo/FrNmPnInfoLength)"!]
      [!ENDIF!]
    [!ENDIF!]
    
    
    [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[(node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and (NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_UDPNM')]) > 0"!]
      [!VAR "BusNames" = "concat($BusNames,' UdpNm')"!]
      [!VAR "TempPassiveChannels" = "num:i(0)"!]
      [!LOOP "as:modconf('Nm')[1]/NmChannelConfig/eb-list::*"!]
        [!IF "node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType) and (NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_UDPNM')"!]
          [!IF "node:exists(node:ref(NmComMChannelRef)/ComMPncGatewayType) and (node:ref(NmComMChannelRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!]
            [!VAR "TempPassiveChannels" = "num:i($TempPassiveChannels + 1)"!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!VAR "BusNrOfPassiveChannels" = "concat($BusNrOfPassiveChannels,' ',$TempPassiveChannels)"!]
      [!IF "node:exists(as:modconf('UdpNm')[1]/UdpNmGlobalConfig/eb-list::*[1]/UdpNmPnInfo/UdpNmPnInfoLength)"!]
        [!VAR "PnInfoLength" = "num:i(as:modconf('UdpNm')[1]/UdpNmGlobalConfig/eb-list::*[1]/UdpNmPnInfo/UdpNmPnInfoLength)"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!] [!/*[!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!] 
               */!]
[!ENDIF!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]               
[!ENDMACRO!]

[!/* end of multiple inclusion protection */!]
[!ENDIF!]

[!ENDNOCODE!]
