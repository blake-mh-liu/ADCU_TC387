/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*================================================================================================*/

#ifndef CSM_MACVERIFY_H
#define CSM_MACVERIFY_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_MacVerifyCfg.h>

#if (CSM_MACVERIFY_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start MAC verify computation.
 **
 ** This function requests the start of an MAC verify computation. The start function of the
 ** configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId   Holds the identifier of the CSM module configuration that has to be
 **                     used during the operation.
 ** \param[in]  keyPtr  Holds a pointer to the key necessary for the MAC verification.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifyStart
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(Csm_SymKeyType,   AUTOMATIC, CSM_APPL_DATA) keyPtr
);

/** \brief  Update MAC verify computation.
 **
 ** This function requests the update of the MAC verify computation for the given data. The
 ** update function of the configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId       Holds the identifier of the CSM module configuration that has to be
 **                         used during the operation.
 ** \param[in]  dataPtr     Holds a pointer to the data for which a MAC shall be verified.
 ** \param[in]  dataLength  Contains the number of bytes for which the MAC shall be verified.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifyUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                      dataLength
);

/** \brief  Finish MAC verify computation.
 **
 ** This function requests the finishing of the MAC verify computation and the storing of the
 ** calculated checksum result in the given buffer. The finish function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in ]  cfgId      Holds the identifier of the CSM module configuration that has to be
 **                         used during the operation.
 ** \param[in ]  MacPtr     Holds a pointer to the memory location which will hold the MAC to
 **                         verify.
 ** \param[out]  MacLength  Holds the length of the MAC to be verified. Note = the computed MAC
 **                         will be internally truncated to this length.
 ** \param[out]  resultPtr  Holds a pointer to the memory location which will hold the result
 **                         of the MAC verification.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_MacVerifyFinish
(
          Csm_ConfigIdType                                cfgId,
  P2CONST(uint8,                AUTOMATIC, CSM_APPL_DATA) MacPtr,
          uint32                                          MacLength,
    P2VAR(Csm_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) resultPtr
);

/** \brief  Used by the mac verify primitive to indicate finished computation.
 **
 ** This function has to be called by the mac verify primitive to indicate that it has finished
 ** the current start, update, or finish computation. This function then calls the configured
 ** callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_MacVerifyCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the mac verify primitive to indicate end of service.
 **
 ** This function has to be called by the mac verify primitive to indicate that it has
 ** completely finished the currently computed service. This function then sets the mac verify
 ** computation state machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_MacVerifyServiceFinishNotification
(
  void
);

#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the mac verify computation tasks.
 **
 ** This function performs the actual mac verify computation tasks which have been requested by
 ** the service functions. The function calls the main function of the configured primitive to
 ** perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_MacVerifyMainFunction
(
  void
);

#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the mac verify computation interface.
 **
 ** This function initializes the mac verify computation interface such that a service can be
 ** requested with Csm_MacVerifyStart().
 **/
extern FUNC(void, CSM_CODE) Csm_MacVerifyInit
(
  void
);

#define CSM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief The run state of the service.
 **/
extern VAR(boolean, CSM_VAR) Csm_MacVerifyIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_MacVerifyCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_MacVerify_Ret_CallbackNotification;
#endif /* #if (CSM_MACVERIFY_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_MACVERIFY_ENABLED == STD_ON) */

#endif /* #ifndef CSM_MACVERIFY_H */

/*==================[end of file]=================================================================*/

