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

#ifndef CSM_SIGNATUREGENERATE_H
#define CSM_SIGNATUREGENERATE_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_SignatureGenerateCfg.h>

#if (CSM_SIGNATUREGENERATE_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start signature generation computation.
 **
 ** This function requests the start of an signature generation computation. The start function
 ** of the configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId   Holds the identifier of the CSM module configuration that has to be
 **                     used during the operation.
 ** \param[in]  keyPtr  Holds a pointer to the key necessary for the signature generation.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SignatureGenerateStart
(
          Csm_ConfigIdType                                  cfgId,
  P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_DATA) keyPtr
);

/** \brief  Update signature generation computation.
 **
 ** This function requests the update of the signature generation computation for the given
 ** data. The update function of the configured primitive is called and its return value is
 ** returned.
 **
 ** \param[in]  cfgId       Holds the identifier of the CSM module configuration that has to be
 **                         used during the operation.
 ** \param[in]  dataPtr     Holds a pointer to the data that shall be signed.
 ** \param[in]  dataLength  Contains the length of the data to be signed.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SignatureGenerateUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                      dataLength
);

/** \brief  Finish signature generation computation.
 **
 ** This function requests the finishing of the signature generation computation and the
 ** storing of the calculated checksum result in the given buffer. The finish function of the
 ** configured primitive is called and its return value is returned.
 **
 ** \param[in    ]  cfgId            Holds the identifier of the CSM module configuration that
 **                                  has to be used during the operation.
 ** \param[out   ]  resultPtr        Holds a pointer to the memory location which will hold the
 **                                  result of the signature generation.
 ** \param[in,out]  resultLengthPtr  Holds a pointer to the memory location in which the length
 **                                  information is stored. On calling this function this
 **                                  parameter shall contain the size of the buffer provided by
 **                                  resultPtr. When the request has finished, the actual
 **                                  length of the computed signature shall be stored
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK            request successful
 ** \retval  CSM_E_NOT_OK        request failed
 ** \retval  CSM_E_BUSY          request failed, service is still busy
 ** \retval  CSM_E_SMALL_BUFFER  the provided buffer is too small to store the result
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SignatureGenerateFinish
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

/** \brief  Used by the signature generation primitive to indicate finished computation.
 **
 ** This function has to be called by the signature generation primitive to indicate that it
 ** has finished the current start, update, or finish computation. This function then calls the
 ** configured callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_SignatureGenerateCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the signature generation primitive to indicate end of service.
 **
 ** This function has to be called by the signature generation primitive to indicate that it
 ** has completely finished the currently computed service. This function then sets the
 ** signature generation computation state machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_SignatureGenerateServiceFinishNotification
(
  void
);

#if (CSM_SIGNATUREGENERATE_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the signature generation computation tasks.
 **
 ** This function performs the actual signature generation computation tasks which have been
 ** requested by the service functions. The function calls the main function of the configured
 ** primitive to perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_SignatureGenerateMainFunction
(
  void
);

#endif /* #if (CSM_SIGNATUREGENERATE_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the signature generation computation interface.
 **
 ** This function initializes the signature generation computation interface such that a
 ** service can be requested with Csm_SignatureGenerateStart().
 **/
extern FUNC(void, CSM_CODE) Csm_SignatureGenerateInit
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
extern VAR(boolean, CSM_VAR) Csm_SignatureGenerateIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_SignatureGenerateCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_SIGNATUREGENERATE_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_SignatureGenerate_Ret_CallbackNotification;
#endif /* #if (CSM_SIGNATUREGENERATE_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_SIGNATUREGENERATE_ENABLED == STD_ON) */

#endif /* #ifndef CSM_SIGNATUREGENERATE_H */

/*==================[end of file]=================================================================*/

