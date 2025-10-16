/**
 * \file
 *
 * \brief AUTOSAR CanNm
 *
 * This file contains the implementation of the AUTOSAR
 * module CanNm.
 *
 * \version 6.20.6
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*===============================[includes]=================================*/
[!INCLUDE "../../generate_macros/CanNm_Checks.m"!][!//
[!INCLUDE "../../generate_macros/CanNm_Macros.m"!][!//
[!CALL "GetMulticorePerChannelSupport"!][!//

#define CANNM_NO_CFGCLASSMIX_REQUIRED
#ifndef CANNM_NO_PBCFG_REQUIRED
#define CANNM_NO_PBCFG_REQUIRED
#endif

#include <CanNm_Int.h>          /* CanNm internal interface */
#include <CanNm_Hsm.h>          /* public API of CanNm_Hsm.c */
#include <CanNm_HsmCanNm.h>
[!IF "$MulticorePerChannelSupport = 'true'"!][!//
#include <SchM_CanNm.h>
[!SELECT "as:modconf('Os')[1]/OsApplication/eb-list::*/OsAppEcucPartitionRef"!][!//
[!VAR "Partition" = "node:value(.)"!][!//
[!VAR "Application" = "node:name(..)"!][!//
[!IF "node:exists(as:modconf('ComM')[1]/ComMConfigSet/eb-list::*[1]/ComMChannel/eb-list::*[($Partition = node:value(ComMChannelPartitionRef)) and (ComMBusType = 'COMM_BUS_TYPE_CAN') and ((ComMNetworkManagement/ComMNmVariant = 'FULL') or (ComMNetworkManagement/ComMNmVariant = 'PASSIVE'))])"!][!//
#include <SchM_CanNm_1_ChOsApp_[!"$Application"!].h>
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDIF!][!//

[!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMultiCoreSupport)"!][!//
#include <SchM_CanNm.h>
[!ENDIF!][!//

/*===========================[macro definitions]============================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*=====================[external constants]=================================*/

/*=====================[internal constants]=================================*/

/*=======================[external data]====================================*/

/*=======================[internal data]====================================*/

/*=====================[external functions definitions]=====================*/

[!IF "$MulticorePerChannelSupport = 'true'"!][!//
/* !LINKSTO CanNm.EB.CanNm_MainFunction_Main.Enable,1 */
/* !LINKSTO CanNm.EB.CanNm_MainFunction_X.Enable,1 */
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)

[!IF "node:refvalid(as:modconf('ComM')[1]/ComMGeneral/ComMMasterPNCEcuCPartitionRef)"!][!//
#define CANNM_START_SEC_CODE
#include <CanNm_MemMap.h>

/* !LINKSTO CanNm.EB.CanNm_MainFunction_Main,1 */
FUNC(void, CANNM_CODE) CanNm_MainFunction_Main(void)
{
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
  if (TRUE == CanNm_Initialized)
  {
    CanNm_HandlePnInfo(&CanNm_EiraStatus, CANNM_PN_EIRA_PDUID, CANNM_MAIN_PARTITION_HANDLE);
    CanNm_HandlePnTimers(&CanNm_EiraStatus, CANNM_PN_EIRA_PDUID);
  }
#endif
}

#define CANNM_STOP_SEC_CODE
#include <CanNm_MemMap.h>
[!ENDIF!][!//

/* same order as in CanNm_ChanConfig variable*/
[!SELECT "util:distinct(node:order(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*,'CanNmRxPdu/eb-list::*[1]/CanNmRxPduId'))"!][!//
[!VAR "Channel_Idx" = "CanNmRxPdu/eb-list::*[1]/CanNmRxPduId"!][!//
[!VAR "Application" = "node:name(as:modconf('Os')[1]/OsApplication/eb-list::*[node:exists(OsAppEcucPartitionRef) and (node:value(OsAppEcucPartitionRef) = node:value(node:ref(node:current()/CanNmComMNetworkHandleRef)/ComMChannelPartitionRef))][1])"!][!//
#define CANNM_1_ChOsApp_[!"$Application"!]_START_SEC_CODE
#include <CanNm_1_ChOsApp_[!"$Application"!]_MemMap.h>
/* !LINKSTO CanNm.EB.CanNm_MainFunction_X,1 */
/* !LINKSTO CanNm.EB.CanNm_MainFunction_X.Name,1 */
FUNC(void, CANNM_CODE) CanNm_1_ChOsApp_[!"$Application"!]_MainFunction_[!"$Channel_Idx"!](void)
{
  if (TRUE == CanNm_Initialized)
  {
#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
    CanNm_HandlePNSyncShutdown(CANNM_PL_SF([!"$Channel_Idx"!]));
#endif
#endif

    CANNM_CHANNEL_STATUS([!"$Channel_Idx"!]).MessageFlags &= (uint8)(~(uint8)(CANNM_MESSAGE_SENT_ON_CYCLE));
    CanNm_HandleTimerTick(CANNM_PL_SF([!"$Channel_Idx"!]));

    (void) CANNM_HSMMAININST(&CanNm_HsmScCanNm, [!"$Channel_Idx"!]);

#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
    if(CANNM_CHANNEL_CONFIG([!"$Channel_Idx"!]).EraCalcEnabled == STD_ON)
    {
      CanNm_HandlePnInfo(&CANNM_CHANNEL_STATUS([!"$Channel_Idx"!]).Era, CANNM_CHANNEL_CONFIG([!"$Channel_Idx"!]).EraPduId, [!"$Channel_Idx"!]);
      CanNm_HandlePnTimers(&CANNM_CHANNEL_STATUS([!"$Channel_Idx"!]).Era, CANNM_CHANNEL_CONFIG([!"$Channel_Idx"!]).EraPduId);
    }
#endif
  }
}
#define CANNM_1_ChOsApp_[!"$Application"!]_STOP_SEC_CODE
#include <CanNm_1_ChOsApp_[!"$Application"!]_MemMap.h>

[!IF "node:refvalid(as:modconf('ComM')[1]/ComMGeneral/ComMMasterPNCEcuCPartitionRef)"!][!//
#define CANNM_START_SEC_CODE
#include <CanNm_MemMap.h>
/* !LINKSTO CanNm.EB.CanNmChannelMultiCore.Receiver,1 */
FUNC(void, CANNM_CODE) CanNm_Main_RecieveFunction_[!"$Channel_Idx"!](void)
{
[!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmPnEiraCalcEnabled)"!][!//
  if (TRUE == CanNm_Initialized)
  {
    while(SCHM_E_OK == SchM_Receive_CanNm_Main_DataGet_[!"$Channel_Idx"!](&CANNM_CHANNEL_STATUS([!"$Channel_Idx"!]).Era.PnTempInfo[0]))
    {
      SchM_Enter_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_MAIN();

      /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.Receiver.Aggregate,1 */
      CanNm_AggregatePnInfo(&CANNM_CHANNEL_STATUS([!"$Channel_Idx"!]).Era.PnTempInfo[0], &CanNm_EiraStatus);

      SchM_Exit_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_MAIN();
    }
  }
[!ENDIF!][!//
}
#define CANNM_STOP_SEC_CODE
#include <CanNm_MemMap.h>
[!ENDIF!][!//
[!ENDSELECT!][!//
#endif /* CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON */
[!ENDIF!][!//


[!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMultiCoreSupport)"!][!//

#define CANNM_START_SEC_CODE
#include <CanNm_MemMap.h>

#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
FUNC(void, CANNM_CODE) CanNm_RequestSynchronizedPncShutdown_Nm_To_CanNm_RcvFnct (void)
{
  Nm_PnSyncShutdown_Nm_To_BusNm_DataType data;

  while (SchM_Receive_CanNm_CanNm_RequestSynchronizedPncShutdown_Nm_To_CanNm_DataGet(&data) == SCHM_E_OK)
  {
    /* !LINKSTO CanNm.EB.PnSyncShutdown.CanNm_RequestSynchronizedPncShutdown.Multicore,1 */
    (void) CanNm_RequestSynchronizedPncShutdown(data.Channel, data.PncId);
  }
}
#endif
#endif

#define CANNM_STOP_SEC_CODE
#include <CanNm_MemMap.h>

[!ENDIF!][!//

/*=====================[external Non API function definitions]==============*/

/*=====================[internal functions definitions]=====================*/

/*==============================[end of file]===============================*/
