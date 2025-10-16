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

#ifndef SASRV_DSD_CFG_H
#define SASRV_DSD_CFG_H

[!AUTOSPACING!][!//
/*==================[includes]====================================================================*/

#include <Rte_SaSrv_Type.h>

/*==================[macros]======================================================================*/

/** \brief Specifies whether Development Error Tracer (DET) is enabled for SASRV or not. */
#if (defined SASRV_DET_ENABLED)
#error SASRV_DET_ENABLED already defined
#endif
#define SASRV_DET_ENABLED                 [!//
[!IF "SaSrvGeneral/SaSrvEnableDet = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief The number of configured security access levels. */
#if (defined SASRV_NO_SECURITY_LEVELS)
#error SASRV_NO_SECURITY_LEVELS already defined
#endif
#define SASRV_NO_SECURITY_LEVELS [!"num:i(count(SaSrvSecurityLevelConfig/*))"!]U

#if (defined SASRV_RNG_SIZE)
#error SASRV_RNG_SIZE is already defined
#endif
/** \brief Random number size in bytes */
#define SASRV_RNG_SIZE         [!"node:value(as:ref(as:ref(SaSrvGeneral/SaSrvRandomGenerateRef)/CsmJobPrimitiveRef)/CsmRandomGenerate/CsmRandomGenerateConfig/CsmRandomGenerateResultLength)"!]U

#if (defined SASRV_MAC_SIZE)
#error SASRV_MAC_SIZE is already defined
#endif
/** \brief Random number size in bytes */
#define SASRV_MAC_SIZE         SASRV_RNG_SIZE

#if (defined SASRV_HANDLE_ENTROPY)
#error SASRV_HANDLE_ENTROPY is already defined
#endif
/** \brief Switch indicating if the entropy of the random number service is handled by SaSrv or not */
#define SASRV_HANDLE_ENTROPY    [!//
[!IF "SaSrvGeneral/SaSrvHandleEntropy = 'true'"!] STD_ON [!ELSE!] STD_OFF [!ENDIF!]

[!IF "SaSrvGeneral/SaSrvHandleEntropy = 'true'"!][!//
#if (defined SASRV_ENTROPY_SIZE)
#error SASRV_ENTROPY_SIZE is already defined
#endif
/** \brief The size of the entropy which shall be used when retriving/setting the entropy
 *         for the random generate service
 */
#define SASRV_ENTROPY_SIZE     [!"node:value(node:ref(SaSrvGeneral/RNGEntropyKeyElemReference)/CryptoKeyElementSize)"!]U
[!ENDIF!][!//

/* -------------------------- [ Start list of generic defines ] --------------------------------- */

#if (defined SASRV_ENTER_CRITICAL_SECTION)
#error SASRV_ENTER_CRITICAL_SECTION is already defined
#endif
/** \brief Enter Critical section.  **/
#define SASRV_ENTER_CRITICAL_SECTION() (void)Rte_Enter_SaSrv_ExclusiveArea()

#if (defined SASRV_EXIT_CRITICAL_SECTION)
#error SASRV_EXIT_CRITICAL_SECTION is already defined
#endif
/** \brief Exit Critical section.  **/
#define SASRV_EXIT_CRITICAL_SECTION()  (void)Rte_Exit_SaSrv_ExclusiveArea()

#if (defined SASRV_E_ENTROPY_EXHAUSTION)
#error SASRV_E_ENTROPY_EXHAUSTION is already defined
#endif
/** \brief The entropy of the random number generator is exhausted
 */
#define SASRV_E_ENTROPY_EXHAUSTION                                                               4U

/* ---------------------------- [ End list of generic defines ] --------------------------------- */

/* -------------------------------- [ DET specific defines ] ------------------------------------ */

/* define function like macro for development error reporting,
 * if development error detection is enabled */
#if (SASRV_DET_ENABLED == STD_ON)

#if (defined SASRV_DET_REPORT_ERROR)
#error SASRV_DET_REPORT_ERROR is already defined
#endif
/** \brief Macro for reporting an error to DET
 **
 ** \param[in] ServiceId Service ID of the API function
 ** \param[in] ErrorCode Error code reported to Det module */
#define SASRV_DET_REPORT_ERROR(ServiceId, ErrorCode)    \
  ((void)Rte_Call_DET_ASR43_Service_ReportError((ServiceId), (ErrorCode)))

#else

#if (defined SASRV_DET_REPORT_ERROR)
#error SASRV_DET_REPORT_ERROR is already defined
#endif
/** \brief Macro for reporting an error to DET
 **
 ** \param[in] ServiceId Service ID of the API function
 ** \param[in] ErrorCode Error code reported to Det module */
#define SASRV_DET_REPORT_ERROR(ServiceId, ErrorCode)

#endif /* (SASRV_DET_ENABLED == STD_ON) */

#if (SASRV_DET_ENABLED == STD_ON)

/* ---------------------------- [ Start list of service IDs ] ----------------------------------- */

#if (defined SASRV_SERVID_GETSEED)
#error SASRV_SERVID_GETSEED already defined
#endif
/** \brief Definition of SASRV_SERVID_GETSEED. */
#define SASRV_SERVID_GETSEED                                                                  0x01U

#if (defined SASRV_SERVID_COMPAREKEY)
#error SASRV_SERVID_COMPAREKEY already defined
#endif
/** \brief Definition of SASRV_SERVID_COMPAREKEY. */
#define SASRV_SERVID_COMPAREKEY                                                               0x02U

#if (defined SASRV_SERVID_SETSECURITYATTEMPTCOUNTER)
#error SASRV_SERVID_SETSECURITYATTEMPTCOUNTER already defined
#endif
/** \brief Definition of SASRV_SERVID_SETSECURITYATTEMPTCOUNTER. */
#define SASRV_SERVID_SETSECURITYATTEMPTCOUNTER                                                0x03U

#if (defined SASRV_SERVID_GETSECURITYATTEMPTCOUNTER)
#error SASRV_SERVID_GETSECURITYATTEMPTCOUNTER already defined
#endif
/** \brief Definition of SASRV_SERVID_GETSECURITYATTEMPTCOUNTER. */
#define SASRV_SERVID_GETSECURITYATTEMPTCOUNTER                                                0x04U

#if (defined SASRV_SERVID_RNG_GENERATION)
#error SASRV_SERVID_RNG_GENERATION already defined
#endif
/** \brief Definition of SASRV_SERVID_RNG_GENERATION. */
#define SASRV_SERVID_RNG_GENERATION                                                           0x05U

#if (defined SASRV_SERVID_MACGENERATE)
#error SASRV_SERVID_MACGENERATE already defined
#endif
/** \brief Definition of SASRV_SERVID_RNG_GENERATION. */
#define SASRV_SERVID_MACGENERATE                                                              0x06U

#if (defined SASRV_SERVID_NVM_SERVICES)
#error SASRV_SERVID_NVM_SERVICES already defined
#endif
/** \brief Definition of Det service ID used when calling the ReportError to indicate a NvM issue.
 */
#define SASRV_SERVID_NVM_SERVICES                                                             0x07U

#if (defined SASRV_SERVID_GET_ENTROPY)
#error SASRV_SERVID_GET_ENTROPY already defined
#endif
/** \brief Definition of SASRV_SERVID_GET_ENTROPY. */
#define SASRV_SERVID_GET_ENTROPY                                                              0x08U

#if (defined SASRV_SERVID_RANDOM_SEED)
#error SASRV_SERVID_RANDOM_SEED already defined
#endif
/** \brief Definition of SASRV_SERVID_RANDOM_SEED. */
#define SASRV_SERVID_RANDOM_SEED                                                              0x09U

/* ------------------------------ [ End list of service IDs ] ----------------------------------- */

/* ---------------------------- [ Start list of DET error IDs ] --------------------------------- */

#if (defined SASRV_INVALID_DATA)
#error SASRV_INVALID_DATA already defined
#endif
/** \brief Dcm called a security access API with invalid input data (e.g. undefined OpStatus value) */
#define SASRV_INVALID_DATA                                                                    0x01U

#if (defined SASRV_PARAM_POINTER)
#error SASRV_PARAM_POINTER already defined
#endif
/** \brief Dcm called a security access API with null pointer */
#define SASRV_PARAM_POINTER                                                                   0x02U

#if (defined SASRV_CRYPTO_FAILED)
#error SASRV_CRYPTO_FAILED already defined
#endif
/** \brief A call to Csm encrypt/decrypt/MAC generate/MAC verify/random generate failed */
#define SASRV_CRYPTO_FAILED                                                                   0x03U

#if (defined SASRV_RNG_ENTROPYEXHAUSTION)
#error SASRV_RNG_ENTROPYEXHAUSTION already defined
#endif
/** \brief The entropy for the Csm random number generator has exhausted */
#define SASRV_RNG_ENTROPYEXHAUSTION                                                           0x04U

#if (defined SASRV_READALL_FAILED)
#error SASRV_READALL_FAILED already defined
#endif
/** \brief The NvM_GetErrorStatus() API reports that the read all operation failed */
#define SASRV_READALL_FAILED                                                                  0x05U

#if (defined SASRV_WRITEBLOCK_FAILED)
#error SASRV_WRITEBLOCK_FAILED already defined
#endif
/** \brief The NvM_GetErrorStatus() API reports that the write block operation failed */
#define SASRV_WRITEBLOCK_FAILED                                                               0x06U

#if (defined SASRV_ENTROPY_FAILED)
#error SASRV_ENTROPY_FAILED already defined
#endif
/** \brief SaSrv was not able to retrive the entropy from the RTE call-out */
#define SASRV_ENTROPY_FAILED                                                                  0x07U

/* ------------------------------ [ End list of DET error IDs ] --------------------------------- */

#endif /* (SASRV_DET_ENABLED == STD_ON) */

#if (defined SASRV_E_COMPARE_KEY_FAILED)
#error SASRV_E_COMPARE_KEY_FAILED already defined
#endif
/** \brief The UDS value used to indicate that the comparison between client and server key failed */
#define SASRV_E_COMPARE_KEY_FAILED                                                            0x0BU

/*==================[type definitions]============================================================*/

/** \brief The required configuration information for each security access level. */
typedef struct
{
  /* !LINKSTO swdd.confData.level,1 */
  /* Security access level */
  uint8   level;
}
SaSrv_DSD_SecurityLevelCfgType;

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define SaSrv_START_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/** \brief Array holding the configuration data for each configured security access level. */
extern CONST(SaSrv_DSD_SecurityLevelCfgType, SaSrv_CONST) SaSrv_DSD_SecurityLevelCfg[SASRV_NO_SECURITY_LEVELS];

#define SaSrv_STOP_SEC_CONST_UNSPECIFIED
#include <SaSrv_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

#endif /* SASRV_DSD_CFG_H */

/*==================[end of file]=================================================================*/
