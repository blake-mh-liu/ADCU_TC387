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

#ifndef CSM_ASYMPRIVATEKEYWRAPSYM_H
#define CSM_ASYMPRIVATEKEYWRAPSYM_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_AsymPrivateKeyWrapSymCfg.h>

#if (CSM_ASYMPRIVATEKEYWRAPSYM_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start asymetric private key wrapping computation.
 **
 ** This function requests the start of an asymetric private key wrapping computation. The
 ** start function of the configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId           Holds the identifier of the CSM module configuration that has
 **                             to be used during the operation.
 ** \param[in]  keyPtr          Holds a pointer to the private key to be wrapped.
 ** \param[in]  wrappingKeyPtr  Holds a pointer to the key used for wrapping.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapSymStart
(
          Csm_ConfigIdType                                  cfgId,
  P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2CONST(Csm_SymKeyType,         AUTOMATIC, CSM_APPL_DATA) wrappingKeyPtr
);

/** \brief  Update asymetric private key wrapping computation.
 **
 ** This function requests the update of the asymetric private key wrapping computation for the
 ** given data. The update function of the configured primitive is called and its return value
 ** is returned.
 **
 ** \param[in    ]  cfgId          Holds the identifier of the CSM module configuration that
 **                                has to be used during the operation.
 ** \param[out   ]  dataPtr        Holds a pointer to the memory location which will hold the
 **                                first chunk of the result of the key wrapping. If the result
 **                                does not fit into the given buffer, the caller shall call
 **                                the service again, until '*dataLengthPtr' is equal to zero,
 **                                indicating that the complete result has been retrieved.
 ** \param[in,out]  dataLengthPtr  Holds a pointer to the memory location in which the length
 **                                information is stored. On calling this function this
 **                                parameter shall contain the size of the buffer provided by
 **                                'dataPtr'. When the request has finished, the actual length
 **                                of the computed value shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapSymUpdate
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) dataLengthPtr
);

/** \brief  Finish asymetric private key wrapping computation.
 **
 ** This function requests the finishing of the asymetric private key wrapping computation and
 ** the storing of the calculated checksum result in the given buffer. The finish function of
 ** the configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId  Holds the identifier of the CSM module configuration that has to be used
 **                    during the operation.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_AsymPrivateKeyWrapSymFinish
(
  Csm_ConfigIdType cfgId
);

/** \brief  Used by the asymetric private key wrapping primitive to indicate finished
 **         computation.
 **
 ** This function has to be called by the asymetric private key wrapping primitive to indicate
 ** that it has finished the current start, update, or finish computation. This function then
 ** calls the configured callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapSymCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the asymetric private key wrapping primitive to indicate end of service.
 **
 ** This function has to be called by the asymetric private key wrapping primitive to indicate
 ** that it has completely finished the currently computed service. This function then sets the
 ** asymetric private key wrapping computation state machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapSymServiceFinishNotification
(
  void
);

#if (CSM_ASYMPRIVATEKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the asymetric private key wrapping computation tasks.
 **
 ** This function performs the actual asymetric private key wrapping computation tasks which
 ** have been requested by the service functions. The function calls the main function of the
 ** configured primitive to perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapSymMainFunction
(
  void
);

#endif /* #if (CSM_ASYMPRIVATEKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the asymetric private key wrapping computation interface.
 **
 ** This function initializes the asymetric private key wrapping computation interface such
 ** that a service can be requested with Csm_AsymPrivateKeyWrapSymStart().
 **/
extern FUNC(void, CSM_CODE) Csm_AsymPrivateKeyWrapSymInit
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
extern VAR(boolean, CSM_VAR) Csm_AsymPrivateKeyWrapSymIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_AsymPrivateKeyWrapSymCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_ASYMPRIVATEKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_AsymPrivateKeyWrapSym_Ret_CallbackNotification;
#endif /* #if (CSM_ASYMPRIVATEKEYWRAPSYM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_ASYMPRIVATEKEYWRAPSYM_ENABLED == STD_ON) */

#endif /* #ifndef CSM_ASYMPRIVATEKEYWRAPSYM_H */

/*==================[end of file]=================================================================*/

