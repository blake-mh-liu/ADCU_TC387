/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \version 5.21.4
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!AUTOSPACING!][!//

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00503.Include,1 */

/*==================[inclusions]============================================*/
[!INCLUDE "../../generate_macros/ComM_Functions.m"!][!//
[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'true'"!]
[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
[!CALL "GetMasterCoreId"!][!//
[!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
[!CALL "macroGetPnOffset"!][!//
[!ENDIF!]

[!CALL "GetUsedUserPlusChannelPlusMasterPncPlusInhibitionOsApplications"!]
[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]
  [!CALL "GetUsedChannelsOsApplications"!]
  [!FOR "Idx1" = "1" TO "count(text:split($FoundChannelsOsApplications,' '))"!]
    [!VAR "CurrentOsApplication" = "string(text:split($FoundChannelsOsApplications,' ')[position() = $Idx1])"!]
#include <SchM_ComM_1_Ch_OsApplication_[!"$CurrentOsApplication"!]_ComM.h>
  [!ENDFOR!] [!/*[!FOR "Idx1" = "1" TO "count(text:split($FoundChannelsOsApplications,' '))"!]*/!]
  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
#include <SchM_ComM_1_MasterPnc.h>
  [!ENDIF!] [!/* [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!] */!]
  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]
#include <SchM_ComM_1_Inhibition.h>
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]*/!]
  [!CALL "GetUsedUserOsApplications"!]
  [!FOR "Idx1" = "1" TO "count(text:split($FoundUserOsApplications,' '))"!]
    [!VAR "CurrentOsApplication" = "string(text:split($FoundUserOsApplications,' ')[position() = $Idx1])"!]
#include <SchM_ComM_1_User_[!"$CurrentOsApplication"!]_ComM.h>
  [!ENDFOR!] [!/*[!FOR "Idx1" = "1" TO "count(text:split($FoundUserOsApplications,' '))"!]*/!]
[!ENDIF!] [!/* [!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!] */!]

/* prevent RTE symbols defined in ComM.h to be visible for ComM's .c files */
#if (defined COMM_INTERNAL_USAGE)
#error COMM_INTERNAL_USAGE already defined
#endif
#define COMM_INTERNAL_USAGE

#include <ComM_BSW.h>                   /* public API symbols */
#include <ComM_BSW_Cfg.h>               /* internal BSW config dependent header */

#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
#include <CanSM_ComM.h>                 /* Can state manager */
#endif

#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
#include <FrSM.h>                       /* Flexray state manager */
#endif

#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
#include <LinSM.h>                      /* Lin state manager */
#endif

#include <ComM_Int.h>
/*==================[macros]================================================*/

[!SELECT "ComMConfigSet/*[1]"!][!//

[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]

[!LOOP "ComMPnc/*"!]
[!VAR "count" = "num:i(count(ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef))"!]
/** \brief Number of Tx EIRA Com Signals mapped to ComMPnc_[!"ComMPncId"!] */
#if (defined COMM_NUM_TX_PNC_[!"ComMPncId"!])
#error COMM_NUM_TX_PNC_[!"ComMPncId"!] already defined
#endif
#define COMM_NUM_TX_PNC_[!"ComMPncId"!]  [!"$count"!]

[!ENDLOOP!]

[!ENDIF!][!//

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

#define COMM_START_SEC_CONST_8
#include <ComM_MemMap.h>


/*---------------[Partial Network Cluster (PNC)]-----------------*/


[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!][!//

[!CALL "GetPnInfoLength"!][!//

[!VAR "PncMaskLength" = "(num:i(num:max(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncId) div 8)) - $macroRetValGetPnOffset + 1"!][!//

[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and
      (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = 'true')"!]
  [!CALL "GetActiveChMixedWithPassive"!]
  [!IF "$ActiveChMixedWithPassive"!]
CONST(uint8, COMM_CONST) ComM_ChannelGatewayType[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
  [!IF "node:exists(ComMPncGatewayType)"!]
    [!IF "(ComMPncGatewayType = 'COMM_GATEWAY_TYPE_ACTIVE')"!]
  COMM_GATEWAY_TYPE_ACTIVE,
    [!ELSE!] [!/*[!IF "(ComMPncGatewayType = 'COMM_GATEWAY_TYPE_ACTIVE')"!]*/!]
  COMM_GATEWAY_TYPE_PASSIVE,
    [!ENDIF!] [!/*[!IF "(ComMPncGatewayType = 'COMM_GATEWAY_TYPE_ACTIVE')"!]*/!]
  [!ELSE!] [!/*[!IF "node:exists(ComMPncGatewayType)"!]*/!]
  COMM_GATEWAY_TYPE_NONE,
  [!ENDIF!] [!/*[!IF "node:exists(ComMPncGatewayType)"!]*/!]
[!ENDLOOP!]
};

  [!ENDIF!]  [!/* [!IF "$ActiveChMixedWithPassive = 'true'"!] */!]
[!ENDIF!] [!/* [!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and
             *      (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = 'true')"!]
             */!]

[!/* Generate a bit mask array for each unique RX EIRA signal */!]
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA']
        [ComMPncComSignalDirection='RX']/ComMPncComSignalRef)), 'ComHandleId'))"!]

[!/* Save the Signal Handle first */!]
[!VAR "HandleId" = "ComHandleId"!]

/** \brief Array of Rx Eira Com signal masks for Com Signal [!"node:name(.)"!] */
STATIC CONST(uint8, COMM_CONST) ComM_PncRxEiraMask_[!"node:name(.)"!][COMM_PN_INFO_LENGTH] =
{
  /* [!"$PnInfoLength  "!] [!"$macroRetValGetPnOffset  "!] [!"$PncMaskLength  "!] */
  [!VAR "loopCount" = "num:i('0')"!]
[!/* Do this for all bytes in the EIRA */!][!//
  [!FOR "I" = "$macroRetValGetPnOffset" TO "$macroRetValGetPnOffset + $PncMaskLength -1"!][!//
    [!VAR "loopCount" = "$loopCount +1"!]
    [!VAR "Mask" = "0"!][!/*
    Get all PNCs within the range of this byte
    */!][!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*[ComMPncId >= num:i($I * 8) and
            ComMPncId < num:i(($I + 1) * 8)], 'ComMPncId'))"!][!/*
          Check if this PNC contain the selected signal reference
          */!][!IF "node:containsValue(util:distinct(node:refs(ComMPncComSignal/*[ComMPncComSignalKind='EIRA']
          [ComMPncComSignalDirection='RX']/ComMPncComSignalRef))/ComHandleId, $HandleId)"!][!/*
          If so, set the respective bit
          */!][!VAR "Mask" = "bit:bitset($Mask, (ComMPncId mod 8))"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!"num:inttohex($Mask)"!]U,
  [!ENDFOR!][!//
  [!/* Initialize the array completely to avoid MISRA warnings */!][!//
  [!FOR "I" = "$loopCount + 1" TO "$PnInfoLength"!][!//
  0x00u,
  [!ENDFOR!][!//
};
[!ENDLOOP!]

[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncGatewayEnabled = 'true'"!]
[!/* Generate a bit mask array for each unique RX ERA signal */!]
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='ERA']
        [ComMPncComSignalDirection='RX']/ComMPncComSignalRef)), 'ComHandleId'))"!]

[!/* Save the Signal Handle first */!]
[!VAR "HandleId" = "ComHandleId"!]

/** \brief Array of Rx Era Com signal masks for Com Signal [!"node:name(.)"!] */
STATIC CONST(uint8, COMM_CONST) ComM_PncRxEraMask_[!"node:name(.)"!][COMM_PN_INFO_LENGTH] =
{
   [!VAR "loopCount" = "num:i('0')"!]
[!/* Do this for all bytes in the EIRA */!][!//
  [!FOR "I" = "$macroRetValGetPnOffset" TO "$macroRetValGetPnOffset + $PncMaskLength -1"!][!//
    [!VAR "loopCount" = "$loopCount +1"!]
    [!VAR "Mask" = "0"!][!/*
    Get all PNCs within the range of this byte
    */!][!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*[ComMPncId >= num:i($I * 8) and
            ComMPncId < num:i(($I + 1) * 8)], 'ComMPncId'))"!][!/*
          Check if this PNC contain the selected signal reference
          */!][!IF "node:containsValue(util:distinct(node:refs(ComMPncComSignal/*[ComMPncComSignalKind='ERA']
          [ComMPncComSignalDirection='RX']/ComMPncComSignalRef))/ComHandleId, $HandleId)"!][!/*
          If so, set the respective bit
          */!][!VAR "Mask" = "bit:bitset($Mask, (ComMPncId mod 8))"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!"num:inttohex($Mask)"!]U,
  [!ENDFOR!][!//
  [!/* Initialize the array completely to avoid MISRA warnings */!][!//
  [!FOR "I" = "$loopCount + 1" TO "$PnInfoLength"!][!//
  0x00u,
  [!ENDFOR!][!//
};
[!ENDLOOP!]
[!ENDIF!]

[!/* Generate a bit mask array for each unique TX EIRA signal */!]
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
            [ComMPncComSignalDirection='TX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
[!/* Save the Signal Handle first */!]
[!VAR "HandleId" = "ComHandleId"!]
/** \brief Array of Tx Eira Com signal masks for Com Signal [!"node:name(.)"!] */
STATIC CONST(uint8, COMM_CONST) ComM_PncTxMask_[!"node:name(.)"!][COMM_PN_INFO_LENGTH] =
{
    [!VAR "loopCount" = "num:i('0')"!]
[!/* Do this for all bytes in the EIRA */!][!//
  [!FOR "I" = "$macroRetValGetPnOffset" TO "$macroRetValGetPnOffset + $PncMaskLength -1"!][!//
    [!VAR "loopCount" = "$loopCount +1"!]
    [!VAR "Mask" = "0"!][!/*
    Get all PNCs within the range of this byte
    */!][!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*[ComMPncId >= num:i($I * 8) and
            ComMPncId < num:i(($I + 1) * 8)], 'ComMPncId'))"!][!/*
          Check if this PNC contain the selected signal reference
          */!][!IF "node:containsValue(util:distinct(node:refs(ComMPncComSignal/*
          [ComMPncComSignalDirection='TX']/ComMPncComSignalRef))/ComHandleId, $HandleId)"!][!/*
          If so, set the respective bit
          */!][!VAR "Mask" = "bit:bitset($Mask, (ComMPncId mod 8))"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!"num:inttohex($Mask)"!]U,
  [!ENDFOR!][!//
  [!/* Initialize the array completely to avoid MISRA warnings */!][!//
  [!FOR "I" = "$loopCount + 1" TO "$PnInfoLength"!][!//
  0x00u,
  [!ENDFOR!][!//
};
[!ENDLOOP!]
[!ENDIF!][!//


[!LOOP "util:distinct(node:order(ComMPnc/*, 'ComMPncId'))"!]
[!IF "num:i(count(ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)) != 0"!]
/** \brief List of Tx Eira Com signals mapped to ComMPnc_[!"ComMPncId"!] */
STATIC CONST(uint8, COMM_CONST) ComM_TxSig_Pnc_[!"ComMPncId"!][COMM_NUM_TX_PNC_[!"ComMPncId"!]] =
{
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
[!VAR "HandleId" = "ComHandleId"!]
[!VAR "SigIndex" = "0"!]
[!LOOP "util:distinct(node:order(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
[!IF "number(ComHandleId) = $HandleId"!]
  [!"num:i($SigIndex)"!], /* [!"node:name(.)"!] */
[!ENDIF!]
[!VAR "SigIndex" = "$SigIndex + 1"!]
[!ENDLOOP!]
[!ENDLOOP!]
};
[!ENDIF!][!//
[!ENDLOOP!][!//

/* !LINKSTO ComM.ECUC_ComM_00892,1 */
[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComM0PncVectorAvoidance) and (as:modconf('ComM')[1]/ComMGeneral/ComM0PncVectorAvoidance = 'true')"!]
/** \brief Pnc Gateway Type Passive */
CONST(boolean, COMM_CONST)
  ComM_PncZeroVectorAvoidanceRelease[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
  /* !LINKSTO ComM.ASR403.ECUC_ComM_00842,1 */
  [!VAR "LocalComMChannelId" = "ComMChannelId"!]
  [!IF "count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[(ComMPncComSignalDirection = 'TX') and
                                                                                       (ComMPncComSignalKind = 'ERA') and
                                                                                       (node:exists(ComMPncComSignalChannelRef)) and
                                                                                       (number(node:ref(ComMPncComSignalChannelRef)/ComMChannelId) = $LocalComMChannelId) and
                                                                                       (node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and
                                                                                       (string(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_PASSIVE')
                                                                                       ]) != 0"!]
    TRUE,
  [!ELSE!]
    FALSE,
  [!ENDIF!]
[!ENDLOOP!]
};
[!ENDIF!]

[!IF "num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*[node:exists(ComMWakeupSleepRequestEnabled) and (ComMWakeupSleepRequestEnabled = 'true') ])) != 0"!]
/** \brief List of which specifies ComMWakeupSleepRequestEnabled setting for channels */
CONST(boolean, COMM_CONST)
  ComM_WakeupSleepRequestEnabledChList[COMM_NUM_CHANNELS] =
{
  [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
    [!IF "node:exists(ComMWakeupSleepRequestEnabled) and (ComMWakeupSleepRequestEnabled = 'true')"!]
 TRUE,
    [!ELSE!]
 FALSE,
    [!ENDIF!]
  [!ENDLOOP!]
};
[!ENDIF!] [!/*[!IF "num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*[node:exists(ComMWakeupSleepRequestEnabled) and (ComMWakeupSleepRequestEnabled = 'true') ])) != 0"!]*/!]


[!IF "num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*[node:exists(ComMPncWakeupSleepRequestEnabled) and (ComMPncWakeupSleepRequestEnabled = 'true') ])) != 0"!]
/** \brief List of which specifies ComMPncWakeupSleepRequestEnabled setting for pncs */
CONST(boolean, COMM_CONST)
  ComM_WakeupSleepRequestEnabledPncList[COMM_NUM_PNC] =
{
[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*, 'ComMPncId'))"!][!//
  [!IF "node:exists(ComMPncWakeupSleepRequestEnabled) and (ComMPncWakeupSleepRequestEnabled = 'true')"!]
TRUE,
  [!ELSE!]
FALSE,
  [!ENDIF!]
[!ENDLOOP!][!//
};
[!ENDIF!] [!/*[!IF "num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*[node:exists(ComMPncWakeupSleepRequestEnabled) and (ComMPncWakeupSleepRequestEnabled = 'true') ])) != 0"!] */!]


#define COMM_STOP_SEC_CONST_8
#include <ComM_MemMap.h>

/*==================[external constants]====================================*/
[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMOptimizePncIndexingForSpeed) and (as:modconf('ComM')[1]/ComMGeneral/ComMOptimizePncIndexingForSpeed = 'true')"!]
#define COMM_START_SEC_CONST_16
#include <ComM_MemMap.h>

[!CALL "GetMaxPncId"!]

CONST(PNCHandleType, COMM_CONST)
  ComM_PncIdList[(COMM_MAX_PNCID - (COMM_PN_OFFSET * 8U)) + 1U] =
{
[!VAR "PncIndex" = "num:i(0)"!]
[!FOR "i" = "num:i($macroRetValGetPnOffset * 8)" TO "$MaxPnxcId"!]
  [!IF "count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*[ComMPncId = $i]) != 0"!]
    [!"$PncIndex"!],
    [!VAR "PncIndex" = "num:i($PncIndex + num:i(1))"!]
  [!ELSE!]
    COMM_INVALID_PNC_ID,
  [!ENDIF!] 
[!ENDFOR!]
};
#define COMM_STOP_SEC_CONST_16
#include <ComM_MemMap.h>
[!ENDIF!] [!/*[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMOptimizePncIndexingForSpeed) and (as:modconf('ComM')[1]/ComMGeneral/ComMOptimizePncIndexingForSpeed = 'true')"!]*/!]
[!ENDIF!] [!/* [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!] */!]


[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'true'"!]
#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

/** \brief List of SchM functions for Requesting ComMode from SMs */
CONST(ComM_BusSM_RequestComMode_FctPtr, COMM_CONST)
  ComM_BusSmRequestComModeMcFpList[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
  [!IF "ComMBusType='COMM_BUS_TYPE_CAN' or
        ComMBusType='COMM_BUS_TYPE_FR' or
        ComMBusType='COMM_BUS_TYPE_ETH' or
        ComMBusType='COMM_BUS_TYPE_LIN'"!]
/* !LINKSTO ComM.EB.SchM_Call_CanSM_RequestComMode,1 */
/* !LINKSTO ComM.EB.SchM_Call_FrSM_RequestComMode,1 */
/* !LINKSTO ComM.EB.SchM_Call_EthSM_RequestComMode,1 */
/* !LINKSTO ComM.EB.SchM_Call_LinSM_RequestComMode,1 */
&SchM_Call_ComM_RequiredCSEntry_BusSM_RequestComMode_[!"node:name(.)"!],
  [!ELSE!]
NULL_PTR,
  [!ENDIF!]
[!ENDLOOP!]
};

[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMDcmUsage = 'true'"!]
/** \brief List of SchM functions for Notifying Dcm */
CONST(ComM_Dcm_Notif_Type, COMM_CONST)
  ComM_Dcm_Notif_FpList[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*/ComMChannel/*, 'ComMChannelId'))"!]
  {
[!IF "count(util:distinct(node:refs(as:modconf('Dcm')[1]/DcmConfigSet/*/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/*/DcmDslConnection/*/DcmDslProtocolRx/*/DcmDslProtocolRxComMChannelRef))[node:exists(ComMChannelId) and (ComMChannelId = node:current()/ComMChannelId)]) != 0"!]
    /* !LINKSTO ComM.EB.SchM_Call_Dcm_ComM_FullComModeEntered,1 */
    &SchM_Call_ComM_RequiredCSEntry_Dcm_ComM_FullComModeEntered_[!"node:name(.)"!],
    [!IF "(ComMBusType = 'COMM_BUS_TYPE_CAN' or ComMBusType = 'COMM_BUS_TYPE_ETH') and (ComMNetworkManagement/ComMNmVariant = 'FULL' or ComMNetworkManagement/ComMNmVariant = 'PASSIVE')"!]
    /* !LINKSTO ComM.EB.SchM_Call_Dcm_ComM_SilentComModeEntered,1 */
    &SchM_Call_ComM_RequiredCSEntry_Dcm_ComM_SilentComModeEntered_[!"node:name(.)"!],
    [!ELSE!]
    NULL_PTR,
    [!ENDIF!]
    /* !LINKSTO ComM.EB.SchM_Call_Dcm_ComM_NoComModeEntered,1 */
    &SchM_Call_ComM_RequiredCSEntry_Dcm_ComM_NoComModeEntered_[!"node:name(.)"!],
[!ELSE!]
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
[!ENDIF!]
  },
[!ENDLOOP!]
};
[!ENDIF!]

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
[!ENDIF!]

#define COMM_START_SEC_CONST_8
#include <ComM_MemMap.h>

[!IF "count(ComMChannel/*) > 1"!][!//

CONST(NetworkHandleType, COMM_CONST)
  ComM_NmChannelOfChannel[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))"!][!//
[!IF "(ComMNetworkManagement/ComMNmVariant = 'FULL') or (ComMNetworkManagement/ComMNmVariant = 'PASSIVE')"!][!//
  [!"num:i(as:modconf('Nm')[1]/NmChannelConfig/*[as:ref(NmComMChannelRef)/ComMChannelId = node:current()/ComMChannelId]/NmChannelId)"!]U,
[!ELSE!][!//
  /* ComM channel [!"as:name(.)"!], ID=[!"ComMChannelId"!]
   * not associated with NM channel, NM never used */
  0xFFU,
[!ENDIF!][!//
[!ENDLOOP!][!//
};

[!ENDIF!][!//

[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true'"!]
CONST(uint8, COMM_CONST)
  ComM_EB_NoWakeupNvStorage[COMM_NUM_BYTES_NVM] =
{
[!VAR "VarNoWakeupNvStorage" = "0"!][!//
[!LOOP "util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))"!][!//
  [!IF "ComMGlobalNvmBlockDescriptor = 'true'"!][!//
   [!VAR "VarNoWakeupNvStorage" = "bit:or($VarNoWakeupNvStorage,bit:shl(1,num:i(ComMChannelId mod 8)))"!][!//
  [!ENDIF!][!//
  [!IF "((ComMChannelId + 1) mod 8) = 0 "!][!//
    [!"num:i($VarNoWakeupNvStorage)"!]U,
    [!VAR "VarNoWakeupNvStorage" = "0"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "((util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))[last()]/ComMChannelId + 1) mod 8) != 0"!]
  [!"num:i($VarNoWakeupNvStorage)"!]U
[!ENDIF!][!//
};
[!ENDIF!][!//

[!IF "count(ComMPnc/*) > 0"!][!//

CONST(boolean, COMM_CONST)
  ComM_PncNmRequest[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))"!][!//
[!IF "ComMNetworkManagement/ComMPncNmRequest = 'true'"!][!//
 TRUE,
[!ELSE!][!//
 FALSE,
[!ENDIF!][!//
[!ENDLOOP!][!//
};

[!ENDIF!][!//

#define COMM_STOP_SEC_CONST_8
#include <ComM_MemMap.h>

#define COMM_START_SEC_CONST_16
#include <ComM_MemMap.h>

#if ((COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)      \
     || (COMM_NM_VARIANT_NONE_NEEDED == STD_ON))
/* Timeout after which state "NetReqNoNm" is left when ComMNmVariant='LIGHT' or
 * 'NONE' */
CONST(uint16, COMM_CONST) ComM_NetReqNoNmTimeoutMs[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))"!][!//
  /* for channel [!"as:name(.)"!] */
[!IF "(ComMNetworkManagement/ComMNmVariant = 'LIGHT') or (ComMNetworkManagement/ComMNmVariant = 'NONE')"!][!//
  [!"num:i((../../../../ComMGeneral/ComMTMinFullComModeDuration * 1000) div (ComMMainFunctionPeriod * 1000))"!]U, /* Nm variant 'LIGHT' or 'NONE' */
[!ELSE!][!//
  0xFFU, /* channel with real bus NM support, value never used */
[!ENDIF!][!//
[!ENDLOOP!][!//
};
#endif

#if (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)
/* Timeout after which state "ready sleep" is left in ComMNmVariant=LIGHT */
CONST(uint16, COMM_CONST) ComM_ReadySleepNoNmTimeoutMs[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))"!][!//
  /* for channel [!"as:name(.)"!] */
[!IF "(ComMNetworkManagement/ComMNmVariant = 'LIGHT')"!][!//
  [!"num:i((ComMNetworkManagement/ComMNmLightTimeout * 1000) div (ComMMainFunctionPeriod * 1000))"!]U, /* Nm variant LIGHT */
[!ELSEIF "(ComMNetworkManagement/ComMNmVariant = 'NONE')"!][!//
  0U,    /* Nm variant NONE, "ready sleep" state is instantly left */
[!ELSE!][!//
  0xFFU, /* channel with real bus NM support, value never used */
[!ENDIF!][!//
[!ENDLOOP!][!//
};
#endif

[!IF "count(ComMPnc/*) > 0"!][!//

/** \brief List of Pnc Ids */
CONST(PNCHandleType, COMM_CONST) ComM_PncID[COMM_NUM_PNC] =
{
[!LOOP "util:distinct(node:order(ComMPnc/*, 'ComMPncId'))"!][!//
  [!"ComMPncId"!], /* for PNC [!"as:name(.)"!] */
[!ENDLOOP!][!//
};

[!ENDIF!][!//

#define COMM_STOP_SEC_CONST_16
#include <ComM_MemMap.h>


[!CALL "GetUsedUserPlusChannelPlusMasterPncPlusInhibitionOsApplications"!]
[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]

#define COMM_START_SEC_CONST_8
#include <ComM_MemMap.h>
/** \brief Channels Os application list */
CONST(ApplicationType, COMM_CONST) ComM_Multicore_ChannelOsApplication_List[COMM_NUM_CHANNELS] =
{
  [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
    [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
    [!"$ChannelOsApplication"!],
  [!ENDLOOP!]
};

[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
/** \brief Users Os application list */
CONST(ApplicationType, COMM_CONST) ComM_Multicore_UserOsApplication_List[COMM_NUM_USERS] =
{
  [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*,'ComMUserIdentifier'))"!]
    [!CALL "GetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
  [!"$UserOsApplication"!],
  [!ENDLOOP!]
};
[!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]

#define COMM_STOP_SEC_CONST_8
#include <ComM_MemMap.h>

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

/** \brief Channels enter exclusive area list */
CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_ChannelEnterExclusiveArea_FctPtr_List[COMM_NUM_CHANNELS] =
{
  [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
    [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
  &SchM_Enter_ComM_1_Ch_OsApplication_[!"$ChannelOsApplication"!]_ComM_SCHM_COMM_EXCLUSIVE_AREA_CH_OSAPPLICATION_[!"$ChannelOsApplication"!],
  [!ENDLOOP!]
};

/** \brief Channels exit exclusive area list */
CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_ChannelExitExclusiveArea_FctPtr_List[COMM_NUM_CHANNELS] =
{
  [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
    [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
  &SchM_Exit_ComM_1_Ch_OsApplication_[!"$ChannelOsApplication"!]_ComM_SCHM_COMM_EXCLUSIVE_AREA_CH_OSAPPLICATION_[!"$ChannelOsApplication"!],
  [!ENDLOOP!]
};

  [!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
/** \brief Users enter exclusive area list */
CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_UserEnterExclusiveArea_FctPtr_List[COMM_NUM_USERS] =
{
    [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*,'ComMUserIdentifier'))"!]
      [!CALL "GetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
  &SchM_Enter_ComM_1_User_[!"$UserOsApplication"!]_ComM_SCHM_COMM_EXCLUSIVE_AREA_USER_[!"$UserOsApplication"!],
    [!ENDLOOP!]
};

/** \brief Users exit exclusive area list */
CONST(ComM_Multicore_ExclusiveArea_FctPtr, COMM_CONST) ComM_Multicore_UserExitExclusiveArea_FctPtr_List[COMM_NUM_USERS] =
{
    [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*,'ComMUserIdentifier'))"!]
      [!CALL "GetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
  &SchM_Exit_ComM_1_User_[!"$UserOsApplication"!]_ComM_SCHM_COMM_EXCLUSIVE_AREA_USER_[!"$UserOsApplication"!],
    [!ENDLOOP!]
};
  [!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

#define COMM_START_SEC_CONST_8
#include <ComM_MemMap.h>
  [!CALL "GetChToCh_FromOsAppToOsAppList"!]
  [!IF "count(text:split($ChToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to channel function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_ChToChSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS][COMM_NUM_CHANNELS] =
{
    [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
      [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
      [!VAR "FromOsApplication"= "$ChannelOsApplication"!]
  {
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
        [!VAR "ToOsApplication"= "$ChannelOsApplication"!]
        [!CALL "GetChToCh_FromOsAppToOsAppIndex","ChToChFromOsApp_ToOsApp"= "$ChToChFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
        [!"num:i($ChToChFctPtrIndex)"!],
      [!ENDLOOP!]
  },
    [!ENDLOOP!]
};
  [!ENDIF!] [!/*[!IF "count(text:split($ChToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]

  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]
    [!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
      [!CALL "GetUserToInhibition_FromOsAppToOsAppList"!]
      [!IF "count(text:split($UserToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]
        [!CALL "GetInhibitionOsApplication"!]
        [!VAR "ToOsApplication"= "$InhibitionOsApplication"!]
/** \brief Multicore user to inhibition function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_UserToInhibitionSchmSend_FctPtr_IndexList[COMM_NUM_USERS] =
{
        [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*, 'ComMUserIdentifier'))"!]
          [!CALL "GetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
          [!VAR "FromOsApplication"= "$UserOsApplication"!]
          [!CALL "GetUserToInhibition_FromOsAppToOsAppIndex","UserToInhibitionFromOsApp_ToOsApp"="$UserToInhibitionFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"$UserToInhibitionFctPtrIndex"!],
        [!ENDLOOP!]
};
      [!ENDIF!] [!/*[!IF "count(text:split($UserToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    [!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]*/!]

  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true') and (num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
    [!CALL "GetUserToMasterPnc_FromOsAppToOsAppList"!]
    [!CALL "GetMasterPncOsApplication"!]
    [!IF "count(text:split($UserToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]
      [!VAR "ToOsApplication" = "$MasterPncOsApplication"!]
/** \brief Multicore user to master pnc function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_UserToMasterPncSchmSend_FctPtr_IndexList[COMM_NUM_USERS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*, 'ComMUserIdentifier'))"!]
        [!CALL "GetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
        [!VAR "FromOsApplication"= "$UserOsApplication"!]
        [!CALL "GetUserToMasterPnc_FromOsAppToOsAppIndex","UserToMasterPncFromOsApp_ToOsApp"="$UserToMasterPncFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"$UserToMasterPncFctPtrIndex"!],
      [!ENDLOOP!] [!/*[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*, 'ComMUserIdentifier'))"!]*/!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($UserToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]*/!]
  [!ENDIF!]

  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
    [!CALL "GetUsedChannelsOsApplications"!]
    [!CALL "GetChToMasterPnc_FromOsAppToOsAppList"!]
    [!IF "count(text:split($ChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]
      [!CALL "GetMasterPncOsApplication"!]
      [!VAR "ToOsApplication"= "$MasterPncOsApplication"!]
/** \brief Multicore channel to master pnc function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_ChToMasterPncSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
        [!VAR "FromOsApplication"= "$ChannelOsApplication"!]
        [!CALL "GetChToMasterPnc_FromOsAppToOsAppIndex","ChToMasterPncFromOsApp_ToOsApp"= "$ChToMasterPncFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"num:i($ChToMasterPncFctPtrIndex)"!],
      [!ENDLOOP!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($ChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    [!CALL "GetUsedChannelsOsApplications"!]
    [!CALL "GetMasterPncToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($MasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]
      [!CALL "GetMasterPncOsApplication"!]
      [!VAR "FromOsApplication"= "$MasterPncOsApplication"!]
/** \brief Multicore master pnc to channel function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
        [!VAR "ToOsApplication"= "$ChannelOsApplication"!]
        [!CALL "GetMasterPncToCh_FromOsAppToOsAppIndex","MasterPncToChFromOsApp_ToOsApp"= "$MasterPncToChFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"num:i($MasterPncToChFctPtrIndex)"!],
      [!ENDLOOP!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($MasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]

    [!CALL "GetEvaluateChannelMasterPncToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($EvaluateChannelMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]
      [!CALL "GetMasterPncOsApplication"!]
      [!VAR "FromOsApplication"= "$MasterPncOsApplication"!]
/** \brief Multicore master pnc to channel function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_EvaluateChannelMasterPncToChSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
        [!VAR "ToOsApplication"= "$ChannelOsApplication"!]
        [!CALL "GetEvaluateChannelMasterPncToCh_FromOsAppToOsAppIndex","EvaluateChannelMasterPncToChFromOsApp_ToOsApp"= "$EvaluateChannelMasterPncToChFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"num:i($EvaluateChannelMasterPncToChFctPtrIndex)"!],
      [!ENDLOOP!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($EvaluateChannelMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]    
  [!ENDIF!] [!/*[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]*/!]

  [!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
    [!CALL "GetUserToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($UserToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore user to channel function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[COMM_NUM_USERS][COMM_NUM_CHANNELS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*, 'ComMUserIdentifier'))"!]
  {
        [!CALL "GetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
        [!VAR "FromOsApplication"= "$UserOsApplication"!]
        [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
          [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
          [!VAR "ToOsApplication"= "$ChannelOsApplication"!]
          [!CALL "GetUserToCh_FromOsAppToOsAppIndex","UserToChFromOsApp_ToOsApp"="$UserToChFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"num:i($UserToChFctPtrIndex)"!],
        [!ENDLOOP!] [!/*[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]*/!]
  },
      [!ENDLOOP!] [!/*[!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*"!]*/!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($UserToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]
  [!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]

  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMRteUsage = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true')"!]
    [!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
      [!CALL "GetChToUser_FromOsAppToOsAppList"!]
      [!IF "count(text:split($ChToUserFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to user function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS][COMM_NUM_USERS] =
{
        [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
  {
          [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
          [!VAR "FromOsApplication"= "$ChannelOsApplication"!]
          [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*, 'ComMUserIdentifier'))"!]
            [!CALL "GetUserOsApplication","UserEcuCPartitionRef"="ComMUserEcucPartitionRef"!]
            [!VAR "ToOsApplication"= "$UserOsApplication"!]
            [!CALL "GetChToUser_FromOsAppToOsAppIndex","ChToUserFromOsApp_ToOsApp"="$ChToUserFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
    [!"num:i($ChToUserFctPtrIndex)"!],
          [!ENDLOOP!] [!/*[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*, 'ComMUserIdentifier'))"!]*/!]
  },
        [!ENDLOOP!] [!/*[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]*/!]
};
      [!ENDIF!] [!/*[!IF "count(text:split($ChToUserFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    [!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMRteUsage = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true')"!] */!]


  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]
    [!CALL "GetInhibitionOsApplication"!]
    [!CALL "GetInhibitionToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($InhibitionToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore inhibition to channel function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
        [!VAR "FromOsApplication"= "$InhibitionOsApplication"!]
        [!VAR "ToOsApplication"= "$ChannelOsApplication"!]
        [!CALL "GetInhibitionToCh_FromOsAppToOsAppIndex","InhibitionToChFromOsApp_ToOsApp"="$InhibitionToChFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"num:i($InhibitionToChFctPtrIndex)"!],
      [!ENDLOOP!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($InhibitionToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    [!CALL "GetChToInhibition_FromOsAppToOsAppList"!]
    [!IF "count(text:split($ChToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to inhibition function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
        [!VAR "FromOsApplication"= "$ChannelOsApplication"!]
        [!VAR "ToOsApplication"= "$InhibitionOsApplication"!]
        [!CALL "GetChToInhibition_FromOsAppToOsAppIndex","ChToInhibitionFromOsApp_ToOsApp"="$ChToInhibitionFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"num:i($ChToInhibitionFctPtrIndex)"!],
      [!ENDLOOP!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($ChToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]*/!]
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]*/!]

  [!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = 'true')"!]
    [!CALL "GetSynchShutDownChToMasterPnc_FromOsAppToOsAppList"!]
    [!CALL "GetNumberOfGatewayTypePassiveChannels"!]
    [!IF "count(text:split($SynchShutDownChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to master pnc function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_SynchShutDownChToMasterPncSchmSend_FctPtr_IndexList[COMM_SYNCRONIZED_SHUTDOWN_PASSIVE_CHANNEL_COUNT] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!IF "node:exists(ComMPncGatewayType) and (ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!]
          [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
          [!VAR "FromOsApplication"= "$ChannelOsApplication"!]
          [!VAR "ToOsApplication"= "$MasterPncOsApplication"!]
          [!CALL "GetSynchShutDownChToMasterPnc_FromOsAppToOsAppIndex","SynchShutDownChToMasterPncFromOsApp_ToOsApp"="$SynchShutDownChToMasterPncFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
[!"num:i($SynchShutDownChToMasterPncFctPtrIndex)"!],
        [!ENDIF!][!/*[!IF "node:exists(ComMPncGatewayType) and (ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!]*/!]
      [!ENDLOOP!][!/*[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]*/!]

};
    [!ENDIF!] [!/* [!IF "count(text:split($SynchShutDownChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!] */!]
    [!CALL "GetSynchShutDownMasterPncToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($SynchShutDownMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore master pnc to ch function pointer index list */
CONST(uint8, COMM_CONST) ComM_Multicore_SynchShutDownMasterPncToChSchmSend_FctPtr_IndexList[COMM_NUM_CHANNELS] =
{
      [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
        [!VAR "FromOsApplication"= "$MasterPncOsApplication"!]
        [!VAR "ToOsApplication"= "$ChannelOsApplication"!]
        [!CALL "GetSynchShutDownMasterPncToCh_FromOsAppToOsAppIndex","SynchShutDownMasterPncToChFromOsApp_ToOsApp"="$SynchShutDownMasterPncToChFromOsApp_ToOsApp","FromOsApplication"="$FromOsApplication","ToOsApplication"="$ToOsApplication"!]
  [!"num:i($SynchShutDownMasterPncToChFctPtrIndex)"!],
      [!ENDLOOP!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($SynchShutDownMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]
  [!ENDIF!] [!/*[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = 'true')"!]*/!]
#define COMM_STOP_SEC_CONST_8
#include <ComM_MemMap.h>

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMDcmUsage = 'true'"!]
/** \brief List of SchM functions for Notifying Dcm */
CONST(ComM_Dcm_Notif_Type, COMM_CONST)
  ComM_Dcm_Notif_FpList[COMM_NUM_CHANNELS] =
{
    [!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*/ComMChannel/*, 'ComMChannelId'))"!]
  {
      [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef" = "ComMChannelPartitionRef"!]
      [!IF "count(util:distinct(node:refs(as:modconf('Dcm')[1]/DcmConfigSet/*/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/*/DcmDslConnection/*/DcmDslProtocolRx/*/DcmDslProtocolRxComMChannelRef))[node:exists(ComMChannelId) and (ComMChannelId = node:current()/ComMChannelId)]) != 0"!]
    /* !LINKSTO ComM.EB.SchM_Call_Dcm_ComM_FullComModeEntered,1 */
    &SchM_Call_ComM_1_Ch_OsApplication_[!"$ChannelOsApplication"!]_ComM_RequiredCSEntry_Dcm_ComM_FullComModeEntered_[!"node:name(.)"!],
        [!IF "(ComMBusType = 'COMM_BUS_TYPE_CAN' or ComMBusType = 'COMM_BUS_TYPE_ETH') and (ComMNetworkManagement/ComMNmVariant = 'FULL' or ComMNetworkManagement/ComMNmVariant = 'PASSIVE')"!]
    /* !LINKSTO ComM.EB.SchM_Call_Dcm_ComM_SilentComModeEntered,1 */
    &SchM_Call_ComM_1_Ch_OsApplication_[!"$ChannelOsApplication"!]_ComM_RequiredCSEntry_Dcm_ComM_SilentComModeEntered_[!"node:name(.)"!],
        [!ELSE!] [!/*[!IF "(ComMBusType = 'COMM_BUS_TYPE_CAN' or ComMBusType = 'COMM_BUS_TYPE_ETH') and (ComMNetworkManagement/ComMNmVariant = 'FULL' or ComMNetworkManagement/ComMNmVariant = 'PASSIVE')"!]*/!]
    NULL_PTR,
        [!ENDIF!] [!/*[!IF "(ComMBusType = 'COMM_BUS_TYPE_CAN' or ComMBusType = 'COMM_BUS_TYPE_ETH') and (ComMNetworkManagement/ComMNmVariant = 'FULL' or ComMNetworkManagement/ComMNmVariant = 'PASSIVE')"!]*/!]
    /* !LINKSTO ComM.EB.SchM_Call_Dcm_ComM_NoComModeEntered,1 */
    &SchM_Call_ComM_1_Ch_OsApplication_[!"$ChannelOsApplication"!]_ComM_RequiredCSEntry_Dcm_ComM_NoComModeEntered_[!"node:name(.)"!],
      [!ELSE!] [!/*[!IF "count(util:distinct(node:refs(as:modconf('Dcm')[1]/DcmConfigSet/*/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/*/DcmDslConnection/*/DcmDslProtocolRx/*/DcmDslProtocolRxComMChannelRef))[node:exists(ComMChannelId) and (ComMChannelId = node:current()/ComMChannelId)]) != 0"!]*/!]
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
      [!ENDIF!] [!/*[!IF "count(util:distinct(node:refs(as:modconf('Dcm')[1]/DcmConfigSet/*/DcmDsl/DcmDslProtocol/DcmDslProtocolRow/*/DcmDslConnection/*/DcmDslProtocolRx/*/DcmDslProtocolRxComMChannelRef))[node:exists(ComMChannelId) and (ComMChannelId = node:current()/ComMChannelId)]) != 0"!]*/!]
  },
    [!ENDLOOP!] [!/*[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*/ComMChannel/*, 'ComMChannelId'))"!]*/!]
};
  [!ENDIF!] [!/* [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMDcmUsage = 'true'"!] */!]

  [!CALL "GetChToCh_FromOsAppToOsAppList"!]
  [!IF "count(text:split($ChToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to channel function pointer list */
CONST(ComM_Multicore_ChToChSchmSend_FctPtr, COMM_CONST) ComM_Multicore_ChToChSchmSend_FctPtr_List[COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH] =
{
    [!FOR "Idx1" = "1" TO "count(text:split($ChToChFromOsApp_ToOsApp,' '))"!]
      [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($ChToChFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
      [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
      [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_Ch_OsApplication_[!"$FromOsApplication"!]_ComM_ComM_Ch_To_Ch_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
    [!ENDFOR!]
};
  [!ENDIF!] [!/*[!IF "count(text:split($ChToChFromOsApp_ToOsApp,' ')) > 0"!] */!]

  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]
    [!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
      [!CALL "GetUserToInhibition_FromOsAppToOsAppList"!]
      [!IF "count(text:split($UserToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore user to inhibition function pointer list */
CONST(ComM_Multicore_UserToInhibitionPncSchmSend_FctPtr, COMM_CONST) ComM_Multicore_UserToInhibitonSchmSend_FctPtr_List[COMM_OS_APPLICATION_USER_TO_INHIBITION_PNC_FCTPTR_LENGTH] =
{
        [!FOR "Idx1" = "1" TO "count(text:split($UserToInhibitionFromOsApp_ToOsApp,' '))"!]
          [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($UserToInhibitionFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
          [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
          [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_User_[!"$FromOsApplication"!]_ComM_ComM_User_To_Inhibition_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
        [!ENDFOR!]
};
      [!ENDIF!] [!/*[!IF "count(text:split($UserToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    [!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]*/!]

  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true') and (num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
    [!CALL "GetUserToMasterPnc_FromOsAppToOsAppList"!]
    [!IF "count(text:split($UserToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore user to master pnc function pointer list */
CONST(ComM_Multicore_UserToMasterPncSchmSend_FctPtr, COMM_CONST) ComM_Multicore_UserToMasterPncSchmSend_FctPtr_List[COMM_OS_APPLICATION_USER_TO_MASTER_PNC_FCTPTR_LENGTH] =
{
        [!FOR "Idx1" = "1" TO "count(text:split($UserToMasterPncFromOsApp_ToOsApp,' '))"!]
          [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($UserToMasterPncFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
          [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
          [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
   &SchM_Send_ComM_1_User_[!"$FromOsApplication"!]_ComM_ComM_User_To_MasterPnc_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet
        [!ENDFOR!]
};
    [!ENDIF!] [!/*[!IF "num:i(count(text:split($UserToMasterPncFromOsApp_ToOsApp,' '))) = num:i(0)"!]*/!]
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true') and (num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]

  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
    [!CALL "GetUsedChannelsOsApplications"!]
    [!CALL "GetChToMasterPnc_FromOsAppToOsAppList"!]
    [!CALL "GetMasterPncOsApplication"!]
    [!IF "count(text:split($ChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to master pnc function pointer list */
CONST(ComM_Multicore_ChToMasterPncSchmSend_FctPtr, COMM_CONST) ComM_Multicore_ChToMasterPncSchmSend_FctPtr_List[COMM_OS_APPLICATION_CH_TO_MASTER_PNC_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($ChToMasterPncFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($ChToMasterPncFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_Ch_OsApplication_[!"$FromOsApplication"!]_ComM_ComM_Ch_To_MasterPnc_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($ChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    [!CALL "GetUsedChannelsOsApplications"!]
    [!CALL "GetMasterPncToCh_FromOsAppToOsAppList"!]
    [!CALL "GetMasterPncOsApplication"!]
    [!IF "count(text:split($MasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore master pnc to channel function pointer list */
CONST(ComM_Multicore_MasterPncToChSchmSend_FctPtr, COMM_CONST) ComM_Multicore_MasterPncToChPncSchmSend_FctPtr_List[COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($MasterPncToChFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($MasterPncToChFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_MasterPnc_ComM_MasterPnc_To_Ch_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($MasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]
   [!CALL "GetEvaluateChannelMasterPncToCh_FromOsAppToOsAppList"!]
   [!IF "count(text:split($EvaluateChannelMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore master pnc to channel function pointer list */
CONST(ComM_Multicore_EvaluateChannelMasterPncToChSchmSend_FctPtr, COMM_CONST) ComM_Multicore_EvaluateChannelMasterPncToChPncSchmSend_FctPtr_List[COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($EvaluateChannelMasterPncToChFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($EvaluateChannelMasterPncToChFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_MasterPnc_ComM_EvaluateChannel_MasterPnc_To_Ch_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($EvaluateChannelMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]    
    
  [!ENDIF!] [!/*[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]*/!]

  [!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
    [!CALL "GetUserToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($UserToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore user to channel function pointer list */
CONST(ComM_Multicore_UserToChSchmSend_FctPtr, COMM_CONST) ComM_Multicore_UserToChSchmSend_FctPtr_List[COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($UserToChFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($UserToChFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_User_[!"$FromOsApplication"!]_ComM_ComM_User_To_Ch_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($UserToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]
  [!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]

  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMRteUsage = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true')"!]
    [!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]
      [!CALL "GetChToUser_FromOsAppToOsAppList"!]
      [!IF "count(text:split($ChToUserFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to user function pointer list */
CONST(ComM_Multicore_ChToUserSchmSend_FctPtr, COMM_CONST) ComM_Multicore_ChToUserSchmSend_FctPtr_List[COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH] =
{
        [!FOR "Idx1" = "1" TO "count(text:split($ChToUserFromOsApp_ToOsApp,' '))"!]
          [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($ChToUserFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
          [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
          [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
   &SchM_Send_ComM_1_Ch_OsApplication_[!"$FromOsApplication"!]_ComM_ComM_Ch_To_User_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
        [!ENDFOR!]
};
      [!ENDIF!] [!/*[!IF "count(text:split($ChToUserFromOsApp_ToOsApp,' ')) > 0"!]]*/!]
    [!ENDIF!] [!/*[!IF "(num:i(count(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMUser/*)) > 0)"!]*/!]
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMRteUsage = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true')"!]*/!]

  [!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]
    [!CALL "GetInhibitionToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($InhibitionToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore inhibition to channel function pointer list */
CONST(ComM_Multicore_InhibitionToChSchmSend_FctPtr, COMM_CONST) ComM_Multicore_InhibitionToChSchmSend_FctPtr_List[COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($InhibitionToChFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($InhibitionToChFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_Inhibition_ComM_Inhibition_To_Ch_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($InhibitionToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    [!CALL "GetChToInhibition_FromOsAppToOsAppList"!]
    [!IF "count(text:split($ChToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to inhibition function pointer list */
CONST(ComM_Multicore_ChToInhibitionSchmSend_FctPtr, COMM_CONST) ComM_Multicore_ChToInhibitionSchmSend_FctPtr_List[COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($ChToInhibitionFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($ChToInhibitionFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_Ch_OsApplication_[!"$FromOsApplication"!]_ComM_ComM_Ch_To_Inhibition_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]
};
    [!ENDIF!][!/*[!IF "count(text:split($ChToInhibitionFromOsApp_ToOsApp,' ')) > 0"!]*/!]
  [!ENDIF!] [!/*[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!]*/!]


  [!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = 'true')"!]
    [!CALL "GetSynchShutDownChToMasterPnc_FromOsAppToOsAppList"!]
    [!IF "count(text:split($SynchShutDownChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore channel to masterpncv function pointer list */
CONST(ComM_Multicore_SynchShutDownChToMasterPncSend_FctPtr, COMM_CONST) ComM_Multicore_SynchShutDownChToMasterPncSchmSend_FctPtr_List[COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($SynchShutDownChToMasterPncFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($SynchShutDownChToMasterPncFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_Ch_OsApplication_[!"$FromOsApplication"!]_ComM_ComM_SynchShutDownCh_To_MasterPnc_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]
};
    [!ENDIF!] [!/*[!IF "count(text:split($SynchShutDownChToMasterPncFromOsApp_ToOsApp,' ')) > 0"!]*/!]
    
    [!CALL "GetSynchShutDownMasterPncToCh_FromOsAppToOsAppList"!]
    [!IF "count(text:split($SynchShutDownMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]
/** \brief Multicore master pnc to channel function pointer index list */
CONST(ComM_Multicore_SynchShutDownMasterPncToChSend_FctPtr, COMM_CONST) ComM_Multicore_SynchShutDownMasterPncToChSchmSend_FctPtr_List[COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH] =
{
      [!FOR "Idx1" = "1" TO "count(text:split($SynchShutDownMasterPncToChFromOsApp_ToOsApp,' '))"!]
        [!VAR "CurrentFromOsAppToOsApp" = "string(text:split($SynchShutDownMasterPncToChFromOsApp_ToOsApp,' ')[position() = $Idx1])"!]
        [!VAR "FromOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 1])"!]
        [!VAR "ToOsApplication" = "string(text:split($CurrentFromOsAppToOsApp,'->')[position() = 2])"!]
  &SchM_Send_ComM_1_MasterPnc_ComM_SynchShutDown_MasterPnc_To_Ch_From_[!"$FromOsApplication"!]_To_[!"$ToOsApplication"!]_DataSet,
      [!ENDFOR!]      
      
};
    [!ENDIF!] [!/*[!IF "count(text:split($SynchShutDownMasterPncToChFromOsApp_ToOsApp,' ')) > 0"!]*/!]    
    
  [!ENDIF!] [!/*[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = 'true')"!]*/!]
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

#define COMM_START_SEC_CONST_16
#include <ComM_MemMap.h>
  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
      [!CALL "GetMulticoreNoOfRxBuffers"!]
      [!CALL "GetMasterPncOsApplication"!]
      [!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)))) > 0"!]
/** \brief Multicore RX EIRA configuration list */
CONST(ComM_RxSignal_Struct_Type, COMM_CONST) ComM_RxComSignalEiraCfg[COMM_NUM_RX_EIRA_SIGNALS] =
{
    [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
  {
        [!"ComHandleId"!],  /* [!"node:name(.)"!] */
      [!IF "num:i($MulticoreNoOfRxBuffers) != 0"!]
        [!CALL "GetSignalOsApplication","SignalHandle"="ComHandleId","Direction"="'RX'"!]
        [!IF "$SignalOsApplication != $MasterPncOsApplication"!]
          [!CALL "GetMulticoreRxSignalIndex","SignalHandleId"="ComHandleId"!]
          [!"num:i($MulticoreRxSignalIndex)"!]U, /* MulticoreRxBufferIndex */
          FALSE /* isLocalOsApplication */
        [!ELSE!]
          0U,  /* MulticoreRxBufferIndex not used */
          TRUE /* isLocalOsApplication */
        [!ENDIF!]
      [!ENDIF!]

  },
    [!ENDLOOP!] [!/* [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)), 'ComHandleId'))"!]*/!]
};
    [!ENDIF!] [!/*[!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)))) > 0"!]*/!]
    [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncGatewayEnabled = 'true'"!]
/** \brief Multicore active RX ERA configuration list */
CONST(ComM_RxSignal_Struct_Type, COMM_CONST) ComM_RxComSignalActiveEraCfg[COMM_NUM_RX_ACTIVE_ERA_SIGNALS] =
{
      [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
                             [ComMPncComSignalKind='ERA']
                             [ComMPncComSignalDirection='RX']
                             [(node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType='COMM_GATEWAY_TYPE_ACTIVE')]/ComMPncComSignalRef)),
                             'ComHandleId'))"!]
  {
          [!"ComHandleId"!],  /* [!"node:name(.)"!] */
        [!IF "num:i($MulticoreNoOfRxBuffers) != 0"!]
          [!CALL "GetSignalOsApplication","SignalHandle"="ComHandleId","Direction"="'RX'"!]
          [!IF "$SignalOsApplication != $MasterPncOsApplication"!]
            [!CALL "GetMulticoreRxSignalIndex","SignalHandleId"="ComHandleId"!]
            [!"num:i($MulticoreRxSignalIndex)"!]U, /* MulticoreRxBufferIndex */
            FALSE /* isLocalOsApplication */
          [!ELSE!]
            0U, /* MulticoreRxBufferIndex not used */
            TRUE /* isLocalOsApplication */
          [!ENDIF!]
        [!ENDIF!]
  },
      [!ENDLOOP!] [!/* [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
                             [ComMPncComSignalKind='ERA']
                             [ComMPncComSignalDirection='RX']
                             [(node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType='COMM_GATEWAY_TYPE_ACTIVE')]/ComMPncComSignalRef)),
                             'ComHandleId'))"!] */!]
};

/** \brief Multicore unfiltered RX ERA configuration list */
CONST(ComM_RxSignal_Struct_Type, COMM_CONST) ComM_RxComSignalUnfilteredEraCfg[COMM_NUM_RX_UNFILTERED_ERA_SIGNALS] =
{
      [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
                                   [ComMPncComSignalKind='ERA']
                                   [ComMPncComSignalDirection='RX']
                                   /ComMPncComSignalRef)),
                                   'ComHandleId'))"!]
        {
          [!"ComHandleId"!],  /* [!"node:name(.)"!] */
        [!IF "num:i($MulticoreNoOfRxBuffers) != 0"!]
          [!CALL "GetSignalOsApplication","SignalHandle"="ComHandleId","Direction"="'RX'"!]
          [!IF "$SignalOsApplication != $MasterPncOsApplication"!]
            [!CALL "GetMulticoreRxSignalIndex","SignalHandleId"="ComHandleId"!]
            [!"num:i($MulticoreRxSignalIndex)"!]U, /* MulticoreRxBufferIndex */
            FALSE /* isLocalOsApplication */
          [!ELSE!]
            0U, /* MulticoreRxBufferIndex not used */
            TRUE /* isLocalOsApplication */
          [!ENDIF!]
        [!ENDIF!]
        },
      [!ENDLOOP!][!/*[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
                                   [ComMPncComSignalKind='ERA']
                                   [ComMPncComSignalDirection='RX']
                                   /ComMPncComSignalRef)),
                                   'ComHandleId'))"!]*/!]
};
    [!ENDIF!] [!/*[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncGatewayEnabled = 'true'"!]*/!]
  [!ENDIF!] [!/*[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]*/!]
#define COMM_STOP_SEC_CONST_16
#include <ComM_MemMap.h>

[!ELSE!] [!/*[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]*/!]
  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!][!//
#define COMM_START_SEC_CONST_16
#include <ComM_MemMap.h>
    [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'true'"!][!//
      [!CALL "GetNoOfRxBuffers"!][!//
    [!ENDIF!]

    [!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)))) > 0"!]
CONST(ComM_RxSignal_Struct_Type, COMM_CONST) ComM_RxComSignalEiraCfg[COMM_NUM_RX_EIRA_SIGNALS] =
{
    [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA']
          [ComMPncComSignalDirection='RX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
  {
        [!WS "4"!][!"ComHandleId"!],  /* [!"node:name(.)"!] */
      [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport='true'"!][!//
        [!IF "num:i($NoOfRxBuffers) != 0"!][!//
          [!VAR "FoundCore" = "''"!][!//
          [!CALL "GetCore","SignalHandle"="ComHandleId","Direction"="'RX'"!][!//
          [!IF "num:i($FoundCore) != num:i($MasterCoreId)"!][!//
            [!CALL "GetRxSignalIndex","SignalHandleId"="ComHandleId"!][!//
            [!WS "4"!][!"num:i($RxSignalIndex)"!]U, /* MulticoreRxBufferIndex */
            [!WS "4"!]FALSE /* isLocalCore */
          [!ELSE!][!//
            [!WS "4"!]0U,  /* MulticoreRxBufferIndex not used */
            [!WS "4"!]TRUE /* isLocalCore */
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!]
  },
  [!ENDLOOP!][!//
};
    [!ENDIF!] [!/*[!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)))) > 0"!]*/!]
    [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncGatewayEnabled = 'true'"!]
CONST(ComM_RxSignal_Struct_Type, COMM_CONST) ComM_RxComSignalActiveEraCfg[COMM_NUM_RX_ACTIVE_ERA_SIGNALS] =
{
      [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
                             [ComMPncComSignalKind='ERA']
                             [ComMPncComSignalDirection='RX']
                             [(node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType='COMM_GATEWAY_TYPE_ACTIVE')]/ComMPncComSignalRef)),
                             'ComHandleId'))"!]
  {
          [!WS "4"!][!"ComHandleId"!],  /* [!"node:name(.)"!] */
        [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport='true'"!][!//
          [!IF "num:i($NoOfRxBuffers) != 0"!][!//
            [!VAR "FoundCore" = "''"!][!//
            [!CALL "GetCore","SignalHandle"="ComHandleId","Direction"="'RX'"!][!//
            [!IF "num:i($FoundCore) != num:i($MasterCoreId)"!][!//
              [!CALL "GetRxSignalIndex","SignalHandleId"="ComHandleId"!][!//
              [!WS "4"!][!"num:i($RxSignalIndex)"!]U, /* MulticoreRxBufferIndex */
              [!WS "4"!]FALSE /* isLocalCore */
            [!ELSE!] [!//
              [!WS "4"!]0U, /* MulticoreRxBufferIndex not used */
              [!WS "4"!]TRUE /* isLocalCore */
            [!ENDIF!]
          [!ENDIF!][!//
        [!ENDIF!][!//
  },
      [!ENDLOOP!][!//
};

CONST(ComM_RxSignal_Struct_Type, COMM_CONST) ComM_RxComSignalUnfilteredEraCfg[COMM_NUM_RX_UNFILTERED_ERA_SIGNALS] =
{
      [!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
                             [ComMPncComSignalKind='ERA']
                             [ComMPncComSignalDirection='RX']
                             /ComMPncComSignalRef)),
                             'ComHandleId'))"!]
  {
          [!WS "4"!][!"ComHandleId"!],  /* [!"node:name(.)"!] */
        [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport='true'"!][!//
          [!IF "num:i($NoOfRxBuffers) != 0"!][!//
            [!VAR "FoundCore" = "''"!][!//
            [!CALL "GetCore","SignalHandle"="ComHandleId","Direction"="'RX'"!][!//
            [!IF "num:i($FoundCore) != num:i($MasterCoreId)"!][!//
              [!CALL "GetRxSignalIndex","SignalHandleId"="ComHandleId"!][!//
              [!WS "4"!][!"num:i($RxSignalIndex)"!]U, /* MulticoreRxBufferIndex */
              [!WS "4"!]FALSE /* isLocalCore */
            [!ELSE!] [!//
              [!WS "4"!]0U, /* MulticoreRxBufferIndex not used */
              [!WS "4"!]TRUE /* isLocalCore */
            [!ENDIF!]
          [!ENDIF!][!//
        [!ENDIF!][!//
  },
      [!ENDLOOP!][!//
};
    [!ENDIF!] [!/*[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncGatewayEnabled = 'true'"!]*/!]
#define COMM_STOP_SEC_CONST_16
#include <ComM_MemMap.h>
  [!ENDIF!] [!/* [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!] */!]
[!ENDIF!][!/*[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]*/!]


[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'true'"!][!//
[!CALL "GetNoOfTxBuffers"!][!//
[!ENDIF!]
[!CALL "GetUsedUserPlusChannelPlusMasterPncPlusInhibitionOsApplications"!]
[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]
[!CALL "GetMulticoreNoOfTxBuffers"!]
[!CALL "GetMasterPncOsApplication"!]
[!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)))) > 0"!]
#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
/** \brief Multicore unfiltered TX signals configuration list */
CONST(ComM_TxSignal_Struct_Type, COMM_CONST) ComM_TxComSignalCfg[COMM_NUM_TX_SIGNALS] =
{
  [!VAR "TxIdx" = "0"!][!//
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
  {
  [!VAR "Handle" = "ComHandleId"!]
  [!VAR "foundsignal" = "'false'"!]
  [!IF "num:i($MulticoreNoOfTxBuffers) != 0"!]
    [!CALL "GetSignalOsApplication","SignalHandle"="ComHandleId","Direction"="'TX'"!][!//
    [!IF "$SignalOsApplication != $MasterPncOsApplication"!][!//
      &SchM_Send_ComM_1_MasterPnc_ComM_SgnMasterPnc_From_[!"$MasterPncOsApplication"!]_To_[!"$SignalOsApplication "!]_DataSet_[!"node:name(.)"!],
      [!"num:i($TxIdx)"!],  /* MulticoreTxBufferIndex */
      [!VAR "TxIdx" = "num:i($TxIdx) + 1"!]
    [!ELSE!]
      NULL_PTR,
      0U, /* MulticoreTxBufferIndex not used */
    [!ENDIF!][!//
    [!WS "4"!][!"ComHandleId"!], /* [!"node:name(.)"!] */
    [!WS "4"!][!"$SignalOsApplication"!],  /* SignalOsApplication */
    [!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!]
      [!IF "$foundsignal = 'false'"!]
        [!IF "number(node:ref(ComMPncComSignalRef)/ComHandleId) = $Handle"!]
          [!IF "ComMPncComSignalKind = 'ERA'"!]
            [!IF "((node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_ACTIVE')"!]
      COMM_EIRA_ERA_ACTIVE
            [!ELSE!] [!/*[!IF "((node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_ACTIVE')"!]*/!]
      COMM_ERA_PASSIVE
            [!ENDIF!] [!/*[!IF "((node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_ACTIVE')"!]*/!]
          [!ELSE!] [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
      COMM_EIRA_ERA_ACTIVE
          [!ENDIF!] [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
          [!VAR "foundsignal" = "'true'"!]
        [!ENDIF!] [!/*[!IF "number(node:ref(ComMPncComSignalRef)/ComHandleId) = $Handle"!] */!]
      [!ENDIF!] [!/*[!IF "$foundsignal = 'false'"!]*/!]
    [!ENDLOOP!] [!/*[!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!]*/!]
  [!ELSE!][!/*[!IF "num:i($MulticoreNoOfTxBuffers) != 0"!]*/!]
    [!"ComHandleId"!], /* [!"node:name(.)"!] */
    [!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!]
      [!IF "$foundsignal = 'false'"!]
        [!IF "number(node:ref(ComMPncComSignalRef)/ComHandleId) = $Handle"!]
          [!IF "ComMPncComSignalKind = 'ERA'"!]
            [!IF "(node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and ((node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_ACTIVE')"!]
    COMM_EIRA_ERA_ACTIVE
            [!ELSE!] [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
    COMM_ERA_PASSIVE
            [!ENDIF!]  [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
          [!ELSE!]
    COMM_EIRA_ERA_ACTIVE
          [!ENDIF!] [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
          [!VAR "foundsignal" = "'true'"!]
        [!ENDIF!] [!/*[!IF "number(node:ref(ComMPncComSignalRef)/ComHandleId) = $Handle"!]*/!]
      [!ENDIF!] [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
    [!ENDLOOP!] [!/*[!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!]*/!]
  [!ENDIF!][!/*[!IF "num:i($MulticoreNoOfTxBuffers) != 0"!]*/!]
  },
[!ENDLOOP!][!//
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
[!ENDIF!] [!/*[!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)))) > 0"!]*/!]
[!ELSE!] [!/*[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]*/!]
#if (COMM_NUM_TX_SIGNALS > 0U)
#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
CONST(ComM_TxSignal_Struct_Type, COMM_CONST) ComM_TxComSignalCfg[COMM_NUM_TX_SIGNALS] =
{
  [!VAR "TxIdx" = "0"!][!//
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
  {
  [!VAR "Handle" = "ComHandleId"!]
  [!VAR "foundsignal" = "'false'"!]
  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'true'"!][!//
    [!IF "num:i($NoOfTxBuffers) != 0"!][!//
      [!VAR "FoundCore" = "''"!][!//
      [!CALL "GetCore","SignalHandle"="ComHandleId","Direction"="'TX'"!][!//
      [!IF "num:i($FoundCore) != num:i($MasterCoreId)"!][!//
        [!WS "4"!]&SchM_Send_ComM_Master_DataSet_[!"node:name(.)"!],
        [!WS "4"!][!"num:i($TxIdx)"!],  /* MulticoreTxBufferIndex */
        [!VAR "TxIdx" = "num:i($TxIdx) + 1"!][!//
      [!ELSE!][!//
        [!WS "4"!]NULL_PTR,
        [!WS "4"!]0U, /* MulticoreTxBufferIndex not used */
      [!ENDIF!][!//
      [!WS "4"!][!"ComHandleId"!], /* [!"node:name(.)"!] */
      [!WS "4"!][!"num:i($FoundCore)"!],  /* CoreId */
      [!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!][!/*
        */!][!IF "$foundsignal = 'false'"!][!/*
          */!][!IF "number(node:ref(ComMPncComSignalRef)/ComHandleId) = $Handle"!][!/*
            */!][!IF "ComMPncComSignalKind = 'ERA'"!][!/*
              */!][!IF "((node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_ACTIVE')"!][!/*
        */!][!WS "4"!]COMM_EIRA_ERA_ACTIVE[!/*
              */!][!ELSE!][!/*
        */!][!WS "4"!]COMM_ERA_PASSIVE[!/*
              */!][!ENDIF!][!/*
            */!][!ELSE!][!/*
        */!][!WS "4"!]COMM_EIRA_ERA_ACTIVE[!/*
            */!][!ENDIF!][!/*
            */!][!VAR "foundsignal" = "'true'"!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!//
    [!ELSE!][!//
      [!WS "4"!][!"ComHandleId"!], /* [!"node:name(.)"!] */
      [!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!][!/*
        */!][!IF "$foundsignal = 'false'"!][!/*
          */!][!IF "number(node:ref(ComMPncComSignalRef)/ComHandleId) = $Handle"!][!/*
            */!][!IF "ComMPncComSignalKind = 'ERA'"!][!/*
              */!][!IF "(node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and ((node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_ACTIVE')"!][!/*
      */!][!WS "4"!]COMM_EIRA_ERA_ACTIVE[!/*
              */!][!ELSE!][!/*
      */!][!WS "4"!]COMM_ERA_PASSIVE[!/*
              */!][!ENDIF!][!/*
            */!][!ELSE!][!/*
      */!][!WS "4"!]COMM_EIRA_ERA_ACTIVE[!/*
            */!][!ENDIF!][!/*
            */!][!VAR "foundsignal" = "'true'"!][!/*
          */!][!ENDIF!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!//
    [!ENDIF!][!//
  [!ELSE!][!//
    [!WS "4"!][!"ComHandleId"!], /* [!"node:name(.)"!] */
    [!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!][!/*
      */!][!IF "$foundsignal = 'false'"!][!/*
        */!][!IF "number(node:ref(ComMPncComSignalRef)/ComHandleId) = $Handle"!][!/*
          */!][!IF "ComMPncComSignalKind = 'ERA'"!][!/*
            */!][!IF "(node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and ((node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType) = 'COMM_GATEWAY_TYPE_ACTIVE')"!][!/*
    */!][!WS "4"!]COMM_EIRA_ERA_ACTIVE[!/*
            */!][!ELSE!][!/*
    */!][!WS "4"!]COMM_ERA_PASSIVE[!/*
            */!][!ENDIF!][!/*
          */!][!ELSE!][!/*
    */!][!WS "4"!]COMM_EIRA_ERA_ACTIVE[!/*
          */!][!ENDIF!][!/*
          */!][!VAR "foundsignal" = "'true'"!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDIF!][!/*
    */!][!ENDLOOP!][!//
  [!ENDIF!][!//
  },
[!ENDLOOP!][!//
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
#endif /* (COMM_NUM_TX_SIGNALS > 0U) */
[!ENDIF!] [!/*[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]*/!]
[!ENDIF!] [!/*[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]*/!]

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true'"!][!//
CONST(ComM_ASR40_InhibitionStatusType, COMM_CONST)
  ComM_ChannelInhibitionStatusInit[COMM_NUM_BYTES_NVM] =
{
[!VAR "VarComMNoCom" = "0"!][!//
[!LOOP "util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))"!][!//
  [!IF "ComMNoCom = 'true'"!][!//
   [!VAR "VarComMNoCom" = "bit:or($VarComMNoCom,bit:shl(1,num:i(ComMChannelId mod 8)))"!][!//
  [!ENDIF!][!//
  [!IF "((ComMChannelId + 1) mod 8) = 0"!][!//
    [!"num:i($VarComMNoCom)"!]U,
    [!VAR "VarComMNoCom" = "0"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "((util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))[last()]/ComMChannelId + 1) mod 8) != 0"!]
  [!"num:i($VarComMNoCom)"!]U
[!ENDIF!][!//
};
[!ENDIF!][!//

[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMModeLimitationEnabled = 'true') or (as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!][!//
CONST(ComM_NvDataType, COMM_CONST) ComM_EB_NvROM =
{
  0U, /* InhibitionCounter */
  [!"num:i(as:modconf('ComM')[1]/ComMGeneral/ComMEcuGroupClassification)"!]U, /* ECUGroupClassification */
[!IF "(as:modconf('ComM')[1]/ComMGeneral/ComMWakeupInhibitionEnabled = 'true')"!][!//
  { /* ChannelWakeUpInhibition array */
[!VAR "VarComMNoWakeup" = "0"!][!//
[!LOOP "util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))"!][!//
  [!IF "ComMNoWakeup = 'true'"!][!//
    [!VAR "VarComMNoWakeup" = "bit:or($VarComMNoWakeup,bit:shl(1,num:i(ComMChannelId mod 8)))"!][!//
  [!ENDIF!][!//
  [!IF "((ComMChannelId + 1) mod 8) = 0"!][!//
    [!"num:i($VarComMNoWakeup)"!]U,
    [!VAR "VarComMNoWakeup" = "0"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "((util:distinct(node:order(ComMChannel/*, 'ComMChannelId'))[last()]/ComMChannelId + 1) mod 8) != 0"!]
  [!"num:i($VarComMNoWakeup)"!]U
[!ENDIF!][!//
  }
[!ENDIF!][!//
};
[!ENDIF!][!//


[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]

#if (COMM_NUM_TX_SIGNALS > 0U)
CONST(ComM_PncTxSigMapType, COMM_CONST) ComM_PncTxSignalMap[COMM_NUM_PNC] =
{
[!LOOP "util:distinct(node:order(ComMPnc/*, 'ComMPncId'))"!]
  /* [!"node:name(.)"!] */
  {
    [!IF "num:i(count(ComMPncComSignal/*[ComMPncComSignalDirection='TX']/ComMPncComSignalRef)) != 0"!][!//
    ComM_TxSig_Pnc_[!"ComMPncId"!],      /* TxSignalList */
    [!ELSE!][!//
    NULL_PTR,
    [!ENDIF!][!//
    COMM_NUM_TX_PNC_[!"ComMPncId"!]     /* NumTxSignal */
  },
[!ENDLOOP!]
};
#endif /* (COMM_NUM_TX_SIGNALS > 0U) */

[!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)))) > 0"!]
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST) ComM_PncRxEiraMask[COMM_NUM_RX_EIRA_SIGNALS] =
{
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA']
        [ComMPncComSignalDirection='RX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
  /* Com Signal: [!"node:name(.)"!] */
  ComM_PncRxEiraMask_[!"node:name(.)"!],
[!ENDLOOP!]
};
[!ENDIF!] [!/*[!IF "num:i(count(util:distinct(node:refs(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='EIRA'][ComMPncComSignalDirection='RX']/ComMPncComSignalRef)))) > 0"!]*/!]

[!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncGatewayEnabled = 'true'"!]
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST) ComM_PncRxActiveEraMask[COMM_NUM_RX_ACTIVE_ERA_SIGNALS] =
{
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='ERA']
        [ComMPncComSignalDirection='RX'][(node:exists(node:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType)) and (as:ref(ComMPncComSignalChannelRef)/ComMPncGatewayType='COMM_GATEWAY_TYPE_ACTIVE')]/ComMPncComSignalRef)), 'ComHandleId'))"!]
  /* Com Signal: [!"node:name(.)"!] */
  ComM_PncRxEraMask_[!"node:name(.)"!],
[!ENDLOOP!]
};

CONSTP2CONST(uint8, COMM_CONST, COMM_CONST) ComM_PncRxUnfilteredEraMask[COMM_NUM_RX_UNFILTERED_ERA_SIGNALS] =
{
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalKind='ERA']
        [ComMPncComSignalDirection='RX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
  /* Com Signal: [!"node:name(.)"!] */
  ComM_PncRxEraMask_[!"node:name(.)"!],
[!ENDLOOP!]
};
[!ENDIF!]

#if (COMM_NUM_TX_SIGNALS > 0U)
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST) ComM_PncTxMask[COMM_NUM_TX_SIGNALS] =
{
[!LOOP "util:distinct(node:order(util:distinct(node:refs(ComMPnc/*/ComMPncComSignal/*
        [ComMPncComSignalDirection='TX']/ComMPncComSignalRef)), 'ComHandleId'))"!]
  /* Com Signal: [!"node:name(.)"!] */
  ComM_PncTxMask_[!"node:name(.)"!],
[!ENDLOOP!]
};
#endif /* (COMM_NUM_TX_SIGNALS > 0U) */

[!ENDIF!]

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

[!ENDSELECT!][!//

[!/*
            */!]

/*==================[internal data]=========================================*/

#if(COMM_VLAN_SUPPORT)

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
CONST(ComM_VlanTableStructType, COMM_CONST) ComM_VlanConfigTable[COMM_VLAN_MANAGED_CH_NB] =
{
[!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*"!][!//
  [!IF "node:exists(node:current()/ComMManageReference/*[1])"!][!//
   {
    [!"num:i(node:current()/ComMChannelId)"!]U, /* ManagedChId */
    [!"num:i(util:distinct(node:refs(node:current()/ComMManageReference/*[1]))/ComMChannelId)"!]U /* ManagingChId */
   },
  [!ENDIF!][!//
[!ENDLOOP!][!//
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
#endif

[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and
      (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = 'true')"!]
#define COMM_START_SEC_CONST_8
#include <ComM_MemMap.h>
[!CALL "GetActiveChMixedWithPassive"!]
[!IF "$ActiveChMixedWithPassive"!]
[!VAR "ComMGatewayTypePassiveCount" = "num:i(0)"!]
CONST(uint8, COMM_CONST) ComM_SyncronizedShutdownPassiveChannelList[COMM_NUM_CHANNELS] =
{
[!LOOP "util:distinct(node:order(as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMChannel/*, 'ComMChannelId'))"!]
  [!IF "node:exists(ComMPncGatewayType) and (ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!]
  [!"$ComMGatewayTypePassiveCount"!],
      [!VAR "ComMGatewayTypePassiveCount" = "num:i($ComMGatewayTypePassiveCount + 1)"!]

  [!ELSE!] [!/* [!IF "node:exists(ComMPncGatewayType) and (ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!] */!]
  0xFF,
  [!ENDIF!]
[!ENDLOOP!] [!/* [!IF "node:exists(ComMPncGatewayType) and (ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE')"!] */!]
};
[!ENDIF!][!/* [!IF "$ActiveChMixedWithPassive"!] */!]

#define COMM_STOP_SEC_CONST_8
#include <ComM_MemMap.h>
[!ENDIF!] [!/*[!IF "node:exists(as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled) and
              (as:modconf('ComM')[1]/ComMGeneral/ComMSynchronizedPncShutdownEnabled = ''true'"!] */!]


/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
