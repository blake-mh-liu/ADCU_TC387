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

#ifndef CSM_RANDOMGENERATE_H
#define CSM_RANDOMGENERATE_H

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_RandomGenerateCfg.h>

#if (CSM_RANDOMGENERATE_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <MemMap.h>

/** \brief  Process random generate computation.
 **
 ** tbd
 **
 ** \param[in ]  cfgId         Holds the identifier of the CSM module configuration that has to
 **                            be used during the operation.
 ** \param[out]  resultPtr     Holds a pointer to the memory location which will hold the
 **                            result of the random number generation. The memory location must
 **                            have at least the size 'resultLength'.
 ** \param[in ]  resultLength  Holds the amount of random bytes which should be generated.
 **
 ** \returns  Error value.
 **
 ** \retval  CSM_E_OK                  request successful
 ** \retval  CSM_E_NOT_OK              request failed
 ** \retval  CSM_E_BUSY                request failed, service is still busy
 ** \retval  CSM_E_ENTROPY_EXHAUSTION  request failed, entropy of randum number generator is
 **                                    exhausted
 **/
extern FUNC(Csm_ReturnType, CSM_CODE) Csm_RandomGenerate
(
        Csm_ConfigIdType                            cfgId,
  P2VAR(uint8,            AUTOMATIC, CSM_APPL_DATA) resultPtr,
        uint32                                      resultLength
);

/** \brief  Used by the random generate primitive to indicate finished computation.
 **
 ** This function has to be called by the random generate primitive to indicate that it has
 ** finished the current start, update, or finish computation. This function then calls the
 ** configured callback function to inform the user.
 **
 ** \param[out]  result  The error code of the computation. This value will be passed through to
 **                      the user.
 **/
extern FUNC(void, CSM_CODE) Csm_RandomGenerateCallbackNotification
(
  Csm_ReturnType result
);

/** \brief  Used by the random generate primitive to indicate end of service.
 **
 ** This function has to be called by the random generate primitive to indicate that it has
 ** completely finished the currently computed service. This function then sets the random
 ** generate computation state machine to the idle state.
 **/
extern FUNC(void, CSM_CODE) Csm_RandomGenerateServiceFinishNotification
(
  void
);

#if (CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED == STD_OFF)

/** \brief  Perform the random generate computation tasks.
 **
 ** This function performs the actual random generate computation tasks which have been
 ** requested by the service functions. The function calls the main function of the configured
 ** primitive to perform the tasks.
 **/
extern FUNC(void, CSM_CODE) Csm_RandomGenerateMainFunction
(
  void
);

#endif /* #if (CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED == STD_OFF) */

/** \brief  Initialization of the random generate computation interface.
 **
 ** This function initializes the random generate computation interface such that a service can
 ** be requested with Csm_RandomGenerateStart().
 **/
extern FUNC(void, CSM_CODE) Csm_RandomGenerateInit
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
extern VAR(boolean, CSM_VAR) Csm_RandomGenerateIsRunning;

#define CSM_STOP_SEC_VAR_INIT_BOOLEAN
#include <MemMap.h>

#define CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0696, 1
 */
/** \brief Id of the current configuration.
 **/
extern VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_RandomGenerateCurrentConfigId;

/** \brief Synchronous mode callback notification return value
 **/
#if (CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED == STD_ON)
extern volatile VAR(Csm_ReturnType, CSM_VAR) Csm_RandomGenerate_Ret_CallbackNotification;
#endif /* #if (CSM_RANDOMGENERATE_SYNCJOBPROCESSING_ENABLED == STD_ON) */

#define CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*================================================================================================*/

#endif /* #if (CSM_RANDOMGENERATE_ENABLED == STD_ON) */

#endif /* #ifndef CSM_RANDOMGENERATE_H */

/*==================[end of file]=================================================================*/

