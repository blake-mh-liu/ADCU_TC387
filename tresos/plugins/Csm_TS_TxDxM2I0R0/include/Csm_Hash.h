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

#ifndef CSM_HASH_H
#define CSM_HASH_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_HashCfg.h>

#if (CSM_HASH_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start hash computation.
 **
 ** This function requests the start of an hash computation. The start function of the
 ** configured primitive is called and its return value is returned.
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
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_HashStart
(
  Csm_ConfigIdType cfgId
);

/** \brief  Update hash computation.
 **
 ** This function requests the update of the hash computation for the given data. The update
 ** function of the configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId       Holds the identifier of the CSM module configuration that has to be
 **                         used during the operation.
 ** \param[in]  dataPtr     Holds a pointer to the data to be hashed.
 ** \param[in]  dataLength  Contains the number of bytes to be hashed.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_HashUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                      dataLength
);

/** \brief  Finish hash computation.
 **
 ** This function requests the finishing of the hash computation and the storing of the
 ** calculated checksum result in the given buffer. The finish function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in    ]  cfgId                Holds the identifier of the CSM module configuration
 **                                      that has to be used during the operation.
 ** \param[out   ]  resultPtr            Holds a pointer to the memory location which will hold
 **                                      the result of the hash value computation. If the
 **                                      result does not fit into the given buffer, and
 **                                      truncation is allowed, the result shall be truncated.
 ** \param[in,out]  resultLengthPtr      Holds a pointer to the memory location in which the
 **                                      length information is stored. On calling this function
 **                                      this parameter shall contain the size of the buffer
 **                                      provided by resultPtr. When the request has finished,
 **                                      the actual length of the returned value shall be
 **                                      stored.
 ** \param[in    ]  TruncationIsAllowed  This parameter states whether a truncation of the
 **                                      result is allowed or not. TRUE = truncation is
 **                                      allowed. FALSE = truncation is not allowed.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK            request successful
 ** \retval  CSM_E_NOT_OK        request failed
 ** \retval  CSM_E_BUSY          request failed, service is still busy
 ** \retval  CSM_E_SMALL_BUFFER  the provided buffer is too small to store the result, and
 **                              truncation was not allowed.
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_HashFinish
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) resultLengthPtr,
        boolean                                     TruncationIsAllowed
);

/** \brief  Algorithm identifier of hash primitive
 **
 ** This function returns the algorithm identifier of the hash primitive defined in the given
 ** configuration. See RFC 3279 for examples.
 **
 ** \param[in ]  cfgId                 Holds the identifier of the CSM module configuration
 **                                    that has to be used during the operation.
 ** \param[out]  AlgorithmIdLengthPtr  A pointer to a variable where the actual length of the
 **                                    algorithm identifier is stored.
 **
 ** \returns  A pointer to the ID of the algorithm.
 **/
extern FUNC_P2CONST(uint8, AUTOMATIC, CSM_CODE) Csm_HashAlgorithmId
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) AlgorithmIdLengthPtr
);

/** \brief  Used by the hash primitive to indicate finished computation.
 **
 ** This function has to be called by the hash primitive to indicate that it has finished the
 ** current start, update, or finish computation. This function then calls the configured
 ** callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_HashCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the hash primitive to indicate end of service.
 **
 ** This function has to be called by the hash primitive to indicate that it has completely
 ** finished the currently computed service. This function then sets the hash computation state
 ** machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_HashServiceFinishNotification
(
  void
);

#if (CSM_HASH_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the hash computation tasks.
 **
 ** This function performs the actual hash computation tasks which have been requested by the
 ** service functions. The function calls the main function of the configured primitive to
 ** perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_HashMainFunction
(
  void
);

#endif /* #if (CSM_HASH_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the hash computation interface.
 **
 ** This function initializes the hash computation interface such that a service can be
 ** requested with Csm_HashStart().
 **/
extern FUNC(void, CSM_CODE) Csm_HashInit
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
extern VAR(boolean, CSM_VAR) Csm_HashIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_HashCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_HASH_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_Hash_Ret_CallbackNotification;
#endif /* #if (CSM_HASH_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_HASH_ENABLED == STD_ON) */

#endif /* #ifndef CSM_HASH_H */

/*==================[end of file]=================================================================*/

