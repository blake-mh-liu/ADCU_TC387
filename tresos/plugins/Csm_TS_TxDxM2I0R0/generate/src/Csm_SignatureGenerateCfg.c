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
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmSignatureGenerate/CsmSignatureGenerateConfig/*))"!][!//
[!INDENT "0"!][!//
  [!VAR "ServiceEnabled" = "'true'"!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!//
/*==================[includes]====================================================================*/

[!IF "(CsmGeneral/CsmRteUsage = 'true') and (count(CsmSignatureGenerate/CsmSignatureGenerateConfig/*[(CsmSignatureGenerateEnableRteInterface = 'true')]) > 0)"!][!//
#include <Rte_Csm.h>
[!ENDIF!][!//
#include <Csm_Types.h>
#include <Csm_SignatureGenerateCfg.h>

[!IF "$ServiceEnabled = 'true'"!][!//
[!//
[!VAR "CsmInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Csm')/CsmSignatureGenerate/CsmSignatureGenerateConfig/*,'node:value(./CsmSignatureGeneratePrimitiveName)')"!][!//
[!IF "$CsmInclude != node:value(./CsmSignatureGeneratePrimitiveName)"!][!//
[!VAR "CsmInclude" = "node:value(./CsmSignatureGeneratePrimitiveName)"!][!//
#include <Cry_[!"node:value(./CsmSignatureGeneratePrimitiveName)"!].h>
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
CONST(Csm_SignatureGenerateConfigType, CSM_CONST)
  Csm_SignatureGenerateConfigurations[[!"num:i(count(as:modconf('Csm')/CsmSignatureGenerate/CsmSignatureGenerateConfig/*))"!]] =
{
[!LOOP "as:modconf('Csm')/CsmSignatureGenerate/CsmSignatureGenerateConfig/*"!][!//
  {
[!IF "as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing = 'false'"!][!//
[!IF "(as:modconf('Csm')/CsmGeneral/CsmRteUsage = 'false') or (./CsmSignatureGenerateEnableRteInterface='false')"!][!//
    &[!"node:value(./CsmCallbackSignatureGenerate)"!],
[!ELSE!][!//
    &Rte_Call_PNJobFinished_CsmSignatureGenerate_[!"name(.)"!]_JobFinished,
[!ENDIF!][!//
[!ELSE!][!//
    /* !LINKSTO EB_CSM_SDS_0001,1 */
[!IF "node:exists(./CsmCallbackSignatureGenerate) and (node:value(./CsmCallbackSignatureGenerate) != '')"!][!//
    &[!"node:value(./CsmCallbackSignatureGenerate)"!],
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
    &Cry_[!"node:value(./CsmSignatureGeneratePrimitiveName)"!]Start,
    &Cry_[!"node:value(./CsmSignatureGeneratePrimitiveName)"!]Update,
    &Cry_[!"node:value(./CsmSignatureGeneratePrimitiveName)"!]Finish,
    &Cry_[!"node:value(./CsmSignatureGeneratePrimitiveName)"!]MainFunction,
    &([!"node:value(./CsmSignatureGenerateInitConfiguration)"!]),
[!IF "(./CsmSignatureGenerateEnableRestart) = 'true'"!][!//
    TRUE,
[!ELSE!][!//
    FALSE,
[!ENDIF!][!//
[!IF "node:exists(./CsmSignatureGenerateUsePriorities)"!][!//
[!IF "(./CsmSignatureGenerateUsePriorities) = 'true'"!][!//
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
typedef void Csm_SignatureGenerateCfg_EmptyTranslationUnit_t;

[!ENDIF!][!/* [!IF "$ServiceEnabled != 'true'"!] */!][!//
[!//
/*==================[end of file]=================================================================*/

