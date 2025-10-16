/**
 * \file
 *
 * \brief AUTOSAR LinIf
 *
 * This file contains the implementation of the AUTOSAR
 * module LinIf.
 *
 * \version 5.8.50
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <LinIf_Trace.h>

#define LINIF_NO_PBCFG_REQUIRED
#include <LinIf.h>            /* Module library API */
#include <LinIf_Int.h>        /* LinIf internal data */

#include <LinSM_Cbk.h>        /* LinSM callback functions */
#include <SchM_LinIf.h>       /* for protecting exclusive areas */

#if ((LINIF_DEV_ERROR_DETECT == STD_ON) || (LINIF_RUNTIME_ERROR_REPORTING == STD_ON))
#include <Det.h>              /* Default Error Tracer */
#endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) || (LINIF_RUNTIME_ERROR_REPORTING == STD_ON) */

#ifdef LINIF_WAKEUP_REV2_NOT_USED
#include <EcuM.h>            /* EcuM_WakeupSourceType */
#endif /* LINIF_WAKEUP_REV2_NOT_USED */

#ifdef LINIF_WAKEUP_LINAPI_42
#include <LinIf_Cbk.h>       /* LinIf callback functions */
#endif /* LINIF_WAKEUP_LINAPI_42 */


#if (TS_MERGED_COMPILE == STD_OFF)
/* AUTOSAR Memory Mapping - start section for code */
#define LINIF_START_SEC_CODE
#include <LinIf_MemMap.h>
#endif /* TS_MERGED_COMPILE */

/*==================[internal function declarations]========================*/

#if (LINIF_MASTER_SUPPORTED == STD_ON)

/** \brief This function handle te wake up pulse time.
 *
 *  \param currentChannel  Channel which is currently processed
 *  \param nodeType        Master or Slave
*   \param SleepFlags      Sleep flags
 *  \param Result          Result of Lin_Wakeup
 */
STATIC FUNC(void, LINIF_CODE) LinIf_HandleWakeUpPulseTime
(
  uint8 currentChannel,
  uint8 nodeType,
  uint8 *SleepFlags,
  Std_ReturnType Result
);

#endif /* LINIF_MASTER_SUPPORTED == STD_ON */


/*==================[external function definitions]==========================*/

/** \brief Wake up channel
 **
 ** This function wakes up a LIN channel.
 **
 ** \param[in] Channel The LinIf channel to operate on.
 **
 */
FUNC(Std_ReturnType, LINIF_CODE) LinIf_Wakeup
(
    NetworkHandleType Channel
)
{
    Std_ReturnType Result = E_NOT_OK;     /* return value */
    boolean CallWakeupConf = FALSE;
    boolean CheckResult = FALSE;
    boolean CallWakeup = FALSE;
#ifdef LINIF_WAKEUP_LINAPI_42
    boolean CallWakeupInternal = FALSE;
    boolean WakeupInternalClearFlag = FALSE;
#endif /* LINIF_WAKEUP_LINAPI_42 */
    boolean WakeupOngoingFlag = FALSE;

    DBG_LINIF_WAKEUP_ENTRY(Channel);

#if (LINIF_DEV_ERROR_DETECT == STD_ON)
    /* check DET errors first */
    if (LINIF_UNINIT_ACCESS)
    {
        /* !LINKSTO LinIf.SWS_LinIf_00376_1.LINIF_E_UNINIT,1 */
        (void)Det_ReportError(LINIF_MODULE_ID,
                              LINIF_INSTANCE_ID,
                              LINIF_API_WAKEUP,
                              LINIF_E_UNINIT
                             );
    }
    else if ( Channel >= (LinIf_ConfigPtr->NumChannelsMaster + LinIf_ConfigPtr->NumSlaveChannels) )
    {
        (void)Det_ReportError(LINIF_MODULE_ID,
                              LINIF_INSTANCE_ID,
                              LINIF_API_WAKEUP,
                              LINIF_E_NONEXISTENT_CHANNEL
                             );
    }
    else
#endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */

    {
        CONSTP2VAR(LinIf_ChannelInfoType, AUTOMATIC, LINIF_VAR) pIfChannel =
            &LinIf_ChannelInfo[Channel];

        uint8 SleepFlags;
        uint8 currentState;
        uint8 nodeTypeMask = (LINIF_CFG_GET_CHANNEL[Channel].CfgFlags & LINIF_NODETYPE_MASK);

        /* enter critical region */
        SchM_Enter_LinIf_SCHM_LINIF_EXCLUSIVE_AREA_0();
        {

            TS_AtomicAssign8(currentState, pIfChannel->cFSM);
            TS_AtomicAssign8(SleepFlags, pIfChannel->SleepHandling);

#ifdef LINIF_WAKEUP_LINAPI_42
            /* wakeup requests are only allowed if currently no other Sleep/Wakeup
               request is ongoing */
            if((SleepFlags & LINIF_WAKEUP_INTERNAL_ONGOING_FLAG) == LINIF_WAKEUP_INTERNAL_ONGOING_FLAG)
            {
              if((SleepFlags & LINIF_SLEEP_ONGOING_FLAG) == LINIF_SLEEP_ONGOING_FLAG)
              {
                Result = E_OK;
                /* LINKSTO LinIf.SWS_LinIf_00760_1,1,
                           LinIf.EB.WakeupDuringSleepOngoing,1 */
                SleepFlags |= LINIF_WAKEUP_REQUESTED_FLAG;

                SleepFlags &= ((uint8) ~LINIF_WAKEUP_INTERNAL_ONGOING_FLAG);

                TS_AtomicAssign8(pIfChannel->SleepHandling, SleepFlags);

              }
              else
              {
                if(currentState == LINIF_CHANNEL_OPERATIONAL)
                {
                  /* LinIf already running, but confirm the request */
                  CallWakeupConf = TRUE;
                  WakeupInternalClearFlag = TRUE;
                  Result = E_OK;
                }
                else
                {
                  /* LinIf is sleeping, wake up the bus and tell the Driver to only
                     wake up itself */
                  CallWakeupInternal = TRUE;
                }
                /* clear sleep request if there is one pending */
                SleepFlags &= ((uint8) ~LINIF_SLEEP_REQUESTED_FLAG);
                TS_AtomicAssign8(pIfChannel->SleepHandling, SleepFlags);
              }
            }
            /* !LINKSTO LinIf.SWS_LinIf_00459, 2*/
            else if((SleepFlags & LINIF_SLEEP_REQUESTED_FLAG) == LINIF_SLEEP_REQUESTED_FLAG)
#else
            if((SleepFlags & LINIF_SLEEP_REQUESTED_FLAG) == LINIF_SLEEP_REQUESTED_FLAG)
#endif /* LINIF_WAKEUP_LINAPI_42 */
            {
              Result = E_OK;
              SleepFlags = LINIF_NO_SLEEP_REQUEST;
              TS_AtomicAssign8(pIfChannel->SleepHandling, SleepFlags);

              /* wake up requested before go to sleep command was transmitted, abort go to
                 sleep process and report successful wake up */
               /* !LINKSTO LinIf.SWS_LinIf_00459.WakeupConfirmation, 1*/
              CallWakeupConf = TRUE;
            }
            /* LinIf_MainFunction is processing the goto sleep command */
            else if((SleepFlags & LINIF_SLEEP_ONGOING_FLAG) == LINIF_SLEEP_ONGOING_FLAG)
            {
              Result = E_OK;
              /* LINKSTO LinIf.SWS_LinIf_00760_1,1 */
              SleepFlags |= LINIF_WAKEUP_REQUESTED_FLAG;
              TS_AtomicAssign8(pIfChannel->SleepHandling, SleepFlags);
            }
#if(LINIF_SLAVE_SUPPORTED == STD_ON)
            else if ((SleepFlags & LINIF_WAKEUP_CONFIRMED_FLAG) == LINIF_WAKEUP_CONFIRMED_FLAG)
            {
              /* !LINKSTO LinIf.EB.WakeupWaitHeader, 1*/
              /* LinIf is already awake, waiting for the first HeaderIndication */
              Result = E_OK;
            }
#endif /* LINIF_SLAVE_SUPPORTED == STD_ON */
            /* LinIf_MainFunction is not processing the goto sleep command */
            else if((SleepFlags == LINIF_NO_SLEEP_REQUEST) || ((SleepFlags & LINIF_WAKEUP_PULSE_ONGOING_FLAG) == LINIF_WAKEUP_PULSE_ONGOING_FLAG))
            {
              /* !LINKSTO LinIf.EB.WakeUpPulseOngoing,1 */
              if(currentState == LINIF_CHANNEL_OPERATIONAL)
              {
                /* LinIf already running, but confirm the request */
                CallWakeupConf = TRUE;
#ifdef LINIF_WAKEUP_LINAPI_42
                WakeupInternalClearFlag = TRUE;
#endif /* LINIF_WAKEUP_LINAPI_42 */
                Result = E_OK;
              }
              else
              {
                /* LinIf is sleeping, wake up the bus and tell the Driver to also
                   wake up the cluster */
                CallWakeup = TRUE;
                SleepFlags |= LINIF_WAKEUP_ONGOING_FLAG;
                TS_AtomicAssign8(pIfChannel->SleepHandling, SleepFlags);
                WakeupOngoingFlag = TRUE;
              }
            }
            else
            {
              /* will not be handled, return E_NOT_OK */
            }
        }

        if(CallWakeup)
        {
          Result = LinIf_LinDriverConfig[LINIF_GET_LIN_DRIVER_INDEX(Channel)].wakeup(LINIF_GET_LIN_CHANNEL(Channel));
          CheckResult = TRUE;
#if (LINIF_MASTER_SUPPORTED == STD_ON)
          LinIf_HandleWakeUpPulseTime(Channel,nodeTypeMask,&SleepFlags,Result);
#endif /* LINIF_MASTER_SUPPORTED == STD_ON */
        }
#ifdef LINIF_WAKEUP_LINAPI_42
        else if(CallWakeupInternal)
        {
          Result = LinIf_LinDriverConfig[LINIF_GET_LIN_DRIVER_INDEX(Channel)].wakeupInt(LINIF_GET_LIN_CHANNEL(Channel));
          CheckResult = TRUE;
        }
        else
        {
          /* MISRA-C:2012 Rule 15.7 */
        }
#endif /* LINIF_WAKEUP_LINAPI_42 */

        /* leave critical region */
        SchM_Exit_LinIf_SCHM_LINIF_EXCLUSIVE_AREA_0();

        if(CheckResult)
        {
          if(Result == E_OK)
          {
            /* confirm successful wakeup and set LinIf into operational */
            CallWakeupConf = TRUE;

            SchM_Enter_LinIf_SCHM_LINIF_EXCLUSIVE_AREA_0();
            {
#if (LINIF_SLAVE_SUPPORTED == STD_ON)
              if (LINIF_CH_IS_SLAVE == nodeTypeMask)
              {
                LinIf_StartTimerBI(LINIF_CFG_GET_CHANNEL_SLAVE(LINIF_CFG_GET_CHANNEL[Channel].LinIfChIndex), LINIF_GET_CHANNEL_SLAVE(Channel));
                SleepFlags |= LINIF_WAKEUP_CONFIRMED_FLAG;
                pIfChannel->SleepHandling = SleepFlags;
              }
#endif
              pIfChannel->cFSM = LINIF_CHANNEL_OPERATIONAL;
            }
            SchM_Exit_LinIf_SCHM_LINIF_EXCLUSIVE_AREA_0();

#ifdef LINIF_WAKEUP_LINAPI_42
            if(CallWakeupInternal)
            {
              /* clear wakeup internal flag */
              WakeupInternalClearFlag = TRUE;
            }
#endif /* LINIF_WAKEUP_LINAPI_42 */
          }
          else
          {
            /* !LINKSTO LinIf.SWS_LinIf_00670,2,
                        LinIf.SWS_LinIf_00762,1
             */
            LINIF_CFG_GET_UL_WUCONF_FPTR(Channel)(LINIF_GET_COMM_CHANNEL(Channel), FALSE);
          }
        }
        if(CallWakeupConf && (LINIF_CH_IS_MASTER == nodeTypeMask))
        {
          /* !LINKSTO LinIf.SWS_LinIf_00496, 2*/
          LINIF_CFG_GET_UL_WUCONF_FPTR(Channel)(LINIF_GET_COMM_CHANNEL(Channel), TRUE);
        }

        /* clear wakeup flag */
        if(WakeupOngoingFlag)
        {
          TS_AtomicAssign8(pIfChannel->SleepHandling, SleepFlags & (~(uint8)LINIF_WAKEUP_ONGOING_FLAG));
        }

#ifdef LINIF_WAKEUP_LINAPI_42
        /* clear wakeup internal flag */
        if(WakeupInternalClearFlag)
        {
          TS_AtomicAssign8(pIfChannel->SleepHandling, SleepFlags & (~(uint8)LINIF_WAKEUP_INTERNAL_ONGOING_FLAG));
        }
#endif /* #if LINIF_USE_LINAPI_42 */

    }

    DBG_LINIF_WAKEUP_EXIT(Result,Channel);

    return Result;
}

#ifdef LINIF_WAKEUP_LINAPI_42
/**
 * \brief Wakeup Confirmation function
 *
 * This service is called by Lin Driver or by the Lin Tranciever Driver
 * to report the wake up source after the successful wakeup detection
 * during CheckWakeup or after power on by bus.
 *
 * \param[in] WakeupSource - Source device which initiated the
 *  wakeup event: LIN controller or LIN transceiver
 */
FUNC(void, LINIF_CODE) LinIf_WakeupConfirmation
(
  EcuM_WakeupSourceType WakeupSource
)
{
  DBG_LINIF_WAKEUPCONFIRMATION_ENTRY(WakeupSource);

#if (LINIF_DEV_ERROR_DETECT == STD_ON)
  if(LINIF_UNINIT_ACCESS)
  {
      (void)Det_ReportError(LINIF_MODULE_ID,
                            LINIF_INSTANCE_ID,
                            LINIF_API_WAKEUPCONF,
                            LINIF_E_UNINIT
                           );
  }
  else
#endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  {
    NetworkHandleType channelIdx;

#if (LINIF_DEV_ERROR_DETECT == STD_ON)
    boolean invalidWakeupSource = TRUE;
#endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */

/* iterate over all LIN channels */
    for( channelIdx = 0U ; channelIdx < (LinIf_ConfigPtr->NumChannelsMaster + LinIf_ConfigPtr->NumSlaveChannels) ; channelIdx++ )
    {
      /* check if a valid EcuMWakeupSourceId is defined for this channel */
      if( LINIF_INVALIDECUMWAKEUPSOURCEID != LINIF_CFG_GET_CHANNEL[channelIdx].LinWakeupSourceId )
      {
      const uint32 WakeupSourceMask = (uint32)((uint32)1UL << LINIF_CFG_GET_CHANNEL[channelIdx].LinWakeupSourceId);

        if( (WakeupSource & WakeupSourceMask) == WakeupSourceMask )
        {
#if (LINIF_DEV_ERROR_DETECT == STD_ON)
          invalidWakeupSource = FALSE;
#endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */

          /* Set wakeup flag for requested channel */
          /* !LINKSTO LinIf.SWS_LinIf_00716,1 */
          TS_AtomicAssign8(LinIf_ChannelInfo[channelIdx].SleepHandling,
                           LinIf_ChannelInfo[channelIdx].SleepHandling | LINIF_WAKEUP_INTERNAL_ONGOING_FLAG);
        }
      }
    }

#if (LINIF_DEV_ERROR_DETECT == STD_ON)
    /* in case the given WakeupSource does not match any of the possible Lin WakeupSources,
       report to LINIF_E_PARAM_WAKEUPSOURCE DET */
    if(invalidWakeupSource)
    {
      (void)Det_ReportError(LINIF_MODULE_ID,
                           LINIF_INSTANCE_ID,
                           LINIF_API_WAKEUPCONF,
                           LINIF_E_PARAM_WAKEUPSOURCE
                           );
    }
#endif /* (LINIF_DEV_ERROR_DETECT == STD_ON) */
  }

  DBG_LINIF_WAKEUPCONFIRMATION_EXIT(WakeupSource);
}
#endif /* LINIF_WAKEUP_LINAPI_42 */

/*==================[internal function definitions]=========================*/

#if (LINIF_MASTER_SUPPORTED == STD_ON)

/** \brief This function handle te wake up pulse time. */
STATIC FUNC(void, LINIF_CODE) LinIf_HandleWakeUpPulseTime
(
  uint8 currentChannel,
  uint8 nodeType,
  uint8 *SleepFlags,
  Std_ReturnType Result
)
{
  if (LINIF_CH_IS_MASTER == nodeType)
  {
    /* !LINKSTO LinIf.EB.SWS_LinIf_00296_LinIfWakeUpTime, 1*/
    if ((1U == LINIF_CFG_GET_CHANNEL_MASTER(LINIF_CFG_GET_CHANNEL[currentChannel].LinIfChIndex)->EnforceWakeUpTime) && (Result == E_OK))
    {
      CONSTP2VAR(LinIf_MasterChannelInfoType, AUTOMATIC, LINIF_VAR) pIfChannelMaster = &LinIf_MasterChannelInfo[currentChannel];
      CONSTP2VAR(LinIf_ChannelInfoType, AUTOMATIC, LINIF_VAR) pIfChannel = &LinIf_ChannelInfo[currentChannel];

      *SleepFlags |= LINIF_WAKEUP_PULSE_ONGOING_FLAG;
      pIfChannel->SleepHandling = *SleepFlags;
      pIfChannelMaster->ScheduleDelay = LINIF_CFG_GET_CHANNEL_MASTER(LINIF_CFG_GET_CHANNEL[currentChannel].LinIfChIndex)->WakeUpPulseTime;
    }
  }
}

#endif /* LINIF_MASTER_SUPPORTED == STD_ON */

#if (TS_MERGED_COMPILE == STD_OFF)
/* AUTOSAR Memory Mapping - end section for code */
#define LINIF_STOP_SEC_CODE
#include <LinIf_MemMap.h>
#endif /* TS_MERGED_COMPILE */

/*==================[end of file]============================================*/
