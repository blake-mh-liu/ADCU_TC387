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
#include <BswM_LinSM.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_START_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */

FUNC(void, LINSM_CODE) LinSM_WakeupConfirmation
(
  NetworkHandleType network,
  boolean success
)
{
  boolean Wakeup = FALSE;
  LinSM_ChannelIdType id;

  DBG_LINSM_WAKEUPCONFIRMATION_ENTRY(network,success);

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
  if ( LinSM_GlobalState == LINSM_GLOBAL_UNINIT )
  {
    LINSM_DET(LINSM_SID_WAKEUPCONFIRMATION, LINSM_E_UNINIT);
  }
  else
#endif

  {
#if (LINSM_DEV_ERROR_DETECT == STD_ON)
    if ( ! (LINSM_COMM_NW_IS_VALID(network)) )
    {
      LINSM_DET(LINSM_SID_WAKEUPCONFIRMATION, LINSM_E_NONEXISTENT_NETWORK);
    }
    else
#endif
    {
      ComM_ModeType mode = COMM_NO_COMMUNICATION;
      LinSM_ModeType bswMMode = LINSM_FULL_COM;

      id = LINSM_COMM_NW_TO_ID(network);

      /* enter critical section */
      LINSM_ENTER_CRITICAL_SECTION(); /* protect channel state and timer */

      if (LINSM_CHANNEL_STATE(id) == LINSM_WAKEUP)
      {
        Wakeup = TRUE;
        /* wakeup is expected - stop timeout */
        LINSM_CHANNEL_TIMER(id) = 0U;

        if (success == FALSE)
        {
          LINSM_CHANNEL_STATE(id) = LINSM_NO_COM;
          /* mode is already COMM_NO_COMMUNICATION */
          bswMMode = LINSM_NO_COM;
        }
        else
        {
          LINSM_CHANNEL_STATE(id) = LINSM_FULL_COM;
          mode = COMM_FULL_COMMUNICATION;
          bswMMode = LINSM_FULL_COM;
        }
      }

      /* leave critical section */
      LINSM_LEAVE_CRITICAL_SECTION();

      if ((success == TRUE) && (Wakeup == TRUE))
      {
        /* signal ComM and BswM */
        LINSM_CALL_SM_MODEINDICATION(network, mode);
        BswM_LinSM_CurrentState(network, bswMMode);
        /* Deviation MISRAC2012-1 */
        LINSM_NOTIF_TRCV_NORMAL(id);
      }

#if (LINSM_BSWM_WAKEUP_AND_SLEEP_INDICATION == STD_ON)
      /* !LINKSTO LinSM.EB.LinSM_BswM_LINSM_WAKEUP_ConfirmationFailure,1 */
      if ((success == FALSE) && (Wakeup == TRUE) && (LINSM_BSWM_WAKEUPANDSLEEPINDICATION(id) != FALSE))
      {
        BswM_LinSM_CurrentState(network, bswMMode);
      }
#endif
        /* wakeup not expected - signal DET */
#if (LINSM_DEV_ERROR_DETECT == STD_ON)
      if (Wakeup == FALSE)
      {
        LINSM_DET(LINSM_SID_WAKEUPCONFIRMATION, LINSM_E_UNEXPECTED_CALLOUT);
      }
#endif
    }
  }

  DBG_LINSM_WAKEUPCONFIRMATION_EXIT(network,success);
}

#if (TS_MERGED_COMPILE == STD_OFF)
#define LINSM_STOP_SEC_CODE
#include <LinSM_MemMap.h> /* !LINKSTO LinSM.ASR40.SWS_LinSM_00014,1 */
#endif /* TS_MERGED_COMPILE */

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/

