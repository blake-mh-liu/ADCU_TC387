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


/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
 *
 * Reason:
 * The macro is used in function parameter declarations and definitions of structure member where
 * the number of parentheses matter.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * In case define CANNM_PN_SUPPORTED == STD_ON and defines
 * CANNM_PN_EIRA_CALC_ENABLED == STD_OFF and
 * CANNM_PN_ERA_CALC_ENABLED == STD_OFF
 * variable ValidPnMessage is initialized to FALSE but it's value is never modified.
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The warning "condition is always true" is a tasking compiler issue (TCVX-41885).
 * If the condition were always true then an infinite loop would occur.
 */

/*===============================[includes]=================================*/
#define CANNM_NO_CFGCLASSMIX_REQUIRED
#ifndef CANNM_NO_PBCFG_REQUIRED
#define CANNM_NO_PBCFG_REQUIRED
#endif

#include <CanNm_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <TSMem.h>

/* !LINKSTO CanNm.ASR403.CANNM306,1 */
#include <CanNm_Api.h>          /* CanNm API definitions (own interface) */
#include <CanNm_Int.h>          /* CanNm internal interface */
#include <CanNm_Cbk.h>          /* CanNm callback API (own interface) */
#include <CanNm_Hsm.h>          /* public API of CanNm_Hsm.c */
#include <CanNm_HsmCanNm.h>     /* public statechart model definitions, */
#include <CanNm_Lcfg.h>
#include <CanNm_Lcfg_Static.h>

/* !LINKSTO CanNm.ASR403.CANNM307,1 */
#include <Nm_Cbk.h>             /* Nm API for Nm_StateChangeNotification() */
/* !LINKSTO CanNm.ASR403.CANNM310,1 */
#include <SchM_CanNm.h>         /* SchM-header for CanNm */
/* !LINKSTO CanNm.SWS_CanNm_00312,1 */
#include <CanIf.h>              /* CanIf API, CanIf_Transmit() */

#if ((CANNM_COM_USER_DATA_SUPPORT ==STD_ON) || (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
/* !LINKSTO CanNm.SWS_CanNm_00326,1 */
#include <PduR_CanNm.h>         /* PduR API for CanNm */
#endif

#if ((CANNM_DEV_ERROR_DETECT == STD_ON) || (CANNM_DET_RUNTIME_CHECKS == STD_ON))
/* Development Error Tracer (CANNM_DET_REPORT_ERROR() macros) */
/* !LINKSTO CanNm.SWS_CanNm_00308,1 */
#include <Det.h>
#endif

/*===========================[macro definitions]============================*/

/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef CANNM_VENDOR_ID /* configuration check */
#error CANNM_VENDOR_ID must be defined
#endif

#if (CANNM_VENDOR_ID != 1U) /* vendor check */
#error CANNM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef CANNM_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error CANNM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANNM_AR_RELEASE_MAJOR_VERSION != 4U)
#error CANNM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef CANNM_AR_RELEASE_MINOR_VERSION /* configuration check */
#error CANNM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANNM_AR_RELEASE_MINOR_VERSION != 0U )
#error CANNM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#ifndef CANNM_AR_RELEASE_REVISION_VERSION /* configuration check */
#error CANNM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (CANNM_AR_RELEASE_REVISION_VERSION != 3U )
#error CANNM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef CANNM_SW_MAJOR_VERSION /* configuration check */
#error CANNM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (CANNM_SW_MAJOR_VERSION != 6U)
#error CANNM_SW_MAJOR_VERSION wrong (!= 6U)
#endif

#ifndef CANNM_SW_MINOR_VERSION /* configuration check */
#error CANNM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (CANNM_SW_MINOR_VERSION < 20U)
#error CANNM_SW_MINOR_VERSION wrong (< 20U)
#endif

#ifndef CANNM_SW_PATCH_VERSION /* configuration check */
#error CANNM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (CANNM_SW_PATCH_VERSION < 6U)
#error CANNM_SW_PATCH_VERSION wrong (< 6U)
#endif

/*------------------[module internal macros]--------------------------------*/
/* just an abbreviating macro */
#if (defined CANNM_EMIT)
#error CANNM_EMIT is already defined
#endif
#define CANNM_EMIT(a,b)                                 \
        CANNM_HSMEMITINST(&CanNm_HsmScCanNm, (a),( b))

#if (defined CANNM_EMITTOSELF)
#error CANNM_EMITTOSELF is already defined
#endif
#define CANNM_EMITTOSELF(a,b)                           \
        CANNM_HSMEMITTOSELFINST(&CanNm_HsmScCanNm, (a),( b))

#if (defined CANNM_HANDLE_TICK)
#error CANNM_HANDLE_TICK is already defined
#endif
#define CANNM_HANDLE_TICK(instIdx, timer, event)         \
  do                                                     \
  {                                                      \
    if (CANNM_CHANNEL_STATUS(instIdx).timer > 0U)        \
   {                                                     \
     --CANNM_CHANNEL_STATUS(instIdx).timer;              \
     if (CANNM_CHANNEL_STATUS(instIdx).timer == 0U)      \
     {                                                   \
       (void)CANNM_EMIT(instIdx, event);                 \
     }                                                   \
   }                                                     \
  }                                                      \
  while (0)

#if (defined CANNM_HANDLE_TICK2)
#error CANNM_HANDLE_TICK2 is already defined
#endif
#define CANNM_HANDLE_TICK2(instIdx, timer, event)        \
  do                                                     \
  {                                                      \
   if (CANNM_CHANNEL_STATUS(instIdx).timer > 0U)         \
   {                                                     \
     CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(instIdx);                \
     --CANNM_CHANNEL_STATUS(instIdx).timer;              \
     CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(instIdx);         \
     if (CANNM_CHANNEL_STATUS(instIdx).timer == 0U)      \
     {                                                   \
       (void)CANNM_EMIT(instIdx, event);                 \
     }                                                   \
   }                                                     \
  }                                                      \
  while (0)

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/
/* !LINKSTO CanNm.ASR403.CANNM311,1 */
#define CANNM_START_SEC_CODE
#include <CanNm_MemMap.h>

#if (CANNM_CARWAKEUP_RX_ENABLED == STD_ON)
/** \brief Process Car wakeup functionality
 ** \param instIdx index of state machine instance to work on */
/* Deviation MISRAC2012-1 */
STATIC FUNC(void, CANNM_CODE) CanNm_HandleCarWakeup(
  CANNM_PDL_SF(PduIdType instIdx));
#endif

#define CANNM_STOP_SEC_CODE
#include <CanNm_MemMap.h>

/*=====================[external constants]=================================*/

/*=====================[internal constants]=================================*/

/*=======================[external data]====================================*/

#define CANNM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanNm_MemMap.h>

VAR(CanNm_ChanStatusType, CANNM_VAR_CLEARED)
  CanNm_ChanStatus[CANNM_NUMBER_OF_CHANNELS];

P2CONST(CanNm_ConfigType, CANNM_VAR_CLEARED, CANNM_APPL_CONST) CanNm_RootPtr;

/** \brief Partial netoworking info: EiraValue and EiraTimer */
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
VAR(CanNm_PnStatusType, CANNM_VAR_CLEARED) CanNm_EiraStatus;
#endif

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
#if (CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM > 0)
VAR(CanNm_SynchronizedPncShutdownIdsType, CANNM_VAR_CLEARED)
  CanNm_SynchronizedPncShutdownIds[CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM];
#endif

#if (CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM > 0)
VAR(CanNm_SynchronizedPncShutdownRxIdsType, CANNM_VAR_CLEARED)
  CanNm_SynchronizedPncShutdownRxIds[CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM];
#endif
#endif

#define CANNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <CanNm_MemMap.h>

#define CANNM_START_SEC_VAR_INIT_8
#include <CanNm_MemMap.h>

/** \brief Intialization information of CanNm module */
VAR(boolean, CANNM_VAR) CanNm_Initialized = FALSE;

#define CANNM_STOP_SEC_VAR_INIT_8
#include <CanNm_MemMap.h>

/*=======================[internal data]====================================*/

/*=====================[external functions definitions]=====================*/

#define CANNM_START_SEC_CODE
#include <CanNm_MemMap.h>

/*------------------[CanNm_IsValidConfig]---------------------------------------------*/

/* !LINKSTO CanNm.EB.Impl.IsValid,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_IsValidConfig
(
  P2CONST(void, AUTOMATIC, CANNM_APPL_CONST) voidConfigPtr
)
{
  /* Assume an invalid configuration */
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(CanNm_ConfigType,AUTOMATIC,CANNM_APPL_CONST) ConfigPtr = voidConfigPtr;

  if (ConfigPtr != NULL_PTR)
  {
    /* Check if the configuration fits to the platform */
    if (TS_PlatformSigIsValid(ConfigPtr->PlatformSignature))
    {
      /* Validate the post build configuration against the compile time configuration */
      if (CANNM_CFG_SIGNATURE == ConfigPtr->CfgSignature)
      {
        /* Validate the post build configuration against the link time configuration */
        if (CanNm_LcfgSignature == ConfigPtr->LcfgSignature)
        {
          /* Validate the Published information in post build configuration against the
          Published information in compile time configuration*/
          if(CANNM_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
          {
            /* Indicate that the configuration is valid */
            RetVal = E_OK;
          }
        }
      }
    }
  }

  return RetVal;
}

/*------------------[CanNm_Init]---------------------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00208,1 */
FUNC(void, CANNM_CODE) CanNm_Init
(
  CONSTP2CONST(CanNm_ConfigType, AUTOMATIC, CANNM_APPL_CONST) cannmConfigPtr
)
{
  uint8 instIdx;
  NetworkHandleType ChIdx;
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
#if (CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM > 0)
  uint8 ActiveGatewayIdx = 0;
#endif
#if (CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM > 0)
  uint8 PassiveGatewayIdx = 0;
#endif
#endif
  /* No protection against races required, as there is no concurrent
   * calling of functions expected at initialization time of the ComStack */

  /* !LINKSTO CanNm.SWS_CanNm_00060,1 */

  P2CONST(CanNm_ConfigType,AUTOMATIC,CANNM_APPL_CONST) LocalConfigPtr = cannmConfigPtr;

  DBG_CANNM_INIT_ENTRY(cannmConfigPtr);

  /* !LINKSTO CanNm.EB.ImplicitUninitState,1, CanNm.EB.NotSuccessfulInitialization,1 */
  /* Deviation TASKING-2 */
  for(instIdx=0U; instIdx<CANNM_NUMBER_OF_CHANNELS; ++instIdx)
  {
      CANNM_CHANNEL_STATUS(instIdx).CurState = NM_STATE_UNINIT;
  }
  CanNm_Initialized = FALSE;

    /* Save the configuration pointer */
#if (CANNM_PBCFGM_SUPPORT_ENABLED == STD_ON)
    /* If the initialization function is called with a null pointer get the configuration from the
     * post build configuration manager */
  if (LocalConfigPtr == NULL_PTR)
  {
      /* !LINKSTO CanNm.EB.Impl.Init,1 */
      PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
      if (E_OK == PbcfgM_GetConfig(
            CANNM_MODULE_ID,
            CANNM_INSTANCE_ID,
            &ModuleConfig))
      {
          LocalConfigPtr = (P2CONST(CanNm_ConfigType, AUTOMATIC, CANNM_APPL_CONST)) ModuleConfig;
      }
  }
#endif /* CANNM_PBCFGM_SUPPORT_ENABLED == STD_OFF */

/* check if development error detection is enabled */
/* !LINKSTO CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)

  /* check whether parameter LocalConfigPtr is a NULL_PTR */
  if(LocalConfigPtr == NULL_PTR)
  {
    /* found a NULL_PTR, report to DET */
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    (void)Det_ReportError(CANNM_MODULE_ID,
                          CANNM_INSTANCE_ID,
                          CANNM_SERVID_INIT,
                          CANNM_E_NULL_POINTER
                         );
  }
  /* check that configuration pointer is valid */
  else if ( E_OK != CanNm_IsValidConfig(LocalConfigPtr))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.4,1 */
    (void)Det_ReportError(CANNM_MODULE_ID,
                          CANNM_INSTANCE_ID,
                          CANNM_SERVID_INIT,
                          CANNM_E_INIT_FAILED
                         );
  }
  else
  if(PB_REQUIRED_CFG_RAM_SIZE > CANNM_DATA_MEM_SIZE)
  {
    /* !LINKSTO CanNm.EB.PostBuildRamSize.3,1 */
    CANNM_DET_REPORT_ERROR(CANNM_INSTANCE_ID, CANNM_SERVID_INIT, CANNM_E_INIT_FAILED);
  }
  else
#else /* check that configuration is valid */
  if(CanNm_IsValidConfig(LocalConfigPtr) == E_OK)
#endif
  {
    CanNm_RootPtr = LocalConfigPtr;

    /* Deviation TASKING-2 */
    for(ChIdx = 0U; ChIdx < CANNM_NUMBER_OF_CHANNELS; ChIdx++)
    {
      CANNM_CHANNEL_STATUS(ChIdx).RxPduPtr = &CanNm_Rx_Tx_Buffer[CANNM_CHANNEL_BUFFER_OFFSET(ChIdx)];
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      CANNM_CHANNEL_STATUS(ChIdx).TxPduPtr = &CanNm_Rx_Tx_Buffer[CANNM_TX_BUFFER_OFFSET + \
                                                                 CANNM_CHANNEL_BUFFER_OFFSET(ChIdx)];
#endif
      CANNM_CHANNEL_STATUS(ChIdx).MessageFlags = 0U;
      /* !LINKSTO CanNm.SWS_CanNm_00141,1 */
      CANNM_CHANNEL_STATUS(ChIdx).CurState = NM_STATE_BUS_SLEEP;
      CANNM_CHANNEL_STATUS(ChIdx).CanNmTimer = 0U;
      CANNM_CHANNEL_STATUS(ChIdx).UniversalTimer = 0U;
      CANNM_CHANNEL_STATUS(ChIdx).RmsTimer = 0U;
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
#if (CANNM_IMMEDIATE_TRANSMISSION == STD_ON)
      CANNM_CHANNEL_STATUS(ChIdx).ImmediateNmTransmissionCounter = 0U;
#endif /* (CANNM_IMMEDIATE_TRANSMISSION == STD_ON) */
      /* !LINKSTO CanNm.SWS_CanNm_00033,1 */
      CANNM_CHANNEL_STATUS(ChIdx).MsgCycleTimer = 0U;
#if (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
      /* !LINKSTO CanNm.ASR403.CANNM061,1 */
      CANNM_CHANNEL_STATUS(ChIdx).TimeoutTimer = 0U;
#endif
#endif
      /* !LINKSTO CanNm.SWS_CanNm_00143,1 */
      CANNM_CHANNEL_STATUS(ChIdx).ChanStatus = 0U;
#if (CANNM_PN_SUPPORTED == STD_ON)
      CANNM_CHANNEL_STATUS(ChIdx).PnFilterEnabled = FALSE;
#endif
#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
      /* !LINKSTO CanNm.SWS_CanNm_00435,1 */
      TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).Era.PnValue, 0U, CANNM_PN_INFO_LENGTH);
      TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).Era.PnInfo, 0U, CANNM_PN_INFO_LENGTH);
      TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).Era.PnTempInfo, 0U, CANNM_PN_INFO_LENGTH);
      TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).Era.PnTimer, 0x00U, (CANNM_EIRA_MAX_TIMER_SIZE * sizeof(CanNm_TimeType)));
#endif
#if (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
      CANNM_CHANNEL_STATUS(ChIdx).ActiveWakeUp1 = 0U;
      CANNM_CHANNEL_STATUS(ChIdx).ActiveWakeUp2 = 0U;
#endif /* CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON */

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
      CANNM_CHANNEL_STATUS(ChIdx).PnSyncShutdownFlags = 0U;
#if (CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM > 0)
      if (CANNM_CHANNEL_CONFIG(ChIdx).CanNmTypeOfGateway == CANNM_GATEWAY_TYPE_ACTIVE)
      {
        CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownIdsPtr = &CanNm_SynchronizedPncShutdownIds[ActiveGatewayIdx];
        ActiveGatewayIdx++;
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
        CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownIdsPtr->PnRetransmissionTimer = 0U;
        TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoSent, 0U, CANNM_PN_INFO_LENGTH);
#endif /* CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0 */
        TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoRcv, 0U, CANNM_PN_INFO_LENGTH);
        TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg, 0U, CANNM_PN_INFO_LENGTH);
      }
      else
#endif
      {
        CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownIdsPtr = NULL_PTR;
      }

#if (CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM > 0)
      if (CANNM_CHANNEL_CONFIG(ChIdx).CanNmTypeOfGateway == CANNM_GATEWAY_TYPE_PASSIVE)
      {
        CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownRxIdsPtr = &CanNm_SynchronizedPncShutdownRxIds[PassiveGatewayIdx];
        PassiveGatewayIdx++;
        TS_MemSet(CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRx, 0U, CANNM_PN_INFO_LENGTH);
      }
      else
#endif
      {
        CANNM_CHANNEL_STATUS(ChIdx).CanNm_SynchronizedPncShutdownRxIdsPtr = NULL_PTR;
      }
#endif /* CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON */
    }

    /* Initialize CanNm state machine, perform initial transitions */
    /* !LINKSTO CanNm.SWS_CanNm_00144,1 */
    CanNm_HsmInit(&CanNm_HsmScCanNm);
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
    /* !LINKSTO CanNm.SWS_CanNm_00424,1 */
    TS_MemSet(CanNm_EiraStatus.PnValue, 0x00U, CANNM_PN_INFO_LENGTH);
    TS_MemSet(CanNm_EiraStatus.PnInfo, 0x00U, CANNM_PN_INFO_LENGTH);
    TS_MemSet(CanNm_EiraStatus.PnTempInfo, 0x00U, CANNM_PN_INFO_LENGTH);
    TS_MemSet(CanNm_EiraStatus.PnTimer, 0x00U, (CANNM_EIRA_MAX_TIMER_SIZE * sizeof(CanNm_TimeType)));
#endif
    CanNm_Initialized = TRUE;
  }

  DBG_CANNM_INIT_EXIT(cannmConfigPtr);
}

/*------------------[CanNm_PassiveStartUp]-----------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00211,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_PassiveStartUp
(
  NetworkHandleType nmChannelHandle
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_PASSIVESTARTUP_ENTRY(nmChannelHandle);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_PASSIVESTARTUP, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_PASSIVESTARTUP, CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDPassiveStartUp,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_PASSIVESTARTUP, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
    boolean emitComControlEv = FALSE;
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif
    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00128.1,1, CanNm.EB_Ref.SWS_CanNm_00128.2,1 */
    /* !LINKSTO CanNm.EB.Dsn.StateDynamics.PASSIVE_START_BUS_SLEEP_MODE,1 */
    /* !LINKSTO CanNm.EB.Dsn.StateDynamics.PASSIVE_START_PREPARE_BUS_SLEEP_MODE,1 */
    if ((CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_BUS_SLEEP) ||
        (CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_PREPARE_BUS_SLEEP))
    {
#if (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
      if (CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 == 0U)
      {
        CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 = CANNM_PASSIVE_STARTUP_AWB;
      }
      else
      {
        /* ActiveWakeUp2 can be written only by CanNm_PassiveStartUp and CanNm_NetworkRelease
         * CanNm_NetworkRequest and CanNm_NetworkGwEraRequest can write only to ActiveWakeUp1.
         * ActiveWakeUp1, ActiveWakeUp2 is set to zero on initialization on
         * BusSleepModeEntry and on PrepareBusSleepModeEntry
         */
        CANNM_CHANNEL_STATUS(index).ActiveWakeUp2 = CANNM_PASSIVE_STARTUP_AWB;
      }
#endif /* CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON */

      emitComControlEv = TRUE;
      retVal = E_OK;
    }
    else
    {
      /* !LINKSTO CanNm.SWS_CanNm_00147,1, CanNm.SWS_CanNm_00189,1 */
      retVal = E_NOT_OK;
    }
    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

    if (emitComControlEv == TRUE)
    {
      /* Emit the event to trigger transition to RepeatMessageState */
      CANNM_EMIT(index, CANNM_HSM_CANNM_EV_NETWORK_START);
    }
  }


  DBG_CANNM_PASSIVESTARTUP_EXIT(retVal,nmChannelHandle);

  return retVal;
}

/*------------------[CanNm_NetworkRequest]-----------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00213,1, CanNm.SWS_CanNm_00257,1 */
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRequest
(
  NetworkHandleType nmChannelHandle
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_NETWORKREQUEST_ENTRY(nmChannelHandle);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKREQUEST, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {

    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.EB_Ref.SWS_CanNm_00192,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKREQUEST, CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDNetworkRequest,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKREQUEST, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif
    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
    /* Set the network requested flag */
    /* !LINKSTO CanNm.SWS_CanNm_00104,1, CanNm.SWS_CanNm_00255,1 */
    CANNM_CHANNEL_STATUS(index).ChanStatus |= (uint8)CANNM_NETWORK_REQUESTED;
#if (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)

    if (CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 == 0U)
    {
      CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 = CANNM_NETWORK_REQUEST_AWB;
    }
#endif /* CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON */
    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

    /* Emit the event to trigger the transition */
    CANNM_EMIT(index, CANNM_HSM_CANNM_EV_NET_REQ_STATUS_CHANGED);
    /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
    retVal = E_OK;
  }


  DBG_CANNM_NETWORKREQUEST_EXIT(retVal,nmChannelHandle);

  return retVal;
}

/*------------------[CanNm_NetworkGwEraRequest]-----------------------------------*/
/* !LINKSTO CanNm.EB.CanNm_NetworkGwEraRequest,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkGwEraRequest
(
  NetworkHandleType nmChannelHandle
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_NETWORKGWERAREQUEST_ENTRY(nmChannelHandle);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKGWERAREQUEST, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {

    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.EB_Ref.SWS_CanNm_00192,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKGWERAREQUEST, CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDNetworkGwEraRequest,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKGWERAREQUEST, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif
    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
    /* Set the network requested flag */
    /* !LINKSTO CanNm.EB.CanNm_NetworkGwEraRequest.NetworkRequest,1 */
    CANNM_CHANNEL_STATUS(index).ChanStatus |= (uint8)CANNM_NETWORK_REQUESTED;
#if (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
    if (CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 == 0U)
    {
      CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 = CANNM_NETWORK_GW_ERA_REQUEST_AWB;
    }
#endif /* CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON */
    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);
    /* Emit the event to trigger the transition */
    CANNM_EMIT(index, CANNM_HSM_CANNM_EV_NET_REQ_STATUS_CHANGED);
    /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
    retVal = E_OK;
  }


  DBG_CANNM_NETWORKGWERAREQUEST_EXIT(retVal,nmChannelHandle);

  return retVal;
}

/*------------------[CanNm_NetworkRelease]-----------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00214,1, CanNm.SWS_CanNm_00260,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRelease
(
  NetworkHandleType nmChannelHandle
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_NETWORKRELEASE_ENTRY(nmChannelHandle);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKRELEASE, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKRELEASE, CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDNetworkRelease,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_NETWORKRELEASE, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
    /* Clear the Network requested flag */
    /* !LINKSTO CanNm.SWS_CanNm_00105,1, CanNm.ASR403.CANNM258,1 */
    CANNM_CHANNEL_STATUS(index).ChanStatus &= (uint8)(~CANNM_NETWORK_REQUESTED);
#if (CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON)
    if ((CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 == CANNM_NETWORK_REQUEST_AWB) ||
        (CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 == CANNM_NETWORK_GW_ERA_REQUEST_AWB))
    {
      CANNM_CHANNEL_STATUS(index).ActiveWakeUp1 = CANNM_CHANNEL_STATUS(index).ActiveWakeUp2;
      CANNM_CHANNEL_STATUS(index).ActiveWakeUp2 = 0U;
    }
#endif /* CANNM_ACTIVE_WAKEUP_BIT_ENABLED == STD_ON */
    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);
    CANNM_EMIT(index, CANNM_HSM_CANNM_EV_NET_REQ_STATUS_CHANGED);
    /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
    retVal = E_OK;
  }


  DBG_CANNM_NETWORKRELEASE_EXIT(retVal,nmChannelHandle);

  return retVal;
}

#endif /* (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

/*------------------[CanNm_DisableCommunication]-----------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00170,1, CanNm.SWS_CanNm_00215,1, CanNm.SWS_CanNm_00262,1 */
#if (CANNM_COM_CONTROL_ENABLED == STD_ON)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_DisableCommunication
(
  NetworkHandleType nmChannelHandle
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_DISABLECOMMUNICATION_ENTRY(nmChannelHandle);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_DISABLECOMMUNICATION, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_DISABLECOMMUNICATION, CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDDisableCommunication,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_DISABLECOMMUNICATION, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    boolean emitComControlEv = FALSE;
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

    if (((CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_REPEAT_MESSAGE) ||
         (CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_NORMAL_OPERATION)
        ) ||
        (CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_READY_SLEEP)
       )
    {
      if ((CANNM_CHANNEL_STATUS(index).ChanStatus & CANNM_COM_DISABLED) == 0U)
      {
        CANNM_CHANNEL_STATUS(index).ChanStatus |= CANNM_COM_DISABLED;

        emitComControlEv = TRUE;

        retVal = E_OK;
      }
      else
      {
        /* !LINKSTO CanNm.EB.SWS_CanNm_00177_Implicit,1 */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* !LINKSTO CanNm.SWS_CanNm_00172,1 */
      retVal = E_NOT_OK;
    }

    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

    if(emitComControlEv == TRUE)
    {
      CANNM_EMIT(index, CANNM_HSM_CANNM_EV_COM_CONTROL);
    }
#else
    /* !LINKSTO CanNm.ASR403.CANNM298,1, CanNm.SWS_CanNm_00189,1 */
    retVal = E_NOT_OK;
#endif /* (CANNM_PASSIVE_MODE_ENABLED == STD_ON) */
  }


  DBG_CANNM_DISABLECOMMUNICATION_EXIT(retVal,nmChannelHandle);

  return retVal;
}

/*------------------[CanNm_EnableCommunication]------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00264,1 */
/* This function only exists if communication control is on,
 * so we do not need to care for passive mode */
/* !LINKSTO CanNm.SWS_CanNm_00216,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_EnableCommunication
(
  NetworkHandleType nmChannelHandle
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_ENABLECOMMUNICATION_ENTRY(nmChannelHandle);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_ENABLECOMMUNICATION, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_ENABLECOMMUNICATION,
      CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDEnableCommunication,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_ENABLECOMMUNICATION, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    boolean emitComControlEv = FALSE;
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

    if (((CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_REPEAT_MESSAGE) ||
         (CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_NORMAL_OPERATION)
        ) ||
        (CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_READY_SLEEP)
       )
    {
      if ((CANNM_CHANNEL_STATUS(index).ChanStatus & CANNM_COM_DISABLED) != 0U)
      {
        /* !LINKSTO CanNm.SWS_CanNm_00176,1 */
        CANNM_CHANNEL_STATUS(index).ChanStatus &= (uint8)(~CANNM_COM_DISABLED);

        emitComControlEv = TRUE;

        retVal = E_OK;
      }
      else
      {
        /* !LINKSTO CanNm.SWS_CanNm_00177,1 */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* !LINKSTO CanNm.SWS_CanNm_00295,1 */
      retVal = E_NOT_OK;
    }

    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

    if(emitComControlEv == TRUE)
    {
      CANNM_EMIT(index, CANNM_HSM_CANNM_EV_COM_CONTROL);
    }
#else
    /* !LINKSTO CanNm.ASR403.CANNM297,1, CanNm.SWS_CanNm_00189,1 */
    retVal = E_NOT_OK;
#endif /* (CANNM_PASSIVE_MODE_ENABLED == STD_ON) */
  }


  DBG_CANNM_ENABLECOMMUNICATION_EXIT(retVal,nmChannelHandle);

  return retVal;
}
#endif /* (CANNM_COM_CONTROL_ENABLED == STD_ON) */

/*------------------------[CanNm_SetUserData]--------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00327,1, CanNm.SWS_CanNm_00159,1, CanNm.ASR403.CANNM217,1, CanNm.SWS_CanNm_00266,1 */
#if ((CANNM_USER_DATA_ENABLED == STD_ON)        \
  && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)    \
  && (CANNM_COM_USER_DATA_SUPPORT == STD_OFF))
FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetUserData
(
  NetworkHandleType nmChannelHandle,
  P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
)
{
  /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_SETUSERDATA_ENTRY(nmChannelHandle,nmUserDataPtr);

  /* Perform checks, get index */
  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_SETUSERDATA, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_SETUSERDATA, CANNM_E_INVALID_CHANNEL);
  }
  else if (nmUserDataPtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.SWS_CanNm_00244,1, CanNm.ASR403.CANNM292,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_SETUSERDATA, CANNM_E_NULL_POINTER);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDSetUserData,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_SETUSERDATA, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
    if (0U == CANNM_CHANNEL_USERDATALENGTH(index))
    {
      /* !LINKSTO CanNm.EB.ComUserDataSupport.SetGetUserDataNoUserData,1, CanNm.SWS_CanNm_00244,1 */
      CANNM_DET_REPORT_ERROR(
        nmChannelHandle, CANNM_SERVID_SETUSERDATA, CANNM_E_INVALID_FUNCTION_ARG);
    }
    else
#endif
    {
      CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
      TS_MemCpy(
        &CANNM_CHANNEL_STATUS(index).TxPduPtr[CANNM_CHANNEL_CONFIG(index).UDFBPos],
        nmUserDataPtr, (uint32)CANNM_CHANNEL_USERDATALENGTH(index));
      CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);
      retVal = E_OK;
    }
  }


  DBG_CANNM_SETUSERDATA_EXIT(retVal,nmChannelHandle,nmUserDataPtr);

  return retVal;
}

#endif /* ((CANNM_USER_DATA_ENABLED == STD_ON)
        * && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
        * && (CANNM_COM_USER_DATA_SUPPORT == STD_OFF)) */

/*------------------------[CanNm_GetUserData]--------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00160,1, CanNm.SWS_CanNm_00218,1, CanNm.SWS_CanNm_00268,1 */
#if (CANNM_USER_DATA_ENABLED == STD_ON)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetUserData
(
  NetworkHandleType                        nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_GETUSERDATA_ENTRY(nmChannelHandle,nmUserDataPtr);

  /* Perform checks, get index */
  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETUSERDATA, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETUSERDATA, CANNM_E_INVALID_CHANNEL);
  }
  else if (nmUserDataPtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(nmChannelHandle, CANNM_SERVID_GETUSERDATA, CANNM_E_NULL_POINTER);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDGetUserData,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETUSERDATA, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
    if (0U == CANNM_CHANNEL_USERDATALENGTH(index))
    {
      /* !LINKSTO CanNm.EB.ComUserDataSupport.SetGetUserDataNoUserData,1, CanNm.SWS_CanNm_00244,1 */
      CANNM_DET_REPORT_ERROR(
        nmChannelHandle, CANNM_SERVID_GETUSERDATA, CANNM_E_INVALID_FUNCTION_ARG);
    }
    else
#endif
    {
      CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

      /* Copy user data */
      TS_MemCpy(nmUserDataPtr,
                &CANNM_CHANNEL_STATUS(index).RxPduPtr[CANNM_CHANNEL_CONFIG(index).UDFBPos],
                (uint32)CANNM_CHANNEL_USERDATALENGTH(index)
               );

      CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);
      /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
      retVal = E_OK;
    }
  }


  DBG_CANNM_GETUSERDATA_EXIT(retVal,nmChannelHandle,nmUserDataPtr);

  return retVal;
}
#endif /* (CANNM_USER_DATA_ENABLED == STD_ON) */


/*------------------------[CanNm_GetNodeIdentifier]--------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00219,1, CanNm.ASR403.CANNM270,1 */
#if (CANNM_NODE_ID_ENABLED == STD_ON)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetNodeIdentifier
(
  NetworkHandleType                        nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr
)
{
  Std_ReturnType retVal   = E_NOT_OK;

#if ((CANNM_DEV_ERROR_DETECT == STD_ON) || (CANNM_HSM_INST_MULTI_ENABLED == STD_ON))
  NetworkHandleType index = 0U;

  if(nmChannelHandle < CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
  {
    index = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
  }
#endif

#if (CANNM_DEV_ERROR_DETECT == STD_OFF)
  TS_PARAM_UNUSED(nmChannelHandle);
#endif

  DBG_CANNM_GETNODEIDENTIFIER_ENTRY(nmChannelHandle,nmNodeIdPtr);

  /* Perform checks, get index */
  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETNODEIDENTIFIER, CANNM_E_NO_INIT);
  }
  else if(  (nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
          ||(index >= CANNM_NUMBER_OF_CHANNELS)
          ||(CANNM_CHANNEL_CONFIG(index).CanNmNodeIdEnabled == FALSE)
         )
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETNODEIDENTIFIER, CANNM_E_INVALID_CHANNEL);
  }
  else if (nmNodeIdPtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETNODEIDENTIFIER, CANNM_E_NULL_POINTER);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() != CANNM_CHANNEL_CONFIG(index).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDGetNodeIdentifier,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETNODEIDENTIFIER, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
    /* !LINKSTO CanNm.SWS_CanNm_00132,1 */
    /* !LINKSTO CanNm.ASR403.CANNM270,1 */
    if(CANNM_CHANNEL_CONFIG(index).CanNmNodeIdEnabled == TRUE)
    {
      *nmNodeIdPtr = CANNM_CHANNEL_STATUS(index).RxPduPtr[CANNM_CHANNEL_CONFIG(index).NidPos];
      /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
      retVal = E_OK;
    }
    else
    {
      retVal = E_NOT_OK;
    }


  }


  DBG_CANNM_GETNODEIDENTIFIER_EXIT(retVal,nmChannelHandle,nmNodeIdPtr);

  return retVal;
}

/*------------------------[CanNm_GetLocalNodeIdentifier]---------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00220,1, CanNm.ASR403.CANNM272,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetLocalNodeIdentifier
(
  NetworkHandleType                        nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr
)
{
  Std_ReturnType retVal   = E_NOT_OK;

#if ((CANNM_DEV_ERROR_DETECT == STD_ON) || (CANNM_HSM_INST_MULTI_ENABLED == STD_ON))
  NetworkHandleType index = 0U;

  if(nmChannelHandle < CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
  {
    index = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
  }
#endif

#if ((CANNM_DEV_ERROR_DETECT == STD_OFF) && (CANNM_NODEID_CALLBACK_ENABLED == STD_OFF) && (CANNM_HSM_INST_MULTI_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(nmChannelHandle);
#endif

  DBG_CANNM_GETLOCALNODEIDENTIFIER_ENTRY(nmChannelHandle,nmNodeIdPtr);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETLOCALNODEIDENTIFIER, CANNM_E_NO_INIT);
  }

  else if ( (nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
          ||(index >= CANNM_NUMBER_OF_CHANNELS)
          ||(CANNM_CHANNEL_CONFIG(index).CanNmNodeIdEnabled == FALSE)
          )
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETLOCALNODEIDENTIFIER,
      CANNM_E_INVALID_CHANNEL);
  }

  else if (nmNodeIdPtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(nmChannelHandle,CANNM_SERVID_GETLOCALNODEIDENTIFIER,
      CANNM_E_NULL_POINTER);
  }

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() != CANNM_CHANNEL_CONFIG(index).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDGetLocalNodeIdentifier,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETLOCALNODEIDENTIFIER, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
    /* !LINKSTO CanNm.SWS_CanNm_00133,1 */
#if (CANNM_NODEID_CALLBACK_ENABLED == STD_ON)
    /* !LINKSTO CanNm.EB.CanNmNodeIdCallback.1,1 */
    /* Store the value return by Node Id callback function */
    *nmNodeIdPtr = CANNM_NODEID_CALLBACK_NAME(nmChannelHandle);
#else
     /* !LINKSTO CanNm.ASR403.CANNM272,1 */
     if(CANNM_CHANNEL_CONFIG(index).CanNmNodeIdEnabled == TRUE)
     {
       *nmNodeIdPtr = CANNM_CHANNEL_NODEID(CanNm_IndexFromNmChannelHandle[nmChannelHandle]);
       /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
       retVal = E_OK;
     }
     else
     {
       retVal = E_NOT_OK;
     }
#endif

  }
  DBG_CANNM_GETLOCALNODEIDENTIFIER_EXIT(retVal,nmChannelHandle,nmNodeIdPtr);

  return retVal;
}
#endif /* (CANNM_NODE_ID_ENABLED == STD_ON) */

/*------------------------[CanNm_RepeatMessageRequest]---------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00221,1, CanNm.ASR403.CANNM274,1, CanNm.EB_Ref.CANNM135.2,1 */
#if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RepeatMessageRequest
(
  NetworkHandleType nmChannelHandle
)
{
  Std_ReturnType retVal   = E_NOT_OK;
  Nm_StateType CurState   = NM_STATE_UNINIT;

#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
  NetworkHandleType index = 0U;

  if(nmChannelHandle < CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
  {
    index = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
  }
#endif

#if (CANNM_DEV_ERROR_DETECT == STD_OFF)
  TS_PARAM_UNUSED(nmChannelHandle);
#endif

  DBG_CANNM_REPEATMESSAGEREQUEST_ENTRY(nmChannelHandle);
  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REPEATMESSAGEREQUEST, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REPEATMESSAGEREQUEST,
      CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() != CANNM_CHANNEL_CONFIG(index).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDRepeatMessageRequest,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REPEATMESSAGEREQUEST, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {

    CurState = CANNM_CHANNEL_STATUS(index).CurState;

    if ((CANNM_CHANNEL_CONFIG(index).CanNmNodeDetectionEnabled == TRUE) &&
        ((CurState == NM_STATE_NORMAL_OPERATION) || (CurState == NM_STATE_READY_SLEEP))
       )
    {
      CONSTP2VAR(uint8, AUTOMATIC, CANNM_VAR_CLEARED) TxPduPtr
        = &CANNM_CHANNEL_STATUS(index).TxPduPtr[
          CANNM_CHANNEL_CONFIG(index).CbvPos];

      /* !LINKSTO CanNm.SWS_CanNm_00113,1, CanNm.SWS_CanNm_00121,1 */
      TS_AtomicSetBit_8(TxPduPtr, CANNM_CBV_REPEATMESSAGEBIT);

      CANNM_EMIT(index, CANNM_HSM_CANNM_EV_REPEAT_MESSAGE_REASON);

      retVal = E_OK;
    }
    else
    {
      /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00137.1,1, CanNm.EB_Ref.SWS_CanNm_00137.2,1, CanNm.EB_Ref.SWS_CanNm_00137.3,1 */
      /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
      retVal = E_NOT_OK;
    }
  }


  DBG_CANNM_REPEATMESSAGEREQUEST_EXIT(retVal,nmChannelHandle);

  return retVal;
}
#endif /*  (CANNM_NODE_DETECTION_ENABLED == STD_ON)  */

/*------------------------[CanNm_GetPduData]---------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00138,1, CanNm.SWS_CanNm_00222,1, CanNm.EB_Ref.CANNM276.1,1, CanNm.EB_Ref.CANNM276.2,1, CanNm.EB_Ref.CANNM276.3,1 */
#if ((CANNM_USER_DATA_ENABLED == STD_ON)        \
  || (CANNM_NODE_ID_ENABLED == STD_ON)          \
  || (CANNM_NODE_DETECTION_ENABLED == STD_ON))
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetPduData
(
  NetworkHandleType                        nmChannelHandle,
  P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmPduDataPtr
)
{
  Std_ReturnType retVal   = E_NOT_OK;
#if ((CANNM_DEV_ERROR_DETECT == STD_ON) || (CANNM_HSM_INST_MULTI_ENABLED == STD_ON))
  NetworkHandleType index = 0U;

  if(nmChannelHandle < CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
  {
    index = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
  }
#endif

  DBG_CANNM_GETPDUDATA_ENTRY(nmChannelHandle,nmPduDataPtr);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETPDUDATA, CANNM_E_NO_INIT);
  }
  else if ( (nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
          ||(index >= CANNM_NUMBER_OF_CHANNELS)
          )
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETPDUDATA, CANNM_E_INVALID_CHANNEL);
  }
  else if (nmPduDataPtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETPDUDATA, CANNM_E_NULL_POINTER);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() != CANNM_CHANNEL_CONFIG(index).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDGetPduData,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETPDUDATA, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

#if(CANNM_USER_DATA_ENABLED == STD_OFF)

    if((CANNM_CHANNEL_CONFIG(index).CanNmNodeDetectionEnabled == TRUE) ||
       (CANNM_CHANNEL_CONFIG(index).CanNmNodeIdEnabled == TRUE)
      )
#endif
    {
      /* PduLength cannot be set to zero.
       * This is ensured by the code generator/configuration schema.
       */
      CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

      /* Copy Pdu data */
      TS_MemCpy(
        nmPduDataPtr, CANNM_CHANNEL_STATUS(index).RxPduPtr,
        CANNM_CHANNEL_PDULENGTH(index));

      CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

      /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
      retVal = E_OK;
    }
  }


  DBG_CANNM_GETPDUDATA_EXIT(retVal,nmChannelHandle,nmPduDataPtr);

  return retVal;
}
#endif /* if ((CANNM_USER_DATA_ENABLED == STD_ON)
        * || (CANNM_NODE_ID_ENABLED == STD_ON)
        * || (CANNM_NODE_DETECTION_ENABLED == STD_ON)) */


/*------------------------[CanNm_GetState]-----------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00223,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetState
(
  NetworkHandleType                               nmChannelHandle,
  P2VAR(Nm_StateType, AUTOMATIC, CANNM_APPL_DATA) nmStatePtr,
  P2VAR(Nm_ModeType, AUTOMATIC, CANNM_APPL_DATA)  nmModePtr
)
{
  Nm_StateType CurState;
  /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_GETSTATE_ENTRY(nmChannelHandle,nmStatePtr,nmModePtr);

  /* Check if the module has been initialized */
  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETSTATE, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETSTATE, CANNM_E_INVALID_CHANNEL);
  }
  else if (nmStatePtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETSTATE, CANNM_E_NULL_POINTER);
  }
  else if (nmModePtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.SWS_CanNm_00244,1, CanNm.ASR403.CANNM292,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETSTATE, CANNM_E_NULL_POINTER);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDGetState,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_GETSTATE, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

    CurState = CANNM_CHANNEL_STATUS(index).CurState;

    /* !LINKSTO CanNm.SWS_CanNm_00092,1, CanNm.SWS_CanNm_00091,1 */
    switch (CurState)
    {
      /* !LINKSTO CanNm.SWS_CanNm_00094,1 */
      case NM_STATE_NORMAL_OPERATION: /* fall through */
      case NM_STATE_REPEAT_MESSAGE: /* fall through */
      case NM_STATE_READY_SLEEP:
        *nmModePtr = NM_MODE_NETWORK;
        *nmStatePtr = CurState;
        retVal = E_OK;
        break;
      case NM_STATE_PREPARE_BUS_SLEEP:
        *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP;
        *nmStatePtr = CurState;
        retVal = E_OK;
        break;
      default:
        /* By default, Bus sleep state is the current state
           after initialization */
        *nmModePtr = NM_MODE_BUS_SLEEP;
        *nmStatePtr = CurState;
        retVal = E_OK;
        break;
    }
  }


  DBG_CANNM_GETSTATE_EXIT(retVal,nmChannelHandle,nmStatePtr,nmModePtr);

  return retVal;
}

/*------------------------[CanNm_GetVersionInfo]-----------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00224,1, CanNm.ASR403.CANNM278,1 */
#if (CANNM_VERSION_INFO_API == STD_ON)
FUNC(void, CANNM_CODE) CanNm_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CANNM_APPL_DATA) versioninfo
)
{
  DBG_CANNM_GETVERSIONINFO_ENTRY(versioninfo);

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == versioninfo)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.SWS_CanNm_00244,1, CanNm.ASR403.CANNM292,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_INSTANCE_ID, CANNM_SERVID_GETVERSIONINFO, CANNM_E_NULL_POINTER);
  }
  else
#endif
  {
    /* !LINKSTO CanNm.ASR403.CANNM225,1 */
    versioninfo->vendorID         = CANNM_VENDOR_ID;
    versioninfo->moduleID         = CANNM_MODULE_ID;
    versioninfo->sw_major_version = CANNM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CANNM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CANNM_SW_PATCH_VERSION;
  }

  DBG_CANNM_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* (CANNM_VERSION_INFO_API == STD_ON) */

/*------------------------[CanNm_RequestBusSynchronization]------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00226,1, CanNm.SWS_CanNm_00072,1, CanNm.SWS_CanNm_00280,1 */
#if ((CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)      \
  && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF))
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestBusSynchronization
(
  NetworkHandleType nmChannelHandle
)
{
  /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_REQUESTBUSSYNCHRONIZATION_ENTRY(nmChannelHandle);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REQUESTBUSSYNCHRONIZATION,
      CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REQUESTBUSSYNCHRONIZATION,
      CANNM_E_INVALID_CHANNEL);
  }
  else
#endif
  {
    Nm_StateType CurState;
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

#if (CANNM_COM_CONTROL_ENABLED == STD_ON)
    if ((CANNM_CHANNEL_STATUS(index).ChanStatus & CANNM_COM_DISABLED) != 0U)
    {
      /* !LINKSTO CanNm.SWS_CanNm_00181,1 */
      retVal = E_NOT_OK;
    }
    else
#endif
    {
      CurState = CANNM_CHANNEL_STATUS(index).CurState;

      if ((CurState == NM_STATE_BUS_SLEEP) ||
          (CurState == NM_STATE_PREPARE_BUS_SLEEP))
      {
        /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00187.1,1, CanNm.EB_Ref.SWS_CanNm_00187.2,1 */
        retVal = E_NOT_OK;
      }
      else
      {
        PduInfoType pduInfo;         /* for sending */

        /* prepare pduInfo */
        pduInfo.SduDataPtr = CANNM_CHANNEL_STATUS(index).TxPduPtr;
        pduInfo.SduLength  = CANNM_CHANNEL_PDULENGTH(index);
#if (CANNM_COM_USER_DATA_SUPPORT == STD_ON)
        CanNm_GetPduUserData(CANNM_INST(index), &pduInfo);
#endif
        /* !LINKSTO CanNm.SWS_CanNm_00130,1 */
        if (E_OK == CanIf_Transmit(CANNM_CHANNEL_TXPDUID(index), &pduInfo))
        {
          retVal = E_OK;
        }

        /* It may be necessary to reset the user data; bug 19201 */
      }
    }
  }


  DBG_CANNM_REQUESTBUSSYNCHRONIZATION_EXIT(retVal,nmChannelHandle);

  return retVal;
}
#endif /* if ((CANNM_BUS_SYNCHRONIZATION == STD_ON)
          && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF))*/

/*------------------------[CanNm_CheckRemoteSleepIndication]-----------------*/
/* !LINKSTO CanNm.SWS_CanNm_00227,1, CanNm.SWS_CanNm_00282,1, CanNm.SWS_CanNm_00153,1 */
#if (CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON)
FUNC(Std_ReturnType, CANNM_CODE) CanNm_CheckRemoteSleepIndication
(
  NetworkHandleType                          nmChannelHandle,
  P2VAR(boolean, AUTOMATIC, CANNM_APPL_DATA) nmRemoteSleepIndPtr
)
{
  /* It makes no sense to protect this function against interruption, as
   * if the result shall be reliable for the caller, it must protect the
   * whole call against interruption anyway. */

  Std_ReturnType retVal = E_NOT_OK;

  DBG_CANNM_CHECKREMOTESLEEPINDICATION_ENTRY(nmChannelHandle,nmRemoteSleepIndPtr);

  /* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_CHECKREMOTESLEEPINDICATION,
      CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_CHECKREMOTESLEEPINDICATION,
      CANNM_E_INVALID_CHANNEL);
  }
  else if (nmRemoteSleepIndPtr == NULL_PTR)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_CHECKREMOTESLEEPINDICATION,
      CANNM_E_NULL_POINTER);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDCheckRemoteSleepIndication,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_CHECKREMOTESLEEPINDICATION, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
    Nm_StateType CurState;
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif

    CurState = CANNM_CHANNEL_STATUS(index).CurState;

    if ((CurState == NM_STATE_NORMAL_OPERATION) ||
        (CurState == NM_STATE_READY_SLEEP))
    {
      if ((CANNM_CHANNEL_STATUS(index).ChanStatus & CANNM_RSI_TRUE) == CANNM_RSI_TRUE)
      {
        *nmRemoteSleepIndPtr = TRUE;
        retVal = E_OK;
      }
      else
      {
        *nmRemoteSleepIndPtr = FALSE;
        retVal = E_OK;
      }
    }
    else
    {
      /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00154.1,1, CanNm.EB_Ref.SWS_CanNm_00154.2,1, CanNm.EB_Ref.SWS_CanNm_00154.3,1 */
      /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
      retVal = E_NOT_OK;
    }
  }


  DBG_CANNM_CHECKREMOTESLEEPINDICATION_EXIT(retVal,nmChannelHandle,nmRemoteSleepIndPtr);

  return retVal;
}
#endif /* (CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON) */


#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_OFF)
/*------------------------[CanNm_MainFunction]-------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00234,1 */
FUNC(void, CANNM_CODE) CanNm_MainFunction(void)
{
  /* Always perform initialization check w/o Det report. See EB
   * req. CanNm.EB.MainFunction.InitCheck. Related SWS requirements are not
   * fulfilled. */

  DBG_CANNM_MAINFUNCTION_ENTRY();
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.EB.MainFunction.InitCheck,1 */
  if (TRUE == CanNm_Initialized)
  {
#if (CANNM_HSM_CANNM_NUM_INST > 1U)
    uint8 i;
#endif
#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
    uint8 Index;
#endif

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
#if (CANNM_HSM_CANNM_NUM_INST > 1U)
    for (i = 0U; i < CANNM_HSM_CANNM_NUM_INST; i++)
#endif
    {
      CanNm_HandlePNSyncShutdown(CANNM_PL_SF(i));
    }
#endif

    /* process timers and emit timeout events */
#if (CANNM_HSM_CANNM_NUM_INST > 1U)
    for (i = 0U; i < CANNM_HSM_CANNM_NUM_INST; ++i)
#endif
    {
      CANNM_CHANNEL_STATUS(i).MessageFlags &= (uint8)(~(uint8)(CANNM_MESSAGE_SENT_ON_CYCLE));
      CanNm_HandleTimerTick(CANNM_PL_SF(i));
    }

    /* Main processing function of HSM */
    CanNm_HsmMain(&CanNm_HsmScCanNm);

#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
    /* !LINKSTO CanNm.ASR403.CANNM422,1, CanNm.ASR403.CANNM423,1 */
    CanNm_HandlePnInfo(&CanNm_EiraStatus, CANNM_PN_EIRA_PDUID);
    CanNm_HandlePnTimers(&CanNm_EiraStatus, CANNM_PN_EIRA_PDUID);
#endif

#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
    /* Process ERA for all channels*/
    /* Deviation TASKING-2 */
    for (Index = 0U; Index < CANNM_NUMBER_OF_CHANNELS; Index++)
    {
      if(CANNM_CHANNEL_CONFIG(Index).EraCalcEnabled == STD_ON)
      {
        /* !LINKSTO CanNm.ASR403.CANNM433,1, CanNm.ASR403.CANNM434,1 */
        CanNm_HandlePnInfo(&CANNM_CHANNEL_STATUS(Index).Era, CANNM_CHANNEL_CONFIG(Index).EraPduId);
        CanNm_HandlePnTimers(&CANNM_CHANNEL_STATUS(Index).Era, CANNM_CHANNEL_CONFIG(Index).EraPduId);
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
        CanNm_HandlePNSyncShutdownForwardReq(CANNM_PL_SF(Index));
#endif
      }
      else
      {
        /* added for C coverage */
      }
    }
#endif

  }

  DBG_CANNM_MAINFUNCTION_EXIT();
}
#endif

/*------------------------[CanNm_TxConfirmation]-----------------------------*/
/* !LINKSTO CanNm.ASR403.CANNM228,1, CanNm.SWS_CanNm_00284,1, CanNm.EB_Ref.SWS_CanNm_00073.1,1, CanNm.EB_Ref.SWS_CanNm_00073.2,1 */
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)             \
  && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
FUNC(void, CANNM_CODE) CanNm_TxConfirmation
(
 PduIdType TxPduId
)
{
  DBG_CANNM_TXCONFIRMATION_ENTRY(TxPduId);

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1, CanNm.EB_Ref.CANNM229.2,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_INSTANCE_ID, CANNM_SERVID_TXCONFIRMATION, CANNM_E_NO_INIT);
  }
  else
#endif
  {
#if ((CANNM_NUMBER_OF_CHANNELS > 1U) || (CANNM_DEV_ERROR_DETECT == STD_ON))
    NetworkHandleType index = 0U;

    /* lookup CanNm channel related given TxPduId */
    /* Deviation TASKING-2 */
    for(index = 0U; index < CANNM_NUMBER_OF_CHANNELS; ++index)
    {
      if (CANNM_CHANNEL_CONFIG(index).TxConfPduId == TxPduId)
      {
        break;
      }
    }

#endif

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
    if (index >= CANNM_NUMBER_OF_CHANNELS)
    {
      /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.3,1, CanNm.EB_Ref.CANNM229.1,1, CanNm.SWS_CanNm_00244,1 */
      CANNM_DET_REPORT_ERROR(
        CANNM_INVALID_PDU_INSTANCE_ID, CANNM_SERVID_TXCONFIRMATION,
        CANNM_E_INVALID_PDUID);
    }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
    else if (GetApplicationID() != CANNM_CHANNEL_CONFIG(index).ChannelApplicationID)
    {
      /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDTxConfirmation,1 */
      CANNM_DET_REPORT_ERROR(
        CANNM_CHANNEL_CONFIG(index).nmChannelId, CANNM_SERVID_TXCONFIRMATION, CANNM_E_INVALID_OSAPPLICATION);
    }
#endif
    else
#endif
    {
#if (CANNM_COM_USER_DATA_SUPPORT == STD_ON)
      /* !LINKSTO CanNm.SWS_CanNm_00329,1, CanNm.EB.ComUserDataSupport.PduRCallsNoUserData.3,1, CanNm.EB.PduRAPIs.TxPduId_1,1 */
      if (0U != CANNM_CHANNEL_USERDATALENGTH(index))
      {
        PduR_CanNmTxConfirmation(CANNM_CHANNEL_USERTXCONFPDUID(index));
      }
#endif
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
      if ((CANNM_CHANNEL_STATUS(index).TxPduPtr[CANNM_CHANNEL_CONFIG(index).CbvPos] & CANNM_CBV_PNSRBITMASK) != 0U)
      {
        TS_AtomicSetBit_8(&CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags, CANNM_PN_SYNC_SHUTDOWN_TX_BIT);
      }
#endif
#endif
      CANNM_EMIT(index, CANNM_HSM_CANNM_EV_TX_CONFIRMATION);
    }
  }
#if ((CANNM_HSM_INST_MULTI_ENABLED == STD_OFF) && (CANNM_DEV_ERROR_DETECT == STD_OFF))
  TS_PARAM_UNUSED(TxPduId);
#endif

  DBG_CANNM_TXCONFIRMATION_EXIT(TxPduId);
}
#endif /* (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) &&
          (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF) */

/*------------------------[CanNm_RxIndication]-------------------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00231,1 */
FUNC(void, CANNM_CODE) CanNm_RxIndication
(
 PduIdType                                      RxPduId,
 P2VAR(PduInfoType, AUTOMATIC, CANNM_APPL_DATA) PduInfoPtr
)
{
#if (CANNM_COM_USER_DATA_SUPPORT == STD_ON)
  PduInfoType UserPdu;
#endif
#if ((CANNM_DET_RUNTIME_CHECKS == STD_ON) && (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON))
  boolean invPncSyncShutdownReq = FALSE;
#endif
#if (CANNM_HSM_INST_MULTI_ENABLED != STD_ON)
  TS_PARAM_UNUSED(RxPduId);
#endif

  DBG_CANNM_RXINDICATION_ENTRY(RxPduId,PduInfoPtr);

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1, CanNm.EB_Ref.CANNM232.2,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_INSTANCE_ID, CANNM_SERVID_RXINDICATION, CANNM_E_NO_INIT);
  }
  else if (RxPduId >= CANNM_NUMBER_OF_CHANNELS)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.3,1, CanNm.EB_Ref.CANNM232.1,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_INVALID_PDU_INSTANCE_ID, CANNM_SERVID_RXINDICATION,
      CANNM_E_INVALID_PDUID);
  }
  else if (((PduInfoPtr == NULL_PTR) ||
            (PduInfoPtr->SduDataPtr == NULL_PTR)
           ) ||
           (PduInfoPtr->SduLength > CANNM_CHANNEL_PDULENGTH(RxPduId))
          )
  {
    /* Here we report CANNM_E_NULL_POINTER for length overflow,too */
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.EB_Ref.CANNM232.3,1, CanNm.ASR403.CANNM233,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_CHANNEL_CONFIG(RxPduId).nmChannelId,
      CANNM_SERVID_RXINDICATION, CANNM_E_NULL_POINTER);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() != CANNM_CHANNEL_CONFIG(RxPduId).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDRxIndication,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_CHANNEL_CONFIG(RxPduId).nmChannelId, CANNM_SERVID_RXINDICATION, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_PN_SUPPORTED == STD_ON)
    boolean ValidPnMessage = FALSE;
#endif

    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(RxPduId);

    /* !LINKSTO CanNm.SWS_CanNm_00035,1 */
    /* Copy Pdu Data to internal buffer */
    TS_MemCpy(CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
/* !LINKSTO CanNm.SWS_CanNm_00412,1 */
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON) || (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
    /* !LINKSTO CanNm.EB.PnEnabled_FALSE.1,1 */
    if (CANNM_CHANNEL_PNENABLED(RxPduId) == TRUE)
    {
      ValidPnMessage = CanNm_IsValidPnMessage(RxPduId);
      if (ValidPnMessage == TRUE)
      {
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
        if ((CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr[CANNM_CHANNEL_CONFIG(RxPduId).CbvPos] &
             CANNM_CBV_PNSRBITMASK) == 0U
           )
#endif
        {
          /* CanNm_RxIndication could be called more than once within the interval of 2 main function
           * calls. Therefore, the external requests to be aggregated.
           */
#if (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
          if (CANNM_CHANNEL_CONFIG(RxPduId).EraCalcEnabled == STD_ON)
          {
            /* !LINKSTO CanNm.ASR403.CANNM433,1, CanNm.ASR403.CANNM434,1 */
            CanNm_AggregatePnInfo(&CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr[CANNM_PN_INFO_OFFSET],
                                  &CANNM_CHANNEL_STATUS(RxPduId).Era
                                 );
          }
          else
          {
            /* added for C coverage */
          }
#endif /* #if (CANNM_PN_ERA_CALC_ENABLED == STD_ON) */
#if ((CANNM_PN_EIRA_CALC_ENABLED == STD_ON) && (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_OFF))
          CanNm_AggregatePnInfo(&CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr[CANNM_PN_INFO_OFFSET],
                                &CanNm_EiraStatus
                                );
#endif /* #if ((CANNM_PN_EIRA_CALC_ENABLED == STD_ON) && (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_OFF)) */
        }
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
        else
        {
          if (CANNM_CHANNEL_CONFIG(RxPduId).CanNmTypeOfGateway == CANNM_GATEWAY_TYPE_PASSIVE)
          {
            CanNm_AggregatePnInfoSyncShutdown(&CANNM_CHANNEL_STATUS(RxPduId).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRx[0],
                                              &CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr[CANNM_PN_INFO_OFFSET]
                                             );
            CANNM_CHANNEL_STATUS(RxPduId).PnSyncShutdownFlags |= CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX;
          }
        }
#endif
      }

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
      if (((CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr[CANNM_CHANNEL_CONFIG(RxPduId).CbvPos] &
             CANNM_CBV_PNSRBITMASK) != 0U
          ) &&
          (CANNM_CHANNEL_CONFIG(RxPduId).CanNmTypeOfGateway == CANNM_GATEWAY_TYPE_ACTIVE)
         )
      {
#if (CANNM_DET_RUNTIME_CHECKS == STD_ON)
        invPncSyncShutdownReq = TRUE;
#endif
#if (CANNM_PN_SYNC_SHUTDOWN_ERROR_REACTION_ENABLED == STD_ON)
        CANNM_CHANNEL_STATUS(RxPduId).PnSyncShutdownFlags |= CANNM_PN_SYNC_SHUTDOWN_INVMSG;
#endif
      }
#endif
    }
#endif /* #if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON) || (CANNM_PN_ERA_CALC_ENABLED == STD_ON) */
    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(RxPduId);

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
#if (CANNM_DET_RUNTIME_CHECKS == STD_ON)
    if (invPncSyncShutdownReq == TRUE)
    {
            /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00461,1, CanNm.EB_Ref.SWS_CanNm_00317.3,1, CanNm.SWS_CanNm_00324,1 */
            CANNM_DET_REPORT_RUNTIME_ERROR( CANNM_CHANNEL_CONFIG(RxPduId).nmChannelId,
                                            CANNM_SERVID_RXINDICATION,
                                            CANNM_E_INVALID_PN_SYNC_SHUTDOWN_REQUEST
                                          );
    }
#endif
#endif

#if (CANNM_CARWAKEUP_RX_ENABLED == STD_ON)
    /* Requirement CanNm.SWS_CanNm_00407 is satisfied since
     * the calling of the function Nm_CarWakeUpIndication
     * is done after the population of RxPduPtr buffer
     */
    /* !LINKSTO CanNm.SWS_CanNm_00407,1 */
    CanNm_HandleCarWakeup(CANNM_PL_SF(RxPduId));
#endif
#if (CANNM_PN_SUPPORTED == STD_ON)
    /* !LINKSTO CanNm.SWS_CanNm_00409,1, CanNm.SWS_CanNm_00410,1, CanNm.SWS_CanNm_00411,1, CanNm.SWS_CanNm_00420,1, CanNm.ASR403.CANNM403,1, CanNm.SWS_CanNm_00421,1 */
    /* Deviation TASKING-1 */
    if (((ValidPnMessage == TRUE) ||
         (CANNM_CHANNEL_PNENABLED(RxPduId) == FALSE)
        ) ||
        ((CANNM_CHANNEL_CONFIG(RxPduId).AllNmMessagesKeepAwake == TRUE) ||
         (CANNM_CHANNEL_STATUS(RxPduId).PnFilterEnabled == FALSE)
        )
       )
#endif /*(CANNM_PN_SUPPORTED == STD_ON)*/
    {
#if (CANNM_COM_USER_DATA_SUPPORT == STD_ON)
      /* !LINKSTO CanNm.EB.ComUserDataSupport.PduRCallsNoUserData.2,1 */
      if(CANNM_CHANNEL_USERRXPDUENABLED(RxPduId) == TRUE)
      {
        UserPdu.SduLength = (PduLengthType)CANNM_CHANNEL_USERDATALENGTH(RxPduId);
        UserPdu.SduDataPtr =
          &(CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr[CANNM_CHANNEL_CONFIG(RxPduId).UDFBPos]);

        /* !LINKSTO CanNm.EB.ComUserDataSupport.CanNmUserDataRxIndication,1 */
        PduR_CanNmRxIndication(CANNM_CHANNEL_USERRXPDUID(RxPduId), &UserPdu);
      }
#endif /* (CANNM_COM_USER_DATA_SUPPORT == STD_ON) */
      /* !LINKSTO CanNm.EB_Ref.CANNM135.1,1 */
#if (CANNM_NODE_DETECTION_ENABLED == STD_ON)
      /* Notify again if the RepeatMessageBit is set */
      if ((CANNM_CHANNEL_CONFIG(RxPduId).CanNmNodeDetectionEnabled == TRUE) &&
          TS_IsBitSet(&(CANNM_CHANNEL_STATUS(RxPduId).RxPduPtr[CANNM_CHANNEL_CONFIG(RxPduId).CbvPos]),
                      CANNM_CBV_REPEATMESSAGEBIT, uint8)
         )
      {
#if (CANNM_REPEAT_MSG_IND_ENABLED == STD_ON)
        uint8 Index;

        /* Nm_RepeatMessageIndication has to be called for all the channels
           which are configured with this Rx Pdu */
        /* Deviation TASKING-2 */
        for (Index = 0U; Index < CANNM_NUMBER_OF_CHANNELS; Index++)
        {
          if ((CANNM_CHANNEL_CONFIG(Index).RxPduId == RxPduId)      &&      \
              (CANNM_CHANNEL_CONFIG(Index).CanNmRepeatMsgIndEnabled == TRUE)\
             )
          {
            /* !LINKSTO CanNm.ASR403.CANNM014,1 */
#if (CANNM_MULTICORE_ENABLED == STD_OFF)
            CANNM_CALL_NM_REPEATMESSAGEINDICATION(CANNM_INST(Index));
#else
            if (CANNM_CALL_NM_REPEATMESSAGEINDICATION(CANNM_INST(Index)) != SCHM_E_OK)
            {
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
             /* !LINKSTO CanNm.EB.SchM_Call_DET,1 */
             CANNM_DET_REPORT_ERROR(CANNM_INST(Index),
                                    CANNM_SERVID_RXINDICATION,
                                    CANNM_E_REPEATMESSAGEINDICATION);
#endif
            }
#endif
          }
        }
#endif
        CANNM_EMIT((uint8)RxPduId, CANNM_HSM_CANNM_EV_REPEAT_MESSAGE_REASON);
      }
#endif

      CANNM_EMIT((uint8)RxPduId, CANNM_HSM_CANNM_EV_RX_INDICATION);
    }
  }

  DBG_CANNM_RXINDICATION_EXIT(RxPduId,PduInfoPtr);
}

/*------------------------[CanNm_Transmit]-----------------------------------*/
#if (CANNM_COM_USER_DATA_SUPPORT == STD_ON)
/* !LINKSTO CanNm.SWS_CanNm_00331,1, CanNm.ASR403.CANNM330,1, CanNm.EB_Ref.SWS_CanNm_00333.1,2, CanNm.EB_Ref.SWS_CanNm_00333.2,2 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_Transmit(
    PduIdType CanTxPduId,
    P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA) PduInfoPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* Here CanTxPduId reffers to CanNmTxUserDataPduId.
   * CanNmTxUserDataPduId has the same id as the RxPduId.
   */
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  uint8 index = 0U;
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
  boolean StatusPNSRBit = FALSE;
#endif

  DBG_CANNM_TRANSMIT_ENTRY(CanTxPduId,PduInfoPtr);

  /* lookup CanNm channel related given TxPduId */
  /* Deviation TASKING-2 */
  for(index = 0U; index < CANNM_NUMBER_OF_CHANNELS; index++)
  {
    if (CANNM_CHANNEL_CONFIG(index).UserTxPduId == CanTxPduId)
    {
      break;
    }
  }

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1, CanNm.ASR403.CANNM191,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_INSTANCE_ID, CANNM_SERVID_CANNMTRANSMIT, CANNM_E_NO_INIT);
  }
  else if (index >= CANNM_NUMBER_OF_CHANNELS)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.3,1, CanNm.SWS_CanNm_00244,1, CanNm.ASR403.CANNM196,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_INVALID_PDU_INSTANCE_ID, CANNM_SERVID_CANNMTRANSMIT,
      CANNM_E_INVALID_PDUID);
  }
  /* !LINKSTO CanNm.ASR403.CANNM199,1 */
  else if ((PduInfoPtr == NULL_PTR) ||
           (PduInfoPtr->SduDataPtr == NULL_PTR))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.5,1, CanNm.ASR403.CANNM292,1, CanNm.SWS_CanNm_00244,1, CanNm.ASR403.CANNM196,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_CHANNEL_CONFIG(index).nmChannelId,
      CANNM_SERVID_CANNMTRANSMIT, CANNM_E_NULL_POINTER);
  }
  /* !LINKSTO CanNm.ASR403.CANNM199,1 */
  else if ((PduInfoPtr->SduLength == 0U) ||
           (CANNM_CHANNEL_USERDATALENGTH(index) < PduInfoPtr->SduLength))
  {
    /* !LINKSTO CanNm.SWS_CanNm_00244,1, CanNm.ASR403.CANNM196,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_CHANNEL_CONFIG(index).nmChannelId,
      CANNM_SERVID_CANNMTRANSMIT, CANNM_E_INVALID_FUNCTION_ARG);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() != CANNM_CHANNEL_CONFIG(index).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDTransmit,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_CHANNEL_CONFIG(index).nmChannelId, CANNM_SERVID_CANNMTRANSMIT, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
    Nm_StateType CurState;
    CurState = CANNM_CHANNEL_STATUS(index).CurState;

    if ((CurState == NM_STATE_REPEAT_MESSAGE) ||
        (CurState == NM_STATE_NORMAL_OPERATION))
    {
      PduInfoType pduInfoLocal;
      uint8 UDFBPos = CANNM_CHANNEL_CONFIG(index).UDFBPos;
      /* prepare pduInfoLocal */
      pduInfoLocal.SduDataPtr = CANNM_CHANNEL_STATUS(index).TxPduPtr;
      pduInfoLocal.SduLength  = CANNM_CHANNEL_PDULENGTH(index);

      /* Some bytes may remain unchanged in case UDFBPos + UserDataLength != RX/TX PduLength */
      CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
      if ((CANNM_CHANNEL_STATUS(index).TxPduPtr[CANNM_CHANNEL_CONFIG(index).CbvPos] &
           CANNM_CBV_PNSRBITMASK) != 0U
         )
      {
        StatusPNSRBit = TRUE;
      }
      else
#endif
      {
        TS_MemCpy( &(pduInfoLocal.SduDataPtr[UDFBPos]), PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
      }
      CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
      /* !LINKSTO CanNm.EB.PnSyncShutdown.CanNm_Transmit,1 */
      if (StatusPNSRBit == FALSE)
#endif
      {
        if(E_OK == CanIf_Transmit(CANNM_CHANNEL_TXPDUID(index), &pduInfoLocal))
        {
  #if (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)
          CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
          CANNM_TX_TIMER_START(index, CANNM_CHANNEL_CONFIG(index).MsgTimeoutTime);
          CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);
  #endif
          retVal = E_OK;
        }
      }
#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
      else
      {
        retVal = E_OK;
      }
#endif
    }
  }
  DBG_CANNM_TRANSMIT_EXIT(retVal,CanTxPduId,PduInfoPtr);
#else /* (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
  DBG_CANNM_TRANSMIT_ENTRY(CanTxPduId,PduInfoPtr);
  TS_PARAM_UNUSED(CanTxPduId);
  TS_PARAM_UNUSED(PduInfoPtr);
  DBG_CANNM_TRANSMIT_EXIT(retVal,CanTxPduId,PduInfoPtr);
  /* !LINKSTO CanNm.SWS_CanNm_00189,1 */
#endif /* (CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

  return retVal;
}
#endif /* (CANNM_COM_USER_DATA_SUPPORT == STD_ON) */

/*------------------------[CanNm_GetPduUserData]-----------------------------*/
#if ((CANNM_COM_USER_DATA_SUPPORT == STD_ON) || (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
FUNC(void, CANNM_CODE) CanNm_GetPduUserData(uint8 instIdx,
                                            P2VAR(PduInfoType, AUTOMATIC, AUTOMATIC) pduInfo
                                           )
{
#if (!((CANNM_HSM_INST_MULTI_ENABLED == STD_ON) && \
      (CANNM_COM_USER_DATA_SUPPORT == STD_ON)))
  TS_PARAM_UNUSED(instIdx);
#endif

#if (CANNM_COM_USER_DATA_SUPPORT == STD_ON)
  /* !LINKSTO CanNm.EB.ComUserDataSupport.PduRCallsNoUserData.1,1 */
  if( 0U != CANNM_CHANNEL_USERDATALENGTH(instIdx))
  {
    uint8 UDFBPos = CANNM_CHANNEL_CONFIG(instIdx).UDFBPos;
    PduInfoType PduUserInfo;
    PduUserInfo.SduDataPtr = &(pduInfo->SduDataPtr[UDFBPos]);
    PduUserInfo.SduLength  = pduInfo->SduLength - UDFBPos;

    /* !LINKSTO CanNm.SWS_CanNm_00328,1, CanNm.EB.PduRAPIs.TxPduId_2,1 */
    (void)PduR_CanNmTriggerTransmit(CANNM_CHANNEL_USERTXCONFPDUID(instIdx), &PduUserInfo);
  }
#endif
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
  /* !LINKSTO CanNm.EB.PnEnabled_FALSE.2,1 */
  if (CANNM_CHANNEL_PNENABLED(instIdx) == TRUE)
  {
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_OFF)
    /* Protect aggregation of EIRA as this is being called from RxIndication too */
    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(instIdx);

    CanNm_AggregatePnInfo(&pduInfo->SduDataPtr[CANNM_PN_INFO_OFFSET],
                          &CanNm_EiraStatus
                         );

    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(instIdx);
#else
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.Sender.Tx,1 */
    (void) CANNM_CHANNEL_CONFIG(instIdx).ChannelPnInfoSend(&pduInfo->SduDataPtr[CANNM_PN_INFO_OFFSET]);
#endif
  }
#endif
}
#endif /* ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) */


/*------------------------[CanNm_ConfirmPnAvailability]----------------------*/
/* !LINKSTO CanNm.SWS_CanNm_00344,1, CanNm.ASR403.CANNM346,1 */
#if (CANNM_PN_SUPPORTED == STD_ON)
FUNC(void, CANNM_CODE) CanNm_ConfirmPnAvailability
(
  NetworkHandleType nmChannelHandle
)
{
  DBG_CANNM_CONFIRMPNAVAILABILITY_ENTRY(nmChannelHandle);

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      CANNM_INSTANCE_ID, CANNM_SERVID_CONFIRMPNAVAILABILITY, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_CONFIRMPNAVAILABILITY, CANNM_E_INVALID_CHANNEL);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDConfirmPnAvailability,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_CONFIRMPNAVAILABILITY, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
    const NetworkHandleType index
       = CanNm_IndexFromNmChannelHandle[nmChannelHandle];
#else
    TS_PARAM_UNUSED(nmChannelHandle);
#endif
#if (CANNM_PN_SUPPORTED == STD_ON)
   if (CANNM_CHANNEL_PNENABLED(index) == TRUE)
   {
     /* !LINKSTO CanNm.SWS_CanNm_00404,1 */
     CANNM_CHANNEL_STATUS(index).PnFilterEnabled = TRUE;
   }
#endif
  }

  DBG_CANNM_CONFIRMPNAVAILABILITY_EXIT(nmChannelHandle);
}
#endif /* (CANNM_PN_SUPPORTED == STD_ON) */


/*-------------------[CanNm_RequestSynchronizedPncShutdown]------------------*/
/* !LINKSTO CanNm.ASRR2111.SWS_CanNm_91003,1, CanNm.ASRR2111.SWS_CanNm_00467,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestSynchronizedPncShutdown
(
  NetworkHandleType nmChannelHandle,
  PNCHandleType pncId
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
  DBG_CANNM_REQUESTSYNCHRONIZEDPNCSHUTDOWN_ENTRY(nmChannelHandle,pncId);

/* !LINKSTO CanNm.ASR403.CANNM243,1, CanNm.ASR403.CANNM241,1 */
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO CanNm.ASR403.CANNM039,1 */
  if (CanNm_Initialized == FALSE)
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.1,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, CANNM_E_NO_INIT);
  }
  else if ((nmChannelHandle >= CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
    || (CanNm_IndexFromNmChannelHandle[nmChannelHandle]
      >= CANNM_NUMBER_OF_CHANNELS))
  {
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00316.2,1, CanNm.SWS_CanNm_00244,1, CanNm.EB_Ref.SWS_CanNm_00192,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, CANNM_E_INVALID_CHANNEL);
  }
  else if ((pncId < (8U * CANNM_PN_INFO_OFFSET)) ||
           (pncId >= (8U * (CANNM_PN_INFO_OFFSET + CANNM_PN_INFO_LENGTH)))
          )
  {
    /* !LINKSTO CanNm.EB.PnSyncShutdown.CanNm_RequestSynchronizedPncShutdown.InvalidPncId,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, CANNM_E_INVALID_FUNCTION_ARG);
  }
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  else if (GetApplicationID() !=
        CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).ChannelApplicationID)
  {
    /* !LINKSTO CanNm.EB.CanNmChannelMultiCore.DetAppIDRequestSynchronizedPncShutdown,1 */
    CANNM_DET_REPORT_ERROR(
      nmChannelHandle, CANNM_SERVID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, CANNM_E_INVALID_OSAPPLICATION);
  }
#endif
  else
#endif
  {
    if (CANNM_CHANNEL_CONFIG(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).CanNmTypeOfGateway ==
        CANNM_GATEWAY_TYPE_ACTIVE)
    {
      const uint8 index = (uint8)(pncId >> SHIFT_3_BITS) - CANNM_PN_INFO_OFFSET;

      /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00462,1 */
      TS_AtomicSetBit_8(
          &CANNM_CHANNEL_STATUS(CanNm_IndexFromNmChannelHandle[nmChannelHandle]).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoRcv[index],
          (uint8)(pncId & MASK_3_BITS)
          );

      retVal = E_OK;
    }
  }

  DBG_CANNM_REQUESTSYNCHRONIZEDPNCSHUTDOWN_EXIT(nmChannelHandle,pncId);

#else /* CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON */
  TS_PARAM_UNUSED(nmChannelHandle);
  TS_PARAM_UNUSED(pncId);
  DBG_CANNM_REQUESTSYNCHRONIZEDPNCSHUTDOWN_ENTRY(nmChannelHandle,pncId);
  DBG_CANNM_REQUESTSYNCHRONIZEDPNCSHUTDOWN_EXIT(nmChannelHandle,pncId);
  retVal = E_OK;
#endif /* CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON */

  return retVal;
}

/*-------------------------[CanNm_Dummy_RxIndication]------------------------*/
/* CHECK: NOPARSE */
/* No parse has been added because
 * (CanNm_Dummy_RxIndication function has been added with the support for multi core.)
 * when modelling the cross core function calls (Schm_Call) context is required
 * for modelling the calling context.
 * The RxIndication is called from an interrupt context which cannot be modelled
 * in Rte therefore a dummy context has been added.
 * Rte generates a function declaration, here an empty function definitions
 * is provided but never called.
 */
#if ((CANNM_MULTICORE_ENABLED == STD_ON) &&\
     ((CANNM_REPEAT_MSG_IND_ENABLED == STD_ON) || (CANNM_CARWAKEUP_RX_ENABLED == STD_ON)))
FUNC(void, CANNM_CODE) CanNm_Dummy_RxIndication (void)
{

}
#endif
/* CHECK: PARSE */

/*=====================[external Non API function definitions]=====================*/
#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON) || (CANNM_PN_ERA_CALC_ENABLED == STD_ON)
FUNC(boolean, CANNM_CODE) CanNm_IsValidPnMessage
(
  PduIdType PduId
)
{
  boolean ValidMessage = FALSE;
  P2CONST(uint8, AUTOMATIC, CANNM_VAR_CLEARED) PnInfo =
          &CANNM_CHANNEL_STATUS(PduId).RxPduPtr[CANNM_PN_INFO_OFFSET];


  if (TS_IsBitSet(&(CANNM_CHANNEL_STATUS(PduId).RxPduPtr[CanNm_ChanConfig[PduId].CbvPos]),
                    CANNM_CBV_PNINFOBIT, uint8
                   )
       )
  {
    if (CanNm_ChanStatus[PduId].PnFilterEnabled == TRUE)
    {
      uint8 PnPduId;
      for (PnPduId=0U; ((PnPduId < CANNM_PN_INFO_LENGTH) && (ValidMessage == FALSE)); PnPduId++)
      {
        /* !LINKSTO CanNm.ASR403.CANNM418,1, CanNm.SWS_CanNm_00419,1 */
        if ((PnInfo[PnPduId] & CanNm_RootPtr->PnFilterMask[PnPduId]) != 0U)
        {
          ValidMessage = TRUE;
        }
      }
    }
    else
    {
      ValidMessage = TRUE;
    }
  }

  return ValidMessage;
}

#endif

/*=====================[internal functions definitions]=====================*/

/* Deviation MISRAC2012-1 */
FUNC(void, CANNM_CODE) CanNm_HandleTimerTick(
   CANNM_PDL_SF(uint8 instIdx))
{
  CANNM_HANDLE_TICK(instIdx, UniversalTimer, CANNM_HSM_CANNM_EV_UNI_TIMEOUT);
  CANNM_HANDLE_TICK(instIdx, RmsTimer, CANNM_HSM_CANNM_EV_RMS_TIMEOUT);
#if ((CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF) \
  && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF))
  CANNM_HANDLE_TICK2(instIdx, TimeoutTimer, CANNM_HSM_CANNM_EV_TX_TIMEOUT);
#endif
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  CANNM_HANDLE_TICK(instIdx, MsgCycleTimer, CANNM_HSM_CANNM_EV_MSG_CYCLE_TIMEOUT);
#endif
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  /*ready to expire*/
  if(CANNM_CHANNEL_STATUS(instIdx).CanNmTimer == 1U)
  {
    CANNM_CHANNEL_STATUS(instIdx).NmTimerExpired = TRUE;
  }
#endif
  CANNM_HANDLE_TICK(instIdx, CanNmTimer, CANNM_HSM_CANNM_EV_NM_TIMEOUT);

}

#if (CANNM_CARWAKEUP_RX_ENABLED == STD_ON)
/* Deviation MISRAC2012-1 */
STATIC FUNC(void, CANNM_CODE) CanNm_HandleCarWakeup(
  CANNM_PDL_SF(PduIdType instIdx))
{
  if (CANNM_CHANNEL_CONFIG(instIdx).CanNmCarWakeUpRxEnabled == TRUE)
  {
    uint8 CwuBytePos = CANNM_CHANNEL_CONFIG(instIdx).CanNmCarWakeUpBytePosition;
    uint8 CwuMask = 1U << CANNM_CHANNEL_CONFIG(instIdx).CanNmCarWakeUpBitPosition;
    uint8 RecNid = 0U;
    boolean CallCarWakeUpIndication = FALSE;
    /* Parameter CanNmCarWakeUpFilterEnabled can be set to true
     * only in case NodeId is configured this is assured by an xdm check.
     * Reading of the NodeId shall be done only if CanNmCarWakeUpFilterEnabled
     * is set to true, this assures that NodeId is configured.
     */
    if(CANNM_CHANNEL_CONFIG(instIdx).CanNmCarWakeUpFilterEnabled == TRUE)
    {
      RecNid = CANNM_CHANNEL_STATUS(instIdx).RxPduPtr[CANNM_CHANNEL_CONFIG(instIdx).NidPos];
    }

    if((CANNM_CHANNEL_STATUS(instIdx).RxPduPtr[CwuBytePos] & CwuMask) != 0U)
    {
      /* !LINKSTO CanNm.SWS_CanNm_00406,1 */
      if (CANNM_CHANNEL_CONFIG(instIdx).CanNmCarWakeUpFilterEnabled == FALSE)
      {
        CallCarWakeUpIndication = TRUE;
      }

      /* !LINKSTO CanNm.SWS_CanNm_00408,1 */
      if ((CANNM_CHANNEL_CONFIG(instIdx).CanNmCarWakeUpFilterEnabled == TRUE) &&
          (RecNid == CANNM_CHANNEL_CONFIG(instIdx).CanNmCarWakeUpFilterNodeId))
      {
        CallCarWakeUpIndication = TRUE;
      }

      if(CallCarWakeUpIndication == TRUE)
      {
#if (CANNM_MULTICORE_ENABLED == STD_OFF)
        CANNM_CALL_NM_CARWAKEUPINDICATION(CANNM_INST(instIdx));
#else
        if (CANNM_CALL_NM_CARWAKEUPINDICATION(CANNM_INST(instIdx)) != SCHM_E_OK)
        {
#if (CANNM_DEV_ERROR_DETECT == STD_ON)
           uint8 CanNm_Instance_Macro;
#if (CANNM_HSM_INST_MULTI_ENABLED == STD_ON)
           CanNm_Instance_Macro = (uint8)(CANNM_INST(instIdx));
#else
           CanNm_Instance_Macro = 0U;
#endif
           /* !LINKSTO CanNm.EB.SchM_Call_DET,1 */
           CANNM_DET_REPORT_ERROR(CanNm_Instance_Macro,
                                  CANNM_SERVID_RXINDICATION,
                                  CANNM_E_CARWAKEUPINDICATION);
#endif
        }
#endif
      }
    }
  }
}
#endif
#if ((CANNM_PN_EIRA_CALC_ENABLED == STD_ON) || (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
FUNC(void, CANNM_CODE) CanNm_HandlePnTimers
(
  P2VAR(CanNm_PnStatusType,AUTOMATIC, CANNM_VAR_CLEARED) pPnStatus,
  PduIdType PduId
)
{
  uint16 PnIndex;
  boolean EiraChanged = FALSE;

  for (PnIndex = 0U; PnIndex < CANNM_EIRA_MAX_TIMER_SIZE; PnIndex++)
  {
    /* Get EiraTimer index from mapped EIRA/ERA timer array.
     *
     * Timers in EiraTimer holds values corresponding to each PN (each bit)
     * by mapping through CanNm_EiraTimerMap.
     * For example EiraTimer[0] is the timer for PN0 (Bit 0 of EiraValue[0]) and
     * EiraTimer[9] is the timer for PN9 (Bit 1 of EiraValue[1]). */
    uint16 EiraIndex = CanNm_RootPtr->EiraTimerMap[PnIndex];

    if (CANNM_EIRA_TIMER_INVALID != EiraIndex)
    {
      if (0U < pPnStatus->PnTimer[EiraIndex])
      {
        /* Decrement PN timer. */
        pPnStatus->PnTimer[EiraIndex]--;

        if (0U == pPnStatus->PnTimer[EiraIndex])
        {
          /* If PN timer get expired, then clear the corresponding PN status bit
           * and set the flag to indicate a change in EIRA status */
          /* !LINKSTO CanNm.SWS_CanNm_00442,1, CanNm.SWS_CanNm_00431,1 */
          pPnStatus->PnValue[PnIndex/8U] &= (uint8)~((uint8)(1U << (PnIndex%8U)));
          EiraChanged = TRUE;
        }
      }
    }
  }

  if (EiraChanged == TRUE)
  {
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = pPnStatus->PnValue;
    pduInfo.SduLength = CANNM_PN_INFO_LENGTH;
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00443.2,1, CanNm.EB_Ref.SWS_CanNm_00432.3,1 */
    PduR_CanNmRxIndication(PduId, &pduInfo);
  }
}

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
FUNC(void, CANNM_CODE) CanNm_HandlePnInfo
(
  P2VAR(CanNm_PnStatusType, AUTOMATIC, CANNM_VAR_CLEARED) PnStatePtr,
  PduIdType PduId,
  NetworkHandleType ChannelIndex
)
#else
FUNC(void, CANNM_CODE) CanNm_HandlePnInfo
(
  P2VAR(CanNm_PnStatusType, AUTOMATIC, CANNM_VAR_CLEARED) PnStatePtr,
  PduIdType PduId
)
#endif
{
  uint8 PnIndex;
  boolean EiraChanged = FALSE;

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  if (CANNM_MAIN_PARTITION_HANDLE == ChannelIndex)
  {
    SchM_Enter_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_MAIN();
  }
  else
  {
    CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(ChannelIndex);
  }
#else
  SchM_Enter_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_0();
#endif

  /* copy and clear external requests */
  TS_MemCpy(PnStatePtr->PnTempInfo, PnStatePtr->PnInfo, CANNM_PN_INFO_LENGTH);
  TS_MemSet(PnStatePtr->PnInfo, 0U, CANNM_PN_INFO_LENGTH);

#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
  if (CANNM_MAIN_PARTITION_HANDLE == ChannelIndex)
  {
    SchM_Exit_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_MAIN();
  }
  else
  {
    CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(ChannelIndex);
  }
#else
  SchM_Exit_CanNm_SCHM_CANNM_EXCLUSIVE_AREA_0();
#endif

#if ((CANNM_PN_EIRA_CALC_ENABLED == STD_ON) && (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON))
  if (ChannelIndex != CANNM_MAIN_PARTITION_HANDLE)
  {
    (void) CANNM_CHANNEL_CONFIG(ChannelIndex).ChannelPnInfoSend(PnStatePtr->PnTempInfo);
  }
#endif /*#if ((CANNM_PN_EIRA_CALC_ENABLED == STD_ON) && (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON))*/

  /* Deviation TASKING-2 */
  for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
  {
    if ((PnStatePtr->PnTempInfo[PnIndex] & CanNm_RootPtr->PnFilterMask[PnIndex]) != 0U)
    {
      uint8 PnBitPos;
      for (PnBitPos = 0U; PnBitPos < 8U; PnBitPos++)
      {
        if (CanNm_RootPtr->EiraTimerMap[(PnIndex * 8U) + PnBitPos] != CANNM_EIRA_TIMER_INVALID)
        {
          uint8 PnBitMask = 1U << PnBitPos;
          if ((PnStatePtr->PnTempInfo[PnIndex] & PnBitMask) != 0U)
          {
            if ((PnStatePtr->PnValue[PnIndex] & PnBitMask) == 0U)
            {
              /* !LINKSTO CanNm.SWS_CanNm_00437,1, CanNm.ASR403.CANNM425,1, CanNm.SWS_CanNm_00426,1, CanNm.SWS_CanNm_00427,1 */
              PnStatePtr->PnValue[PnIndex] |= PnBitMask;
              EiraChanged = TRUE;
            }
            /* load timer value */
            /* !LINKSTO CanNm.SWS_CanNm_00439,1, CanNm.SWS_CanNm_00429,1, CanNm.ASR403.CANNM430,1 */
            PnStatePtr->PnTimer[CanNm_RootPtr->EiraTimerMap[(PnIndex * 8U) + PnBitPos]]
                  = CANNM_PN_RESET_TIME + 1U;
          }
        }
      }
    }
  }

  if (EiraChanged == TRUE)
  {
    PduInfoType pduInfo;
    pduInfo.SduDataPtr = PnStatePtr->PnValue;
    pduInfo.SduLength = CANNM_PN_INFO_LENGTH;
    /* !LINKSTO CanNm.EB_Ref.SWS_CanNm_00443.1,1, CanNm.EB_Ref.SWS_CanNm_00432.1,1, CanNm.EB_Ref.SWS_CanNm_00432.2,1 */
    PduR_CanNmRxIndication(PduId, &pduInfo);
  }
}

FUNC(void, CANNM_CODE) CanNm_AggregatePnInfo
(
  P2CONST(uint8, AUTOMATIC, CANNM_VAR_CLEARED) PnInfo,
  P2VAR(CanNm_PnStatusType,AUTOMATIC, CANNM_VAR_CLEARED) pPnStatus
)
{
  uint8 PnIndex;

  /* Deviation TASKING-2 */
  for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
  {
      /* Aggregate external requests */
      /* !LINKSTO CanNm.ASR403.CANNM436,1 */
      pPnStatus->PnInfo[PnIndex] |= (uint8)(PnInfo[PnIndex] & CanNm_RootPtr->PnFilterMask[PnIndex]);
  }
}

#if (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON)
FUNC(void, CANNM_CODE) CanNm_AggregatePnInfoSyncShutdown
(
  P2VAR(uint8, AUTOMATIC, CANNM_VAR_CLEARED) PnInfoDest,
  P2CONST(uint8, AUTOMATIC, CANNM_VAR_CLEARED) PnInfoSrc
)
{
  uint8 PnIndex;

  /* Deviation TASKING-2 */
  for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
  {
      PnInfoDest[PnIndex] |= (uint8)(PnInfoSrc[PnIndex] & CanNm_RootPtr->PnFilterMask[PnIndex]);
  }
}

/* Deviation MISRAC2012-1 */
FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown(
  CANNM_PDL_SF(uint8 index)
)
{
  uint16 PnIndex;
  uint8 newSyncShutdownReq = 0U;
  PduInfoType pduInfo;
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
  uint8 retransmit = 0U;
#else
#if (CANNM_DET_RUNTIME_CHECKS == STD_ON)
  Std_ReturnType retVal = E_NOT_OK;
#endif
#endif

  if ((CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_REPEAT_MESSAGE) ||
      (CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_NORMAL_OPERATION) ||
      (CANNM_CHANNEL_STATUS(index).CurState == NM_STATE_READY_SLEEP)
     )
  {
    if (CANNM_CHANNEL_CONFIG(index).CanNmTypeOfGateway == CANNM_GATEWAY_TYPE_ACTIVE)
    {
      CanNm_HandlePNSyncShutdown_ActiveChAggregateReq(CANNM_PL_SF(index));

      /* Deviation TASKING-2 */
      for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
      {
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
        /* check that a new request was added to agg buffer since previous sync shutdown request */
        retransmit |=
            (CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg[PnIndex]) &
            (uint8)(~(uint8)(CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoSent[PnIndex]));
#endif
        newSyncShutdownReq |=
            CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg[PnIndex];
      }

      if (newSyncShutdownReq != 0U)
      {
        if (CANNM_CHANNEL_STATUS(index).MsgCycleTimer == 1U)
        {
          /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00460,1 */
          /* timer of normal nm message is about to expire, delay it by 1 cycle */
          CANNM_CHANNEL_STATUS(index).MsgCycleTimer = 2U;
        }

        pduInfo.SduDataPtr = &CANNM_CHANNEL_STATUS(index).TxPduPtr[CANNM_CHANNEL_CONFIG(index).UDFBPos];
        pduInfo.SduLength  = CANNM_CHANNEL_PDULENGTH(index) - CANNM_CHANNEL_CONFIG(index).UDFBPos;

        /* retrieve user data from comm */
        (void) PduR_CanNmTriggerTransmit(CANNM_CHANNEL_USERTXCONFPDUID(index), &pduInfo);

        pduInfo.SduDataPtr = CANNM_CHANNEL_STATUS(index).TxPduPtr;
        pduInfo.SduLength  = CANNM_CHANNEL_PDULENGTH(index);

        CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

        /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00045,2, CanNm.ASRR2111.SWS_CanNm_00506,1 */
        pduInfo.SduDataPtr[CANNM_CHANNEL_CONFIG(index).CbvPos] |= CANNM_CBV_PNSRBITMASK;

        /* Deviation TASKING-2 */
        for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
        {
          /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00506,1 */
          pduInfo.SduDataPtr[CANNM_PN_INFO_OFFSET+ PnIndex] =
            CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg[PnIndex];
        }

        CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
        if (retransmit != 0U)
        {
          CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnRetransmissionTimer =
              CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION;

          TS_MemCpy(CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoSent,
                    CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg,
                    (uint32)CANNM_PN_INFO_LENGTH);
        }
#endif

#if  ((CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION == 0) && \
      (CANNM_DET_RUNTIME_CHECKS == STD_ON))
        retVal = CanIf_Transmit(CANNM_CHANNEL_TXPDUID(index), &pduInfo);

        if (retVal == E_NOT_OK)
        {
          /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00471,1, CanNm.EB_Ref.SWS_CanNm_00317.4,1, CanNm.SWS_CanNm_00324,1 */
          CANNM_DET_REPORT_RUNTIME_ERROR(CANNM_INST(index),
                                         CANNM_SERVID_MAINFUNCTION_X,
                                         CANNM_E_TRANSMISSION_OF_PN_SHUTDOWN_MESSAGE_FAILED);
        }
#else
        (void) CanIf_Transmit(CANNM_CHANNEL_TXPDUID(index), &pduInfo);
#endif
        TS_AtomicSetBit_8(&CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags,
                          (uint8) CANNM_PN_SYNC_SHUTDOWN_RCV_BIT
                         );

#if (CANNM_PN_EIRA_CALC_ENABLED == STD_ON)
#if (CANNM_MULTICORE_CHANNEL_SUPPORT == STD_ON)
        (void) CANNM_CHANNEL_CONFIG(index).ChannelPnInfoSend(
                 CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg
               );

#else
        CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);
        CanNm_AggregatePnInfo(CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg,
                              &CanNm_EiraStatus
                             );
        CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);
#endif
#endif /* (CANNM_PN_EIRA_CALC_ENABLED == STD_ON) */

        /* when there is no retransmission the aggregate buffer is reseted */
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION == 0)
        TS_MemSet(CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg,
                  0U,
                  (uint32)CANNM_PN_INFO_LENGTH);
#endif
      }
#if (CANNM_PN_SYNC_SHUTDOWN_ERROR_REACTION_ENABLED == STD_ON)
      /* if a PNSR set to 1 is received on an active channel and we are in normal/repeat message state
         (pn sync shutdown message has priority) */
      else if (CANNM_CHANNEL_STATUS(index).CurState != NM_STATE_READY_SLEEP)
      {
        CanNm_HandlePNSyncShutdown_ActiveChInvMsg(CANNM_PL_SF(index));
      }
#endif
      else
      {
        /* do nothing */
      }
    }
    else if (CANNM_CHANNEL_CONFIG(index).CanNmTypeOfGateway == CANNM_GATEWAY_TYPE_PASSIVE)
    {
      CanNm_HandlePNSyncShutdown_PassiveCh(CANNM_PL_SF(index));
    }
    else
    {
      /* do nothing */
    }
  }
}

/* Deviation MISRAC2012-1 */
FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown_ActiveChAggregateReq(
  CANNM_PDL_SF(uint8 index)
)
{
  uint16 PnIndex;
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
  boolean retransmitTimeout = FALSE;
  boolean MessageSent;
#if (CANNM_DET_RUNTIME_CHECKS == STD_ON)
  boolean retransmitTimeoutDet = FALSE;
#endif
#endif

  TS_AtomicClearBit_8(&CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags,
                      (uint8) CANNM_PN_SYNC_SHUTDOWN_RCV_BIT
                     );

#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
  if (CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnRetransmissionTimer > 0U)
  {
    /* !LINKSTO CanNm.EB.PnSyncShutdown.CanNm_TxConfirmation.Timeout,1 */
    CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnRetransmissionTimer--;
    if (CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnRetransmissionTimer == 0U)
    {
      retransmitTimeout = TRUE;
    }
  }
#endif

  CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

  /* Deviation TASKING-2 */
  for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
  {
    /* aggregate the received sync shutdown requests into Agg buffer */
    CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg[PnIndex] |=
        (uint8)(CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoRcv[PnIndex] &
                CanNm_RootPtr->PnFilterMask[PnIndex]);
    CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoRcv[PnIndex] = 0U;
  }

  /* reset tx flags */
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
  if ((CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags & CANNM_PN_SYNC_SHUTDOWN_TX) != 0U)
  {
    CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags &= (uint8)(~(uint8)(CANNM_PN_SYNC_SHUTDOWN_TX));
    CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnRetransmissionTimer = 0U;

    MessageSent = TRUE;
  }
  else
  {
    if (retransmitTimeout == TRUE)
    {
      retransmitTimeoutDet = TRUE;

      MessageSent = TRUE;
    }
    else
    {
      MessageSent = FALSE;
    }
  }

  if (MessageSent == TRUE)
#endif
  {
    CANNM_CHANNEL_STATUS(index).TxPduPtr[CANNM_CHANNEL_CONFIG(index).CbvPos] &=
      (uint8)(~(uint8)(CANNM_CBV_PNSRBITMASK));
  }

  CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

#if ((CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0) && \
     (CANNM_DET_RUNTIME_CHECKS == STD_ON))
  if (retransmitTimeoutDet == TRUE)
  {
      /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00472,1, CanNm.EB_Ref.SWS_CanNm_00317.4,1, CanNm.SWS_CanNm_00324,1 */
      CANNM_DET_REPORT_RUNTIME_ERROR(CANNM_INST(index),
                                     CANNM_SERVID_MAINFUNCTION_X,
                                     CANNM_E_TRANSMISSION_OF_PN_SHUTDOWN_MESSAGE_FAILED);
  }
#endif

  /* remove shutdown requets for which tx confirmation was received, pn sync shutdown
     retransmission timer expired, or a timeout occured */
#if (CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION != 0)
  /* on else clause(empty) the agg buffer is kept to be retransmitted */
  /* !LINKSTO CanNm.EB.PnSyncShutdown.CanNm_TxConfirmation.Timeout,1 */
  if (MessageSent == TRUE)
  {
    /* Deviation TASKING-2 */
    for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
    {
      CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoAgg[PnIndex] &=
          (uint8)(~(uint8)(CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoSent[PnIndex]));

      /* !LINKSTO CanNm.EB.PnSyncShutdown.CanNm_TxConfirmation.Ok,1 */
      CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownIdsPtr->PnInfoSent[PnIndex] = 0U;
    }
  }
#endif
}

#if (CANNM_PN_SYNC_SHUTDOWN_ERROR_REACTION_ENABLED == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown_ActiveChInvMsg(
  CANNM_PDL_SF(uint8 index)
)
{
  boolean InvalidMsg;

  CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

  InvalidMsg = FALSE;
  if ((CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags & CANNM_PN_SYNC_SHUTDOWN_INVMSG) != 0U)
  {
    InvalidMsg = TRUE;
    CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags &= (uint8)(~(uint8)(CANNM_PN_SYNC_SHUTDOWN_INVMSG));
  }

  CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

  if (InvalidMsg == TRUE)
  {
    /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00461,1 */
    (void)CANNM_EMITTOSELF(index, CANNM_HSM_CANNM_EV_MSG_CYCLE_TIMEOUT);
  }
}
#endif

/* Deviation MISRAC2012-1 */
FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdown_PassiveCh(
  CANNM_PDL_SF(uint8 index)
)
{
  uint16 PnIndex;
  uint8 PnBitPos;
  uint8 PnBitMask;
  uint8 newForwardSyncShutdown = 0U;

  CANNM_ENTER_CHANNEL_EXCLUSIVE_AREA(index);

  if ((CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags & CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX) != 0U)
  {
    CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags &= (uint8)(~(uint8)(CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_RX));

    /* copy rx buffer into aggregate, and remove requests that were received on the bus */
    /* Deviation TASKING-2 */
    for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
    {
      newForwardSyncShutdown |= CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRx[PnIndex];

#if (CANNM_MULTICORE_ENABLED == STD_ON)
      CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRxAgg.PnInfo[PnIndex] =
#else
      CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRxAgg[PnIndex] =
#endif
          CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRx[PnIndex];

      CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRx[PnIndex] = 0U;
    }
  }

  CANNM_EXIT_CHANNEL_EXCLUSIVE_AREA(index);

  if (newForwardSyncShutdown != 0U)
  {
    /* set flag to make call Nm_ForwardSynchronizedPncShutdown at end of main function */
    TS_AtomicSetBit_8 (&CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags,
                       (uint8) CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD_BIT
                      );

    /* make timer expire during this main function cycle */
    /* Deviation TASKING-2 */
    for (PnIndex = 0U; PnIndex < CANNM_PN_INFO_LENGTH; PnIndex++)
    {
      for (PnBitPos = 0U; PnBitPos < 8U; PnBitPos++)
      {
        PnBitMask = 1U << PnBitPos;
#if (CANNM_MULTICORE_ENABLED == STD_ON)
        if ((CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRxAgg.PnInfo[PnIndex] &
            PnBitMask) != 0U
           )
#else
        if ((CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRxAgg[PnIndex] &
            PnBitMask) != 0U
           )
#endif
        {
          CANNM_CHANNEL_STATUS(index).Era.PnTimer[CanNm_RootPtr->EiraTimerMap[(PnIndex * 8U) + PnBitPos]] = 1U;
        }
      }
    }
  }
}

/* Deviation MISRAC2012-1 */
FUNC(void, CANNM_CODE) CanNm_HandlePNSyncShutdownForwardReq(
  CANNM_PDL_SF(uint8 index)
)
{
  if ((CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags & CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD) != 0U)
  {
    TS_AtomicClearBit_8(&CANNM_CHANNEL_STATUS(index).PnSyncShutdownFlags, CANNM_PN_SYNC_SHUTDOWN_PASSIVE_CH_FWD_BIT);

#if (CANNM_MULTICORE_ENABLED == STD_ON)
    /* !LINKSTO CanNm.EB.PnSyncShutdown.Nm_ForwardSynchronizedPncShutdown.Multicore,1 */
    CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRxAgg.Channel =
        CANNM_CHANNEL_CONFIG(index).nmChannelId;
    (void) SchM_Send_CanNm_CanNm_ForwardSynchronizedPncShutdown_CanNm_To_Nm_DataSet(
        &CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRxAgg
        );
#else
    /* !LINKSTO CanNm.ASRR2111.SWS_CanNm_00504,1 */
    (void) Nm_ForwardSynchronizedPncShutdown(CANNM_CHANNEL_CONFIG(index).nmChannelId,
      CANNM_CHANNEL_STATUS(index).CanNm_SynchronizedPncShutdownRxIdsPtr->PnInfoRxAgg
    );
#endif
  }
}

#endif /* (CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED == STD_ON) */

#endif /*((CANNM_PN_EIRA_CALC_ENABLED == STD_ON) || (CANNM_PN_ERA_CALC_ENABLED == STD_ON)) */

/* !LINKSTO CanNm.EB.CanNmMultiCoreUseSingleCS.CanNm_MultipleNetworkOperations.Available,1 */
#if (CANNM_MULTICORE_USE_SINGLE_CS == STD_ON)
/* !LINKSTO CanNm.EB.CanNmMultiCoreUseSingleCS.CanNm_MultipleNetworkOperations,1 */
FUNC(Std_ReturnType, CANNM_CODE) CanNm_MultipleNetworkOperations
(
  NetworkHandleType nmChannelHandle,
  uint8             operation
)
{
  Std_ReturnType retVal = E_NOT_OK;
  /* !LINKSTO CanNm.EB.CanNmMultiCoreUseSingleCS.PassiveStartup,1 */
  if (operation == CANNM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP)
  {
    retVal = CanNm_PassiveStartUp(nmChannelHandle);
  }
#if (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  /* !LINKSTO CanNm.EB.CanNmMultiCoreUseSingleCS.NetworkRequest,1 */
  else if (operation == CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST)
  {
    retVal = CanNm_NetworkRequest(nmChannelHandle);
  }
  /* !LINKSTO CanNm.EB.CanNmMultiCoreUseSingleCS.NetworkRelease,1 */
  else if (operation == CANNM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE)
  {
    retVal = CanNm_NetworkRelease(nmChannelHandle);
  }
  /* !LINKSTO CanNm.EB.CanNmMultiCoreUseSingleCS.NetworkGwEraRequest,1 */
  else
  {
    retVal = CanNm_NetworkGwEraRequest(nmChannelHandle);
  }
#endif
  return retVal;
}
#endif

#define CANNM_STOP_SEC_CODE
#include <CanNm_MemMap.h>

/*==============================[end of file]===============================*/
