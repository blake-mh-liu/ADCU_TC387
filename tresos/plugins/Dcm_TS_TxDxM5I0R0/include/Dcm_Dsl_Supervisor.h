/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Dcm.Dsn.File.Supervisor.Core.PublicApi,1 */
/* This file contains the implementation of the Supervisor Core software unit. */

#ifndef DCM_DSL_SUPERVISOR_H
#define DCM_DSL_SUPERVISOR_H
/*==================[inclusions]=================================================================*/
#include <Dcm.h>
#include <ComStack_Types.h>                        /* AUTOSAR standard types */
#include <Dcm_Dsl_CommunicationServices.h>         /* Dcm Dsl Communication Services header file */
#include <Dcm_Dsl_DiagnosticSessionHandler.h>
#include <Dcm_Dsl_CommunicationServices_RxConnections.h>
#include <Dcm_Dsl_CommunicationServices_TxConnections.h>

#if (DCM_DEV_ERROR_DETECT == STD_ON)
/* Development Error Tracer (DCM_DET_REPORT_ERROR() macros) */
#include <Det.h>
#endif
/*==================[macros]=====================================================================*/

/** @defgroup Macro_Dcm_ReceptionArbitrationResultType Macros for Dcm_ReceptionArbitrationResultType
 ** \brief    These macros are used as values for Dcm_ReceptionArbitrationResultType
 **  @{
 */
/* General reject. Don't process this/throw this away. */
#if (defined DCM_SUPERVISOR_ARBITRATION_REJECT_NO_RX)
  #error "DCM_SUPERVISOR_ARBITRATION_REJECT_NO_RX is already defined"
#endif
#define DCM_SUPERVISOR_ARBITRATION_REJECT_NO_RX 0x00U

/* Rejected because MainConnection is busy. */
#if (defined DCM_SUPERVISOR_ARBITRATION_REJECT_MAIN_CONNECTION)
  #error "DCM_SUPERVISOR_ARBITRATION_REJECT_MAIN_CONNECTION is already defined"
#endif
#define DCM_SUPERVISOR_ARBITRATION_REJECT_MAIN_CONNECTION 0x01U

/* Rejected because ComMChannel went to NoComMode. */
#if (defined DCM_SUPERVISOR_ARBITRATION_REJECT_COMMCHANNEL)
  #error "DCM_SUPERVISOR_ARBITRATION_REJECT_COMMCHANNEL is already defined"
#endif
#define DCM_SUPERVISOR_ARBITRATION_REJECT_COMMCHANNEL 0x02U

/* Rejected because of other Protocol of same type already running or presumptive
   on different stack. */
#if (defined DCM_SUPERVISOR_ARBITRATION_REJECT_SAME_PROTOCOL_TYPE)
  #error "DCM_SUPERVISOR_ARBITRATION_REJECT_SAME_PROTOCOL_TYPE is already defined"
#endif
#define DCM_SUPERVISOR_ARBITRATION_REJECT_SAME_PROTOCOL_TYPE 0x03U

/* Rejected because of priority reasons. */
#if (defined DCM_SUPERVISOR_ARBITRATION_REJECT_PRIORITY)
  #error "DCM_SUPERVISOR_ARBITRATION_REJECT_PRIORITY is already defined"
#endif
#define DCM_SUPERVISOR_ARBITRATION_REJECT_PRIORITY 0x04U

/* Accepted */
#if (defined DCM_SUPERVISOR_ARBITRATION_ACCEPT)
  #error "DCM_SUPERVISOR_ARBITRATION_ACCEPT is already defined"
#endif
#define DCM_SUPERVISOR_ARBITRATION_ACCEPT 0x06U
/* @} */
/* End of macros definitions for Dcm_ReceptionArbitrationResultType */

/** @defgroup Macro_Dcm_ProtocolGroupType Macros for Dcm_ProtocolGroupType
 ** \brief    These macros are used as values for Dcm_ProtocolGroupType
 **  @{
 */
#if (defined DCM_PROTOCOL_INVALID_GROUP)
  #error "DCM_PROTOCOL_INVALID_GROUP is already defined"
#endif
#define DCM_PROTOCOL_INVALID_GROUP 0x00U

#if (defined DCM_PROTOCOL_OBD_GROUP)
  #error "DCM_PROTOCOL_OBD_GROUP is already defined"
#endif
#define DCM_PROTOCOL_OBD_GROUP 0x01U

#if (defined DCM_PROTOCOL_UDS_GROUP)
  #error "DCM_PROTOCOL_UDS_GROUP is already defined"
#endif
#define DCM_PROTOCOL_UDS_GROUP 0x02U

/* @} */
/* End of macros definitions for Dcm_ProtocolGroupType */

/** @defgroup Macro_Dcm_SessionSwitchPermissionType Macros for
 **           Dcm_SessionSwitchPermissionType
 ** \brief    These macros are used as values for Dcm_SessionSwitchPermissionType
 **  @{
 */
/** \brief Invalid generic value */
#if (defined DCM_SUPERVISOR_SESSION_SWITCH_INVALID)
  #error "DCM_SUPERVISOR_SESSION_SWITCH_INVALID is already defined"
#endif
#define DCM_SUPERVISOR_SESSION_SWITCH_INVALID 0x00U

/** \brief Protocol stack busy, retry session switch later */
#if (defined DCM_SUPERVISOR_SESSION_SWITCH_BUSY_RETRY)
  #error "DCM_SUPERVISOR_SESSION_SWITCH_BUSY_RETRY is already defined"
#endif
#define DCM_SUPERVISOR_SESSION_SWITCH_BUSY_RETRY 0x01U

/** \brief Protocol stack busy, discard session switch (this is because the request
 ** is to switch to a non-default session and an OBD protocol is either running
 ** or is presumptive. */
#if (defined DCM_SUPERVISOR_SESSION_SWITCH_BUSY_DISCARD)
  #error "DCM_SUPERVISOR_SESSION_SWITCH_BUSY_DISCARD is already defined"
#endif
#define DCM_SUPERVISOR_SESSION_SWITCH_BUSY_DISCARD 0x02U

/** \brief Accept session switch. */
#if (defined DCM_SUPERVISOR_SESSION_SWITCH_ACCEPT)
  #error "DCM_SUPERVISOR_SESSION_SWITCH_ACCEPT is already defined"
#endif
#define DCM_SUPERVISOR_SESSION_SWITCH_ACCEPT 0x03U
/* @} */
/* End of macros definitions for Dcm_SessionSwitchPermissionType */

/*==================[type definitions]===========================================================*/

typedef uint8 Dcm_ReceptionArbitrationResultType;

typedef uint8 Dcm_ProtocolGroupType;

typedef uint8 Dcm_SupervisorProtocolRequestTypeType;

typedef uint8 Dcm_TimerIndexType;

typedef uint8 Dcm_SessionSwitchPermissionType;

/*==================[external function declarations]=============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Initializes the sub-units of the Supervisor and enqueues a session reset request
 **
 ** Calls the initialization functions of the following sub-units:
 **    - CommunicationSessionHandling
 **    - ProtocolHandling
 **    - MainConnectionHandling
 **
 ** \param  none
 ** \return none
 */
extern FUNC(void, DCM_CODE) Dcm_Dsl_Supervisor_Init(
  void
);

/** \brief Calls the MainFunction of the sub-units and resets the diagnostic session if flagged
 **
 ** Calls the MainFunction of the following sub-units:
 **    - CommunicationSessionHandling
 **    - MainConnectionHandling
 **    - ProtocolHandling
 **
 ** \param  none
 ** \return none
 */
extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_PreProcessingMainFunction(
  void
);

/** \brief Calls the MainFunction of CommunicationSessionHandling and MainConnectionHandling
 **        sub-units
 **
 ** This function is called after the execution of the DCM HSM
 **
 ** \param  none
 ** \return none
 */
extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_PostProcessingMainFunction(
  void
);

extern FUNC(void, DCM_CODE) Dcm_Dsl_Supervisor_InhibitRequestProcessing(
  void
);

extern FUNC(boolean, DCM_CODE) Dcm_Dsl_Supervisor_RequestProcessingInhibited(
  void
);

extern FUNC(void, DCM_CODE) Dcm_Dsl_Supervisor_DisinhibitRequestProcessing(
  void
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_IncomingReception(
  Dcm_BufferUserType RxConnectionId,
  Dcm_RequestTypeType RequestType
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_AnnounceIncomingApplicationDiagnosticRequest(
  Dcm_BufferUserType RxConnectionId
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_IncomingReceptionFinished(
  Dcm_BufferUserType RxConnectionId
);

extern FUNC(Dcm_BufferUserType, DCM_CODE) Dcm_Dsl_Supervisor_GetLatestExternalUDSProtocol(
  Dcm_ProtocolStackNumberType StackNumber
);

extern FUNC(boolean, DCM_CODE) Dcm_Dsl_Supervisor_CheckIfExternalUDSProtocolExist(
  void
);

#if (DCM_NUM_UDS_STACKS > 0)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_Supervisor_GetLatestExternalUDSProtocolConfig(
  Dcm_ProtocolConfigPtrType CurrentProtocolConfig,
  Dcm_ProtocolStackNumberType StackNumber
);
#endif /* #if (DCM_NUM_UDS_STACKS > 0) */

extern FUNC(Dcm_ProtocolGroupType, DCM_CODE) Dcm_Dsl_Supervisor_GetProtocolGroupTypeForProtocol(
  Dcm_ProtocolIndexType ProtocolIndex
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_P2TimerTimeout(
  Dcm_TimerIndexType TimerIndex
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_TransmissionFinished(
  Dcm_BufferUserType TxConnectionId,
  Dcm_TxResultType TransmissionResult
);

extern FUNC (Dcm_ProtocolIndexType, DCM_CODE) Dcm_Dsl_Supervisor_GetProcessingProtocolIndex(
  Dcm_BufferUserType RxConnectionId,
  Dcm_RequestOriginType RequestOrigin
);

extern FUNC (Dcm_SessionSwitchPermissionType, DCM_CODE) Dcm_Dsl_Supervisor_IsSessionClearedToSwitch(
  Dcm_SesCtrlType NewSession,
  Dcm_ProtocolIndexType ProcessingProtocolIdx
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_ProtocolFree(
  Dcm_BufferUserType ProtocolID
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_ProcessingEnd(
  Dcm_BufferUserType RxConnectionId
);

extern FUNC(Dcm_RequestTypeType, DCM_CODE) Dcm_Dsl_Supervisor_RequestRxPermission(
  Dcm_BufferUserType RxConnectionId,
  PduLengthType Length,
  Dcm_RequestOriginType RequestOrigin
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_ProcessRequest(
  Dcm_BufferUserType RxConnectionId,
  Dcm_RequestTypeType RequestType,
  Dcm_BufferType RequestBuffer
);

#if (DCM_HAS_ROE_TYPE2 == STD_ON)

extern FUNC (boolean, DCM_CODE) Dcm_Dsl_Supervisor_IsTYPE2ROEPresent(
  Dcm_ProtocolIndexType ProtocolIndex
);
#endif

extern FUNC (Dcm_SupervisorProtocolRequestTypeType, DCM_CODE) Dcm_Dsl_Supervisor_GetProtocolRequestType(
    Dcm_BufferUserType ProtocolId
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_DefaultSessionEntered(
  void
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_DumpMainConnectionsByProtocol(
  void
);

extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_DumpProtocolsAndQueues(
  void
);

/** \brief Returns the protocol index based on RxPduId and message type.
 *
 * If a Reference to a DcmDslResponseOnEvent connection is configured, the ROE processing takes
 * place on the protocol that owns the referenced ROE connection. This function returns the right
 * protocol index for the given RxPduId based on the message type whether is a NORMAL request or
 * an ROE request.
 *
 *  \param RxPduId [in]         The RxPduId of the incoming request.
 *  \param RequestOrigin [in]   The RequestOrigin of the incoming request.
 *
 *  \return Dcm_ProtocolIndexType
 */
extern FUNC(Dcm_ProtocolIndexType, DCM_CODE)   Dcm_Dsl_Supervisor_GetProtocolIndexFromRxPduIdAndRequestType(
    PduIdType RxPduId,
    Dcm_RequestOriginType RequestOrigin);

/** \brief Triggered by other units to enqueue a synchronized request of a reset to the default
 *         session
 *
 *  \param  none
 *
 *  \return none
 */
extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_EnqueueResetOfDiagnosticSession(
  void
);

#if (DCM_APPL_TXCONFIRMATION_NOTIFICATION == STD_ON)
extern FUNC (void, DCM_CODE) Dcm_Dsl_Supervisor_ApplicationTransmisionConfirmationEnqueued_SetFlag(
  const boolean ApplicationTransmisionConfirmationEnqueued
);
#endif

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* ifndef DCM_DSL_SUPERVISOR_H */
/*==================[end of file]================================================================*/
