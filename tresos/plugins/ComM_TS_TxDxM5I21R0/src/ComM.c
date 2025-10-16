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



/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
 *
 * Reason:
 * The macro is used in function parameter declarations and definitions of structure member
 * where the number of parentheses matter.
 *
 * MISRAC2012-2) Deviated Rule: 8.9 (advisory)
 * An object should be defined at block scope if its identifier only appears in a single function.
 *
 * Reason:
 * The object has internal linkage for readability improvement.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * In the context of expression "for (index = 0U; index < "max_element_number" ; ++index)"
 * when "max_element_number = 1" the message condition is always true is expected;
 * Expression "index < max_element_number" is always evaluated as true if ""max_element_number" = 1".
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * If number of ComMPnc = 0 and ComMModeLimitationEnabled = false and ComMWakeupInhibitionEnabled = false,
 * the message condition is always true is expected for TestSequences: ComM_ComTest_6, ComM_ComTest_2,
 * ComM_ComTest_8, ComM_ComTest_ResourceConsumption, ComM_ComTest_3;
 *
 * TASKING-3) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * if COMM_MODE_LIMITATION_ENABLED is set to STD_OFF NoComInhibitionStatus is always false
 * if COMM_WAKEUP_INHIBITION_ENABLED is set to STD_OFF WkUpInhibitionStatus is always false
 *
 * TASKING-4) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * In some test cases the return value of Com_ReceiveSignal is always E_OK
 *
 */

 /*==================[inclusions]============================================*/

#include <ComM_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <TSMem.h>

#include <ComM.h>               /* ComM API definitions (own interface) */
#include <ComM_BSW.h>           /* Module specific public APIs */

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
#include <ComM_Nm.h>            /* NM callback APIs */
#include <Nm.h>
#endif

#if (COMM_DCM_ENABLED == STD_ON)
#include <ComM_Dcm.h>           /* DCM callback APIs */
#endif

#include <ComM_EcuMBswM.h>      /* ECUM and BSWM callback APIs */
#include <ComM_BusSm.h>         /* Bus State manager callback APIs */

#include <ComM_BSW_Cfg.h>      /* Module internal BSW specific interface */
#include <ComM_Int.h>           /* Internal Rte proxy function declarations */

#if (COMM_NVM_ENABLED == STD_ON)
/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.NvM,1 */
#include <NvM.h>                /* Memory Access APIs */
#endif

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.CanSM,1 */
#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
#include <CanSM_ComM.h>        /* Can state manager */
#endif

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.FrSM,1 */
#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
#include <FrSM.h>              /* Flexray state manager */
#endif

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.LinSM,1 */
#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
#include <LinSM.h>             /* Lin state manager */
#endif
/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.EthSM,1 */
#if (COMM_ETHSM_ACCESS_NEEDED == STD_ON)
#include <EthSM.h>             /* Eth state manager */
#endif

#if (COMM_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.Det,1 */
#include <Det.h>                /* Det API */
#endif

#if (COMM_INCLUDE_RTE == STD_ON)
#include <ComM_Rte_Cfg.h>  /* internal Rte config dependent header */
#endif

/* for the case COMM_INCLUDE_RTE == STD_OFF these symbols are provided via
 * ComM.h. */

#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_PNC_SUPPORT == STD_ON))
#include <SchM_ComM_1_MasterPnc.h>
#endif /* ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_PNC_SUPPORT == STD_ON)) */

#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && \
     (((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))))
#include <SchM_ComM_1_Inhibition.h>
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && \
        *      (((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))))
        */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#include <Os.h>
#endif

/*==================[macros]================================================*/

/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef COMM_VENDOR_ID /* configuration check */
#error COMM_VENDOR_ID must be defined
#endif

#if (COMM_VENDOR_ID != 1U) /* vendor check */
#error COMM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef COMM_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error COMM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (COMM_AR_RELEASE_MAJOR_VERSION != 4U)
#error COMM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef COMM_AR_RELEASE_MINOR_VERSION /* configuration check */
#error COMM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (COMM_AR_RELEASE_MINOR_VERSION != 1U )
#error COMM_AR_RELEASE_MINOR_VERSION wrong (!= 1U)
#endif

#ifndef COMM_AR_RELEASE_REVISION_VERSION /* configuration check */
#error COMM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (COMM_AR_RELEASE_REVISION_VERSION != 3U )
#error COMM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef COMM_SW_MAJOR_VERSION /* configuration check */
#error COMM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (COMM_SW_MAJOR_VERSION != 5U)
#error COMM_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#ifndef COMM_SW_MINOR_VERSION /* configuration check */
#error COMM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (COMM_SW_MINOR_VERSION < 21U)
#error COMM_SW_MINOR_VERSION wrong (< 21U)
#endif

#ifndef COMM_SW_PATCH_VERSION /* configuration check */
#error COMM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (COMM_SW_PATCH_VERSION < 4U)
#error COMM_SW_PATCH_VERSION wrong (< 4U)
#endif

/** \brief ID for the invalid event */
#if (defined COMM_EVENT_INVALID)
#error COMM_EVENT_INVALID already defined
#endif
#define COMM_EVENT_INVALID                  255U

/*--------------------------------------------------------------------------*/
#if (COMM_MULTICORE_ENABLED == STD_OFF)
#if (defined COMM_BUSSM_GET_CURRENT_COM_MODE)
#error COMM_BUSSM_GET_CURRENT_COM_MODE already defined
#endif
#if (COMM_NUM_USERS != 0U)
/** \brief Call wrapper for bus state manager function
 * <Bus>SM_GetCurrentComMode() */
#define COMM_BUSSM_GET_CURRENT_COM_MODE(channel, mode)                  \
  (ComM_BusSMGetCurrentComModeFpList[COMM_BUSTYPE_OF_CHANNEL(channel)]((channel), (mode)))
#endif
#endif
/*--------------------------------------------------------------------------*/

/* Macro for Det checks of channel identifier as function argument */
#if (defined COMM_IS_CHANNEL_INVALID)
#error COMM_IS_CHANNEL_INVALID already defined
#endif

#if (defined STEP_1_CHANNEL_INVALID)
#error STEP_1_CHANNEL_INVALID already defined
#endif

#if (defined STEP_2_CHANNEL_INVALID)
#error STEP_2_CHANNEL_INVALID already defined
#endif

#if (defined STEP_3_CHANNEL_INVALID)
#error STEP_3_CHANNEL_INVALID already defined
#endif

#if (defined STEP_4_CHANNEL_INVALID)
#error STEP_4_CHANNEL_INVALID already defined
#endif

#define STEP_1_CHANNEL_INVALID(Channel) ((Channel) >= COMM_NUM_CHANNELS)

#if (COMM_NM_VARIANT_NONE_NEEDED == STD_ON)
#define STEP_2_CHANNEL_INVALID(Channel) \
            (STEP_1_CHANNEL_INVALID(Channel) || (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_NONE_VARIANT))
#else
#define STEP_2_CHANNEL_INVALID(Channel) STEP_1_CHANNEL_INVALID(Channel)
#endif

#if (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)
#define STEP_3_CHANNEL_INVALID(Channel) \
            (STEP_2_CHANNEL_INVALID(Channel) || (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_LIGHT_VARIANT))
#else
#define STEP_3_CHANNEL_INVALID(Channel) STEP_2_CHANNEL_INVALID(Channel)
#endif

#if (COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_ON)
#define STEP_4_CHANNEL_INVALID(Channel) \
            (STEP_3_CHANNEL_INVALID(Channel) || (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_SLAVE_ACTIVE_VARIANT))
#else
#define STEP_4_CHANNEL_INVALID(Channel) STEP_3_CHANNEL_INVALID(Channel)
#endif

#if (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_ON)
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00667.Nm_NetworkRequest,1 */
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.SLAVE_ACTIVE,1 */
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.SLAVE_PASSIVE,1 */
#define COMM_IS_CHANNEL_INVALID(Channel) \
            (STEP_4_CHANNEL_INVALID(Channel) || (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_SLAVE_PASSIVE_VARIANT))
#else
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00667.Nm_NetworkRequest,1 */
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.SLAVE_ACTIVE,1 */
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.SLAVE_PASSIVE,1 */
#define COMM_IS_CHANNEL_INVALID(Channel) STEP_4_CHANNEL_INVALID(Channel)
#endif

#if (defined COMM_IS_RX_EIRA)
#error COMM_IS_RX_EIRA already defined
#endif
#define COMM_IS_RX_EIRA 0U

#if (defined COMM_IS_RX_ACTIVE_ERA)
#error COMM_IS_RX_ACTIVE_ERA already defined
#endif
#define COMM_IS_RX_ACTIVE_ERA 1U

#if (defined COMM_IS_RX_UNFILTERED_ERA)
#error COMM_IS_RX_UNFILTERED_ERA already defined
#endif
#define COMM_IS_RX_UNFILTERED_ERA 2U
/*==================[type definitions]======================================*/

/** \brief Function pointer type for the bus state manager functions to
 ** query the current communication mode. */
typedef P2FUNC(Std_ReturnType, COMM_APPL_CODE, ComM_BusSMGetCurrentComModeType)
(
  NetworkHandleType                       Channel,
  P2VAR(uint8, AUTOMATIC, COMM_APPL_DATA) ComMode
);


/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>
#if (COMM_PNC_SUPPORT == STD_ON)
#if (COMM_NUM_USERS != 0U)
/** \brief Handles evaluate PNC for specific user
 **
 ** This function calls evaluate PNC for user specified by input parameter with ComM mode
 ** specified also by input parameter
 **
 ** \param[in]     User (specifies the user for which pncs the evaluate pnc shall be called)
 ** \param[in]     ComMode (specifies the the communication mode for which pncs the evaluate pnc shallbe called)
 **
 */
STATIC FUNC(void, COMM_CODE) ComM_RequestComModePNC_Helper
(
  ComM_ASR40_UserHandleType User
);
#endif /* #if (COMM_NUM_USERS != 0U) */

/** \brief Updates Rx(EIRA/ERA) arrays
 **
 ** This functions emits PNC state machine events based on SignalMergedPtr and RxEiraMerged
 **
 ** \param[in] SignalMergedPtr received EIRA or ERA merged (RxEira, RxEra)
 ** \param[in,out] RxEiraMerged Contains temporary ERA, EIRA information
 ** \param[in]     SignaleKind Is EIRA or ERA active or ERA passive signal set is processed (EIRA if isEira is set to true)
 */
STATIC FUNC(void, COMM_CODE) ComM_ProcessPncComSignals_EmitEvents
(
  P2CONST(uint8, AUTOMATIC, COMM_APPL_DATA) SignalMergedPtr,
  P2CONST(uint8, AUTOMATIC, COMM_APPL_CONST) RxEiraMerged,
  uint8 SignalKind
);
/** \brief Updates Rx(EIRA/ERA) arrays
 **
 ** This functions reads the RX signal values from Com and updates RxEira or RxEra arrays
 **
 ** \param[in,out] SignalStatusPtr notification if EIRA or ERA RX signals where updated
 ** \param[in]     ComM_RxSignal_Struct_Type List of EIRA or ERA RX signals
 ** \param[in,out] SignalMergedPtr received EIRA or ERA merged (RxEira, RxEra)
 ** \param[in]     SignaleKind Is EIRA or ERA active or ERA passive signal set is processed (EIRA if isEira is set to true)
 */
STATIC FUNC(void, COMM_CODE) ComM_ProcessPncComSignals
(
  P2VAR(boolean, AUTOMATIC, COMM_APPL_DATA) SignalStatusPtr,
  P2CONST(ComM_RxSignal_Struct_Type, AUTOMATIC, COMM_APPL_CONST) SignalConfigurationPtr,
  P2VAR(uint8, AUTOMATIC, COMM_APPL_DATA) SignalMergedPtr,
  uint8 SignalKind
);

/** \brief Handle EcuM PNC wakeup indication
 **
 ** This functions handle PNC wakeup indication following a EcuM PNC wakeup request.
 **
 ** \param[in] Index of the PNC for which wakeup indication was received.
 */
STATIC FUNC(void,COMM_CODE) ComM_PNCWakeUpIndication_PncHandle(PNCHandleType pncIdx);

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0)
/** \brief Call Schm functions for sending PNC information from Mater to Slave core */
STATIC FUNC(void, COMM_CODE) ComM_ProcessTxSignals(void);
#endif /* #if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0) */
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (COMM_NO_OF_TX_BUFFERS != 0)
  /** \brief Call Schm functions for sending PNC information from Mater to Slave core */
STATIC FUNC(void, COMM_CODE) ComM_ProcessTxSignals(void);
#endif /* #if (COMM_NO_OF_TX_BUFFERS != 0) */
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
STATIC FUNC(void, COMM_CODE) ComM_Internal_CopySynchronizedPncShutdownInfo(void);
STATIC FUNC(void, COMM_CODE) ComM_InitSynchronusShutDownVars(void);
STATIC FUNC(void, COMM_CODE) ComM_Internal_ForwardSynchronizedPncShutdown(void);
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
        */
#endif /*#if (COMM_PNC_SUPPORT == STD_ON)*/
#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*==================[external constants]====================================*/

#define COMM_START_SEC_CONST_8
#include <ComM_MemMap.h>

#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON)
CONST(uint8, COMM_CONST) ComM_BusTypeOfChannel[COMM_NUM_CHANNELS]
  = COMM_BUSTYPE_OF_CHANNEL_INIT;
#endif

#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
CONST(uint8, COMM_CONST) ComM_NmVariantOfChannel[COMM_NUM_CHANNELS]
  = COMM_NM_VARIANT_OF_CHANNEL_INIT;
#endif

#define COMM_STOP_SEC_CONST_8
#include <ComM_MemMap.h>

/*==================[internal constants]====================================*/
#if ((COMM_MULTICORE_ENABLED == STD_OFF) && (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF))
#if (COMM_NUM_USERS != 0U)

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

/** \brief Stores function pointer for bus specific state managers **/
/* Deviation MISRAC2012-2 */
STATIC CONST(ComM_BusSMGetCurrentComModeType, COMM_CONST)
  ComM_BusSMGetCurrentComModeFpList[5] =
{
#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00855,1, ComM.EB_Ref.SWS_ComM_00962.CanSM,1 */
  &CanSM_GetCurrentComMode,      /* COMM_BUS_TYPE_CAN = 0 */
#else
  NULL_PTR,                /* never accessed if no CAN channel is available */
#endif
#if (COMM_ETHSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00860,1, ComM.EB_Ref.SWS_ComM_00962.EthSM,1 */
  &EthSM_GetCurrentComMode,      /* COMM_BUS_TYPE_ETH = 1 */
#else
  NULL_PTR,                /* never accessed if no CAN channel is available */
#endif
#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00853,1, ComM.EB_Ref.SWS_ComM_00962.FrSM,1 */
  &FrSM_GetCurrentComMode,       /* COMM_BUS_TYPE_FR = 2 */
#else
  NULL_PTR,                 /* never accessed if no FR channel is available */
#endif
  NULL_PTR,                   /* COMM_BUS_TYPE_INTERNAL = 3 */
#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00857,1, ComM.EB_Ref.SWS_ComM_00962.LinSM,1 */
  &LinSM_GetCurrentComMode      /* COMM_BUS_TYPE_LIN = 4 */
#else
  NULL_PTR                /* never accessed if no LIN channel is available */
#endif
};

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

#endif
#endif /*#if ((COMM_MULTICORE_ENABLED == STD_OFF) && (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)) */

/*==================[external data]=========================================*/

#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>

#if (COMM_DCM_ENABLED == STD_ON)
VAR(boolean, COMM_VAR)         ComM_DcmActiveStatus[COMM_NUM_CHANNELS];
#endif /* if (COMM_DCM_ENABLED == STD_ON) */

VAR(boolean, COMM_VAR) ComM_Communication_Allowed[COMM_NUM_CHANNELS];

VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_RequestedComMode[COMM_NUM_CHANNELS];

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
VAR(boolean, COMM_VAR)   ComM_PassiveExecuted[COMM_NUM_CHANNELS];
#endif /* #if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) */

#if (COMM_PNC_GW_ENABLED == STD_ON)
VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_RequestedComModeWithoutPnc[COMM_NUM_CHANNELS];
#endif /* COMM_PNC_GW_ENABLED == STD_ON) */

#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)
VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_RequestedComModeWakeupSleepRequest[COMM_NUM_CHANNELS];
#endif /* #if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON) */

VAR(boolean, COMM_VAR) ComM_PassiveStartupStatus[COMM_NUM_CHANNELS];

VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_ChannelMode[COMM_NUM_CHANNELS];

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_ChannelModePrevious[COMM_NUM_CHANNELS];
#endif

VAR(ComM_StateType, COMM_VAR)  ComM_ChanState[COMM_NUM_CHANNELS];

VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_UserRequestedComMode[USER_ARRAY_SIZE];


#if (COMM_PNC_SUPPORT == STD_ON)
VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_PNCRequestedComMode[COMM_NUM_PNC];

VAR(uint8, COMM_VAR) ComM_PNCState[COMM_NUM_PNC];

#if (COMM_0_PNC_VECTOR_AVOIDANCE == STD_ON)
VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_PNCRequestedComMode0PncVectorAvoidance[COMM_NUM_PNC];
#endif

/* !LINKSTO ComM.SWS_ComM_00982,1 */
VAR(uint8, COMM_VAR) ComM_TxEiraEraActive[COMM_PN_INFO_LENGTH];
#if (COMM_NUM_RX_EIRA_SIGNALS > 0)
VAR(uint8, COMM_VAR) ComM_RxEira[COMM_PN_INFO_LENGTH];
#endif /* #if (COMM_NUM_RX_EIRA_SIGNALS > 0) */
#if(COMM_PNC_GW_ENABLED == STD_ON)
VAR(uint8, COMM_VAR) ComM_RxActiveEra[COMM_PN_INFO_LENGTH];
VAR(uint8, COMM_VAR) ComM_RxUnfilteredEra[COMM_PN_INFO_LENGTH];
VAR(uint8, COMM_VAR) ComM_TxEraPassive[COMM_PN_INFO_LENGTH];
#endif

#if (COMM_NUM_RX_EIRA_SIGNALS > 0)
VAR(boolean, COMM_VAR) ComM_RxEiraSignalStatus;
#endif /*#if (COMM_NUM_RX_EIRA_SIGNALS > 0)*/
#if(COMM_PNC_GW_ENABLED == STD_ON)
VAR(boolean, COMM_VAR) ComM_RxActiveEraSignalStatus;
VAR(boolean, COMM_VAR) ComM_RxUnfilteredEraSignalStatus;
#endif
VAR(ComM_PncModeType, COMM_VAR)   ComM_PncStateUserRequest[COMM_PN_INFO_LENGTH];


#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0)
VAR(uint8, COMM_VAR) ComM_MulticoreTxBuffer[COMM_MULTICORE_NO_OF_TX_BUFFERS][COMM_PN_INFO_LENGTH];
VAR(boolean, COMM_VAR) ComM_MulticoreTxBufferStatus[COMM_MULTICORE_NO_OF_TX_BUFFERS];
#endif /* #if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0) */
#if (COMM_MULTICORE_NO_OF_RX_BUFFERS != 0)
VAR(uint8, COMM_VAR) ComM_MulticoreRxBuffer[COMM_MULTICORE_NO_OF_RX_BUFFERS][COMM_PN_INFO_LENGTH];
#endif /* #if (COMM_MULTICORE_NO_OF_RX_BUFFERS != 0) */
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (COMM_NO_OF_TX_BUFFERS != 0)
VAR(uint8, COMM_VAR) ComM_MulticoreTxBuffer[COMM_NO_OF_TX_BUFFERS][COMM_PN_INFO_LENGTH];
VAR(boolean, COMM_VAR) ComM_MulticoreTxBufferStatus[COMM_NO_OF_TX_BUFFERS];
#endif /* #if (COMM_NO_OF_TX_BUFFERS != 0) */
#if (COMM_NO_OF_RX_BUFFERS != 0)
VAR(uint8, COMM_VAR) ComM_MulticoreRxBuffer[COMM_NO_OF_RX_BUFFERS][COMM_PN_INFO_LENGTH];
#endif /* #if (COMM_NO_OF_RX_BUFFERS != 0) */
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#endif /* if (COMM_PNC_SUPPORT == STD_ON) */

#if (COMM_INCLUDE_RTE == STD_ON)
VAR(boolean, COMM_VAR) ComM_RteNotificationSuccessful[USER_ARRAY_SIZE];

#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */
#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
VAR(uint8, COMM_VAR) ComM_SynchronusShutDownArr[COMM_PN_INFO_LENGTH];
STATIC VAR(uint8, COMM_VAR) ComM_SynchronusShutDownArrLocal[COMM_PN_INFO_LENGTH];
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE_COUNT == STD_ON))
        */
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON))
VAR(uint8, COMM_VAR) ComM_BusSmModeToReport[COMM_NUM_CHANNELS];
#endif /*#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON))*/
#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>

#define COMM_START_SEC_VAR_INIT_8
#include <ComM_MemMap.h>

VAR(ComM_InitStatusType, COMM_VAR) ComM_InitStatus = COMM_UNINIT;

#define COMM_STOP_SEC_VAR_INIT_8
#include <ComM_MemMap.h>


#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>

VAR(ComM_NvDataType, COMM_VAR_POWER_ON_CLEARED) ComM_EB_NvRAM;

#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>

#endif

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>

P2CONST(ComM_ConfigType,AUTOMATIC,COMM_APPL_CONST) ComM_ConfigPtr;

#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_NM_ACCESS_NEEDED == STD_ON))
VAR(Nm_ModeType, COMM_VAR) ComM_LastNmMode[COMM_NUM_CHANNELS];
#endif

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
VAR(ComM_DoActionType, COMM_VAR) ComM_RteNotificationDoActFkp;

#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */

#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0)
/** \brief Multicore channel to master pnc function pointer index list */
STATIC VAR(ComM_SynchShutDown_Ch_To_MasterPnc_DataType, COMM_VAR) ComM_SynchShutDownChToMasterPncData[COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH];

#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
        */

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
/** \brief Multicore Master pnc to channel data status buffer */
VAR(boolean, COMM_VAR) ComM_EvaluateChannel_MasterPnc_To_Ch_Status[COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH];
#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
#endif /*  #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
/** \brief Multicore Master pnc to channel data status buffer */
VAR(boolean, COMM_VAR) ComM_SynchShutDown_MasterPnc_To_Ch_Status[COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH];
#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */

#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
/** \brief Multicore Master pnc to channel data */
VAR(ComM_EvaluateChannel_MasterPnc_To_Ch_DataType, COMM_VAR) ComM_EvaluateChannel_MasterPnc_To_Ch;
#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
#endif /*  #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
/** \brief Multicore Master pnc to channel data */
VAR(ComM_SynchShutDown_MasterPnc_To_Ch_DataType, COMM_VAR) ComM_SynchShutDown_MasterPnc_To_Ch;
#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ComM_MemMap.h>
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

/*==================[internal data]=========================================*/

#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Array to store NoCom Inhibition status of ComM Channels. */
STATIC VAR(uint8, COMM_VAR) ComM_ChannelNoComInhibition[COMM_NUM_BYTES_NVM];
#endif

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
#if (COMM_PNC_SUPPORT == STD_ON)
/* Deviation MISRAC2012-2 */
STATIC volatile VAR(boolean,COMM_VAR) ComMPncMainfunctionRunning;
#endif /* #if (COMM_PNC_SUPPORT == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */


#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief Array to store WakeUp Inhibition status of ComM Channels. */
STATIC VAR(uint8, COMM_VAR) ComM_ChannelWakeUpInhibition[COMM_NUM_BYTES_NVM];
#endif

#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>

/*==================[external function definitions]=========================*/

#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>

#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
STATIC FUNC(void, COMM_CODE) ComM_InitSynchronusShutDownVars(void)
{
  uint8 idx1;
  for (idx1 = 0; idx1 < COMM_PN_INFO_LENGTH; idx1++)
  {
    ComM_SynchronusShutDownArr[idx1] = 0;
    ComM_SynchronusShutDownArrLocal[idx1] = 0;
  }

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0)
  for (idx1 = 0; idx1 < COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH; idx1++)
  {
    uint8 idx2;
    for (idx2 = 0; idx2 < COMM_PN_INFO_LENGTH; idx2++)
    {
      ComM_SynchShutDownChToMasterPncData[idx1].PnInfo[idx2] = 0U;
    }
  }
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
}
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
        */
/*------------------[ComM_Init]----------------------------------------------*/
/* !LINKSTO ComM.SWS_ComM_00146,1, ComM.SWS_ComM_00927,1 */
FUNC(void, COMM_CODE) ComM_Init
(
  P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST) ConfigPtr
)
{
  uint8_least i;
  P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST) LocalConfigPtr = ConfigPtr;

  DBG_COMM_INIT_ENTRY(ConfigPtr);

  /* Post Build Initializations */
/* !LINKSTO ComM.EB.PB.Impl.PbCfgM,1 */
#if ( COMM_PBCFGM_SUPPORT_ENABLED == STD_ON )
  if (LocalConfigPtr == NULL_PTR)
  {
    PbcfgM_ModuleConfigPtrType ModuleConfig = NULL_PTR;
    if (E_OK == PbcfgM_GetConfig( COMM_MODULE_ID, COMM_INSTANCE_ID, &ModuleConfig))
    {
      LocalConfigPtr = (P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST)) ModuleConfig;
    }
  }
#endif

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check whether parameter LocalConfigPtr is a NULL_PTR or invalid */
  if (LocalConfigPtr == NULL_PTR)
  {
    /* Found a NULL_PTR, report to DET */
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_INIT, COMM_E_WRONG_PARAMETERS);
  }
  else if (E_OK != ComM_IsValidConfig(LocalConfigPtr))
  {
    /* Check that configuration pointer is valid. */
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_INIT, COMM_E_WRONG_PARAMETERS);
  }
  else
#else
  /* !LINKSTO ComM.EB.ComM_Init_NULL_PTR,1 */
  if(ComM_IsValidConfig(LocalConfigPtr) == E_OK)
#endif /* COMM_DEV_ERROR_DETECT */
  {
    /* Initialize module */

    /* Set the pointer to the post-build configuration */
    ComM_ConfigPtr = LocalConfigPtr;

    /* Pre Compile Initializations */
    /* Deviation TASKING-1 */
    for (i = 0U; i < COMM_NUM_CHANNELS; ++i)
    {
      /* Requested communication mode for each channel */
      /* !LINKSTO ComM.SWS_ComM_00485,1 */
      ComM_RequestedComMode[i]    = COMM_NO_COMMUNICATION;
      /* Initialize ComM Channel State */
      ComM_ChanState[i]          = COMM_NO_COM_NO_PENDING_REQUEST;
      /* Initialize ComM Channel Mode */
      ComM_ChannelMode[i]         = COMM_NO_COMMUNICATION;
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
      ComM_ChannelModePrevious[i] = COMM_NO_COMMUNICATION;
#endif
#if (COMM_PNC_GW_ENABLED == STD_ON)
      ComM_RequestedComModeWithoutPnc[i] = COMM_NO_COMMUNICATION;
#endif /* COMM_PNC_GW_ENABLED == STD_ON) */
#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)
      ComM_RequestedComModeWakeupSleepRequest[i] = COMM_NO_COMMUNICATION;
#endif /* #if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON) */
      /* The persistent storage is supported we don't
       * to react on a NvM callback after the initialization as the
       * the Read All and Write All will called in EcuM_Init(). */
    }
    /* !LINKSTO ComM.SWS_ComM_00313,1 */
    /* Requested communication mode of each user */
    TS_MemSet(ComM_UserRequestedComMode, COMM_NO_COMMUNICATION, USER_ARRAY_SIZE);

    /* Initialize ComM state machine, perform initial transitions */
    ComM_HsmInit(&ComM_HsmScComM);

    /* Initializing the Channel communication status and Dcm request status */
    /* Deviation TASKING-1 */
    for (i = 0U; i < COMM_NUM_CHANNELS; ++i)
    {
      ComM_Communication_Allowed[i] = FALSE;
#if (COMM_DCM_ENABLED == STD_ON)
      ComM_DcmActiveStatus[i] = FALSE;
#endif
      ComM_PassiveStartupStatus[i] = FALSE;
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
      ComM_PassiveExecuted[i] = FALSE;
#endif /* #if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) */
    }

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))

  /* The persistent storage is supported we don't need
   * to react on a NvM callback after the initialization as the
   * the Read All and Write All will be called in EcuM_Init().
   */

/* !LINKSTO ComM.SWS_ComM_00864,1 */
#if (COMM_NVM_ENABLED == STD_OFF)
    /* NvM storage disabled, re-initialize RAM data */
    ComM_EB_NvRAM = ComM_EB_NvROM;
#endif

    /* Initializing the Channel Inhibition status */
    /* Deviation TASKING-1 */
    for (i = 0U; i < COMM_NUM_BYTES_NVM; ++i)
    {

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
      ComM_ChannelNoComInhibition[i] = ComM_ChannelInhibitionStatusInit[i];
#endif

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
      ComM_ChannelWakeUpInhibition[i] = ComM_EB_NvRAM.ChannelWakeUpInhibition[i];
#endif
    }
#endif
#if (COMM_PNC_SUPPORT == STD_ON)
    if( COMM_PNC_ENABLED )
    {
      /* Initializing the pnc */
      ComM_HsmInit(&ComM_HsmScComMPnc);

      /* Deviation TASKING-1 */
      for (i = 0U; i < COMM_PN_INFO_LENGTH; i++)
      {
#if(COMM_PNC_GW_ENABLED == STD_ON)
        ComM_RxActiveEra[i] = 0U;
        ComM_RxUnfilteredEra[i] = 0U;
        ComM_TxEraPassive[i] = 0U;
#endif
#if (COMM_NUM_RX_EIRA_SIGNALS > 0)
        ComM_RxEira[i] = 0U;
#endif /*#if (COMM_NUM_RX_EIRA_SIGNALS > 0)*/
        ComM_TxEiraEraActive[i] = 0U;
      }
#if (COMM_NUM_RX_EIRA_SIGNALS > 0)
      ComM_RxEiraSignalStatus = FALSE;
#endif /*#if (COMM_NUM_RX_EIRA_SIGNALS > 0)*/
#if(COMM_PNC_GW_ENABLED == STD_ON)
      ComM_RxActiveEraSignalStatus = FALSE;
      ComM_RxUnfilteredEraSignalStatus = FALSE;
#endif
      /* Deviation TASKING-1 */
      for (i = 0U; i < COMM_PN_INFO_LENGTH; ++i)
      {
        ComM_PncStateUserRequest[i] = 0U;
      }

      TS_MemSet(ComM_PNCRequestedComMode, COMM_NO_COMMUNICATION, COMM_NUM_PNC * sizeof(ComM_ASR40_ModeType));
      TS_MemSet(ComM_PNCState, PNC_NO_COMMUNICATION, COMM_NUM_PNC * sizeof(uint8));

#if(COMM_0_PNC_VECTOR_AVOIDANCE == STD_ON)
      TS_MemSet(ComM_PNCRequestedComMode0PncVectorAvoidance, COMM_NO_COMMUNICATION, COMM_NUM_PNC * sizeof(ComM_ASR40_ModeType));
#endif

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0)
      for(i = 0U; i < COMM_MULTICORE_NO_OF_TX_BUFFERS; i++)
      {
        uint8 j = 0U;
        for(j = 0U; j < COMM_PN_INFO_LENGTH; j++)
        {
          ComM_MulticoreTxBuffer[i][j] = 0U;
        }
        ComM_MulticoreTxBufferStatus[i] = FALSE;
      }
#endif /* #if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0) */
#if (COMM_MULTICORE_NO_OF_RX_BUFFERS != 0)
      for(i = 0U; i < COMM_MULTICORE_NO_OF_RX_BUFFERS; i++)
      {
        uint8 j = 0U;
        for(j = 0U; j < COMM_PN_INFO_LENGTH; j++)
        {
          ComM_MulticoreRxBuffer[i][j] = 0U;
        }
      }
#endif /* #if (COMM_NO_OF_RX_BUFFERS != 0) */
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (COMM_NO_OF_TX_BUFFERS != 0)
      for(i = 0U; i < COMM_NO_OF_TX_BUFFERS; i++)
      {
        uint8 j = 0U;
        for(j = 0U; j < COMM_PN_INFO_LENGTH; j++)
        {
          ComM_MulticoreTxBuffer[i][j] = 0U;
        }
        ComM_MulticoreTxBufferStatus[i] = FALSE;
      }
#endif /* #if (COMM_NO_OF_TX_BUFFERS != 0) */
#if (COMM_NO_OF_RX_BUFFERS != 0)
      for(i = 0U; i < COMM_NO_OF_RX_BUFFERS; i++)
      {
        uint8 j = 0U;
        for(j = 0U; j < COMM_PN_INFO_LENGTH; j++)
        {
          ComM_MulticoreRxBuffer[i][j] = 0U;
        }
      }
#endif /* #if (COMM_NO_OF_RX_BUFFERS != 0) */
#if (COMM_NM_ACCESS_NEEDED == STD_ON)
      for(i=0U;i<COMM_NUM_CHANNELS;i++)
      {
        ComM_LastNmMode[i] = NM_MODE_BUS_SLEEP;
      }
#endif /* #if (COMM_NM_ACCESS_NEEDED == STD_ON) */
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
    }
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
    ComMPncMainfunctionRunning = FALSE;
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */
#endif

#if ((COMM_INCLUDE_RTE == STD_ON) && (COMM_NUM_USERS != 0U))
    /* Deviation TASKING-1 */
    for (i = 0U; i < USER_ARRAY_SIZE; ++i)
    {
      ComM_RteNotificationSuccessful[i] = TRUE;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
    ComM_RteModeUser[i] = COMM_NO_COMMUNICATION;
#else /*(COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
#if (COMM_ENABLE_ASR32_SERVICE_API == STD_ON)
      ComM_ASR32_RteModeUser[i] = COMM_NO_COMMUNICATION;
#endif
#if (COMM_ENABLE_ASR40_SERVICE_API == STD_ON)
      ComM_ASR40_RteModeUser[i] = COMM_NO_COMMUNICATION;
#endif
#if (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE)
      ComM_RteModeUser[i] = COMM_NO_COMMUNICATION;
#endif
#endif /* (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
    }
#endif /* #if ((COMM_INCLUDE_RTE == STD_ON) && (COMM_NUM_USERS != 0U))*/

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
    ComM_RteNotificationDoActFkp = ComM_RteNotificationDoAction;
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */


#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
    ComM_InitSynchronusShutDownVars();
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
        */
    /* Set initialization status in global variable */
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON))
    for(i=0U;i<COMM_NUM_CHANNELS;i++)
    {
      ComM_BusSmModeToReport[i] = COMM_INVALID_COM_MODE;
    }
#endif /*#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON))*/

    ComM_InitStatus      = COMM_INIT;
  }

  DBG_COMM_INIT_EXIT(ConfigPtr);
}

/*------------------[ComM_DeInit]--------------------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00147,1, ComM.SWS_ComM_00794,1 */
FUNC(void, COMM_CODE) ComM_DeInit(void)
{
  uint8_least i;

  DBG_COMM_DEINIT_ENTRY();

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_DEINIT, COMM_E_NOT_INITED);
  }
  else
#endif
  {
    /* Check whether all the channels are in the 'NoCommunication' state */
    /* Deviation TASKING-1 */
    for (i = 0U; i < COMM_NUM_CHANNELS; i++)
    {
      /* get locally cached com mode, the BusSm of channels of BusType=Internal
       * cannot be queried */
      if (ComM_ChanState[i] != COMM_NO_COM_NO_PENDING_REQUEST)
      {
        break;
      }
    }

    /* De-init module only if all channels are in no communication state */
    if (COMM_NUM_CHANNELS == i)
    {
      /* deinit module global init status variable */
      ComM_InitStatus = COMM_UNINIT;
    }
  }

  DBG_COMM_DEINIT_EXIT();
}

/*------------------[ComM_GetState]-----------------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00872,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_GetState
(
  NetworkHandleType                                Channel,
  P2VAR(ComM_StateType, AUTOMATIC, COMM_APPL_DATA) State
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif

  DBG_COMM_GETSTATE_ENTRY(Channel,State);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_STATE, COMM_E_NOT_INITED);
    /* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00649.COMM_E_UNINIT,1 */
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == State) || (Channel >= COMM_NUM_CHANNELS))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_STATE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_PRECONDITION_ASSERT_ENABLED == STD_ON)
    COMM_PRECONDITION_ASSERT((ComM_ChanState[Channel] <= COMM_SILENT_COM),COMM_SID_GET_STATE);
#endif

    *State = ComM_ChanState[Channel];
    RetVal = E_OK;
  }

  DBG_COMM_GETSTATE_EXIT(RetVal,Channel,State);

  return RetVal;
}

/*------------------[ComM_GetStatus]-----------------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00242,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_GetStatus
(
  P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_APPL_DATA) Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_GETSTATUS_ENTRY(Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == Status)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_STATUS, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {

#if (COMM_PRECONDITION_ASSERT_ENABLED == STD_ON)
    COMM_PRECONDITION_ASSERT((ComM_InitStatus <= COMM_INIT),COMM_SID_GET_STATUS);
#endif
    *Status = ComM_InitStatus;
    RetVal = E_OK;
  }

  DBG_COMM_GETSTATUS_EXIT(RetVal,Status);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetInhibitionStatus]-------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1, ComM.SWS_ComM_00488,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetInhibitionStatus
(
  NetworkHandleType                                           Channel,
  P2VAR(ComM_ASR32_InhibitionStatusType, AUTOMATIC, COMM_APPL_DATA) Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETINHIBITIONSTATUS_ENTRY(Channel,Status);

  RetVal = ComM_ASR40_GetInhibitionStatus(Channel, Status);

  DBG_COMM_ASR32_GETINHIBITIONSTATUS_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_GetInhibitionStatus]-------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00619,1, ComM.SWS_ComM_00488,1, ComM.SWS_ComM_00182,1 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetInhibitionStatus
(
  NetworkHandleType                                           Channel,
  P2VAR(ComM_ASR40_InhibitionStatusType, AUTOMATIC, COMM_APPL_DATA) Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  ComM_ASR40_InhibitionStatusType ChannelInhibitionStatus = 0U;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_GETINHIBITIONSTATUS_ENTRY(Channel,Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_INHIBITION_STATUS, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == Status) || (Channel >= COMM_NUM_CHANNELS))
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_GET_INHIBITION_STATUS, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    /* assemble bit encoded channel inhibition status */
    if (TRUE == ComM_ChannelWakeUpInhibitionStatus(Channel))
    {
      ChannelInhibitionStatus |= COMM_PREVENT_WAKEUP;
    }
#endif
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
    if (TRUE == ComM_ChannelNoComInhibitionStatus(Channel))
    {
      ChannelInhibitionStatus |= COMM_LIMIT_NOCOMM;
    }
#endif

    *Status = ChannelInhibitionStatus;
    RetVal  = E_OK;
  }

  DBG_COMM_ASR40_GETINHIBITIONSTATUS_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_RequestComMode]------------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_RequestComMode
(
  ComM_ASR32_UserHandleType User,
  ComM_ASR32_ModeType       ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_REQUESTCOMMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_RequestComMode(User, ComMode);

  DBG_COMM_ASR32_REQUESTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}
#endif

#if (COMM_NUM_USERS != 0U)
#if (COMM_PNC_SUPPORT == STD_ON)
STATIC FUNC(void, COMM_CODE) ComM_RequestComModePNC_Helper
(
  ComM_ASR40_UserHandleType User
)
{
  PNCHandleType PncPos;
  if( COMM_PNC_ENABLED )
  {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_USER_TO_MASTER_PNC_FCTPTR_LENGTH != 0)
    if (ComM_Multicore_UserToMasterPncSchmSend_FctPtr_IndexList[User] != COMM_MULTICORE_INVALID_FCT_INDEX)
    {
      ComM_User_To_MasterPnc_DataType UserToMasterPncData;
      UserToMasterPncData.User = User;
      UserToMasterPncData.Operation = COMM_MULTICORE_EVALUATE_PNC;
      /* !LINKSTO ComM.EB.UserToMasterPncCrossPartition,1 */
      if (ComM_Multicore_UserToMasterPncSchmSend_FctPtr_List[ComM_Multicore_UserToMasterPncSchmSend_FctPtr_IndexList[User]](&UserToMasterPncData) != SCHM_E_OK)
      {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO ComM.EB.UserToMasterPncDataSetError,1 */
        COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_REQUEST_COM_MODE, COMM_E_USER_TO_MASTERPNC_DATASET_ERROR);
#endif
      }
    }
    else
#endif /*#if (COMM_OS_APPLICATION_USER_TO_MASTER_PNC_FCTPTR_LENGTH != 0)*/
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
    {
      for (PncPos = 0U; PncPos < COMM_NUM_PNCS_OF_USER(User); PncPos++)
      {
        const PNCHandleType Pnc = COMM_PNC_OF_USER(User,PncPos);
        /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_RequestComMode_NO_COM_REQ_BY_ALL_COMM_USER,1 */
        ComM_EvaluatePnc(Pnc);
      }
    }
  }
}
#endif /*#if (COMM_PNC_SUPPORT == STD_ON) */

FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModeChannel_Helper
(
  ComM_ASR40_UserHandleType User,
  boolean isUserContext
)
{
  Std_ReturnType RetVal = E_OK;
  uint8_least ChannelPos;

#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0))
  boolean SentToApplication[COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH];
#endif /* ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  ApplicationType CurrentApplication = GetApplicationID();
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(isUserContext);
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */

#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0))
  TS_MemSet(SentToApplication, FALSE, COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH);
#endif /* ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)) */

  /* Get all channels for a specific user and set ComMode  */
  for (ChannelPos = 0U; ChannelPos < COMM_NUM_CHANNELS_OF_USER(User); ChannelPos++)
  {
    const uint8 Channel = COMM_CHANNEL_OF_USER(User,ChannelPos);
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
    boolean execute = FALSE;
    if ((CurrentApplication == ComM_Multicore_ChannelOsApplication_List[Channel]) && (isUserContext == FALSE))
    {
      execute = TRUE;
    }
    if (isUserContext == TRUE)
    {
      execute = TRUE;
    }
    if (execute == TRUE)
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
    {
      boolean EmitEventReqStatusChanged = TRUE;
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)  || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
      boolean InhibitionStatus = FALSE;
#endif
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
      ComM_StateType ComM_ChanState_local = ComM_ChanState[Channel];
#endif
      if (COMM_FULL_COMMUNICATION == ComM_UserRequestedComMode[User])
      {
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
        if (TRUE == ComM_ChannelNoComInhibitionStatus(Channel))
        {
          InhibitionStatus = TRUE;
        }
#endif
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
        if ((TRUE == ComM_ChannelWakeUpInhibitionStatus(Channel)) &&
            /* !LINKSTO ComM.SWS_ComM_00842,1 */
            ((COMM_FULL_COM_NETWORK_REQUESTED >  ComM_ChanState_local) ||
             (COMM_SILENT_COM                 == ComM_ChanState_local)
            )
           )
        {
          InhibitionStatus = TRUE;
        }
#endif
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
        /* Inhibit user request if "Limit to No Comm Mode" is on OR "Wake up
         * inhibition" is on, AND current user state is No Comm */
        if ((TRUE == InhibitionStatus) && (isUserContext == TRUE))
        {
          boolean Call_ComMPersDataModified = FALSE;
          /* Return COMM_E_MODE_LIMITATION when inhibition is enabled for
           * any channel of a user */
          /* !LINKSTO ComM.EB_Ref.SWS_ComM_00649.COMM_E_MODE_LIMITATION,1 */
          RetVal = COMM_E_MODE_LIMITATION;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_USER_TO_INHIBITION_PNC_FCTPTR_LENGTH != 0)
          if (ComM_Multicore_UserToInhibitionSchmSend_FctPtr_IndexList[User] != COMM_MULTICORE_INVALID_FCT_INDEX)
          {
            uint8 dummyByte = 0;
            /* !LINKSTO ComM.EB.UserToInhibitionCrossPartition,1 */
            if (ComM_Multicore_UserToInhibitonSchmSend_FctPtr_List[ComM_Multicore_UserToInhibitionSchmSend_FctPtr_IndexList[User]](dummyByte) != SCHM_E_OK)
            {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO ComM.EB.UserToInhibitionDataSetError,1 */
              COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_REQUEST_COM_MODE, COMM_E_USER_TO_INHIBITION_DATASET_ERROR);
#endif
            }
          }
          else
#endif /*#if (COMM_OS_APPLICATION_USER_TO_INHIBITION_PNC_FCTPTR_LENGTH != 0)*/
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
          {
            COMM_USER_ENTER_EXCLUSIVE_AREA(User);
            if(ComM_EB_NvRAM.InhibitionCounter < 0xFFFFU)
            {
              ComM_EB_NvRAM.InhibitionCounter++;
              Call_ComMPersDataModified = TRUE;
            }
            COMM_USER_EXIT_EXCLUSIVE_AREA(User);
            if (Call_ComMPersDataModified == TRUE)
            {
              COMM_PERS_DATA_MODIFIED();
            }
          }
        }
        else
#endif
        {
          /* Do Nothing */
        }
      }
      else
      {
        /* Do Nothing */
      }
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)  || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
      if (InhibitionStatus == TRUE)
      {
        /* Do not emit event 'REQ_STATUS_CHANGED' if inhibition is active */
        EmitEventReqStatusChanged = FALSE;
      }
#endif /* #if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)  || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)
      if ((ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel] != COMM_MULTICORE_INVALID_FCT_INDEX) && (isUserContext == TRUE))
      {
        if (SentToApplication[ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel]] == FALSE)
        {
          ComM_User_To_Ch_DataType UserToChData;
          UserToChData.User = User;
          UserToChData.Operation = COMM_MULTICORE_CHANNEL_EVALUATE_CHANNEL_AND_EMIT_REQ_STATUS_CHANGED;
          /* !LINKSTO ComM.EB.UserToChannelCrossPartition,1 */
          if (ComM_Multicore_UserToChSchmSend_FctPtr_List[ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel]](&UserToChData) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO ComM.EB.UserToChannelDataSetError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_REQUEST_COM_MODE, COMM_E_USER_TO_CH_DATASET_ERROR);
#endif
          }
          SentToApplication[ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel]] = TRUE;
        }
      }
      else
#endif /*#if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)*/
#endif/*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
      {
        ComM_EvaluateChannel(Channel);
        /* Emit event 'REQ_STATUS_CHANGED' if request is accepted
         * and the user is directly mapped to
         * the channel. If the user is indirectly mapped to this channel via a PNC, it is up to the
         * PNC to request the appropriate mode.
         * The channels in the array ComM_ChannelsOfUser are ordered, so that directly mapped channels
         * are located before indirectly (via PNC) mapped channels.
         */
         /* Deviation TASKING-2 */
#pragma warning 549
        if ((TRUE == EmitEventReqStatusChanged) && (COMM_DIRECT_NUM_CHANNELS_OF_USER(User) > ChannelPos))
#pragma warning default
        {
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_RequestComMode_REQ_STATUS_CHANGED,1 */
          COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
        }
      }
    }
  }
  return RetVal;
}
#endif /*#if (COMM_NUM_USERS != 0U)*/

/*------------------[ComM_RequestComMode]------------------------------------*/
/* !LINKSTO ComM.EB.SWS_ComM_00110,1, ComM.ASR32.ComM110,1, ComM.SWS_ComM_00978,1, ComM.SWS_ComM_00972,1, ComM.EB_Ref.SWS_ComM_00218.NOCOM,1, ComM.SWS_ComM_00151,1 */
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00218.SILENTCOM,1, ComM.SWS_ComM_00848,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_RequestComMode
(
  ComM_ASR40_UserHandleType User,
  ComM_ASR40_ModeType       ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_REQUESTCOMMODE_ENTRY(User,ComMode);
#if (COMM_NUM_USERS == 0U)
  TS_PARAM_UNUSED(User);
  TS_PARAM_UNUSED(ComMode);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_REQUEST_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_REQUEST_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
#endif
#else /* #if (COMM_NUM_USERS == 0U) */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_REQUEST_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (User >= COMM_NUM_USERS)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_REQUEST_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else if ((ComMode != COMM_NO_COMMUNICATION) && (ComMode != COMM_FULL_COMMUNICATION))
  {
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00151.DetReport.WrongComModeReq,1 */
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_REQUEST_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* The SchM functions can't be called direct because it's not possible
       to include the Rte files here. Thus the SchM wrapper functions from
       the Rte specific compilation unit must be called. */
    /* store user requested mode */
    ComM_UserRequestedComMode[User] = ComMode;

#if (COMM_PNC_SUPPORT == STD_ON)
    ComM_RequestComModePNC_Helper(User);
#endif /* #if (COMM_PNC_SUPPORT == STD_ON) */
    RetVal = ComM_RequestComModeChannel_Helper(User, TRUE);
  }
#endif /* #if (COMM_NUM_USERS == 0U) */
  DBG_COMM_ASR40_REQUESTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetMaxComMode]-------------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetMaxComMode
(
  ComM_ASR32_UserHandleType                             User,
  P2VAR(ComM_ASR32_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETMAXCOMMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_GetMaxComMode(User, ComMode);

  DBG_COMM_ASR32_GETMAXCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}
#endif

/*------------------[ComM_GetMaxComMode]-------------------------------------*/
/* !LINKSTO ComM.SWS_ComM_00686,1, ComM.ASR403.SWS_ComM_00085,1, ComM.SWS_ComM_00374,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetMaxComMode
(
  ComM_ASR40_UserHandleType                             User,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_NUM_USERS != 0U)
  uint8_least i;
  uint8 Channel;
  boolean comAllowed = FALSE;
#endif
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif

  DBG_COMM_ASR40_GETMAXCOMMODE_ENTRY(User,ComMode);
#if (COMM_NUM_USERS == 0U)
  TS_PARAM_UNUSED(User);
  TS_PARAM_UNUSED(ComMode);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    /* !LINKSTO ComM.ASR403.SWS_ComM_00858,1 */
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_MAX_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_MAX_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
#endif
#else /* #if (COMM_NUM_USERS == 0U) */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    /* !LINKSTO ComM.ASR403.SWS_ComM_00858,1 */
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_MAX_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == ComMode) || (User >= COMM_NUM_USERS))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_MAX_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    ComM_StateType ComM_ChanState_local;
    /* Check for limitations, see extended functionality */
    *ComMode = COMM_FULL_COMMUNICATION;

    /* Get all channels for a specific user and check for
     * limitations/inhibitions */
    for (i = 0U; i < COMM_NUM_CHANNELS_OF_USER(User); i++)
    {
      boolean NoComInhibitionStatus = FALSE;
      boolean WkUpInhibitionStatus = FALSE;

      Channel = COMM_CHANNEL_OF_USER(User,i);
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
        if (TRUE == ComM_ChannelNoComInhibitionStatus(Channel))
        {
          NoComInhibitionStatus = TRUE;
        }
#endif
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
        /* !LINKSTO ComM.SWS_ComM_00219,1 */
        if (TRUE == ComM_ChannelWakeUpInhibitionStatus(Channel))
        {
          WkUpInhibitionStatus = TRUE;
        }
#endif
      ComM_ChanState_local = ComM_ChanState[Channel];
      comAllowed = ComM_Communication_Allowed[Channel];
      /* If any one channel has inhibition on and currently is in No Com
       * mode, set the lowest possible mode */
      /* Deviation TASKING-3 <START> */
#pragma warning 549
      if (((COMM_NO_COM_NO_PENDING_REQUEST == ComM_ChanState_local) ||
           (COMM_NO_COM_REQUEST_PENDING    == ComM_ChanState_local)
          ) &&
          ((TRUE  == NoComInhibitionStatus                         ) ||
           (TRUE  == WkUpInhibitionStatus                          ) ||
           (FALSE == comAllowed                                    )
          )
         )
#pragma warning default
      /* Deviation TASKING-3 <STOP> */
      {
        *ComMode = COMM_NO_COMMUNICATION;
        break;
      }
      /* If current state of channel is Silent Com and inhibition is active,
       * the max available mode for user is Silent Communication */
      /* Deviation TASKING-3 <START> */
#pragma warning 549
      else if ((COMM_SILENT_COM == ComM_ChanState[Channel]                       ) &&
               ((TRUE == NoComInhibitionStatus) || (TRUE == WkUpInhibitionStatus))
              )
#pragma warning default
      /* Deviation TASKING-3 <STOP> */
      {
        *ComMode = COMM_SILENT_COMMUNICATION;
      }
      else
      {
        /* do nothing */
      }
    }

    RetVal = E_OK;
  }
#endif /* #if (COMM_NUM_USERS == 0U) */
  DBG_COMM_ASR40_GETMAXCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetRequestedComMode]-------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetRequestedMode
(
  ComM_ASR32_UserHandleType                             User,
  P2VAR(ComM_ASR32_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETREQUESTEDMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_GetRequestedComMode(User, ComMode);

  DBG_COMM_ASR32_GETREQUESTEDMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}
#endif

/*------------------[ComM_GetRequestedComMode]-------------------------------*/
/* !LINKSTO ComM.SWS_ComM_00500,1, ComM.ASR403.SWS_ComM_00079,1, ComM.SWS_ComM_00625,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetRequestedComMode
(
  ComM_ASR40_UserHandleType                             User,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_GETREQUESTEDCOMMODE_ENTRY(User,ComMode);
#if (COMM_NUM_USERS == 0U)
  TS_PARAM_UNUSED(User);
  TS_PARAM_UNUSED(ComMode);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_REQUESTED_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_GET_REQUESTED_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
#endif
#else /* #if (COMM_NUM_USERS == 0U) */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_REQUESTED_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == ComMode) || (User >= COMM_NUM_USERS))
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_GET_REQUESTED_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_PRECONDITION_ASSERT_ENABLED == STD_ON)
    {
      COMM_PRECONDITION_ASSERT(((ComM_UserRequestedComMode[User] == COMM_NO_COMMUNICATION) ||
                                (ComM_UserRequestedComMode[User] == COMM_FULL_COMMUNICATION)),
                                COMM_SID_GET_REQUESTED_COM_MODE);
    }
#endif
    *ComMode = ComM_UserRequestedComMode[User];
    RetVal = E_OK;
  }
#endif /* #if (COMM_NUM_USERS == 0U) */
  DBG_COMM_ASR40_GETREQUESTEDCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetCurrentComMode]---------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetCurrentComMode
(
  ComM_ASR32_UserHandleType                             User,
  P2VAR(ComM_ASR32_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETCURRENTCOMMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_GetCurrentComMode(User, ComMode);

  DBG_COMM_ASR32_GETCURRENTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#endif

/*------------------[ComM_GetCurrentComMode]---------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00083,1, ComM.SWS_ComM_00084,1, ComM.SWS_ComM_00176,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetCurrentComMode
(
  ComM_ASR40_UserHandleType                             User,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_NUM_USERS != 0U)
  uint8_least    i;
#endif
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_GETCURRENTCOMMODE_ENTRY(User,ComMode);
#if (COMM_NUM_USERS == 0U)
  TS_PARAM_UNUSED(User);
  TS_PARAM_UNUSED(ComMode);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    /* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00234.WRONG_PARAMETERS,1 */
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_CURRENT_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
  {
    /* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00234.WRONG_PARAMETERS,1 */
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_GET_CURRENT_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
#endif
#else /* #if (COMM_NUM_USERS == 0U) */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    /* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00234.WRONG_PARAMETERS,1 */
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_CURRENT_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == ComMode) || (User >= COMM_NUM_USERS))
  {
    /* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00234.WRONG_PARAMETERS,1 */
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_GET_CURRENT_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {

    ComM_ASR40_ModeType localComMode;
    ComM_ASR40_ModeType ResultComMode = COMM_FULL_COMMUNICATION;

    /* Get all channels for a specific user and set ComMode  */
    for (i = 0U; i < COMM_NUM_CHANNELS_OF_USER(User); i++)
    {
      const uint8 channel = COMM_CHANNEL_OF_USER(User,i);
      /* get locally cached com mode, the BusSm of channels of BusType=Internal
       * cannot be queried */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
      localComMode = ComM_ChannelMode[channel];
      RetVal = E_OK;
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_OFF)
#if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON)
      if (COMM_BUSTYPE_OF_CHANNEL(channel) == COMM_BUS_TYPE_INTERNAL)
      {

        localComMode = ComM_ChannelMode[channel];
        RetVal = E_OK;
      }
      else
#endif
      {
        /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.BusSM_GetCurrentComMode,1 */
        RetVal = COMM_BUSSM_GET_CURRENT_COM_MODE(channel, &localComMode);
#if (COMM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
        COMM_POSTCONDITION_ASSERT((E_OK == RetVal),COMM_SID_GET_CURRENT_COM_MODE);
#endif
        if( RetVal != E_OK)
        {
          break;
        }
      }
#else /* (COMM_MULTICORE_ENABLED == STD_OFF) */
      localComMode = ComM_ChannelMode[channel];
      RetVal = E_OK;
#endif
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      /* get the lowest communication mode possible */
      if (localComMode < ResultComMode)
      {
        ResultComMode = localComMode;
      }
    }
    if (E_OK == RetVal)
    {
      *ComMode = ResultComMode;
    }
  }
#endif /* #if (COMM_NUM_USERS == 0U) */
  DBG_COMM_ASR40_GETCURRENTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

/* !LINKSTO ComM.EB.ComM_GetCurrentPNCComMode,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetCurrentPNCComMode
(
  ComM_ASR40_UserHandleType                             User,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_GETCURRENTPNCCOMMODE_ENTRY(User,ComMode);

#if (COMM_NUM_USERS == 0U)
  TS_PARAM_UNUSED(User);
  TS_PARAM_UNUSED(ComMode);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_CURRENT_PNC_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_CURRENT_PNC_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
#endif /* #if (COMM_DEV_ERROR_DETECT == STD_ON) */
#else /* #if (COMM_NUM_USERS == 0U) */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_CURRENT_PNC_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (User >= COMM_NUM_USERS)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_CURRENT_PNC_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else if (ComMode == NULL_PTR)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_CURRENT_PNC_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */
  {
#if (COMM_PNC_SUPPORT == STD_ON)
    PNCHandleType numPncs = 0U;
    numPncs = COMM_NUM_PNCS_OF_USER(User);
    if (numPncs == 0U)
    {
      /* !LINKSTO ComM.SWS_ComM_01023,1 */
      RetVal = COMM_E_NO_PNC_ASSIGNED;
    }
    else if(numPncs > 1U)
    {
      /* !LINKSTO ComM.SWS_ComM_01022,1 */
      RetVal = COMM_E_MULTIPLE_PNC_ASSIGNED;
    }
    else
    {
      /* !LINKSTO ComM.EB.ComM_GetCurrentPNCComMode.ReturnedComMode.COMM_FULL_COMMUNICATION,1 */
      /* !LINKSTO ComM.EB.ComM_GetCurrentPNCComMode.ReturnedComMode.COMM_NO_COMMUNICATION,1 */
      if ((ComM_PNCState[COMM_PNC_OF_USER(User,0U)] == PNC_REQUESTED) ||
          (ComM_PNCState[COMM_PNC_OF_USER(User,0U)] == PNC_READY_SLEEP) ||
          (ComM_PNCState[COMM_PNC_OF_USER(User,0U)] == PNC_PREPARE_SLEEP))
      {
        (*ComMode) = COMM_FULL_COMMUNICATION;
      }
      else
      {
        (*ComMode) = COMM_NO_COMMUNICATION;
      }
      RetVal = E_OK;
    }
#else /* (COMM_PNC_SUPPORT == STD_ON) */
#if (COMM_DEV_ERROR_DETECT == STD_OFF)
    TS_PARAM_UNUSED(User);
    TS_PARAM_UNUSED(ComMode);
#endif /* (COMM_DEV_ERROR_DETECT == STD_OFF) */
    RetVal = COMM_E_NO_PNC_ASSIGNED;
#endif /* (COMM_PNC_SUPPORT == STD_ON) */
  }
#endif /* #if (COMM_NUM_USERS == 0U) */

  DBG_COMM_ASR40_GETCURRENTPNCCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_PreventWakeUp]---------------------------*/

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_PreventWakeUp
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_PREVENTWAKEUP_ENTRY(Channel,Status);

  RetVal = ComM_ASR40_PreventWakeUp(Channel, Status);

  DBG_COMM_ASR32_PREVENTWAKEUP_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_PreventWakeUp]-------------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00156,1, ComM.ASR32.ComM156,1 */
/* !LINKSTO ComM.SWS_ComM_00799,1, ComM.SWS_ComM_00470,1 */
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_PreventWakeUp
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_PREVENTWAKEUP_ENTRY(Channel,Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_PREVENT_WAKE_UP, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_PREVENT_WAKE_UP, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* If ECU group classification has bit 0 set, allow Prevent wake up */
    if (COMM_PREVENT_WAKEUP == (ComM_EB_NvRAM.ECUGroupClassification & COMM_PREVENT_WAKEUP))
    {
      if (TRUE == Status)
      {
        if (TRUE != ComM_ChannelWakeUpInhibitionStatus(Channel))
        {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)
          if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel] != COMM_MULTICORE_INVALID_FCT_INDEX)
          {
            ComM_Ch_To_Inhibition_DataType data;
            data.Operation = COMM_MULTICORE_COMM_PREVENT_WAKEUP_TRUE;
            data.Channel   = Channel;
            /* !LINKSTO ComM.EB.ChannelToInhibitionCrossPartition,1 */
            if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_List[ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel]](&data) != SCHM_E_OK)
            {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO ComM.EB.ChannelToInhibitionDataSetError,1 */
              COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_PREVENT_WAKE_UP, COMM_E_CH_TO_INHIBITION_DATASET_ERROR);
#endif
            }
          }
          else
#endif /*#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0) */
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
          {
            /* Set inhibition status of channel as Wake Up Inhibition */
            ComM_SetChannelComMInhibitionStatus(Channel, COMM_PREVENT_WAKEUP, TRUE, NULL_PTR);
          }
        }
      }
      else
      {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)
        if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel] != COMM_MULTICORE_INVALID_FCT_INDEX)
        {
          ComM_Ch_To_Inhibition_DataType data;
          data.Operation = COMM_MULTICORE_COMM_PREVENT_WAKEUP_FALSE;
          data.Channel   = Channel;
          /* !LINKSTO ComM.EB.ChannelToInhibitionCrossPartition,1 */
          if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_List[ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel]](&data) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_PREVENT_WAKE_UP, COMM_E_CH_TO_INHIBITION_DATASET_ERROR);
#endif
          }
        }
        else
#endif /*#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0) */
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
        {
          /* Reset Bit 0 Request of Wake Up Inhibition */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_ComM_PreventWakeUp_REQ_STATUS_CHANGED,1 */
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_PREVENT_WAKEUP, FALSE, NULL_PTR);
        }
      }
      /* Set return value to E_OK only if ECU group classification allowed
       * access */
      RetVal = E_OK;
    }
  }

  DBG_COMM_ASR40_PREVENTWAKEUP_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_LimitChannelToNoComMode]---------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_LimitChannelToNoComMode
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_ENTRY(Channel,Status);

  RetVal = ComM_ASR40_LimitChannelToNoComMode(Channel, Status);

  DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_LimitChannelToNoComMode]---------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00163,1, ComM.ASR32.ComM163,1, ComM.SWS_ComM_00470,1 */
/* !LINKSTO ComM.EB_Ref.SWS_ComM_00800.ComM_LimitChannelToNoComMode,1, ComM.SWS_ComM_00303,1, ComM.SWS_ComM_00841,1, ComM.SWS_ComM_00215,1 */
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_LimitChannelToNoComMode
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_ENTRY(Channel,Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_LIMIT_CHANNEL_TO_NO_COM, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_LIMIT_CHANNEL_TO_NO_COM, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* If ECU group classification has bit 1 set, allow Limit to No Comm */
    if (COMM_LIMIT_NOCOMM == (ComM_EB_NvRAM.ECUGroupClassification & COMM_LIMIT_NOCOMM))
    {
      if (TRUE == Status)
      {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)
        if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel] != COMM_MULTICORE_INVALID_FCT_INDEX)
        {
          ComM_Ch_To_Inhibition_DataType data;
          data.Operation = COMM_MULTICORE_COMM_LIMIT_NOCOM_TRUE;
          data.Channel   = Channel;
          /* !LINKSTO ComM.EB.ChannelToInhibitionCrossPartition,1 */
          if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_List[ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel]](&data) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_LIMIT_CHANNEL_TO_NO_COM, COMM_E_CH_TO_INHIBITION_DATASET_ERROR);
#endif
          }
        }
        else
#endif /*#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)*/
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
        {
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_LimitChannelToNoComMode_LIMIT_TO_NO_COM,1 */
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, TRUE, NULL_PTR);
        }
      }
      else
      {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)
        if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel] != COMM_MULTICORE_INVALID_FCT_INDEX)
        {
          ComM_Ch_To_Inhibition_DataType data;
          data.Operation = COMM_MULTICORE_COMM_LIMIT_NOCOM_FALSE;
          data.Channel   = Channel;
          /* !LINKSTO ComM.EB.ChannelToInhibitionCrossPartition,1 */
          if (ComM_Multicore_ChToInhibitionSchmSend_FctPtr_List[ComM_Multicore_ChToInhibitionSchmSend_FctPtr_IndexList[Channel]](&data) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_LIMIT_CHANNEL_TO_NO_COM, COMM_E_CH_TO_INHIBITION_DATASET_ERROR);
#endif
          }
        }
        else
#endif /*#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)*/
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
        {
          /* Reset Bit 1 Request of Limit to No Com */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_LimitChannelToNoCom_REQ_STATUS_CHANGED,1 */
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, FALSE, NULL_PTR);
        }
      }
      /* Set return value to E_OK only if ECU group classification allowed
       * access */
      RetVal = E_OK;
    }
  }

  DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_LimitECUToNoComMode]-------------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_LimitECUToNoComMode
(
  boolean Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_LIMITECUTONOCOMMODE_ENTRY(Status);

  RetVal = ComM_ASR40_LimitECUToNoComMode(Status);

  DBG_COMM_ASR32_LIMITECUTONOCOMMODE_EXIT(RetVal,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_LimitECUToNoComMode]-------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00124,1, ComM.ASR32.ComM124,1, ComM.SWS_ComM_00470,1 */
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_LimitECUToNoComMode
(
  boolean Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 Channel;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_LIMITECUTONOCOMMODE_ENTRY(Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_LIMIT_ECU_TO_NO_COM, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
#endif
  {
    /* If ECU group classification has bit 1 set, allow Limit to No Comm */
    if (COMM_LIMIT_NOCOMM == (ComM_EB_NvRAM.ECUGroupClassification & COMM_LIMIT_NOCOMM))
    {
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0))
      boolean SentToApplication[COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH];
      TS_MemSet(SentToApplication, FALSE, COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH);
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)) */
      /* Deviation TASKING-1 */
      for (Channel = 0U; Channel < COMM_NUM_CHANNELS; Channel++)
      {
        if (TRUE == Status)
        {
          /* Set Event for limit to no com */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_LimitECUToNoComMode_LIMIT_TO_NO_COM,1 */
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0))
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, TRUE, SentToApplication);
#else /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)) */
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, TRUE, NULL_PTR);
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)) */
        }
        else
        {
          /* Reset Bit 1 Request of Limit to No Com */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_LimitECUToNoCom_REQ_STATUS_CHANGED,1 */
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0))
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, FALSE, SentToApplication);
#else /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)) */
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, FALSE, NULL_PTR);
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)) */
        }
      }
      /* Set return value to E_OK only if ECU group classification allowed
       * access */
      RetVal = E_OK;
    }
  }

  DBG_COMM_ASR40_LIMITECUTONOCOMMODE_EXIT(RetVal,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_ReadInhibitCounter]--------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_ReadInhibitCounter
(
  P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_READINHIBITCOUNTER_ENTRY(CounterValue);

  RetVal = ComM_ASR40_ReadInhibitCounter(CounterValue);

  DBG_COMM_ASR32_READINHIBITCOUNTER_EXIT(RetVal,CounterValue);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_ReadInhibitCounter]--------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00224,1, ComM.ASR32.ComM224,1, ComM.SWS_ComM_00302,1, ComM.ASR403.SWS_ComM_00802,1, ComM.SWS_ComM_00141,1, ComM.SWS_ComM_00138,1, ComM.SWS_ComM_00142,1 */
/* !LINKSTO ComM.SWS_ComM_00143,1 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_ReadInhibitCounter
(
  P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_READINHIBITCOUNTER_ENTRY(CounterValue);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_READ_INHIBIT_COUNTER, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (NULL_PTR == CounterValue)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_READ_INHIBIT_COUNTER, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
    *CounterValue = ComM_EB_NvRAM.InhibitionCounter;
    COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();
    RetVal = E_OK;
  }

  DBG_COMM_ASR40_READINHIBITCOUNTER_EXIT(RetVal,CounterValue);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_ResetInhibitCounter]-------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1, ComM.SWS_ComM_00301,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_ResetInhibitCounter
(
  void
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_RESETINHIBITCOUNTER_ENTRY();

  RetVal = ComM_ASR40_ResetInhibitCounter();

  DBG_COMM_ASR32_RESETINHIBITCOUNTER_EXIT(RetVal);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_ResetInhibitCounter]-------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00108,1, ComM.ASR403.SWS_ComM_00803,1, ComM.SWS_ComM_00301,1 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_ResetInhibitCounter
(
  void
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_RESETINHIBITCOUNTER_ENTRY();

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_RESET_INHIBIT_COUNTER, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
#endif
  {
    COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
    ComM_EB_NvRAM.InhibitionCounter = 0U;
    COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();
    /* Set NvRAM modified */
    COMM_PERS_DATA_MODIFIED();
    RetVal = E_OK;
  }

  DBG_COMM_ASR40_RESETINHIBITCOUNTER_EXIT(RetVal);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_SetECUGroupClassification]-------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_SetECUGroupClassification
(
  ComM_ASR32_InhibitionStatusType Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_ENTRY(Status);

  RetVal = ComM_ASR40_SetECUGroupClassification(Status);

  DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_EXIT(RetVal,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_SetECUGroupClassification]-------------------------*/
/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00552.ComM_SetECUGroupClassification,1 */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_SetECUGroupClassification
(
  ComM_ASR40_InhibitionStatusType Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_ENTRY(Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_SET_ECU_GROUP_CLASS, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
#endif
  {
    /* Change variable (in NvRAM mirror) */
    ComM_EB_NvRAM.ECUGroupClassification = Status;
    /* Set NvRAM modified */
    COMM_PERS_DATA_MODIFIED();
    RetVal = E_OK;
  }

  DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_EXIT(RetVal,Status);

  return RetVal;
}
#endif

/*------------------[ComM_GetVersionInfo]------------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00370,1 */
#if (COMM_VERSION_INFO_API == STD_ON)
FUNC(void, COMM_CODE) ComM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, COMM_APPL_DATA) VersionInfoPtr)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_GETVERSIONINFO_ENTRY(VersionInfoPtr);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == VersionInfoPtr)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_GET_VERSION_INFO, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    VersionInfoPtr->vendorID         = COMM_VENDOR_ID;
    VersionInfoPtr->moduleID         = COMM_MODULE_ID;
    VersionInfoPtr->sw_major_version = COMM_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = COMM_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = COMM_SW_PATCH_VERSION;
  }

  DBG_COMM_GETVERSIONINFO_EXIT(VersionInfoPtr);
}
#endif

/*------------------[ComM_ChannelNoComInhibitionStatus]----------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
FUNC(boolean, COMM_CODE) ComM_ChannelNoComInhibitionStatus(
  uint8 instIdx)
{
  boolean RetVal;

  RetVal = ComM_BitArrayIsBitSet(ComM_ChannelNoComInhibition, instIdx);

  return RetVal;
}
#endif

/*------------------[ComM_ChannelWakeUpInhibitionStatus]---------------------*/

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
FUNC(boolean, COMM_CODE) ComM_ChannelWakeUpInhibitionStatus(
  uint8 instIdx)
{
  boolean RetVal;

  RetVal = ComM_BitArrayIsBitSet(ComM_ChannelWakeUpInhibition, instIdx);

  return RetVal;
}
#endif

/*------------------[ComM_Nm_NetworkStartIndication]-------------------------*/
/* !LINKSTO ComM.SWS_ComM_00383,1, ComM.SWS_ComM_00583,1 */
#if (COMM_NM_ACCESS_NEEDED == STD_ON)
FUNC(void, COMM_CODE) ComM_Nm_NetworkStartIndication
(
  NetworkHandleType Channel
)
{
#if (COMM_DCM_ENABLED == STD_ON)
  boolean PassiveStartupStatus = FALSE;
#endif
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_NM_NETWORKSTARTINDICATION_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_NETWORK_START_IND, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_NETWORK_START_IND, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_DCM_ENABLED == STD_ON)
    PassiveStartupStatus = ComM_DcmActiveStatus[Channel];
    if((ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION) &&
       (PassiveStartupStatus == FALSE))
#else
    if(ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION)
#endif
    {
      ComM_PassiveStartupStatus[COMM_INST(Channel)] = TRUE;
    }
    /* Set Event for network start indication */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_Nm_NetworkStartIndication_PASSIVE_WAKEUP_IND,1 */
    /* !LINKSTO ComM.EB.ComM_PASSIVE_WAKEUP_IND_NoComNoPendingReq,1, ComM.SWS_ComM_00903,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
  }

#if ((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_HSM_INST_MULTI_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(Channel);
#endif

  DBG_COMM_NM_NETWORKSTARTINDICATION_EXIT(Channel);
}

/*------------------[ComM_Nm_NetworkMode]------------------------------------*/
/* !LINKSTO ComM.SWS_ComM_00390,1 */
FUNC(void, COMM_CODE) ComM_Nm_NetworkMode
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_NM_NETWORKMODE_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_NETWORK_MODE, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_NETWORK_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_MULTICORE_ENABLED == STD_ON)
     /* !LINKSTO ComM.EB.BusNm_GetState,1 */
     ComM_LastNmMode[Channel] = NM_MODE_NETWORK;
#endif
    /* Set Event for network mode indication */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_Nm_NetworkMode_NM_MODE_SWITCHED,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_MODE_SWITCHED);
  }

#if ((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_HSM_INST_MULTI_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(Channel);
#endif

  DBG_COMM_NM_NETWORKMODE_EXIT(Channel);
}

/*------------------[ComM_Nm_PrepareBusSleepMode]----------------------------*/
/* !LINKSTO ComM.SWS_ComM_00391,1 */
FUNC(void, COMM_CODE) ComM_Nm_PrepareBusSleepMode
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_NM_PREPAREBUSSLEEPMODE_ENTRY(Channel);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_PREPARE_BUS_SLEEP, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_PREPARE_BUS_SLEEP, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_MULTICORE_ENABLED == STD_ON)
     /* !LINKSTO ComM.EB.BusNm_GetState,1 */
     ComM_LastNmMode[Channel] = NM_MODE_PREPARE_BUS_SLEEP;
#endif
    /* Set Event for prepare bus sleep mode indication */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_Nm_PrepareBusSleepMode_NM_MODE_SWITCHED,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_MODE_SWITCHED);
  }

#if ((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_HSM_INST_MULTI_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(Channel);
#endif

  DBG_COMM_NM_PREPAREBUSSLEEPMODE_EXIT(Channel);
}

/*------------------[ComM_Nm_BusSleepMode]-----------------------------------*/
/* !LINKSTO ComM.SWS_ComM_00392,1 */
FUNC(void, COMM_CODE) ComM_Nm_BusSleepMode
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_NM_BUSSLEEPMODE_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_BUS_SLEEP_MODE, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_BUS_SLEEP_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_MULTICORE_ENABLED == STD_ON)
     /* !LINKSTO ComM.EB.BusNm_GetState,1 */
     ComM_LastNmMode[Channel] = NM_MODE_BUS_SLEEP;
#endif
    /* Set Event for bus sleep mode indication */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_Nm_BusSleepMode_NM_MODE_SWITCHED,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_MODE_SWITCHED);
  }

#if ((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_HSM_INST_MULTI_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(Channel);
#endif

  DBG_COMM_NM_BUSSLEEPMODE_EXIT(Channel);
}

/*------------------[ComM_Nm_RestartIndication]------------------------------*/
/* !LINKSTO ComM.SWS_ComM_00792,1 */
FUNC(void, COMM_CODE) ComM_Nm_RestartIndication
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
#if (COMM_DCM_ENABLED == STD_ON)
  boolean PassiveStartupStatus = FALSE;
#endif
  DBG_COMM_NM_RESTARTINDICATION_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_RESTART_IND, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_RESTART_IND, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_DCM_ENABLED == STD_ON)
    PassiveStartupStatus = ComM_DcmActiveStatus[Channel];
    if((ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION) &&
       (PassiveStartupStatus == FALSE))
#else
    if(ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION)
#endif
    {
      ComM_PassiveStartupStatus[COMM_INST(Channel)] = TRUE;
    }
    /* Set Event for Nm restart indication */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_Nm_RestartIndication_PASSIVE_WAKEUP_IND,1, ComM.SWS_ComM_00902,1 */
    /* !LINKSTO ComM.SWS_ComM_00894,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
  }

#if ((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_HSM_INST_MULTI_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(Channel);
#endif

  DBG_COMM_NM_RESTARTINDICATION_EXIT(Channel);
}

#if (COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON)

/* !LINKSTO ComM.ASR21-11.SWS_ComM_91030,1 */
FUNC(void, COMM_CODE) ComM_Nm_ForwardSynchronizedPncShutdown
(
  NetworkHandleType Channel,
  P2CONST(uint8, AUTOMATIC, COMM_APPL_CONST) PncBitVectorPtr
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN_ENTRY(Channel,PncBitVectorPtr);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN, COMM_E_NOT_INITED);
  }
  else if ((NULL_PTR == PncBitVectorPtr) || (Channel >= COMM_NUM_CHANNELS))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON)
    if (ComM_SyncronizedShutdownPassiveChannelList[Channel] != 255U)
    {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0)
      const uint8 SynchPassiveChannelIndex = ComM_SyncronizedShutdownPassiveChannelList[Channel];
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      uint16 cntr = 0;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0)
      if (ComM_Multicore_SynchShutDownChToMasterPncSchmSend_FctPtr_IndexList[SynchPassiveChannelIndex] != COMM_MULTICORE_INVALID_FCT_INDEX)
      {
        const uint8 SynchPassiveChannelFctPtrIndex = ComM_Multicore_SynchShutDownChToMasterPncSchmSend_FctPtr_IndexList[SynchPassiveChannelIndex];

        COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(&ComM_HsmScComM, Channel);
        for (cntr = 0; cntr < COMM_PN_INFO_LENGTH; cntr++)
        {
          ComM_SynchShutDownChToMasterPncData[SynchPassiveChannelFctPtrIndex].PnInfo[cntr] = PncBitVectorPtr[cntr];
        }
        COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(&ComM_HsmScComM, Channel);

        if (ComM_Multicore_SynchShutDownChToMasterPncSchmSend_FctPtr_List[SynchPassiveChannelFctPtrIndex](&ComM_SynchShutDownChToMasterPncData[SynchPassiveChannelFctPtrIndex]) != SCHM_E_OK)
        {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
          COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN, COMM_E_CH_TO_MASTERPNC_DATASET_ERROR);
#endif
        }
      }
      else
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWNCH_TO_MASTERPNC_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      {
        COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(&ComM_HsmScComM, Channel);
        for (cntr = 0; cntr < COMM_PN_INFO_LENGTH; cntr++)
        {
          ComM_SynchronusShutDownArr[cntr] |= (PncBitVectorPtr[cntr] & COMM_SYNCHRONIZED_SHUTDOWN_PNC_MASK(cntr));
        }
        COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(&ComM_HsmScComM, Channel);
      }
    }
#endif /* #if (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON) */
  }

  DBG_COMM_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN_EXIT(Channel,PncBitVectorPtr);
}
#endif /* #if (COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) */

#endif /* (COMM_NM_ACCESS_NEEDED == STD_ON) */

/*------------------[ComM_BusSM_BusSleepMode]-----------------------------------*/
/* !LINKSTO ComM.SWS_ComM_91000,1 */
FUNC(void, COMM_CODE) ComM_BusSM_BusSleepMode
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  boolean DetReported = FALSE;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
 DBG_COMM_BUSSM_BUSSLEEPMODE_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_BUS_SLEEP_MODE, COMM_E_NOT_INITED);
    DetReported = TRUE;
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_BUS_SLEEP_MODE, COMM_E_WRONG_PARAMETERS);
    DetReported = TRUE;
  }
  else
  {

  }
#endif
#if ((COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_OFF) && \
     (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_OFF))
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (DetReported == FALSE)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_BUS_SLEEP_MODE, COMM_E_WRONG_PARAMETERS);
  }
#endif /* #if (COMM_DEV_ERROR_DETECT == STD_ON) */
#else /* #if ((COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_OFF) && \
       *      (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_OFF))
       */
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_NONE_NEEDED == STD_ON))
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (DetReported == FALSE)
  {
    if ((COMM_NM_VARIANT_OF_CHANNEL(Channel) != COMM_NM_SLAVE_ACTIVE_VARIANT) &&
        (COMM_NM_VARIANT_OF_CHANNEL(Channel) != COMM_NM_SLAVE_PASSIVE_VARIANT))
    {
      COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_BUS_SLEEP_MODE, COMM_E_WRONG_PARAMETERS);
      DetReported = TRUE;
    }
  }
#endif /* #if (COMM_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || \
               (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) || \
               (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON) || \
               (COMM_NM_VARIANT_NONE_NEEDED == STD_ON))*/
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (DetReported == FALSE)
#endif
  {
    /* Set Event for bus sleep mode indication */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_01018.NmVariant.SLAVE_ACTIVE,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_01018.NmVariant.SLAVE_PASSIVE,1 */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.BUS_SM_SLEEP_INDICATION,1 */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.BUS_SM_SLEEP_INDICATION_NO_COMMUNICATION,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_BUS_SM_SLEEP_INDICATION);
  }

#endif /* #if ((COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_OFF) && \
        *      (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_OFF))
        */

#if ((COMM_DEV_ERROR_DETECT == STD_OFF) && ((COMM_HSM_INST_MULTI_ENABLED == STD_OFF) || \
                                            ((COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_OFF) && \
                                             (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_OFF))))
  TS_PARAM_UNUSED(Channel);
#endif

  DBG_COMM_BUSSM_BUSSLEEPMODE_EXIT(Channel);
}

#if (COMM_DCM_ENABLED == STD_ON)
/*------------------[ComM_DCM_ActiveDiagnostic]------------------------------*/
/* !LINKSTO ComM.SWS_ComM_00873,1 */
FUNC(void, COMM_CODE) ComM_DCM_ActiveDiagnostic
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_DCM_ACTIVEDIAGNOSTIC_ENTRY(Channel);

#if (((COMM_DEV_ERROR_DETECT              == STD_OFF)  && \
      (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)  && \
      (COMM_NM_VARIANT_PASSIVE_ONLY       == STD_OFF)) || \
                                                          \
      ((COMM_DEV_ERROR_DETECT             == STD_OFF)  && \
      (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)  && \
      (COMM_NM_VARIANT_PASSIVE_ONLY       == STD_ON))  || \
                                                          \
      ((COMM_DEV_ERROR_DETECT             == STD_OFF)  && \
      (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)   && \
      (COMM_NM_VARIANT_PASSIVE_ONLY       == STD_ON)))
  TS_PARAM_UNUSED(Channel);
#endif
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_DCM_ACTIVE_DIAGNOSTIC, COMM_E_NOT_INITED);
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_DCM_ACTIVE_DIAGNOSTIC, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Diagnostic session on a Passive channel is not possible. */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00889.NmVariant.LIGHT,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00889.NmVariant.NONE,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00866.NmVariant.FULL,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00866.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00866.NmVariant.NONE,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00876.NmVariant.FULL,1, ComM.EB_Ref.SWS_ComM_00876.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00876.NmVariant.NONE,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00878.NmVariant.FULL,1, ComM.EB_Ref.SWS_ComM_00878.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00878.NmVariant.NONE,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00883.NmVariant.FULL,1, ComM.EB_Ref.SWS_ComM_00883.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00883.NmVariant.NONE,1 */
#if (COMM_NM_VARIANT_PASSIVE_ONLY == STD_OFF)
#if (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON)
    if (COMM_NM_VARIANT_OF_CHANNEL(Channel) != COMM_NM_PASSIVE_VARIANT)
#endif /* #if (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) */
    {
      COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
      /* Set the bit (active diagnostic request) for the corresponding
       * channel in the bit array */
      ComM_DcmActiveStatus[Channel] = TRUE;
      COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
      /* notify state machine about changed diagnostics communication state */
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_DCM_ActiveDiagnostic_REQ_STATUS_CHANGED,1 */
      COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
#endif
  }
  DBG_COMM_DCM_ACTIVEDIAGNOSTIC_EXIT(Channel);
}

/*------------------[ComM_DCM_InactiveDiagnostic]----------------------------*/
/* !LINKSTO ComM.SWS_ComM_00874,1 */
FUNC(void, COMM_CODE) ComM_DCM_InactiveDiagnostic
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_DCM_INACTIVEDIAGNOSTIC_ENTRY(Channel);
#if (((COMM_DEV_ERROR_DETECT              == STD_OFF)  && \
      (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)  && \
      (COMM_NM_VARIANT_PASSIVE_ONLY       == STD_OFF)) || \
                                                          \
      ((COMM_DEV_ERROR_DETECT             == STD_OFF)  && \
      (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF)  && \
      (COMM_NM_VARIANT_PASSIVE_ONLY       == STD_ON))  || \
                                                          \
      ((COMM_DEV_ERROR_DETECT             == STD_OFF)  && \
      (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)   && \
      (COMM_NM_VARIANT_PASSIVE_ONLY       == STD_ON)))
  TS_PARAM_UNUSED(Channel);
#endif
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_DCM_INACTIVE_DIAGNOSTIC, COMM_E_NOT_INITED);
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_DCM_INACTIVE_DIAGNOSTIC, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_NM_VARIANT_PASSIVE_ONLY == STD_OFF)
    /* Diagnostic session on a Passive channel is not possible.
     * See RFC #56661 */
#if (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON)
    if (COMM_NM_VARIANT_OF_CHANNEL(Channel) != COMM_NM_PASSIVE_VARIANT)
#endif /* #if (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) */
    {
      COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
      /* Clear the bit (active diagnostic request) for the corresponding
       * channel in the bit array */
      ComM_DcmActiveStatus[Channel] = FALSE;
      COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
      /* notify state machine about changed diagnostics communication state */
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_DCM_InactiveDiagnostic_REQ_STATUS_CHANGED,1 */
      COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
#endif
  }

  DBG_COMM_DCM_INACTIVEDIAGNOSTIC_EXIT(Channel);
}
#endif  /* (COMM_DCM_ENABLED == STD_ON) */

/*------------------[ComM_EcuM_WakeUpIndication]-----------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00275,1, ComM.SWS_ComM_00066,1 */
FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication
(
  NetworkHandleType Channel
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ECUM_WAKEUPINDICATION_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_ECUM_WAKE_UP_INDICATION, COMM_E_NOT_INITED);
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_ECUM_WAKE_UP_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    ComM_EcuM_WakeUpIndication_Helper(Channel, TRUE);
  }
  DBG_COMM_ECUM_WAKEUPINDICATION_EXIT(Channel);
}

/* !LINKSTO ComM.SWS_ComM_91001,1 */
FUNC(void, COMM_CODE) ComM_EcuM_PNCWakeUpIndication
(
  PNCHandleType PNCid
)
{
#if (COMM_PNC_SUPPORT == STD_ON)
  PNCHandleType PncIDIdx;
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_ECUM_PNCWAKEUPINDICATION_ENTRY(PNCid);

#if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF)
  /* Find index from PNCIDs, since PNCIDs are generated in
     sorted order */
  /* Deviation TASKING-1 */
  for (PncIDIdx = 0U; PncIDIdx < COMM_NUM_PNC; PncIDIdx++)
  {
    if(PNCid == ComM_PncID[PncIDIdx])
    {
      break;
    }
  }
#else /* #if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF) */
  PncIDIdx = COMM_INVALID_PNC_ID;

  if ((PNCid >= COMM_MIN_PNCID) && (PNCid <= COMM_MAX_PNCID))
  {
    PncIDIdx = ComM_PncIdList[PNCid - (COMM_PN_OFFSET * 8U)];
  }
#endif /* #if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF) */
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    /* !LINKSTO ComM.ASR430.SWS_ComM_00965,1 */
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_ECUM_PNC_WAKE_UP_INDICATION, COMM_E_NOT_INITED);
  }
  else if (PncIDIdx >= COMM_NUM_PNC)
  {
    COMM_DET_REPORT_ERROR(
      InstanceID, COMM_SID_ECUM_PNC_WAKE_UP_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {

    /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication_ComMPncEnable_FALSE,1 */
    if(COMM_PNC_ENABLED)
    {
      ComM_PNCWakeUpIndication_PncHandle(PncIDIdx);
      ComM_PNCWakeUpIndication_ChannelHandle(PncIDIdx, TRUE);
    }
  }
  DBG_COMM_ECUM_PNCWAKEUPINDICATION_EXIT(PNCid);
#else
  /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication_No_PNCs,1 */
  TS_PARAM_UNUSED(PNCid);
#endif
}

/*------------------[ComM_CommunicationAllowed]-----------------------------*/
/* !LINKSTO ComM.SWS_ComM_00871,1, ComM.SWS_ComM_00884,1, ComM.SWS_ComM_00885,1 */
FUNC(void, COMM_CODE) ComM_CommunicationAllowed
(
  NetworkHandleType Channel,
  boolean           Allowed
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_COMMUNICATIONALLOWED_ENTRY(Channel,Allowed);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_COMMUNICATIONALLOWED, COMM_E_NOT_INITED);
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_COMMUNICATIONALLOWED, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    if(TRUE == Allowed)
    {
      COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
      ComM_Communication_Allowed[Channel] = TRUE;
      COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
    }
    else
    {
      COMM_CHANNELPNC_ENTER_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
      /* Clear the bit for the corresponding channel */
      ComM_Communication_Allowed[Channel] = FALSE;
      COMM_CHANNELPNC_EXIT_EXCLUSIVE_AREA(&ComM_HsmScComM , Channel);
    }
    /* Set Event for communication allowed */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_CommunicationAllowed_COMALLOWED_CHANGED,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_COMALLOWED_CHANGED);
  }

  DBG_COMM_COMMUNICATIONALLOWED_EXIT(Channel,Allowed);
}

/*------------------[ComM_BusSM_ModeIndication]------------------------------*/
/* !LINKSTO ComM.ASR403.SWS_ComM_00675,1 */
FUNC(void, COMM_CODE) ComM_BusSM_ModeIndication
(
  NetworkHandleType                                     Channel,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  uint8 InstanceID = GetApplicationID();
#else
  uint8 InstanceID = COMM_INSTANCE_ID;
#endif
#endif
  DBG_COMM_BUSSM_MODEINDICATION_ENTRY(Channel,ComMode);
#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_INDICATION, COMM_E_NOT_INITED);
  }
  else if ((NULL_PTR == ComMode) || (Channel >= COMM_NUM_CHANNELS))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
#if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON)
  else if (COMM_BUSTYPE_OF_CHANNEL(Channel) == COMM_BUS_TYPE_INTERNAL)
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
  else if (((*ComMode) != COMM_NO_COMMUNICATION) &&
           ((*ComMode) != COMM_SILENT_COMMUNICATION) &&
           ((*ComMode) != COMM_FULL_COMMUNICATION))
  {
    COMM_DET_REPORT_ERROR(InstanceID, COMM_SID_BUS_SM_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
#endif
  else
#endif
  {
    /* !LINKSTO ComM.EB.Dsn.Algorithm.BusSMModeIndication,1 */
    ComM_ChannelMode[Channel] = *ComMode;

    /* Set Bus Mode indication for corresponding channel */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.BUSSM_MODE_IND,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_BUSSM_MODE_IND);
  }

  DBG_COMM_BUSSM_MODEINDICATION_EXIT(Channel,ComMode);
}

/*==================[internal function definitions]=========================*/

/*------------------[ComM_EB_GetUserRequestedComMode]----------------------------------*/
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetUserRequestedComMode
(
  uint8 User
)
{
  ComM_ASR40_ModeType ret;
  ret = ComM_UserRequestedComMode[User];
  return ret;
}

/*------------------[ComM_EB_SetRequestedComMode]----------------------------------*/
FUNC(void, COMM_CODE) ComM_EB_SetRequestedComMode
(
  uint8 Channel,
  ComM_ASR40_ModeType ComMode,
  ComM_ASR40_ModeType ComModeWithoutPncRequest,
  ComM_ASR40_ModeType ComModeWakeupSleepRequest
)
{
#if (COMM_PNC_GW_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(ComModeWithoutPncRequest);
#endif /* #if (COMM_PNC_GW_ENABLED == STD_ON) */
#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(ComModeWakeupSleepRequest);
#endif /*#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON) */
  ComM_RequestedComMode[Channel] = ComMode;
#if (COMM_PNC_GW_ENABLED == STD_ON)
  ComM_RequestedComModeWithoutPnc[Channel] = ComModeWithoutPncRequest;
#endif /* #if (COMM_PNC_GW_ENABLED == STD_ON) */
#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)
  ComM_RequestedComModeWakeupSleepRequest[Channel] = ComModeWakeupSleepRequest;
#endif
}

/*------------------[ComM_EvaluatePnc]----------------------------------*/

#if (COMM_PNC_SUPPORT == STD_ON)
FUNC(void, COMM_CODE) ComM_EvaluatePnc
(
  PNCHandleType Pnc
)
{

  const uint8_least NumUser = COMM_NUM_USERS_OF_PNC(Pnc);
  uint8_least       UserPos;
  /* !LINKSTO ComM.SWS_ComM_00825,1 */
  const uint8 Index = ((uint8)(ComM_PncID[COMM_INST(Pnc)] >> SHIFT_3_BITS)) - COMM_PN_OFFSET;
  ComM_ASR40_ModeType ComMode = COMM_NO_COMMUNICATION;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  SchM_Enter_ComM_1_MasterPnc_SCHM_COMM_EXCLUSIVE_AREA_MASTERPNC();
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

  /* Search highest mode requested by users of a PNC */
  for (UserPos = 0U; UserPos < NumUser; UserPos++)
  {
    const uint8 UserOfPnc = COMM_USER_OF_PNC(Pnc,UserPos);

    if (ComMode < ComM_UserRequestedComMode[UserOfPnc])
    {
      ComMode = ComM_UserRequestedComMode[UserOfPnc];
    }
  }

  /* if users request full communication mode or diagnostics request full
  * com */
  if (COMM_FULL_COMMUNICATION == ComMode)
  {
    ComM_PncStateUserRequest[Index] = ComM_PncStateUserRequest[Index] | (uint8)(1U << (ComM_PncID[COMM_INST(Pnc)] & MASK_3_BITS));
  }
  else /* no user needs full com */
  {
    ComM_PncStateUserRequest[Index] = ComM_PncStateUserRequest[Index] & (uint8)(~(1U << (ComM_PncID[COMM_INST(Pnc)] & MASK_3_BITS)));
  }
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  SchM_Exit_ComM_1_MasterPnc_SCHM_COMM_EXCLUSIVE_AREA_MASTERPNC();
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  if (COMM_FULL_COMMUNICATION == ComMode)
  {
#if(COMM_PNC_GW_ENABLED == STD_ON)
    COMM_PNC_EMIT(Pnc, COMM_HSM_COMMPNC_EV_PNC_UPDATE_TX_PASSIVE);
#endif

    /* Set Event for full communication mode */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_REQ_BY_COMM_USER,1 */
    /* !LINKSTO ComM.EB.SWS_ComM_00165_UserRequest,1 */
    COMM_PNC_EMIT(Pnc, COMM_HSM_COMMPNC_EV_PNC_REQ_STATUS_CHANGED);
  }
  else
  {
    /* Set Event for ready sleep mode */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_RequestComMode_NO_COM_REQ_BY_ALL_COMM_USER,1 */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ModeLimitation_NO_COM_REQ_BY_ALL_COMM_USER,1 */
    COMM_PNC_EMIT(Pnc, COMM_HSM_COMMPNC_EV_PNC_REQ_STATUS_CHANGED);

#if(COMM_PNC_GW_ENABLED == STD_ON)
    COMM_PNC_EMIT(Pnc, COMM_HSM_COMMPNC_EV_PNC_UPDATE_TX_PASSIVE);
#endif
  }
}
#endif

/*------------------[ComM_SetChannelComMInhibitionStatus]--------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(void, COMM_CODE) ComM_SetChannelComMInhibitionStatus
(
  uint8                                instIdx,
  ComM_ASR40_InhibitionStatusType      Inhibitiontype,
  boolean                              Status,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) SentToApplication
)
{

#if (COMM_MODE_LIMITATION_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(Inhibitiontype);
#endif

#if (!((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)))
  TS_PARAM_UNUSED(SentToApplication);
#endif /* (!((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0))) */

/* !LINKSTO ComM.SWS_ComM_00690,1 */
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
  if (COMM_LIMIT_NOCOMM == Inhibitiontype)
  {
    if (TRUE == Status)
    {
      /* Set inhibition status of channel as Limit to No Com */
      COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
      ComM_BitArraySet(ComM_ChannelNoComInhibition, instIdx);
      COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)
      if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx] != COMM_MULTICORE_INVALID_FCT_INDEX)
      {
        ComM_Inhibition_To_Ch_DataType data;
        boolean sendData = FALSE;
        data.Channel = instIdx;
        if (SentToApplication != NULL_PTR)
        {
          data.Operation = COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM_ALL_CHANNELS;
          if (SentToApplication[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]] == FALSE)
          {
            sendData = TRUE;
            SentToApplication[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]] = TRUE;
          }
        }
        else
        {
          data.Operation = COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM;
          sendData = TRUE;
        }
        if (sendData == TRUE)
        {
          /* !LINKSTO ComM.EB.InhibitionToChannelCrossPartition,1 */
          if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_List[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]](&data) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO ComM.EB.InhibitionToChannelSetError,1 */
            /* !LINKSTO ComM.EB.SetChannelComMInhibitionStatusDataSetSIDError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_CHANNEL_COMM_INHIBITION_SET, COMM_E_INHIBITION_TO_CH_DATASET_ERROR);
#endif
          }
        }
      }
      else
#endif /*#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)*/
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
      {
        COMM_EMIT(instIdx, COMM_HSM_COMM_EV_LIMIT_TO_NO_COM);
      }
    }
    else
    {
      /* Reset Bit Request of Limit to No Com */
      COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
      ComM_BitArrayClear(ComM_ChannelNoComInhibition, instIdx);
      COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();
      /* emit event 'REQ_STATUS_CHANGED'. This triggers the required
       * transitions if there are user requests when inhibition was active */
      /* !LINKSTO ComM.SWS_ComM_00839,1, ComM.SWS_ComM_00840,1 */
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_LimitChannelToNoCom_REQ_STATUS_CHANGED,1 */
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_LimitECUToNoCom_REQ_STATUS_CHANGED,1 */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)
      if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx] != COMM_MULTICORE_INVALID_FCT_INDEX)
      {
        ComM_Inhibition_To_Ch_DataType data;
        boolean sendData = FALSE;
        data.Channel = instIdx;
        if (SentToApplication != NULL_PTR)
        {
          data.Operation = COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED_ALL_CHANNELS;
          if (SentToApplication[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]] == FALSE)
          {
            sendData = TRUE;
            SentToApplication[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]] = TRUE;
          }
        }
        else
        {
          data.Operation = COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED;
          sendData = TRUE;
        }
        if (sendData == TRUE)
        {
          /* !LINKSTO ComM.EB.InhibitionToChannelCrossPartition,1 */
          if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_List[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]](&data) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO ComM.EB.InhibitionToChannelSetError,1 */
            /* !LINKSTO ComM.EB.SetChannelComMInhibitionStatusDataSetSIDError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_CHANNEL_COMM_INHIBITION_SET, COMM_E_INHIBITION_TO_CH_DATASET_ERROR);
#endif
          }
        }
      }
      else
#endif /*#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0) */
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
      {
        COMM_EMIT(instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
      }
    }
  }
  else
#endif
  {
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    /* Find out if storing in NvRAM is allowed */
    const boolean changeNvRamAllowed = ComM_BitArrayIsBitSet(ComM_EB_NoWakeupNvStorage, instIdx);

    /* Modify Wakeup inhibition */
    if (TRUE == Status)
    {
      /* Enable inhibition */

      /* Set runtime variable */
      COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
      ComM_BitArraySet(ComM_ChannelWakeUpInhibition, instIdx);
      COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();

      /* Check setting NvRAM */
      if (TRUE == changeNvRamAllowed)
      {
        /* Set value in NvRAM */
        COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
        ComM_BitArraySet(ComM_EB_NvRAM.ChannelWakeUpInhibition, instIdx);
        COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();
        /* Set NvRAM modified */
        COMM_PERS_DATA_MODIFIED();
      }
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)
      if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx] != COMM_MULTICORE_INVALID_FCT_INDEX)
      {
        ComM_Inhibition_To_Ch_DataType data;
        data.Channel = instIdx;
        data.Operation = COMM_MULTICORE_EMIT_WAKEUP_INHIBITION;
        /* !LINKSTO ComM.EB.InhibitionToChannelCrossPartition,1 */
        if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_List[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]](&data) != SCHM_E_OK)
        {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO ComM.EB.InhibitionToChannelSetError,1 */
          /* !LINKSTO ComM.EB.SetChannelComMInhibitionStatusDataSetSIDError,1 */
          COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_CHANNEL_COMM_INHIBITION_SET, COMM_E_INHIBITION_TO_CH_DATASET_ERROR);
#endif
        }
      }
      else
#endif /* #if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0) */
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
      {
        COMM_EMIT(instIdx, COMM_HSM_COMM_EV_WAKEUP_INHIBITION);
      }
    }
    else
    {
      /* Take back inhibition */

      /* Clear runtime value */
      COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
      ComM_BitArrayClear(ComM_ChannelWakeUpInhibition, instIdx);
      COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();

      /* Check setting NvRAM */
      if (TRUE == changeNvRamAllowed)
      {
        /* Clear value in NvRAM */
        COMM_INHIBITION_ENTER_EXCLUSIVE_AREA();
        ComM_BitArrayClear(ComM_EB_NvRAM.ChannelWakeUpInhibition, instIdx);
        COMM_INHIBITION_EXIT_EXCLUSIVE_AREA();
        /* Set NvRAM modified */
        COMM_PERS_DATA_MODIFIED();
      }

      /* emit event 'REQ_STATUS_CHANGED'. This triggers the required
       * transitions if there are user requests when inhibition was active */
      /* !LINKSTO ComM.SWS_ComM_00839,1, ComM.SWS_ComM_00840,1 */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)
      if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx] != COMM_MULTICORE_INVALID_FCT_INDEX)
      {
        ComM_Inhibition_To_Ch_DataType data;
        data.Channel = instIdx;
        data.Operation = COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED;
        /* !LINKSTO ComM.EB.InhibitionToChannelCrossPartition,1 */
        if (ComM_Multicore_InhibitionToChSchmSend_FctPtr_List[ComM_Multicore_InhibitionToChSchmSend_FctPtr_IndexList[instIdx]](&data) != SCHM_E_OK)
        {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO ComM.EB.InhibitionToChannelSetError,1 */
          /* !LINKSTO ComM.EB.SetChannelComMInhibitionStatusDataSetSIDError,1 */
          COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_CHANNEL_COMM_INHIBITION_SET, COMM_E_INHIBITION_TO_CH_DATASET_ERROR);
#endif
        }
      }
      else
#endif /*#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)  */
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      {
        /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_ComM_PreventWakeUp_REQ_STATUS_CHANGED,1 */
        COMM_EMIT(instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
      }
    }
#endif
  }
}
#endif

FUNC(void, COMM_CODE) ComM_BitArraySet
(
  P2VAR(uint8, AUTOMATIC, COMM_APPL_DATA) arr,
  uint16                                  idx
)
{
  arr[idx / 8U] |= (uint8)(1U << (idx % 8U));
}

FUNC(void, COMM_CODE) ComM_BitArrayClear
(
  P2VAR(uint8, AUTOMATIC, COMM_APPL_DATA) arr,
  uint16                                 idx
)
{
  arr[idx / 8U] &= (uint8)(~(uint8)(1U << (idx % 8U)));
}

FUNC(boolean, COMM_CODE) ComM_BitArrayIsBitSet
(
  P2CONST(uint8, AUTOMATIC, COMM_APPL_DATA) arr,
  uint16                                    idx
)
{
  boolean RetVal;

  RetVal = ((((uint8)(arr[idx / 8U] >> (idx % 8U))) & 1U) != 0U) ? TRUE : FALSE;

  return RetVal;
}

#if (COMM_PNC_SUPPORT == STD_ON)
#if (COMM_NUM_PNC > 0)
/*------------------[ComM_EB_GetPncRequestedComMode]----------------------------------*/
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetPncRequestedComMode
(
  uint8 Channel,
  PNCHandleType PncPos
)
{
  ComM_ASR40_ModeType reqMode;
#if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF)
  PNCHandleType Idx;
  PNCHandleType PncIDIdx = 0U;
  /* Find index from PNCIDs, since PNCIDs are generated in
     sorted order */
  /* Deviation TASKING-1 */
  for (Idx = 0U; Idx < COMM_NUM_PNC; ++Idx)
  {
    if( COMM_PNC_OF_CHANNEL(Channel,PncPos) == ComM_PncID[Idx] )
    {
      PncIDIdx = Idx;
    }
  }
  reqMode = ComM_PNCRequestedComMode[PncIDIdx];
#else /* #if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF) */
  reqMode = ComM_PNCRequestedComMode[ComM_PncIdList[COMM_PNC_OF_CHANNEL(Channel,PncPos) - (COMM_PN_OFFSET * 8U)]];
#endif /* #if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF) */
  return reqMode;
}

/*-----------------[ComM_EB_GetPncRequestedComMode0PncVectorAvoidance]-----------------*/
#if(COMM_0_PNC_VECTOR_AVOIDANCE == STD_ON)
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetPncRequestedComMode0PncVectorAvoidance
(
  uint8 Channel,
  PNCHandleType PncPos
)
{
  ComM_ASR40_ModeType reqMode;
#if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF)
  PNCHandleType Idx;
  PNCHandleType PncIDIdx = 0U;
  /* Find index from PNCIDs, since PNCIDs are generated in
     sorted order */
  for (Idx = 0U; Idx < COMM_NUM_PNC; ++Idx)
  {
    if(COMM_PNC_OF_CHANNEL(Channel,PncPos) == ComM_PncID[Idx])
    {
      PncIDIdx = Idx;
    }
  }
  reqMode = ComM_PNCRequestedComMode0PncVectorAvoidance[PncIDIdx];
#else /* #if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF) */
  reqMode = ComM_PNCRequestedComMode0PncVectorAvoidance[ComM_PncIdList[COMM_PNC_OF_CHANNEL(Channel,PncPos) - (COMM_PN_OFFSET * 8U)]];
#endif /* #if (COMM_OPTIMIZE_PNC_INDEXING_FOR_SPEED == STD_OFF) */
  return reqMode;
}
#endif
#endif /* (COMM_NUM_PNC > 0) */

STATIC FUNC(void, COMM_CODE) ComM_ProcessPncComSignals
(
  P2VAR(boolean, AUTOMATIC, COMM_APPL_DATA) SignalStatusPtr,
  P2CONST(ComM_RxSignal_Struct_Type, AUTOMATIC, COMM_APPL_CONST) SignalConfigurationPtr,
  P2VAR(uint8, AUTOMATIC, COMM_APPL_DATA) SignalMergedPtr,
  uint8 SignalKind
)
{
  /* No *_least type for a loop variable as the variable is also used as
     an argument whose underlying type is uint8  */
  uint8 Index;
  uint8 i;
  uint8 RxEiraMerged[COMM_PN_INFO_LENGTH];
  /* Flag to indicate if at least one signal is received successfully */
  boolean EiraStatus = FALSE;

  uint8 signalCount = 0U;
  /* Initialise RxEiraMerged */
  TS_MemSet(RxEiraMerged, 0U, COMM_PN_INFO_LENGTH * sizeof(uint8));

#if(COMM_PNC_GW_ENABLED == STD_ON)
  if(SignalKind == COMM_IS_RX_ACTIVE_ERA)
  {
    signalCount = COMM_NUM_RX_ACTIVE_ERA_SIGNALS;
  }

  if(SignalKind == COMM_IS_RX_UNFILTERED_ERA)
  {
    signalCount = COMM_NUM_RX_UNFILTERED_ERA_SIGNALS;
  }
#else
  TS_PARAM_UNUSED(SignalKind);
#endif /* #if(COMM_PNC_GW_ENABLED == STD_ON) */
#if (COMM_NUM_RX_EIRA_SIGNALS > 0)
#if(COMM_PNC_GW_ENABLED == STD_ON)
  if(SignalKind == COMM_IS_RX_EIRA)
#endif /* #if(COMM_PNC_GW_ENABLED == STD_ON) */
  {
    signalCount = COMM_NUM_RX_EIRA_SIGNALS;
  }
#endif /* #if (COMM_NUM_RX_EIRA_SIGNALS > 0) */
  if (*SignalStatusPtr == TRUE)
  {
    /* EIRA change has been notified by Com, reset flag */
    *SignalStatusPtr = FALSE;
    for (Index = 0U; Index < signalCount; Index++)
    {
      uint8 RxEiraReceived[COMM_PN_INFO_LENGTH];
      Std_ReturnType retVal;
      /* Read EIRA signal into a temporary buffer */
      /* !LINKSTO ComM.SWS_ComM_00984,1 */
      /* !LINKSTO ComM.EB_Ref.SWS_ComM_00829.Com_ReceiveSignal,1 */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_MULTICORE_NO_OF_RX_BUFFERS == 0)
      retVal = Com_ReceiveSignal(SignalConfigurationPtr[Index].ComHandleId, RxEiraReceived);
#else /* #if (COMM_MULTICORE_NO_OF_RX_BUFFERS == 0) */
      if (SignalConfigurationPtr[Index].isLocalOsApplication == TRUE)
      {
        retVal = Com_ReceiveSignal(SignalConfigurationPtr[Index].ComHandleId, RxEiraReceived);
      }
      else
      {
        uint16 index = SignalConfigurationPtr[Index].MulticoreRxBufferIndex;
        retVal = E_OK;
        SchM_Enter_ComM_1_MasterPnc_SCHM_COMM_EXCLUSIVE_AREA_MASTERPNC();
        TS_MemCpy(RxEiraReceived, &ComM_MulticoreRxBuffer[index][0], COMM_PN_INFO_LENGTH);
        SchM_Exit_ComM_1_MasterPnc_SCHM_COMM_EXCLUSIVE_AREA_MASTERPNC();
      }
#endif /* #if (COMM_MULTICORE_NO_OF_RX_BUFFERS == 0) */
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_OFF)
      retVal = Com_ReceiveSignal(SignalConfigurationPtr[Index].ComHandleId, RxEiraReceived);
#else /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
#if (COMM_NO_OF_RX_BUFFERS == 0)
      retVal = Com_ReceiveSignal(SignalConfigurationPtr[Index].ComHandleId, RxEiraReceived);
#else /* #if (COMM_NO_OF_RX_BUFFERS == 0) */
      if (SignalConfigurationPtr[Index].isLocalCore == TRUE)
      {
        retVal = Com_ReceiveSignal(SignalConfigurationPtr[Index].ComHandleId, RxEiraReceived);
      }
      else
      {
        uint16 index = SignalConfigurationPtr[Index].MulticoreRxBufferIndex;
        retVal = E_OK;
        ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
        TS_MemCpy(RxEiraReceived, &ComM_MulticoreRxBuffer[index][0], COMM_PN_INFO_LENGTH);
        ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();
      }
#endif /* #if (COMM_NO_OF_RX_BUFFERS == 0) */
#endif /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      if (E_OK == retVal)
      {
        /* Update the flag if at least one signal is received */
        EiraStatus = TRUE;
        /* Data from multiple signals may be available at the same time;
         * So, merge the contents of the newly received signal into
         * another buffer.
         */
        /* Deviation TASKING-1 */
        for (i = 0U; i < COMM_PN_INFO_LENGTH; i++)
        {
          /* Some PNCs may not reference this RX EIRA Com signal.
           * Therefore, the bits corresponding to PNCs which do not
           * reference this Com signal have to be masked out before
           * copying into the global EIRA bit vector.
           */
          /* !LINKSTO ComM.SWS_ComM_00944,1, ComM.SWS_ComM_00945,1 */
#if(COMM_PNC_GW_ENABLED == STD_ON)
          if(SignalKind == COMM_IS_RX_ACTIVE_ERA)
          {
            RxEiraMerged[i] |= (uint8)(RxEiraReceived[i] & ComM_PncRxActiveEraMask[Index][i]);
          }

          if(SignalKind == COMM_IS_RX_UNFILTERED_ERA)
          {
            RxEiraMerged[i] |= (uint8)(RxEiraReceived[i] & ComM_PncRxUnfilteredEraMask[Index][i]);
          }

#endif /* #if(COMM_PNC_GW_ENABLED == STD_ON) */
#if (COMM_NUM_RX_EIRA_SIGNALS > 0)
#if(COMM_PNC_GW_ENABLED == STD_ON)
          if(SignalKind == COMM_IS_RX_EIRA)
#endif /* #if(COMM_PNC_GW_ENABLED == STD_ON) */
          {
            RxEiraMerged[i] |= (uint8)(RxEiraReceived[i] & ComM_PncRxEiraMask[Index][i]);
          }
#endif /* #if (COMM_NUM_RX_EIRA_SIGNALS > 0) */
        }
      }
      else
      {
#if (COMM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
        /*use main function SID*/
        /* Deviation TASKING-4 */
        COMM_POSTCONDITION_ASSERT((retVal != E_OK),COMM_SID_MAIN_FUNCTION);
#endif
      }
    }
  }
  /* If at least one signal is received */
  if (TRUE == EiraStatus)
  {
    ComM_ProcessPncComSignals_EmitEvents(SignalMergedPtr,
                                         RxEiraMerged,
                                         SignalKind);
    /* Copy new EIRA to old EIRA for next evaluation */
    /* Deviation TASKING-1 */
    for (Index = 0U; Index < COMM_PN_INFO_LENGTH; Index++)
    {
      SignalMergedPtr[Index] = RxEiraMerged[Index];
    }
  }
}


STATIC FUNC(void, COMM_CODE) ComM_ProcessPncComSignals_EmitEvents
(
  P2CONST(uint8, AUTOMATIC, COMM_APPL_DATA) SignalMergedPtr,
  P2CONST(uint8, AUTOMATIC, COMM_APPL_CONST) RxEiraMerged,
  uint8 SignalKind
)
{
  PNCHandleType PncIdx;
  uint8 Index;
  /* Deviation TASKING-1 */
  for (PncIdx = 0U; PncIdx < COMM_NUM_PNC; PncIdx++)
  {
    uint8 EiraMask;

    /* Each bit of EIRA stands for one PNC.
    * For example bit 0 of Byte 0 stands for PNC_0 and bit 0 of Byte 1
    * stands for PNC_8
    */
    /* Calculate the byte index from PncID */
    Index = ((uint8)(ComM_PncID[PncIdx] >> SHIFT_3_BITS)) - COMM_PN_OFFSET;
    /* Calculate the byte mask based on bit position of this Pnc */
    EiraMask = (uint8)(1U << (ComM_PncID[PncIdx] & MASK_3_BITS));
    if((SignalMergedPtr[Index] & EiraMask) != (RxEiraMerged[Index] & EiraMask))
    {
      if (SignalKind == COMM_IS_RX_EIRA)
      {
        /* There is a change in EIRA, append the EIRA event to the queue */
        /* !LINKSTO ComM.EB.Dsn.StateDynamics.COMCBK,1, ComM.SWS_ComM_00950,1 */
        COMM_PNC_EMIT(PncIdx, COMM_HSM_COMMPNC_EV_COMCBK);
      }
      else /* if ((SignalKind == COMM_IS_RX_UNFILTERED_ERA) || (SignalKind == COMM_IS_RX_ACTIVE_ERA)) */
      {
        if ((RxEiraMerged[Index] & EiraMask) != 0U)
        {
          if (SignalKind == COMM_IS_RX_ACTIVE_ERA)
          {
            COMM_PNC_EMIT(PncIdx, COMM_HSM_COMMPNC_EV_PNC_UPDATE_TX_PASSIVE);
          }
          /* There is a change in ERA to 1 */
          /* !LINKSTO ComM.SWS_ComM_00934,1, ComM.SWS_ComM_00951,1 */
          /* !LINKSTO ComM.EB.SWS_ComM_00165_ERARequest,1 */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_REQ_BY_COMM_USER_PNC_PREPARE_SLEEP_1,1 */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_REQ_BY_COMM_USER_PNC_PREPARE_SLEEP_2,1 */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_REQ_BY_COMM_USER_PNC_READY_SLEEP_0,1 */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_REQ_BY_COMM_USER_PNC_READY_SLEEP_1,1 */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_REQ_BY_COMM_USER_PNC_READY_SLEEP_2,1 */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_REQ_BY_COMM_USER_PNC_NO_COMMUNICATION_1,1 */
          /* !LINKSTO ComM.EB.ComM_PncReadySleep_PncRequested,1 */
          COMM_PNC_EMIT(PncIdx, COMM_HSM_COMMPNC_EV_PNC_REQ_STATUS_CHANGED);
        }
        else
        {
          /* There is a change in ERA to 0 */
          /* !LINKSTO ComM.EB.Dsn.StateDynamics.NO_COM_REQ_BY_ALL_COMM_USER_PNC_REQUESTED_0,1 */
          COMM_PNC_EMIT(PncIdx, COMM_HSM_COMMPNC_EV_PNC_REQ_STATUS_CHANGED);
          if (SignalKind == COMM_IS_RX_ACTIVE_ERA)
          {
            COMM_PNC_EMIT(PncIdx, COMM_HSM_COMMPNC_EV_PNC_UPDATE_TX_PASSIVE);
          }
        }
      }
    }
  }
}


#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0)
STATIC FUNC(void, COMM_CODE) ComM_ProcessTxSignals(void)
{
  uint16 i = 0;
  for (i = 0; i < COMM_NUM_TX_SIGNALS; i++)
  {
    if (ComM_TxComSignalCfg[i].SchMSendFctPtr != NULL_PTR)
    {
      uint16 index = ComM_TxComSignalCfg[i].MulticoreTxBufferIndex;
      P2VAR(uint8, AUTOMATIC, COMM_VAR) Dataptr = (uint8*)(&ComM_MulticoreTxBuffer[index][0]);
      if(ComM_MulticoreTxBufferStatus[index] == TRUE)
      {
        /* !LINKSTO ComM.EB.MasterPncToSignalCrossPartition,1 */
        if (ComM_TxComSignalCfg[i].SchMSendFctPtr(Dataptr) == SCHM_E_OK)
        {
          ComM_MulticoreTxBufferStatus[index] = FALSE;
        }
#if (COMM_DEV_ERROR_DETECT == STD_ON)
        else
        {
          /* !LINKSTO ComM.EB.MasterPncToSignalDataSetSIDError,1 */
          /* !LINKSTO ComM.EB.MasterPncToSignalSetError,1 */
          COMM_DET_REPORT_ERROR(ComM_TxComSignalCfg[i].SignalOsApplication, COMM_SID_MASTER_DATA_SET, COMM_E_MASTER_DATA_SET);
        }
#endif
      }
    }
  }
}
#endif /* #if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0) */
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (COMM_NO_OF_TX_BUFFERS != 0)
STATIC FUNC(void, COMM_CODE) ComM_ProcessTxSignals(void)
{
   uint16 i = 0;
   for (i = 0; i < COMM_NUM_TX_SIGNALS; i++)
   {
      if (ComM_TxComSignalCfg[i].SchMSendFctPtr != NULL_PTR)
      {
        uint16 index = ComM_TxComSignalCfg[i].MulticoreTxBufferIndex;
        P2VAR(uint8, AUTOMATIC, COMM_VAR) Dataptr = (uint8*)(&ComM_MulticoreTxBuffer[index][0]);
        if(ComM_MulticoreTxBufferStatus[index] == TRUE)
        {
          /* !LINKSTO ComM.EB.SchM_Call_Sender_Receiver_SendSlaveCore,1 */
          if (ComM_TxComSignalCfg[i].SchMSendFctPtr(Dataptr) == SCHM_E_OK)
          {
            ComM_MulticoreTxBufferStatus[index] = FALSE;
          }
#if (COMM_DEV_ERROR_DETECT == STD_ON)
          else
          {
            /* !LINKSTO ComM.EB.SchM_Call_Sender_Receiver_DET,1 */
            COMM_DET_REPORT_ERROR(ComM_TxComSignalCfg[i].CoreId, COMM_SID_MASTER_DATA_SET, COMM_E_MASTER_DATA_SET);
          }
#endif
       }
    }
  }
}
#endif /* #if (COMM_NO_OF_TX_BUFFERS != 0)*/
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

FUNC(void, COMM_CODE) ComM_PncMainFunction
(
void
)
{
  /* No *_least type for a loop variable as the variable is also used as
     an argument whose underlying type is uint8  */
  PNCHandleType PncIdx;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
  boolean ComMExecutePncMainFunction = FALSE;
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
  ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
  /* CHECK: NOPARSE */
  /* No parse have been added because
   * current test strategy does not permit
   * that a mainfunction to interrupt another mainfunction.
   */
  if (ComMPncMainfunctionRunning == FALSE)
  {
    ComMPncMainfunctionRunning = TRUE;
    ComMExecutePncMainFunction = TRUE;
  }
  ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
  if (ComMExecutePncMainFunction == TRUE)
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */
  {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
    TS_MemSet(&ComM_EvaluateChannel_MasterPnc_To_Ch, 0U, sizeof(ComM_EvaluateChannel_MasterPnc_To_Ch_DataType));
    TS_MemSet(ComM_EvaluateChannel_MasterPnc_To_Ch_Status, FALSE, sizeof(ComM_EvaluateChannel_MasterPnc_To_Ch_Status));
#endif /* #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
    TS_MemSet(&ComM_SynchShutDown_MasterPnc_To_Ch, 0U, sizeof(ComM_SynchShutDown_MasterPnc_To_Ch));
    TS_MemSet(ComM_SynchShutDown_MasterPnc_To_Ch_Status, FALSE, sizeof(ComM_SynchShutDown_MasterPnc_To_Ch_Status));
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
    ComM_Internal_CopySynchronizedPncShutdownInfo();
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
        */
#if(COMM_PNC_GW_ENABLED == STD_ON)
    ComM_ProcessPncComSignals(&ComM_RxActiveEraSignalStatus,
                              ComM_RxComSignalActiveEraCfg,
                              ComM_RxActiveEra,
                              COMM_IS_RX_ACTIVE_ERA
                              );
    ComM_ProcessPncComSignals(&ComM_RxUnfilteredEraSignalStatus,
                              ComM_RxComSignalUnfilteredEraCfg,
                              ComM_RxUnfilteredEra,
                              COMM_IS_RX_UNFILTERED_ERA
                              );
#endif
#if (COMM_NUM_RX_EIRA_SIGNALS > 0)
    ComM_ProcessPncComSignals(&ComM_RxEiraSignalStatus,
                              ComM_RxComSignalEiraCfg,
                              ComM_RxEira,
                              COMM_IS_RX_EIRA
                              );
#endif /* #if (COMM_NUM_RX_EIRA_SIGNALS > 0) */
    /* Deviation TASKING-1 */
    for (PncIdx = 0U; PncIdx < COMM_NUM_PNC; PncIdx++)
    {
      if(COMM_PNC_HSM_EVENT_PENDING(PncIdx))
      {
        /* Schedule the pnc state machine */
        (void) COMM_HSMMAININST((&ComM_HsmScComMPnc), (PncIdx));
      }
    }

#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
    ComM_Internal_ForwardSynchronizedPncShutdown();
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
        */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
    ComMPncMainfunctionRunning = FALSE;
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0)
    ComM_ProcessTxSignals();
#endif /* #if (COMM_MULTICORE_NO_OF_TX_BUFFERS != 0) */
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_MULTICORE_ENABLED == STD_ON)
#if (COMM_NO_OF_TX_BUFFERS != 0)
    ComM_ProcessTxSignals();
#endif /* #if (COMM_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_NO_OF_TX_BUFFERS != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
    {
      uint8 cntr;
      for (cntr = 0U; cntr < COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH; cntr++)
      {
        if (ComM_EvaluateChannel_MasterPnc_To_Ch_Status[cntr] == TRUE)
        {
          /* !LINKSTO ComM.EB.PncMainfunctionDataSetSIDError,1 */
          if (ComM_Multicore_EvaluateChannelMasterPncToChPncSchmSend_FctPtr_List[cntr](&ComM_EvaluateChannel_MasterPnc_To_Ch) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO ComM.EB.MasterPncToChannelSetError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_MAIN_FUNCTIONPNC, COMM_E_MASTERPNC_TO_CH_DATASET_ERROR);
#endif
          }
        }
      }
    }
#endif /* #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
    {
      uint8 cntr;
      for (cntr = 0U; cntr < COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH; cntr++)
      {
        if (ComM_SynchShutDown_MasterPnc_To_Ch_Status[cntr] == TRUE)
        {
          if (ComM_Multicore_SynchShutDownMasterPncToChSchmSend_FctPtr_List[cntr](&ComM_SynchShutDown_MasterPnc_To_Ch) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO ComM.EB.MasterPncToChannelSetError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_MAIN_FUNCTIONPNC, COMM_E_MASTERPNC_TO_CH_DATASET_ERROR);
#endif
          }
        }
      }
    }
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  }
  /* CHECK: PARSE */
}
#endif

FUNC(Std_ReturnType, COMM_CODE) ComM_IsValidConfig
(
  P2CONST(void, AUTOMATIC, COMM_APPL_CONST) voidConfigPtr
)
{
  /* Assume an invalid configuration */
  Std_ReturnType result = E_NOT_OK;
  P2CONST(ComM_ConfigType, AUTOMATIC, COMM_APPL_CONST) ConfigPtr = voidConfigPtr;

  if(ConfigPtr != NULL_PTR)
  {
    /* Check if the configuration fits to the platform */
    if(TS_PlatformSigIsValid(ConfigPtr->PlatformSignature) == TRUE )
    {
      /* Validate the post build configuration against the compile time configuration */
      if(COMM_CFG_SIGNATURE == ConfigPtr->CfgSignature)
      {
        /* Validate the post build configuration against the link time configuration */
        if(ComM_LcfgSignature == ConfigPtr->LcfgSignature)
        {
          /* Validate the Published information in post build configuration against the
           * Published information in compile time configuration
           */
          if(COMM_PUBLIC_INFO_SIGNATURE == ConfigPtr->PublicInfoSignature)
          {
            /* Indicate that the configuration is valid */
            result = E_OK;
          }
        }
      }
    }
  }
  return result;
}
#if(COMM_PNC_SUPPORT == STD_ON)
STATIC FUNC(void,COMM_CODE) ComM_PNCWakeUpIndication_PncHandle(PNCHandleType pncIdx)
{
  /* !LINKSTO ComM.SWS_ComM_00964,1 */
  COMM_PNC_EMIT(pncIdx, COMM_HSM_COMMPNC_EV_ECUM_PNCWAKEUP_IND);
  TS_PARAM_UNUSED(pncIdx);
}

FUNC(void,COMM_CODE) ComM_PNCWakeUpIndication_ChannelHandle(PNCHandleType pncIdx, boolean isPncContext)
{
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0))
  boolean SentToApplication[COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH];
  ComM_MasterPnc_To_Ch_DataType MasterPncToChData;
  ApplicationType CurrentApplication = GetApplicationID();
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)) */
#if (COMM_DCM_ENABLED == STD_ON)
  boolean PassiveStartupStatus = FALSE;
#endif
  uint8 chIdx = 0U;

#if (!((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)))
  TS_PARAM_UNUSED(isPncContext);
#endif /* #if (!((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0))) */

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
  MasterPncToChData.PncId = pncIdx;
  TS_MemSet(SentToApplication, FALSE, COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH);
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */

#if(COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
  /* Deviation TASKING-1 */
  for (chIdx = 0; chIdx < COMM_NUM_CHANNELS; chIdx++)
  {
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0))
    boolean execute = FALSE;
    if ((CurrentApplication == ComM_Multicore_ChannelOsApplication_List[chIdx]) && (isPncContext == FALSE))
    {
      execute = TRUE;
    }
    if (isPncContext == TRUE)
    {
      execute = TRUE;
    }
    if (execute == TRUE)
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)) */
    {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
      if ((ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[chIdx] != COMM_MULTICORE_INVALID_FCT_INDEX) &&
          (isPncContext == TRUE))
      {
        if (SentToApplication[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[chIdx]] == FALSE)
        {
          /* !LINKSTO ComM.EB.MasterPncToChannelCrossPartition,1 */
          /* !LINKSTO ComM.EB.PncMainfunctionDataSetSIDError,1 */
          if (ComM_Multicore_MasterPncToChPncSchmSend_FctPtr_List[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[chIdx]](&MasterPncToChData) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO ComM.EB.MasterPncToChannelSetError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_ECUM_PNC_WAKE_UP_INDICATION, COMM_E_MASTERPNC_TO_CH_DATASET_ERROR);
#endif
          }
          SentToApplication[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[chIdx]] = TRUE;
        }
      }
      else
#endif /* #if (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif  /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      {
         /* !LINKSTO ComM.EB.SWS_ComM_Channel_ComMSynchronousWakeUp_true,1 */
         /* !LINKSTO ComM.SWS_ComM_01015,1 */
#if (COMM_DCM_ENABLED == STD_ON)
        PassiveStartupStatus = ComM_DcmActiveStatus[chIdx];
        if((ComM_RequestedComMode[chIdx] == COMM_NO_COMMUNICATION) &&
           (PassiveStartupStatus == FALSE))
#else
        if(ComM_RequestedComMode[chIdx] == COMM_NO_COMMUNICATION)
#endif
        {
          ComM_PassiveStartupStatus[COMM_INST(chIdx)] = TRUE;
        }
        /* !LINKSTO ComM.EB.Dsn.StateDynamics.ECUM_PNCWAKEUP_IND_PNC_NO_COMMUNICATION,1 */
        /* !LINKSTO ComM.EB.SWS_ComM_Channel_ComMSynchronousWakeUp_false,1 */
        COMM_EMIT(chIdx, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
      }
    }
  }
  TS_PARAM_UNUSED(pncIdx);
#else
  for (chIdx = 0U; chIdx < COMM_NUM_CHANNELS_OF_PNC(pncIdx); chIdx++)
  {
    const uint8 Channel = COMM_CHANNEL_OF_PNC(pncIdx,chIdx);
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0))
    boolean execute = FALSE;
    if ((CurrentApplication == ComM_Multicore_ChannelOsApplication_List[Channel]) && (isPncContext == FALSE))
    {
      execute = TRUE;
    }
    if (isPncContext == TRUE)
    {
      execute = TRUE;
    }
    if (execute == TRUE)
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)) */
    {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
      if ((ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[Channel] != COMM_MULTICORE_INVALID_FCT_INDEX) &&
          (isPncContext == TRUE))
      {
        if (SentToApplication[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[Channel]] == FALSE)
        {
          /* !LINKSTO ComM.EB.MasterPncToChannelCrossPartition,1 */
          /* !LINKSTO ComM.EB.PncMainfunctionDataSetSIDError,1 */
          if (ComM_Multicore_MasterPncToChPncSchmSend_FctPtr_List[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[Channel]](&MasterPncToChData) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO ComM.EB.MasterPncToChannelSetError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_ECUM_PNC_WAKE_UP_INDICATION, COMM_E_MASTERPNC_TO_CH_DATASET_ERROR);
#endif
          }
          SentToApplication[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[Channel]] = TRUE;
        }
      }
      else
#endif /*#if (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif  /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      {
#if (COMM_DCM_ENABLED == STD_ON)
        PassiveStartupStatus = ComM_DcmActiveStatus[Channel];
        if((ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION) &&
           (PassiveStartupStatus == FALSE))
#else
        if(ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION)
#endif
        {
          ComM_PassiveStartupStatus[COMM_INST(Channel)] = TRUE;
        }
        /* !LINKSTO ComM.EB.Dsn.StateDynamics.ECUM_PNCWAKEUP_IND_PNC_NO_COMMUNICATION,1 */
        /* !LINKSTO ComM.EB.SWS_ComM_Channel_ComMSynchronousWakeUp_false,1 */
        COMM_EMIT(Channel, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
      }
    }
#if(COMM_VLAN_SUPPORT)
    {
      uint32 index;
      /* Deviation TASKING-1 */
      for(index=0;index<COMM_VLAN_MANAGED_CH_NB;index++)
      {
        if(ComM_VlanConfigTable[index].managedCh == Channel)
        {
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0))
          execute = FALSE;
          if ((CurrentApplication == ComM_Multicore_ChannelOsApplication_List[ComM_VlanConfigTable[index].managingCh]) && (isPncContext == FALSE))
          {
            execute = TRUE;
          }
          if (isPncContext == TRUE)
          {
            execute = TRUE;
          }
          if (execute == TRUE)
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)) */
          {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
            if ((ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[ComM_VlanConfigTable[index].managingCh] != COMM_MULTICORE_INVALID_FCT_INDEX) &&
                (isPncContext == TRUE))
            {
              if (SentToApplication[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[ComM_VlanConfigTable[index].managingCh]] == FALSE)
              {
                /* !LINKSTO ComM.EB.MasterPncToChannelCrossPartition,1 */
                /* !LINKSTO ComM.EB.PncMainfunctionDataSetSIDError,1 */
                if (ComM_Multicore_MasterPncToChPncSchmSend_FctPtr_List[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[ComM_VlanConfigTable[index].managingCh]](&MasterPncToChData) != SCHM_E_OK)
                {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
                  /* !LINKSTO ComM.EB.MasterPncToChannelSetError,1 */
                  COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_ECUM_PNC_WAKE_UP_INDICATION, COMM_E_MASTERPNC_TO_CH_DATASET_ERROR);
#endif
                }
                SentToApplication[ComM_Multicore_MasterPncToChSchmSend_FctPtr_IndexList[ComM_VlanConfigTable[index].managingCh]] = TRUE;
              }
            }
            else
#endif /*#if (COMM_OS_APPLICATION_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)*/
#endif  /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
            {
#if (COMM_DCM_ENABLED == STD_ON)
              PassiveStartupStatus = ComM_DcmActiveStatus[ComM_VlanConfigTable[index].managingCh];
              if((ComM_RequestedComMode[ComM_VlanConfigTable[index].managingCh] == COMM_NO_COMMUNICATION) &&
                 (PassiveStartupStatus == FALSE))
#else
              if(ComM_RequestedComMode[ComM_VlanConfigTable[index].managingCh] == COMM_NO_COMMUNICATION)
#endif
              {
                ComM_PassiveStartupStatus[COMM_INST(ComM_VlanConfigTable[index].managingCh)] = TRUE;
              }
              /* !LINKSTO ComM.EB.Dsn.StateDynamics.ECUM_PNCWAKEUP_IND_PNC_NO_COMMUNICATION,1 */
              /* !LINKSTO ComM.EB.SWS_ComM_Channel_ComMSynchronousWakeUp_false,1 */
              COMM_EMIT(ComM_VlanConfigTable[index].managingCh, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
            }
          }
        }
      }
    }
#endif
  }
#endif
}

#if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
STATIC FUNC(void, COMM_CODE) ComM_Internal_CopySynchronizedPncShutdownInfo(void)
{
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  SchM_Enter_ComM_1_MasterPnc_SCHM_COMM_EXCLUSIVE_AREA_MASTERPNC();
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  TS_MemCpy(&ComM_SynchronusShutDownArrLocal[0],
            &ComM_SynchronusShutDownArr[0],
            COMM_PN_INFO_LENGTH);
  TS_MemSet(&ComM_SynchronusShutDownArr[0],
            0U,
            COMM_PN_INFO_LENGTH);
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  SchM_Exit_ComM_1_MasterPnc_SCHM_COMM_EXCLUSIVE_AREA_MASTERPNC();
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
}

STATIC FUNC(void, COMM_CODE) ComM_Internal_ForwardSynchronizedPncShutdown(void)
{
  uint16 PncByte, PncBit, PncIDIdx, chIdx;
  /* Deviation TASKING-1 */
  for (PncIDIdx = 0U; PncIDIdx < COMM_NUM_PNC; PncIDIdx++)
  {
    if (COMM_IS_PNC_ACTIVE_MIXED_WITH_PASSIVE(PncIDIdx) == TRUE)
    {
      PncByte = (uint8)((ComM_PncID[PncIDIdx] >> SHIFT_3_BITS) - COMM_PN_OFFSET);
      PncBit  = (uint8)((ComM_PncID[PncIDIdx] & MASK_3_BITS));

      if (ComM_HsmScComMPnc.instances[PncIDIdx].stateId != ((ComM_HsmStateIdxType)COMM_HSM_COMMPNC_SIDX_PNCREQUESTED))
      {
        if ((ComM_SynchronusShutDownArrLocal[PncByte] & (1U << PncBit)) != 0U)
        {
          for (chIdx = 0U; chIdx < COMM_NUM_CHANNELS_OF_PNC(PncIDIdx); chIdx++)
          {
            const uint8 Channel = COMM_CHANNEL_OF_PNC(PncIDIdx,chIdx);
            if (ComM_ChannelGatewayType[Channel] == COMM_GATEWAY_TYPE_ACTIVE)
            {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
              if (ComM_Multicore_SynchShutDownMasterPncToChSchmSend_FctPtr_IndexList[Channel] != COMM_MULTICORE_INVALID_FCT_INDEX)
              {
                /* !LINKSTO ComM.EB.MasterPncToChannelCrossPartition,1 */
                ComM_SynchShutDown_MasterPnc_To_Ch.Multicore_PncList[PncIDIdx / 8U] |= (1U << (PncIDIdx % 8U));
                ComM_SynchShutDown_MasterPnc_To_Ch_Status[ComM_Multicore_SynchShutDownMasterPncToChSchmSend_FctPtr_IndexList[Channel]] = TRUE;
              }
              else
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif  /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
              {
                /* !LINKSTO ComM.EB_Ref.ASR21-11.SWS_ComM_01082.Nm_RequestSynchronizedPncShutdown,1 */
                /* !LINKSTO ComM.EB_Ref.ASR21-11.SWS_ComM_01082.COMM_PNC_REQUESTED.To.COMM_PNC_READY_SLEEP,1 */
                /* !LINKSTO ComM.EB_Ref.SWS_ComM_00829.Nm_RequestSynchronizedPncShutdown,1 */
                (void) Nm_RequestSynchronizedPncShutdown(Channel, ComM_PncID[PncIDIdx]);
              }
            }
          }
        }
      }
    }
  }
}
#endif /* #if ((COMM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON))
        */
#endif /*(COMM_PNC_SUPPORT == STD_ON)*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && \
     (COMM_NUM_USERS > 0))
FUNC(void, COMM_CODE) ComM_ClearUserRequest_Helper(
  uint8   instIdx,
  boolean isChannelContext)
{
  /* Get number of users of specific channel */
  const uint8 NumUser = COMM_NUM_USERS_OF_CHANNEL(instIdx);
  uint8_least UserIdx;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  ApplicationType CurrentApplication = GetApplicationID();
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0)
  boolean ChSentToUserApplication[COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH];
#endif /* #if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)
  boolean UserSentToChApplication[COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH];
#endif /* #if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(isChannelContext);
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0)
  TS_MemSet(ChSentToUserApplication, FALSE, COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH);
#endif /* #if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)
  TS_MemSet(UserSentToChApplication, FALSE, COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH);
#endif /* #if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED != 0) */
  /* For all users of shared channel of ComM */
  for (UserIdx = 0U; UserIdx < NumUser; ++UserIdx)
  {
    /* Get specific users of shared channel */
    const uint8 User = COMM_USERSOFCHANNEL(instIdx,UserIdx);
    boolean AllInNoCom = TRUE;
    uint8_least ChannelPos;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
    boolean execute = FALSE;
    if ((CurrentApplication == ComM_Multicore_UserOsApplication_List[User]) && (isChannelContext == FALSE))
    {
      execute = TRUE;
    }
    if (isChannelContext == TRUE)
    {
      execute = TRUE;
    }
    /* isChannelContext == FALSE is only called from User Context */
    if (execute == TRUE)
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
    {
      /* [ComM.SWS_ComM_00582]: Check if all the channels that belong to the user
       * have entered COMM_NO_COMMUNICATION mode.
       */
      for (ChannelPos = 0U; ChannelPos < COMM_NUM_CHANNELS_OF_USER(User); ++ChannelPos)
      {
        const uint8 Channel = COMM_CHANNEL_OF_USER(User,ChannelPos);
        /* Check current communication mode of the channel  */
        if (COMM_NO_COMMUNICATION < ComM_ChannelMode[Channel])
        {
          /* At least one channel has not yet reached COMM_NO_COMMUNICATION.
           * Reset the flag and leave the loop.
           */
          AllInNoCom = FALSE;
          break;
        }
      }

      /* Clear the user request if all the channels that belong to the user
       * have entered COMM_NO_COMMUNICATION mode
       */
      if (TRUE == AllInNoCom)
      {
#if (COMM_NUM_PNC > 0U)
        uint16 PncPos;
#endif /* #if (COMM_NUM_PNC > 0U) */

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0)
        /* In case data needs to be transfered from Channel Partition to User Partition */
        if ((ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[instIdx][User] != COMM_MULTICORE_INVALID_FCT_INDEX) &&
            (isChannelContext == TRUE))
        {
          if (ChSentToUserApplication[ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[instIdx][User]] == FALSE)
          {
            ComM_Ch_To_User_DataType data;
            data.Operation = COMM_MULTICORE_CLEAR_USER_REQUEST;
            data.Channel = instIdx;
            /* !LINKSTO ComM.EB.ChannelToUserCrossPartition,1 */
            if (ComM_Multicore_ChToUserSchmSend_FctPtr_List[ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[instIdx][User]](&data) != SCHM_E_OK)
            {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO ComM.EB.ChannelToUserSetError,1 */
              COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_MAIN_FUNCTION, COMM_E_CH_TO_USER_DATASET_ERROR);
#endif
            }
            ChSentToUserApplication[ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[instIdx][User]] = TRUE;
          }
        }
        else
#endif /*#if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0)*/
        {
          ComM_UserRequestedComMode[User] = COMM_NO_COMMUNICATION;
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0))
          TS_MemSet(UserSentToChApplication, FALSE, COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH);
#endif /* #if ((COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0) && (COMM_OS_APPLICATION_MULTICORE_ENABLED != 0)) */

          for (ChannelPos = 0U; ChannelPos < COMM_NUM_CHANNELS_OF_USER(User); ++ChannelPos)
          {
            const uint8 Channel = COMM_CHANNEL_OF_USER(User,ChannelPos);
#if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)
            if (ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel] != COMM_MULTICORE_INVALID_FCT_INDEX)
            {
              if (UserSentToChApplication[ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel]] == FALSE)
              {
                ComM_User_To_Ch_DataType UserToChData;
                UserToChData.User = User;
                UserToChData.Operation = COMM_MULTICORE_EVALUATE_CHANNEL;
                /* !LINKSTO ComM.EB.UserToChannelCrossPartition,1 */
                if (ComM_Multicore_UserToChSchmSend_FctPtr_List[ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel]](&UserToChData) != SCHM_E_OK)
                {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
                  if (isChannelContext == TRUE)
                  {
                    /* !LINKSTO ComM.EB.UserToChannelDataSetError,1 */
                    COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_MAIN_FUNCTION, COMM_E_USER_TO_CH_DATASET_ERROR);
                  }
                  else
                  {
                    /* !LINKSTO ComM.EB.ChannelToUserDataGetSIDError,1 */
                    /* !LINKSTO ComM.EB.UserToChannelDataSetError,1 */
                    COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_CHANNEL_TO_USER_DATA_GET, COMM_E_USER_TO_CH_DATASET_ERROR);
                  }
#endif
                }
                UserSentToChApplication[ComM_Multicore_UserToChSchmSend_FctPtr_IndexList[User][Channel]] = TRUE;
              }
            }
            else
#endif /*#if (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)*/
            {
              ComM_EvaluateChannel(Channel);
            }
          }
#if (COMM_NUM_PNC > 0U)
#if (COMM_OS_APPLICATION_USER_TO_MASTER_PNC_FCTPTR_LENGTH != 0)
          if (ComM_Multicore_UserToMasterPncSchmSend_FctPtr_IndexList[User] != COMM_MULTICORE_INVALID_FCT_INDEX)
          {
            ComM_User_To_MasterPnc_DataType UserToMasterPncData;
            UserToMasterPncData.User = User;
            UserToMasterPncData.Operation = COMM_MULTICORE_EVALUATE_PNC;
            /* !LINKSTO ComM.EB.UserToMasterPncCrossPartition,1 */
            if (ComM_Multicore_UserToMasterPncSchmSend_FctPtr_List[ComM_Multicore_UserToMasterPncSchmSend_FctPtr_IndexList[User]](&UserToMasterPncData) != SCHM_E_OK)
            {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
              if (isChannelContext == TRUE)
              {
                /* !LINKSTO ComM.EB.UserToMasterPncDataSetError,1 */
                COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_MAIN_FUNCTION, COMM_E_USER_TO_MASTERPNC_DATASET_ERROR);
              }
              else
              {
                /* !LINKSTO ComM.EB.ChannelToUserDataGetSIDError,1 */
                /* !LINKSTO ComM.EB.UserToMasterPncDataSetError,1 */
                COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_CHANNEL_TO_USER_DATA_GET, COMM_E_USER_TO_MASTERPNC_DATASET_ERROR);
              }
#endif
            }
          }
          else
#endif /*#if (COMM_OS_APPLICATION_USER_TO_MASTER_PNC_FCTPTR_LENGTH != 0)*/
          {
            for (PncPos = 0U; PncPos < COMM_NUM_PNCS_OF_USER(User); PncPos++)
            {
              const uint16 Pnc = COMM_PNC_OF_USER(User,PncPos);
              /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_RequestComMode_NO_COM_REQ_BY_ALL_COMM_USER,1 */
              ComM_EvaluatePnc(Pnc);
            }
          }
#endif /* #if (COMM_NUM_PNC > 0U) */
        }
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
        /* Call the SchM wrapper functions */
        ComM_UserRequestedComMode[User] = COMM_NO_COMMUNICATION;
        for (ChannelPos = 0U; ChannelPos < COMM_NUM_CHANNELS_OF_USER(User); ++ChannelPos)
        {
          const uint8 Channel = COMM_CHANNEL_OF_USER(User,ChannelPos);
          ComM_EvaluateChannel(Channel);
        }
#if (COMM_NUM_PNC > 0U)
        /* Clear also the requests on the PNCs
         * - otherwise, the user request is cleared, but the PNC still requests the concerned
         *   channels, when mode limitation is lifted. and the channel would wake up, although the
         *   original user request is cleared.
         */
        for (PncPos = 0U; PncPos < COMM_NUM_PNCS_OF_USER(User); PncPos++)
        {
           const uint16 Pnc = COMM_PNC_OF_USER(User,PncPos);
           /* !LINKSTO ComM.EB.Dsn.StateDynamics.ModeLimitation_NO_COM_REQ_BY_ALL_COMM_USER,1 */
           ComM_EvaluatePnc(Pnc);
        }
#endif /* #if (COMM_NUM_PNC > 0U) */
#endif/* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
      }
    }
  }
}
#endif /* ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && \
        *  (COMM_NUM_USERS > 0))
        */

FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication_Helper
(
  NetworkHandleType Channel,
  boolean isComMEcuMWakeUpIndicationContext
)
{
#if (COMM_DCM_ENABLED == STD_ON)
  boolean PassiveStartupStatus = FALSE;
#endif
  /* If COMM_SYNCHRONOUS_WAKE_UP is enabled, indicate all channels
   * a passive wakeup */
#if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0)
  ComM_Ch_To_Ch_DataType ChToChdata;
  boolean SentToApplication[COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH];
  ApplicationType CurrentApplication = GetApplicationID();
#endif /* #if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  uint8 chIdx = 0U;
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0))
  TS_MemSet(SentToApplication, FALSE, COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH);
  ChToChdata.Channel = Channel;
  ChToChdata.Operation = COMM_MULTICORE_ECUM_WAKEUP_INDICATION;
#endif /* ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_USER_TO_CH_FCTPTR_LENGTH != 0)) */
  /* Set Event for EcuM wakeup indication */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_EcuM_WakeUpIndication_syncWU_PASSIVE_WAKEUP_IND,1, ComM.SWS_ComM_00694,1 */
  /* Deviation TASKING-1 */
  for (chIdx = 0; chIdx < COMM_NUM_CHANNELS; chIdx++)
  {
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0))
    boolean execute = FALSE;
    if ((CurrentApplication == ComM_Multicore_ChannelOsApplication_List[chIdx]) && (isComMEcuMWakeUpIndicationContext == FALSE))
    {
      execute = TRUE;
    }
    if (isComMEcuMWakeUpIndicationContext == TRUE)
    {
      execute = TRUE;
    }
    if (execute == TRUE)
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0)) */
    {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0)
      if ((ComM_Multicore_ChToChSchmSend_FctPtr_IndexList[Channel][chIdx] != COMM_MULTICORE_INVALID_FCT_INDEX) &&
          (isComMEcuMWakeUpIndicationContext == TRUE))
      {
        if (SentToApplication[ComM_Multicore_ChToChSchmSend_FctPtr_IndexList[Channel][chIdx]] == FALSE)
        {
          /* !LINKSTO ComM.EB.ChannelToChannelCrossPartition,1 */
          if (ComM_Multicore_ChToChSchmSend_FctPtr_List[ComM_Multicore_ChToChSchmSend_FctPtr_IndexList[Channel][chIdx]](&ChToChdata) != SCHM_E_OK)
          {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
            /* !LINKSTO ComM.EB.ChannelToChannelDataSetError,1 */
            COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_ECUM_WAKE_UP_INDICATION, COMM_E_CH_TO_CH_DATASET_ERROR);
#endif
          }
          SentToApplication[ComM_Multicore_ChToChSchmSend_FctPtr_IndexList[Channel][chIdx]] = TRUE;
        }
      }
      else
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0) */
      {
#if (COMM_DCM_ENABLED == STD_ON)
        PassiveStartupStatus = ComM_DcmActiveStatus[chIdx];
        if((ComM_RequestedComMode[chIdx] == COMM_NO_COMMUNICATION) &&
           (PassiveStartupStatus == FALSE))
#else
        if(ComM_RequestedComMode[chIdx] == COMM_NO_COMMUNICATION)
#endif
        {
          ComM_PassiveStartupStatus[COMM_INST(chIdx)] = TRUE;
        }
        COMM_EMIT(chIdx, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
      }
    }
  }
  TS_PARAM_UNUSED(Channel);
#if (COMM_PNC_SUPPORT == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  if (isComMEcuMWakeUpIndicationContext == TRUE)
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  {
    if( COMM_PNC_ENABLED )
    {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_MASTER_PNC_FCTPTR_LENGTH != 0)
      if (ComM_Multicore_ChToMasterPncSchmSend_FctPtr_IndexList[Channel] != COMM_MULTICORE_INVALID_FCT_INDEX)
      {
        ComM_Ch_To_MasterPnc_DataType ChToMasterPncdata;
        ChToMasterPncdata.Operation = COMM_MULTICORE_ECUM_WAKEUP_EMIT_PNCPASSIVE_WAKEUP_IND;
        /* !LINKSTO ComM.EB.ChannelToMasterPncCrossPartition,1 */
        if (ComM_Multicore_ChToMasterPncSchmSend_FctPtr_List[ComM_Multicore_ChToMasterPncSchmSend_FctPtr_IndexList[Channel]](&ChToMasterPncdata) != SCHM_E_OK)
        {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO ComM.EB.ChannelToMasterPncDataSetError,1 */
          COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_ECUM_WAKE_UP_INDICATION, COMM_E_CH_TO_MASTERPNC_DATASET_ERROR);
#endif
        }
      }
      else
#endif /*#if (COMM_OS_APPLICATION_CH_TO_MASTER_PNC_FCTPTR_LENGTH != 0)*/
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)*/
      {
        /* !LINKSTO ComM.EB.Dsn.StateDynamics.ECUM_WAKEUP_IND_PNC_NO_COMMUNICATION,1 */
        /* !LINKSTO ComM.EB.Dsn.StateDynamics.ECUM_WAKEUP_IND,1 */
        (void)ComM_HsmEmit(&ComM_HsmScComMPnc, COMM_HSM_COMMPNC_EV_ECUM_WAKEUP_IND);
      }
    }
  }
#endif
#else /*COMM_SYNCHRONOUS_WAKE_UP*/
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  if (isComMEcuMWakeUpIndicationContext == TRUE)
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  {
#if (COMM_DCM_ENABLED == STD_ON)
    PassiveStartupStatus = ComM_DcmActiveStatus[Channel];
    if((ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION) &&
       (PassiveStartupStatus == FALSE))
#else
    if(ComM_RequestedComMode[Channel] == COMM_NO_COMMUNICATION)
#endif
    {
      ComM_PassiveStartupStatus[COMM_INST(Channel)] = TRUE;
    }
    /* Set Event for EcuM wakeup indication */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComM_EcuM_WakeUpIndication_PASSIVE_WAKEUP_IND,1 */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
  }

#if(COMM_VLAN_SUPPORT)
  {
    uint32 index;
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0)
    ComM_Ch_To_Ch_DataType ChToChdata;
    ApplicationType CurrentApplication = GetApplicationID();
#endif /* #if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0) */
#endif /*#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
    /* Deviation TASKING-1 */
    for(index=0;index<COMM_VLAN_MANAGED_CH_NB;index++)
    {
      if(ComM_VlanConfigTable[index].managedCh == Channel)
      {
#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0))
        boolean execute = FALSE;
        if ((CurrentApplication == ComM_Multicore_ChannelOsApplication_List[ComM_VlanConfigTable[index].managingCh]) && (isComMEcuMWakeUpIndicationContext == FALSE))
        {
          execute = TRUE;
        }
        if (isComMEcuMWakeUpIndicationContext == TRUE)
        {
          execute = TRUE;
        }
        if (execute == TRUE)
#endif /* #if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0)) */
        {
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0)
          if ((ComM_Multicore_ChToChSchmSend_FctPtr_IndexList[Channel][ComM_VlanConfigTable[index].managingCh] != COMM_MULTICORE_INVALID_FCT_INDEX) &&
              (isComMEcuMWakeUpIndicationContext == TRUE))
          {
            ChToChdata.Channel = Channel;
            ChToChdata.Operation = COMM_MULTICORE_ECUM_WAKEUP_INDICATION;
            /* !LINKSTO ComM.EB.ChannelToChannelCrossPartition,1 */
            if (ComM_Multicore_ChToChSchmSend_FctPtr_List[ComM_Multicore_ChToChSchmSend_FctPtr_IndexList[Channel][ComM_VlanConfigTable[index].managingCh]](&ChToChdata) != SCHM_E_OK)
            {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO ComM.EB.ChannelToChannelDataSetError,1 */
              COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_ECUM_WAKE_UP_INDICATION, COMM_E_CH_TO_CH_DATASET_ERROR);
#endif
            }
          }
          else
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_OS_APPLICATION_CH_TO_CH_FCTPTR_LENGTH != 0) */
          {
#if (COMM_DCM_ENABLED == STD_ON)
            PassiveStartupStatus = ComM_DcmActiveStatus[ComM_VlanConfigTable[index].managingCh];
            if((ComM_RequestedComMode[ComM_VlanConfigTable[index].managingCh] == COMM_NO_COMMUNICATION) &&
               (PassiveStartupStatus == FALSE))
#else
            if(ComM_RequestedComMode[ComM_VlanConfigTable[index].managingCh] == COMM_NO_COMMUNICATION)
#endif
            {
              ComM_PassiveStartupStatus[COMM_INST(ComM_VlanConfigTable[index].managingCh)] = TRUE;
            }
            COMM_EMIT(ComM_VlanConfigTable[index].managingCh, COMM_HSM_COMM_EV_PASSIVE_WAKEUP_IND);
          }
        }
        break;
      }
    }
  }
#endif

#if ((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_HSM_INST_MULTI_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(Channel);
#endif
#endif
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(isComMEcuMWakeUpIndicationContext);
#endif /* #if #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */
}

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0)
FUNC(void, COMM_CODE) ComM_Multicore_Inhibition_To_Ch_Helper
(
  P2CONST(ComM_Inhibition_To_Ch_DataType, AUTOMATIC, AUTOMATIC) data
)
{
  if (data->Operation == COMM_MULTICORE_EMIT_WAKEUP_INHIBITION)
  {
    COMM_EMIT(data->Channel, COMM_HSM_COMM_EV_WAKEUP_INHIBITION);
  }
  if (data->Operation == COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM)
  {
    COMM_EMIT(data->Channel, COMM_HSM_COMM_EV_LIMIT_TO_NO_COM);
  }
  if (data->Operation == COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED)
  {
    COMM_EMIT(data->Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
  }
  if (data->Operation == COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM_ALL_CHANNELS)
  {
    uint8 Channel;
    ApplicationType CurrentApplication = GetApplicationID();
    for (Channel = 0U; Channel < COMM_NUM_CHANNELS; Channel++)
    {
      if(CurrentApplication == ComM_Multicore_ChannelOsApplication_List[Channel])
      {
         COMM_EMIT(Channel, COMM_HSM_COMM_EV_LIMIT_TO_NO_COM);
      }
    }
  }
  if (data->Operation == COMM_MULTICORE_EMIT_REQ_STATUS_CHANGED_ALL_CHANNELS)
  {
    uint8 Channel;
    ApplicationType CurrentApplication = GetApplicationID();
    for (Channel = 0U; Channel < COMM_NUM_CHANNELS; Channel++)
    {
      if(CurrentApplication == ComM_Multicore_ChannelOsApplication_List[Channel])
      {
        COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
      }
    }
  }
}
#endif /* #if (COMM_OS_APPLICATION_INHIBITION_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0)
FUNC(void, COMM_CODE) ComM_Multicore_Ch_To_Inhibition_Helper
(
  P2CONST(ComM_Ch_To_Inhibition_DataType, AUTOMATIC, AUTOMATIC) data
)
{
  if (data->Operation == COMM_MULTICORE_COMM_PREVENT_WAKEUP_TRUE)
  {
    ComM_SetChannelComMInhibitionStatus(data->Channel, COMM_PREVENT_WAKEUP, TRUE, NULL_PTR);
  }
  if (data->Operation == COMM_MULTICORE_COMM_PREVENT_WAKEUP_FALSE)
  {
    ComM_SetChannelComMInhibitionStatus(data->Channel, COMM_PREVENT_WAKEUP, FALSE, NULL_PTR);
  }
  if (data->Operation == COMM_MULTICORE_COMM_LIMIT_NOCOM_TRUE)
  {
    ComM_SetChannelComMInhibitionStatus(data->Channel, COMM_LIMIT_NOCOMM, TRUE, NULL_PTR);
  }
  if(data->Operation == COMM_MULTICORE_COMM_LIMIT_NOCOM_FALSE)
  {
    ComM_SetChannelComMInhibitionStatus(data->Channel, COMM_LIMIT_NOCOMM, FALSE, NULL_PTR);
  }
}
#endif /* #if (COMM_OS_APPLICATION_CH_TO_INHIBITION_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0)
FUNC(void, COMM_CODE) ComM_Multicore_EvaluateChannel_MasterPnc_To_Ch_Helper
(
  P2CONST(ComM_EvaluateChannel_MasterPnc_To_Ch_DataType, AUTOMATIC, COMM_APPL_DATA) data
)
{
  uint8 Channel;
  ApplicationType CurrentApplication;
  CurrentApplication = GetApplicationID();
  for (Channel = 0U; Channel < COMM_NUM_CHANNELS; Channel++)
  {
    if(CurrentApplication == ComM_Multicore_ChannelOsApplication_List[Channel])
    {
      if ((data->MulticoreChannelList[Channel / 8U] & ( 1U << (Channel % 8U))) != 0U)
      {
        ComM_EvaluateChannel(Channel);
        COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
        if ((data->MulticoreOperationList[Channel] & COMM_MULTICORE_OP_WAKEUPSLEEPREQUEST) != 0U)
        {
          COMM_EMIT_TO_SELF(Channel, COMM_HSM_COMM_EV_BUSSM_REQUEST_FULL_COM_WITH_WAKEUP_REQUEST);
        }
        if ((data->MulticoreOperationList[Channel] & COMM_MULTICORE_OP_PNCNMREQUEST) != 0U)
        {
          COMM_EMIT(Channel, COMM_HSM_COMM_EV_PNC_NM_REQUEST);
        }
      }
    }
  }
}
#endif /* #if (COMM_OS_APPLICATION_EVALUATE_CHANNEL_MASTER_PNC_TO_CH_FCTPTR_LENGTH != 0) */
#if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0)
FUNC(void, COMM_CODE) ComM_Multicore_SynchShutDown_MasterPnc_To_Ch_Helper
(
  P2CONST(ComM_SynchShutDown_MasterPnc_To_Ch_DataType, AUTOMATIC, COMM_APPL_DATA) data
)
{
  uint16 pncIdx = 0U;
  uint8 chIdx;
  ApplicationType CurrentApplication = GetApplicationID();
  for (pncIdx = 0; pncIdx < COMM_NUM_PNC; pncIdx++)
  {
    if ((data->Multicore_PncList[pncIdx / 8U] & (1U << (pncIdx % 8U))) != 0U)
    {
      for (chIdx = 0U; chIdx < COMM_NUM_CHANNELS_OF_PNC(pncIdx); chIdx++)
      {
        const uint8 Channel = COMM_CHANNEL_OF_PNC(pncIdx,chIdx);
        if(CurrentApplication == ComM_Multicore_ChannelOsApplication_List[Channel])
        {
          /* !LINKSTO ComM.EB_Ref.ASR21-11.SWS_ComM_01082.Nm_RequestSynchronizedPncShutdown,1 */
          /* !LINKSTO ComM.EB_Ref.ASR21-11.SWS_ComM_01082.COMM_PNC_REQUESTED.To.COMM_PNC_READY_SLEEP,1 */
          /* It shall cover the case when all coordinated channels for a pnc are active and
           * it shall cover the case when forwarding the shut down information only on active channels
           */
#if (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON)
          if (ComM_ChannelGatewayType[Channel] == COMM_GATEWAY_TYPE_ACTIVE)
#endif /* #if (COMM_SYNCRONIZED_SHUTDOWN_CHANNEL_GATEWAY_TYPE_ACTIVE_MIXED_WITH_PASSIVE == STD_ON)*/
          {
            (void) Nm_RequestSynchronizedPncShutdown(Channel, ComM_PncID[pncIdx]);
          }
        }
      }
    }
  }
}
#endif /* #if (COMM_OS_APPLICATION_SYNCHSHUTDOWN_MASTERPNC_TO_CH_FCTPTR_LENGTH != 0) */
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */

#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*==================[end of file]===========================================*/
