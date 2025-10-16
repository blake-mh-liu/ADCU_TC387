[!/**
 * \file
 *
 * \brief AUTOSAR CanSM
 *
 * This file contains the implementation of the AUTOSAR
 * module CanSM.
 *
 * \version 3.7.21
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!NOCODE!]
[!IF "not(var:defined('CANSM_MACROS_M'))"!]
[!VAR "CANSM_MACROS_M"="'true'"!]

[!VAR "useTransceiver"="num:i(as:modconf('CanSM')[1]/CanSMGeneral/CanSMMaxNumberOfTransceivers) > 0"!]
[!VAR "useDEM"="as:modconf('CanSM')[1]/ReportToDem/CanSMBusOffReportToDem = 'DEM'"!]

[!/* some resources needs to be available in code if PnSupport or(!!) transceiver are enabled  */!]
[!VAR "globalPnSupport"="as:modconf('CanSM')[1]/CanSMGeneral/CanSMPNSupport"!]
[!VAR "multiCoreSupport"="as:modconf('CanSM')[1]/CanSMGeneral/CanSMMultiCoreSupport"!]
[!VAR "ChannelsDistributionSupport"="as:modconf('CanSM')[1]/CanSMGeneral/CanSMDistributedChannelProcessingSupport"!]
[!IF "$ChannelsDistributionSupport = 'true'"!]
  [!VAR "ChannelsInitDistributionSupport"="as:modconf('CanSM')[1]/CanSMGeneral/CanSMDistributedChannelInitEnable"!]
[!ENDIF!]

[!/*
*** macros generate line breaks when expanded, so use comment-indentation here ***
*/!][!MACRO "CalcToTicks", "time", "maxTicks"!][!/*
*** results are limited to <= maxTicks, which is only necessary in case of rounding errors, ***
*** because ranges of interacting parameters are appropriately limited ***
   */!][!VAR "macroTicks"="num:i(ceiling($time div as:modconf('CanSM')[1]/CanSMGeneral/CanSMMainFunctionTimePeriod))"!][!/*
   */!][!IF "$macroTicks > num:i($maxTicks)"!][!/*
   */!][!"$maxTicks"!][!/*
   */!][!ELSE!][!/*
   */!][!"$macroTicks"!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDMACRO!][!//

[!/*
*** Macro to calculate number of partitions referenced by CanSM Channels ***
*/!][!MACRO "NumberOfPartitions"!][!/*
  */!][!VAR "CANSM_EcuC_Partition"="'false'"!][!/*
  */!][!VAR "CANSM_EcuC_Main"="'false'"!][!/*
  */!][!VAR "CANSM_EcuC_Partition_Count"="num:i(0)"!][!/*
  */!][!LOOP "(util:distinct(node:order(as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*)))"!][!/*
     */!][!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!/*
        */!][!VAR "CANSM_EcuC_Partition"="'true'"!][!/*
     */!][!ELSE!][!/*
        */!][!VAR "CANSM_EcuC_Main"="'true'"!][!/*
        */!][!VAR "CANSM_EcuC_Partition_Count"="num:i(1)"!][!/*
     */!][!ENDIF!][!/*
     */!][!IF "($CANSM_EcuC_Partition = 'true') and ($CANSM_EcuC_Main = 'true')"!][!/*
        */!][!BREAK!][!/*
     */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
  */!][!IF "($CANSM_EcuC_Partition = 'true')"!][!/*
    */!][!LOOP "as:modconf('EcuC')[1]/EcucPartitionCollection/EcucPartition/*"!][!/*
      */!][!VAR "EcuC_Partition_Referenced"="'false'"!][!/*
      */!][!VAR "PartitionName" = "as:name(.)"!][!/*
      */!][!LOOP "as:modconf('CanSM')[1]/CanSMConfiguration/*[1]/CanSMManagerNetwork/*"!][!/*
        */!][!IF "node:exists(node:ref(./CanSMComMNetworkHandleRef)/ComMChannelPartitionRef)"!][!/*
          */!][!IF "($PartitionName = as:name(as:ref(as:ref(CanSMComMNetworkHandleRef)/ComMChannelPartitionRef))) and ($EcuC_Partition_Referenced = 'false')"!][!/*
            */!][!VAR "EcuC_Partition_Referenced"="'true'"!][!/*
            */!][!VAR "CANSM_EcuC_Partition_Count"="$CANSM_EcuC_Partition_Count + 1"!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDLOOP!][!/*
  */!][!ENDIF!][!/*
  */!][!CODE!][!/*
    */!][!"num:i($CANSM_EcuC_Partition_Count)"!][!/*
  */!][!ENDCODE!][!/*
*/!][!ENDMACRO!][!//

[!ENDIF!]
[!ENDNOCODE!][!//
