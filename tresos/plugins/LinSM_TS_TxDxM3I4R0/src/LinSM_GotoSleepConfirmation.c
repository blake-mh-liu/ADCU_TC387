/**
 * \file
 *
 * \brief AUTOSAR LinSM
 *
 * This file contains the implementation of the AUTOSAR
 * module LinSM.
 *
 * \version 3.4.34
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA-C:2012 Deviations:
 *
 *  MISRAC2012-1) Deviated Rule: 2.2
 *    There shall be no dead code
 *
 *    Reason:
 *    - If transceiver notification is disabled the macro is
 *      expanded into an empty statement.
 */

/*==================[inclusions]============================================*/

#include <LinSM_Trace.h>
#include <LinSM_Internal.h>
#include <BswM_LinSM.h>/* !LINKSTO LinSM.ASR40.SWS_LinSM_00201_EB, 1 */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[internal function declarations]========================*/
#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_START_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */
/**
 * \brief LinSM check GotoSleep state and comfirm GotoSleep to ComM.
 *
 * \param[in] success       True if goto sleep was successfully sent, false otherwise
 * \param[in] id            LinSM channel id
 * \param[in,out] mode      mode to report to ComM
 * \param[in,out] bswMMode  mode to report to BswM
 */
STATIC FUNC(boolean, LINSM_CODE) LinSM_CheckGoToSleep
(
  boolean success,
  LinSM_ChannelIdType id,
  CONSTP2VAR(ComM_ModeType, AUTOMATIC, AUTOMATIC) mode,
  CONSTP2VAR(LinSM_ModeType, AUTOMATIC, AUTOMATIC) bswMMode
);
#if (LINSM_SLAVE_NODES_ENABLED == STD_ON)
/**
 * \brief LinSM evaluate the occurrence of a Request ComMode expected after BusSleepMode
 *
 * \param[in] success       True if goto sleep was successfully sent, false otherwise
 * \param[in] GotoSleep     True if LINSM_CHANNEL_STATE is LINSM_GOTO_SLEEP, false otherwise
 * \param[in] id            LinSM channel id
 */
STATIC FUNC(boolean, LINSM_CODE) LinSM_SLAVE_WaitNoComReq
(
  boolean success,
  boolean GotoSleep,
  LinSM_ChannelIdType id
);
#endif
#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_STOP_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */
/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/
#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_START_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */
FUNC(void, LINSM_CODE) LinSM_GotoSleepConfirmation
(
  NetworkHandleType network,
  boolean success
)
{
  boolean GotoSleep = FALSE;
  LinSM_ChannelIdType id;

  DBG_LINSM_GOTOSLEEPCONFIRMATION_ENTRY(network,success);

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
  if ( LinSM_GlobalState == LINSM_GLOBAL_UNINIT )
  {
    LINSM_DET(LINSM_SID_GOTOSLEEPCONF, LINSM_E_UNINIT);
  }
  else
#endif

  {
#if (LINSM_DEV_ERROR_DETECT == STD_ON)
    if ( ! (LINSM_COMM_NW_IS_VALID(network)) )
    {
      LINSM_DET(LINSM_SID_GOTOSLEEPCONF, LINSM_E_NONEXISTENT_NETWORK);
    }
    else
#endif
    {
      ComM_ModeType mode = COMM_NO_COMMUNICATION;
      LinSM_ModeType bswMMode = LINSM_NO_COM;
#if (LINSM_SLAVE_NODES_ENABLED == STD_ON)
      boolean waitNoComReqTmp = FALSE;
#endif
      id = LINSM_COMM_NW_TO_ID(network);

      /* enter critical section */
      LINSM_ENTER_CRITICAL_SECTION(); /* protect channel state and timer */

      GotoSleep= LinSM_CheckGoToSleep(success, id, &mode , &bswMMode);

#if (LINSM_SLAVE_NODES_ENABLED == STD_ON)
      waitNoComReqTmp= LinSM_SLAVE_WaitNoComReq(success, GotoSleep, id);
#endif
      /* leave critical section */
      LINSM_LEAVE_CRITICAL_SECTION();

      if ((success == TRUE) && (GotoSleep == TRUE))
      {
#if (LINSM_SLAVE_NODES_ENABLED == STD_ON)
        if (LINSM_CHANNEL_IS_SLAVE(id) == TRUE)
        {
          if (waitNoComReqTmp == FALSE)
          {
            /* signal ComM and BswM */
            LINSM_CALL_SM_MODEINDICATION(network, mode);
            BswM_LinSM_CurrentState(network, bswMMode);
            /* Deviation MISRAC2012-1 */
            LINSM_NOTIF_TRCV_SLEEP(id);
          }
        }
        else
#endif
        {
          /* signal ComM and BswM */
          LINSM_CALL_SM_MODEINDICATION(network, mode);
          BswM_LinSM_CurrentState(network, bswMMode);
          /* Deviation MISRAC2012-1 */
          LINSM_NOTIF_TRCV_SLEEP(id);
        }
      }
#if (LINSM_BSWM_WAKEUP_AND_SLEEP_INDICATION == STD_ON)
      /* !LINKSTO LinSM.EB.LinSM_BswM_LINSM_GOTO_SLEEP_ConfirmationFailure,1 */
      if ((success == FALSE) && (GotoSleep == TRUE) && (LINSM_BSWM_WAKEUPANDSLEEPINDICATION(id) != FALSE))
      {
        BswM_LinSM_CurrentState(network, bswMMode);
      }
#endif

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
      if (GotoSleep == FALSE)
      {
        /* confirmation not expected - signal DET */
        LINSM_DET(LINSM_SID_GOTOSLEEPCONF, LINSM_E_UNEXPECTED_CALLOUT);
      }
#endif
    }
  }

  DBG_LINSM_GOTOSLEEPCONFIRMATION_EXIT(network,success);
}
#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_STOP_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */

/*==================[internal function definitions]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_START_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */
STATIC FUNC(boolean, LINSM_CODE) LinSM_CheckGoToSleep
(
  boolean success,
  LinSM_ChannelIdType id,
  CONSTP2VAR(ComM_ModeType, AUTOMATIC, AUTOMATIC) mode,
  CONSTP2VAR(LinSM_ModeType, AUTOMATIC, AUTOMATIC) bswMMode
)
{
boolean GotoSleep = FALSE;
  if (LINSM_CHANNEL_STATE(id) == LINSM_GOTO_SLEEP)
  {
    GotoSleep = TRUE;

#if (LINSM_SLAVE_NODES_ENABLED == STD_ON)
    if (LINSM_CHANNEL_SLAVE_WAITNOCOMREQ(id) == TRUE)
    {
      /* for slave nodes, reset confirmation timer only when NO_COM request comes
      from ComM and LinSM confirms GotoSleep to ComM */
    }
    else
#endif
    {
      /* confirmation is expected - stop confirmation timeout */
      LINSM_CHANNEL_TIMER(id) = 0U;
    }


    if (success == FALSE)
    {
      LINSM_CHANNEL_STATE(id) = LINSM_FULL_COM;
      *mode = COMM_FULL_COMMUNICATION;
      *bswMMode = LINSM_FULL_COM;
      /* old schedule remains active */
    }
    else
    {
#if (LINSM_SLAVE_NODES_ENABLED == STD_ON)
      LINSM_CHANNEL_SLAVE_WAITSLEEPCONF(id) = FALSE;
      if (LINSM_CHANNEL_IS_SLAVE(id) == TRUE)
      {
        if (LINSM_CHANNEL_SLAVE_WAITNOCOMREQ(id) == FALSE)
        {
          LINSM_CHANNEL_STATE(id) = LINSM_NO_COM;
          LINSM_CHANNEL_SLAVE_GOTOSLEEPINPROGRESS(id) = FALSE;
          LINSM_CHANNEL_SILENCE_TIME(id) = LINSM_INVALID_SILENCE_AFTER_WAKEUP;
          *mode = COMM_NO_COMMUNICATION;
          *bswMMode = LINSM_NO_COM;
        }
      }
      else
#endif
      {
#if (LINSM_MASTER_NODES_ENABLED == STD_ON)
        LINSM_CHANNEL_STATE(id) = LINSM_NO_COM;
        /* (re-)set null schedule */
        LINSM_CHANNEL_LASTSCHEDULE(id) = 0U;
        *mode = COMM_NO_COMMUNICATION;
        *bswMMode = LINSM_NO_COM;
#endif
      }
    }
  }
  return GotoSleep;
}

#if (LINSM_SLAVE_NODES_ENABLED == STD_ON)
STATIC FUNC(boolean, LINSM_CODE) LinSM_SLAVE_WaitNoComReq
(
  boolean success,
  boolean GotoSleep,
  LinSM_ChannelIdType id
)
{
  boolean waitNoComReqTmp = FALSE;
  if (LINSM_CHANNEL_IS_SLAVE(id) == TRUE)
  {
    if ((success == FALSE) || (GotoSleep == FALSE))
    {
      LINSM_CHANNEL_SLAVE_WAITNOCOMREQ(id) = FALSE;
      LINSM_CHANNEL_TIMER(id) = 0U;
    }
    waitNoComReqTmp = LINSM_CHANNEL_SLAVE_WAITNOCOMREQ(id);
  }
  return waitNoComReqTmp;
}
#endif

#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_STOP_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */

/*==================[end of file]===========================================*/

