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

#ifndef CSM_CHECKSUM_H
#define CSM_CHECKSUM_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_ChecksumCfg.h>

#if (CSM_CHECKSUM_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start checksum computation.
 **
 ** This function requests the start of an checksum computation. The start function of the
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
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_ChecksumStart
(
  Csm_ConfigIdType cfgId
);

/** \brief  Update checksum computation.
 **
 ** This function requests the update of the checksum computation for the given data. The
 ** update function of the configured primitive is called and its return value is returned.
 **
 ** \param[in]  cfgId       Holds the identifier of the CSM module configuration that has to be
 **                         used during the operation.
 ** \param[in]  dataPtr     Holds a pointer to the data for which the checksum shall be
 **                         calculated.
 ** \param[in]  dataLength  Contains the length of the input data in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_ChecksumUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                      dataLength
);

/** \brief  Finish checksum computation.
 **
 ** This function requests the finishing of the checksum computation and the storing of the
 ** calculated checksum result in the given buffer. The finish function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in    ]  cfgId                Holds the identifier of the CSM module configuration
 **                                      that has to be used during the operation.
 ** \param[out   ]  resultPtr            Holds a pointer to the memory location which will hold
 **                                      the result of the checksum calculation. If the result
 **                                      does not fit into the given buffer, and truncation is
 **                                      allowed, the result shall be truncated.
 ** \param[in,out]  resultLengthPtr      Holds a pointer to the memory location in which the
 **                                      length information is stored. On calling this function
 **                                      this parameter shall contain the size of the buffer
 **                                      provided by resultPtr. When the request has finished,
 **                                      the actual length of the computed checksum shall be
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
 ** \retval  CSM_E_SMALL_BUFFER  the provided buffer is too small to store the result
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_ChecksumFinish
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32,           AUTOMATIC, CSM_APPL_DATA) resultLengthPtr,
        boolean                                     TruncationIsAllowed
);

/** \brief  Used by the checksum primitive to indicate finished computation.
 **
 ** This function has to be called by the checksum primitive to indicate that it has finished
 ** the current start, update, or finish computation. This function then calls the configured
 ** callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_ChecksumCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the checksum primitive to indicate end of service.
 **
 ** This function has to be called by the checksum primitive to indicate that it has completely
 ** finished the currently computed service. This function then sets the checksum computation
 ** state machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_ChecksumServiceFinishNotification
(
  void
);

#if (CSM_CHECKSUM_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the checksum computation tasks.
 **
 ** This function performs the actual checksum computation tasks which have been requested by
 ** the service functions. The function calls the main function of the configured primitive to
 ** perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_ChecksumMainFunction
(
  void
);

#endif /* #if (CSM_CHECKSUM_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the checksum computation interface.
 **
 ** This function initializes the checksum computation interface such that a service can be
 ** requested with Csm_ChecksumStart().
 **/
extern FUNC(void, CSM_CODE) Csm_ChecksumInit
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
extern VAR(boolean, CSM_VAR) Csm_ChecksumIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_ChecksumCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_CHECKSUM_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_Checksum_Ret_CallbackNotification;
#endif /* #if (CSM_CHECKSUM_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_CHECKSUM_ENABLED == STD_ON) */

#endif /* #ifndef CSM_CHECKSUM_H */

/*==================[end of file]=================================================================*/

