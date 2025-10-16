/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef DCM_AUTHENTICATION_CFG_H
#define DCM_AUTHENTICATION_CFG_H

/* !LINKSTO Dcm.Dsn.File.Authentication.ConfigH,1 */

/*==================[includes]===================================================================*/

[!AUTOSPACING!]
#include <Std_Types.h>
[!INCLUDE "../include/Dcm_common.m"!]
/*==================[macros]=====================================================================*/

/** @defgroup Macro_Dcm_AuthenticationConfigurationType Macros for 
 **           Dcm_AuthenticationConfigurationType
 ** \brief   These macros are used as values for Dcm_AuthenticationConfigurationType
 **  @{
 */
/** \brief Authentication not configured */
#if (defined DCM_AUTHENTICATION_CONFIGURATION_NONE)
  #error "DCM_AUTHENTICATION_CONFIGURATION_NONE is already defined"
#endif
#define DCM_AUTHENTICATION_CONFIGURATION_NONE 0x00U

/** \brief Authentication with PKI Certificate Exchange (APCE) */
#if (defined DCM_AUTHENTICATION_CONFIGURATION_APCE)
  #error "DCM_AUTHENTICATION_CONFIGURATION_APCE is already defined"
#endif
#define DCM_AUTHENTICATION_CONFIGURATION_APCE 0x02U

/** \brief Authentication with Challenge-Response (ACR) and Asymmetric Cryptography  */
#if (defined DCM_AUTHENTICATION_CONFIGURATION_ACRAC)
  #error "DCM_AUTHENTICATION_CONFIGURATION_ACRAC is already defined"
#endif
#define DCM_AUTHENTICATION_CONFIGURATION_ACRAC 0x03U

/** \brief Authentication with Challenge-Response (ACR) and Symmetric Cryptography  */
#if (defined DCM_AUTHENTICATION_CONFIGURATION_ACRSC)
  #error "DCM_AUTHENTICATION_CONFIGURATION_ACRSC is already defined"
#endif
#define DCM_AUTHENTICATION_CONFIGURATION_ACRSC 0x04U

/* @} */
/* End of macros definitions for Dcm_AuthenticationConfigurationType */ 

#if (defined DCM_AUTHENTICATION_CONFIGURATION) /* To prevent double declaration */
#error DCM_AUTHENTICATION_CONFIGURATION already defined
#endif /* if (defined DCM_AUTHENTICATION_CONFIGURATION) */
/** \brief Configured authentication type */
#define DCM_AUTHENTICATION_CONFIGURATION                   [!//
[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication)"!]
DCM_AUTHENTICATION_CONFIGURATION_APCE
[!ELSE!][!//
DCM_AUTHENTICATION_CONFIGURATION_NONE
[!ENDIF!]

#if (defined DCM_DSP_USE_SERVICE_0X29 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X29  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X29 ) */
/** \brief Defines whether UDS service 0x29 is configured */
#define DCM_DSP_USE_SERVICE_0X29           [!"$DCM_DSP_USE_SERVICE_0X29"!]

#if (defined DCM_0X29_0X00_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X29_0X00_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X29_0X00_SSVC_ENABLED ) */

/** \brief Subservice 0x00 for 0x29 enabled or not */
#define DCM_0X29_0X00_SSVC_ENABLED           [!//
[!IF "node:exists(DcmConfigSet/eb-list::*/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId='41']/eb-list::*/eb-list::*[DcmDsdSubServiceId='0' and not(node:exists(DcmDsdSubServiceFnc))])"!]
STD_ON
[!ELSE!][!//
STD_OFF
[!ENDIF!]

#if (defined DCM_0X29_0X01_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X29_0X01_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X29_0X01_SSVC_ENABLED ) */

/** \brief Subservice 0x01 for 0x29 enabled or not */
#define DCM_0X29_0X01_SSVC_ENABLED           [!//
[!IF "node:exists(DcmConfigSet/eb-list::*/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId='41']/eb-list::*/eb-list::*[DcmDsdSubServiceId='1' and not(node:exists(DcmDsdSubServiceFnc))])"!]
STD_ON
[!ELSE!][!//
STD_OFF
[!ENDIF!]

#if (defined DCM_0X29_0X02_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X29_0X02_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X29_0X02_SSVC_ENABLED ) */

/** \brief Subservice 0x02 for 0x29 enabled or not */
#define DCM_0X29_0X02_SSVC_ENABLED           [!"$DCM_0X29_0X02_SSVC_ENABLED"!]

#if (defined DCM_0X29_0X03_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X29_0X03_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X29_0X03_SSVC_ENABLED ) */

/** \brief Subservice 0x03 for 0x29 enabled or not */
#define DCM_0X29_0X03_SSVC_ENABLED           [!//
[!IF "node:exists(DcmConfigSet/eb-list::*/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId='41']/eb-list::*/eb-list::*[DcmDsdSubServiceId='3' and not(node:exists(DcmDsdSubServiceFnc))])"!]
STD_ON
[!ELSE!][!//
STD_OFF
[!ENDIF!]

#if (defined DCM_0X29_0X08_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X29_0X08_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X29_0X08_SSVC_ENABLED ) */

/** \brief Subservice 0x08 for 0x29 enabled or not */
#define DCM_0X29_0X08_SSVC_ENABLED           [!//
[!IF "node:exists(DcmConfigSet/eb-list::*/DcmDsd/DcmDsdServiceTable/eb-list::*/DcmDsdService/eb-list::*[DcmDsdSidTabServiceId='41']/eb-list::*/eb-list::*[DcmDsdSubServiceId='8' and not(node:exists(DcmDsdSubServiceFnc))])"!]
STD_ON
[!ELSE!][!//
STD_OFF
[!ENDIF!]

/** \brief Defines whether authentication connection container contains at least one entry */
#define DCM_AUTHENTICATION_CONNECTION                      [!"$DCM_AUTHENTICATION_CONNECTION"!]

/** \brief Defines whether Authentication default session timeout is used */
#define DCM_AUTHENTICATION_IDLECONNECTIONTIMER           [!"$DCM_AUTHENTICATION_IDLECONNECTIONTIMER"!]

[!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
#if (defined DCM_NUM_AUTHENTICATION_CONNECTIONS) /* To prevent double declaration */
#error DCM_NUM_AUTHENTICATION_CONNECTIONS already defined
#endif /* if (defined DCM_NUM_AUTHENTICATION_CONNECTIONS) */
/** \brief The number of authentication connections */
#define DCM_NUM_AUTHENTICATION_CONNECTIONS                 [!//
[!"num:i(count(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationConnection/eb-list::*))"!]U

#if (defined DCM_DSP_AUTHENTICATION_ROLE_SIZE) /* To prevent double declaration */
#error DCM_DSP_AUTHENTICATION_ROLE_SIZE already defined
#endif /* if (defined DCM_DSP_AUTHENTICATION_ROLE_SIZE) */
/** \brief Size of authentication role
 **
 ** The the size in bytes used in both, certificates and ECU internal static role configuration
 */
[!VAR "AuthenticationRoleSize" = "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationRoleSize"!]
#define DCM_DSP_AUTHENTICATION_ROLE_SIZE                   [!"$AuthenticationRoleSize"!]U

#if (defined DCM_MAX_CHALLENGE_LENGTH) /* To prevent double declaration */
#error DCM_MAX_CHALLENGE_LENGTH already defined
#endif /* if (defined DCM_MAX_CHALLENGE_LENGTH) */
/** \brief Maximum length of ECU challenge */
#define DCM_MAX_CHALLENGE_LENGTH                           [!//
[!"num:max(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationConnection/eb-list::*/DcmDspAuthenticationEcuChallengeLength)"!]U

[!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
#if (defined DCM_NUM_SIGNATUREGENERATE_JOBS) /* To prevent double declaration */
#error DCM_NUM_SIGNATUREGENERATE_JOBS already defined
#endif /* if (defined DCM_NUM_SIGNATUREGENERATE_JOBS) */
/** \brief Number of SignatureGenerate jobs */
[!VAR "SignaturegenerateJobNum" = "num:i(count(util:distinct(node:refs(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationConnection/eb-list::*/DcmDspAuthenticationClientChallengeSignJobRef))))"!]
#define DCM_NUM_SIGNATUREGENERATE_JOBS                     [!"$SignaturegenerateJobNum"!]U

#if (defined DCM_SIGNEDCHALLENGEBUFFER_SIZE) /* To prevent double declaration */
#error DCM_SIGNEDCHALLENGEBUFFER_SIZE already defined
#endif /* if (defined DCM_SIGNEDCHALLENGEBUFFER_SIZE) */
/** \brief Size of the buffer for signed challenge */
#define DCM_SIGNEDCHALLENGEBUFFER_SIZE                     [!//
[!"num:i(num:sum(node:foreach(node:paths(util:distinct(node:refs(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationConnection/eb-list::*/DcmDspAuthenticationClientChallengeSignJobRef))/CsmJobPrimitiveRef), "XPath", "as:ref(node:ref($XPath))/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateResultLength")))"!]U
[!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED

#if (defined AUTHENTICATION_GENERAL_NRC_MODERULE) /* To prevent double declaration */
#error AUTHENTICATION_GENERAL_NRC_MODERULE already defined
#endif /* if (defined AUTHENTICATION_GENERAL_NRC_MODERULE) */
/** \brief Defines whether Authentication General NRC mode rule is used */
#define AUTHENTICATION_GENERAL_NRC_MODERULE                [!"$AUTHENTICATION_GENERAL_NRC_MODERULE"!][!//

[!IF "node:exists(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationGeneralNRC)"!]
#if (defined DCM_DSP_AUTHENTICATION_GENERAL_NRC) /* To prevent double declaration */
#error DCM_DSP_AUTHENTICATION_GENERAL_NRC already defined
#endif /* if (defined DCM_DSP_AUTHENTICATION_GENERAL_NRC) */
/** \brief General NRC value */
#define DCM_DSP_AUTHENTICATION_GENERAL_NRC                 [!//
[!"num:inttohex(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationGeneralNRC, 2)"!]U
[!ENDIF!]

#define DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT         [!"$DCM_MODEDECLARATION_SUPPORT"!]

/** \brief Crypto stack is compatible with Autosar versions before R20-11 */
#if (defined DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
  #error "DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11 is already defined"
#endif
#define DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11 0x00U

/** \brief Crypto stack is compatible with Autosar versions R20/R21-11 */
#if (defined DCM_AUTHENTICATION_CRYPTO_VARIANT_AFTER_AUTOSAR_R20_11)
  #error "DCM_AUTHENTICATION_CRYPTO_VARIANT_AFTER_AUTOSAR_R20_11 is already defined"
#endif
#define DCM_AUTHENTICATION_CRYPTO_VARIANT_AFTER_AUTOSAR_R20_11 0x01U

#if (defined DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT)
#error DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT already defined
#endif
/** \brief Crypto stack compatibility */
#define DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT                 [!//
[!IF "node:exists(as:modconf('Csm')[1]/CsmJobs/CsmJob/eb-list::*/CsmProcessingMode)"!] [!//
DCM_AUTHENTICATION_CRYPTO_VARIANT_AFTER_AUTOSAR_R20_11
[!ELSE!][!//
DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11
[!ENDIF!]

/*==================[type definitions]===========================================================*/

#if (DCM_MAX_CHALLENGE_LENGTH > 0xFFU)
/** \brief Define the size of the challenge length */
typedef uint16 Dcm_ChallengeLengthType;
#else
/** \brief Define the size of the challenge length */
typedef uint8 Dcm_ChallengeLengthType;
#endif

[!IF "$AUTHENTICATION_GENERAL_NRC_MODERULE = 'STD_ON'"!]
/** \brief Type for Dcm mode rule function */
typedef P2FUNC(boolean, DCM_APPL_CODE, Dcm_AuthenticationModeRuleFunctionType)
  (P2VAR(uint8, AUTOMATIC, DCM_VAR) Nrc);
[!ENDIF!]

[!IF "$DCM_AUTHENTICATION_IDLECONNECTIONTIMER = 'STD_ON'"!]
/** \brief Type for Authentication default session timeout value */
typedef uint32 Dcm_AuthenticationIdleTimerValueType;
[!ENDIF!]

[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
/** \brief Function pointer to DcmAuthenticationState SchM_Switch function */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_AuthenticationStateSchMSwitchFunctionType)
  (uint8 AuthenticationState);
[!IF "$DCM_RTE_USAGE = 'STD_ON'"!]
/** \brief Function pointer to DcmAuthenticationState Rte_Switch function */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_AuthenticationStateRteSwitchFunctionType)
  (uint8 AuthenticationState);
[!ENDIF!][!// DCM_RTE_USAGE
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationConnectionType,1 */
typedef struct
{
  /** \brief Csm Job Id of a random generate job for creating server challenge */
  uint32 RandomGenerateJobId;
  /** \brief Csm Job Id of a signature verify job for verifying proof of ownership client */
  uint32 SignatureVerifyJobId;
[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
  /** \brief ModeSwitch function pointer for DcmAuthenticationState 
             used by BswModuleEntities */
  Dcm_AuthenticationStateSchMSwitchFunctionType AuthenticationSchMSwitch;
[!IF "$DCM_RTE_USAGE = 'STD_ON'"!]
  /** \brief ModeSwitch function pointer for DcmAuthenticationState
             used by RunnableEntities */
  Dcm_AuthenticationStateRteSwitchFunctionType AuthenticationRteSwitch;
[!ENDIF!][!// DCM_RTE_USAGE
[!ENDIF!][!// DCM_MODEDECLARATION_SUPPORT
  /** \brief KeyM Certificate Id used to store the certificate of the client within the KeyM  */
  uint16 KeyMCertificateId;
  /** \brief KeyM Certificate Element Id of the role for the authenticated state  */
  uint16 RoleElementId;
[!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
  /** \brief KeyM Certificate Id used to store the certificate of the server within the KeyM */
  uint16 KeyMServerCertificateId;
[!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED
  /** \brief Length in byte of the ECU challenge */
  Dcm_ChallengeLengthType ChallengeLength;
[!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
  /** \brief Internal job index for signatureGenerate (zero based, consecutive) */
  uint8 SignatureGenerateJobDescriptorIndex;
[!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED
}
Dcm_AuthenticationConnectionType;

[!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
typedef struct
{
  /** \brief Buffer index for Dcm_AuthenticationSignedChallenge */
  uint32 BufferIndex;
  /** \brief Maximum size of the output signature length in bytes */
  uint32 MaxLengthOfSignedChallenge;
  /** \brief Csm Job Id of a signature generate job for signing client challenge */
  uint32 SignatureGenerateJobId;
}
Dcm_SignatureGenerateJobDescriptorType;
[!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationConfigType,1 */
typedef struct
{
  /** \brief Array for the configuration parameters of AuthenticationConnections */
  Dcm_AuthenticationConnectionType AuthenticationConnection[DCM_NUM_AUTHENTICATION_CONNECTIONS];

[!IF "$DCM_AUTHENTICATION_IDLECONNECTIONTIMER = 'STD_ON'"!]
  /** \brief Dcm Authentication default session timeout value */
  Dcm_AuthenticationIdleTimerValueType AuthenticationDefaultSessionTimeout;
[!ENDIF!][!// AUTHENTICATION_DEFAULTSESSION_TIMEOOUT

[!IF "$AUTHENTICATION_GENERAL_NRC_MODERULE = 'STD_ON'"!]
  /** \brief Dcm mode rule reference used to change NRC with GeneralNRC */
  Dcm_AuthenticationModeRuleFunctionType AuthenticationGeneralNRCModeRule;
[!ENDIF!][!// AUTHENTICATION_GENERAL_NRC_MODERULE

  /** \brief Role used in deauthenticated state for all connections */
  uint8 DeauthenticatedRole[DCM_DSP_AUTHENTICATION_ROLE_SIZE];

}
Dcm_AuthenticationConfigType;

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationConfigPtrType,1 */
/** \brief Pointer to authentication configuration */
typedef P2CONST(Dcm_AuthenticationConfigType, TYPEDEF, DCM_CONST) 
  Dcm_AuthenticationConfigPtrType;

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

/*==================[external constants]=========================================================*/
#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

extern CONST(Dcm_AuthenticationConfigPtrType, DCM_CONST) Dcm_AuthenticationConfigPtr;

[!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
extern CONST(Dcm_SignatureGenerateJobDescriptorType, DCM_CONST) Dcm_SignatureGenerateJobDescriptor[DCM_NUM_SIGNATUREGENERATE_JOBS];
[!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h> 
/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/
[!ENDIF!][!// DCM_AUTHENTICATION_CONNECTION
#endif /* ifndef DCM_AUTHENTICATION_CFG_H */
/*==================[end of file]================================================================*/
