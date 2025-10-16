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

#ifndef SASRV_DSP_CFG_H
#define SASRV_DSP_CFG_H

/*==================[includes]====================================================================*/

#include <Rte_SaSrv_Type.h>

/*==================[macros]======================================================================*/

[!SELECT "as:modconf('Dcm')"!][!//
#if (defined SASRV_DSP_DCM_SECURITYACCESS_MAX_ATTEMPT_COUNTER_READOUT_TIME)
#error SASRV_DSP_DCM_SECURITYACCESS_MAX_ATTEMPT_COUNTER_READOUT_TIME already defined
#endif
/** \brief Configures the delay, in seconds, from startup, allowed for allAttemptCounter values to be obtained from the Application */
#define SASRV_DSP_DCM_SECURITYACCESS_MAX_ATTEMPT_COUNTER_READOUT_TIME [!"num:integer(num:mul(node:value(DcmConfigSet/*[1]/DcmDsp/DcmDspSecurity/DcmDspSecurityMaxAttemptCounterReadoutTime), 1000))"!]U
[!ENDSELECT!][!//

#if (defined SASRV_DSP_FIXED_VALUE_LEN)
#error SASRV_DSP_FIXED_VALUE_LEN already defined
#endif
/** \brief The length of the fixed value used in the calculate key algorithm. */
#define SASRV_DSP_FIXED_VALUE_LEN 5U

#if (defined SASRV_DSP_NO_SECURITY_LEVELS)
#error SASRV_DSP_NO_SECURITY_LEVELS already defined
#endif
/** \brief The number of configured security access levels. */
#define SASRV_DSP_NO_SECURITY_LEVELS [!"num:i(count(SaSrvSecurityLevelConfig/*))"!]U

[!IF "node:value(SaSrvGeneral/SaSrvHandleEntropy) = 'true'"!][!//
  [!VAR "KeyName" = "node:name(as:ref(as:ref(SaSrvGeneral/SaSrvRandomGenerateRef)/CsmJobKeyRef))"!][!//
#if (defined SASRV_DSP_RTE_CALL_KEYMANAGEMENT_KEYSETVALID)
#error SASRV_DSP_RTE_CALL_KEYMANAGEMENT_KEYSETVALID already defined
#endif
/** \brief The name of the RTE operation which is generating the new entropy. */
#define SASRV_DSP_RTE_CALL_KEYMANAGEMENT_KEYSETVALID Rte_Call_CsmKeyManagement_[!"$KeyName"!]_KeySetValid

#if (defined SASRV_DSP_RTE_CALL_KEYMANAGEMENT_RANDOMSEED)
#error SASRV_DSP_RTE_CALL_KEYMANAGEMENT_RANDOMSEED already defined
#endif
/** \brief The name of the RTE operation which is generating the new entropy. */
#define SASRV_DSP_RTE_CALL_KEYMANAGEMENT_RANDOMSEED Rte_Call_CsmKeyManagement_[!"$KeyName"!]_RandomSeed
[!ENDIF!][!//

#if (defined SASRV_DSP_DCM_E_PENDING)
#error SASRV_DSP_DCM_E_PENDING already defined
#endif
/** \brief Redefine pending value. */
#define SASRV_DSP_DCM_E_PENDING RTE_E_SecurityAccess_[!"node:name(SaSrvSecurityLevelConfig/*[1])"!]_DCM_E_PENDING

#if (defined SASRV_DSP_MAIN_FUNCTION_PERIOD)
#error SASRV_DSP_MAIN_FUNCTION_PERIOD already defined
#endif
/** \brief Main function period in ms. */
#define SASRV_DSP_MAIN_FUNCTION_PERIOD [!"num:i(SaSrvGeneral/SaSrvMainFunctionPeriod)"!]U


#if (defined SASRV_DSP_NR_OF_ATTEMPT_COUNTER_RETRY)
#error SASRV_DSP_NR_OF_ATTEMPT_COUNTER_RETRY already defined
#endif
/** \brief Number of attempt counter retries. */
#define SASRV_DSP_NR_OF_ATTEMPT_COUNTER_RETRY SASRV_DSP_DCM_SECURITYACCESS_MAX_ATTEMPT_COUNTER_READOUT_TIME/SASRV_DSP_MAIN_FUNCTION_PERIOD

[!SELECT "as:modconf('Dcm')"!][!//
#if (defined SASRV_DSP_NR_OF_WRITE_ATTEMPT_COUNTER_RETRY)
#error SASRV_DSP_NR_OF_WRITE_ATTEMPT_COUNTER_RETRY already defined
#endif
/** \brief Number of write attempt counter retries. */
#define SASRV_DSP_NR_OF_WRITE_ATTEMPT_COUNTER_RETRY [!"num:integer(ceiling(node:value(DcmConfigSet/*[1]/DcmDsp/DcmDspSecurity/DcmDspSecurityMaxAttemptCounterWriteTime) div node:value(DcmConfigSet/*[1]/DcmGeneral/DcmTaskTime)))"!]U
[!ENDSELECT!][!//

[!VAR "RNGKeyLen" = "node:value(as:ref(as:ref(SaSrvGeneral/SaSrvRandomGenerateRef)/CsmJobPrimitiveRef)/CsmRandomGenerate/CsmRandomGenerateConfig/CsmRandomGenerateResultLength)"!][!//
[!VAR "NoSecLevel" = "num:i(count(./SaSrvSecurityLevelConfig/*))"!]
#if (defined SASRV_DSP_INIT_BUFFER)
#error SASRV_DSP_INIT_BUFFER already defined
#endif
/** \brief Macro used for buffers initializations. */
#define SASRV_DSP_INIT_BUFFER [!//
{[!LOOP "SaSrvSecurityLevelConfig/*"!]{[!//
[!FOR "i" = "1" TO "$RNGKeyLen"!][!//
0x00U[!IF "$i < $RNGKeyLen"!], [!ENDIF!][!//
[!ENDFOR!][!//
}[!IF "@index < ($NoSecLevel - 1)"!], [!ENDIF!][!//
[!ENDLOOP!]}

/*==================[type definitions]============================================================*/

/** \brief The required configuration information for each security access level. */
typedef struct
{
  /* !LINKSTO swdd.confData.staticSeedEnable, 1 */
  /* Configuration flag to enable Static Seed */
  boolean staticSeedEnable;
  /* !LINKSTO swdd.confData.maxNumberOfFailedAttempts, 1 */
  /* Configuration variable to store number of failed attempts of SecurityAccess sequences */
  uint8   maxNumberOfFailedAttempts;
}
SaSrv_DSP_SecurityLevelCfgType;

/*==================[external function declarations]==============================================*/

#define SaSrv_START_SEC_CODE
#include <SaSrv_MemMap.h>

/**
 *  \brief Get NVM block status Service.
 *
 * Queries the write data operation status of a configured NVM block for a specific security access level.
 *
 * \param[out]   ResultPtr      Output status.
 * \param[in]    CfgId          Configuration identifier.
 * \return Standard Return Code.
 * \retval E_OK     No Error.
 * \retval E_NOT_OK operation failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_NvMService_GetErrorStatus
(
  P2VAR(uint8, AUTOMATIC, SaSrv_APPL_DATA) ResultPtr,
        uint8                              CfgId
);

/**
 *  \brief Write NVM block Service.
 *
 * Writes data to non-volatile memory of a configured NVM block for a specific security access level.
 *
 * \param[in]   DataPtr       Input data to write.
 * \param[in]   CfgId         Configuration identifier.
 * \return Standard Return Code.
 * \retval E_OK     No Error.
 * \retval E_NOT_OK operation failed.
 *
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 *
 */
extern FUNC(Std_ReturnType, SaSrv_CODE) SaSrv_DSP_NvMService_WriteBlock
(
  P2CONST(void, AUTOMATIC, SaSrv_CONST) DataPtr,
  uint8                                 CfgId
);

#define SaSrv_STOP_SEC_CODE
#include <SaSrv_MemMap.h>

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define SaSrv_START_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/** \brief Array holding the configuration data for each configured security access level. */
extern CONST(SaSrv_DSP_SecurityLevelCfgType, SaSrv_CONST) SaSrv_DSP_SecurityLevelCfg[SASRV_DSP_NO_SECURITY_LEVELS];

#define SaSrv_STOP_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

#endif /* SASRV_DSP_CFG_H */

/*==================[end of file]=================================================================*/
