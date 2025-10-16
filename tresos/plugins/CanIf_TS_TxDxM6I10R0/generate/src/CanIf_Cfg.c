/**
 * \file
 *
 * \brief AUTOSAR CanIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CanIf.
 *
 * \version 6.10.40
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 9.5 (Required)
 *    Where designated initializers are used to initialize an array object the
 *    size of the array shall be specified explicitly.
 *
 *    Reason:
 *    Array size and initialization are depending on configuration whereas the
 *    array declaration is used by configuration-independent library code.
 */

/*==================[inclusions]=============================================*/
[!INCLUDE "../../generate_macros/CanIf_PreCompileMacros.m"!]
[!INCLUDE "../../generate_macros/CanIf_Macros.m"!]

#define CANIF_NO_CFGCLASSMIX_REQUIRED
#ifndef CANIF_NO_PBCFG_REQUIRED
#define CANIF_NO_PBCFG_REQUIRED
#endif
#include <CanIf.h>                /* CanIf Types */
#include <CanIf_Int.h>
#include <CanIf_Int_Cfg.h>

[!IF "CanIfPublicCfg/CanIfMulticoreWakeupExtension = 'true'"!]
#include <SchM_CanIf.h>
[!ENDIF!]

[!IF "$canifMFSupport"!][!//
[!INCLUDE "../../generate_macros/CanIf_DecoupledProcessing.m"!][!//
  [!IF "$canifMulticoreEnabled = 'true'"!]
    [!VAR "PartitionsRefs" = "''"!]
        [!LOOP "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfTxProcessing/*"!]
      [!VAR "currentPartitionName" = "as:name(as:ref(CanIfPartitionRef))"!]
      [!VAR "currentPartition" = "as:path(as:ref(CanIfPartitionRef))"!]
      [!IF "$PartitionsRefs = ''"!]
        [!VAR "PartitionsRefs"!][!"$PartitionsRefs"!];[!"$currentPartitionName"!]:[!"$currentPartition"!][!ENDVAR!]
#include <SchM_CanIf_1_[!"$currentPartitionName"!].h>
      [!ELSE!]
        [!LOOP "text:order(text:split($PartitionsRefs, ';'))"!]
          [!VAR "txPartition" = "text:split(., ':')[2]"!]
          [!IF "$txPartition != $currentPartition"!]
            [!VAR "PartitionsRefs"!][!"$PartitionsRefs"!];[!"$currentPartitionName"!]:[!"$currentPartition"!][!ENDVAR!]
#include <SchM_CanIf_1_[!"$currentPartitionName"!].h>
          [!ENDIF!]
        [!ENDLOOP!]
      [!ENDIF!]
    [!ENDLOOP!]

    [!LOOP "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfRxProcessing/*"!]
      [!VAR "currentPartitionName" = "as:name(as:ref(CanIfPartitionRef))"!]
      [!VAR "currentPartition" = "as:path(as:ref(CanIfPartitionRef))"!]
      [!IF "$PartitionsRefs = ''"!]
        [!VAR "PartitionsRefs"!][!"$PartitionsRefs"!];[!"$currentPartitionName"!]:[!"$currentPartition"!][!ENDVAR!]
#include <SchM_CanIf_1_[!"$currentPartitionName"!].h>
      [!ELSE!]
        [!LOOP "text:order(text:split($PartitionsRefs, ';'))"!]
          [!VAR "partition" = "text:split(., ':')[2]"!]
          [!IF "$partition != $currentPartition"!]
            [!VAR "PartitionsRefs"!][!"$PartitionsRefs"!];[!"$currentPartitionName"!]:[!"$currentPartition"!][!ENDVAR!]
#include <SchM_CanIf_1_[!"$currentPartitionName"!].h>
          [!ENDIF!]
        [!ENDLOOP!]
      [!ENDIF!]
    [!ENDLOOP!]
  [!ELSE!]
#include <SchM_CanIf.h>
  [!ENDIF!]
[!ELSE!]
[!VAR "decoupledRxSupported" = "false()"!]
[!VAR "txDecoupledSupport" = "false()"!]
[!ENDIF!]

[!/* *** include CAN driver(s) header(s) *** */!][!//
[!IF "$canIfPublicMultipleDrvSupport = 'true'"!][!//
  [!FOR "i"="0" TO "$canDriverNum - 1"!][!//
    [!VAR "drvInfix"!][!CALL "CreateCanDriverInfixByIdx", "idx"="$i"!][!ENDVAR!][!//
#include <Can_[!"$drvInfix"!].h>              /* AUTOSAR Can driver with Id [!"text:split($drvInfix, '_')[1]"!], Infix [!"text:split($drvInfix, '_')[2]"!] */
  [!ENDFOR!][!//
[!ELSE!][!//
#include <Can.h>              /* AUTOSAR Can driver header file inclusion */
[!ENDIF!][!//

[!/* *** include transceiver drivers if necessary *** */!]
[!IF "$canTrcvSupport"!]
  [!IF "$useTransceiverInfix = 'true'"!]
    [!FOR "i"="0" TO "$trcvDriversNum - 1"!]
      [!VAR "trcvInfix"!][!CALL "CreateTrcvInfixByIdx", "idx"="$i"!][!ENDVAR!]
      [!IF "$trcvInfix = ''"!]
#include <CanTrcv.h>              /* AUTOSAR CanTrcv definitions */
      [!ELSE!]
#include <CanTrcv_[!"$trcvInfix"!].h>   /* AUTOSAR CanTrcv definitions */
      [!ENDIF!]
    [!ENDFOR!]
  [!ELSE!]
#include <CanTrcv.h>              /* AUTOSAR CanTrcv definitions */
  [!ENDIF!]
[!ENDIF!]

/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_CanIf.h */
#define PDUR_NO_PBCFG_REQUIRED

[!LOOP "text:split($ulCbFuncLUT)"!]
  [!VAR "tmpUpperLayerName"="text:split( ., ':' )[1]"!]
  [!IF "$tmpUpperLayerName = 'PDUR'"!]
#include <PduR_CanIf.h>            /* PduR callback function declarations */
  [!ENDIF!][!//
  [!IF "$tmpUpperLayerName = 'CAN_TP'"!]
#include <CanTp_Cbk.h>             /* CanTp callback function declarations */
  [!ENDIF!][!//
  [!IF "$tmpUpperLayerName = 'CAN_TSYN'"!]
#include <CanTSyn.h>               /* CanTSyn callback function declarations */
  [!ENDIF!][!//
  [!IF "$tmpUpperLayerName = 'CAN_NM'"!]
#include <CanNm_Cbk.h>             /* CanNm callback function declarations */
  [!ENDIF!][!//
  [!IF "$tmpUpperLayerName = 'J1939NM'"!]
#include <J1939Nm_Cbk.h>           /* J1939Nm callback function declarations */
  [!ENDIF!][!//
  [!IF "$tmpUpperLayerName = 'J1939TP'"!]
#include <J1939Tp_Cbk.h>           /* J1939Tp callback function declarations */
  [!ENDIF!][!//
[!ENDLOOP!]

[!LOOP "CanIfPublicCfg/CanIfPublicCddHeaderFile/*"!][!//
#include <[!"."!]>   /* CDD header file */
[!ENDLOOP!][!//

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[internal constants]=====================================*/

/*==================[external constants]=====================================*/
[!IF "CanIfPublicCfg/CanIfMulticoreWakeupExtension = 'true'"!]

[!IF "$canWakeupSupport = 'true'"!]
CONST(SchM_CanIf_CheckWakeupFctPtrType, CANIF_APPL_CONST) CanIf_CallSchM_CanControllerWakeup[[!"$controllerNum"!]] =
{
[!LOOP "as:modconf('CanIf')[1]/CanIfCtrlDrvCfg/*"!]
[!VAR "DrvCfgName" = "node:name(.)"!]
   [!LOOP "CanIfCtrlCfg/*"!]
     [!VAR "CtrlCfgName" ="node:name(.)"!]
      &SchM_Call_CanIf_RequiredCSEntry_CheckDriverWakeup_[!"$DrvCfgName"!]_[!"$CtrlCfgName"!],
   [!ENDLOOP!]
[!ENDLOOP!]
};
[!ENDIF!]

[!IF "$canTrcvSupport"!]
CONST(SchM_CanIf_CBWakeupByBusFctPtrType, CANIF_APPL_CONST) CanIf_CallSchM_CanTrcvWakeup[[!"$trcvChannelsNum"!]] =
{
[!LOOP "as:modconf('CanIf')[1]/CanIfTrcvDrvCfg/*"!]
[!VAR "TrcvDrvCfgName" = "node:name(.)"!]
   [!LOOP "CanIfTrcvCfg/*"!]
     [!VAR "TrcvCfgName" ="node:name(.)"!]
      &SchM_Call_CanIf_RequiredCSEntry_CheckTrcvWakeup_[!"$TrcvDrvCfgName"!]_[!"$TrcvCfgName"!],
   [!ENDLOOP!]
[!ENDLOOP!]
};
[!ENDIF!]

[!ENDIF!]


#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanIf_MemMap.h>

/** \brief Configuration of CAN driver(s) function pointers */
CONST( CanIf_CanDrvFctConfigType, CANIF_APPL_CONST )
  CanIf_CanDrvFctConfig[[!"$canDriverNum"!]] =
{
[!FOR "i"="0" TO "$canDriverNum - 1"!]
  [!IF "$canIfPublicMultipleDrvSupport = 'true'"!]
    [!VAR "CanDriverInfix"!][!CALL "CreateCanDriverInfixByIdx", "idx"="$i"!]_[!ENDVAR!]
  [!ELSE!]
    [!VAR "CanDriverInfix" = "''"!]
  [!ENDIF!]
  {
    &Can_[!"$CanDriverInfix"!]Write,
    &Can_[!"$CanDriverInfix"!]SetControllerMode,
  [!VAR "CanDriverWUSupport"!][!CALL "CanDriverWakeupSupport", "idx"="$i"!][!ENDVAR!]
  [!IF "$canWakeupSupport = 'true'"!]
  [!IF "$CanDriverWUSupport = 'true'"!]
    &Can_[!"$CanDriverInfix"!]CheckWakeup,
  [!ELSE!]
    NULL_PTR,
  [!ENDIF!]
  [!ENDIF!]
  [!IF "CanIfPublicCfg/CanIfSetBaudrateApi = 'true'"!]
    &Can_[!"$CanDriverInfix"!]SetBaudrate,
  [!ENDIF!]
  [!IF "$canIfBusMirrorSupport = 'true'"!]
    [!IF "$canIfCanGetCntrlStateSupported = 'true'"!]
    &Can_[!"$CanDriverInfix"!]GetControllerErrorState,
    [!ENDIF!]
    [!IF "$canIfCanTxErrCntSupported = 'true'"!]
    &Can_[!"$CanDriverInfix"!]GetControllerTxErrorCounter,
    [!ENDIF!]
  [!ENDIF!]
  [!IF "($canDriverCompatibility = 'ASR21_11') and ($canIfGlobalTimeSupport)"!]
    &Can_[!"$CanDriverInfix"!]GetCurrentTime,
    &Can_[!"$CanDriverInfix"!]EnableEgressTimeStamp,
    &Can_[!"$CanDriverInfix"!]GetEgressTimeStamp,
    &Can_[!"$CanDriverInfix"!]GetIngressTimeStamp,
  [!ENDIF!]
    [!VAR "HohOffset"!][!CALL "GetDriverHohOffset", "idx"="$i"!][!ENDVAR!]
    [!"$HohOffset"!]u,
  },
[!ENDFOR!]
};

/* !LINKSTO CanIf.EB.MultipleTrcv,1 */
[!IF "$canTrcvSupport"!]
/** \brief Configuration of CanTrcv function pointers */
CONST( CanIf_CanTrcvConfigType, CANIF_APPL_CONST )
  CanIf_CanTrcvConfig[[!"$trcvDriversNum"!]] =
{
[!FOR "i"="0" TO "$trcvDriversNum - 1"!]
  [!IF "$useTransceiverInfix = 'true'"!]
    [!VAR "trcvInfix"!][!CALL "CreateTrcvInfixByIdx", "idx"="$i"!]_[!ENDVAR!]
  [!ELSE!]
    [!VAR "trcvInfix" = "''"!]
  [!ENDIF!]
  {
    &CanTrcv_[!"$trcvInfix"!]SetOpMode,
    &CanTrcv_[!"$trcvInfix"!]GetOpMode,
[!IF "$canTrcvWakeupSupport = 'true'"!]
    &CanTrcv_[!"$trcvInfix"!]GetBusWuReason,
    &CanTrcv_[!"$trcvInfix"!]SetWakeupMode,
  [!SELECT "CanIfTrcvDrvCfg/*[position() = ($i+1)]"!]
  [!IF "count(CanIfTrcvCfg/*[CanIfTrcvWakeupSupport = 'true']) > 0"!]
    &CanTrcv_[!"$trcvInfix"!]CheckWakeup,
  [!ELSE!]
    NULL_PTR,
  [!ENDIF!]
  [!ENDSELECT!]
[!ENDIF!]
[!IF "$canifPNSupport"!]
  [!VAR "CanTrcvPnSupport"!][!CALL "GetPnSupportByIdx", "idx"="$i"!][!ENDVAR!]
  [!IF "$CanTrcvPnSupport = 'true'"!]
    &CanTrcv_[!"$trcvInfix"!]ClearTrcvWufFlag,
    &CanTrcv_[!"$trcvInfix"!]CheckWakeFlag
  [!ELSE!]
    &CanIf_ClearTrcvWufFlag_HlpNoPn,
    &CanIf_CheckWakeFlag_HlpNoPn
  [!ENDIF!]
[!ENDIF!]
  },
[!ENDFOR!]
};
[!ENDIF!]


[!IF "($ulRxIndicationSupport = 'true') or ($cddRxIndicationSupport = 'true') or ($ulTxConfirmationSupport = 'true') or ($dlcErrorNotifSupport = 'true') or ($dlcPassedNotifSupport = 'true')"!]
/** \brief Configuration of upper layer callback function pointers */
/* Deviation MISRAC2012-1 <START> */
CONST( CanIf_CbkFctPtrTblType, CANIF_APPL_CONST ) CanIf_CbkFctPtrTbl[] =
{
  [!LOOP "text:split($ulCbFuncLUT)"!]
  {
    [!VAR "tmpUpperLayerName"="text:split( ., ':' )[1]"!]
     /* [!"$tmpUpperLayerName"!] */
    [!VAR "tmpRxIndication"="text:split( ., ':' )[3]"!]
    [!VAR "tmpCddRxIndication"="text:split( ., ':' )[4]"!]
    [!VAR "tmpTxConfirmation"="text:split( ., ':' )[5]"!]
    [!VAR "tmpTxConfirmationWithResult"="text:split( ., ':' )[6]"!]
    [!VAR "tmpDlcFailedNofif"="text:split( ., ':' )[7]"!]
    [!VAR "tmpDlcPassedNofif"="text:split( ., ':' )[8]"!]
[!IF "$ulRxIndicationSupport = 'true'"!]
    [!"$tmpRxIndication"!],
[!ENDIF!]
[!IF "$cddRxIndicationSupport = 'true'"!]
    [!"$tmpCddRxIndication"!],
[!ENDIF!]
[!IF "$ulTxConfirmationSupport = 'true'"!]
    [!"$tmpTxConfirmation"!],
[!IF "$ulTxConfirmationResutSupported = 'true'"!]
    [!"$tmpTxConfirmationWithResult"!],
[!ENDIF!]
[!ENDIF!]
[!IF "$dlcErrorNotifSupport = 'true'"!]
    [!"$tmpDlcFailedNofif"!],
[!ENDIF!]
[!IF "$dlcPassedNotifSupport = 'true'"!]
    [!"$tmpDlcPassedNofif"!],
[!ENDIF!]
  },
  [!ENDLOOP!]
};
/* Deviation MISRAC2012-1 <STOP> */
[!ENDIF!]


[!IF "$txDecoupledSupport = 'true'"!]
/** \brief Configuration of Tx decoupled processing */
/* Deviation MISRAC2012-1 <START> */
CONST( CanIf_MfTxPtrTblType, CANIF_APPL_CONST ) CanIf_MfTxFctPtrTbl[] =
{
  [!VAR "txOffset" = "num:i(0)"!]
  [!LOOP "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfTxProcessing/*"!]
  {
   [!IF "$canifMulticoreEnabled = 'true'"!]
    &SchM_ActMainFunction_CanIf_1_[!"node:name(as:ref(CanIfPartitionRef))"!]_Tx_[!"node:name(.)"!],
   [!ELSE!]
    &SchM_ActMainFunction_CanIf_Tx_[!"node:name(.)"!],
   [!ENDIF!]
    [!"$txOffset"!]U,
    [!"num:i(CanIfTxPduQueueSize)"!]U
    [!VAR "txOffset" = "num:i($txOffset + CanIfTxPduQueueSize)"!]
  },
  [!ENDLOOP!]
};
/* Deviation MISRAC2012-1 <STOP> */
[!ENDIF!]


[!IF "$decoupledRxSupported = 'true'"!]
/** \brief Configuration of Rx decoupled processing */
/* Deviation MISRAC2012-1 <START> */
CONST( CanIf_MfRxPtrTblType, CANIF_APPL_CONST ) CanIf_MfRxFctPtrTbl[] =
{
  [!VAR "rxOffset" = "num:i(0)"!]
  [!VAR "rxPayloadOffset" = "num:i(0)"!]
  [!LOOP "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfRxProcessing/*"!]
  {
    [!IF "$canifMulticoreEnabled = 'true'"!]
    &SchM_ActMainFunction_CanIf_1_[!"node:name(as:ref(CanIfPartitionRef))"!]_Rx_[!"node:name(.)"!],
    [!ELSE!]
    &SchM_ActMainFunction_CanIf_Rx_[!"node:name(.)"!],
    [!ENDIF!]
    [!"num:i(CanIfPublicMaxPayloadQueueSize)"!]U,
    [!"$rxPayloadOffset"!]U,
    [!"$rxOffset"!]U,
    [!"num:i(CanIfRxPduQueueSize)"!]U
    [!VAR "rxOffset" = "num:i($rxOffset + CanIfRxPduQueueSize)"!]
    [!VAR "rxPayloadOffset" = "num:i($rxPayloadOffset + CanIfPublicMaxPayloadQueueSize)"!]
  },
  [!ENDLOOP!]
};
/* Deviation MISRAC2012-1 <STOP> */
[!ENDIF!]

[!IF "$canIfBusMirrorSupport = 'true' and $canifMulticoreEnabled = 'true'"!]
/** \brief Configuration of Tx mirroring buffers per controller */
CONST(CanIf_CtrlMirrorBuffType, CANIF_APPL_CONST) CanIf_TxMirrBuffPtr[[!"num:i(count(as:modconf('CanIf')[1]/CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*))"!]U] =
{
[!LOOP "node:order(as:modconf('CanIf')[1]/CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*, 'CanIfCtrlId')"!]
  [!VAR "ctrlPartRef" = "''"!]
  [!IF "node:exists(node:ref(CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef)"!]
  [!VAR "ctrlPartRef" = "node:ref(CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef"!]
  [!ENDIF!]
  {
  &CanIf_MirrorBuffPayload[!IF "$ctrlPartRef != ''"!]_[!"as:modconf('CanIf')[1]/CanIfMirroringSupport/CanIfTxMirrorBuffers/CanIfTxMirrorBufferSize/*[CanIfTxBufPartRef = $ctrlPartRef]/@index"!][!ENDIF!][0U],
  &CanIf_MirrorBuff[!IF "$ctrlPartRef != ''"!]_[!"as:modconf('CanIf')[1]/CanIfMirroringSupport/CanIfTxMirrorBuffers/CanIfTxMirrorBufferSize/*[CanIfTxBufPartRef = $ctrlPartRef]/@index"!][!ENDIF!][0U],
  &CanIf_MirrNextFreeIdx[!IF "$ctrlPartRef != ''"!]_[!"as:modconf('CanIf')[1]/CanIfMirroringSupport/CanIfTxMirrorBuffers/CanIfTxMirrorBufferSize/*[CanIfTxBufPartRef = $ctrlPartRef]/@index"!][!ENDIF!],
  [!IF "$ctrlPartRef != ''"!]
  [!"num:i(ceiling(as:modconf('CanIf')[1]/CanIfMirroringSupport/CanIfTxMirrorBuffers/CanIfTxMirrorBufferSize/*[CanIfTxBufPartRef = $ctrlPartRef]/CanIfTxMirrorBufferSizePart div 8))"!]U,
  [!ELSE!]
  [!"$canIfTxMirrorSize"!]U,
  [!ENDIF!]
  },
[!ENDLOOP!]
};
[!ENDIF!]


#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanIf_MemMap.h>

/*==================[external data]==========================================*/

[!SELECT "as:modconf('CanIf')[1]/CanIfPublicCfg"!]

#define CANIF_START_SEC_VAR_CLEARED_8
#include <CanIf_MemMap.h>

#if( ( CANIF_WAKEUP_VALIDATION_API == STD_ON ) || \
     ( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON )  || \
     ( CANIF_PUBLIC_PN_SUPPORT == STD_ON) || \
     ( CANIF_BUS_MIRRORING_SUPPORT == STD_ON ) )

/** \brief Controller flags
 **
 ** This array contains the wakeup flags of all configured
 ** controllers. If a bit/flag has the value 1 it is set.
 ** Bit masks are:
 ** CANIF_WAKEUP_MASK             Wakeup flag
 ** CANIF_WAKEUP_VALIDATION_MASK  Wakeup validation flag
 ** CANIF_TX_CONFIRMATION_MASK    Tx confirmation flag
 ** CANIF_PN_FILTER_ACTIVE_MASK   Partial networking filter flag
 ** CANIF_BUS_MIRRORING_MASK      Mirroring flag
 */
VAR( uint8, CANIF_VAR )
  CanIf_CanControllerFlags[[!"CanIfPublicMaxCtrl"!]U];

#endif /* ( CANIF_WAKEUP_VALIDATION_API == STD_ON ) || \
          ( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON )  || \
          ( CANIF_PUBLIC_PN_SUPPORT == STD_ON) || \
          ( CANIF_BUS_MIRRORING_SUPPORT == STD_ON ) ) */

[!IF "CanIfMultiCoreSupport = 'true'"!]
  [!IF "CanIfPublicReadTxPduNotifyStatusApi = 'true' or CanIfPublicReadRxPduNotifyStatusApi = 'true'"!]
    [!LOOP "node:order(as:modconf('CanIf')[1]/CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*, 'CanIfCtrlId')"!]
      [!IF "../../../../CanIfPublicCfg/CanIfPublicReadTxPduNotifyStatusApi = 'true'"!]

/** \brief Bit-array of Tx notification flags (if enabled) */
STATIC VAR( uint8, CANIF_VAR )
  CanIf_TxLPduNotifyFlags_[!"num:i(CanIfCtrlId)"!][([!IF "node:exists(CanIfCtrlMaxTxNotifyPdus)"!][!"num:i(CanIfCtrlMaxTxNotifyPdus)"!][!ELSE!]1[!ENDIF!]U+7U)/8U];
      [!ENDIF!]

        [!IF "../../../../CanIfPublicCfg/CanIfPublicReadRxPduNotifyStatusApi = 'true'"!]
/** \brief Bit-array of Rx notification flags (if enabled) */
STATIC VAR( uint8, CANIF_VAR )
  CanIf_RxLPduNotifyFlags_[!"num:i(CanIfCtrlId)"!][([!IF "node:exists(CanIfCtrlMaxRxNotifyPdus)"!][!"num:i(CanIfCtrlMaxRxNotifyPdus)"!][!ELSE!]1[!ENDIF!]U+7U)/8U];
        [!ENDIF!]
    [!ENDLOOP!]

#define CANIF_STOP_SEC_VAR_CLEARED_8
#include <CanIf_MemMap.h>

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanIf_MemMap.h>
    [!IF "CanIfPublicReadTxPduNotifyStatusApi = 'true'"!]
CONST(CanIf_TxLPduNotifyFlagType, CANIF_APPL_CONST) CanIf_ControllerTxLPduNotifyFlag[CANIF_CTRL_SIZE] =
{
      [!LOOP "node:order(as:modconf('CanIf')[1]/CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*, 'CanIfCtrlId')"!]
  {
    &CanIf_TxLPduNotifyFlags_[!"num:i(CanIfCtrlId)"!][0U]
  },
      [!ENDLOOP!]
};
    [!ENDIF!]

    [!IF "CanIfPublicReadRxPduNotifyStatusApi = 'true'"!]
CONST(CanIf_RxLPduNotifyFlagType, CANIF_APPL_CONST) CanIf_ControllerRxLPduNotifyFlag[CANIF_CTRL_SIZE] =
{
      [!LOOP "node:order(as:modconf('CanIf')[1]/CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*, 'CanIfCtrlId')"!]
  {
    &CanIf_RxLPduNotifyFlags_[!"num:i(CanIfCtrlId)"!][0U]
  },
      [!ENDLOOP!]
};
    [!ENDIF!]
#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanIf_MemMap.h>

#define CANIF_START_SEC_VAR_CLEARED_8
#include <CanIf_MemMap.h>
  [!ENDIF!]
[!ELSE!]
  [!IF "CanIfPublicReadTxPduNotifyStatusApi = 'true'"!]
/** \brief Bit-array of Tx notification flags (if enabled) */
VAR( uint8, CANIF_VAR )
  CanIf_TxLPduNotifyFlags[([!IF "node:exists(CanIfPublicMaxTxNotifyPdus)"!][!"CanIfPublicMaxTxNotifyPdus"!][!ELSE!]1[!ENDIF!]U+7U)/8U];
  [!ENDIF!]

  [!IF "CanIfPublicReadRxPduNotifyStatusApi = 'true'"!]
/** \brief Bit-array of Rx notification flags (if enabled) */
VAR( uint8, CANIF_VAR )
  CanIf_RxLPduNotifyFlags[([!IF "node:exists(CanIfPublicMaxRxNotifyPdus)"!][!"CanIfPublicMaxRxNotifyPdus"!][!ELSE!]1[!ENDIF!]U+7U)/8U];
  [!ENDIF!]

[!ENDIF!]

[!IF "CanIfPublicReadRxPduDataApi = 'true'"!]
/** \brief Array of Rx buffers */
VAR( uint8, CANIF_VAR ) CanIf_RxBuffer[[!IF "node:exists(CanIfPublicMaxRxBuffer)"!][!"CanIfPublicMaxRxBuffer"!][!ELSE!]1[!ENDIF!]U];
[!ENDIF!]

[!IF "CanIfPublicTxBuffering = 'true'"!]
/** \brief Tx buffer memory */
VAR( uint8, CANIF_VAR ) CanIf_TxBufferMemory[[!IF "node:exists(CanIfPublicMaxTxBufferSize)"!][!"CanIfPublicMaxTxBufferSize"!][!ELSE!]1[!ENDIF!]U];
[!ENDIF!]

[!IF "$decoupledRxSupported = 'true'"!]
/** \brief Array of Rx queued data */
VAR( uint8, CANIF_VAR )
  CanIf_RxDataQueue[[!"num:i($canifMaxPayloadQueueSize)"!]U];
[!ENDIF!]

[!IF "$canIfBusMirrorSupport = 'true'"!]
[!IF "(CanIfMultiCoreSupport = 'false') or ((CanIfMultiCoreSupport = 'true') and (count(../CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*) > count(node:refs(../CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*/CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef)))"!]
/** \brief Temporary buffer for mirroring (payload)
 **
 ** This is used to temporarily store the payload
 ** of the PDUs that are not assigned to a partition
 */
VAR( uint8, CANIF_VAR )
  CanIf_MirrorBuffPayload[[!"$canIfTxMirrorBufSize"!]U];
[!ENDIF!]

[!IF "$canifMulticoreEnabled = 'true'"!]
/** \brief Temporary buffer for mirroring (payload)
 **
 ** This is used to temporarily store the payload
 ** of the PDUs that are assigned to a partition
 */
[!LOOP "../CanIfMirroringSupport/CanIfTxMirrorBuffers/CanIfTxMirrorBufferSize/*"!]
VAR( uint8, CANIF_VAR )
  CanIf_MirrorBuffPayload_[!"@index"!][[!"num:i(ceiling(CanIfTxMirrorBufferSizePart div 8) * 8)"!]U];
[!ENDLOOP!]
[!ENDIF!]

[!ENDIF!]

[!IF "($ulTxConfirmationSupport = 'true') and ($ulTxConfirmationResutSupported = 'true')"!]
/** \brief Array for marking Tx pdus in expectation of confirmation
 **
 ** This is used to temporarily mark the Tx pdus that have yet to receive
 ** a TxConfirmation. Each bit represents a Tx pdu (where pduID = bitPosition+8*arrayIndex).
 */
VAR( uint8, CANIF_VAR )
  CanIf_TxPduNoConf[[!"num:i(($canIfMaxTxPdus div 8)+1)"!]U];
[!ENDIF!]

#define CANIF_STOP_SEC_VAR_CLEARED_8
#include <CanIf_MemMap.h>

#define CANIF_START_SEC_VAR_CLEARED_16
#include <CanIf_MemMap.h>

[!IF "$decoupledRxSupported"!]
/** \brief Array of Rx queue Indexes
 **
 ** This is total number of bytes stored in the payload queue of a Main Function during
 ** message reception if Rx processing is enabled.
 */
VAR( uint16, CANIF_VAR )
  CanIf_MFRxQueueLoad[[!"$numRxMFs"!]U];
[!ENDIF!]

[!IF "$publicTxBufferingSupport = 'true'"!]
/** \brief Array of a HTH's number of pending Tx requests */
VAR( CanIf_TxBufferIndexType, CANIF_VAR )
  CanIf_NrOfPendingTxRequests[[!IF "node:exists(CanIfPublicMaxHths)"!][!"CanIfPublicMaxHths"!][!ELSE!]1[!ENDIF!]U];

/** \brief Pending transmit request buffers
 **
 ** This array stores pending transmit request IDs. It is named as array (8)
 ** in the CAN interface design.
 */
VAR( CanIf_LPduIndexType, CANIF_VAR )
  CanIf_PendingTxBuffers[[!IF "node:exists(CanIfPublicMaxTxBuffers)"!][!"CanIfPublicMaxTxBuffers"!][!ELSE!]1[!ENDIF!]U];
[!ENDIF!]

[!IF "$decoupledRxSupported = 'true'"!]
/** \brief Total size of the queue
 **
 ** This variable shows the current value of the queue of the CAN interface.
 */
VAR( uint16, CANIF_VAR ) CanIf_TotalRxQueueSize[[!"$numRxMFs"!]U];
[!ENDIF!]

[!IF "$canifRxDecMeasureSupport = 'true'"!]
/** \brief Number of Rx Pdus exceeding the queue
 **
 ** This variable shows the current value of the queue of the CAN interface.
 */
VAR( uint16, CANIF_VAR ) CanIf_NoOfRxPdusExceedingQueue[[!"$numRxMFs"!]U];
[!ENDIF!]

[!IF "$txDecoupledSupport = 'true'"!]
/** \brief Total size of the queue
 **
 ** This variable shows the current value of the queue of the CAN interface.
 */
volatile VAR( uint16, CANIF_VAR ) CanIf_TotalTxQueueSize[[!"$numTxMFs"!]U];
[!ENDIF!]

[!IF "$canifTxDecMeasureSupport = 'true' and $ulTxConfirmationSupport = 'true'"!]
/** \brief Number of Tx Pdus exceeding the queue
 **
 ** This variable shows the current value of the queue of the CAN interface.
 */
volatile VAR( uint16, CANIF_VAR ) CanIf_NoOfTxPdusExceedingQueue[[!"$numTxMFs"!]U];
[!ENDIF!]

#define CANIF_STOP_SEC_VAR_CLEARED_16
#include <CanIf_MemMap.h>

#define CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanIf_MemMap.h>

VAR( CanIf_ControllerModeType, CANIF_VAR )
  CanIf_CanControllerMode[[!"CanIfPublicMaxCtrl"!]U];

VAR( CanIf_PduModeType, CANIF_VAR )
  CanIf_PduMode[[!"CanIfPublicMaxCtrl"!]U];

[!IF "$canifSetDynTxIdSupported='true' or $CanIfMetaDataSupport='true' "!]
/** \brief Array for dynamic CAN IDs
 **
 ** This array contains the current set CAN ID for dynamic Tx L-PDUs.
 */
 VAR( Can_IdType, CANIF_VAR )
  CanIf_DynamicTxLPduCanIds[[!IF "node:exists(CanIfPublicMaxDynTxPdus)"!][!"CanIfPublicMaxDynTxPdus"!][!ELSE!]1[!ENDIF!]U];
[!ENDIF!]

[!IF "$publicTxBufferingSupport"!]
/** \brief Array of Tx buffers
 **
 ** This is the array of Tx buffers used during message transmission if Tx
 ** buffering is enabled.
 */
VAR( CanIf_TxBufferType, CANIF_VAR )
  CanIf_TxBuffer[[!IF "node:exists(CanIfPublicMaxTxBuffers)"!][!"CanIfPublicMaxTxBuffers"!][!ELSE!]1[!ENDIF!]U];
[!ENDIF!]

[!IF "$txDecoupledSupport"!]
/** \brief Array of Tx queue
 **
 ** This is the array of Tx queue used during message transmission confirmation
 ** if Tx processing is enabled.
 */
VAR( CanIf_TxQueueType, CANIF_VAR )
  CanIf_TxPduQueue[[!"$canifTxPduQueueSize"!]U];

/** \brief Array of Tx decoupled main function transmission read/write indexes
 **
 ** This is the array of Tx queue read/write indexes used during message transmission
 ** confirmation and MF processing if Tx processing is enabled.
 */
VAR( CanIf_MfTxTblRWIdxType, CANIF_VAR )
  CanIf_MfTxTblRWIdx[[!"$numTxMFs"!]U];
[!ENDIF!]

[!IF "$decoupledRxSupported"!]
/** \brief Array of Rx queue
 **
 ** This is the array of Rx queue used during message reception
 ** if Rx processing is enabled.
 */
VAR( CanIf_RxQueueType, CANIF_VAR )
  CanIf_RxPduQueue[[!"$canifRxPduQueueSize"!]U];

/** \brief Array of Rx decoupled main function reception read/write indexes
 **
 ** This is the array of Rx queue read/write indexes used during message reception
 ** indication and MF processing if Rx processing is enabled.
 */
VAR( CanIf_MfRxTblRWIdxType, CANIF_VAR )
  CanIf_MfRxTblRWIdx[[!"$numRxMFs"!]U];
[!ENDIF!]

[!IF "$canIfBusMirrorSupport = 'true'"!]
[!IF "(CanIfMultiCoreSupport = 'false') or ((CanIfMultiCoreSupport = 'true') and (count(../CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*) > count(node:refs(../CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*/CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef)))"!]
/** \brief Temporary buffer for mirroring
 **
 ** This is used to temporarily store the PDUs that are not assigned to a partition
 ** and the next free index in that buffer.
 */
VAR( CanIf_MirrorBuffType, CANIF_VAR )
  CanIf_MirrorBuff[[!"$canIfTxMirrorSize"!]U];
VAR( PduIndexType, CANIF_VAR )
  CanIf_MirrNextFreeIdx;
[!ENDIF!]

[!IF "CanIfMultiCoreSupport = 'true'"!]
/** \brief Temporary buffer for mirroring
 **
 ** This is used to temporarily store the PDUs that are assigned to a partition
 ** and the next free index in that buffer.
 */
[!LOOP "../CanIfMirroringSupport/CanIfTxMirrorBuffers/CanIfTxMirrorBufferSize/*"!]
VAR( CanIf_MirrorBuffType, CANIF_VAR )
  CanIf_MirrorBuff_[!"@index"!][[!"num:i(ceiling(CanIfTxMirrorBufferSizePart div 8))"!]U];
VAR( PduIndexType, CANIF_VAR )
  CanIf_MirrNextFreeIdx_[!"@index"!];
[!ENDLOOP!]
[!ENDIF!]

[!ENDIF!]

#define CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanIf_MemMap.h>

[!ENDSELECT!]

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

[!IF "CanIfPublicCfg/CanIfMulticoreWakeupExtension = 'true'"!]
#define CANIF_START_SEC_CODE
#include <CanIf_MemMap.h>

/** \brief Dummy Schedulable used by SchM to handle SchM calls. */
FUNC( void, CANIF_CODE ) CanIf_DummyMF (void)
{

}

#define CANIF_STOP_SEC_CODE
#include <CanIf_MemMap.h>
[!ENDIF!]

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
[!ENDCODE!][!//
