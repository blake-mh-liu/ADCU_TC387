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

#ifndef CSM_SYMBLOCKDECRYPT_H
#define CSM_SYMBLOCKDECRYPT_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_SymBlockDecryptCfg.h>

#if (CSM_SYMBLOCKDECRYPT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start symmetrical block decryption computation.
 **
 ** This function requests the start of an symmetrical block decryption computation. The start
 ** function of the configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId   Holds the identifier of the CSM module configuration that has to be
 **                     used during the operation.
 ** \param[in]  keyPtr  Holds a pointer to the key which has to be used during the symmetrical
 **                     block decryption computation
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptStart
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(Csm_SymKeyType,   AUTOMATIC, CSM_APPL_DATA) keyPtr
);

/** \brief  Update symmetrical block decryption computation.
 **
 ** This function requests the update of the symmetrical block decryption computation for the
 ** given data. The update function of the configured primitive is called and its return value
 ** is returned.
 **
 ** \param[in    ]  cfgId               Holds the identifier of the CSM module configuration
 **                                     that has to be used during the operation.
 ** \param[in    ]  cipherTextPtr       Holds a pointer to the constant cipher text that shall
 **                                     be decrypted.
 ** \param[in    ]  cipherTextLength    Contains the length of the cipher text in bytes.
 ** \param[out   ]  plainTextPtr        Holds a pointer to the memory location which will hold
 **                                     the decrypted text.
 ** \param[in,out]  plainTextLengthPtr  Holds a pointer to a memory location in which the
 **                                     length information is stored. On calling this function
 **                                     this parameter shall contain the size of the buffer
 **                                     provided by plainTextPtr. When the request has
 **                                     finished, the amount of data that has been decrypted
 **                                     shall be stored.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK            request successful
 ** \retval  CSM_E_NOT_OK        request failed
 ** \retval  CSM_E_BUSY          request failed, service is still busy
 ** \retval  CSM_E_SMALL_BUFFER  the provided buffer is too small to store the result
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) cipherTextPtr,
          uint32                                      cipherTextLength,
    P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) plainTextPtr,
    P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) plainTextLengthPtr
);

/** \brief  Finish symmetrical block decryption computation.
 **
 ** This function requests the finishing of the symmetrical block decryption computation and
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
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SymBlockDecryptFinish
(
  Csm_ConfigIdType cfgId
);

/** \brief  Used by the symmetrical block decryption primitive to indicate finished computation.
 **
 ** This function has to be called by the symmetrical block decryption primitive to indicate
 ** that it has finished the current start, update, or finish computation. This function then
 ** calls the configured callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_SymBlockDecryptCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the symmetrical block decryption primitive to indicate end of service.
 **
 ** This function has to be called by the symmetrical block decryption primitive to indicate
 ** that it has completely finished the currently computed service. This function then sets the
 ** symmetrical block decryption computation state machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_SymBlockDecryptServiceFinishNotification
(
  void
);

#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the symmetrical block decryption computation tasks.
 **
 ** This function performs the actual symmetrical block decryption computation tasks which have
 ** been requested by the service functions. The function calls the main function of the
 ** configured primitive to perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_SymBlockDecryptMainFunction
(
  void
);

#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the symmetrical block decryption computation interface.
 **
 ** This function initializes the symmetrical block decryption computation interface such that
 ** a service can be requested with Csm_SymBlockDecryptStart().
 **/
extern FUNC(void, CSM_CODE) Csm_SymBlockDecryptInit
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
extern VAR(boolean, CSM_VAR) Csm_SymBlockDecryptIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_SymBlockDecryptCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_SymBlockDecrypt_Ret_CallbackNotification;
#endif /* #if (CSM_SYMBLOCKDECRYPT_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_SYMBLOCKDECRYPT_ENABLED == STD_ON) */

#endif /* #ifndef CSM_SYMBLOCKDECRYPT_H */

/*==================[end of file]=================================================================*/

