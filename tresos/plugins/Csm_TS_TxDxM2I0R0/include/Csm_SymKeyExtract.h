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

#ifndef CSM_SYMKEYEXTRACT_H
#define CSM_SYMKEYEXTRACT_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_SymKeyExtractCfg.h>

#if (CSM_SYMKEYEXTRACT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Start symmetrical key extraction computation.
 **
 ** This function requests the start of an symmetrical key extraction computation. The start
 ** function of the configured primitive is called and its return value is returned.
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
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyExtractStart
(
  Csm_ConfigIdType cfgId
);

/** \brief  Update symmetrical key extraction computation.
 **
 ** This function requests the update of the symmetrical key extraction computation for the
 ** given data. The update function of the configured primitive is called and its return value
 ** is returned.
 **
 ** \param[in]  cfgId       Holds the identifier of the CSM module configuration that has to be
 **                         used during the operation.
 ** \param[in]  dataPtr     Holds a pointer to the data which contains the key in a format
 **                         which cannot be used directly by the CSM. From this data the key
 **                         will be extracted in a CSM-conforming format.
 ** \param[in]  dataLength  Holds the length of the data in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyExtractUpdate
(
          Csm_ConfigIdType                            cfgId,
  P2CONST(uint8,            AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                      dataLength
);

/** \brief  Finish symmetrical key extraction computation.
 **
 ** This function requests the finishing of the symmetrical key extraction computation and the
 ** storing of the calculated checksum result in the given buffer. The finish function of the
 ** configured primitive is called and its return value is returned.
 **
 ** \param[in    ]  cfgId   Holds the identifier of the CSM module configuration that has to be
 **                         used during the operation.
 ** \param[in,out]  keyPtr  Holds a pointer to a structure where the result (i.e. the
 **                         symmetrical key) is stored in.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK      request successful
 ** \retval  CSM_E_NOT_OK  request failed
 ** \retval  CSM_E_BUSY    request failed, service is still busy
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_SymKeyExtractFinish
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(Csm_SymKeyType,   AUTOMATIC, CSM_APPL_DATA) keyPtr
);

/** \brief  Used by the symmetrical key extraction primitive to indicate finished computation.
 **
 ** This function has to be called by the symmetrical key extraction primitive to indicate that
 ** it has finished the current start, update, or finish computation. This function then calls
 ** the configured callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_SymKeyExtractCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the symmetrical key extraction primitive to indicate end of service.
 **
 ** This function has to be called by the symmetrical key extraction primitive to indicate that
 ** it has completely finished the currently computed service. This function then sets the
 ** symmetrical key extraction computation state machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_SymKeyExtractServiceFinishNotification
(
  void
);

#if (CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the symmetrical key extraction computation tasks.
 **
 ** This function performs the actual symmetrical key extraction computation tasks which have
 ** been requested by the service functions. The function calls the main function of the
 ** configured primitive to perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_SymKeyExtractMainFunction
(
  void
);

#endif /* #if (CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the symmetrical key extraction computation interface.
 **
 ** This function initializes the symmetrical key extraction computation interface such that a
 ** service can be requested with Csm_SymKeyExtractStart().
 **/
extern FUNC(void, CSM_CODE) Csm_SymKeyExtractInit
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
extern VAR(boolean, CSM_VAR) Csm_SymKeyExtractIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_SymKeyExtractCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_SymKeyExtract_Ret_CallbackNotification;
#endif /* #if (CSM_SYMKEYEXTRACT_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_SYMKEYEXTRACT_ENABLED == STD_ON) */

#endif /* #ifndef CSM_SYMKEYEXTRACT_H */

/*==================[end of file]=================================================================*/

