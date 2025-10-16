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

[!VAR "ServiceEnabled" = "'false'"!][!//
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSignatureVerify/CsmSignatureVerifyConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSignatureVerify/CsmSignatureVerifyConfig/*[(CsmSignatureVerifyEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_SignatureVerifyCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmSignatureVerify/CsmSignatureVerifyConfig/*,'node:value(./CsmSignatureVerifyPrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmSignatureVerifyPrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmSignatureVerifyPrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmSignatureVerifyPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
#define CSM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO CSM0025, 1
 */
/* !LINKSTO CSM0535, 1
 */
CONST(Csm_SignatureVerifyConfigType, CSM_CONST)
  Csm_SignatureVerifyConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSignatureVerify/CsmSignatureVerifyConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmSignatureVerify/CsmSignatureVerifyConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmSignatureVerifyEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackSignatureVerify)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmSignatureVerify_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackSignatureVerify) and (node:value(./CsmCallbackSignatureVerify) != '')"!][!//
    &[!"node:value(./CsmCallbackSignatureVerify)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmSignatureVerifyPrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmSignatureVerifyPrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmSignatureVerifyPrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmSignatureVerifyPrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmSignatureVerifyInitConfiguration)"!]),
[!IF "(./CsmSignatureVerifyEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmSignatureVerifyUsePriorities)"!][!//
[!IF "(./CsmSignatureVerifyUsePriorities) = 'true'"!][!//
    TRUE
[!ELSE!][!//
    FALSE
[!ENDIF!][!//
[!ENDIF!][!//
  },
[!ENDLOOP!][!//
};

#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!/* [!IF "$ServiceEnabled = 'true'"!] */!][!//
[!//
/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

[!IF "$ServiceEnabled != 'true'"!][!//
[!//
/** \brief  Dummy definition preventing this file from being empty, if there is no configuration. */
typedef void Csm_SignatureVerifyCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

