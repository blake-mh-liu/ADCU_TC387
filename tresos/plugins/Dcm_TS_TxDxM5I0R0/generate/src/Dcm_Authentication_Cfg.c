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

/* !LINKSTO Dcm.Dsn.File.Authentication.ConfigC,1 */

/*==================[inclusions]=================================================================*/
[!AUTOSPACING!]
[!INDENT "0"!]
[!INCLUDE "../include/Dcm_common.m"!]
#include <Dcm_Authentication_Cfg.h>
[!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!][!//
#include <SchM_Dcm.h>
[!IF "$DCM_RTE_USAGE = 'STD_ON'"!]
#include <Rte_Dcm.h>
[!ENDIF!]
[!ENDIF!]
[!IF "$AUTHENTICATION_GENERAL_NRC_MODERULE = 'STD_ON'"!]
#include <Dcm_Cfg.h>                                           /* Generated configuration header */
[!ENDIF!]
[!IF "$DCM_AUTHENTICATION_CONNECTION = 'STD_ON'"!]
/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/
#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

/* !LINKSTO Dcm.EB.RequestVerification.AuthenticationCheck.RoleVerification.RoleFormat.LittleEndian,1 */
[!VAR "RoleValue" = "''"!]
[!VAR "Role" = "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationDeauthenticatedRole"!]
[!FOR "i" = "0" TO "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationRoleSize - 1"!]
  [!VAR "RoleValue"!]
    [!"num:inttohex($Role mod 256, 2)"!]U, [!//
    [!VAR "Role" = "$Role div 256"!]
    [!"$RoleValue"!][!//
  [!ENDVAR!]
[!ENDFOR!]

[!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
[!VAR "SignatureGenerateJobDescriptor" = "''"!]
[!VAR "SignatureGenerateJobIndex" = "0"!]
[!VAR "SignatureGenerateJobIds" = "'#'"!]
[!VAR "SignatureGenerateJobDescriptorEntry" = "''"!]
[!VAR "AuthenticationSignedChallengeBufferIndex" = "0"!]
[!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED

STATIC CONST(Dcm_AuthenticationConfigType, DCM_CONST) Dcm_AuthenticationConfig =
{
  [!INDENT "2"!] 
  /* AuthenticationConnection Array */
  {
    [!INDENT "4"!]
    [!LOOP "DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationConnection/eb-list::*"!]
    {
      [!INDENT "6"!] 
      [!"node:ref(DcmDspAuthenticationRandomJobRef)/CsmJobId"!]U, /* RandomGenerateJobId */
      [!"node:ref(DcmDspAuthenticationVerifyProofOfOwnerShipClientJobRef)/CsmJobId"!]U, /* SignatureVerifyJobId */
      [!IF "$DCM_MODEDECLARATION_SUPPORT = 'STD_ON'"!]
        &SchM_Switch_Dcm_DcmAuthenticationState_[!"as:name(node:ref(DcmDspAuthenticationConnectionMainConnectionRef))"!],
        [!IF "$DCM_RTE_USAGE = 'STD_ON'"!]
          &Rte_Switch_AuthenticationStateModeSwitchInterface_[!"as:name(node:ref(DcmDspAuthenticationConnectionMainConnectionRef))"!]_authenticationState,
        [!ENDIF!]
      [!ENDIF!]
      [!"node:ref(DcmDspAuthenticationConnectionCertificateRef)/KeyMCertificateId"!]U, /* KeyMCertificateId */
      [!"node:ref(DcmDspAuthenticationRoleElementRef)/KeyMCertificateElementId"!]U, /* RoleElementId */
      [!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
        [!"node:ref(DcmDspAuthenticationECUCertificateRef)/KeyMCertificateId"!]U, /* KeyMServerCertificateId */
      [!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED
      [!"DcmDspAuthenticationEcuChallengeLength"!]U, /* ChallengeLength */[!//
      [!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
        [!VAR "SignatureGenerateJobId" = "node:ref(DcmDspAuthenticationClientChallengeSignJobRef)/CsmJobId"!]
        [!IF "not(contains($SignatureGenerateJobIds, concat('#', $SignatureGenerateJobId, '|')))"!]
          [!// Found new job entry
          [!VAR "SignatureGenerateJobIds" = "concat($SignatureGenerateJobIds, $SignatureGenerateJobId, '|', num:i($SignatureGenerateJobIndex), '#')"!]
          [!VAR "SignatureGenerateJobDescriptorIndex" = "num:i($SignatureGenerateJobIndex)"!]
          [!VAR "MaxLengthOfSignedChallenge" = "node:ref(node:ref(DcmDspAuthenticationClientChallengeSignJobRef)/CsmJobPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateResultLength"!]
          [!VAR "SignatureGenerateJobDescriptorEntry"!]
            [!"$SignatureGenerateJobDescriptorEntry"!][!//
            [!INDENT "2"!] 
            {
              [!INDENT "4"!] 
              [!"num:i($AuthenticationSignedChallengeBufferIndex)"!], /* BufferIndex */
              [!"$MaxLengthOfSignedChallenge"!], /* MaxLengthOfSignedChallenge */
              [!"$SignatureGenerateJobId"!] /* SignatureGenerateJobId */
              [!ENDINDENT!] 
            }, /* index: [!"num:i($SignatureGenerateJobIndex)"!] */
            [!ENDINDENT!] 
          [!ENDVAR!]
          [!VAR "SignatureGenerateJobIndex" = "$SignatureGenerateJobIndex + 1"!]
          [!VAR "AuthenticationSignedChallengeBufferIndex" = "$AuthenticationSignedChallengeBufferIndex + $MaxLengthOfSignedChallenge"!]
        [!ELSE!]
          [!// Found existing job entry
          [!VAR "SignatureGenerateJobDescriptorIndex" = "substring-before(substring-after($SignatureGenerateJobIds, concat('#', $SignatureGenerateJobId, '|')), "#")"!]
        [!ENDIF!]
        [!"num:i($SignatureGenerateJobDescriptorIndex)"!]U, /* SignatureGenerateJobDescriptorIndex */
      [!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED
      [!ENDINDENT!]
    },
    [!ENDLOOP!]
    [!ENDINDENT!]
  },
  [!IF "$DCM_AUTHENTICATION_IDLECONNECTIONTIMER = 'STD_ON'"!]
     [!"num:integer(ceiling(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationDefaultSessionTimeOut div DcmConfigSet/eb-list::*[1]/DcmGeneral/DcmTaskTime))"!]U, /* Authentication default session timeout */
  [!ENDIF!]
  [!IF "$AUTHENTICATION_GENERAL_NRC_MODERULE = 'STD_ON'"!]
    &Dcm_ModeRule_[!"as:name(as:ref(DcmConfigSet/eb-list::*[1]/DcmDsp/DcmDspAuthentication/DcmDspAuthenticationGeneralNRCModeRuleRef))"!]_Result, /* Authentication GeneralNRC Mode rule reference */
  [!ENDIF!]
  { [!"$RoleValue"!]} /* DeauthenticatedRole */
  [!ENDINDENT!]
};

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>
/*==================[internal data]==============================================================*/

/*==================[external constants]=========================================================*/
#define DCM_START_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

CONST(Dcm_AuthenticationConfigPtrType, DCM_CONST) 
  Dcm_AuthenticationConfigPtr = &Dcm_AuthenticationConfig;

[!IF "$DCM_0X29_0X02_SSVC_ENABLED = 'STD_ON'"!]
CONST(Dcm_SignatureGenerateJobDescriptorType, DCM_CONST) Dcm_SignatureGenerateJobDescriptor[] =
{
  [!WS "2"!][!"$SignatureGenerateJobDescriptorEntry"!][!//
}; 
[!ENDIF!][!// DCM_0X29_0X02_SSVC_ENABLED

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/
[!ENDIF!][!// DCM_AUTHENTICATION_CONNECTION
[!ENDINDENT!]

/*==================[end of file]================================================================*/
