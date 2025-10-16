[!/**
 * \file
 *
 * \brief AUTOSAR J1939Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Nm.
 *
 * \version 1.1.13
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('J1939NM_VARS_M'))"!][!/*
*/!][!VAR "J1939NM_VARS_M"="'true'"!][!/*

*** Total number of Channels ***
*/!][!VAR "J1939NmMaxChannel" = "num:integer(count(J1939NmConfigSet/eb-list::*[1]/J1939NmChannel/eb-list::*))"!][!/*

*** Total number of Nodes ***
*/!][!VAR "J1939NmMaxNodes" = "num:integer(count(J1939NmConfigSet/eb-list::*[1]/J1939NmNode/eb-list::*))"!][!/*

*** Total number of ComM Channels mapped to J1939Nm Channels ***
*/!][!VAR "J1939NmChannelMapToComMChannel" = "'0'"!][!/*
*/!][!LOOP "(J1939NmConfigSet/eb-list::*[1]/J1939NmChannel/eb-list::*)"!][!/*
  */!][!IF "node:refvalid(J1939NmComMNetworkHandleRef)"!][!/*
    */!][!VAR "J1939NmChannelMapToComMChannel" = "$J1939NmChannelMapToComMChannel + 1"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

*** Total number of J1939Nm Nodes ***
*/!][!VAR "J1939NmMaxNodeChannels" = "'0'"!][!/*
*/!][!LOOP "(J1939NmConfigSet/eb-list::*[1]/J1939NmNode/eb-list::*)"!][!/*
  */!][!LOOP "(J1939NmNodeChannelRef/eb-list::*)"!][!/*
    */!][!VAR "J1939NmMaxNodeChannels" = "$J1939NmMaxNodeChannels + 1"!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*

*** Calculation of Bus-Off Delay Tick period in milliseconds ***
*/!][!VAR "J1939NmBusOffDelayTickPeriod" = "((J1939NmGeneral/J1939NmBusOffDelayTickPeriod) * 1000)"!][!/*

*** Calculation of Mainfunction period in milliseconds ***
*/!][!VAR "J1939NmMainFunctionPeriod" = "((J1939NmGeneral/J1939NmMainFunctionPeriod) * 1000)"!][!/*

*** Calculation of number of DEM event refs ***
*/!][!VAR "J1939NmDemEventRefCount" = "num:integer(count(as:modconf('J1939Nm')[1]/J1939NmConfigSet/eb-list::*[1]/J1939NmChannel/eb-list::*/J1939NmNodeSpecificDemEventParameterRefs/eb-list::*))"!][!/*

*** Fixed size of the Metadata field (Preferred Address + PGN) of a J1939Nm message, in bytes ***
*/!][!VAR "PrefAddressSize" = "'1'"!][!/*
*/!][!VAR "PGNsize" = "'3'"!][!/*
*/!][!VAR "J1939NmMetaDataLength" = "num:i($PrefAddressSize + $PGNsize)"!][!/*

*/!]
[!VAR "TotalMaxChannel" = "num:i(as:modconf('J1939Nm')[1]/J1939NmGeneral/J1939NmChMaxSize)"!]
[!VAR "TotalMaxNode" = "num:i(as:modconf('J1939Nm')[1]/J1939NmGeneral/J1939NmNodeMaxSize)"!]
[!/*

*** constant values ***
*/!][!VAR "ValueFFtoInt" = "num:hextoint('0xFF')"!][!/*
*/!][!VAR "Value1FtoInt" = "num:hextoint('0x1F')"!][!/*
*/!][!VAR "ValueE0toInt" = "num:hextoint('0xE0')"!][!/*
*/!][!VAR "Value0FtoInt" = "num:hextoint('0x0F')"!][!/*
*/!][!VAR "Value80toInt" = "num:hextoint('0x80')"!][!/*
*/!][!VAR "Value7FtoInt" = "num:hextoint('0x7F')"!][!/*
*/!][!VAR "Value70toInt" = "num:hextoint('0x70')"!][!/*

*** End of file ***
*/!][!ENDIF!][!/*
*/!][!//