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

#ifndef SASRV_DSD_H
#define SASRV_DSD_H

/*==================[includes]====================================================================*/

#include <SaSrv_DSD_Cfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

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
 * \param[in]  Level                    Security access level.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_GetSeed
(
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Seed,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           Level
);

/**
 * \brief The CompareKey operation for security access level.
 *
 * \param[in]  Key       The key to compare.
 * \param[in]  OpStatus  Operation status (optional, only if the security access level
 *                       uses ASYNCH_CLIENT_SERVER approach).
 * \param[out] ErrorCode Negative response error code.
 * \param[in]  Level     Security access level.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_CompareKey
(
  P2CONST(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Key,
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode,
          uint8                                                           Level
);

/**
 * \brief The GetSecurityAttemptCounter operation for security access level.
 *
 * \param[in]  OpStatus       Operation status (optional, only if the security access level
 *                            uses ASYNCH_CLIENT_SERVER approach).
 * \param[out] AttemptCounter The attempt counter value.
 * \param[in]  Level          Security access level.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_SetSecurityAttemptCounter
(
  SaSrv_Dcm_OpStatusType OpStatus,
  uint8                  AttemptCounter,
  uint8                  Level
);

/**
 * \brief The SetSecurityAttemptCounter operation for security access level.
 *
 * \param[in] OpStatus        Operation status (optional, only if the security access level
 *                            uses ASYNCH_CLIENT_SERVER approach).
 * \param[in] AttemptCounter  The attempt counter value.
 * \param[in] Level           Security access level.
 *
 * \return Standard Return Code
 * \retval E_OK     No Error.
 * \retval E_NOT_OK Request failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSD_GetSecurityAttemptCounter
(
        SaSrv_Dcm_OpStatusType             OpStatus,
  P2VAR(uint8, AUTOMATIC, SaSrv_APPL_DATA) AttemptCounter,
        uint8                              Level
);

#if (SASRV_HANDLE_ENTROPY == STD_ON)
/**
 * \brief This function initialize the module and handles the random generate service entropy
 */
extern FUNC(void, SaSrv_CODE) SaSrv_DSD_Init
(
  void
);

/**
 * \brief This function sets the module to a not initialized state
 */
extern FUNC(void, SaSrv_CODE) SaSrv_DSD_DeInit
(
  void
);
#endif /* #if (SASRV_HANDLE_ENTROPY == STD_ON) */

extern FUNC(void, SaSrv_CODE) SaSrv_DSD_MainFunction
(
  void
);

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#endif /* SASRV_DSD_H */

/*==================[end of file]=================================================================*/

