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

/* Implementation of the state handler functions of the state machine
 * ComM.
 *
 * This file contains the implementation of the state functions.  It
 * is generated but must be edited to implement the real actions.  If the
 * state machine model is updated and the code generator regenerates the
 * files the user must manually merge the changes with any existing hand
 * written code.
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
 *
 * MISRAC2012-3) Deviated Rule: 20.10 (advisory)
 * The # and ## preprocessor operators should not be used.
 *
 * Reason:
 * Encapsulation of generic code into macros improves readability by reducing redundant code.
 *
 * MISRAC2012-4) Deviated Rule: 13.5 (required)
 * The right hand operand of a logical && or || operator shall not contain persistent side effects.
 *
 * Reason:
 * Function like macros and functions are used to read configuration settings and variables.
 * These constructs are free of side effects.
 */

/* CHECK: RULE 301 OFF (this file is partly generated, some lines may be
 * longer then 100 characters) */

/*==================[inclusions]============================================*/

/* prevent RTE symbols defined in ComM.h to be visible for ComM's .c files */
#if (defined COMM_INTERNAL_USAGE)
#error COMM_INTERNAL_USAGE already defined
#endif
#define COMM_INTERNAL_USAGE

#include <ComM_Trace.h>
#include <ComM_BSW.h>
#include <ComM_BSW_Cfg.h>
#include <ComM_Int.h>

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
#include <ComM_Nm.h>             /* NM callback APIs */
#include <NmStack_Types.h> /* Nm stack specific types, includes Std_Types.h */

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.Nm,1 */
#include <Nm.h>                /* Network Management Identifiers */
#endif /* (COMM_NM_ACCESS_NEEDED == STD_ON) */

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.Dcm,1 */
#if (COMM_DCM_ENABLED == STD_ON)
#include <Dcm_Cbk.h>            /* Diagnostic communication manager */
#endif

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00506.BswM,1 */
#include <BswM_ComM.h>

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
#include <Det.h>               /* Det API */
#endif

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
#include <Os.h>
#endif
#include <TSMem.h>

/*==================[macros]================================================*/

#if (defined COMM_PARAM_UNUSED)
#error COMM_PARAM_UNUSED already defined
#endif

#if (COMM_HSM_INST_MULTI_ENABLED == STD_ON)
#define COMM_PARAM_UNUSED(instIdx)      TS_PARAM_UNUSED(instIdx)
#else
#define COMM_PARAM_UNUSED(instIdx)      /* nothing */
#endif

#if (defined ComM_StartTimer)
#error ComM_StartTimer already defined
#endif
#define ComM_StartTimer(Channel,Event,StartValue) \
  do                                              \
  {                                               \
    COMM_TIMEOUT_EVENT(Channel) = (Event);        \
    COMM_TIMER(Channel)         = (StartValue);   \
  } while (0)

#if (defined ComM_StopTimer)
#error ComM_StopTimer already defined
#endif
#define ComM_StopTimer(a)  ComM_StartTimer(a, COMM_HSM_EVENT_INVALID, 0U)

/* Define wrapper to NM functions only if ComM requires Nm access */
#if (COMM_NM_ACCESS_NEEDED == STD_ON)

/* !LINKSTO ComM.EB.Dsn.ErrorHandling.Nm_PassiveStartup,1
 */
/* !LINKSTO ComM.EB.Dsn.ErrorHandling.Nm_NetworkRequest,1
 */
/* !LINKSTO ComM.EB.Dsn.ErrorHandling.Nm_NetworkRelease,1
 */
/** \brief Call wrapper to Nm_*() functions */
#if (defined COMM_NM_CALL)
#error COMM_NM_CALL already defined
#endif
/* Deviation MISRAC2012-3 */
#define COMM_NM_CALL(func,channel) ((void)Nm_##func(COMM_NM_CHANNEL_OF_CHANNEL(channel)))

/** \brief Call wrapper to call Nm_PassiveStartUp() */
#if (defined COMM_NM_PASSIVESTARTUP)
#error COMM_NM_PASSIVESTARTUP already defined
#endif
#define COMM_NM_PASSIVESTARTUP(channel) COMM_NM_CALL(PassiveStartUp,channel)
/** \brief Call wrapper to call Nm_NetworkRelease() */
#if (defined COMM_NM_NETWORKRELEASE)
#error COMM_NM_NETWORKRELEASE already defined
#endif
#define COMM_NM_NETWORKRELEASE(channel) COMM_NM_CALL(NetworkRelease,channel)
/** \brief Call wrapper to call Nm_NetworkRequest() */
#if (defined COMM_NM_NETWORKREQUEST)
#error COMM_NM_NETWORKREQUEST already defined
#endif
#define COMM_NM_NETWORKREQUEST(channel) COMM_NM_CALL(NetworkRequest,channel)
/** \brief Call wrapper to call Nm_NetworkGwEraRequest() */
#if (defined COMM_NM_NETWORKGWERAREQUEST)
#error COMM_NM_NETWORKGWERAREQUEST already defined
#endif
#define COMM_NM_NETWORKGWERAREQUEST(channel) COMM_NM_CALL(NetworkGwEraRequest,channel)
#endif  /* COMM_NM_ACCESS_NEEDED == STD_ON */

/* !LINKSTO ComM.EB.Dsn.ErrorHandling.BusSm,1 */
/** \brief Call wrapper for bus state manager function
 * <Bus>SM_GetCurrentComMode() */

#if (COMM_MULTICORE_ENABLED == STD_OFF)
#if (defined COMM_BUSSM_REQUEST_COM_MODE)
#error COMM_BUSSM_REQUEST_COM_MODE already defined
#endif
#define COMM_BUSSM_REQUEST_COM_MODE(channel, mode)                           \
  ((void) ComM_BusSMRequestComModeFpList[COMM_BUSTYPE_OF_CHANNEL(channel)]  \
  (COMM_INST(channel), (mode)))
#endif /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */

#if (defined COMM_CHANNEL_NOCOM_INHIBITION_STATUS)
#error COMM_CHANNEL_NOCOM_INHIBITION_STATUS already defined
#endif
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Evaluate NoCom Inhibition status for ComM channels
 *
 * Always FALSE if mode limitation is disabled. */
#define COMM_CHANNEL_NOCOM_INHIBITION_STATUS(a)        \
  ComM_ChannelNoComInhibitionStatus(COMM_INST(a))
#else
#define COMM_CHANNEL_NOCOM_INHIBITION_STATUS(a)  FALSE
#endif

#if (defined COMM_CHANNEL_WAKEUP_INHIBITION_STATUS)
#error COMM_CHANNEL_WAKEUP_INHIBITION_STATUS already defined
#endif
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief WakeUp Inhibition status for ComM channels
 *
 * always FALSE if wakeup inhibition is disabled. */
#define COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(a)       \
  ComM_ChannelWakeUpInhibitionStatus(COMM_INST(a))
#else
#define COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(a) FALSE
#endif

/** \brief Time counter value for checking the timeouts of different states */
#if (defined COMM_TIMER)
#error COMM_TIMER already defined
#endif
#define COMM_TIMER(Channel)                     \
  COMM_INST_ACCESS(ComM_Timer,Channel)

/** \brief Time counter value for checking the timeouts of different states */
#if (defined COMM_TIMEOUT_EVENT)
#error COMM_TIMEOUT_EVENT already defined
#endif
#define COMM_TIMEOUT_EVENT(Channel)             \
  COMM_INST_ACCESS(ComM_TimeoutEvent,Channel)

/** \brief Current mode of the ComM Channel. */
#if (defined COMM_CHANNELMODE)
#error COMM_CHANNELMODE already defined
#endif
#define COMM_CHANNELMODE(Channel)               \
  COMM_INST_ACCESS(ComM_ChannelMode,Channel)

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Current mode of the ComM Channel before ComM_ClearUserRequest was called. */
#if (defined COMM_CHANNELMODE_PREVIOUS)
#error COMM_CHANNELMODE_PREVIOUS already defined
#endif
#define COMM_CHANNELMODE_PREVIOUS(Channel)               \
  COMM_INST_ACCESS(ComM_ChannelModePrevious,Channel)
#endif


/** \brief Current state of the ComM Channel. */
#if (defined COMM_CHANNELSTATE)
#error COMM_CHANNELSTATE already defined
#endif
#define COMM_CHANNELSTATE(Channel)               \
  COMM_INST_ACCESS(ComM_ChanState,Channel)

/** \brief Currently requested ComM Mode. */
#if (defined COMM_REQUESTEDCOMMODE)
#error COMM_REQUESTEDCOMMODE already defined
#endif
#define COMM_REQUESTEDCOMMODE(Channel)                  \
  COMM_INST_ACCESS(ComM_RequestedComMode,Channel)


#if (defined COMM_PASSIVEEXECUTED)
#error COMM_PASSIVEEXECUTED already defined
#endif
#define COMM_PASSIVEEXECUTED(Channel)                  \
  COMM_INST_ACCESS(ComM_PassiveExecuted,Channel)

/** \brief Currently requested ComM Mode. */
#if (defined COMM_REQUESTEDCOMMODEWITHOUTPNC)
#error COMM_REQUESTEDCOMMODEWITHOUTPNC already defined
#endif
#define COMM_REQUESTEDCOMMODEWITHOUTPNC(Channel)                  \
  COMM_INST_ACCESS(ComM_RequestedComModeWithoutPnc,Channel)

/** \brief Currently requested ComM Mode. */
#if (defined COMM_REQUESTEDCOMMODEWAKEUPSLEEPREQUEST)
#error COMM_REQUESTEDCOMMODEWAKEUPSLEEPREQUEST already defined
#endif
#define COMM_REQUESTEDCOMMODEWAKEUPSLEEPREQUEST(Channel)                  \
  COMM_INST_ACCESS(ComM_RequestedComModeWakeupSleepRequest,Channel)

/** \brief Ready Sleep Timeout. */
#if (defined COMM_READYSLEEPNONMTIMEOUTMS)
#error COMM_READYSLEEPNONMTIMEOUTMS already defined
#endif
#define COMM_READYSLEEPNONMTIMEOUTMS(Channel)                   \
  COMM_INST_ACCESS(ComM_ReadySleepNoNmTimeoutMs,Channel)

/** \brief Full Com Mode Duration. */
#if (defined COMM_MIN_FULL_COM_MODE_DURATION)
#error COMM_MIN_FULL_COM_MODE_DURATION already defined
#endif
#define COMM_MIN_FULL_COM_MODE_DURATION(Channel)                   \
  COMM_INST_ACCESS(ComM_NetReqNoNmTimeoutMs,Channel)

/** \brief Startup mode for each channel. */
#if (defined COMM_CHANNELPASSIVEWAKEUP)
#error COMM_CHANNELPASSIVEWAKEUP already defined
#endif
#define COMM_CHANNELPASSIVEWAKEUP(Channel)                   \
  COMM_INST_ACCESS(ComM_ChannelPassiveWakeup,Channel)

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/

/*==================[type definitions]======================================*/

/** \brief Function pointer type for the bus state manager functions to
 ** request a new communication mode. */
typedef P2FUNC(Std_ReturnType, COMM_APPL_CODE, ComM_BusSMRequestComModeType)(
  NetworkHandleType Channel,
  uint8             ComMode);

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>

#if (((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)) || \
     ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)))
/** \brief Notify the DCM via SchM mechanism
 ** \param[in] PctPtr Function pointer for Full Communication, Silent Communication, No communication SchM functions
 ** \param[in] Channel chanel for which the reporting shall be done
 ** \param[in] errorId errorId for which the DET will be called in case SchM notification fails
 */
STATIC FUNC(void, COMM_CODE) ComM_DcmMcNotify(
  ComM_Dcm_Notif_FctPtr  FctPtr,
  uint8                  Channel,
  uint8                  errorId
  );
#endif /* #if (((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)) || \
        *     ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)))
        */

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && (COMM_NUM_USERS > 0))
 /** \brief Clears all ComM requests
 **
 ** This function clears all ComM user requests and set the state to No
 ** ComMode.
 **
 ** \param[in] instIdx index of state machine instance.
 ** \param[in] tryClear try to clear user request despite the mode indication from State manager. */
STATIC FUNC(void, COMM_CODE) ComM_ClearUserRequest(
  uint8   instIdx,
  boolean tryClear
  );
#endif

/** \brief Evaluate if the channel can be requested.
 **
 ** This function checks if the channel is requested by the Dcm or by a user and mode limitation is
 ** not active.
 **
 ** \param[in] Channel Network channel which shall be requested.
 */
/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsFullComAllowed(
  COMM_PDL_SF(uint8 Channel));

/** \brief Evaluate if the channel is allowed to wake up from 'No Communication'.
 **
 ** This function checks if the channel is requested by the Dcm or by any user and no
 ** mode inhibition is active.
 **
 ** \param[in] Channel Network channel which shall be requested.
 */
/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsWakeupAllowed(
  COMM_PDL_SF(uint8 Channel));

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Evaluate if the channel can be limited to no communication.
 **
 ** This function checks if the channel has limit to no communication set and
 ** is not passively requested and it is not requested by the DCM
 **
 ** \param[in] Channel Network channel which shall be requested.
 */
/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsLimitToNoCom(
  COMM_PDL_SF(uint8 Channel));
#endif /* #if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief Evaluate if the channel can be inhibited for wakeup.
 **
 ** This function checks if the channel has wakeup inhibition set and
 ** is not passively requested and it is not requested by the DCM
 **
 ** \param[in] Channel Network channel which shall be requested.
 */
/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsWakeupInhibition(
  COMM_PDL_SF(uint8 Channel));
#endif /* #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */

/** \brief Evaluate if the channel is not requested.
 **
 ** This function checks if the channel is:
 ** - not requested bythe user and
 ** - not requested passively and
 ** - not requested by the DCM
 **
 ** \param[in] Channel Network channel which shall be requested.
 */
/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsNotRequested(
  COMM_PDL_SF(uint8 Channel));

#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

#if (COMM_MULTICORE_ENABLED == STD_OFF)
#define COMM_START_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>

/** \brief Stores function pointer for bus specific state managers **/
STATIC CONST(ComM_BusSMRequestComModeType, COMM_CONST)
  ComM_BusSMRequestComModeFpList[5] =
{
#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00854,1, ComM.SWS_ComM_00402,1, ComM.SWS_ComM_00664,1, ComM.EB_Ref.SWS_ComM_00962.CanSM,1 */
  &CanSM_RequestComMode,         /* COMM_BUS_TYPE_CAN = 0 */
#else
  NULL_PTR,                /* never accessed if no CAN channel is available */
#endif
#if (COMM_ETHSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00859,1, ComM.EB_Ref.SWS_ComM_00962.EthSM,1 */
  &EthSM_RequestComMode,         /* COMM_BUS_TYPE_ETH = 1 */
#else
  NULL_PTR,                /* never accessed if no ETH channel is available */
#endif
#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00852,1, ComM.EB_Ref.SWS_ComM_00962.FrSM,1 */
  &FrSM_RequestComMode,          /* COMM_BUS_TYPE_FR = 2 */
#else
  NULL_PTR,                 /* never accessed if no FR channel is available */
#endif
  NULL_PTR,                 /* COMM_BUS_TYPE_INTERNAL = 3 */
#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
  /* !LINKSTO ComM.ASR403.SWS_ComM_00856,1, ComM.EB_Ref.SWS_ComM_00962.LinSM,1 */
  &LinSM_RequestComMode         /* COMM_BUS_TYPE_LIN = 4 */
#else
  NULL_PTR                /* never accessed if no LIN channel is available */
#endif
};

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <ComM_MemMap.h>
#endif
/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#define COMM_START_SEC_VAR_CLEARED_16
#include <ComM_MemMap.h>

/** \brief Time counter value for checking the timeouts of different states */
/* Deviation MISRAC2012-2 */
STATIC VAR(uint16, COMM_VAR) ComM_Timer[COMM_NUM_CHANNELS];

#define COMM_STOP_SEC_VAR_CLEARED_16
#include <ComM_MemMap.h>

#define COMM_START_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>

/** \brief Event to be sent on timeout */
/* Deviation MISRAC2012-2 */
STATIC VAR(ComM_HsmEventType, COMM_VAR) ComM_TimeoutEvent[COMM_NUM_CHANNELS];

/** \brief Flag for passive wakeup. */
STATIC VAR(boolean, COMM_VAR) ComM_ChannelPassiveWakeup[COMM_NUM_CHANNELS];


#define COMM_STOP_SEC_VAR_CLEARED_8
#include <ComM_MemMap.h>


/*==================[external function definitions]=========================*/

#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>

/* ************************ state functions ******************************* */

/* ************************************************************************
 * State: TOP
 * Parent state: none
 * Init substate: NO_COMMUNICATION
 * Transitions originating from this state:
 * 1) BUSSM_MODE_IND[]/ComM_Notify(ComM_ChannelMode); ComM_ClearUserRequest();
 */


/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfTOPAction1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* action 'ComM_Notify(ComM_ChannelMode); ComM_ClearUserRequest();'
   * for BUSSM_MODE_IND[]/...
   * internal transition */
  /* !LINKSTO ComM.EB.Dsn.Algorithm.ModePropagation,1 */
  ComM_Notify(((uint8)instIdx), (COMM_CHANNELMODE(instIdx)));
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && (COMM_NUM_USERS > 0))
  ComM_ClearUserRequest(COMM_INST((uint8)instIdx), FALSE);
#endif
}

/* ************************************************************************
 * State: FULL_COMMUNICATION
 * Parent state: TOP
 * Init substate: FULL_COM_NETWORK_REQUESTED
 * Transitions originating from this state:
 * 1) BUSSM_REQUEST_FULL_COM_WITH_WAKEUP_REQUEST[]/COMM_BUSSM_REQUEST_COM_MODE(COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST)
 * 2) FULL_COMMUNICATION -> NO_COMMUNICATION: BUS_SM_SLEEP_INDICATION[]/
 * 3) FULL_COMMUNICATION -> NO_COMMUNICATION: NM_MODE_SWITCHED[(ComM_NmGetMode() == NM_MODE_BUS_SLEEP)]/
 */

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COMMUNICATIONEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* entry action 'if (COMM_BUS_TYPE_INTERNAL== ComMBusType) ComM_Notify(COMM_FULL_COMMUNICATION);if (COMM_BUS_TYPE_INTERNAL!= ComMBusType) ComM_BusSmRequestComMode(COMM_FULL_COMMUNICATION);' */
#if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON)
#if ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) && (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON))
  if (COMM_BUS_TYPE_INTERNAL == COMM_BUSTYPE_OF_CHANNEL(instIdx))
#endif
  {
    ComM_Notify(((uint8)instIdx), (COMM_FULL_COMMUNICATION));
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
    COMM_CHANNELMODE_PREVIOUS(instIdx) = COMM_FULL_COMMUNICATION;
#endif
  }
#endif

#if ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) || \
     ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_OFF) && (COMM_BUSTYPE_INTERNAL_NEEDED == STD_OFF)))
#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON)
  if (COMM_BUS_TYPE_INTERNAL != COMM_BUSTYPE_OF_CHANNEL(instIdx))
#endif /*#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) */
  {
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00069.BusSMRequest.COMM_FULL_COMMUNICATION.WithRequest.COMM_FULL_COMMUNICATION,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00069.BusSMRequest.COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST.WithRequest.COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00069.BusSMRequest.COMM_FULL_COMMUNICATION.WithRequest.COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST,1 */
    ComM_ASR40_ModeType ComMode;
    ComMode = COMM_FULL_COMMUNICATION;
#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)
    if ((ComM_WakeupSleepRequestEnabledChList[COMM_INST(instIdx)] == TRUE) &&
        (COMM_REQUESTEDCOMMODEWAKEUPSLEEPREQUEST(instIdx) == COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST))
    {
      ComMode = COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST;
    }
#endif /*#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)*/
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.BusSM_RequestComMode,1 */
    /* !LINKSTO ComM.SWS_ComM_01020,1 */
#if (COMM_MULTICORE_ENABLED == STD_OFF)
    COMM_BUSSM_REQUEST_COM_MODE((uint8)instIdx, ComMode);
#endif
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_OFF))
    if(COMM_BUSSM_REQUEST_COM_MODE((uint8)instIdx, ComMode) != SCHM_E_OK)
    {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO ComM.EB.SchM_Call_Client_Server_DET,1 */
      COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID,
                            COMM_SID_MAIN_FUNCTION,
                            COMM_E_BUSSM_REQUESTCOMMODE);
#endif
    }
#endif /* #if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_OFF)) */
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON))
    ComM_BusSmModeToReport[COMM_INST(instIdx)] = ComMode;
#endif /* #if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)) */
  }
#endif /*#if ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) || \
        *     ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_OFF) && (COMM_BUSTYPE_INTERNAL_NEEDED == STD_OFF)))
        */
}

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COMMUNICATIONAction1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* action 'COMM_BUSSM_REQUEST_COM_MODE(COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST)'
   * for BUSSM_REQUEST_FULL_COM_WITH_WAKEUP_REQUEST[]/...
   * internal transition */
  /* !LINKSTO SWS_ComM_01057,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.FullCommunicationAction1,1 */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.BusSM_RequestComMode,1 */
  /* !LINKSTO ComM.SWS_ComM_01020,1 */
#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)
#if (COMM_MULTICORE_ENABLED == STD_ON)
  ComM_BusSmModeToReport[COMM_INST(instIdx)] = COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST;
#else
  COMM_BUSSM_REQUEST_COM_MODE((uint8)instIdx, COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST);
#endif
  /* CHECK: NOPARSE */
  /* If COMM_WAKEUPSLEEPREQUEST_ENABLED is STD_OFF then #else is not reachable
   * due to: on single core COMM_HSM_COMM_EV_BUSSM_REQUEST_FULL_COM_WITH_WAKEUP_REQUEST
   * event is guarded COMM_WAKEUPSLEEPREQUEST_ENABLED; on multicore the operation
   * that emits event COMM_HSM_COMM_EV_BUSSM_REQUEST_FULL_COM_WITH_WAKEUP_REQUEST
   * that guards this action is only set if COMM_WAKEUPSLEEPREQUEST_ENABLED is STD_ON
   *  */
#else /* #if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON) */
  COMM_PARAM_UNUSED(instIdx);
#endif /*#if (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON) */
  /* CHECK: PARSE */
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COMMUNICATIONGuard3(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition '(ComM_NmGetMode() == NM_MODE_BUS_SLEEP)'
   * for NM_MODE_SWITCHED[...]/
   * external transition to state NO_COMMUNICATION */

  boolean ret = FALSE;

#if (COMM_NM_ACCESS_NEEDED == STD_ON)

#if (COMM_MULTICORE_ENABLED == STD_ON)
  Nm_ModeType  nmMode;
#else
  Nm_StateType nmState;
  Nm_ModeType  nmMode;
#endif

  /* return value can be ignored, as the only reasons for E_NOT_OK are
   * - wrong network handles (development error, would have occurred already before)
   * - Nm is not yet initialized, but as this function is only called,
   *   when Nm has called a network indicated before, Nm must be initialized.
   */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.NM_MODE_SWITCHED_FULL_COMMUNICATION,1, ComM.SWS_ComM_00637,1 */
#if (COMM_MULTICORE_ENABLED == STD_ON)
   /* !LINKSTO ComM.EB.BusNm_GetState,1 */
   nmMode = ComM_LastNmMode[COMM_INST(instIdx)];
#else
  (void) Nm_GetState(COMM_NM_CHANNEL_OF_CHANNEL(instIdx), &nmState, &nmMode);
#endif
  ret = ((NM_MODE_BUS_SLEEP == nmMode) ? TRUE : FALSE);
#endif
  COMM_PARAM_UNUSED(instIdx);
  return ret;
}

/* ************************************************************************
 * State: FULL_COM_NETWORK_REQUESTED
 * Parent state: FULL_COMMUNICATION
 * Init substate: FULL_COM_NETWORK_REQUESTED_ENTRY
 * Transitions originating from this state:
 * 1) PNC_NM_REQUEST[]/Nm_NetworkRequest();
 * 2) FULL_COM_NETWORK_REQUESTED -> FULL_COM_READY_SLEEP: LIMIT_TO_NO_COM[!ComM_IsFullComAllowed()]/
 * 3) FULL_COM_NETWORK_REQUESTED -> SILENT_COMMUNICATION: NM_MODE_SWITCHED[(ComMNmVariant == PASSIVE) && (ComM_NmGetMode() == NM_MODE_PREPARE_BUS_SLEEP)]/
 * 4) FULL_COM_NETWORK_REQUESTED -> FULL_COM_NETWORK_REQUESTED: RE_REQUEST_NETWORK[]/
 */

/* !LINKSTO ComM.SWS_ComM_00899,1, ComM.SWS_ComM_00869,1 */
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTEDEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* entry action 'ComM_ChanState = COMM_FULL_COM_NETWORK_REQUESTED;if ((ComM_IsFullComAllowed == FALSE) && (ComMNmVariant == FULL|PASSIVE)) Nm_PassiveStartup(); if ((ComM_IsFullComAllowed == TRUE) && (ComMNmVariant == FULL)) Nm_NetworkRequest();' */
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON))
  boolean executePassiveStartup = FALSE;
#endif /* #if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON)) */
#if ((COMM_PNC_GW_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON) && (COMM_NM_VARIANT_FULL_NEEDED == STD_ON))
  boolean DcmActiveStatus = FALSE;
#endif /* ((COMM_PNC_GW_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON) && (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)) */
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON))
  boolean IsFullComAllowed = FALSE;
  IsFullComAllowed = ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx));
#endif /* ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON)) */

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
   COMM_PASSIVEEXECUTED(instIdx) = FALSE;
#endif /* #if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) */

#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON))
  if ((COMM_CHANNELSTATE(instIdx) == COMM_NO_COM_REQUEST_PENDING) ||
      (COMM_CHANNELSTATE(instIdx) == COMM_SILENT_COM))
  {
    executePassiveStartup = TRUE;
  }
#endif /* #if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON)) */

  COMM_CHANNELSTATE(instIdx) = COMM_FULL_COM_NETWORK_REQUESTED;
  /* if NmVariant is FULL, request the network */
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON))
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  if ((IsFullComAllowed == FALSE) &&
      ((COMM_NM_FULL_VARIANT    == COMM_NM_VARIANT_OF_CHANNEL(instIdx)) ||
       (COMM_NM_PASSIVE_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
      )
     )
#else
  if (IsFullComAllowed == FALSE)
#endif
  {
    /* !LINKSTO ComM.SWS_ComM_00870,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Nm_PassiveStartup,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00665.ComM_EcuM_WakeUpIndication,2 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00665.ComM_EcuM_PNCWakeUpIndication,2 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00665.ComM_EcuM_WakeUpIndication.ManagedChannel,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00665.ComM_EcuM_PNCWakeUpIndication.ManagedChannel,1 */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.LIMIT_TO_NO_COM_MODE_PASSIVE_STARTUP,1 */
    /* CHECK: NOPARSE */
    /* No parse has been added since in case interrupt occurs between ComM_HsmComMSfFULL_COM_NETWORK_REQUESTEDEntry
     * from Ready Sleep State and before calling ComM_IsFullComAllowed (which in this case evaluates to FALSE)
     * The no parse is active only for if (executePassiveStartup == FALSE)
     */
    if (executePassiveStartup == TRUE)
    {
      COMM_NM_PASSIVESTARTUP(instIdx);
    }
    /* CHECK: PARSE */
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
    COMM_PASSIVEEXECUTED(instIdx) = TRUE;
#endif /* #if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) */
  }
#endif

#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00667.Nm_NetworkRequest,1 */
  if ((IsFullComAllowed == TRUE) &&
      (COMM_NM_FULL_VARIANT    == COMM_NM_VARIANT_OF_CHANNEL(instIdx)))
#else /* (COMM_NM_VARIANT_FULL_ONLY == STD_OFF) */
  if (IsFullComAllowed == TRUE)
#endif /* (COMM_NM_VARIANT_FULL_ONLY == STD_OFF) */
  {
#if (COMM_PNC_GW_ENABLED == STD_ON)
#if (COMM_DCM_ENABLED == STD_ON)
    DcmActiveStatus = ComM_DcmActiveStatus[COMM_INST(instIdx)];
    if ((COMM_REQUESTEDCOMMODEWITHOUTPNC(instIdx) == COMM_NO_COMMUNICATION) &&
          (DcmActiveStatus == FALSE))
#else /* (COMM_DCM_ENABLED == STD_ON) */
    if (COMM_REQUESTEDCOMMODEWITHOUTPNC(instIdx) == COMM_NO_COMMUNICATION)
#endif /* (COMM_DCM_ENABLED == STD_ON) */
    {
      /* !LINKSTO ComM.EB.ComMPncGatewayEnabled.EB_NM_STACK.Disabled,1 */
      /* !LINKSTO ComM.EB.ComMPncGatewayEnabled.EB_NM_STACK.Enabled,1 */
#if ((defined EB_NM_STACK) && (EB_NM_STACK == STD_ON))
      COMM_NM_NETWORKGWERAREQUEST(instIdx);
#else /* (EB_NM_STACK == STD_ON) */
      if (executePassiveStartup == TRUE)
      {
        COMM_NM_PASSIVESTARTUP(instIdx);
      }
      COMM_NM_NETWORKREQUEST(instIdx);
#endif /* #if ((defined EB_NM_STACK) && (EB_NM_STACK == STD_ON)) */
    }
    else
#endif /* (COMM_PNC_GW_ENABLED == STD_ON) */
    {
      if (executePassiveStartup == TRUE)
      {
        if (ComM_PassiveStartupStatus[COMM_INST(instIdx)] == TRUE)
        {
          /* !LINKSTO ComM.EB.LocalUserRequest.NetworkStartIndication,1 */
          /* !LINKSTO ComM.EB.DcmRequest.NetworkStartIndication,1 */
          /* !LINKSTO ComM.EB.LocalUserRequest.RestartIndication,1 */
          /* !LINKSTO ComM.EB.DcmRequest.RestartIndication,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.True.LocalUserRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.True.DCMRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.False.LocalUserRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.False.DCMRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.False.LocalUserRequest.ManagingChannel,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.False.DCMRequest.ManagingChannel,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication.ComMSynchronousWakeUp.True.LocalUserRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication.ComMSynchronousWakeUp.True.DCMRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication.ComMSynchronousWakeUp.False.LocalUserRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication.ComMSynchronousWakeUp.False.DCMRequest,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication.ComMSynchronousWakeUp.False.LocalUserRequest.ManagingChannel,1 */
          /* !LINKSTO ComM.EB.ComM_EcuM_PNCWakeUpIndication.ComMSynchronousWakeUp.False.DCMRequest.ManagingChannel,1 */
          COMM_NM_PASSIVESTARTUP(instIdx);
        }
      }
      /* !LINKSTO ComM.SWS_ComM_00869,1 */
      /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Nm_NetworkRequest,1 */
      COMM_NM_NETWORKREQUEST(instIdx);
    }
  }
#endif /* (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) */
}
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTEDAction1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* action 'Nm_NetworkRequest();'
   * for PNC_NM_REQUEST[]/...
   * internal transition */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_NETWORK_REQUESTED_NmVariantFULL,1 */
  COMM_PARAM_UNUSED(instIdx);
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)

  /* if NmVariant is FULL, request the network */

  /* No need to check, if the NmVariant of the current channel is FULL ,
   * because the event PNC_NM_REQUEST is only emitted for channels of NmVariant FULL.
   * This is ensured by a check in the ComM.xdm and the PNC state machine.
   */
   /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Nm_NetworkRequest,1 */
  COMM_NM_NETWORKREQUEST(instIdx);

#endif
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTEDGuard2(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition '!ComM_IsFullComAllowed()'
   * for LIMIT_TO_NO_COM[...]/
   * external transition to state FULL_COM_READY_SLEEP */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.LIMIT_TO_NO_COM_FULL_COM_NETWORK_REQUESTED_0,1, ComM.EB_Ref.SWS_ComM_00890.COMM_FULL_COM_READY_SLEEP,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.LIMIT_TO_NO_COM_FULL_COM_NETWORK_REQUESTED_1,1 */
  boolean ret = FALSE;
  ret = (FALSE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTEDGuard3(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition '(ComMNmVariant == PASSIVE) && (ComM_NmGetMode() == NM_MODE_PREPARE_BUS_SLEEP)'
   * for NM_MODE_SWITCHED[...]/
   * external transition to state SILENT_COMMUNICATION */
  boolean ret = FALSE;
#if (COMM_NM_ACCESS_NEEDED == STD_ON)

#if (COMM_MULTICORE_ENABLED == STD_ON)
  Nm_ModeType  nmMode;
#else
  Nm_StateType nmState;
  Nm_ModeType  nmMode;
#endif
  /* return value can be ignored, as the only reasons for E_NOT_OK are
   * - wrong network handles (development error, would have occurred already before)
   * - Nm is not yet initialized, but as this function is only called,
   *   when Nm has called a network indicated before, Nm must be initialized.
   */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.NM_MODE_SWITCHED_FULL_COM_NETWORK_REQUESTED,1 */

#if (COMM_MULTICORE_ENABLED == STD_ON)
  /* !LINKSTO ComM.EB.BusNm_GetState,1 */
  nmMode = ComM_LastNmMode[COMM_INST(instIdx)];
#else
  (void) Nm_GetState(COMM_NM_CHANNEL_OF_CHANNEL(instIdx), &nmState, &nmMode);
#endif
  ret = ((NM_MODE_PREPARE_BUS_SLEEP == nmMode) ? TRUE : FALSE);
#endif
  COMM_PARAM_UNUSED(instIdx);
  return ret;
}

/* ************************************************************************
 * State: FULL_COM_NETWORK_REQUESTED_ENTRY
 * Parent state: FULL_COM_NETWORK_REQUESTED
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) FULL_COM_NETWORK_REQUESTED_ENTRY -> FULL_COM_NETWORK_REQUESTED_PENDING: REQ_STATUS_CHANGED[ComM_IsFullComAllowed()]/
 * 2) FULL_COM_NETWORK_REQUESTED_ENTRY -> FULL_COM_READY_SLEEP: REQ_STATUS_CHANGED[(FULL|PASSIVE|SLAVE_ACTIVE|SLAVE_PASSIVE == ComMNmVariant) && (!ComM_IsFullComAllowed())]/
 * 3) FULL_COM_NETWORK_REQUESTED_ENTRY -> FULL_COM_READY_SLEEP: TIMEOUT[ComM_IsFullComAllowed()]/
 * 4) FULL_COM_NETWORK_REQUESTED_ENTRY -> FULL_COM_NETWORK_REQUESTED_PENDING: TIMEOUT[ComM_IsFullComAllowed()]/
 */

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_ENTRYEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
  if(COMM_CHANNEL_NOCOM_INHIBITION_STATUS((uint8)instIdx) == TRUE)
  {
    COMM_EMIT(instIdx, COMM_HSM_COMM_EV_LIMIT_TO_NO_COM);
  }
#endif
  /* entry action 'if(ComMNmVariant== LIGHT|NONE) ComM_StartTimer(ComMTMinFullComModeDuration);if(ComMNmVariant == FULL|PASSIVE|SLAVE_ACTIVE|SLAVE_PASSIVE) emit REQ_STATUS_CHANGED' */
#if ((COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON) || (COMM_NM_VARIANT_NONE_NEEDED == STD_ON))
#if (COMM_NM_VARIANT_LIGHT_NONE_ONLY == STD_OFF)
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00886.NmVariant.LIGHT,1 */
  if ((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_LIGHT_VARIANT) ||
      /* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.NONE,1, ComM.EB_Ref.SWS_ComM_00886.NmVariant.NONE,1 */
      (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_NONE_VARIANT)
     )
#endif
  {
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComMTMinFullComModeDuration_TIMEOUT,1 */
    ComM_StartTimer(instIdx, COMM_HSM_COMM_EV_TIMEOUT, COMM_MIN_FULL_COM_MODE_DURATION(instIdx));
  }
#endif

#if ( (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || \
      (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) || \
      (COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_ON) || \
      (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_ON) \
    )
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  if ((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ||
      (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT) ||
      (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_SLAVE_ACTIVE_VARIANT) ||
      (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_SLAVE_PASSIVE_VARIANT)
     )
#endif
  {
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_NETWORK_REQUESTED_ENTRY_REQ_STATUS_CHANGED,1 */

    /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_NETWORK_REQUESTED_ENTRY_REQ_STATUS_CHANGED,1 */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_NO_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_2,1 */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_NO_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_3,1 */
    /* !LINKSTO ComM.SWS_ComM_01017,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00915.NmVariant.SLAVE_PASSIVE,1 */
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00915.NmVariant.PASSIVE,1 */
    COMM_EMIT(instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
  }
#endif
}
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_ENTRYExit(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* exit action 'if(ComMNmVariant== LIGHT|NONE) ComM_StopTimer();' */
#if ((COMM_NM_VARIANT_LIGHT_NEEDED == STD_OFF) && (COMM_NM_VARIANT_NONE_NEEDED == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#else
#if (COMM_NM_VARIANT_LIGHT_NONE_ONLY == STD_OFF)
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00886.NmVariant.LIGHT,1 */
  if ((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_LIGHT_VARIANT) ||
      /* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.NONE,1, ComM.EB_Ref.SWS_ComM_00886.NmVariant.NONE,1 */
      (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_NONE_VARIANT)
     )
#endif
  {
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00890.CANCEL_COMMTMINFULLCOMMODEDURATION,1 */
    ComM_StopTimer(instIdx);
  }
#endif
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_ENTRYGuard1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_IsFullComAllowed()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state FULL_COM_NETWORK_REQUESTED_PENDING */
  /* !LINKSTO ComM.EB.ComM_FULL_COM_NETWORK_REQUESTED_Transition_UserRequest,1 */
  /* !LINKSTO ComM.EB.ComM_FULL_COM_NETWORK_REQUESTED_Transition_DcmRequest,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_FULL_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_FULL_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_1,1 */
  boolean ret = FALSE;
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_ON) \
    )
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  ret = ( (TRUE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))              ) &&
          ((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ||
           (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT) ||
           (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_SLAVE_ACTIVE_VARIANT) ||
           (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_SLAVE_PASSIVE_VARIANT)
          )
        ) ? TRUE : FALSE;
#else /* #if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON) */
  ret = (TRUE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
#endif /* #if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON) */
#else /* #if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) .. ) */
  COMM_PARAM_UNUSED(instIdx);
#endif /* #if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) .. ) */
  return ret;
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_ENTRYGuard2(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition '(FULL|PASSIVE == ComMNmVariant) && (!ComM_IsFullComAllowed())'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state FULL_COM_READY_SLEEP */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_NO_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_NO_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_1,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_NO_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_2,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_NO_COMM_FULL_COM_NETWORK_REQUESTED_ENTRY_3,1 */
  /* !LINKSTO ComM.SWS_ComM_01017,1 */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00915.NmVariant.SLAVE_PASSIVE,1 */
  boolean ret = FALSE;
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_SLAVE_ACTIVE_NEEDED == STD_ON) || \
     (COMM_NM_VARIANT_SLAVE_PASSIVE_NEEDED == STD_ON) \
    )
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  ret = ( (FALSE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))              ) &&
          ((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ||
           (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT) ||
           (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_SLAVE_ACTIVE_VARIANT) ||
           (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_SLAVE_PASSIVE_VARIANT)
          )
        ) ? TRUE : FALSE;
#else /* #if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON) */
  ret = (FALSE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
#endif /* #if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON) */
#else /* #if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) .. ) */
  COMM_PARAM_UNUSED(instIdx);
#endif /* #if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON) .. ) */
  return ret;
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_ENTRYGuard3(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition '!ComM_IsFullComAllowed()'
   * for TIMEOUT[...]/
   * external transition to state FULL_COM_READY_SLEEP */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TIMEOUT_NO_USER_REQUEST_FULL_COM_NETWORK_REQUESTED_ENTRY_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TIMEOUT_NO_USER_REQUEST_FULL_COM_NETWORK_REQUESTED_ENTRY_1,1 */
  boolean ret = FALSE;
  ret = (FALSE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_ENTRYGuard4(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_IsFullComAllowed()'
   * for TIMEOUT[...]/
   * external transition to state FULL_COM_NETWORK_REQUESTED_PENDING */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TIMEOUT_USER_REQUEST_FULL_COM_NETWORK_REQUESTED_ENTRY_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TIMEOUT_USER_REQUEST_FULL_COM_NETWORK_REQUESTED_ENTRY_1,1 */
  boolean ret = FALSE;
  ret = (TRUE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}

/* ************************************************************************
 * State: FULL_COM_NETWORK_REQUESTED_PENDING
 * Parent state: FULL_COM_NETWORK_REQUESTED
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) FULL_COM_NETWORK_REQUESTED_PENDING -> FULL_COM_READY_SLEEP: REQ_STATUS_CHANGED[!ComM_IsFullComAllowed()]/
 */
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_PENDINGEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* entry action 'ReRequestNeeded' */
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
  if (COMM_PASSIVEEXECUTED(instIdx) == TRUE)
  {
    COMM_EMIT(instIdx, COMM_HSM_COMM_EV_RE_REQUEST_NETWORK);
  }
#else /* #if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) */
  COMM_PARAM_UNUSED(instIdx);
#endif /* #if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON) */
}


/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_NETWORK_REQUESTED_PENDINGGuard1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition '!ComM_IsFullComAllowed()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state FULL_COM_READY_SLEEP */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_USER_FULL_COM_NETWORK_REQUESTED_PENDING_0,1 */
  boolean ret = FALSE;
  ret = (FALSE == ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}

/* ************************************************************************
 * State: FULL_COM_READY_SLEEP
 * Parent state: FULL_COMMUNICATION
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) FULL_COM_READY_SLEEP -> SILENT_COMMUNICATION: NM_MODE_SWITCHED[(ComMNmVariant == FULL|PASSIVE) && (ComM_NmGetMode() == NM_MODE_PREPARE_BUS_SLEEP)]/
 * 2) FULL_COM_READY_SLEEP -> FULL_COM_NETWORK_REQUESTED: REQ_STATUS_CHANGED[ComM_IsFullComAllowed()]/
 * 3) FULL_COM_READY_SLEEP -> NO_COMMUNICATION: TIMEOUT[]/if(COMM_BUS_TYPE_INTERNAL== ComMBusType) {ComM_Notify(COMM_NO_COMMUNICATION); ComM_ClearUserRequest();}
 */

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_READY_SLEEPEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* entry action 'ComM_ChanState = COMM_FULL_COM_READY_SLEEP;if(ComMNmVariant == LIGHT) ComM_StartTimer(ComMNmLightTimeout);if(ComMNmVariant == FULL) Nm_NetworkRelease();if(ComMNmVariant == FULL|PASSIVE) emit REQ_STATUS_CHANGEDif(NONE== ComMNmVariant) emit TIMEOUT' */
  /* !LINKSTO ComM.SWS_ComM_00888,1 */
  COMM_CHANNELSTATE(instIdx) = COMM_FULL_COM_READY_SLEEP;
#if (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  /* !LINKSTO ComM.SWS_ComM_00891,1 */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.LIGHT,1 */
  if (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_LIGHT_VARIANT)
#endif
  {
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComMNmLightTimeout_TIMEOUT,1 */
    ComM_StartTimer(instIdx, COMM_HSM_COMM_EV_TIMEOUT, COMM_READYSLEEPNONMTIMEOUTMS(instIdx));
  }
#endif
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
  /* !LINKSTO ComM.SWS_ComM_00133,1 */
  if (COMM_NM_FULL_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
#endif
  {
    /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Nm_NetworkRelease,1 */
    COMM_NM_NETWORKRELEASE(instIdx);
  }
#endif
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON))
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
    if ((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ||
        (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT)
       )
#endif
    {
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_READY_SLEEP_ENTRY_REQ_STATUS_CHANGED,1 */
      COMM_EMIT(instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
#endif

/* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_READY_SLEEP_ENTRY_REQ_STATUS_CHANGED,1 */
#if (COMM_RELEASE_NONE_CHANNELS == STD_OFF)
#if (COMM_NM_VARIANT_NONE_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.NONE,1 */
  if (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_NONE_VARIANT)
#endif /* if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON) */
  {
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_READY_SLEEP_TIMEOUT,2 */
    /* !LINKSTO ComM.EB.ComMReleaseNoneChannels,1 */
    COMM_EMIT_TO_SELF(instIdx, COMM_HSM_COMM_EV_TIMEOUT);
  }
#endif /* if (COMM_NM_VARIANT_NONE_NEEDED == STD_ON) */
#else  /* if (COMM_RELEASE_NONE_CHANNELS == STD_OFF) */
  /* !LINKSTO ComM.EB.ComMReleaseNoneChannels_BusTypeDifferentThan_COMM_BUS_TYPE_INTERNAL,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_READY_SLEEP_TIMEOUT_1,1*/
#if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON)
#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON)
  if (COMM_BUSTYPE_OF_CHANNEL(instIdx) == COMM_BUS_TYPE_INTERNAL)
#endif /* if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) */
  {
    /* !LINKSTO ComM.EB.ComMReleaseNoneChannels_BusTypeIs_COMM_BUS_TYPE_INTERNAL,1 */
    /* !LINKSTO ComM.EB.Dsn.StateDynamics.FULL_COM_READY_SLEEP_TIMEOUT_2,1*/
    COMM_EMIT_TO_SELF(instIdx, COMM_HSM_COMM_EV_TIMEOUT);
  }
#endif /* if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON) */
#endif /* if (COMM_RELEASE_NONE_CHANNELS == STD_OFF) */
}
/* !LINKSTO ComM.SWS_ComM_00610,1 */
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_READY_SLEEPExit(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* exit action 'if(ComMNmVariant == LIGHT) ComM_StopTimer();' */
#if ((COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_OFF) || \
     (COMM_NM_VARIANT_LIGHT_NEEDED == STD_OFF))
  COMM_PARAM_UNUSED(instIdx);
#endif

#if (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00602.NmVariant.LIGHT,1 */
  if (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_LIGHT_VARIANT)
#endif
  {
    /* !LINKSTO ComM.SWS_ComM_00892,1 */
    ComM_StopTimer(instIdx);
  }
#endif
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_READY_SLEEPGuard1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition '(ComMNmVariant == FULL|PASSIVE) && (ComM_NmGetMode() == NM_MODE_PREPARE_BUS_SLEEP)'
   * for NM_MODE_SWITCHED[...]/
   * external transition to state SILENT_COMMUNICATION */
  boolean ret = FALSE;

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
#if (COMM_MULTICORE_ENABLED == STD_ON)
  Nm_ModeType  nmMode;
#else
  Nm_StateType nmState;
  Nm_ModeType  nmMode;
#endif

  /* return value can be ignored, as the only reasons for E_NOT_OK are
   * - wrong network handles (development error, would have occurred already before)
   * - Nm is not yet initialized, but as this function is only called,
   *   when Nm has called a network indicated before, Nm must be initialized.
   */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.NM_MODE_SWITCHED_FULL_COM_READY_SLEEP,1 */

#if (COMM_MULTICORE_ENABLED == STD_ON)
  /* !LINKSTO ComM.EB.BusNm_GetState,1 */
  nmMode = ComM_LastNmMode[COMM_INST(instIdx)];
#else
  (void) Nm_GetState(COMM_NM_CHANNEL_OF_CHANNEL(instIdx), &nmState, &nmMode);
#endif

#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
  ret = (((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ||
          (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT)
         ) &&
         (NM_MODE_PREPARE_BUS_SLEEP == nmMode)
        ) ? TRUE : FALSE;
#else
  ret = (NM_MODE_PREPARE_BUS_SLEEP == nmMode) ? TRUE : FALSE;
#endif /* #if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON) */
#endif /* #if (COMM_NM_ACCESS_NEEDED == STD_ON) */
  COMM_PARAM_UNUSED(instIdx);
  return ret;
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfFULL_COM_READY_SLEEPGuard2(
  COMM_PDL_SF(const uint16 instIdx))
{
  boolean ret= FALSE;
  /* guard condition 'ComM_IsFullComAllowed()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state FULL_COM_NETWORK_REQUESTED */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_FULL_COM_READY_SLEEP_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_FULL_COM_READY_SLEEP_1,1, ComM.SWS_ComM_00882,1 */
  ret = (ComM_IsFullComAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfFULL_COM_READY_SLEEPAction3(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* action 'if(COMM_BUS_TYPE_INTERNAL== ComMBusType) {ComM_Notify(COMM_NO_COMMUNICATION); ComM_ClearUserRequest();}'
   * for TIMEOUT[]/...
   * external transition to state NO_COMMUNICATION */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TIMEOUT_FULL_COM_READY_SLEEP_1,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TIMEOUT_FULL_COM_READY_SLEEP_0,1 */
#if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_OFF)
  COMM_PARAM_UNUSED(instIdx);
#else
#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON)
  if (COMM_BUS_TYPE_INTERNAL == COMM_BUSTYPE_OF_CHANNEL(instIdx))
#endif /* #if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) */
  {
    /* !LINKSTO ComM.SWS_ComM_00671,1, ComM.SWS_ComM_00582,1 */
    ComM_Notify(((uint8)instIdx), (COMM_NO_COMMUNICATION));
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && (COMM_NUM_USERS > 0))
    ComM_ClearUserRequest(COMM_INST((uint8)instIdx), FALSE);
#endif /* #if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
  }
#endif /* #if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON) */
}

/* ************************************************************************
 * State: NO_COMMUNICATION
 * Parent state: TOP
 * Init substate: NO_COM_NO_PENDING_REQUEST
 * Transitions originating from this state:
 */

/* !LINKSTO ComM.SWS_ComM_00898,1, ComM.SWS_ComM_00313,1, ComM.SWS_ComM_00288,1 */
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfNO_COMMUNICATIONEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* entry action 'if(ComMNmVariant==FULL) Nm_NetworkRelease();if (COMM_BUS_TYPE_INTERNAL!= ComMBusType) ComM_BusSmRequestComMode(COMM_NO_COMMUNICATION);if(ComMNmVariant == FULL|PASSIVE) emit REQ_STATUS_CHANGED' */

  ComM_PassiveStartupStatus[COMM_INST(instIdx)] = FALSE;

  if (COMM_CHANNELSTATE(instIdx) != COMM_NO_COM_NO_PENDING_REQUEST)
  {
#if ((COMM_RESET_AFTER_FORCING_NOCOMM == STD_ON) && (COMM_MODE_LIMITATION_ENABLED == STD_ON))
    /* !LINKSTO ComM.SWS_ComM_00355,1, ComM.ECUC_ComM_00558,1 */
    /* following check was made to make sure that a reset is not triggered during initialization entry in nocomm state */
    if (COMM_CHANNEL_NOCOM_INHIBITION_STATUS((uint8)instIdx) == TRUE)
    {
      /* !LINKSTO ComM.EB_Ref.SWS_ComM_00829.BswM_ComM_InitiateReset,1 */
      BswM_ComM_InitiateReset();
    }
#endif
#if (COMM_NM_VARIANT_FULL_NEEDED == STD_ON)
#if (COMM_NM_VARIANT_FULL_ONLY == STD_OFF)
    if (COMM_NM_FULL_VARIANT == COMM_NM_VARIANT_OF_CHANNEL(instIdx))
#endif
    {
      /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Nm_NetworkRelease,1 */
      COMM_NM_NETWORKRELEASE(instIdx);
    }
#endif
#if ((COMM_NM_VARIANT_FULL_NEEDED == STD_ON) || (COMM_NM_VARIANT_PASSIVE_NEEDED == STD_ON))
#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
    if ((COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_FULL_VARIANT) ||
        (COMM_NM_VARIANT_OF_CHANNEL(instIdx) == COMM_NM_PASSIVE_VARIANT)
       )
#endif
    {
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.NO_COMMUNICATION_ENTRY_REQ_STATUS_CHANGED,1 */
      COMM_EMIT(instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
#endif
#if ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) || \
     ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_OFF) && (COMM_BUSTYPE_INTERNAL_NEEDED == STD_OFF)))
#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON)
    if (COMM_BUS_TYPE_INTERNAL != COMM_BUSTYPE_OF_CHANNEL(instIdx))
#endif /*#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) */
    {
      /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.BusSM_RequestComMode,1 */
      /* !LINKSTO ComM.SWS_ComM_01020,1 */
      /* !LINKSTO ComM.SWS_ComM_00073,1 */
#if (COMM_MULTICORE_ENABLED == STD_OFF)
      COMM_BUSSM_REQUEST_COM_MODE((uint8)instIdx, COMM_NO_COMMUNICATION);
#endif
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_OFF))
      if(COMM_BUSSM_REQUEST_COM_MODE((uint8)instIdx, COMM_NO_COMMUNICATION) != SCHM_E_OK)
      {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO ComM.EB.SchM_Call_Client_Server_DET,1 */
        COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID,
                              COMM_SID_MAIN_FUNCTION,
                              COMM_E_BUSSM_REQUESTCOMMODE);
#endif
      }
#endif /*#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_OFF))*/
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON))
      ComM_BusSmModeToReport[COMM_INST(instIdx)] = COMM_NO_COMMUNICATION;
#endif /* #if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)) */
    }
#endif /*#if ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON) || \
        *     ((COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_OFF) && (COMM_BUSTYPE_INTERNAL_NEEDED == STD_OFF)))
        */
  }
}

/* ************************************************************************
 * State: NO_COM_NO_PENDING_REQUEST
 * Parent state: NO_COMMUNICATION
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) NO_COM_NO_PENDING_REQUEST -> NO_COM_REQUEST_PENDING: PASSIVE_WAKEUP_IND[]/ComM_ChannelPassiveWakeup = TRUE
 * 2) NO_COM_NO_PENDING_REQUEST -> NO_COM_REQUEST_PENDING: REQ_STATUS_CHANGED[ComM_IsWakeupAllowed()]/
 */

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfNO_COM_NO_PENDING_REQUESTEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* entry action 'ComM_ComM_ChanState = COMM_NO_COM_NO_PENDING_REQUEST;ComM_ChannelPassiveWakeup = FALSE' */
  COMM_CHANNELSTATE(instIdx) = COMM_NO_COM_NO_PENDING_REQUEST;
  COMM_CHANNELPASSIVEWAKEUP(instIdx) = FALSE;
}

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfNO_COM_NO_PENDING_REQUESTAction1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* action 'ComM_ChannelPassiveWakeup = TRUE'
   * for PASSIVE_WAKEUP_IND[]/...
   * external transition to state NO_COM_REQUEST_PENDING */
  COMM_CHANNELPASSIVEWAKEUP(instIdx) = TRUE;
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfNO_COM_NO_PENDING_REQUESTGuard2(
  COMM_PDL_SF(const uint16 instIdx))
{
  boolean ret = FALSE;
  /* guard condition 'ComM_IsWakeupAllowed()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state NO_COM_REQUEST_PENDING */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_USER_NO_COM_NO_PENDING_REQUEST_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_DCM_NO_COM_NO_PENDING_REQUEST_1,1 */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00876.NmVariant.FULL,1, ComM.EB_Ref.SWS_ComM_00876.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00876.NmVariant.NONE,1 */
  ret = (ComM_IsWakeupAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}

/* ************************************************************************
 * State: NO_COM_REQUEST_PENDING
 * Parent state: NO_COMMUNICATION
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) NO_COM_REQUEST_PENDING -> FULL_COMMUNICATION: COMALLOWED_CHANGED[ComM_Communication_Allowed == TRUE]/
 * 2) NO_COM_REQUEST_PENDING -> NO_COM_NO_PENDING_REQUEST: LIMIT_TO_NO_COM[ComM_IsLimitToNoCom]/ComM_ClearUserRequest
 * 3) NO_COM_REQUEST_PENDING -> NO_COM_REQUEST_PENDING: PASSIVE_WAKEUP_IND[]/ComM_ChannelPassiveWakeup = TRUE
 * 4) NO_COM_REQUEST_PENDING -> NO_COM_NO_PENDING_REQUEST: REQ_STATUS_CHANGED[ComM_IsNotRequested]/
 * 5) NO_COM_REQUEST_PENDING -> NO_COM_NO_PENDING_REQUEST: WAKEUP_INHIBITION[ComM_IsWakeupInhibition]/
 */

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfNO_COM_REQUEST_PENDINGEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* entry action 'ComM_ChanState = COMM_NO_COM_REQUEST_PENDING;emit COMALLOWED_CHANGED' */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00893.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.False,1 */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00893.ComM_EcuM_WakeUpIndication.ComMSynchronousWakeUp.False.ManagingChannel,1 */
  /* !LINKSTO ComM.SWS_ComM_01014,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.PASSIVE_WAKEUP_IND_NO_COM_NO_PENDING_REQUEST_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.PASSIVE_WAKEUP_IND_NO_COM_NO_PENDING_REQUEST_1,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.PASSIVE_WAKEUP_IND_NO_COM_NO_PENDING_REQUEST_2,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.PASSIVE_WAKEUP_IND_NO_COM_NO_PENDING_REQUEST_3,1 */
  COMM_CHANNELSTATE(instIdx) = COMM_NO_COM_REQUEST_PENDING;
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.NO_COM_REQUEST_PENDING_COMALLOWED_CHANGED,1 */
  /* !LINKSTO ComM.SWS_ComM_00875,1  */
  COMM_EMIT_TO_SELF(instIdx, COMM_HSM_COMM_EV_COMALLOWED_CHANGED);
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfNO_COM_REQUEST_PENDINGGuard1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_Communication_Allowed == TRUE'
   * for COMALLOWED_CHANGED[...]/
   * external transition to state FULL_COMMUNICATION */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.COMALLOWED_CHANGE_NO_COM_PENDING_REQUEST,1, ComM.SWS_ComM_00896,1, ComM.SWS_ComM_00895,1 */
  return ComM_Communication_Allowed[COMM_INST(instIdx)];
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfNO_COM_REQUEST_PENDINGGuard2(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_IsLimitToNoCom'
   * for LIMIT_TO_NO_COM[...]/ComM_ClearUserRequest
   * external transition to state NO_COM_NO_PENDING_REQUEST */
  boolean ret = FALSE;
  COMM_PARAM_UNUSED(instIdx);
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
  /* !LINKSTO ComM.EB.LimitToNoCom,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.LIMIT_TO_NO_COM_NO_COM_REQUEST_PENDING_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.LIMIT_TO_NO_COM_NO_COM_REQUEST_PENDING_1,1 */
  ret = (ComM_IsLimitToNoCom(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
#endif /* #if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
  return ret;
}

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfNO_COM_REQUEST_PENDINGAction2(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* action 'ComM_ClearUserRequest'
   * for LIMIT_TO_NO_COM[ComM_IsLimitToNoCom]/...
   * external transition to state NO_COM_NO_PENDING_REQUEST */
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && (COMM_NUM_USERS > 0))
  /* !LINKSTO ComM.EB.LimitToNoComClearUserRequest,1 */
  ComM_ClearUserRequest(COMM_INST((uint8)instIdx), TRUE);
  /* CHECK: NOPARSE */
  /* If COMM_MODE_LIMITATION_ENABLED is STD_OFF then ComM_SetChannelComMInhibitionStatus
   * is not defined, and also the multicore operations COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM
   * and COMM_MULTICORE_EMIT_LIMIT_TO_NO_COM_ALL_CHANNELS are never being sent, resulting in
   * this action never being reached
   */
#else /* #if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
  COMM_PARAM_UNUSED(instIdx);
#endif
  /* CHECK: PARSE */
}

/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfNO_COM_REQUEST_PENDINGAction3(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* action 'ComM_ChannelPassiveWakeup = TRUE'
   * for PASSIVE_WAKEUP_IND[]/...
   * external transition to state NO_COM_REQUEST_PENDING */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.PASSIVE_WAKEUP_INDICATION_NO_COM_REQUEST_PENDING_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.PASSIVE_WAKEUP_INDICATION_NO_COM_REQUEST_PENDING_1,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.PASSIVE_WAKEUP_INDICATION_NO_COM_REQUEST_PENDING_2,1 */
  COMM_CHANNELPASSIVEWAKEUP(instIdx) = TRUE;
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfNO_COM_REQUEST_PENDINGGuard4(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_IsNotRequested'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state NO_COM_NO_PENDING_REQUEST */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_USER_NO_COM_PENDING_REQUEST_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_DCM_NO_COM_PENDING_REQUEST_1,1, ComM.SWS_ComM_00897,1 */
  boolean ret = FALSE;
  ret = (ComM_IsNotRequested(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}

/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfNO_COM_REQUEST_PENDINGGuard5(
  COMM_PDL_SF(const uint16 instIdx))
{
  boolean ret = FALSE;
  COMM_PARAM_UNUSED(instIdx);
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
  /* guard condition 'ComM_IsWakeupInhibition'
   * for WAKEUP_INHIBITION[...]/
   * external transition to state NO_COM_NO_PENDING_REQUEST */
  /* !LINKSTO ComM.EB.WakeupInhibition,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.WAKEUP_INHIBITION_NO_COM_REQUEST_PENDING,1 */
  ret = (ComM_IsWakeupInhibition(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
#endif /* #if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) */
  return ret;
}

/* ************************************************************************
 * State: SILENT_COMMUNICATION
 * Parent state: TOP
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) SILENT_COMMUNICATION -> FULL_COM_READY_SLEEP: NM_MODE_SWITCHED[ComM_NmGetMode() == NM_MODE_NETWORK]/
 * 2) SILENT_COMMUNICATION -> NO_COMMUNICATION: NM_MODE_SWITCHED[ComM_NmGetMode() == NM_MODE_BUS_SLEEP]/
 * 3) SILENT_COMMUNICATION -> FULL_COMMUNICATION: REQ_STATUS_CHANGED[ComM_IsWakeupAllowed()]/
 */

/* !LINKSTO ComM.SWS_ComM_00071,1 */
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_HsmComMSfSILENT_COMMUNICATIONEntry(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* !LINKSTO ComM.ASR403.SWS_ComM_00299,1 */
  /* entry action 'ComM_ChanState = COMM_SILENT_COM;ComM_BusSmRequestComMode(COMM_SILENT_COMMUNICATION);' */
  COMM_CHANNELSTATE(instIdx) = COMM_SILENT_COM;

  ComM_PassiveStartupStatus[COMM_INST(instIdx)] = FALSE;

  /* Here no need to check if ComMBusType is COMM_BUS_TYPE_INTERNAL since
   * only a channel with ComMNmVariant atribute FULL or PASSIVE
   * can indicate Silent Communication.
   * A channel with ComMBusType set to COMM_BUS_TYPE_INTERNAL
   * can only have atribute ComMNmVariant set as NONE.
   */
   /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.BusSM_RequestComMode,1 */
   /* !LINKSTO ComM.SWS_ComM_01020,1 */
#if (COMM_MULTICORE_ENABLED == STD_OFF)
  COMM_BUSSM_REQUEST_COM_MODE((uint8)instIdx, COMM_SILENT_COMMUNICATION);
#endif
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_OFF))
  if(COMM_BUSSM_REQUEST_COM_MODE((uint8)instIdx, COMM_SILENT_COMMUNICATION) != SCHM_E_OK)
  {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO ComM.EB.SchM_Call_Client_Server_DET,1 */
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID,
                          COMM_SID_MAIN_FUNCTION,
                          COMM_E_BUSSM_REQUESTCOMMODE);
#endif
  }
#endif /* #if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_OFF)) */
#if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON))
  ComM_BusSmModeToReport[COMM_INST(instIdx)] = COMM_SILENT_COMMUNICATION;
#endif /* #if ((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_WAKEUPSLEEPREQUEST_ENABLED == STD_ON)) */
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfSILENT_COMMUNICATIONGuard1(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_NmGetMode() == NM_MODE_NETWORK'
   * for NM_MODE_SWITCHED[...]/
   * external transition to state FULL_COM_READY_SLEEP */

  boolean      ret = FALSE;
#if (COMM_NM_ACCESS_NEEDED == STD_ON)
#if (COMM_MULTICORE_ENABLED == STD_ON)
  Nm_ModeType  nmMode;
#else
  Nm_StateType nmState;
  Nm_ModeType  nmMode;
#endif
  /* return value can be ignored, as the only reasons for E_NOT_OK are
   * - wrong network handles (development error, would have occurred already before)
   * - Nm is not yet initialized, but as this function is only called,
   *   when Nm has called a network indicated before, Nm must be initialized.
   */
   /* !LINKSTO ComM.EB.Dsn.StateDynamics.NM_MODE_SWITCHED_SILENT_COMMUNICATION_0,1, ComM.SWS_ComM_00296,1 */
#if (COMM_MULTICORE_ENABLED == STD_ON)
  /* !LINKSTO ComM.EB.BusNm_GetState,1 */
  nmMode = ComM_LastNmMode[COMM_INST(instIdx)];
#else
  (void) Nm_GetState(COMM_NM_CHANNEL_OF_CHANNEL(instIdx), &nmState, &nmMode);
#endif
  ret = (NM_MODE_NETWORK == nmMode) ? TRUE : FALSE;
#endif
  COMM_PARAM_UNUSED(instIdx);
  return ret;
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfSILENT_COMMUNICATIONGuard2(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_NmGetMode() == NM_MODE_BUS_SLEEP'
   * for NM_MODE_SWITCHED[...]/
   * external transition to state NO_COMMUNICATION */
  boolean      ret = FALSE;

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
#if (COMM_MULTICORE_ENABLED == STD_ON)
  Nm_ModeType  nmMode;
#else
  Nm_StateType nmState;
  Nm_ModeType  nmMode;
#endif
  /* return value can be ignored, as the only reasons for E_NOT_OK are
   * - wrong network handles (development error, would have occurred already before)
   * - Nm is not yet initialized, but as this function is only called,
   *   when Nm has called a network indicated before, Nm must be initialized.
   */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.NM_MODE_SWITCHED_SILENT_COMMUNICATION_1,1, ComM.SWS_ComM_00295,1 */
#if (COMM_MULTICORE_ENABLED == STD_ON)
 /* !LINKSTO ComM.EB.BusNm_GetState,1 */
 nmMode = ComM_LastNmMode[COMM_INST(instIdx)];
#else
  (void) Nm_GetState(COMM_NM_CHANNEL_OF_CHANNEL(instIdx), &nmState, &nmMode);
#endif
  ret = (NM_MODE_BUS_SLEEP == nmMode) ? TRUE : FALSE;
#endif
  COMM_PARAM_UNUSED(instIdx);
  return ret;
}
/* Deviation MISRAC2012-1 */
FUNC(boolean, COMM_CODE) ComM_HsmComMSfSILENT_COMMUNICATIONGuard3(
  COMM_PDL_SF(const uint16 instIdx))
{
  /* guard condition 'ComM_IsWakeupAllowed()'
   * for REQ_STATUS_CHANGED[...]/
   * external transition to state FULL_COMMUNICATION */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_SILENT_COMMUNICATION_0,1 */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.REQ_STATUS_CHANGED_SILENT_COMMUNICATION_1,1, ComM.SWS_ComM_00877,1 */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00878.NmVariant.FULL,1, ComM.EB_Ref.SWS_ComM_00878.NmVariant.LIGHT,1, ComM.EB_Ref.SWS_ComM_00878.NmVariant.NONE,1 */
  boolean ret = FALSE;
  ret = (ComM_IsWakeupAllowed(COMM_PL_SF((uint8)instIdx))) ? TRUE : FALSE;
  return ret;
}
/*------------------[Timer function]----------------------------------------*/

FUNC(void, COMM_CODE) ComM_ProcessTimers(
  uint8 Channel)
{
#if (COMM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(Channel);
#endif

  if (COMM_TIMER(Channel) > 0U)
  {
    --COMM_TIMER(Channel);
    if (COMM_TIMER(Channel) == 0U)
    {
      /* timeout events are generated outside of transitions, therefore do not
       * use the EMITTOSELF function */
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComMTMinFullComModeDuration_TIMEOUT,1 */
      /* !LINKSTO ComM.EB.Dsn.StateDynamics.ComMNmLightTimeout_TIMEOUT,1 */
      COMM_EMIT(Channel, COMM_TIMEOUT_EVENT(Channel));
    }
  }
}

/*==================[internal function definitions]=========================*/

#if (((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)) || \
     ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)))
STATIC FUNC(void, COMM_CODE) ComM_DcmMcNotify(
  ComM_Dcm_Notif_FctPtr  FctPtr,
  uint8                  Channel,
  uint8                  errorId
  )
{
  if (FctPtr != NULL_PTR)
  {
    if(FctPtr(Channel) != SCHM_E_OK)
    {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO ComM.EB.SchM_Call_Client_Server_DET,1 */
      COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID,
                            COMM_SID_MAIN_FUNCTION,
                            errorId);
#else
      TS_PARAM_UNUSED(errorId);
#endif
    }
  }
}
#endif /* #if (((COMM_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)) || \
        *      ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_DCM_ENABLED == STD_ON)))
        */
/*------------------[ComM_Notify]--------------------------------------------*/

FUNC(void, COMM_CODE) ComM_Notify(
  uint8         Channel,
  ComM_ModeType ComMMode)
{
#if (COMM_INCLUDE_RTE == STD_ON)
  uint8_least i;
#endif

#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0))
  boolean SentToApplication[COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH];
#endif /**/

#if ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0))
  TS_MemSet(SentToApplication, FALSE, COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH);
#endif /* ((COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) && (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0)) */

  /* Set the current mode of the Channel */
#if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON)
  COMM_CHANNELMODE(Channel) = ComMMode;
#endif

/* !LINKSTO ComM.SWS_ComM_00663,1 */
#if (COMM_INCLUDE_RTE == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  for (i = 0U; i < COMM_NUM_USERS_OF_CHANNEL(COMM_INST(Channel)); i++)
  {
    const uint8 User = COMM_USERSOFCHANNEL(Channel,i);
#if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0)
    if (ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[Channel][User] != COMM_MULTICORE_INVALID_FCT_INDEX)
    {
      if (SentToApplication[ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[Channel][User]] == FALSE)
      {
        ComM_Ch_To_User_DataType data;
        data.Operation = COMM_MULTICORE_NOTIFY_RTE;
        data.Channel = Channel;
        data.ComMode = ComMMode;
        /* !LINKSTO ComM.EB.ChannelToUserCrossPartition,1 */
        if (ComM_Multicore_ChToUserSchmSend_FctPtr_List[ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[Channel][User]](&data) != SCHM_E_OK)
        {
#if (COMM_DEV_ERROR_DETECT == STD_ON)
          /* !LINKSTO ComM.EB.ChannelToUserSetError,1 */
          COMM_DET_REPORT_ERROR(GetApplicationID(), COMM_SID_MAIN_FUNCTION, COMM_E_CH_TO_USER_DATASET_ERROR);
#endif
        }
        SentToApplication[ComM_Multicore_ChToUserSchmSend_FctPtr_IndexList[Channel][User]] = TRUE;
      }
    }
    else
#endif /* #if (COMM_OS_APPLICATION_CH_TO_USER_FCTPTR_LENGTH != 0) */
    {
      ComM_RteNotificationSuccessful[User] = FALSE;
    }
  }
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TOPNotifyTransition_1,1 */
  for (i = 0U; i < COMM_NUM_USERS_OF_CHANNEL(COMM_INST(Channel)); i++)
  {
    const uint8 User = COMM_USERSOFCHANNEL(Channel,i);
    ComM_RteNotificationSuccessful[User] = FALSE;
  }
  /* !LINKSTO ComM.SWS_ComM_00778,1 */
  ComM_SwitchCurrentRteMode(COMM_PL_SF(Channel));
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */

  /* Report communication mode of ComM to BswM */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TOPNotifyTransition_0,1, ComM.SWS_ComM_00861,1, ComM.EB_Ref.SWS_ComM_00828.BswM_ComM_CurrentMode,1 */
  BswM_ComM_CurrentMode(COMM_INST(Channel), ComMMode);


#if (COMM_DCM_ENABLED == STD_ON)
#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON)
  if (COMM_FULL_COMMUNICATION == COMM_CHANNELMODE(Channel))
  {
    ComM_DcmMcNotify(ComM_Dcm_Notif_FpList[COMM_INST(Channel)].FullComNotif,
                     COMM_INST(Channel),
                     COMM_E_DCM_COMM_FULLCOMMODEENTERED);
  }
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Dcm_ComM_SilentComModeEntered,1 */
  else if (COMM_SILENT_COMMUNICATION == COMM_CHANNELMODE(Channel))
  {
    ComM_DcmMcNotify(ComM_Dcm_Notif_FpList[COMM_INST(Channel)].SilentComNotif,
                     COMM_INST(Channel),
                     COMM_E_DCM_COMM_SILENTCOMMODEENTERED);
  }
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Dcm_ComM_NoComModeEntered,1 */
  else
  {
    ComM_DcmMcNotify(ComM_Dcm_Notif_FpList[COMM_INST(Channel)].NoComNotif,
                     COMM_INST(Channel),
                     COMM_E_DCM_COMM_NOCOMMODEENTERED);
  }
#else /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
  /* Report communication mode of ComM to DCM */
  /* !LINKSTO ComM.EB.Dsn.StateDynamics.TOPNotifyTransition_2,1 */
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Dcm_ComM_FullComModeEntered,1 */
  if (COMM_FULL_COMMUNICATION == COMM_CHANNELMODE(Channel))
  {
#if (COMM_MULTICORE_ENABLED == STD_OFF)
    Dcm_ComM_FullComModeEntered(COMM_INST(Channel));
#else /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
    ComM_DcmMcNotify(ComM_Dcm_Notif_FpList[COMM_INST(Channel)].FullComNotif,
                     COMM_INST(Channel),
                     COMM_E_DCM_COMM_FULLCOMMODEENTERED);
#endif /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
  }
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Dcm_ComM_SilentComModeEntered,1 */
  else if (COMM_SILENT_COMMUNICATION == COMM_CHANNELMODE(Channel))
  {
#if (COMM_MULTICORE_ENABLED == STD_OFF)
    Dcm_ComM_SilentComModeEntered(COMM_INST(Channel));
#else /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
    ComM_DcmMcNotify(ComM_Dcm_Notif_FpList[COMM_INST(Channel)].SilentComNotif,
                     COMM_INST(Channel),
                     COMM_E_DCM_COMM_SILENTCOMMODEENTERED);
#endif /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
  }
  /* !LINKSTO ComM.EB_Ref.SWS_ComM_00828.Dcm_ComM_NoComModeEntered,1 */
  else
  {
#if (COMM_MULTICORE_ENABLED == STD_OFF)
    Dcm_ComM_NoComModeEntered(COMM_INST(Channel));
#else /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
    ComM_DcmMcNotify(ComM_Dcm_Notif_FpList[COMM_INST(Channel)].NoComNotif,
                     COMM_INST(Channel),
                     COMM_E_DCM_COMM_NOCOMMODEENTERED);
#endif /* #if (COMM_MULTICORE_ENABLED == STD_OFF) */
  }
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_ON) */
#endif /* #if (COMM_DCM_ENABLED == STD_ON) */
}

#if (COMM_INCLUDE_RTE == STD_ON)
/*------------------[ComM_SwitchCurrentRteMode]--------------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(void, COMM_CODE) ComM_SwitchCurrentRteMode(COMM_PDL_SF(uint8 Channel))
{
  uint8_least i;
  /* For all users of the channel */
  for (i = 0U; i < COMM_NUM_USERS_OF_CHANNEL(COMM_INST(Channel)); i++)
  {
    const uint8 User = COMM_USERSOFCHANNEL(Channel,i);
    if (FALSE == ComM_RteNotificationSuccessful[User])
    {
     /* Report the mode to RTE, if the current mode was not yet reported to
      * the Rte for this user */
      COMM_EB_RTE_NOTIFY(User);
    }
  }
}
#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */

/*------------------[ComM_ClearUserRequest]----------------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) && (COMM_NUM_USERS > 0))
STATIC FUNC(void, COMM_CODE) ComM_ClearUserRequest(
  uint8   instIdx,
  boolean tryClear)
{
#if (COMM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif
  if ((TRUE                    == COMM_CHANNEL_NOCOM_INHIBITION_STATUS(instIdx)) &&
      ((tryClear               == TRUE) ||
       ((COMM_NO_COMMUNICATION == COMM_CHANNELMODE(instIdx)                    ) &&
        (COMM_NO_COMMUNICATION != COMM_CHANNELMODE_PREVIOUS(instIdx)           ))))
  {
    ComM_ClearUserRequest_Helper(instIdx, TRUE);
  }
  COMM_CHANNELMODE_PREVIOUS(instIdx) = COMM_CHANNELMODE(instIdx);
}
#endif

/*------------------[ComM_IsFullComAllowed]--------------------------*/

/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsFullComAllowed(
  COMM_PDL_SF(uint8 Channel))
{
  boolean ret = FALSE;
  /* return TRUE if communication mode is requested and Limit to No Com is
   * disabled for the channel or active diagnostic request is active */
#if (COMM_DCM_ENABLED == STD_ON)
  /* Deviation MISRAC2012-4 <START> */
  ret = ( ( ((COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) ||
             (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST)) &&
             (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE)
           ) ||
           (TRUE == ComM_DcmActiveStatus[COMM_INST(Channel)])
         ) ? TRUE : FALSE;
#else
  ret =  ( ((COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) ||
            (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST)) &&
            (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE)
          ) ? TRUE : FALSE;
  /* Deviation MISRAC2012-4 <STOP> */
#endif
  return ret;
}

/*------------------[ComM_IsWakeupAllowed]------------------------*/

/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsWakeupAllowed(
  COMM_PDL_SF(uint8 Channel))
{
  boolean ret = FALSE;
  /* return TRUE if communication mode is requested and Limit to No Com is
   * disabled and WakeUp Inhibition is disabled for the channel or active
   * diagnostic request is active */

#if (COMM_DCM_ENABLED == STD_ON)
  /* Deviation MISRAC2012-4 <START> */
  ret = ( ( ((COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) ||
             (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST)) &&
             ( (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE) &&
               (COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(Channel) == FALSE)
             )
           ) ||
           (TRUE == ComM_DcmActiveStatus[COMM_INST(Channel)])
         ) ? TRUE : FALSE;
#else
  ret =  ( ((COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION) ||
            (COMM_REQUESTEDCOMMODE(Channel) == COMM_FULL_COMMUNICATION_WITH_WAKEUP_REQUEST)) &&
            ( (COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == FALSE) &&
              (COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(Channel) == FALSE)
            )
          ) ? TRUE : FALSE;
  /* Deviation MISRAC2012-4 <STOP> */
#endif
  return ret;
}

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsLimitToNoCom(
  COMM_PDL_SF(uint8 Channel))
{
  boolean ret = FALSE;
#if (COMM_DCM_ENABLED == STD_ON)
  ret = ((COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == TRUE) &&
          /* Deviation MISRAC2012-4 */
          (COMM_CHANNELPASSIVEWAKEUP(Channel) == FALSE) &&
          (FALSE == ComM_DcmActiveStatus[COMM_INST(Channel)])
        ) ? TRUE : FALSE;
#else
  ret = ((COMM_CHANNEL_NOCOM_INHIBITION_STATUS(Channel) == TRUE) &&
         (COMM_CHANNELPASSIVEWAKEUP(Channel) == FALSE)
        )? TRUE : FALSE;
#endif
  return ret;
}
#endif /* #if (COMM_MODE_LIMITATION_ENABLED == STD_ON) */
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsWakeupInhibition(
  COMM_PDL_SF(uint8 Channel))
{
  boolean ret = FALSE;
#if (COMM_DCM_ENABLED == STD_ON)
  ret = ((COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(Channel) == TRUE) &&
         /* Deviation MISRAC2012-4 */
         (COMM_CHANNELPASSIVEWAKEUP(Channel) == FALSE) &&
         (FALSE == ComM_DcmActiveStatus[COMM_INST(Channel)])
        ) ? TRUE : FALSE;
#else
  ret = ((COMM_CHANNEL_WAKEUP_INHIBITION_STATUS(Channel) == TRUE) &&
         (COMM_CHANNELPASSIVEWAKEUP(Channel) == FALSE)
        ) ? TRUE : FALSE;
#endif
  return ret;
}
#endif /*#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)*/

/* Deviation MISRAC2012-1 */
STATIC FUNC(boolean, COMM_CODE) ComM_IsNotRequested(
  COMM_PDL_SF(uint8 Channel))
{
  boolean ret = FALSE;
#if (COMM_DCM_ENABLED == STD_ON)
  ret = ((COMM_REQUESTEDCOMMODE(Channel) == COMM_NO_COMMUNICATION) &&
         /* Deviation MISRAC2012-4 */
         (COMM_CHANNELPASSIVEWAKEUP(Channel) == FALSE) &&
         (FALSE == ComM_DcmActiveStatus[COMM_INST(Channel)])
        ) ? TRUE : FALSE;
#else
  ret = ((COMM_REQUESTEDCOMMODE(Channel) == COMM_NO_COMMUNICATION) &&
         (COMM_CHANNELPASSIVEWAKEUP(Channel) == FALSE)
        ) ? TRUE : FALSE;
#endif
  return ret;
}

#if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF)
void ComM_RteNotificationDoAction(uint8 instIdx)
{
#if (COMM_INCLUDE_RTE == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#else
  ComM_SwitchCurrentRteMode(COMM_PL_SF(instIdx));
  TS_PARAM_UNUSED(instIdx);
#endif
}
#endif /* #if (COMM_OS_APPLICATION_MULTICORE_ENABLED == STD_OFF) */

#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*==================[end of file]===========================================*/
