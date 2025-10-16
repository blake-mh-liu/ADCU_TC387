/**
 * \file
 *
 * \brief AUTOSAR Xcp
 *
 * This file contains the implementation of the AUTOSAR
 * module Xcp.
 *
 * \version 2.13.5
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
 * MISRAC2012-1) Deviated Rule: 8.9 (advisory)
 * An object should be defined at block scope if its identifier only appears in a single function
 *
 * Reason:
 * Using the variable at function scope would require making the variable static, which
 * would prevent allocation to a predefined memory section.
 *
 * MISRAC2012-2) Deviated Rule: 13.5 (required)
 * The right hand operand of a logical && or || operator shall not contain persistent side effects.
 *
 * Reason:
 * GetApplicationID() doesn't have any side effect.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * This warning seems to be a compiler problem. The condition is false on other module configurations.
 *
 */

[!INCLUDE "../../generate_macros/Xcp_Vars.m"!][!//
/*==================[inclusions]============================================*/

#include <Xcp_Trace.h>
#include <Std_Types.h>        /* AUTOSAR standard types */
#include <TSAutosar.h>        /* EB specific standard types */

#include <Xcp.h>              /* Module public API */
#if ( (XCP_DEFAULT_XCP_MODULE_STATE == STD_ON) || (XCP_ENABLE_XCP_CONTROL_API == STD_ON) )
#include <Xcp_Int.h>          /* Internal types */
#include <TSMem.h>            /* EB memory functions */
#include <Xcp_Cbk.h>          /* Callbacks and callouts of Xcp */

#if (XCP_RESOURCE_CAL_PAG == XCP_RESOURCE_CAL_PAG_MASK)
#include <Xcp_UserCallouts.h> /* User Callout Function declarations */
#endif

#include <SchM_Xcp.h>         /* Needed for exclusive area definition */
[!IF "$XcpBswDistributionEnabled"!][!//
[!SELECT "XcpConfig/eb-list::*[1]"!][!//
[!VAR "XcpConnectionOsAppRefNameList" = "''"!][!//
[!LOOP "(XcpConnectionCfg/eb-list::*)"!][!//
[!IF "node:existsAndTrue(../../../../XcpGeneral/XcpEventTriggerMainFunc) or node:exists(../../../../XcpGeneral/XcpSupportComMainFunctions)"!][!//
[!IF "node:existsAndFalse(../../../../XcpGeneral/XcpServiceWrapper)"!][!//
[!IF "node:exists(XcpConnectionApplicationRef)"!][!//
  [!VAR "XcpConnectionOsAppRefName"="as:name(as:ref(./XcpConnectionApplicationRef))"!][!//
  [!IF "not(contains($XcpConnectionOsAppRefNameList,concat(' ',$XcpConnectionOsAppRefName,' ')))"!][!//
#include <SchM_Xcp_1_[!"$XcpConnectionOsAppRefName"!].h>
    [!VAR "XcpConnectionOsAppRefNameList" = "concat($XcpConnectionOsAppRefNameList,' ',$XcpConnectionOsAppRefName,' ')"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDIF!][!//
/*==================[macros]================================================*/
[!AUTOSPACING!][!//
[!VAR "XcpEventChannelMFEnabled"="(node:existsAndTrue(XcpGeneral/XcpEventTriggerMainFunc)) and (node:exists(XcpConfig/eb-list::*[1]/XcpEventChannel)) and (num:i(count(XcpConfig/eb-list::*[1]/XcpEventChannel/eb-list::*)) > 0)"!]
[!VAR "EventChannelIndex" = "0"!]
[!IF "$XcpEventChannelMFEnabled"!]
  [!LOOP "XcpConfig/eb-list::*[1]/XcpEventChannel/eb-list::*"!]
    [!IF "XcpEventChannelTimeCycle > 0"!]
/** \brief The index of the Event MainFunction in the Xcp_IsMFEventCurrentlyProcessing flags */
#if (defined XCP_EVENT_MAIN_FUNCTION_[!"as:name(.)"!]_INDEX)
#error XCP_EVENT_MAIN_FUNCTION_[!"as:name(.)"!]_INDEX already defined
#endif
#define XCP_EVENT_MAIN_FUNCTION_[!"as:name(.)"!]_INDEX      [!"num:i($EventChannelIndex)"!]U
    [!VAR "EventChannelIndex" = "$EventChannelIndex + 1"!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDIF!]


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[external constants]====================================*/

/*==================[internal data]=========================================*/

#define XCP_START_SEC_VAR_INIT_8
#include <Xcp_MemMap.h>

[!VAR "XcpCrcMFEnabled"="node:existsAndTrue(XcpGeneral/XcpBuildChecksumMainFunctionSupport)"!]
[!VAR "XcpComMFEnabled"="node:exists(XcpGeneral/XcpSupportComMainFunctions)"!]

[!IF "node:existsAndTrue($XcpComMFEnabled)"!]
/* Deviation MISRAC2012-1 <START> */
/* Xcp_TxMainFunction processing status */
STATIC VAR(boolean, XCP_VAR) Xcp_TxMainFunction_Running = FALSE;
/* Xcp_RxMainFunction processing status */
STATIC VAR(boolean, XCP_VAR) Xcp_RxMainFunction_Running = FALSE;
/* Deviation MISRAC2012-1 <STOP> */
[!ENDIF!]
[!IF "node:existsAndTrue($XcpCrcMFEnabled)"!]
/* Xcp_CrcMainFunction processing status */
/* Deviation MISRAC2012-1 <START> */
STATIC VAR(boolean, XCP_VAR) Xcp_CrcMainFunction_Running = FALSE;
/* Deviation MISRAC2012-1 <STOP> */
[!ENDIF!]

/*==================[external data]=========================================*/

[!IF "$XcpEventChannelMFEnabled"!]
/** \brief Flags signaling if an Event Main Function is currently executing or not */
VAR(uint8, XCP_VAR) Xcp_IsMFEventCurrentlyProcessing[XCP_EVENT_PROCESSING_FLAG_SIZE] = {0};

/** \brief Flag to disable the execution of any event main function: triggered when
 ** an autonomous disconnect is going to happen
 **/
VAR(boolean, XCP_VAR) Xcp_EventMainFunctionsExecutionIsAllowed = TRUE;

[!ENDIF!]

#define XCP_STOP_SEC_VAR_INIT_8
#include <Xcp_MemMap.h>

/*==================[external function definitions]=========================*/

[!IF "(node:existsAndTrue($XcpEventChannelMFEnabled)) or (node:existsAndTrue($XcpCrcMFEnabled)) or (node:existsAndTrue($XcpComMFEnabled))"!]
#define XCP_START_SEC_CODE
#include <Xcp_MemMap.h>
[!ENDIF!]
[!IF "$XcpEventChannelMFEnabled"!]
  [!LOOP "XcpConfig/eb-list::*[1]/XcpEventChannel/eb-list::*"!]
    [!IF "XcpEventChannelTimeCycle > 0"!]

/*------------------[Xcp_MainFunction_EventChannel---------------------------------------*/
FUNC(void, XCP_CODE) Xcp_MainFunction_[!"as:name(.)"!](void)
{
  boolean ExecuteMainFunction = FALSE;   /* Indicates whether main function must be continued. */
#if (XCP_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Atomic_value_t activeConnectionId = Atomics_Load(&Xcp_ActiveConnectionId);
#endif
  DBG_XCP_MAINFUNCTION_[!"text:toupper(as:name(.))"!]_ENTRY();

#if (XCP_BSW_DISTRIBUTION_ENABLED == STD_ON)
  /* Deviation MISRAC2012-2 <START> */
  /* Deviation TASKING-1 <START> */
  if (
       (activeConnectionId == XCP_NO_ACTIVE_CONNECTION)
       ||
       (
         (activeConnectionId != XCP_NO_ACTIVE_CONNECTION) &&
         (Xcp_ConnectionToPartitionMap[activeConnectionId] != (uint8)GetApplicationID())
       )
     )
  /* Deviation TASKING-1 <STOP> */
  /* Deviation MISRAC2012-2 <STOP> */
  {
    return;
  }
#endif

  if (Xcp_ControlStateOfXcpModule == XCP_STATE_ACTIVE)
  {
    /* Enter critical section */
    SchM_Enter_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();

#if ((XCP_ON_FLEXRAY_ENABLED == STD_ON) && (XCP_FLEXRAY_TP_COMMANDS_SUPPORTED == STD_ON))
      /* check if the Xcp_MainFunction is already being processed */
    if ((XCP_IS_BYTE_FLAG_SET(XCP_EVENT_MAIN_FUNCTION_[!"as:name(.)"!]_INDEX,
                               Xcp_IsMFEventCurrentlyProcessing) == FALSE) &&
        (Xcp_Initialized == TRUE) &&
#if (XCP_NO_OF_CONNECTIONS > 1U)
        /* If we don't have any message on the bus or the message is different then FlexRay, we can continue */
        ((Xcp_ConnectionStatus.ConnectionId == XCP_INVALID_CONNECTION_ID) ||
         (Xcp_ConnectionCfg[Xcp_ConnectionStatus.ConnectionId].ConnectionType != XCP_CONNECTION_OVER_FLEXRAY) ||
         (XCP_IS_FLAG_BIT_SET(XCP_FLEXRAY_BUFFERS_READY_BIT, Xcp_ConnectionStatus.Flags, uint8) == TRUE)) &&
#else
        /* continue processing only when the Flexray Hardware Buffers are initialized */
        (XCP_IS_FLAG_BIT_SET(XCP_FLEXRAY_BUFFERS_READY_BIT, Xcp_ConnectionStatus.Flags, uint8) == TRUE) &&
#endif  /* (XCP_NO_OF_CONNECTIONS > 1U) */
        (Xcp_EventMainFunctionsExecutionIsAllowed == TRUE))
#else
      /* check if the Xcp_MainFunction is already being processed */
    if ((XCP_IS_BYTE_FLAG_SET(XCP_EVENT_MAIN_FUNCTION_[!"as:name(.)"!]_INDEX,
                               Xcp_IsMFEventCurrentlyProcessing) == FALSE) &&
       (Xcp_Initialized == TRUE) &&
       (Xcp_EventMainFunctionsExecutionIsAllowed == TRUE))

#endif /* ((XCP_ON_FLEXRAY_ENABLED == STD_ON) && (XCP_FLEXRAY_TP_COMMANDS_SUPPORTED == STD_ON)) */
    {
      XCP_SET_BYTE_FLAG(XCP_EVENT_MAIN_FUNCTION_[!"as:name(.)"!]_INDEX, Xcp_IsMFEventCurrentlyProcessing);
      ExecuteMainFunction = TRUE;
    }

    /* Exit critical section */
    SchM_Exit_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();

    /* Check whether XCP is initialized  and the Xcp_MainFunction_Event
     * is not already being processed */
    if (ExecuteMainFunction == TRUE)
    {
      /* Execute Receive processor */
      Xcp_ProcessReception(XCP_SID_EVENT_MAIN_FUNCTION);

#if (XCP_MAX_DAQ > 0U)
      /* Execute Event [!"as:name(.)"!] */
      Xcp_ProcessEvents([!"XcpEventChannelNumber"!]U);
#endif /* (XCP_MAX_DAQ > 0U) */

      /* Execute Transmit processor */
      Xcp_ProcessTransmit(XCP_SID_EVENT_MAIN_FUNCTION);
      DBG_XCP_MAINFUNCTION_[!"text:toupper(as:name(.))"!]_FINISHED();
    }

    /* reset the processing status of this event main function */
    XCP_CLEAR_BYTE_FLAG_ATOMIC(XCP_EVENT_MAIN_FUNCTION_[!"as:name(.)"!]_INDEX, Xcp_IsMFEventCurrentlyProcessing);

  }
  else/*(Xcp_ControlStateOfXcpModule == XCP_STATE_ACTIVE && Xcp_EventMainFunctionsExecutionIsAllowed == TRUE)*/
  {
    TS_PARAM_UNUSED(ExecuteMainFunction);
  }

  DBG_XCP_MAINFUNCTION_[!"text:toupper(as:name(.))"!]_EXIT();
}
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDIF!]

[!IF "$XcpCrcMFEnabled"!]
/*------------------[Xcp_CrcMainFunction]---------------------------------------*/
FUNC(void, XCP_CODE) Xcp_CrcMainFunction(void)
{
  boolean ExecuteMainFunction = FALSE;   /* Indicates whether main function must be continued. */

  DBG_XCP_CRCMAINFUNCTION_ENTRY();

  if (Xcp_ControlStateOfXcpModule != XCP_STATE_INACTIVE)
  {
    /* Enter critical section */
    SchM_Enter_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();
    /* check if the Xcp_MainFunction is already being processed */
    if ((Xcp_CrcMainFunction_Running == FALSE) &&
        (Xcp_Initialized == TRUE))
    {
      Xcp_CrcMainFunction_Running = TRUE;
      ExecuteMainFunction = TRUE;
    }
    /* Exit critical section */
    SchM_Exit_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();

    /* Check whether XCP is initialized  and the Xcp_TxMainFunction
     * is not already being processed */
    if (ExecuteMainFunction == TRUE)
    {
      if(Xcp_GetBuildChecksumReqStatus() == E_OK)
      {
        Xcp_CalculateCRCAsync();
      }
      /* reset the processing status of Xcp_TxMainFunction */
      Xcp_CrcMainFunction_Running = FALSE;

    }
  }
  else/*(Xcp_ControlStateOfXcpModule == XCP_STATE_INACTIVE)*/
  {
    TS_PARAM_UNUSED(ExecuteMainFunction);
  }

  DBG_XCP_CRCMAINFUNCTION_EXIT();
}
[!ENDIF!]

[!IF "node:existsAndTrue($XcpComMFEnabled)"!]
/*------------------[Xcp_TxMainFunction]---------------------------------------*/
FUNC(void,XCP_CODE) Xcp_TxMainFunction(void)
{
  boolean ExecuteMainFunction = FALSE;   /* Indicates whether main function must be continued. */
#if (XCP_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Atomic_value_t activeConnectionId = Atomics_Load(&Xcp_ActiveConnectionId);
#endif
  DBG_XCP_TXMAINFUNCTION_ENTRY();

#if (XCP_BSW_DISTRIBUTION_ENABLED == STD_ON)
  /* Deviation MISRAC2012-2 <START> */
  /* Deviation TASKING-1 <START> */
  if (
       (activeConnectionId == XCP_NO_ACTIVE_CONNECTION)
       ||
       (
         (activeConnectionId != XCP_NO_ACTIVE_CONNECTION) &&
         (Xcp_ConnectionToPartitionMap[activeConnectionId] != (uint8)GetApplicationID())
       )
     )
  /* Deviation TASKING-1 <STOP> */
  /* Deviation MISRAC2012-2 <STOP> */
  {
    return;
  }
#endif

  if (Xcp_ControlStateOfXcpModule != XCP_STATE_INACTIVE)
  {
    /* Enter critical section */
    SchM_Enter_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();
    /* check if the Xcp_MainFunction is already being processed */

#if ((XCP_ON_FLEXRAY_ENABLED == STD_ON) && (XCP_FLEXRAY_TP_COMMANDS_SUPPORTED == STD_ON))
    if ((Xcp_TxMainFunction_Running == FALSE) &&
        (Xcp_Initialized == TRUE)) &&
         /* continue processing only when the Flexray Hardware Buffers are initialized */
#if (XCP_NO_OF_CONNECTIONS > 1U)
        /* If we don't have any message on the bus or the message is different then FlexRay, we can continue */
        ((Xcp_ConnectionStatus.ConnectionId == XCP_INVALID_CONNECTION_ID) ||
         (Xcp_ConnectionCfg[Xcp_ConnectionStatus.ConnectionId].ConnectionType != XCP_CONNECTION_OVER_FLEXRAY) ||
         (XCP_IS_FLAG_BIT_SET(XCP_FLEXRAY_BUFFERS_READY_BIT, Xcp_ConnectionStatus.Flags, uint8) == TRUE))
#else
        /* continue processing only when the Flexray Hardware Buffers are initialized */
        (XCP_IS_FLAG_BIT_SET(XCP_FLEXRAY_BUFFERS_READY_BIT, Xcp_ConnectionStatus.Flags, uint8) == TRUE)
#endif /* (XCP_NO_OF_CONNECTIONS > 1U) */
#else
    if ((Xcp_TxMainFunction_Running == FALSE) &&
        (Xcp_Initialized == TRUE))
#endif /* ((XCP_ON_FLEXRAY_ENABLED == STD_ON) && (XCP_FLEXRAY_TP_COMMANDS_SUPPORTED == STD_ON)) */

    {
      Xcp_TxMainFunction_Running = TRUE;
      ExecuteMainFunction = TRUE;
    }
    /* Exit critical section */
    SchM_Exit_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();

    /* Check whether XCP is initialized  and the Xcp_TxMainFunction
     * is not already being processed */
    if (ExecuteMainFunction == TRUE)
    {
      /* Execute Transmit processor */
      Xcp_ProcessTransmit(XCP_SID_TX_MAIN_FUNCTION);

      /* reset the processing status of Xcp_TxMainFunction */
      Xcp_TxMainFunction_Running = FALSE;

      DBG_XCP_TXMAINFUNCTION_FINISHED();
    }
  }
  else/*(Xcp_ControlStateOfXcpModule == XCP_STATE_INACTIVE)*/
  {
    TS_PARAM_UNUSED(ExecuteMainFunction);
  }

  DBG_XCP_TXMAINFUNCTION_EXIT();
}

/*------------------[Xcp_RxMainFunction]---------------------------------------*/
FUNC(void,XCP_CODE) Xcp_RxMainFunction(void)
{
  boolean ExecuteMainFunction = FALSE;   /* Indicates whether main function must be continued. */

#if (XCP_BSW_DISTRIBUTION_ENABLED == STD_ON)
  Atomic_value_t activeConnectionId = Atomics_Load(&Xcp_ActiveConnectionId);
#endif
  DBG_XCP_RXMAINFUNCTION_ENTRY();

#if (XCP_BSW_DISTRIBUTION_ENABLED == STD_ON)
  /* Deviation MISRAC2012-2 <START> */
  /* Deviation TASKING-1 <START> */
  if (
       (activeConnectionId == XCP_NO_ACTIVE_CONNECTION)
       ||
       (
         (activeConnectionId != XCP_NO_ACTIVE_CONNECTION) &&
         (Xcp_ConnectionToPartitionMap[activeConnectionId] != (uint8)GetApplicationID())
       )
     )
  /* Deviation TASKING-1 <STOP> */
  /* Deviation MISRAC2012-2 <STOP> */
  {
    return;
  }
#endif

  if (Xcp_ControlStateOfXcpModule != XCP_STATE_INACTIVE)
  {
    /* Enter critical section */
    SchM_Enter_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();
    /* check if the Xcp_MainFunction is already being processed */

#if ((XCP_ON_FLEXRAY_ENABLED == STD_ON) && (XCP_FLEXRAY_TP_COMMANDS_SUPPORTED == STD_ON))
    if ((Xcp_RxMainFunction_Running == FALSE) &&
        (Xcp_Initialized == TRUE) &&
        /* continue processing only when the Flexray Hardware Buffers are initialized */
#if (XCP_NO_OF_CONNECTIONS > 1U)
        /* If we don't have any message on the bus or the message is different then FlexRay, we can continue */
        ((Xcp_ConnectionStatus.ConnectionId == XCP_INVALID_CONNECTION_ID) ||
         (Xcp_ConnectionCfg[Xcp_ConnectionStatus.ConnectionId].ConnectionType != XCP_CONNECTION_OVER_FLEXRAY) ||
         /* continue processing only when the Flexray Hardware Buffers are initialized */
         (XCP_IS_FLAG_BIT_SET(XCP_FLEXRAY_BUFFERS_READY_BIT, Xcp_ConnectionStatus.Flags, uint8) == TRUE))
#else
        /* continue processing only when the Flexray Hardware Buffers are initialized */
        (XCP_IS_FLAG_BIT_SET(XCP_FLEXRAY_BUFFERS_READY_BIT, Xcp_ConnectionStatus.Flags, uint8) == TRUE)
#endif /* (XCP_NO_OF_CONNECTIONS > 1U) */
#else
    if ((Xcp_RxMainFunction_Running == FALSE) &&
        (Xcp_Initialized == TRUE))
#endif /* ((XCP_ON_FLEXRAY_ENABLED == STD_ON) && (XCP_FLEXRAY_TP_COMMANDS_SUPPORTED == STD_ON)) */
    {
      Xcp_RxMainFunction_Running = TRUE;
      ExecuteMainFunction = TRUE;
    }
    /* Exit critical section */
    SchM_Exit_Xcp_SCHM_XCP_EXCLUSIVE_AREA_XCP_INTERNALS();

    /* Check whether XCP is initialized  and the Xcp_RxMainFunction
     * is not already being processed */
    if (ExecuteMainFunction == TRUE)
    {
      /* Execute Receive processor */
      Xcp_ProcessReception(XCP_SID_RX_MAIN_FUNCTION);

      /* reset the processing status of Xcp_TxMainFunction */
      Xcp_RxMainFunction_Running = FALSE;

      DBG_XCP_RXMAINFUNCTION_FINISHED();
    }
  }
  else/*(Xcp_ControlStateOfXcpModule == XCP_STATE_INACTIVE)*/
  {
    TS_PARAM_UNUSED(ExecuteMainFunction);
  }
  DBG_XCP_RXMAINFUNCTION_EXIT();
}
[!ENDIF!]

[!IF "(node:existsAndTrue($XcpEventChannelMFEnabled)) or (node:existsAndTrue($XcpCrcMFEnabled)) or (node:existsAndTrue($XcpComMFEnabled))"!]
#define XCP_STOP_SEC_CODE
#include <Xcp_MemMap.h>
[!ENDIF!]

[!IF "$XcpBswDistributionEnabled"!][!//
[!SELECT "XcpConfig/eb-list::*[1]"!][!//

[!VAR "XcpConnectionOsAppRefNameList" = "''"!][!//
[!LOOP "(XcpConnectionCfg/eb-list::*)"!][!//
  [!IF "node:exists(XcpConnectionApplicationRef)"!][!//
  [!VAR "XcpConnectionOsAppRefName"="as:name(as:ref(./XcpConnectionApplicationRef))"!][!//
  [!IF "not(contains($XcpConnectionOsAppRefNameList,concat(' ',$XcpConnectionOsAppRefName,' ')))"!][!//

[!IF "node:existsAndTrue(../../../../XcpGeneral/XcpEventTriggerMainFunc) or node:exists(../../../../XcpGeneral/XcpSupportComMainFunctions)"!][!//
[!IF "node:existsAndFalse(../../../../XcpGeneral/XcpServiceWrapper)"!][!//
/*-------------[Xcp BSW distribution external function definitions]---------------*/
#define XCP_1_[!"$XcpConnectionOsAppRefName"!]_START_SEC_CODE
#include <Xcp_1_[!"$XcpConnectionOsAppRefName"!]_MemMap.h>
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "node:existsAndTrue(../../../../XcpGeneral/XcpEventTriggerMainFunc)"!][!//
  [!IF "(node:exists(../../XcpEventChannel)) and (num:i(count(../../XcpEventChannel/eb-list::*)) > 0)"!][!//
    [!LOOP "../../XcpEventChannel/eb-list::*"!][!//
      [!IF "./XcpEventChannelTimeCycle > 0"!][!//
        [!IF "node:existsAndFalse(../../../../XcpGeneral/XcpServiceWrapper)"!][!//
FUNC(void, XCP_1_[!"$XcpConnectionOsAppRefName"!]_CODE) Xcp_1_[!"$XcpConnectionOsAppRefName"!]_MainFunction_[!"as:name(.)"!](void)
{
  Xcp_MainFunction_[!"as:name(.)"!]();
}
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDIF!][!//

[!IF "node:exists(../../../../XcpGeneral/XcpSupportComMainFunctions)"!][!//
  [!IF "node:existsAndFalse(../../../../XcpGeneral/XcpServiceWrapper)"!][!//
FUNC(void, XCP_1_[!"$XcpConnectionOsAppRefName"!]_CODE) Xcp_1_[!"$XcpConnectionOsAppRefName"!]_RxMainFunction(void)
{
  Xcp_RxMainFunction();
}

FUNC(void, XCP_1_[!"$XcpConnectionOsAppRefName"!]_CODE) Xcp_1_[!"$XcpConnectionOsAppRefName"!]_TxMainFunction(void)
{
  Xcp_TxMainFunction();
}
  [!ENDIF!][!//
[!ENDIF!][!//

[!IF "node:existsAndTrue(../../../../XcpGeneral/XcpEventTriggerMainFunc) or node:exists(../../../../XcpGeneral/XcpSupportComMainFunctions)"!][!//
[!IF "node:existsAndFalse(../../../../XcpGeneral/XcpServiceWrapper)"!][!//
#define XCP_1_[!"$XcpConnectionOsAppRefName"!]_STOP_SEC_CODE
#include <Xcp_1_[!"$XcpConnectionOsAppRefName"!]_MemMap.h>
[!ENDIF!][!//
[!ENDIF!][!//

  [!VAR "XcpConnectionOsAppRefNameList" = "concat($XcpConnectionOsAppRefNameList,' ',$XcpConnectionOsAppRefName,' ')"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

[!ENDSELECT!][!//
[!ENDIF!][!//
/*==================[internal function definitions]=========================*/

#endif /* ( (XCP_DEFAULT_XCP_MODULE_STATE == STD_ON) || (XCP_ENABLE_XCP_CONTROL_API == STD_ON) ) */
/*==================[end of file]===========================================*/
