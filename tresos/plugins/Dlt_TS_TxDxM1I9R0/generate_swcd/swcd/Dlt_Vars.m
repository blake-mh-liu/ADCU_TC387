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
/* !LINKSTO Dlt.swdd.DltGeneration.Template.Dlt_VarsSWCD_m,1 */
*** multiple inclusion protection ***
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

*** Number of Swcs to be notified in case of log level and trace status changes ***
*/!][!VAR "DltNumSwcsToNotify" = "0"!][!/*
*/!][!VAR "VfbTraceFunctionCount" = "0"!][!/*
*/!][!IF "(num:i($DltServiceAPI) >= $AUTOSAR_431) and (DltGeneral/DltRteUsage = 'true')"!][!/*
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

*** Calculate the number of pre-configured AppIDs and ContextIDs ***
*/!][!IF "(num:i($DltServiceAPI) >= $AUTOSAR_431)"!][!/*
    */!][!VAR "MaxAppNo" = "0"!][!/*
    */!][!VAR "MaxCountCtxtPerAPP" = "0"!][!/*

    */!][!VAR "ValOfStringInit" = "num:i(0)"!][!/*
    */!][!VAR "AppNoPerSwC" = "0"!][!/*
    */!][!VAR "uniqueAppId" = "0"!][!/*
    */!][!VAR "uniqueAppIdToBeCompared" = "0"!][!/*
    */!][!IF "(node:exists(DltSwc/*)) and (num:i(count(DltSwc/*)) > 0)"!][!/*
      */!][!FOR "SwcCnt1" = "1" TO "num:i(count(DltSwc/*))"!][!/*
        */!][!IF "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*)) > 0"!][!/*
          */!][!FOR "idx" = "1" TO "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*))"!][!/*
            */!][!VAR "ValOfStringInit" = "text:replace($ValOfStringInit,'0',concat($idx,'0'))"!][!/*
          */!][!ENDFOR!][!/*
          */!][!FOR "countStart" = "1" TO "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*))"!][!/*
            */!][!IF "substring($ValOfStringInit, $countStart,1) = string($countStart)"!][!/*
              */!][!FOR "elementsNo" = "$countStart" TO "num:i(count(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*))"!][!/*
                */!][!VAR "uniqueAppId" = "node:value(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*[num:i($countStart)]/DltSwcApplicationId)"!][!/*
                */!][!VAR "uniqueAppIdToBeCompared" = "node:value(DltSwc/*[num:i($SwcCnt1)]/DltSwcContext/*[num:i($elementsNo)]/DltSwcApplicationId)"!][!/*
                */!][!IF "$uniqueAppIdToBeCompared = $uniqueAppId"!][!/*
                  */!][!VAR "ValOfStringInit" = "text:replace($ValOfStringInit, $elementsNo, '0')"!][!/*
                */!][!ENDIF!][!/*
              */!][!ENDFOR!][!/*
              */!][!VAR "MaxAppNo" = "$MaxAppNo + 1"!][!/*
              */!][!VAR "AppNoPerSwC" ="$AppNoPerSwC + 1"!][!/*
            */!][!ENDIF!][!/*
          */!][!ENDFOR!][!/*
          */!][!VAR "AppNoPerSwC" = "0"!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDFOR!][!/*
    */!][!ENDIF!][!/*

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

*** End of file ***
*/!][!ENDIF!][!/*
*/!][!//
