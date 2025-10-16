/**
 * \file
 *
 * \brief AUTOSAR SaSrv
 *
 * This file contains the implementation of the AUTOSAR
 * module SaSrv.
 *
 * \version 1.2.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef SASRV_DSP_H
#define SASRV_DSP_H

/*==================[includes]====================================================================*/

#include <SaSrv_DSD_Cfg.h>
#include <SaSrv_DSP_Cfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/**
 * \struct SaSrv_DSP_SecurityLevelCtxType
 * \brief  Structure holding all context information for a given security level
 */
typedef struct
{
  /* !LINKSTO swdd.data.numberOfFalseAttemptsCounterRetries,1 */
  /** \brief The number of retries to get the false attempts */
  uint16  numberOfFalseAttemptsCounterRetries;
  /* !LINKSTO swdd.data.numberOfWriteFalseAttemptsCounterRetries,1 */
  /** \brief The number of retries to set the false attempts */
  uint16  numberOfWriteFalseAttemptsCounterRetries;
  /* !LINKSTO swdd.data.falseAttemptsCounter,1 */
  /** \brief The number of false attempts */
  uint8   falseAttemptsCounter;
  /* !LINKSTO swdd.data.falseAttemptsCounter,1 */
  /** \brief The mirror used for the number of false attempts */
  uint8   falseAttemptsCounterMirror;
  /* !LINKSTO swdd.data.readAllDone,1 */
  /** \brief Flag indicating if the error status for NvM_ReadAll() operation was processed. */
  boolean readAllDone;
  /* !LINKSTO swdd.data.staticSeedGenerated, 1 */
  /** \brief Flag indicating if the Static Seed was generated. */
  boolean staticSeedGenerated;
}
SaSrv_DSP_SecurityLevelCtxType;

/*==================[external function declarations]==============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

/**
 * \brief The GetSeed operation for security access level.
 *
 * \param[in]  OpStatus                 Operation status (optional, only if the security access
 *                                      level uses ASYNCH_CLIENT_SERVER approach).
 * \param[out] Seed                     Generated seed.
 * \param[out] ErrorCode                Negative response error code.
 * \param[in]  CfgId                    Configuration identifier.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_GetSeed
(
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Seed,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           CfgId
);

/**
 * \brief The CompareKey operation for security access level.
 *
 * \param[in]  Key       The key to compare.
 * \param[in]  OpStatus  Operation status (optional, only if the security access level
 *                       uses ASYNCH_CLIENT_SERVER approach).
 * \param[out] ErrorCode Negative response error code.
 * \param[in]  CfgId     Configuration identifier.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_CompareKey
(
  P2CONST(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Key,
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           CfgId
);

/**
 * \brief The GetSecurityAttemptCounter operation for security access level.
 *
 * \param[in]  OpStatus       Operation status (optional, only if the security access level
 *                            uses ASYNCH_CLIENT_SERVER approach).
 * \param[out] AttemptCounter The attempt counter value.
 * \param[in]  CfgId          Configuration identifier.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_SetSecurityAttemptCounter
(
  SaSrv_Dcm_OpStatusType OpStatus,
  uint8                  AttemptCounter,
  uint8                  CfgId
);

/**
 * \brief The SetSecurityAttemptCounter operation for security access level.
 *
 * \param[in] OpStatus        Operation status (optional, only if the security access level
 *                            uses ASYNCH_CLIENT_SERVER approach).
 * \param[in] AttemptCounter  The attempt counter value.
 * \param[in] CfgId           Configuration identifier.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_GetSecurityAttemptCounter
(
        SaSrv_Dcm_OpStatusType             OpStatus,
  P2VAR(uint8, AUTOMATIC, SaSrv_APPL_DATA) AttemptCounter,
        uint8                              CfgId
);

#if (SASRV_HANDLE_ENTROPY == STD_ON)
/**
 * \brief This function initialize the module and handles the random generate service entropy
 */
extern FUNC(void, SaSrv_CODE) SaSrv_DSP_Init
(
  void
);

/**
 * \brief This function sets the module to a not initialized state
 */
extern FUNC(void, SaSrv_CODE) SaSrv_DSP_DeInit
(
  void
);
#endif /* #if (SASRV_HANDLE_ENTROPY == STD_ON) */

extern FUNC(void, SaSrv_CODE) SaSrv_DSP_MainFunction
(
  void
);

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

#define SaSrv_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <SaSrv_MemMap.h>

/** \brief Context information for all security levels */
extern VAR(SaSrv_DSP_SecurityLevelCtxType, SaSrv_VAR) SaSrv_DSP_SecurityLevelCtx[SASRV_DSP_NO_SECURITY_LEVELS];

#define SaSrv_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <SaSrv_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#endif /* SASRV_DSP_H */

/*==================[end of file]=================================================================*/

