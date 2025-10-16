/**
 * \file
 *
 * \brief AUTOSAR Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module Nm.
 *
 * \version 5.12.16
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
 * MISRAC2012-1) Deviated Rule: 8.3 (Required)
 * All declarations of an object or function shall use the same names and type qualifiers.
 *
 * Reason:
 * Parameter 'nmNetworkHandle' have implementation data type: 'NetworkHandleType' but multicore
 * implementation use parameter as an uint8(arxml file).
 * In order to avoid MISRA violations, implementation data type for nmNetworkHandle and
 * ComM_ModeType should be updated with ASCPROJECT-5651.
 *
 * MISRAC2012-2) Deviated Rule: 5.5 (Required)
 * Identifiers shall be distinct from macro names
 *
 * Reason:
 * Function declaration and the macro exclude each other. This is guarded by compiler switch,
 * which is not correctly analyzed by Astree.
 *
 * MISRAC2012-3) Deviated Rule: 5.8 (Required)
 * Identifiers that define objects or functions with external linkage shall be unique
 *
 * Reason:
 * Function declaration and the macro exclude each other. This is guarded by compiler switch,
 * which is not correctly analyzed by Astree.
 *
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * In the context of "for (ccIdx = 0U; ccIdx < NM_CC_NUM; ccIdx++)"
 * when "NM_CC_NUM = 1" the message condition is always true is expected;
 * Expression "ccIdx < NM_CC_NUM" is always evaluated as true if "NM_CC_NUM = 1".
 */

/*==================[inclusions]=============================================*/
#include <Nm_Trace.h>
#include <TSAutosar.h>                     /* EB specific standard types */
#include <TSMem.h>        /* Including internal memory routines */
/* !LINKSTO Nm.EB_Ref.SWS_Nm_00123.1,1 */
#include <Nm.h>                    /* Declaration of Nm APIs (own interface) */
#include <Nm_Int.h>       /* Declaration of module internal interfaces */
/* !LINKSTO Nm.EB_Ref.SWS_Nm_00123.2,1 */
#include <Nm_Cbk.h>       /* Declaration of Nm callback APIs (own interface) */

/* !LINKSTO Nm.EB_Ref.SWS_Nm_00124.4,1, Nm.SWS_Nm_00166,1 */
#include <ComM_Nm.h>                                     /* NM callback APIs */

/* !LINKSTO Nm.EB_Ref.SWS_Nm_00124.3,1 */
#include <SchM_Nm.h>                    /* Header of Schedule Manager for Nm */

/* !LINKSTO Nm.EB_Ref.SWS_Nm_00124.5,1, Nm.SWS_Nm_00166,1 */
#if (NM_NM_INCLUDE_BSWM_HEADER == STD_ON)
#include <BswM_Nm.h>
#endif

#if ((NM_BUSNM_NUM == 1U)                              \
     && (NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF))
#include <TSCompiler.h>
/* For the given configuration this translation unit is empty.  The following
 * macro prevents compiler errors or warnings in this case */
TS_PREVENTEMPTYTRANSLATIONUNIT
#endif

/*==================[macros]=================================================*/
/* !LINKSTO Nm.EB_Ref.SWS_Nm_00246.VersionCheck,1 */
/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef NM_VENDOR_ID /* configuration check */
#error NM_VENDOR_ID must be defined
#endif

#if (NM_VENDOR_ID != 1U) /* vendor check */
#error NM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef NM_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error NM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (NM_AR_RELEASE_MAJOR_VERSION != 4U)
#error NM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef NM_AR_RELEASE_MINOR_VERSION /* configuration check */
#error NM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (NM_AR_RELEASE_MINOR_VERSION != 0U )
#error NM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#ifndef NM_AR_RELEASE_REVISION_VERSION /* configuration check */
#error NM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (NM_AR_RELEASE_REVISION_VERSION != 3U )
#error NM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef NM_SW_MAJOR_VERSION /* configuration check */
#error NM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (NM_SW_MAJOR_VERSION != 5U)
#error NM_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#ifndef NM_SW_MINOR_VERSION /* configuration check */
#error NM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (NM_SW_MINOR_VERSION < 12U)
#error NM_SW_MINOR_VERSION wrong (< 12U)
#endif

#ifndef NM_SW_PATCH_VERSION /* configuration check */
#error NM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (NM_SW_PATCH_VERSION < 16U)
#error NM_SW_PATCH_VERSION wrong (< 16U)
#endif

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#define NM_START_SEC_CODE
#include <Nm_MemMap.h>

#if ((NM_PASSIVE_MODE_ENABLED == STD_OFF)               \
  && ((NM_DEV_ERROR_DETECT == STD_ON)                   \
    || (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)))
/** \brief Function requests the BusNm_NetworkRequest
 ** \param NetworkHandle network handle
 ** \param ApiId service Id used for error reporting
 ** \param ErrorId error Id used for error reporting */
STATIC FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRequestInternal
(
  NetworkHandleType NetworkHandle,
  uint8  ApiId,
  uint8  ErrorId
);

/** \brief Function requests the BusNm_NetworkRequest
 ** \param NetworkHandle network handle
 ** \param ApiId service Id used for error reporting
 ** \param ErrorId error Id used for error reporting */
STATIC FUNC(Std_ReturnType, NM_CODE) Nm_NetworkReleaseInternal
(
  NetworkHandleType NetworkHandle,
  uint8  ApiId,
  uint8  ErrorId
);

#endif

#define NM_STOP_SEC_CODE
#include <Nm_MemMap.h>
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)

#define NM_START_SEC_CODE
/* !LINKSTO Nm.EB_Ref.SWS_Nm_00124.2,1 */
#include <Nm_MemMap.h>

/** \brief Function to abort the coordinated shutdown */
STATIC FUNC(void, NM_CODE) Nm_AbortShutdown
(
  NetworkHandleType nmNetworkHandle, boolean allChannels
);

/** \brief if coordinated shutdown is possible it will be initiated */
STATIC FUNC(void, NM_CODE) Nm_CoordinatedShutdownHandler
(
  uint8 ccIdx
);

/** \brief checks whether synchronized network is actively part of coordinated cluster.
 ** \param ccIdx index of the coordinated cluster
 ** \retval FALSE cluster need not wait for synchronizing indication in order start shutdown.
 ** \retval TRUE cluster must wait for synchronizing indication in order start shutdown.
 */
STATIC FUNC(boolean, NM_CODE) Nm_IsSynchronizationRequired
(
  uint8 ccIdx
);

/** \brief Handless BusOff in case of FrNm.
 ** \param ccIdx index of the coordinated cluster
 */
STATIC FUNC(void, NM_CODE) Nm_HandleBusOff
(
  uint8 ccIdx
);

#define NM_STOP_SEC_CODE
#include <Nm_MemMap.h>

#endif

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

#if ((NM_DEV_ERROR_DETECT == STD_ON)                    \
  || (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON))

#define NM_START_SEC_VAR_INIT_8
#include <Nm_MemMap.h>

VAR(boolean, NM_VAR) Nm_Initialized = FALSE;

#define NM_STOP_SEC_VAR_INIT_8
#include <Nm_MemMap.h>

#endif

/*==================[internal data]==========================================*/

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)

#define NM_START_SEC_VAR_CLEARED_8
#include <Nm_MemMap.h>

/** \brief Array of state of each cluster */
STATIC VAR(uint8, NM_VAR) Nm_CcState[NM_CC_NUM];

/** \brief Array of flags storing the shutdown precondition status for each
 * cluster */
/* starting with Autosar 2.1, boolean type is 8-bit, so this array is
 * in SEC_VAR_CLEARED_8 */
STATIC VAR(boolean, NM_VAR) Nm_CoordShutdownPreconOk[NM_CC_NUM];

/** \brief Number of channels in the cluster that are participating
 **        in the coordinated shutdown and sleeping */
STATIC VAR(uint8, NM_VAR) Nm_NmsParticipatingSleepingInCluster[NM_CC_NUM];

/** \brief Number of channels in the cluster that are participating
 **        in the coordinated shutdown  */
STATIC VAR(uint8, NM_VAR) Nm_NmsParticipatingInCluster[NM_CC_NUM];

/** \brief Array of flags storing channel state */
STATIC VAR(uint8, NM_VAR) Nm_ChannelStatus[NM_CHANNEL_NUM];

#define NM_STOP_SEC_VAR_CLEARED_8
#include <Nm_MemMap.h>

#define NM_START_SEC_VAR_CLEARED_16
#include <Nm_MemMap.h>

/** \brief Timers for each channel used in the coordinated shutdown.
 **        Time is measured in units of NmCycletimeMainFunction */
STATIC VAR(uint16, NM_VAR) Nm_Timer[NM_CHANNEL_NUM];

/** \brief Timers for each channel used in the fake remote sleep indication.
 **        Time is measured in units of NmCycletimeMainFunction */
STATIC VAR(uint16, NM_VAR) Nm_WaitForShutdownTimer[NM_CHANNEL_NUM];


#define NM_STOP_SEC_VAR_CLEARED_16
#include <Nm_MemMap.h>

#endif /* NM_COORDINATOR_SUPPORT_ENABLED == STD_ON */


/*==================[external function definitions]==========================*/

#define NM_START_SEC_CODE
#include <Nm_MemMap.h>

#if ((NM_DEV_ERROR_DETECT == STD_ON)                    \
  || (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON))

/* !LINKSTO Nm.SWS_Nm_00030,1 */
/*------------------[Nm_Init]------------------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_Init
(
  void
)
{
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  uint8_least i;
#endif

  DBG_NM_INIT_ENTRY();

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* Reset status for all channels */
  TS_MemSet (Nm_ChannelStatus,
             (NM_CHANNEL_ASLEEP | NM_CHANNEL_REMOTE_NODES_INACTIVE),
             NM_CHANNEL_NUM);

  TS_MemSet (Nm_Timer, 0U, NM_CHANNEL_NUM);

  /* Initialize coordinated shutdown algorithm state machine */
  /* Deviation TASKING-1 */
  for (i = 0U; i < NM_CC_NUM; i++)
  {
    Nm_CcState[i]                           = NM_CC_STATE_WAIT_FOR_SHUTDOWN;
    Nm_CoordShutdownPreconOk[i]             = FALSE;
    Nm_NmsParticipatingSleepingInCluster[i] = 0U;
    Nm_NmsParticipatingInCluster[i]         = 0U;
  }
  for(i = 0U; i < NM_CHANNEL_NUM; i++)
  {
    Nm_WaitForShutdownTimer[i] = 0;
  }
#endif

  Nm_Initialized = TRUE;

  DBG_NM_INIT_EXIT();
}
#endif


/* !LINKSTO Nm.SWS_Nm_00020,1, Nm.SWS_Nm_00118,1 */
/*------------------[Nm_MainFunction]----------------------------------------*/
FUNC(void, NM_CODE) Nm_MainFunction(void)
{

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  uint8             ChannelId;
  uint8             ccIdx;
  uint8_least       ccNwHandleLookupIdx;
  boolean           allTimersExpired;
  NetworkHandleType NetworkHandle;
#endif

  DBG_NM_MAINFUNCTION_ENTRY();

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  /* !LINKSTO Nm.SWS_Nm_00121,1 */
  if (Nm_Initialized == TRUE)
  {
    /* for each coordination clusters (cc) */
    /* Deviation TASKING-1 */
    for (ccIdx = 0U; ccIdx < NM_CC_NUM; ccIdx++)
    {
      Nm_HandleBusOff(ccIdx);
      /* Perform state dependent behavior: */
      switch (Nm_CcState[ccIdx])
      {
        /* !LINKSTO Nm.SWS_Nm_00169,1 */
        case NM_CC_STATE_SHUTDOWN_INITIATED:
          /* Check abortion of coordination algo: */
          allTimersExpired = TRUE;

          /*  for all networks in the coordination cluster taking part in shutdown */
          for (ccNwHandleLookupIdx = 0U;
               ccNwHandleLookupIdx < Nm_CcNmChannelsNum[ccIdx];
               ccNwHandleLookupIdx++
              )
          {
            NetworkHandle = Nm_CcNmChannels[ccIdx][ccNwHandleLookupIdx];

            if (NM_IS_CHANNEL(NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
            {
              ChannelId = Nm_ChanIdxFromNetworkHandle[NetworkHandle];
              if (0U < Nm_Timer[ChannelId])
              {
                --Nm_Timer[ChannelId];

                if (0U == Nm_Timer[ChannelId])
                {
                  /* !LINKSTO Nm.SWS_Nm_00176,1 */
                  {
#if (NM_MULTICORE_ENABLED == STD_ON)
                    Std_ReturnType SchM_ReqBusSynch_RetVal = E_NOT_OK;
                    NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION(NetworkHandle, SchM_ReqBusSynch_RetVal);
#else
                    NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION(NetworkHandle, 0U);
#endif
#if (NM_MULTICORE_ENABLED == STD_ON)
                    if (SchM_ReqBusSynch_RetVal == E_NOT_OK)
                    {
#if (NM_DEV_ERROR_DETECT == STD_ON)
                      /* !LINKSTO Nm.EB.SchM_Call_DET,1 */
                      NM_DET_REPORT_ERROR(NM_SID_MAIN_FUNCTION, NM_E_REQUESTBUSSYNCHRONIZATION);
#endif
                    }
#endif
                  }

                  /* if (BusNm_NetworkRelease() == E_NOT_OK) */
                  if (E_OK != Nm_NetworkReleaseInternal(NetworkHandle,
                                                        NM_SID_MAIN_FUNCTION,
                                                        NM_E_NETWORKRELEASE))
                  {
                    /* !LINKSTO Nm.EB_Ref.SWS_Nm_00236.1,1, Nm.EB_Ref.SWS_Nm_00236.2,1 */
                    Nm_AbortShutdown(NetworkHandle, FALSE);

                    /* Do not wait that for asleep channels below */
                    allTimersExpired = FALSE;
                  }
                }
                else
                {
                  allTimersExpired = FALSE; /* at least one timer still running */
                }
              }
            }
          }

          if (TRUE == allTimersExpired)
          {
            /* Enter critical section: this is to protect the global variables
             * Nm_CcState[], Nm_CoordShutdownPreconOk[], Nm_NmsParticipatingSleepingInCluster[],
             * Nm_ChannelStatus[] and Nm_NmsParticipatingInCluster[] because if main function
             * is preempted by another task say Nm_CoordinatedShutdownHandler() these
             * global variables may be set to some other value.*/
            SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

            /* If all Nms which are acutally participating in the coordinated cluster are asleep,
             * finish coordinated shutdown and reset everything related to coordinated shutdown */
            if (Nm_NmsParticipatingInCluster[ccIdx] == Nm_NmsParticipatingSleepingInCluster[ccIdx])
            {
              /* coordinated shutdown is over */
              /* Reset cluster-specific state */
              Nm_CcState[ccIdx] = NM_CC_STATE_WAIT_FOR_SHUTDOWN;
              Nm_CoordShutdownPreconOk[ccIdx] = FALSE;
              Nm_NmsParticipatingSleepingInCluster[ccIdx] = 0U;
              Nm_NmsParticipatingInCluster[ccIdx] = 0U;

              /* For all networks in the coordination cluster */
              for (ccNwHandleLookupIdx = 0U;
                   ccNwHandleLookupIdx < Nm_CcNmChannelsNum[ccIdx];
                   ccNwHandleLookupIdx++
                  )
              {
                /* Fetch network handle */
                NetworkHandle = Nm_CcNmChannels[ccIdx][ccNwHandleLookupIdx];

                /* Reset channel specific state */
                NM_RESET_CHANNEL(NetworkHandle,
                                 (NM_CHANNEL_ASLEEP | NM_CHANNEL_REMOTE_NODES_INACTIVE)
                                );
              }
            }
            SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
          }
          break;

        case NM_CC_STATE_SHUTDOWN_ABORTED:
          /* !LINKSTO Nm.EB_Ref.SWS_Nm_00171,1, Nm.SWS_Nm_00185,1 */
          Nm_CoordinatedShutdownHandler(ccIdx);
          break;

        default:
          /* case NM_CC_STATE_WAIT_SYNCHRONIZATION: do nothing, wait for state
           * change in function Nm_SynchronizationPoint() */
          /* case NM_CC_STATE_WAIT_FOR_SHUTDOWN: do nothing, wait for state
           * change in other functions, do not evaluate the shutdown criteria
           * here */
          /* case NM_CC_STATE_PREPARE_SHUTDOWN: will be handles within critical
           * section below. */
          break;
      }

      SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
      /* prevent the rescheduling between the checking for Nm_CcState[ccIdx] ==
       * NM_CC_STATE_PREPARE_SHUTDOWN and the setting to
       * NM_CC_STATE_SHUTDOWN_INITIATED.  This could happen if main function is
       * preempted by another task from which e.g. Nm_AbortShutdown() is called
       * in which the state variable may be set to NM_CC_STATE_WAIT_FOR_SHUTDOWN.
       * This would otherwise simply be overwritten if main function is
       * resumed. */

      /* check that the state is unchanged and that the shutdown
       * precondition is still true inside of the critical section */
      if (Nm_CcState[ccIdx] == NM_CC_STATE_PREPARE_SHUTDOWN)
      {
        /* for all channels in cluster */
        for (ccNwHandleLookupIdx = 0U;
             ccNwHandleLookupIdx < Nm_CcNmChannelsNum[ccIdx];
             ccNwHandleLookupIdx++)
        {
          NetworkHandle = Nm_CcNmChannels[ccIdx][ccNwHandleLookupIdx];

          /* Only consider networks being active in a coordinated cluster */
          if (NM_IS_CHANNEL(NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
          {
            /* !LINKSTO Nm.SWS_Nm_00174,1, Nm.ASR403.SWS_Nm_00175,1 */
            Nm_Timer[Nm_ChanIdxFromNetworkHandle[(NetworkHandle)]] =
              NM_CHANNEL_CONFIG(NetworkHandle).ShutdownDelayTimer;
            /* Note: The case NmShutdownDelayTimer = 0 is handled in
             * the code generator to ensure that BusNm_NetworkRelease is called
             * once and only once.
             */
          }
        }

          /* switch main funtion state to start the shutdown */
        Nm_CcState[ccIdx] = NM_CC_STATE_SHUTDOWN_INITIATED;
      }

      SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
    }
  }
#endif

  DBG_NM_MAINFUNCTION_EXIT();

}


#if ((NM_DEV_ERROR_DETECT == STD_ON)                    \
  || (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON))

/* !LINKSTO Nm.SWS_Nm_00031,1 */
/*------------------[Nm_PassiveStartup]--------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_PassiveStartUp
(
  NetworkHandleType  NetworkHandle
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
  uint8 CoordClusterIndex;
#endif

  DBG_NM_PASSIVESTARTUP_ENTRY(NetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_PASSIVE_STARTUP, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00488,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_PASSIVE_STARTUP, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else
#endif
  {

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)

    /* Enter critical section: this is needed to protect the global variables
     * Nm_NmsParticipatingSleepingInCluster[], Nm_ChannelStatus[]
     * and Nm_NmsParticipatingInCluster[] because if Nm_PassiveStartUp() is
     * preempted by another task say Nm_NetworkRequest() these global
     * variables may be set to some other value.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    CoordClusterIndex = NM_CHANNEL_CONFIG(NetworkHandle).CoordClusterIndex;

    /* Update information on how many NMs participate in the cluster */
    if (NM_CC_IDX_INVALID != CoordClusterIndex)
    {
      /* Only count up if the NM was not reported as participating before */
      if (NM_IS_NOT_CHANNEL (NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
      {
        /* Channel is becoming part of the cluster / participating */
        Nm_NmsParticipatingInCluster[CoordClusterIndex]++;
        NM_SET_CHANNEL(NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER);
        /* Since the channel has not been participating in the cluster before, it was not
         * requested before, which means it is in sleep mode */
        Nm_NmsParticipatingSleepingInCluster[CoordClusterIndex]++;
      }
    }

    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    /* !LINKSTO Nm.EB_Ref.SWS_Nm_00181.PassiveStartup,1 */
    Nm_AbortShutdown(NetworkHandle, FALSE);

    /* treat the passiveStartup call as Nm_NetworkRequest() if
     * this channel is part of NetworkCluster[SWS_Nm_00245]. Execute
     * NM_BUSNM_NETWORK_REQUEST */
    if (NM_CC_IDX_INVALID != CoordClusterIndex)
    {
    /* !LINKSTO Nm.SWS_Nm_00245,1 */
    RetVal = Nm_NetworkRequestInternal(NetworkHandle,
                                       NM_SID_PASSIVE_STARTUP,
                                             NM_E_NETWORKREQUEST);
    }
    else
#endif /* NM_COORDINATOR_SUPPORT_ENABLED == STD_ON */
    {
      /* no need to request NetworkHandle, this is done by the direct call of
       * BusNm_PassiveStartUp() below */
      /* forward call to to BusNm */
#if (NM_MULTICORE_ENABLED == STD_OFF)
      RetVal = NM_BUSNM_PASSIVE_START_UP(NetworkHandle);
#else
      if(NM_BUSNM_PASSIVE_START_UP(NetworkHandle) == SCHM_E_OK)
      {
        RetVal = E_OK;
      }
      else
      {
        RetVal = E_NOT_OK;
#if (NM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO Nm.EB.SchM_Call_DET,1 */
        NM_DET_REPORT_ERROR(NM_SID_PASSIVE_STARTUP, NM_E_PASSIVESTARTUP);
#endif
      }
#endif
    }
  }

  DBG_NM_PASSIVESTARTUP_EXIT(RetVal,NetworkHandle);

  return RetVal;
}

#endif

/* !LINKSTO Nm.EB_Ref.SWS_Nm_00130,1, Nm.EB_Ref.SWS_Nm_00132,1 */
#if ((NM_PASSIVE_MODE_ENABLED == STD_OFF)               \
  && ((NM_DEV_ERROR_DETECT == STD_ON)                   \
    || (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)))
/* !LINKSTO Nm.SWS_Nm_00032,1 */
/*------------------[Nm_NetworkRequest]--------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRequest
(
   NetworkHandleType NetworkHandle
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_NM_NETWORKREQUEST_ENTRY(NetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
     NM_DET_REPORT_ERROR(NM_SID_NETWORK_REQUEST, NM_E_UNINIT);
     RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00489,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_REQUEST, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#if ((NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) || (NM_BUSNM_NUM > 1U) || (NM_CHANNEL_NUM > 1U))
  else if (TRUE == NM_CHANNEL_CONFIG(NetworkHandle).PassiveModeEnabled)
  {
    /* !LINKSTO Nm.SWS_Nm_00130,1 */
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_REQUEST, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#endif
  else
#endif
  {

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)

    /* Enter critical section: this is needed to protect the global variables
     * Nm_NmsParticipatingSleepingInCluster[], Nm_ChannelStatus[]
     * and Nm_NmsParticipatingInCluster[] because if Nm_NetworkRequest() is
     * preempted by another task say Nm_PassiveStartUp() these global
     * variables may be set to some other value.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
    {
      const uint8 CoordClusterIndex = NM_CHANNEL_CONFIG(NetworkHandle).CoordClusterIndex;

      /* Update information on how many NMs participate in the cluster */
      if (NM_CC_IDX_INVALID != CoordClusterIndex)
      {
        /* Only count up if the NM was not reported as participating before */
        if (NM_IS_NOT_CHANNEL(NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
        {
          /* Channel is becoming part of the cluster / participating now */
          Nm_NmsParticipatingInCluster[CoordClusterIndex]++;
          NM_SET_CHANNEL (NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER);
          /* Since the channel has not been participating in the cluster before, it was not
           * requested before, which means it is in sleep mode */
          Nm_NmsParticipatingSleepingInCluster[CoordClusterIndex]++;
        }
      }
    }

    /* Channel is marked as being actually requested by ComM */
    NM_SET_CHANNEL(NetworkHandle, NM_CHANNEL_REQUESTED_BY_COMM);

    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    /* !LINKSTO Nm.EB_Ref.SWS_Nm_00181.NetworkRequest,1 */
    Nm_AbortShutdown(NetworkHandle, FALSE);

#endif

    /* no need to request NetworkHandle, this is done next by the direct call */
    /* forward call to BusNm */
    RetVal = Nm_NetworkRequestInternal(NetworkHandle,
                                       NM_SID_NETWORK_REQUEST,
                                       NM_E_NETWORKREQUEST);
  }

  DBG_NM_NETWORKREQUEST_EXIT(RetVal,NetworkHandle);

  return RetVal;
}

/* !LINKSTO Nm.SWS_Nm_00046,1 */
/*------------------[Nm_NetworkRelease]--------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRelease
(
  NetworkHandleType NetworkHandle
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_NM_NETWORKRELEASE_ENTRY(NetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_RELEASE, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00490,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_RELEASE, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#if ((NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) || (NM_BUSNM_NUM > 1U) || (NM_CHANNEL_NUM > 1U))
  else if (TRUE == NM_CHANNEL_CONFIG(NetworkHandle).PassiveModeEnabled)
  {
    /* !LINKSTO Nm.SWS_Nm_00132,1 */
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_RELEASE, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#endif
  else
#endif
  {

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    const uint8 CoordClusterIndex = NM_CHANNEL_CONFIG(NetworkHandle).CoordClusterIndex;

    /* Enter critical section: this is needed to protect the global variable
     * Nm_ChannelStatus[] because if Nm_NetworkRelease() is
     * preempted by another task say Nm_NetworkRequest() Nm_ChannelStatus[]
     * may be set as Nm-channel is requested by ComM.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
    NM_UNSET_CHANNEL (NetworkHandle, NM_CHANNEL_REQUESTED_BY_COMM);
    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    if (NM_CC_IDX_INVALID != CoordClusterIndex)
    {
      /* !LINKSTO Nm.ASR403.SWS_Nm_00170,1, Nm.EB_Ref.SWS_Nm_00171,1 */
      Nm_CoordinatedShutdownHandler(CoordClusterIndex);

      /* If coordinated shutdown is possible it will be initiated in the above
       * function call.  If shutdown is not possible the NetworkRelease request
       * is _not_ forwarded to the BusNm to keep the bus awake as part of the
       * cluster being awake.
       *
       * OK is returned because the release request is not lost but only
       * delayed. */

      /* Nothing to do here: the return value is still E_OK */
      RetVal = E_OK;
    }
    else
#endif /* NM_COORDINATOR_SUPPORT_ENABLED == STD_ON */
    {
      /* else: for non-coordinated channels forward call to BusNm */
      RetVal = Nm_NetworkReleaseInternal(NetworkHandle,
                                         NM_SID_NETWORK_RELEASE,
                                         NM_E_NETWORKRELEASE);
    }
  }

  DBG_NM_NETWORKRELEASE_EXIT(RetVal,NetworkHandle);

  return RetVal;
}

#endif

#if ((NM_PASSIVE_MODE_ENABLED == STD_OFF) && \
     (NM_DEV_ERROR_DETECT == STD_ON) && \
     (EB_NM_STACK == STD_ON))
/* !LINKSTO Nm.EB.Nm_NetworkGwEraRequest,1 */
/*------------------[Nm_NetworkGwEraRequest]--------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_NetworkGwEraRequest
(
   NetworkHandleType NetworkHandle
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_NM_NETWORKGWERAREQUEST_ENTRY(NetworkHandle);

  if (Nm_Initialized == FALSE)
  {
     NM_DET_REPORT_ERROR(NM_SID_NETWORKGWERAREQUEST, NM_E_UNINIT);
     RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_NETWORKGWERAREQUEST, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#if ((NM_BUSNM_NUM > 1U) || (NM_CHANNEL_NUM > 1U))
  else if (TRUE == NM_CHANNEL_CONFIG(NetworkHandle).PassiveModeEnabled)
  {
    NM_DET_REPORT_ERROR(NM_SID_NETWORKGWERAREQUEST, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#endif /* ((NM_BUSNM_NUM > 1U) || (NM_CHANNEL_NUM > 1U)) */
  else
  {
#if (NM_MULTICORE_ENABLED == STD_OFF)
    RetVal = NM_BUSNM_NETWORK_GW_ERA_REQUEST(NetworkHandle);
#else
    /* !LINKSTO Nm.EB.SchM_Call_CanNm_NetworkGwEraRequest,1 */
    /* !LINKSTO Nm.EB.SchM_Call_FrNm_NetworkGwEraRequest,1 */
    /* !LINKSTO Nm.EB.SchM_Call_UdpNm_NetworkGwEraRequest,1 */
    if (NM_BUSNM_NETWORK_GW_ERA_REQUEST(NetworkHandle) == SCHM_E_OK)
    {
      RetVal = E_OK;
    }
    else
    {
      NM_DET_REPORT_ERROR(NM_SID_NETWORKGWERAREQUEST, NM_E_NETWORKGWERAREQUEST);
    }
#endif /* (NM_MULTICORE_ENABLED == STD_OFF) */
  }
  DBG_NM_NETWORKGWERAREQUEST_EXIT(RetVal,NetworkHandle);
  return RetVal;
}
#endif /* ((NM_PASSIVE_MODE_ENABLED == STD_OFF) && \
        *  (NM_DEV_ERROR_DETECT == STD_ON) && \
        *  (EB_NM_STACK == STD_ON)
        */

#if (NM_COM_CONTROL_ENABLED == STD_ON)
#if (NM_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO Nm.SWS_Nm_00033,1 */
/*------------------[Nm_DisableCommunication]--------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_DisableCommunication
(
   NetworkHandleType NetworkHandle
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_DISABLECOMMUNICATION_ENTRY(NetworkHandle);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_DISABLE_COM, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00491,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_DISABLE_COM, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else
  {
    RetVal = NM_BUSNM_DISABLE_COMMUNICATION(NetworkHandle);
  }

  DBG_NM_DISABLECOMMUNICATION_EXIT(RetVal,NetworkHandle);

  return RetVal;
}

/* !LINKSTO Nm.SWS_Nm_00034,1 */
/*------------------[Nm_EnableCommunication]---------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_EnableCommunication
(
   NetworkHandleType NetworkHandle
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_ENABLECOMMUNICATION_ENTRY(NetworkHandle);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_ENABLE_COM, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00492,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_ENABLE_COM, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else
  {
    RetVal = NM_BUSNM_ENABLE_COMMUNICATION(NetworkHandle);
  }

  DBG_NM_ENABLECOMMUNICATION_EXIT(RetVal,NetworkHandle);

  return RetVal;
}
#endif
#endif

/* !LINKSTO Nm.SWS_Nm_00138,1, Nm.SWS_Nm_00241,1 */
#if ((NM_USER_DATA_ENABLED == STD_ON) \
  && (NM_PASSIVE_MODE_ENABLED == STD_OFF) \
  && (NM_COM_USER_DATA_ENABLED == STD_OFF) \
  && (NM_DEV_ERROR_DETECT == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00035,1 */
/*------------------[Nm_SetUserData]-----------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_SetUserData
(
   NetworkHandleType                        NetworkHandle,
   P2CONST(uint8, AUTOMATIC, NM_APPL_DATA) nmUserDataPtr
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_SETUSERDATA_ENTRY(NetworkHandle,nmUserDataPtr);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_SET_USER_DATA, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00493,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_SET_USER_DATA, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else if (nmUserDataPtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_SET_USER_DATA, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
#if (NM_MULTIPLE_BUS_TYPES == STD_ON)
  else if (NM_BUSNM_SET_USER_DATA_FCT_PTR(NetworkHandle) == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_SET_USER_DATA, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
#endif
  else
  {
    RetVal = NM_BUSNM_SET_USER_DATA(NetworkHandle, nmUserDataPtr);
  }

  DBG_NM_SETUSERDATA_EXIT(RetVal,NetworkHandle,nmUserDataPtr);

  return RetVal;
}
#endif

/* !LINKSTO Nm.SWS_Nm_00140,1 */
#if ((NM_USER_DATA_ENABLED == STD_ON)           \
  && (NM_DEV_ERROR_DETECT == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00036,1 */
/*------------------[Nm_GetUserData]-----------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_GetUserData
(
   NetworkHandleType                       NetworkHandle,
   P2VAR(uint8, AUTOMATIC, NM_APPL_DATA)   nmUserDataPtr
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_GETUSERDATA_ENTRY(NetworkHandle,nmUserDataPtr);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_USER_DATA, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00494,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_USER_DATA, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else if (nmUserDataPtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_USER_DATA, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
  else
  {
    RetVal = NM_BUSNM_GET_USER_DATA(NetworkHandle, nmUserDataPtr);
  }

  DBG_NM_GETUSERDATA_EXIT(RetVal,NetworkHandle,nmUserDataPtr);

  return RetVal;
}

#endif

/* !LINKSTO Nm.ASR403.SWS_Nm_00142,2 */
#if (((NM_NODE_ID_ENABLED == STD_ON)            \
    || (NM_NODE_DETECTION_ENABLED == STD_ON)    \
    || (NM_USER_DATA_ENABLED == STD_ON))        \
  && (NM_DEV_ERROR_DETECT == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00037,1 */
/*------------------[Nm_GetPduData]------------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_GetPduData
(
   NetworkHandleType                       NetworkHandle,
   P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmPduData
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_GETPDUDATA_ENTRY(NetworkHandle,nmPduData);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_PDU_DATA, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00495,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_PDU_DATA, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else if (nmPduData == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_PDU_DATA, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
#if (NM_USER_DATA_ENABLED == STD_OFF)
  else if((NM_NODE_DETECTION_ENABLED_VALUE(NetworkHandle) == FALSE) &&
          (NM_NODE_ID_ENABLED_VALUE(NetworkHandle) == FALSE))
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_PDU_DATA, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#endif
  else
  {
    RetVal = NM_BUSNM_GET_PDU_DATA(NetworkHandle, nmPduData);
  }

  DBG_NM_GETPDUDATA_EXIT(RetVal,NetworkHandle,nmPduData);

  return RetVal;
}
#endif

/* !LINKSTO Nm.EB_Ref.SWS_Nm_00144,2 */
#if ((NM_NODE_DETECTION_ENABLED == STD_ON) && (NM_DEV_ERROR_DETECT == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00038,1 */
/*------------------[Nm_RepeatMessageRequest]--------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_RepeatMessageRequest
(
   NetworkHandleType NetworkHandle
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_REPEATMESSAGEREQUEST_ENTRY(NetworkHandle);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_REPEAT_MSG_REQ, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00496,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_REPEAT_MSG_REQ, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#if (NM_NODE_DETECTION_ENABLED_ON_ALL_CHANNELS == STD_OFF)
  else if(NM_NODE_DETECTION_ENABLED_VALUE(NetworkHandle) == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_REPEAT_MSG_REQ, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#endif
  else
  {
    RetVal = NM_BUSNM_REPEAT_MESSAGE_REQUEST(NetworkHandle);
  }

  DBG_NM_REPEATMESSAGEREQUEST_EXIT(RetVal,NetworkHandle);

  return RetVal;
}

#endif

/* !LINKSTO Nm.EB_Ref.SWS_Nm_00146,2, Nm.EB_Ref.SWS_Nm_00148,2 */
#if ((NM_NODE_ID_ENABLED == STD_ON) && (NM_DEV_ERROR_DETECT == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00039,1 */
/*------------------[Nm_GetNodeIdentifier]-----------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_GetNodeIdentifier
(
   NetworkHandleType                     NetworkHandle,
   P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_GETNODEIDENTIFIER_ENTRY(NetworkHandle,nmNodeIdPtr);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_NODE_ID, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00497,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_NODE_ID, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else if (nmNodeIdPtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_NODE_ID, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
#if (NM_NODE_ID_ENABLED_ON_ALL_CHANNELS == STD_OFF)
  else if(NM_NODE_ID_ENABLED_VALUE(NetworkHandle) == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_NODE_ID, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#endif
  else
  {
    RetVal = NM_BUSNM_GET_NODE_IDENTIFIER(NetworkHandle, nmNodeIdPtr);
  }

  DBG_NM_GETNODEIDENTIFIER_EXIT(RetVal,NetworkHandle,nmNodeIdPtr);

  return RetVal;
}

/* !LINKSTO Nm.SWS_Nm_00040,1 */
/*------------------[Nm_GetLocalNodeIdentifier]------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_GetLocalNodeIdentifier
(
   NetworkHandleType                     NetworkHandle,
   P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmNodeIdPtr
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_GETLOCALNODEIDENTIFIER_ENTRY(NetworkHandle,nmNodeIdPtr);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_LOCAL_NODE_ID, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00498,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_LOCAL_NODE_ID, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else if (nmNodeIdPtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_LOCAL_NODE_ID, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
#if (NM_NODE_ID_ENABLED_ON_ALL_CHANNELS == STD_OFF)
  else if(NM_NODE_ID_ENABLED_VALUE(NetworkHandle) == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_LOCAL_NODE_ID, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
#endif
  else
  {
    RetVal = NM_BUSNM_GET_LOCAL_NODE_IDENTIFIER(NetworkHandle, nmNodeIdPtr);
  }

  DBG_NM_GETLOCALNODEIDENTIFIER_EXIT(RetVal,NetworkHandle,nmNodeIdPtr);

  return RetVal;
}
#endif

/* !LINKSTO Nm.SWS_Nm_00150,1 */
#if ((NM_REMOTE_SLEEP_IND_ENABLED == STD_ON) && (NM_DEV_ERROR_DETECT == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00042,1 */
/*------------------[Nm_CheckRemoteSleepIndication]--------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_CheckRemoteSleepIndication
(
   NetworkHandleType                       nmNetworkHandle,
   P2VAR(boolean, AUTOMATIC, NM_APPL_DATA) nmRemoteSleepIndPtr
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_CHECKREMOTESLEEPINDICATION_ENTRY(nmNetworkHandle,nmRemoteSleepIndPtr);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_CHECK_REMOTE_SLEEP_IND, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00499,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_CHECK_REMOTE_SLEEP_IND, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else if (nmRemoteSleepIndPtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_CHECK_REMOTE_SLEEP_IND, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
  else
  {
    RetVal = NM_BUSNM_CHECK_REMOTE_SLEEP_INDICATION(nmNetworkHandle, nmRemoteSleepIndPtr);
  }

  DBG_NM_CHECKREMOTESLEEPINDICATION_EXIT(RetVal,nmNetworkHandle,nmRemoteSleepIndPtr);

  return RetVal;
}
#endif


/*------------------[Nm_GetCoordinatorState]--------------------------------------------*/

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* !LINKSTO Nm.EB.ASR40.Nm_GetCoordinatorState,1 */
FUNC(Std_ReturnType, NM_CODE) Nm_GetCoordinatorState
(
   uint8                                 nmCoordinatorId,
   P2VAR(uint8, AUTOMATIC, NM_APPL_DATA) nmStatePtr
)
{
  Std_ReturnType RetVal = E_NOT_OK

  DBG_NM_GETCOORDINATORSTATE_ENTRY(nmCoordinatorId,nmStatePtr);
#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GETCOORDINATORSTATE, NM_E_UNINIT);
  }
  else if (nmCoordinatorId >= NM_CC_NUM)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_GETCOORDINATORSTATE, NM_E_HANDLE_UNDEF);
  }
  else if (nmStatePtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GETCOORDINATORSTATE, NM_E_PARAM_POINTER);
  }
  else
#endif
  {
    RetVal = E_OK;
    *nmStatePtr = Nm_CcState[nmCoordinatorId];
  }

  DBG_NM_GETCOORDINATORSTATE_EXIT(RetVal,nmCoordinatorId,nmStatePtr);

  return RetVal;
}

#endif


#if (NM_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO Nm.SWS_Nm_00043,1 */
/*------------------[Nm_GetState]--------------------------------------------*/
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(Std_ReturnType, NM_CODE) Nm_GetState
(
   NetworkHandleType                            nmNetworkHandle,
   P2VAR(Nm_StateType, AUTOMATIC, NM_APPL_DATA) nmStatePtr,
   P2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_DATA)  nmModePtr
)
{
  Std_ReturnType RetVal; /* no initialization, all paths set this variable */

  DBG_NM_GETSTATE_ENTRY(nmNetworkHandle,nmStatePtr,nmModePtr);

  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_GET_STATE, NM_E_UNINIT);
    RetVal = E_NOT_OK;
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.SWS_Nm_00500,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_STATE, NM_E_HANDLE_UNDEF);
    RetVal = E_NOT_OK;
  }
  else if (nmStatePtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_STATE, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
  else if (nmModePtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_STATE, NM_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
  else
  {
    RetVal = NM_BUSNM_GET_STATE(nmNetworkHandle, nmStatePtr, nmModePtr);
  }

  DBG_NM_GETSTATE_EXIT(RetVal,nmNetworkHandle,nmStatePtr,nmModePtr);

  return RetVal;
}

#endif

/* !LINKSTO Nm.ASR403.SWS_Nm_00153,1 */
#if (NM_VERSION_INFO_API == STD_ON)
/* !LINKSTO Nm.SWS_Nm_00044,1 */
/*------------------[Nm_GetVersionInfo]--------------------------------------*/
FUNC(void, NM_CODE) Nm_GetVersionInfo(
   P2VAR(Std_VersionInfoType, AUTOMATIC, NM_APPL_DATA) nmVerInfoPtr)
{
  DBG_NM_GETVERSIONINFO_ENTRY(nmVerInfoPtr);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == nmVerInfoPtr)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_GET_VERSION_INFO, NM_E_PARAM_POINTER);
  }
  else
#endif
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00152,1 */
    nmVerInfoPtr->vendorID         = NM_VENDOR_ID;
    nmVerInfoPtr->moduleID         = NM_MODULE_ID;
    nmVerInfoPtr->sw_major_version = NM_SW_MAJOR_VERSION;
    nmVerInfoPtr->sw_minor_version = NM_SW_MINOR_VERSION;
    nmVerInfoPtr->sw_patch_version = NM_SW_PATCH_VERSION;
  }

  DBG_NM_GETVERSIONINFO_EXIT(nmVerInfoPtr);
}
#endif

#if ((NM_DEV_ERROR_DETECT == STD_ON)            || \
     (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) || \
     (NM_MULTICORE_ENABLED == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00154,1, Nm.EB.NmMultiCoreSupport_ON_1,1 */
/*------------------[Nm_NetWorkStartIndication]------------------------------*/
/* Deviation MISRAC2012-1 */
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_NetworkStartIndication
(
  NetworkHandleType nmNetworkHandle
)
{
  DBG_NM_NETWORKSTARTINDICATION_ENTRY(nmNetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_START_IND, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_START_IND, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
   /* Abort Shutdown shall be called before marking the channel as active.
    * This shall be done because of race conditions.
    * In case current function is interrupted by mainfunction and a timer expires
    * in the mainfunction, the channel will be marked
    * first as active (from current function) and then inactive (from mainfunction).
    * If the abort shutdown is called first the timer per channel shall be stoped and
    * in this case the channel shall not be marked as inactive in the mainfunction
    */
   /* !LINKSTO Nm.EB_Ref.SWS_Nm_00181.NetworkStartIndication,1 */
   /* Only if the channel is known as participating in a cluster, call abort routine */
   if (NM_IS_CHANNEL (nmNetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
   {
     Nm_AbortShutdown(nmNetworkHandle, FALSE);
   }
   /* Enter critical section: this is needed to protect the global variable
    * Nm_ChannelStatus[] because if Nm_NetworkStartIndication() is
    * preempted by another task say Nm_BusSleepMode() Nm_ChannelStatus[]
    * may be set as no remote nodes are active */
   SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
   /* Channel has active remote nodes - but is asleep! */
   NM_UNSET_CHANNEL (nmNetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE);
   SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
#endif

    /* !LINKSTO Nm.SWS_Nm_00155,1 */
    ComM_Nm_NetworkStartIndication(nmNetworkHandle);
  }

  DBG_NM_NETWORKSTARTINDICATION_EXIT(nmNetworkHandle);
}

/* !LINKSTO Nm.SWS_Nm_00156,1, Nm.EB.NmMultiCoreSupport_ON_2,1 */
/*------------------[Nm_NetworkMode]-----------------------------------------*/
/* Deviation MISRAC2012-1 */
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_NetworkMode
(
 NetworkHandleType nmNetworkHandle
)
{
  DBG_NM_NETWORKMODE_ENTRY(nmNetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_MODE, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_NETWORK_MODE, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Abort Shutdown shall be called before marking the channel as active.
     * This shall be done because of race conditions.
     * In case current function is interrupted by mainfunction and a timer expires
     * in the mainfunction, the channel will be marked
     * first as active (from current function) and then inactive (from mainfunction).
     * If the abort shutdown is called first the timer per channel shall be stoped and
     * in this case the channel shall not be marked as inactive in the mainfunction
     */
    /* !LINKSTO Nm.EB_Ref.SWS_Nm_00181.NetworkMode,1 */
    /* If the network that indicated NetworkMode was not previously awake, this is a strange error;
     * so we do only call "abort shutdown" if a network that is part of the cluster wakes up */

    if (NM_IS_CHANNEL (nmNetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
    {
      Nm_AbortShutdown(nmNetworkHandle, TRUE);
    }
    /* Enter critical section: this is needed to protect the global variables
     * Nm_ChannelStatus[] and Nm_NmsParticipatingSleepingInCluster[]
     * because if Nm_NetworkMode() is preempted by another task say
     * Nm_NetworkRequest() these global variables may be set to some other value.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    {
      const uint8 CoordClusterIndex = NM_CHANNEL_CONFIG(nmNetworkHandle).CoordClusterIndex;

      /* Access of Nm_ChannelStatus only is required for NMs of a cluster */
      if (NM_CC_IDX_INVALID != CoordClusterIndex)
      {
        /* If Nm_NetworkMode is called for a channel that is not participating in a cluster,
         * that is, that was not requested by ComM before, the BusNm is out of control.
         * In that case, ignore the call as far as it concerns the coordinator */
        if (NM_IS_CHANNEL (nmNetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
        {
          /* We know the channel is participating in a cluster. Check if it was sleeping
           * before before un-setting the sleep flag */
          if (NM_IS_CHANNEL (nmNetworkHandle, NM_CHANNEL_ASLEEP))
          {
            /* The channel came back from Bus Sleep State (Restart); decrease the count of
             * channels in the cluster that are participating and sleeping */
            Nm_NmsParticipatingSleepingInCluster[CoordClusterIndex]--;
          }

          /* We can assume that upon entering network mode, remote nodes will be active */
          NM_UNSET_CHANNEL (nmNetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE);
          /* Channel is not asleep */
          NM_UNSET_CHANNEL (nmNetworkHandle, NM_CHANNEL_ASLEEP);
        }
      }
    }

    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

#endif

    /* !LINKSTO Nm.SWS_Nm_00158,1 */
    ComM_Nm_NetworkMode(nmNetworkHandle);
  }

  DBG_NM_NETWORKMODE_EXIT(nmNetworkHandle);
}

/* !LINKSTO Nm.SWS_Nm_00162,1, Nm.EB.NmMultiCoreSupport_ON_3,1 */
/*------------------[Nm_BusSleepMode]----------------------------------------*/
/* Deviation MISRAC2012-1 */
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_BusSleepMode
(
 NetworkHandleType nmNetworkHandle
)
{
  DBG_NM_BUSSLEEPMODE_ENTRY(nmNetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_BUS_SLEEP_MODE, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_BUS_SLEEP_MODE, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Enter critical section: this is needed to protect the global variables
     * Nm_ChannelStatus[] and Nm_NmsParticipatingSleepingInCluster[]
     * because if Nm_BusSleepMode() is preempted by another task say
     * Nm_NetworkMode() these global variables may be set to some other value.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
    {
      /* Update information on how many NMs in the cluster sleep */
      if (NM_IS_CHANNEL (nmNetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
      {
        /* Only count up if the NM was not reported as sleeping before and is participating in the
         * cluster */
        if (NM_IS_NOT_CHANNEL (nmNetworkHandle, NM_CHANNEL_ASLEEP))
        {
          const uint8 CoordClusterIndex = NM_CHANNEL_CONFIG(nmNetworkHandle).CoordClusterIndex;
          Nm_NmsParticipatingSleepingInCluster[CoordClusterIndex]++;
        }
      }
    }

    /* Channel is asleep, no remote nodes active */
    NM_SET_CHANNEL (nmNetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE);
    NM_SET_CHANNEL (nmNetworkHandle, NM_CHANNEL_ASLEEP);

    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
#endif  /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

    /* !LINKSTO Nm.SWS_Nm_00163,1 */
    ComM_Nm_BusSleepMode(nmNetworkHandle);
  }

  DBG_NM_BUSSLEEPMODE_EXIT(nmNetworkHandle);
}

/* !LINKSTO Nm.SWS_Nm_00159,1, Nm.EB.NmMultiCoreSupport_ON_4,1 */
/*------------------[Nm_PrepareBusSleepMode]---------------------------------*/
/* Deviation MISRAC2012-1 */
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_PrepareBusSleepMode
(
 NetworkHandleType            nmNetworkHandle
)
{
  DBG_NM_PREPAREBUSSLEEPMODE_ENTRY(nmNetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_PREPARE_BUS_SLEEP_MODE, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_PREPARE_BUS_SLEEP_MODE, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Enter critical section: this is needed to protect the global variable
     * Nm_ChannelStatus[] because if Nm_PrepareBusSleepMode() is
     * preempted by another task say Nm_NetworkStartIndication() Nm_ChannelStatus[]
     * may be set as remote nodes are active.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    /* No remote nodes active */
    NM_SET_CHANNEL (nmNetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE);

    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

    /* !LINKSTO Nm.SWS_Nm_00161,1 */
    ComM_Nm_PrepareBusSleepMode(nmNetworkHandle);
  }

  DBG_NM_PREPAREBUSSLEEPMODE_EXIT(nmNetworkHandle);
}

#endif

#if ((NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
     (NM_DEV_ERROR_DETECT == STD_ON))
/* !LINKSTO Nm.ASRR2111.SWS_Nm_91009,1,Nm.EB_Ref.SWS_Nm_00305,1 */
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_ForwardSynchronizedPncShutdown
(
  NetworkHandleType NetworkHandle,
  P2CONST(uint8, AUTOMATIC, NM_APPL_CONST) PncBitVectorPtr
)
{
  DBG_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN_ENTRY(NetworkHandle,PncBitVectorPtr);
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN, NM_E_HANDLE_UNDEF);
  }
  else if (PncBitVectorPtr == NULL_PTR)
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00248,1 */
    NM_DET_REPORT_ERROR(NM_SID_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN, NM_E_PARAM_POINTER);
  }
  else
  {
    ComM_Nm_ForwardSynchronizedPncShutdown(NetworkHandle, PncBitVectorPtr);
  }
  DBG_NM_FORWARDSYNCHRONIZEDPNCSHUTDOWN_EXIT(NetworkHandle,PncBitVectorPtr);
}
#endif /* #if ((NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) && \
        *      (NM_DEV_ERROR_DETECT == STD_ON))
        */

/* !LINKSTO Nm.SWS_Nm_00277,1, Nm.SWS_Nm_00278,1 */
#if ((NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) || \
     (NM_PROVIDE_REMOTE_SLEEP_CALLBACKS == STD_ON))
/* !LINKSTO Nm.SWS_Nm_00192,1 */
/*------------------[Nm_RemoteSleepIndication]-------------------------------*/
/* Deviation MISRAC2012-1 */
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_RemoteSleepIndication
(
 NetworkHandleType nmNetworkHandle
)
{
  DBG_NM_REMOTESLEEPINDICATION_ENTRY(nmNetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_REMOTE_SLEEP_INDICATION, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_REMOTE_SLEEP_INDICATION, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Enter critical section: this is needed to protect the global variable
     * Nm_ChannelStatus[] because if Nm_RemoteSleepIndication() is
     * preempted by another task say Nm_NetworkStartIndication() Nm_ChannelStatus[]
     * may be set as remote nodes are active.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    /* Channel is asleep, no remote nodes active */
    NM_SET_CHANNEL (nmNetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE);

    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    {
      const uint8 CoordClusterIndex = NM_CHANNEL_CONFIG(nmNetworkHandle).CoordClusterIndex;

      if (NM_CC_IDX_INVALID != CoordClusterIndex)
      {
        /* !LINKSTO Nm.ASR403.SWS_Nm_00170,1, Nm.EB_Ref.SWS_Nm_00171,1 */
        Nm_CoordinatedShutdownHandler(CoordClusterIndex);
      }
    }
#endif
    /* !LINKSTO Nm.EB.ASR40.RemoteSleepIndicationCallback,1 */
#if (NM_PROVIDE_REMOTE_SLEEP_CALLBACKS == STD_ON)
    NM_REMOTE_SLEEP_INDICATION_CALLBACK(nmNetworkHandle);
#endif
  }
  DBG_NM_REMOTESLEEPINDICATION_EXIT(nmNetworkHandle);
}

/* !LINKSTO Nm.SWS_Nm_00193,1 */
/*------------------[Nm_RemoteSleepCancellation]-----------------------------*/
/* Deviation MISRAC2012-1 */
/* Deviation MISRAC2012-2 */
/* Deviation MISRAC2012-3 */
FUNC(void, NM_CODE) Nm_RemoteSleepCancellation
(
 NetworkHandleType nmNetworkHandle
)
{
  DBG_NM_REMOTESLEEPCANCELLATION_ENTRY(nmNetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_REMOTE_SLEEP_CANCELLATION, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_REMOTE_SLEEP_CANCELLATION, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
    /* Abort Shutdown shall be called before marking the channel as active.
     * This shall be done because of race conditions.
     * In case current function is interrupted by mainfunction and a timer expires
     * in the mainfunction, the channel will be marked
     * first as active (from current function) and then inactive (from mainfunction).
     * If the abort shutdown is called first the timer per channel shall be stoped and
     * in this case the channel shall not be marked as inactive in the mainfunction
     */
    /* !LINKSTO Nm.EB_Ref.SWS_Nm_00181.RemoteSleepCancelation,1 */
    Nm_AbortShutdown(nmNetworkHandle, TRUE);
    /* Enter critical section: this is needed to protect the global variable
     * Nm_ChannelStatus[] because if Nm_RemoteSleepCancellation() is
     * preempted by another task say Nm_BusSleepMode() Nm_ChannelStatus[]
     * may be set as no remote nodes are active.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    /* Channel is asleep, no remote nodes active */
    NM_UNSET_CHANNEL (nmNetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE);

    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
#endif
    /* !LINKSTO Nm.EB.ASR40.RemoteSleepCancellationCallback,1 */
#if (NM_PROVIDE_REMOTE_SLEEP_CALLBACKS == STD_ON)
    NM_REMOTE_SLEEP_CANCELLATION_CALLBACK(nmNetworkHandle);
#endif
  }

  DBG_NM_REMOTESLEEPCANCELLATION_EXIT(nmNetworkHandle);
}
#endif

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* !LINKSTO Nm.SWS_Nm_00194,1 */
/*------------------[Nm_SynchronizationPoint]-------------------------------*/
FUNC(void, NM_CODE) Nm_SynchronizationPoint
(
 NetworkHandleType nmNetworkHandle
)
{
  DBG_NM_SYNCHRONIZATIONPOINT_ENTRY(nmNetworkHandle);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_SYNCHRONIZATIONPOINT,  NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_SYNCHRONIZATIONPOINT, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {
    const uint8 CoordClusterIndex = NM_CHANNEL_CONFIG(nmNetworkHandle).CoordClusterIndex;
    /* Enter critical section: this is needed to protect the global variable
     * Nm_CcState as the cluster state is modified in different contexts.*/
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
    /* !LINKSTO Nm.SWS_Nm_00172,1 */
    if (NM_CHANNEL_CONFIG(nmNetworkHandle).NmSynchronizingNetwork == TRUE)
    {
      /* !LINKSTO Nm.EB_Ref.SWS_Nm_00173.1,1, Nm.EB_Ref.SWS_Nm_00173.2,1 */
      if (Nm_CcState[CoordClusterIndex] == NM_CC_STATE_WAIT_SYNCHRONIZATION)
      {
        /* switch main funtion state to start the shutdown */
        Nm_CcState[CoordClusterIndex] = NM_CC_STATE_PREPARE_SHUTDOWN;
      }
    }
    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
  }

  DBG_NM_SYNCHRONIZATIONPOINT_EXIT(nmNetworkHandle);
}
#endif

/* !LINKSTO Nm.SWS_Nm_00114,1 */
/*----------------------[Nm_StateChangeNotification]--------------------------*/
#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
/* Deviation MISRAC2012-1 */
FUNC(void, NM_CODE) Nm_StateChangeNotification
(
  NetworkHandleType nmNetworkHandle,
  Nm_StateType nmPreviousState,
  Nm_StateType nmCurrentState
)
{
#if (NM_STATE_REPORT_ENABLED == STD_ON)
  uint8 NmState = 0U;    /* Network Management State */
#endif
#if ((NM_STATE_CHANGE_NOTIFICATION_CALLOUT == STD_OFF) && \
     (NM_STATE_REPORT_ENABLED == STD_OFF) && \
     (NM_DEV_ERROR_DETECT == STD_OFF))
   TS_PARAM_UNUSED(nmNetworkHandle);
#endif
#if ((NM_STATE_CHANGE_NOTIFICATION_CALLOUT == STD_OFF) && (NM_STATE_REPORT_ENABLED == STD_OFF))
   TS_PARAM_UNUSED(nmPreviousState);
   TS_PARAM_UNUSED(nmCurrentState);
#endif
  DBG_NM_STATECHANGENOTIFICATION_ENTRY(nmNetworkHandle,nmPreviousState,nmCurrentState);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_STATECHANGENOTIFICATION, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmNetworkHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_STATECHANGENOTIFICATION, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {
#if (NM_STATE_REPORT_ENABLED == STD_ON)
    /* !LINKSTO Nm.SWS_Nm_00249,1 */
    if (NM_COM_SIGNAL_INVALID != NM_CHANNEL_CONFIG(nmNetworkHandle).NmComHandleId)
    {
      if (NM_STATE_REPEAT_MESSAGE == nmCurrentState)
      {
        switch (nmPreviousState)
        {
          /* Repeat message reached from BusSleep mode */
          case NM_STATE_BUS_SLEEP:
            NmState  = NM_RM_BSM;
            break;

          /* Repeat message reached from PrepareBusSleep mode */
          case NM_STATE_PREPARE_BUS_SLEEP:
            NmState  = NM_RM_PBSM;
            break;

          /* Repeat message reached from ReadySleep mode */
          case NM_STATE_READY_SLEEP:
            NmState  = NM_RM_RS;
            break;

          /* Repeat message reached from Normal Operation */
          case NM_STATE_NORMAL_OPERATION:
            NmState  = NM_RM_NO;
            break;

          default:
            /* Com_SendSignal() shall not be called */
            NmState = NM_NMS_RESET;
            break;
        }
      }
      else if (NM_STATE_NORMAL_OPERATION == nmCurrentState)
      {
        switch(nmPreviousState)
        {
          /* Normal Operation mode reached from Repeat message */
          case NM_STATE_REPEAT_MESSAGE:
            NmState  = NM_NO_RM;
            break;

          /* Normal Operation mode reached from ReadySleep */
          case NM_STATE_READY_SLEEP:
            NmState  = NM_NO_RS;
            break;

          default:
            /* Com_SendSignal() shall not be called */
            NmState = NM_NMS_RESET;
            break;
        }
      }
      else
      {
        /* Com_SendSignal() shall not be called if the current state is not
         * Repeat message or Normal operation */
        NmState = NM_NMS_RESET;
      }
    }

    if (NM_NMS_RESET != NmState)
    {
      /* Invoke Com_SendSignal() with Network Management State */
      (void)Com_SendSignal(NM_CHANNEL_CONFIG(nmNetworkHandle).NmComHandleId, (const void*)&NmState);
    }
#endif

#if (NM_STATE_CHANGE_NOTIFICATION_CALLOUT == STD_ON)
    /* Forward the values of the previous state and current state to
     * a callout function which can be implemented by the user
     * to handle the state change.
     */
    Nm_StateChangeNotificationCallout(nmNetworkHandle, nmPreviousState, nmCurrentState);
#endif
  }

  DBG_NM_STATECHANGENOTIFICATION_EXIT(nmNetworkHandle,nmPreviousState,nmCurrentState);
}
#endif
#if (NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON)
/*------------------[Nm_RequestSynchronizedPncShutdown]--------------------------------------*/
/* !LINKSTO Nm.ASRR2111.SWS_Nm_91005,1, Nm.EB_Ref.SWS_Nm_00506,1 */
FUNC(Std_ReturnType, NM_CODE) Nm_RequestSynchronizedPncShutdown
(
  NetworkHandleType  NetworkHandle,
  PNCHandleType      PncId
)
{
  Std_ReturnType Retval = E_NOT_OK;
  DBG_NM_REQUESTSYNCHRONIZEDPNCSHUTDOWN_ENTRY(NetworkHandle,PncId);

#if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(NetworkHandle))
  {
    /* !LINKSTO Nm.ASRR2111.SWS_Nm_00508,1, Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, NM_E_HANDLE_UNDEF);
  }
  else
#endif /* #if (NM_DEV_ERROR_DETECT == STD_ON) */
  {
#if (NM_BUSNM_NUM == 1)
#if (NM_MULTICORE_ENABLED == STD_ON)
#if (NM_GENERICNM_USED == STD_ON)
    Retval = NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(NetworkHandle,PncId);
#else /* #if (NM_GENERICNM_USED == STD_ON) */
    {
      Nm_PnSyncShutdown_Nm_To_BusNm_DataType data;
      data.PncId = PncId;
      data.Channel = NetworkHandle;
      if (NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC(&data) == SCHM_E_OK)
      {
        Retval = E_OK;
      }
      else
      {
#if (NM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO Nm.EB.Schm_BusNmSynchronizedPncShutDown_Error,1 */
        NM_DET_REPORT_ERROR(NM_SID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, NM_E_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN);
#endif
        Retval = E_NOT_OK;
      }
    }
#endif /*#if (NM_GENERICNM_USED == STD_ON)*/
#else /* #if (NM_MULTICORE_ENABLED == STD_ON) */
    Retval = NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(NetworkHandle,PncId);
#endif /* #if (NM_MULTICORE_ENABLED == STD_ON) */
#else  /*#if (NM_BUSNM_NUM == 1) */
#if (NM_MULTICORE_ENABLED == STD_ON)
#if ((NM_CANNM_USED == STD_ON) || (NM_FRNM_USED == STD_ON) || (NM_UDPNM_USED == STD_ON))
  if (NM_CHANNEL_CONFIG(NetworkHandle).IsGenericBus == FALSE)
  {
    Nm_PnSyncShutdown_Nm_To_BusNm_DataType data;
    data.PncId = PncId;
    data.Channel = NetworkHandle;
    if (NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC(NetworkHandle, &data) == SCHM_E_OK)
    {
      Retval = E_OK;
    }
    else
    {
#if (NM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Nm.EB.Schm_BusNmSynchronizedPncShutDown_Error,1 */
      NM_DET_REPORT_ERROR(NM_SID_REQUESTSYNCHRONIZEDPNCSHUTDOWN, NM_E_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN);
#endif
      Retval = E_NOT_OK;
    }
  }
#endif /*#if ((NM_CANNM_USED == STD_ON) || (NM_FRNM_USED == STD_ON) || (NM_UDPNM_USED == STD_ON))*/
#if (NM_GENERICNM_USED == STD_ON)
  if (NM_CHANNEL_CONFIG(NetworkHandle).IsGenericBus == TRUE)
  {
    Retval = NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(NetworkHandle,PncId);
  }
#endif /*#if (NM_GENERICNM_USED == STD_ON) */
#else /* #if (NM_MULTICORE_ENABLED == STD_ON) */
  Retval = NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(NetworkHandle,PncId);
#endif /* #if (NM_MULTICORE_ENABLED == STD_ON) */
#endif /*#if (NM_BUSNM_NUM == 1) */
  }

  DBG_NM_REQUESTSYNCHRONIZEDPNCSHUTDOWN_EXIT(Retval,NetworkHandle,PncId);
  return Retval;
}
#endif /* (NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED == STD_ON) */


#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/*==================[internal function definitions]==========================*/

/*------------------[Nm_CoordinatedShutdownHandler]--------------------------*/
STATIC FUNC(void, NM_CODE) Nm_CoordinatedShutdownHandler
(
  uint8 ccIdx
)
{
  uint8_least ccNwHandleLookupIdx;

  /* assertion: function is only called for channels being a part of a
   * coordinated cluster */

  /* Enter critical section: this is needed to protect the global variables
   * Nm_CoordShutdownPreconOk[] and Nm_CcState[], because
   * Nm_CoordinatedShutdownHandler() is called from the main function and from
   * API functions and read and sets these global variables */
  SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

  /* check and store shutdown precondition */
  /* !LINKSTO Nm.SWS_Nm_00002,1, Nm.SWS_Nm_00003,1 */
  Nm_CoordShutdownPreconOk[ccIdx]= TRUE;

  /*  for all networks in the coordination cluster */
  for (ccNwHandleLookupIdx = 0U;
       ccNwHandleLookupIdx < Nm_CcNmChannelsNum[ccIdx];
       ccNwHandleLookupIdx++)
  {
    const NetworkHandleType NetworkHandle
      = Nm_CcNmChannels[ccIdx][ccNwHandleLookupIdx];

    /* Only consider networks which are participating in the cluster; for these, check
     * - that the remote nodes are inactive for a cluster which is not a sleep master(e.g. LIN bus).
     * - the channel is not requested by ComM */
    /* !LINKSTO Nm.SWS_Nm_00228,1 */
    if ( (NM_IS_CHANNEL (NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
         &&
         (
           (
           (NM_IS_NOT_CHANNEL(NetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE))
            &&
            (NM_CHANNEL_CONFIG(NetworkHandle).NmChannelSleepMaster == FALSE)
           )
           ||
           (NM_IS_CHANNEL (NetworkHandle, NM_CHANNEL_REQUESTED_BY_COMM))
         )
       )
    {
      Nm_CoordShutdownPreconOk[ccIdx] = FALSE;
      break;
    }
  }
  if (Nm_CoordShutdownPreconOk[ccIdx])
  {
    /* If shutdown is not already started or synchronization point is not already reached */
    if (((Nm_CcState[ccIdx] != NM_CC_STATE_SHUTDOWN_INITIATED) &&
         (Nm_CcState[ccIdx] != NM_CC_STATE_WAIT_SYNCHRONIZATION)
        ) &&
        (Nm_CcState[ccIdx] != NM_CC_STATE_PREPARE_SHUTDOWN)
       )
    {
      if (Nm_IsSynchronizationRequired(ccIdx) == TRUE)
      {
        Nm_CcState[ccIdx] = NM_CC_STATE_WAIT_SYNCHRONIZATION;
      }
      else
      {
        /* switch main funtion state to prepare for shutdown */
        Nm_CcState[ccIdx] = NM_CC_STATE_PREPARE_SHUTDOWN;
      }
    }
  }
  else
  {
    /* Shutdown precondition are not met */
    /* switch main function state to wait for the shutdown conditions to become
     * true again */
    Nm_CcState[ccIdx] = NM_CC_STATE_WAIT_FOR_SHUTDOWN;
  }

  SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
}

/*------------------[Nm_AbortShutdown]---------------------------------------*/
STATIC FUNC(void, NM_CODE) Nm_AbortShutdown
(
  NetworkHandleType nmNetworkHandle, boolean allChannels
)
{
  uint8_least ccNwHandleLookupIdx;
  Nm_ModeType Mode;
  Nm_StateType nmState;
  const uint8 CoordClusterIndex = NM_CHANNEL_CONFIG(nmNetworkHandle).CoordClusterIndex;

  /* Function is called from main function, API and callback API functions and
   * reads and writes global variables: watch out for reentrancy problems! */

  /* If network is part of a cc */
  if (NM_CC_IDX_INVALID != CoordClusterIndex)
  {
    /* Variable to memorize if an initiated shutdown was aborted or not */
    const uint8 ChannelId = Nm_ChanIdxFromNetworkHandle[nmNetworkHandle];
    boolean InitiatedShutdownAborted = FALSE;

    /* Enter critical section to protect global variables */
    SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
    /* If for a channel AbortShutdown is called stop channel specific timer */
    /* !LINKSTO Nm.EB.ASR40.BusOff.NmWaitForShutdownTime_Timer_Stop2,1 */
    Nm_WaitForShutdownTimer[ChannelId] = 0U;

    /* precondition is not met any more, reset global cluster shutdown precondition state */
    Nm_CoordShutdownPreconOk[CoordClusterIndex] = FALSE;

    switch(Nm_CcState[CoordClusterIndex])
    {
        case NM_CC_STATE_PREPARE_SHUTDOWN:
        {
          /* if a shutdown was prepared before (not started) just reset the state
           * back to NM_CC_STATE_WAIT_FOR_SHUTDOWN, in this case no real shutdown
           * actions were performed before */
          Nm_CcState[CoordClusterIndex] = NM_CC_STATE_WAIT_FOR_SHUTDOWN;
          break;
        }
        case NM_CC_STATE_SHUTDOWN_INITIATED:
        case NM_CC_STATE_WAIT_SYNCHRONIZATION:
        {
          /* !LINKSTO Nm.SWS_Nm_00185,1 */
          Nm_CcState[CoordClusterIndex] = NM_CC_STATE_SHUTDOWN_ABORTED;
          InitiatedShutdownAborted = TRUE;
          break;
        }
        default:
        {
          break;
        }
    }

    /* Exit critical section */
    SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();

    /* If an initiated shutdown is aborted, make sure all NMs in cluster get back in sync */
    if (InitiatedShutdownAborted)
    {
      /* for all networks in cluster*/
      for (ccNwHandleLookupIdx = 0U;
           ccNwHandleLookupIdx < Nm_CcNmChannelsNum[CoordClusterIndex];
           ccNwHandleLookupIdx++)
      {
        const NetworkHandleType actNmNetworkHandle =
          Nm_CcNmChannels[CoordClusterIndex][ccNwHandleLookupIdx];

        /* Check if channels slept in erroneously;
         * do not consider the "own" channel unless called from Nm_RemoteSleepCancellation,
         * Nm_NetworkMode.
         * If called from Nm_RemoteSleepCancelation, the network may have been released and
         * RemoteSleepCancelation may have been indicated in ReadySleepState of the NM, so
         * requesting the network again is required.
         * If called from Nm_NetworkMode, the network may have been released and some remote
         * node may have started to send again in PrepareBusSleepState of the NM, where no
         * RemoteSleepCancelation is reported anymore, but the network needs to be requested
         * again just like in the RemoteSleepCancelation case.
         * Also only consider networks that were requested by ComM, i.e. are active in the
         * coordinated cluster */

        if (NM_IS_CHANNEL (actNmNetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER)
            &&
            (allChannels || (actNmNetworkHandle != nmNetworkHandle))
           )
        {
          const Std_ReturnType result
            = NM_BUSNM_GET_STATE(actNmNetworkHandle, &nmState, &Mode);

          if ((result == E_OK) && (Mode == NM_MODE_BUS_SLEEP))
          {
            /* !LINKSTO Nm.SWS_Nm_00182,1 */
            /* If the shutdown is aborted, NM Coordinator shall call
             * ComM_Nm_RestartIndication() for all networks that already
             * indicated 'bus sleep'. */
            ComM_Nm_RestartIndication(actNmNetworkHandle);
          }
          else
          {
            /* !LINKSTO Nm.SWS_Nm_00177,1, Nm.SWS_Nm_00183,1 */
            /*
             * Here we interpret "not indicated 'bus sleep'" also to be true
             * for the case that BusNm_GetState() returns an error. */
            (void)Nm_NetworkRequestInternal(actNmNetworkHandle,
                                            NM_SID_ABORTSHUTDOWN,
                                            NM_E_NETWORKREQUEST);
          }
        } /* if participating in cluster */
      } /* for ccNwHandleLookupIdx */
    } /* if (InitiatedShutdownAborted) */
  } /* if (NM_CC_IDX_INVALID != CoordClusterIndex) */
}

/*------------------[Nm_IsSynchronizationRequired]---------------------------------------*/
STATIC FUNC(boolean, NM_CODE) Nm_IsSynchronizationRequired
(
  uint8 ccIdx
)
{
  boolean SynchNetworkPresent = FALSE;
  NetworkHandleType NetworkHandle=0U;
  uint8_least ccNwHandleLookupIdx;

  /* for all networks in the coordination cluster */
  for (ccNwHandleLookupIdx = 0U;
       ccNwHandleLookupIdx < Nm_CcNmChannelsNum[ccIdx];
       ccNwHandleLookupIdx++)
  {
    NetworkHandle = Nm_CcNmChannels[ccIdx][ccNwHandleLookupIdx];

    if (NM_CHANNEL_CONFIG(NetworkHandle).NmSynchronizingNetwork == TRUE)
    {
      /* There is one synchronizing network in the cluster */
      SynchNetworkPresent = TRUE;
      break;
    }
  }

  if (SynchNetworkPresent == TRUE)
  {
    /* Only consider networks which are participating in the cluster */
    if (NM_IS_NOT_CHANNEL (NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER))
    {
      SynchNetworkPresent = FALSE;
    }
  }

  return (SynchNetworkPresent);
}
#endif /* #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/*------------------[Nm_CarWakeUpIndication]--------------------------------------*/
/* !LINKSTO Nm.ECUC_Nm_00235,1 */
#if (NM_CAR_WAKEUPRX_INDICATION == STD_ON)
/* !LINKSTO Nm.SWS_Nm_00250,1, Nm.SWS_Nm_00251,1 */
FUNC(void, NM_CODE) Nm_CarWakeUpIndication
(
  NetworkHandleType  nmChannelHandle
)
{

  DBG_NM_CARWAKEUPINDICATION_ENTRY(nmChannelHandle);

 #if (NM_DEV_ERROR_DETECT == STD_ON)
  if (Nm_Initialized == FALSE)
  {
    NM_DET_REPORT_ERROR(NM_SID_CARWAKEUPINDICATION, NM_E_UNINIT);
  }
  else if (NM_IS_NETWORK_HANDLE_INVALID(nmChannelHandle))
  {
    /* !LINKSTO Nm.ASR403.SWS_Nm_00233,1 */
    NM_DET_REPORT_ERROR(NM_SID_CARWAKEUPINDICATION, NM_E_HANDLE_UNDEF);
  }
  else
#endif
  {
    NM_NM_CAR_WAKEUP_CALLBACK(nmChannelHandle);
  }
  DBG_NM_CARWAKEUPINDICATION_EXIT(nmChannelHandle);
}
#endif

#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
STATIC FUNC(void, NM_CODE) Nm_HandleBusOff
(
  uint8 ccIdx
)
{
  uint8             ChannelId;
  uint8_least       ccNwHandleLookupIdx;
  boolean           Nm_WaitForShutdownTimerExpired = FALSE;
  boolean           Nm_SynchronizingTimerExpired = FALSE;
  NetworkHandleType NetworkHandle;
  Nm_StateType      nmState;
  Nm_ModeType       nmMode;

  for (ccNwHandleLookupIdx = 0U;
       ccNwHandleLookupIdx < Nm_CcNmChannelsNum[ccIdx];
       ccNwHandleLookupIdx++
      )
  {
    NetworkHandle = Nm_CcNmChannels[ccIdx][ccNwHandleLookupIdx];
    ChannelId = Nm_ChanIdxFromNetworkHandle[NetworkHandle];
    if(NM_CHANNEL_CONFIG(NetworkHandle).WaitForShutdownTime > 0U)
    {
      (void)NM_BUSNM_GET_STATE(NetworkHandle, &nmState, &nmMode);
      SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
      /* !LINKSTO Nm.EB.ASR40.BusOff.SynchronizeState,1, Nm.EB.ASR40.BusOff.BusSleepState,1 */
      if ((NM_IS_CHANNEL(NetworkHandle, NM_CHANNEL_PARTICIPATING_IN_CLUSTER)) &&
          (((nmState == NM_STATE_SYNCHRONIZE) ||
            (nmState == NM_STATE_BUS_SLEEP))))
      {
        if (Nm_WaitForShutdownTimer[ChannelId] > 0U)
        {
          Nm_WaitForShutdownTimer[ChannelId]--;
          if (Nm_WaitForShutdownTimer[ChannelId] == 0U)
          {
            /* !LINKSTO Nm.EB.ASR40.BusOff.NmWaitForShutdownTime_Timer_Expired_1,1 */
            NM_SET_CHANNEL (NetworkHandle, NM_CHANNEL_REMOTE_NODES_INACTIVE);
            Nm_WaitForShutdownTimerExpired = TRUE;
            if (NM_CHANNEL_CONFIG(NetworkHandle).NmSynchronizingNetwork == TRUE)
            {
              Nm_SynchronizingTimerExpired = TRUE;
            }
          }
        }
        else
        {
          Nm_WaitForShutdownTimer[ChannelId] = \
             NM_CHANNEL_CONFIG(NetworkHandle).WaitForShutdownTime;
        }
      }
      else
      {
        /* !LINKSTO Nm.EB.ASR40.BusOff.NmWaitForShutdownTime_Timer_Stop1,1 */
        Nm_WaitForShutdownTimer[ChannelId] = 0U;
      }
      SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
    }
  }

  if (Nm_WaitForShutdownTimerExpired == TRUE)
  {
    Nm_CoordinatedShutdownHandler(ccIdx);
  }

  SchM_Enter_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
  if (Nm_SynchronizingTimerExpired == TRUE)
  {
    /* !LINKSTO Nm.EB.ASR40.BusOff.NmWaitForShutdownTime_Timer_Expired_2,1 */
    if (Nm_CcState[ccIdx] == NM_CC_STATE_WAIT_SYNCHRONIZATION)
    {
      Nm_CcState[ccIdx] = NM_CC_STATE_PREPARE_SHUTDOWN;
    }
  }
  SchM_Exit_Nm_SCHM_NM_EXCLUSIVE_AREA_0();
}

#endif /* #if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

#if ((NM_PASSIVE_MODE_ENABLED == STD_OFF)               \
  && ((NM_DEV_ERROR_DETECT == STD_ON)                   \
    || (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)))
STATIC FUNC(Std_ReturnType, NM_CODE) Nm_NetworkRequestInternal
(
  NetworkHandleType NetworkHandle,
  uint8  ApiId,
  uint8  ErrorId
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (NM_MULTICORE_ENABLED == STD_OFF)
  RetVal = NM_BUSNM_NETWORK_REQUEST(NetworkHandle);
  TS_PARAM_UNUSED(ApiId);
  TS_PARAM_UNUSED(ErrorId);
#else
  if (NM_BUSNM_NETWORK_REQUEST(NetworkHandle) == SCHM_E_OK)
  {
    RetVal = E_OK;
  }
  else
  {
#if (NM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO Nm.EB.SchM_Call_DET,1 */
    NM_DET_REPORT_ERROR(ApiId, ErrorId);
#else
    TS_PARAM_UNUSED(ApiId);
    TS_PARAM_UNUSED(ErrorId);
#endif
  }
#endif
  return RetVal;
}

STATIC FUNC(Std_ReturnType, NM_CODE) Nm_NetworkReleaseInternal
(
  NetworkHandleType NetworkHandle,
  uint8  ApiId,
  uint8  ErrorId
)
{
  Std_ReturnType RetVal = E_NOT_OK;
#if (NM_MULTICORE_ENABLED == STD_OFF)
  RetVal = NM_BUSNM_NETWORK_RELEASE(NetworkHandle);
  TS_PARAM_UNUSED(ApiId);
  TS_PARAM_UNUSED(ErrorId);
#else
  if (NM_BUSNM_NETWORK_RELEASE(NetworkHandle) == SCHM_E_OK)
  {
    RetVal = E_OK;
  }
  else
  {
#if (NM_DEV_ERROR_DETECT == STD_ON)
    /* !LINKSTO Nm.EB.SchM_Call_DET,1 */
    NM_DET_REPORT_ERROR(ApiId, ErrorId);
#else
    TS_PARAM_UNUSED(ApiId);
    TS_PARAM_UNUSED(ErrorId);
#endif
  }
#endif
  return RetVal;
}

#endif

/* CHECK: NOPARSE */
/* No parse have been added because
 * (Nm_Dummy_ComMContext function has been added with the support for multi core)
 * when modelling the cross core function calls (Schm_Call) context is required
 * for modelling the calling context.
 * The Nm_Dummy_ComMContext is called from an interrupt context which cannot be modelled
 * in Rte therefore a dummy context has been added.
 * Rte generates a function declaration, here an empty function definitions
 * is provided
 */
#if (NM_MULTICORE_ENABLED == STD_ON)
FUNC(void, NM_CODE) Nm_Dummy_ComMContext (void)
{

}
#endif
/* CHECK: PARSE */

#if ( ((NM_BUSNM_NUM > 1U)                        ||                    \
       (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) ||                    \
       (NM_STATE_REPORT_ENABLED == STD_ON)        ||                    \
       (NM_CHANNEL_NUM > 1U)) && (NM_MULTICORE_USE_SINGLE_CS == STD_ON) \
    )
FUNC(Std_ReturnType, NM_CODE) Nm_MultipleNetworkOperations
(
  NetworkHandleType nmNetworkHandle,
  uint8 operation
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  if (operation == NM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP)
  {
    /* !LINKSTO Nm.EB.NmMultiCoreUseSingleCS_PassiveStartup,1 */
#if (NM_GENERICNM_USED == STD_ON)
    if (Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].MultipleNetworkOperations == NULL_PTR)
    {
      RetVal = Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].PassiveStartUp(nmNetworkHandle);
    }
    else
#endif
    {
      RetVal = Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].MultipleNetworkOperations(nmNetworkHandle,operation);
    }
  }
#if (NM_PASSIVE_MODE_ENABLED == STD_OFF)
  else
  if (operation == NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST)
  {
    /* !LINKSTO Nm.EB.NmMultiCoreUseSingleCS_NetworkRequest,1 */
#if (NM_GENERICNM_USED == STD_ON)
    if (Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].MultipleNetworkOperations == NULL_PTR)
    {
      RetVal = Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].NetworkRequest(nmNetworkHandle);
    }
    else
#endif
    {
      RetVal = Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].MultipleNetworkOperations(nmNetworkHandle,operation);
    }
  }
  else if (operation == NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE)
  {
     /* !LINKSTO Nm.EB.NmMultiCoreUseSingleCS_NetworkRelease,1 */
#if (NM_GENERICNM_USED == STD_ON)
    if(Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].MultipleNetworkOperations == NULL_PTR)
    {
      RetVal = Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].NetworkRelease(nmNetworkHandle);
    }
    else
#endif
    {
      RetVal = Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].MultipleNetworkOperations(nmNetworkHandle,operation);
    }
  }
  else /* if (operation == NM_MULTI_CORE_USE_SINGLE_CS_GW_ERA_NETWORK_REQUEST) */
  {
    /* If GenericNmEnabled is set to true EB_NM_STACK is set to STD_OFF */
    /* !LINKSTO Nm.EB.NmMultiCoreUseSingleCS_NetworkGwEraRequest,1 */
#if (EB_NM_STACK == STD_ON)
    RetVal = Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].MultipleNetworkOperations(nmNetworkHandle,operation);
#endif /* #if (EB_NM_STACK == STD_ON) */
  }
#endif
  return RetVal;
}
#endif

#define NM_STOP_SEC_CODE
#include <Nm_MemMap.h>

/*==================[end of file]============================================*/
