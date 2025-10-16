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

/*================================================================================================*/

[!AUTOSPACING!][!//
[!SELECT "as:modconf('SaSrv')"!][!//

/*==================[includes]====================================================================*/

#include <SaSrv_DSD_Cfg.h>
#include <SaSrv_DSD.h>
#include <Rte_SaSrv.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define SaSrv_START_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/** \brief Array holding the configuration data for each configured security access level. */
CONST(SaSrv_DSD_SecurityLevelCfgType, SaSrv_CONST) SaSrv_DSD_SecurityLevelCfg[SASRV_NO_SECURITY_LEVELS] =
{
[!LOOP "SaSrvSecurityLevelConfig/*"!]
  [!VAR "SecurityLevelConfigName" = "node:name(.)"!]
  /* Security access level config [!"$SecurityLevelConfigName"!] */
  {
    /* Security access level */
    [!"num:i(node:value(node:ref(./SaSrvSecurityLevelRef)/DcmDspSecurityLevel))"!]U,
  },
[!ENDLOOP!]
};

#define SaSrv_STOP_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

[!LOOP "SaSrvSecurityLevelConfig/*"!][!//
[!VAR "Level" = "num:i(node:value(node:ref(./SaSrvSecurityLevelRef)/DcmDspSecurityLevel))"!]
[!VAR "Indentation" = "string-length(node:name(.))"!]

/**
 * \brief The GetSeed operation for security access level [!"$Level"!].
 *
 * \param[in]  OpStatus                 Operation status (optional, only if the security access
 *                                      level use ASYNCH_CLIENT_SERVER approach).
 * \param[out] Seed                     Generated seed
 * \param[out] ErrorCode                Negative response error code.
 *
 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_SecurityAccess_[!"node:name(.)"!]_GetSeed
(
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Seed,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode
)
{
  return SaSrv_DSD_GetSeed(
                           OpStatus,
                           Seed,
                           ErrorCode,
                           [!"$Level"!]U
                          );
}

/**
 * \brief The CompareKey operation for security access level [!"$Level"!].
 *
 * \param[in]  Key       The key to compare
 * \param[in]  OpStatus  Operation status (optional, only if the security access level
 *                       use ASYNCH_CLIENT_SERVER approach).
 * \param[out] ErrorCode Negative response error code.
 *
 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_SecurityAccess_[!"node:name(.)"!]_CompareKey
(
  P2CONST(uint8,                              AUTOMATIC, SaSrv_APPL_DATA) Key,
          SaSrv_Dcm_OpStatusType                                          OpStatus,
    P2VAR(SaSrv_Dcm_NegativeResponseCodeType, AUTOMATIC, SaSrv_APPL_DATA) ErrorCode
)
{
  return SaSrv_DSD_CompareKey(
                              Key,
                              OpStatus,
                              ErrorCode,
                              [!"$Level"!]U
                             );
}

/**
 * \brief The GetSecurityAttemptCounter operation for security access level [!"$Level"!].
 *
 * \param[in]  OpStatus       Operation status (optional, only if the security access level
 *                            use ASYNCH_CLIENT_SERVER approach).
 * \param[out] AttemptCounter The attempt counter value.
 *
 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_SecurityAccess_[!"node:name(.)"!]_GetSecurityAttemptCounter
(
        SaSrv_Dcm_OpStatusType             OpStatus,
  P2VAR(uint8, AUTOMATIC, SaSrv_APPL_DATA) AttemptCounter
)
{
  return SaSrv_DSD_GetSecurityAttemptCounter(
                                             OpStatus,
                                             AttemptCounter,
                                             [!"$Level"!]U
                                            );
}

/**
 * \brief The SetSecurityAttemptCounter operation for security access level [!"$Level"!].
 *
 * \param[in] OpStatus        Operation status (optional, only if the security access level
 *                            use ASYNCH_CLIENT_SERVER approach).
 * \param[in] AttemptCounter  The attempt counter value.
 *
 */
FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_SecurityAccess_[!"node:name(.)"!]_SetSecurityAttemptCounter
(
  SaSrv_Dcm_OpStatusType OpStatus,
  uint8                  AttemptCounter
)
{
  return SaSrv_DSD_SetSecurityAttemptCounter(
                                             OpStatus,
                                             AttemptCounter,
                                             [!"$Level"!]U
                                            );
}

[!ENDLOOP!][!//

[!IF "SaSrvGeneral/SaSrvHandleEntropy = 'true'"!][!//
/**
 * \brief This function initialize the module and handles the random generate service entropy
 */
FUNC(void, SaSrv_CODE) SaSrv_Init
(
  void
)
{
  SaSrv_DSD_Init();
}

/**
 * \brief This function sets the module to a not initialized state
 */
FUNC(void, SaSrv_CODE) SaSrv_DeInit
(
  void
)
{
  SaSrv_DSD_DeInit();
}
[!ENDIF!][!//

/* !LINKSTO swdd.MainFunction, 1 */
/**
 * \brief The SetSecurityAttemptCounter operation for security access level [!"$Level"!].
 *
 * \param[in] OpStatus        Operation status (optional, only if the security access level
 *                            use ASYNCH_CLIENT_SERVER approach).
 * \param[in] AttemptCounter  The attempt counter value.
 *
 */
FUNC(void, SaSrv_CODE) SaSrv_MainFunction
(
  void
)
{
  SaSrv_DSD_MainFunction();
}

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/
[!ENDSELECT!][!//
