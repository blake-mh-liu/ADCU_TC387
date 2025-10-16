[!/**
 * \file
 *
 * \brief AUTOSAR Dlt
 *
 * This file contains the implementation of the AUTOSAR
 * module Dlt.
 *
 * \version 1.9.2
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/*
/* !LINKSTO Dlt.swdd.DltGeneration.Template.Dlt_Vars_m,1 */
*** Multiple inclusion protection ***
*/!][!IF "not(var:defined('DLT_VARS_M'))"!][!/*
*/!][!VAR "DLT_VARS_M"="'true'"!][!/*

*** Create a DltServiceAPI variable to be used throughout the generated code ***
*** Create variables for DltServiceAPI's range values ***
*/!][!VAR "AUTOSAR_421" = "0"!][!/*
*/!][!VAR "AUTOSAR_422" = "1"!][!/*
*/!][!VAR "AUTOSAR_431" = "2"!][!/*
*/!][!VAR "AUTOSAR_20_11" = "3"!][!/*
*/!][!VAR "AUTOSAR_22_11" = "4"!][!/*
*** Create main variable and initialize with the default value (AUTOSAR_421) ***
*/!][!VAR "DltServiceAPI" = "num:i($AUTOSAR_421)"!][!/*
*** Check the configured range values of DltServiceAPI ***
*/!][!IF "node:exists(as:modconf('Dlt')/DltMultipleConfigurationContainer/DltServiceAPI/DltServiceAPI)"!][!/*
*/!][!IF "as:modconf('Dlt')/DltMultipleConfigurationContainer/DltServiceAPI/DltServiceAPI = 'AUTOSAR_421'"!][!/*
*/!][!VAR "DltServiceAPI" = "num:i($AUTOSAR_421)"!][!/*
*/!][!ELSEIF "as:modconf('Dlt')/DltMultipleConfigurationContainer/DltServiceAPI/DltServiceAPI = 'AUTOSAR_422'"!][!/*
*/!][!VAR "DltServiceAPI" = "num:i($AUTOSAR_422)"!][!/*
*/!][!ELSEIF "as:modconf('Dlt')/DltMultipleConfigurationContainer/DltServiceAPI/DltServiceAPI = 'AUTOSAR_431'"!][!/*
*/!][!VAR "DltServiceAPI" = "num:i($AUTOSAR_431)"!][!/*
*/!][!ELSEIF "as:modconf('Dlt')/DltMultipleConfigurationContainer/DltServiceAPI/DltServiceAPI = 'AUTOSAR_20_11'"!][!/*
*/!][!VAR "DltServiceAPI" = "num:i($AUTOSAR_20_11)"!][!/*
*/!][!ELSE!][!/*
*/!][!VAR "DltServiceAPI" = "num:i($AUTOSAR_22_11)"!][!/*
*/!][!ENDIF!][!/*
*/!][!ENDIF!][!/*

*** Macro for EcuId ***
*/!][!IF "DltMultipleConfigurationContainer/DltProtocol/DltEcuIdChoice = 'Value'"!][!/*
*/!][!VAR "EcuId" = "''"!][!/*
*/!][!FOR "index" = "1" TO "num:i(string-length(node:value(DltMultipleConfigurationContainer/DltProtocol/DltEcuId)))"!][!/*
*/!][!VAR "EcuId" ="concat($EcuId, "'")"!][!/*
*/!][!VAR "EcuId" ="concat($EcuId, substring(node:value(DltMultipleConfigurationContainer/DltProtocol/DltEcuId), $index, 1))"!][!/*
*/!][!VAR "EcuId" ="concat($EcuId, "'")"!][!/*
*/!][!IF "$index != num:i(string-length(node:value(DltMultipleConfigurationContainer/DltProtocol/DltEcuId)))"!][!/*
*/!][!VAR "EcuId" ="concat($EcuId, ',')"!][!/*
*/!][!ENDIF!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*** Create wildcard values for ApplicationId and ContextId, taking into consideration DltApplicationIdLength/DltContextIdLength ***
*/!][!VAR "NullApplicationId" = "''"!][!/*
*/!][!VAR "NullContextId" = "''"!][!/*
*/!][!VAR "AppIdLengthIdx" = "4"!][!/*
*/!][!VAR "CtxIdLengthIdx" = "4"!][!/*
*/!][!IF "node:exists(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength)"!][!/*
*/!][!VAR "AppIdLengthIdx" = "num:i(node:value(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength))"!][!/*
*/!][!ENDIF!][!/*
*/!][!IF "node:exists(as:modconf('Dlt')/DltGeneral/DltContextIdLength)"!][!/*
*/!][!VAR "CtxIdLengthIdx" = "num:i(node:value(as:modconf('Dlt')/DltGeneral/DltContextIdLength))"!][!/*
*/!][!ENDIF!][!/*
*/!][!FOR "index" = "1" TO "num:i($AppIdLengthIdx)"!][!/*
*/!][!VAR "NullApplicationId" ="concat($NullApplicationId, "'\0',")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!FOR "index" = "1" TO "num:i($CtxIdLengthIdx)"!][!/*
*/!][!VAR "NullContextId" ="concat($NullContextId, "'\0',")"!][!/*
*/!][!ENDFOR!][!/*

*** VFB ApplicationId/ContextId ***

*/!][!VAR "VFBApplicationIdMSB" = "''"!][!/*
*/!][!VAR "VFBApplicationIdMSB" = "concat($VFBApplicationIdMSB, "'V','F','B','T'")"!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength)) and ((num:i(node:value(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength))) > 4)"!][!/*
*/!][!FOR "index" = "5" TO "num:i(node:value(DltGeneral/DltApplicationIdLength))"!][!/*
*/!][!VAR "VFBApplicationIdMSB" = "concat($VFBApplicationIdMSB, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*/!][!VAR "VFBApplicationIdLSB" ="''"!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength)) and ((num:i(node:value(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength))) > 4)"!][!/*
*/!][!FOR "index" = "5" TO "num:i(node:value(DltGeneral/DltApplicationIdLength))"!][!/*
*/!][!VAR "VFBApplicationIdLSB" ="concat($VFBApplicationIdLSB, "'\0',")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*
*/!][!VAR "VFBApplicationIdLSB" ="concat($VFBApplicationIdLSB, "'T','B','F','V'")"!][!/*

*/!][!VAR "VFBContextId" ="''"!][!/*
*/!][!VAR "VFBContextId" = "concat($VFBContextId, "'\0','\0','\0','\0'")"!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltContextIdLength)) and ((num:i(node:value(as:modconf('Dlt')/DltGeneral/DltContextIdLength))) > 4)"!][!/*
*/!][!FOR "index" = "5" TO "num:i(node:value(DltGeneral/DltContextIdLength))"!][!/*
*/!][!VAR "VFBContextId" ="concat($VFBContextId, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*** Det ApplicationId/ContextId ***

*/!][!VAR "DetApplicationIdMSB" = "''"!][!/*
*/!][!VAR "DetApplicationIdMSB" = "concat($DetApplicationIdMSB, "'D','E','T'")"!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength)) and ((num:i(node:value(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength))) > 3)"!][!/*
*/!][!FOR "index" = "4" TO "num:i(node:value(DltGeneral/DltApplicationIdLength))"!][!/*
*/!][!VAR "DetApplicationIdMSB" = "concat($DetApplicationIdMSB, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*/!][!VAR "DetApplicationIdLSB" ="''"!][!/*
*/!][!VAR "DetApplicationIdLSB" ="concat($DetApplicationIdLSB, "'T','E','D'")"!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength)) and ((num:i(node:value(as:modconf('Dlt')/DltGeneral/DltApplicationIdLength))) > 3)"!][!/*
*/!][!FOR "index" = "4" TO "num:i(node:value(DltGeneral/DltApplicationIdLength))"!][!/*
*/!][!VAR "DetApplicationIdLSB" ="concat($DetApplicationIdLSB, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*/!][!VAR "DetContextIdMSB" = "''"!][!/*
*/!][!VAR "DetContextIdMSB" = "concat($DetContextIdMSB, "'S','T','D'")"!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltContextIdLength)) and ((num:i(node:value(as:modconf('Dlt')/DltGeneral/DltContextIdLength))) > 3)"!][!/*
*/!][!FOR "index" = "4" TO "num:i(node:value(DltGeneral/DltContextIdLength))"!][!/*
*/!][!VAR "DetContextIdMSB" = "concat($DetContextIdMSB, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*/!][!VAR "DetContextIdLSB" ="''"!][!/*
*/!][!VAR "DetContextIdLSB" ="concat($DetContextIdLSB, "'D','T','S'")"!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltGeneral/DltContextIdLength)) and ((num:i(node:value(as:modconf('Dlt')/DltGeneral/DltContextIdLength))) > 3)"!][!/*
*/!][!FOR "index" = "4" TO "num:i(node:value(DltGeneral/DltContextIdLength))"!][!/*
*/!][!VAR "DetContextIdLSB" ="concat($DetContextIdLSB, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*/!][!IF "((num:i($DltServiceAPI) = $AUTOSAR_431) or (num:i($DltServiceAPI) = $AUTOSAR_20_11)) and (DltGeneral/DltProtocolVersion = 2)"!][!/*

*** Macro for AppId ***
*/!][!MACRO "DltGetAppId","DltSwcIdx", "DltSwcContextIdx"!][!/*
*/!][!VAR "ApplicationId" = "''"!][!/*
*/!][!FOR "index" = "1" TO "num:i(string-length(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcApplicationId)))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, "'")"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, substring(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcApplicationId), $index, 1))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, "'")"!][!/*
*/!][!IF "$index != num:i(string-length(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcApplicationId)))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, ',')"!][!/*
*/!][!ENDIF!][!/*
*/!][!ENDFOR!][!/*
*/!][!FOR "index" = "num:i(string-length(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcApplicationId))) + 1" TO "num:i(node:value(DltGeneral/DltApplicationIdLength))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDMACRO!][!/*

*** Macro for AppId ***
*/!][!MACRO "DltPrepareAppId","APPTOSHOW"!][!/*
*/!][!VAR "ApplicationId" = "''"!][!/*
*/!][!FOR "index" = "1" TO "num:i(string-length($APPTOSHOW))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, "'")"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, substring($APPTOSHOW, $index, 1))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, "'")"!][!/*
*/!][!IF "$index != num:i(string-length($APPTOSHOW))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, ',')"!][!/*
*/!][!ENDIF!][!/*
*/!][!ENDFOR!][!/*
*/!][!FOR "index" = "num:i(string-length($APPTOSHOW)) + 1" TO "num:i(node:value(DltGeneral/DltApplicationIdLength))"!][!/*
*/!][!VAR "ApplicationId" ="concat($ApplicationId, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDMACRO!][!/*

*/!][!MACRO "DltGetCtxId","DltSwcIdx", "DltSwcContextIdx"!][!/*
*/!][!VAR "ContextId" = "''"!][!/*
*/!][!VAR "ContextIdString" = "node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcContextId)"!][!/*
*/!][!FOR "index" = "1" TO "num:i(string-length(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcContextId)))"!][!/*
*/!][!VAR "ContextId" ="concat($ContextId, "'")"!][!/*
*/!][!VAR "ContextId" ="concat($ContextId, substring(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcContextId), $index, 1))"!][!/*
*/!][!VAR "ContextId" ="concat($ContextId, "'")"!][!/*
*/!][!IF "$index != num:i(string-length(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcContextId)))"!][!/*
*/!][!VAR "ContextId" ="concat($ContextId, ',')"!][!/*
*/!][!ENDIF!][!/*
*/!][!ENDFOR!][!/*
*/!][!FOR "index" = "num:i(string-length(node:value(DltSwc/*[num:i($DltSwcIdx)]/DltSwcContext/*[num:i($DltSwcContextIdx)]/DltSwcContextId))) + 1" TO "num:i(node:value(DltGeneral/DltContextIdLength))"!][!/*
*/!][!VAR "ContextId" ="concat($ContextId, ",'\0'")"!][!/*
*/!][!ENDFOR!][!/*
*/!][!ENDMACRO!][!/*

*/!][!ENDIF!][!/*

*** Verify if multi-core support is properly enabled ***
*/!][!VAR "MULTICORE_ENABLED" = "node:exists(as:modconf('Os')[1]/OsOS/OsNumberOfCores) and node:value(as:modconf('Os')[1]/OsOS/OsNumberOfCores) > 1 and node:value(as:modconf('Dlt')/DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution) = 'true'"!][!/*
*/!][!IF "$MULTICORE_ENABLED"!][!/*
  */!][!VAR "MULTICORE_NUM_CORES" = "node:value(as:modconf('Os')[1]/OsOS/OsNumberOfCores) - 1"!][!/*
  */!][!VAR "MULTICORE_NUM_SATELLITES" = "node:value(as:modconf('Dlt')/DltMultipleConfigurationContainer/DltBswDistribution/DltNumberOfSatellites)"!][!/*
  */!][!VAR "MULTICORE_NUM_OF_MSG_PER_SATELLITE" = "node:value(as:modconf('Dlt')/DltMultipleConfigurationContainer/DltBswDistribution/DltNumberOfMessagesPerSatellite)"!][!/*
*/!][!ELSE!][!/*
  */!][!VAR "MULTICORE_NUM_CORES" = "1"!][!/*
  */!][!VAR "MULTICORE_NUM_SATELLITES" = "0"!][!/*
  */!][!VAR "MULTICORE_NUM_OF_MSG_PER_SATELLITE" = "0"!][!/*
*/!][!ENDIF!][!/*

*** Enable or disable the generation of Rte types (by using type emitter) ***
*/!][!VAR "TYPE_RTE" = "'RTE'"!][!/*
*/!][!VAR "TYPE_RTE_AND_MULTICORE" = "'RTE'"!][!/*
*/!][!IF "DltGeneral/DltRteUsage = 'false'"!][!/*
  */!][!VAR "TYPE_RTE" = "'BSW'"!][!/*
  */!][!IF "not(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) or (DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'false')"!][!/*
    */!][!VAR "TYPE_RTE_AND_MULTICORE" = "'BSW'"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDIF!][!/*
*/!][!VAR "TYPE_MULTICORE" = "'RTE'"!][!/*
*/!][!IF "not(node:exists(DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution)) or (DltMultipleConfigurationContainer/DltBswDistribution/DltEnableBswDistribution = 'false')"!][!/*
  */!][!VAR "TYPE_MULTICORE" = "'BSW'"!][!/*
*/!][!ENDIF!][!/*

*** Number of SWCs to be notified in case of log level and trace status changes ***
*/!][!VAR "DltNumSwcsToNotify" = "0"!][!/*
*/!][!VAR "VfbTraceFunctionCount" = "0"!][!/*
*/!][!IF "(num:i($DltServiceAPI) >= $AUTOSAR_431) and (as:modconf('Dlt')/DltGeneral/DltRteUsage = 'true')"!][!/*
  */!][!LOOP "DltSwc/*"!][!/*
    */!][!IF "(node:exists(./DltSwcSupportLogLevelChangeNotification)) and (./DltSwcSupportLogLevelChangeNotification = 'true')"!][!/*
      */!][!VAR "DltNumSwcsToNotify" = "$DltNumSwcsToNotify + 1"!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
*** Number of contexts (VFB trace functions) registered by the Rte for VFB tracing ***
  */!][!IF "(DltGeneral/DltImplementVfbTrace = 'true') and node:exists(as:modconf('Rte')/RteGeneration/RteVfbTraceEnabled) and node:value(as:modconf('Rte')/RteGeneration/RteVfbTraceEnabled) = 'true' and node:exists(as:modconf('Rte')/RteGeneration/RteVfbTraceFunction) and (count(as:modconf('Rte')/RteGeneration/RteVfbTraceFunction/*) > 0)"!][!/*
      */!][!VAR "VfbTraceFunctionCount" = "count(as:modconf('Rte')/RteGeneration/RteVfbTraceFunction/*)"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDIF!][!/*

*/!][!VAR "DltNumSwcsForThresholdNotification" = "0"!][!/*
*/!][!VAR "DltNumOfTHRHReachedNotifications" = "1"!][!/*
*/!][!IF "(num:i($DltServiceAPI) >= $AUTOSAR_431) and (as:modconf('Dlt')/DltGeneral/DltRteUsage = 'true')"!][!/*
  */!][!LOOP "DltSwc/*"!][!/*
    */!][!IF "(node:exists(./DltProvideBufferThresholdCallbackPort)) and (./DltProvideBufferThresholdCallbackPort = 'true')"!][!/*
      */!][!VAR "DltNumSwcsForThresholdNotification" = "$DltNumSwcsForThresholdNotification + 1"!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!IF "$DltNumSwcsForThresholdNotification > $DltNumOfTHRHReachedNotifications"!][!/*
    */!][!VAR "DltNumOfTHRHReachedNotifications" = "$DltNumSwcsForThresholdNotification"!][!/*
  */!][!ENDIF!][!/*
*/!][!ENDIF!][!/*

*** Calculate the number of pre-configured AppIDs and ContextIDs ***
*/!][!IF "(num:i($DltServiceAPI) >= $AUTOSAR_431)"!][!/*
    */!][!VAR "MaxAppNo" = "0"!][!/*
    */!][!VAR "MaxCountCtxtPerAPP" = "0"!][!/*

    */!][!VAR "ApplicationIdStringToBeSplit" = "num:i(0)"!][!/*
    */!][!VAR "ApplicationIdStringSecondToBeSplit" = "num:i(0)"!][!/*

    */!][!IF "(node:exists(DltSwc/*)) and (num:i(count(DltSwc/*)) > 0)"!][!/*
      */!][!FOR "SwcCnt1" = "1" TO "num:i(count(DltSwc/*))"!][!/*
        */!][!IF "(node:exists(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*))"!][!/*
          */!][!IF "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*)) > 0"!][!/*
            */!][!FOR "idx1" = "1" TO "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*))"!][!/*
              */!][!VAR "ApplicationIdStringToBeSplit" = "concat((DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*[num:i($idx1)]/DltSwcApplicationId),',')"!][!/*
              */!][!VAR "ApplicationIdStringSecondToBeSplit" = "concat($ApplicationIdStringSecondToBeSplit,$ApplicationIdStringToBeSplit)"!][!/*
            */!][!ENDFOR!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDFOR!][!/*
    */!][!ENDIF!][!/*

    */!][!VAR "MaxAppNo" = "0"!][!/*
    */!][!VAR "ApplicationIdStringSecondToBeSplit" = "substring-after($ApplicationIdStringSecondToBeSplit, '0')"!][!/*
    */!][!VAR "ApplId1" = "num:i(0)"!][!/*
    */!][!VAR "ApplIdToBeCompared" = "num:i(0)"!][!/*
    */!][!VAR "ApplIdToBeFilledIntoString" = "num:i(0)"!][!/*
    */!][!VAR "ElemSize" = "num:i(0)"!][!/*
    */!][!VAR "CountForAppl" = "num:i(0)"!][!/*
    */!][!VAR "ValOfStringInit1" = "$ApplicationIdStringSecondToBeSplit"!][!/*
    */!][!VAR "ApplIdToBeFilledIntoString" = "concat($ApplIdToBeFilledIntoString, ',')"!][!/*
    */!][!VAR "AppIdNeededForInitValue" = "$ApplicationIdStringSecondToBeSplit"!][!/*
    */!][!VAR "SecondAppIdNeededForInitValue" = "$ApplicationIdStringSecondToBeSplit"!][!/*

    */!][!FOR "idx1" = "1" TO "num:i(count(DltSwc/*/DltSwcContext/*))"!][!/*
      */!][!VAR "ApplId1" = "substring-before($ValOfStringInit1, ',')"!][!/*
      */!][!VAR "ValOfStringInit1" = "substring-after($ValOfStringInit1, ',')"!][!/*
      */!][!VAR "SecondAppIdNeededForInitValue" = "$AppIdNeededForInitValue"!][!/*
      */!][!FOR "idx1" = "1" TO "num:i(count(DltSwc/*/DltSwcContext/*)) + 1"!][!/*
        */!][!VAR "ApplIdToBeCompared" = "substring-before($SecondAppIdNeededForInitValue, ',')"!][!/*
        */!][!VAR "SecondAppIdNeededForInitValue" = "substring-after($SecondAppIdNeededForInitValue, ',')"!][!/*
        */!][!VAR "ElemSize" = "string-length($ApplIdToBeCompared) + $ElemSize + 1"!][!/*
        */!][!VAR "AppIdNeededForInitValue" = "substring($ApplicationIdStringSecondToBeSplit, $ElemSize, (string-length($ApplicationIdStringSecondToBeSplit)-2) - $ElemSize)"!][!/*
        */!][!IF "($ApplIdToBeCompared != 0) and ($ApplIdToBeCompared = $ApplId1)"!][!/*
          */!][!VAR "CountForAppl" = "$CountForAppl + 1"!][!/*
          */!][!VAR "ApplIdToBeFilledIntoString" = "concat($ApplIdToBeFilledIntoString, '0,')"!][!/*
        */!][!ELSE!][!/*
          */!][!VAR "ApplIdToBeFilledIntoString" = "concat($ApplIdToBeFilledIntoString, concat($ApplIdToBeCompared,','))"!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "AppIdNeededForInitValue" = "concat($ApplIdToBeFilledIntoString, $AppIdNeededForInitValue)"!][!/*
      */!][!ENDFOR!][!/*
      */!][!VAR "SecondAppIdNeededForInitValue" = "$AppIdNeededForInitValue"!][!/*
      */!][!VAR "ApplIdToBeFilledIntoString" = "num:i(0)"!][!/*
      */!][!IF "$CountForAppl != 0"!][!/*
        */!][!IF "$CountForAppl > $MaxCountCtxtPerAPP "!][!/*
          */!][!VAR "MaxCountCtxtPerAPP" = "$CountForAppl"!][!/*
        */!][!ENDIF!][!/*
        */!][!VAR "MaxAppNo" = "$MaxAppNo + 1"!][!/*
      */!][!ENDIF!][!/*
      */!][!VAR "CountForAppl" = "0"!][!/*
    */!][!ENDFOR!][!/*

    */!][!IF "($VfbTraceFunctionCount > $MaxCountCtxtPerAPP)"!][!/*
      */!][!VAR "MaxCountCtxtPerAPP" = "$VfbTraceFunctionCount"!][!/*
    */!][!ENDIF!][!/*

*/!][!ENDIF!][!/*

*/!][!VAR "TotalAppNo" = "0"!][!/*
*/!][!VAR "NumberOfAppIDEntries" = "0"!][!/*
*/!][!VAR "ApplicationsFoundForSWCD" = "concat(num:i(0),',')"!][!/*
*/!][!IF "(node:exists(DltSwc/*)) and (num:i(count(DltSwc/*)) > 0)"!][!/*
  */!][!FOR "SwcCnt1" = "1" TO "num:i(count(DltSwc/*))"!][!/*
    */!][!IF "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*)) > 0"!][!/*
      */!][!FOR "idx" = "1" TO "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*))"!][!/*
        */!][!VAR "ApplId1" = "node:value(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*[num:i($idx)]/DltSwcApplicationId)"!][!/*
        */!][!IF "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*)) > 0"!][!/*
          */!][!VAR "EventToBeAdded" = "1"!][!/*
          */!][!VAR "ValOfStringInit1" = "$ApplicationsFoundForSWCD"!][!/*
          */!][!FOR "Index" = "1" TO "num:i($NumberOfAppIDEntries)+1"!][!/*
            */!][!VAR "ApplIdToBeCompared" = "substring-before($ValOfStringInit1, ',')"!][!/*
            */!][!VAR "ValOfStringInit1" = "substring-after($ValOfStringInit1, ',')"!][!/*
            */!][!IF "$ApplIdToBeCompared = $ApplId1"!][!/*
              */!][!VAR "EventToBeAdded" = "0"!][!/*
            */!][!ENDIF!][!/*
          */!][!ENDFOR!][!/*
          */!][!IF "$EventToBeAdded = 1"!][!/*
            */!][!VAR "TotalAppNo" = "$TotalAppNo + 1"!][!/*
            */!][!VAR "NumberOfAppIDEntries" = "$NumberOfAppIDEntries + 1"!][!/*
            */!][!VAR "ApplicationsFoundForSWCD" = "concat($ApplicationsFoundForSWCD, concat($ApplId1,','))"!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDFOR!][!/*
    */!][!ENDIF!][!/*
    */!][!VAR "NumberOfAppIDEntries" = "0"!][!/*
    */!][!VAR "ApplicationsFoundForSWCD" = "concat(num:i(0),',')"!][!/*
  */!][!ENDFOR!][!/*
*/!][!ENDIF!][!/*

*** Calculate the largest DltLogChannelMaxMessageLength out of all the configured log channels ***
*/!][!VAR "LargestDltLogChannelMaxMessageLength" = "1"!][!/*
*/!][!IF "count(as:modconf('Dlt')/DltConfigSet/*/DltLogOutput/*/DltLogChannel/*) > 0"!][!/*
  */!][!LOOP "as:modconf('Dlt')/DltConfigSet/*/DltLogOutput/*/DltLogChannel/*"!][!/*
    */!][!IF "num:i(./DltLogChannelMaxMessageLength) > $LargestDltLogChannelMaxMessageLength"!][!/*
      */!][!VAR "LargestDltLogChannelMaxMessageLength" = "num:i(./DltLogChannelMaxMessageLength)"!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDIF!][!/*

*** Calculate the array size necessary for GetLogInfo to return all configured tuples through the "logInfo" parameter ***
*/!][!VAR "LocalDltAppCtxDescriptionMaximumLength" = "255"!][!/*
*/!][!VAR "TotalNoOfConfiguredContextIds" = "1"!][!/*
*** Initialize variable with the minimum return size possible (one tuple with no description requested - 14 bytes) ***
*/!][!VAR "LogInfoArrayMaxSize" = "14"!][!/*
*/!][!IF "node:exists(as:modconf('Dlt')/DltGeneral/DltAppCtxDescriptionMaximumLength)"!][!/*
  */!][!VAR "LocalDltAppCtxDescriptionMaximumLength" = "num:i(as:modconf('Dlt')/DltGeneral/DltAppCtxDescriptionMaximumLength)"!][!/*
*/!][!ENDIF!][!/*
*/!][!IF "(node:exists(as:modconf('Dlt')/DltSwc/*)) and (num:i(count(as:modconf('Dlt')/DltSwc/*)) > 0)"!][!/*
  */!][!VAR "TotalNoOfConfiguredContextIds" = "num:i(count(as:modconf('Dlt')/DltSwc/*/DltSwcContext/*))"!][!/*
*/!][!ENDIF!][!/*
*/!][!VAR "LogInfoArrayMaxSize" = "(2 + ($TotalAppNo * ($LocalDltAppCtxDescriptionMaximumLength + 7)) + ($TotalNoOfConfiguredContextIds * ($LocalDltAppCtxDescriptionMaximumLength + 7)))"!][!/*

*** End of file ***
*/!][!ENDIF!][!/*
*/!][!//
