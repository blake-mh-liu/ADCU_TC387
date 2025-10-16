/**
 * \file
 *
 * \brief AUTOSAR J1939Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Nm.
 *
 * \version 1.1.13
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef J1939NM_H
#define J1939NM_H

/*==================[includes]===============================================*/
#include <J1939Nm_Cfg.h>          /* Generated module configuration */
#include <J1939Nm_PBcfg.h>        /* Generated Post Build module configuration */
#include <J1939Nm_Lcfg.h>
#include <J1939Nm_Version.h>      /* Generate versioninfo */
/* !LINKSTO EB_Ref.SWS_J1939Nm_00001.1,1*/
#include <J1939Nm_Types.h>

/*==================[macros]=================================================*/

#if (defined DEFAULT_CHANGE_STATE)
#error DEFAULT_CHANGE_STATE already defined
#endif
/** \brief of Default change state of J1939Nm */
#define DEFAULT_CHANGE_STATE            0U


/*------------------[error codes]--------------------------------------------*/

#if (defined J1939NM_E_UNINIT)
#error J1939NM_E_UNINIT already defined
#endif
/** \brief Error Code.
 **
 ** API was called while the module was uninitialized. */
#define J1939NM_E_UNINIT                0x01U

#if (defined J1939NM_E_REINIT)
#error J1939NM_E_REINIT already defined
#endif
/** \brief Error Code.
 **
 ** The Init API was called twice. */
#define J1939NM_E_REINIT                0x02U

#if (defined J1939NM_E_INIT_FAILED)
#error J1939NM_E_INIT_FAILED already defined
#endif
/** \brief Error Code.
 **
 ** Invalid Initialization. */
#define J1939NM_E_INIT_FAILED           0x03U

#if (defined J1939NM_E_PARAM_POINTER)
#error J1939NM_E_PARAM_POINTER already defined
#endif
/** \brief Error Code.
 **
 ** API service was called with a NULL pointer. */
#define J1939NM_E_PARAM_POINTER         0x04U

#if (defined J1939NM_E_INVALID_PDU_SDU_ID)
#error J1939NM_E_INVALID_PDU_SDU_ID already defined
#endif
/** \brief Error Code.
 **
 ** API service was called with a wrong ID. */
#define J1939NM_E_INVALID_PDU_SDU_ID    0x05U

#if (defined J1939NM_E_INVALID_NETWORK_ID)
#error J1939NM_E_INVALID_NETWORK_ID already defined
#endif
/** \brief Error Code.
 **
 ** API service was called with wrong network handle. */
#define J1939NM_E_INVALID_NETWORK_ID    0x06U

#if (defined J1939NM_E_INVALID_PGN)
#error J1939NM_E_INVALID_PGN already defined
#endif
/** \brief Error Code.
 **
 ** API was called with an unsupported PGN. */
#define J1939NM_E_INVALID_PGN           0x07U

#if (defined J1939NM_E_INVALID_PRIO)
#error J1939NM_E_INVALID_PRIO already defined
#endif
/** \brief Error Code.
 **
 ** API was called with an illegal priority. */
#define J1939NM_E_INVALID_PRIO          0x08U

#if (defined J1939NM_E_INVALID_ADDRESS)
#error J1939NM_E_INVALID_ADDRESS already defined
#endif
/** \brief Error Code.
 **
 ** API was called with an illegal node address. */
#define J1939NM_E_INVALID_ADDRESS       0x09U

#if (defined J1939NM_E_INVALID_NODE)
#error J1939NM_E_INVALID_NODE already defined
#endif
/** \brief Error Code.
 **
 ** API was called with an illegal node ID. */
#define J1939NM_E_INVALID_NODE          0x10U


#if (defined J1939NM_E_INVALID_METADATA_HANDLE)
#error J1939NM_E_INVALID_METADATA_HANDLE already defined
#endif
/** \brief Error Code.
 **
 ** API was called with an invalid Metadata handle. */
#define J1939NM_E_INVALID_METADATA_HANDLE          0x0AU

#if (defined J1939NM_E_INVALID_PDU_SDULENGTH)
#error J1939NM_E_INVALID_PDU_SDULENGTH already defined
#endif
/** \brief Error Code.
 **
 ** API was called with an invalid Pdu Sdu length. */
#define J1939NM_E_INVALID_PDU_SDULENGTH          0x0BU
/* brief Definition of DET error code J1939NM_E_INVALID_CALL */
#if (defined J1939NM_E_INVALID_CALL)
#error J1939NM_E_INVALID_CALL already defined!
#endif /* #if (defined J1939NM_E_INVALID_CALL)*/
#define J1939NM_E_INVALID_CALL 0xFF /** Invalid call for this dummy function */

/** \brief Defines Dummy API id of function J1939Nm_SetUserData(). */
#if (defined J1939NM_SETUSERDATA)
#error J1939NM_SETUSERDATA already defined!
#endif /* #if (defined J1939NM_SETUSERDATA)*/
#define J1939NM_SETUSERDATA 0xFA

/** \brief Defines Dummy API id of function J1939Nm_GetUserData(). */
#if (defined J1939NM_GETUSERDATA)
#error J1939NM_GETUSERDATA already defined!
#endif /* #if (defined J1939NM_GETUSERDATA)*/
#define J1939NM_GETUSERDATA 0xFB

/** \brief Defines Dummy API id of function J1939Nm_GetPduData(). */
#if (defined J1939NM_GETPDUDATA)
#error J1939NM_GETPDUDATA already defined!
#endif /* #if (defined J1939NM_GETPDUDATA)*/
#define J1939NM_GETPDUDATA 0xFC

/** \brief Defines Dummy API id of function J1939Nm_CheckRemoteSleepIndication(). */
#if (defined J1939NM_CHECKREMOTESLEEPINDICATION)
#error J1939NM_CHECKREMOTESLEEPINDICATION already defined!
#endif /* #if (defined J1939NM_CHECKREMOTESLEEPINDICATION)*/
#define J1939NM_CHECKREMOTESLEEPINDICATION 0xFD
/*------------------[macros for service IDs]---------------------------------*/

#if (defined J1939NM_API_ID_INIT)
#error J1939NM_API_ID_INIT already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_Init(). */
#define J1939NM_API_ID_INIT                          0x01U

#if (defined J1939NM_API_ID_DEINIT)
#error J1939NM_API_ID_DEINIT already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_DeInit(). */
#define J1939NM_API_ID_DEINIT                        0x02U

#if (defined J1939NM_API_ID_GETVERSIONINFO)
#error J1939NM_API_ID_GETVERSIONINFO already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_GetVersionInfo(). */
#define J1939NM_API_ID_GETVERSIONINFO                0x03U

#if (defined J1939NM_API_ID_NETWORKREQUEST)
#error J1939NM_API_ID_NETWORKREQUEST already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_NetworkRequest(). */
#define J1939NM_API_ID_NETWORKREQUEST                0x05U

#if (defined J1939NM_API_ID_NETWORKRELEASE)
#error J1939NM_API_ID_NETWORKRELEASE already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_NetworkRelease(). */
#define J1939NM_API_ID_NETWORKRELEASE                0x06U

#if (defined J1939NM_API_ID_GETSTATE)
#error J1939NM_API_ID_GETSTATE already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_GetState(). */
#define J1939NM_API_ID_GETSTATE                      0x0DU

#if (defined J1939NM_API_ID_PASSIVESTARTUP)
#error J1939NM_API_ID_PASSIVESTARTUP already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_PassiveStartUp(). */
#define J1939NM_API_ID_PASSIVESTARTUP                0x0FU

#if (defined J1939NM_API_ID_GETBUSOFFDELAY)
#error J1939NM_API_ID_GETBUSOFFDELAY already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_GetBusOffDelay(). */
#define J1939NM_API_ID_GETBUSOFFDELAY                0x14U

/* Callouts */

#if (defined J1939NM_API_ID_RXINDICATION)
#error J1939NM_API_ID_RXINDICATION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_RxIndication(). */
#define J1939NM_API_ID_RXINDICATION                 0x42U

#if (defined J1939NM_API_ID_TXCONFIRMATION)
#error J1939NM_API_ID_TXCONFIRMATION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_TxConfirmation(). */
#define J1939NM_API_ID_TXCONFIRMATION               0x40U

#if (defined J1939NM_API_ID_REQUESTINDICATION)
#error J1939NM_API_ID_REQUESTINDICATION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_TxConfirmation(). */
#define J1939NM_API_ID_REQUESTINDICATION            0x43U

/* Scheduled Functions */

#if (defined J1939NM_API_ID_MAINFUNCTION)
#error J1939NM_API_ID_MAINFUNCTION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for J1939Nm_MainFunction(). */
#define J1939NM_API_ID_MAINFUNCTION                 0x04U


#if (defined J1939NM_INSTANCE_ID)
#error J1939NM_INSTANCE_ID already defined
#endif
/** \brief Instance identifier on 8bit.*/
#define J1939NM_INSTANCE_ID (0U)


/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/* Functions prototypes */
#define J1939NM_START_SEC_CODE
#include <J1939Nm_MemMap.h>

#if (J1939NM_VERSION_INFO_API == STD_ON)

/** \brief Return the modules version information
 **
 ** This function provides the information to module vendor ID, module ID and
 ** software version major.minor.patch
 **
 ** Precondition: ::J1939NM_VERSION_INFO_API = ::STD_ON
 **
 ** \param[out]  VersionInfo     Pointer to where to store the version
 **                              information of this module.
 **
 ** \ServiceID{::J1939NM_API_ID_GETVERSIONINFO}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void,J1939NM_CODE) J1939Nm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939NM_APPL_DATA) versioninfo);

#endif /* (J1939NM_VERSION_INFO_API == STD_ON) */

/*---------------[Interface ECU State Manager <--> J1939Nm]---------------------*/

/** \brief Initializes the XCP.
 **
 ** This function initializes interfaces and variables of the AUTOSAR J1939Nm
 ** module.
 **
 ** Precondition: None.
 **
 ** \param[in]  configPtr  Pointer to a selected configuration structure.
 **
 ** \ServiceID{::J1939NM_API_ID_INIT}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, J1939NM_CODE) J1939Nm_Init(P2CONST(J1939Nm_ConfigType, AUTOMATIC, J1939NM_APPL_CONST) configPtr);

/** \brief Uninitializes the J1939Nm.
 **
 ** This function Uninitializes interfaces and variables of the AUTOSAR J1939Nm
 ** module.
 **
 ** Precondition: None.
 **
 ** \param[in]  configPtr  Pointer to a selected configuration structure.
 **
 ** \ServiceID{::J1939NM_API_ID_DEINIT}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, J1939NM_CODE) J1939Nm_DeInit(void);

extern FUNC(Std_ReturnType,J1939NM_CODE) J1939Nm_NetworkRequest
(
  VAR(NetworkHandleType, AUTOMATIC) nmChannelHandle
);

extern FUNC(Std_ReturnType,J1939NM_CODE) J1939Nm_NetworkRelease
(
  VAR(NetworkHandleType, AUTOMATIC) nmChannelHandle
);

extern FUNC(Std_ReturnType,J1939NM_CODE) J1939Nm_GetState
(
  VAR(NetworkHandleType, J1939NM_VAR) NetworkHandle,
  P2VAR(Nm_StateType, AUTOMATIC, J1939NM_APPL_DATA) nmStatePtr,
  P2VAR(Nm_ModeType, AUTOMATIC, J1939NM_APPL_DATA) nmModePtr
);

extern FUNC(void,J1939NM_CODE) J1939Nm_GetBusOffDelay
(
  VAR(NetworkHandleType, AUTOMATIC) network,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) delayCyclesPtr
);

extern FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_PassiveStartUp
(
  VAR(NetworkHandleType, J1939NM_VAR) nmChannelHandle
);

extern FUNC(void,J1939NM_CODE) J1939Nm_MainFunction(void);

/*==================[Dummy functions]=========================*/
/* these functions are expected in Nm interface,
 * so they were added only for compilation
 * and are not expected to be called
 */
extern FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_SetUserData
(
  VAR(NetworkHandleType, AUTOMATIC) NetworkHandle,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) nmUserDataPtr
);

extern FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetUserData
(
  VAR(NetworkHandleType, AUTOMATIC) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) nmUserDataPtr
);

extern FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_GetPduData
(
  VAR(NetworkHandleType, AUTOMATIC) NetworkHandle,
  P2VAR(uint8, AUTOMATIC, J1939NM_APPL_DATA) nmPduData
);

extern FUNC(Std_ReturnType, J1939NM_CODE) J1939Nm_CheckRemoteSleepIndication
(
  VAR(NetworkHandleType, AUTOMATIC) nmNetworkHandle,
  P2VAR(boolean, AUTOMATIC, J1939NM_APPL_DATA) nmRemoteSleepIndPtr
);

extern FUNC( Std_ReturnType, J1939NM_CODE) J1939Nm_IsValidConfig
(
  P2CONST(void,AUTOMATIC,J1939NM_APPL_CONST) voidConfigPtr
);

#define J1939NM_STOP_SEC_CODE
#include <J1939Nm_MemMap.h>

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

#define J1939NM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Nm_MemMap.h>

extern VAR(J1939Nm_StateType, J1939NM_VAR) J1939Nm_InitState;

#define J1939NM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <J1939Nm_MemMap.h>


#define J1939NM_START_SEC_VAR_CLEARED_8
#include <J1939Nm_MemMap.h>

extern VAR(boolean, J1939NM_VAR) J1939Nm_ProcessPendingRequestFlag[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];
extern VAR(boolean, J1939NM_VAR) J1939Nm_StartDelayFlag[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];
extern VAR(boolean, J1939NM_VAR) J1939Nm_ACLostFlag[J1939NM_NUMBER_OF_CHANNELS_MAX][J1939NM_NUMBER_OF_NODES_MAX];
extern VAR(uint8, J1939NM_VAR) J1939Nm_PendingNode;
extern VAR(uint8, J1939NM_VAR) J1939Nm_PendingChannel;

#define J1939NM_STOP_SEC_VAR_CLEARED_8
#include <J1939Nm_MemMap.h>
/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef J1939NM_H */
/*==================[end of file]============================================*/

